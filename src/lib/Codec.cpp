//=============================================================================
// Codec
// encoding names are specified in http://www.iana.org/assignments/character-sets
//=============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// CodecFactory
//-----------------------------------------------------------------------------
CodecFactoryList CodecFactory::_codecFactoryList;

CodecFactory::CodecFactory(String encoding) : _encoding(std::move(encoding))
{
}

void CodecFactory::Register(CodecFactory* pCodecFactory)
{
	GetList().push_back(pCodecFactory);
}

CodecFactory* CodecFactory::Lookup(const char* encoding)
{
	if (encoding == nullptr) return nullptr;
	for (CodecFactory* pCodecFactory : GetList()) {
		if (::strcasecmp(pCodecFactory->GetEncoding(), encoding) == 0) {
			return pCodecFactory;
		}
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
// Codec
//-----------------------------------------------------------------------------
CodecFactory* Codec::_pCodecFactory_Dumb = nullptr;
RefPtr<Codec> Codec::Dumb;

Codec::Codec(CodecFactory* pCodecFactory, Decoder* pDecoder, Encoder* pEncoder) :
	_pCodecFactory(pCodecFactory), _pDecoder(pDecoder), _pEncoder(pEncoder)
{
}

Codec* Codec::Duplicate() const
{
	return _pCodecFactory->CreateCodec(_pDecoder->GetDelcrFlag(), _pEncoder->GetAddcrFlag());
}

Codec* Codec::Create(const char* encoding, bool delcrFlag, bool addcrFlag)
{
	if (encoding == nullptr) {
		return _pCodecFactory_Dumb->CreateCodec(delcrFlag, addcrFlag);
	}
	CodecFactory* pCodecFactory = CodecFactory::Lookup(encoding);
	if (pCodecFactory == nullptr) {
		Error::Issue(ErrorType::CodecError, "unsupported encoding: %s", encoding);
		return nullptr;
	}
	return pCodecFactory->CreateCodec(delcrFlag, addcrFlag);
}

void Codec::Bootup()
{
	_pCodecFactory_Dumb = new CodecFactoryTmpl<Codec_Dumb>("dumb");
	CodecFactory::Register(_pCodecFactory_Dumb);
	bool delcrFlag = true;
	bool addcrFlag = false;
	Dumb.reset(_pCodecFactory_Dumb->CreateCodec(delcrFlag, addcrFlag));
}

UShort Codec::DBCSToUTF16(const CodeRow codeRows[], int nCodeRows, UShort codeDBCS)
{
	int codeH = (codeDBCS >> 8) & 0xff;
	int codeL = codeDBCS & 0xff;
	if (codeH >= nCodeRows) return 0x0000;
	const CodeRow &codeRow = codeRows[codeH];
	if (codeH == 0) {
		return (codeL < codeRow.nCols)? codeRow.row[codeL] : 0x0000;
	} else if (codeL < 0x40) {
		return 0x0000;
	} else {
		int iCol = codeL - 0x40;
		return (iCol < codeRow.nCols)? codeRow.row[iCol] : 0x0000;
	}
}

UShort Codec::UTF16ToDBCS(const CodeRow codeRows[], int nCodeRows, UShort codeUTF16, Map** ppMap)
{
	Map* pMap = *ppMap;
	if (*ppMap == nullptr) {
		*ppMap = new Map();
		pMap = *ppMap;
		const CodeRow* pCodeRow = codeRows;
		for (int codeL = 0; codeL < pCodeRow->nCols; codeL++) {
			UShort codeUTF16 = pCodeRow->row[codeL];
			UShort codeDBCS = static_cast<UShort>(codeL);
			if (pMap->find(codeUTF16) == pMap->end()) {
				(*pMap)[codeUTF16] = codeDBCS;
			}
		}
		pCodeRow++;
		for (int codeH = 1; codeH < nCodeRows; codeH++, pCodeRow++) {
			UShort codeDBCSBase = static_cast<UShort>(codeH << 8);
			for (int iCol = 0; iCol < pCodeRow->nCols; iCol++) {
				UShort codeUTF16 = pCodeRow->row[iCol];
				if (codeUTF16 == 0x0000) continue;
				UShort codeL = static_cast<UShort>(iCol + 0x40);
				UShort codeDBCS = codeDBCSBase + codeL;
				//printf("%04x -> %04x\n", codeUTF16, codeDBCS);
				if (pMap->find(codeUTF16) == pMap->end()) {
					(*pMap)[codeUTF16] = codeDBCS;
				}
			}
		}
	}
	Map::iterator iter = pMap->find(codeUTF16);
	return (iter == pMap->end())? 0x0000 : iter->second;
}

Codec::WidthProp Codec::GetWidthProp(UInt32 codeUTF32)
{
	for (const WidthInfo* p = _widthInfoTbl; p->codeUTF32Ceil != 0x000000; p++) {
		if (codeUTF32 < p->codeUTF32Ceil) return p->widthProp;
	}
	return WidthProp::N;
}

String Codec::ToString(const StringStyle& ss) const
{
	String str;
	str += "Codec:";
	str += GetEncoding();
	return str;
}

//-----------------------------------------------------------------------------
// Codec::BOM
//-----------------------------------------------------------------------------
// Byte Order Mark of Unicode
const char* const Codec::BOM::UTF8		= "\xef\xbb\xbf";
const char* const Codec::BOM::UTF16BE	= "\xfe\xff";
const char* const Codec::BOM::UTF16LE	= "\xff\xfe";
const char* const Codec::BOM::UTF32BE	= "\x00\x00\xfe\xff";
const char* const Codec::BOM::UTF32LE	= "\xff\xfe\x00\x00";

//-----------------------------------------------------------------------------
// Codec::DecEncBase
//-----------------------------------------------------------------------------
bool Codec::DecEncBase::FollowChar(char& chConv)
{
	if (_idxBuff <= 0) return false;
	chConv = _buffOut[--_idxBuff];
	return true;
}

Codec::Result Codec::DecEncBase::Flush(char& chConv)
{
	return Result::None;
}

//-----------------------------------------------------------------------------
// Codec::Decoder
//-----------------------------------------------------------------------------
bool Codec::Decoder::Decode(String& dst, const UInt8* src, size_t bytes)
{
	char ch;
	for (const UInt8* p = src; bytes > 0; p++, bytes--) {
		Codec::Result rslt = FeedChar(*p, ch);
		if (rslt == Codec::Result::Complete) {
			dst.push_back(ch);
			while (FollowChar(ch)) dst.push_back(ch);
		} else if (rslt == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "failed to decode a binary");
			return false;
		}
	}
	if (Flush(ch) == Codec::Result::Complete) {
		dst.push_back(ch);
		while (FollowChar(ch)) dst.push_back(ch);
	}
	return true;
}

//-----------------------------------------------------------------------------
// Codec::Encoder
//-----------------------------------------------------------------------------
bool Codec::Encoder::Encode(Binary& dst, const char* src)
{
	char ch;
	for (const char* p = src; *p != '\0'; p++) {
		Codec::Result rslt = FeedChar(*p, ch);
		if (rslt == Codec::Result::Complete) {
			dst.push_back(ch);
			while (FollowChar(ch)) dst.push_back(ch);
		} else if (rslt == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "failed to encode a string");
			return false;
		}
	}
	if (Flush(ch) == Codec::Result::Complete) {
		dst.push_back(ch);
		while (FollowChar(ch)) dst.push_back(ch);
	}
	return true;
}

//-----------------------------------------------------------------------------
// Codec_Dumb
//-----------------------------------------------------------------------------
Codec::Result Codec_Dumb::Decoder::FeedChar(char ch, char& chConv)
{
	if (GetDelcrFlag() && ch == '\r') return Codec::Result::None;
	chConv = ch;
	return Codec::Result::Complete;
}

Codec::Result Codec_Dumb::Encoder::FeedChar(char ch, char& chConv)
{
	if (GetAddcrFlag() && ch == '\n') {
		StoreChar('\n');
		chConv = '\r';
	} else {
		chConv = ch;
	}
	return Codec::Result::Complete;
}

//-----------------------------------------------------------------------------
// Codec_UTF
//-----------------------------------------------------------------------------
Codec::Result Codec_UTF::Decoder::FeedUTF32(UInt32 codeUTF32, char& chConv)
{
	_idxBuff = 0;
	if ((codeUTF32 & ~0x7f) == 0) {
		chConv = static_cast<char>(codeUTF32);
		return Codec::Result::Complete;
	}
	StoreChar(0x80 | static_cast<char>(codeUTF32 & 0x3f)); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x1f) == 0) {
		chConv = 0xc0 | static_cast<char>(codeUTF32);
		return Codec::Result::Complete;
	}
	StoreChar(0x80 | static_cast<char>(codeUTF32 & 0x3f)); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x0f) == 0) {
		chConv = 0xe0 | static_cast<char>(codeUTF32);
		return Codec::Result::Complete;
	}
	StoreChar(0x80 | static_cast<char>(codeUTF32 & 0x3f)); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x07) == 0) {
		chConv = 0xf0 | static_cast<char>(codeUTF32);
		return Codec::Result::Complete;
	}
	StoreChar(0x80 | static_cast<char>(codeUTF32 & 0x3f)); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x03) == 0) {
		chConv = 0xf8 | static_cast<char>(codeUTF32);
		return Codec::Result::Complete;
	}
	StoreChar(0x80 | static_cast<char>(codeUTF32 & 0x3f)); codeUTF32 >>= 6;
	chConv = 0xfc | static_cast<char>(codeUTF32);
	return Codec::Result::Complete;
}

Codec::Result Codec_UTF::Encoder::FeedChar(char ch, char& chConv)
{
	if (ch == '\n') {
		if (GetAddcrFlag()) {
			StoreChar('\n');
			chConv = '\r';
		} else {
			chConv = ch;
		}
		return Codec::Result::Complete;
	}
	Codec::Result rtn = Codec::Result::None;
	UChar _ch = static_cast<UChar>(ch);
	if ((_ch & 0x80) == 0x00) {
		rtn = FeedUTF32(_ch, chConv);
		_cntChars = 0;
	} else if ((_ch & 0xc0) == 0x80) {
		if (_cntChars == 1) {
			_codeUTF32 = (_codeUTF32 << 6) | (_ch & 0x3f);
			rtn = FeedUTF32(_codeUTF32, chConv);
			_codeUTF32 = 0x00000000;
			_cntChars = 0;
		} else if (_cntChars > 0) {
			_codeUTF32 = (_codeUTF32 << 6) | (_ch & 0x3f);
			_cntChars--;
		} else {
			_codeUTF32 = 0x00000000;
		}
	} else if ((_ch & 0xe0) == 0xc0) {
		_codeUTF32 = _ch & 0x1f;
		_cntChars = 1;
	} else if ((_ch & 0xf0) == 0xe0) {
		_codeUTF32 = _ch & 0x0f;
		_cntChars = 2;
	} else if ((_ch & 0xf8) == 0xf0) {
		_codeUTF32 = _ch & 0x07;
		_cntChars = 3;
	} else if ((_ch & 0xfc) == 0xf8) {
		_codeUTF32 = _ch & 0x03;
		_cntChars = 4;
	} else {
		_codeUTF32 = _ch & 0x01;
		_cntChars = 5;
	}
	return rtn;
}

//-----------------------------------------------------------------------------
// Codec_SBCS
//-----------------------------------------------------------------------------
Codec::Result Codec_SBCS::Decoder::FeedChar(char ch, char& chConv)
{
	if (GetDelcrFlag() && ch == '\r') return Codec::Result::None;
	chConv = static_cast<UChar>(_tblToUTF16[static_cast<UChar>(ch)]);
	return (chConv == '\0')? Result::Error : Result::Complete;
}

Codec::Result Codec_SBCS::Encoder::FeedUTF32(UInt32 codeUTF32, char& chConv)
{
	auto pPair = _mapToSBCS.find(static_cast<UShort>(codeUTF32));
	if (pPair == _mapToSBCS.end()) return Result::Error;
	chConv = static_cast<UChar>(pPair->second);
	return Result::Complete;
}

//-----------------------------------------------------------------------------
// CodecFactory_SBCS
//-----------------------------------------------------------------------------
CodecFactory_SBCS::CodecFactory_SBCS(String encoding, const UInt16* tblToUTF16) :
	CodecFactory(std::move(encoding)), _tblToUTF16(tblToUTF16)
{
	for (int codeSBCS = 0; codeSBCS < 256; codeSBCS++) {
		UInt16 codeUTF16 = _tblToUTF16[codeSBCS];
		_mapToSBCS[codeUTF16] = codeSBCS;
	}
}

Codec* CodecFactory_SBCS::CreateCodec(bool delcrFlag, bool addcrFlag)
{
	return new Codec_SBCS(
		this, new typename Codec_SBCS::Decoder(delcrFlag, _tblToUTF16),
		new typename Codec_SBCS::Encoder(addcrFlag, _mapToSBCS));
}

//-----------------------------------------------------------------------------
// Codec_DBCS
//-----------------------------------------------------------------------------
Codec::Result Codec_DBCS::Decoder::FeedChar(char ch, char& chConv)
{
	if (GetDelcrFlag() && ch == '\r') return Codec::Result::None;
	UChar _ch = static_cast<UChar>(ch);
	UInt32 codeUTF32 = 0x00000000;
	if (_codeDBCS == 0x0000) {
		if (IsLeadByte(_ch)) {
			_codeDBCS = _ch;
			return Result::None;
		}
		codeUTF32 = DBCSToUTF16(_ch);
	} else {
		_codeDBCS = (_codeDBCS << 8) | _ch;
		codeUTF32 = DBCSToUTF16(_codeDBCS);
		_codeDBCS = 0x0000;
	}
	if (GetDelcrFlag() && codeUTF32 == '\r') return Result::None;
	return FeedUTF32(codeUTF32, chConv);
}

Codec::Result Codec_DBCS::Encoder::FeedUTF32(UInt32 codeUTF32, char& chConv)
{
	UShort codeDBCS = UTF16ToDBCS(static_cast<UShort>(codeUTF32));
	if (codeDBCS == 0x0000) {
		chConv = '\0';
		return Result::Error;
	} else if ((codeDBCS & ~0xff) == 0) {
		char ch = static_cast<char>(codeDBCS & 0xff);
		if (GetAddcrFlag() && ch == '\n') {
			StoreChar('\n');
			chConv = '\r';
		} else {
			chConv = ch;
		}
	} else {
		StoreChar(static_cast<char>(codeDBCS & 0xff));
		chConv = static_cast<char>(codeDBCS >> 8);
	}
	return Result::Complete;
}

}
