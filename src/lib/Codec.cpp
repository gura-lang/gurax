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
CodecFactory* CodecFactory::Dumb = nullptr;

CodecFactory::CodecFactory(String name) : _name(std::move(name))
{
}

void CodecFactory::Register(CodecFactory* pCodecFactory)
{
	GetList().push_back(pCodecFactory);
}

CodecFactory* CodecFactory::Lookup(const char* name)
{
	if (!name) return nullptr;
	for (CodecFactory* pCodecFactory : GetList()) {
		if (::strcasecmp(pCodecFactory->GetName(), name) == 0) {
			return pCodecFactory;
		}
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
// Codec
//-----------------------------------------------------------------------------
RefPtr<Codec> Codec::Dumb;

Codec::Codec(CodecFactory* pCodecFactory, Decoder* pDecoder, Encoder* pEncoder) :
	_pCodecFactory(pCodecFactory), _pDecoder(pDecoder), _pEncoder(pEncoder)
{
}

Codec* Codec::Duplicate() const
{
	return _pCodecFactory->CreateCodec(_pDecoder->GetDelcrFlag(), _pEncoder->GetAddcrFlag());
}

Codec* Codec::Create(const char* name, bool delcrFlag, bool addcrFlag)
{
	if (!name) {
		return CodecFactory::Dumb->CreateCodec(delcrFlag, addcrFlag);
	}
	CodecFactory* pCodecFactory = CodecFactory::Lookup(name);
	if (!pCodecFactory) {
		Error::Issue(ErrorType::CodecError, "unsupported encoding: %s", name);
		return nullptr;
	}
	return pCodecFactory->CreateCodec(delcrFlag, addcrFlag);
}

void Codec::Bootup()
{
	CodecFactory::Dumb = new CodecFactory_Generic<Codec_Dumb>("dumb");
	CodecFactory::Register(CodecFactory::Dumb);
	bool delcrFlag = true;
	bool addcrFlag = false;
	Dumb.reset(CodecFactory::Dumb->CreateCodec(delcrFlag, addcrFlag));
}

UInt16 Codec::DBCSToUTF16(const CodeRow codeRows[], int nCodeRows, UInt16 codeDBCS)
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

UInt16 Codec::UTF16ToDBCS(const CodeRow codeRows[], int nCodeRows, UInt16 codeUTF16, Map** ppMap)
{
	Map* pMap = *ppMap;
	if (!*ppMap) {
		*ppMap = new Map();
		pMap = *ppMap;
		const CodeRow* pCodeRow = codeRows;
		for (int codeL = 0; codeL < pCodeRow->nCols; codeL++) {
			UInt16 codeUTF16 = pCodeRow->row[codeL];
			UInt16 codeDBCS = static_cast<UInt16>(codeL);
			if (pMap->find(codeUTF16) == pMap->end()) {
				(*pMap)[codeUTF16] = codeDBCS;
			}
		}
		pCodeRow++;
		for (int codeH = 1; codeH < nCodeRows; codeH++, pCodeRow++) {
			UInt16 codeDBCSBase = static_cast<UInt16>(codeH << 8);
			for (int iCol = 0; iCol < pCodeRow->nCols; iCol++) {
				UInt16 codeUTF16 = pCodeRow->row[iCol];
				if (codeUTF16 == 0x0000) continue;
				UInt16 codeL = static_cast<UInt16>(iCol + 0x40);
				UInt16 codeDBCS = codeDBCSBase + codeL;
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
	return String().Format("Codec:%s%s%s", GetName(),
				GetDecoder().GetDelcrFlag()? ":delcr" : "",
				GetEncoder().GetAddcrFlag()? ":addcr" : "");
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
// Codec::Decoder
//-----------------------------------------------------------------------------
bool Codec::Decoder::Decode(String& dst, const UInt8* src, size_t bytes)
{
	char buffRtn[BuffSize];
	size_t cnt = 0;
	for (const UInt8* p = src; bytes > 0; p++, bytes--) {
		Codec::Result rslt = FeedData(*p, buffRtn, &cnt);
		if (rslt == Codec::Result::Complete) {
			for (size_t i = 0; i < cnt; i++) dst.push_back(buffRtn[i]);
		} else if (rslt == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "failed to decode a binary");
			return false;
		}
	}
	if (Flush(buffRtn, &cnt) == Codec::Result::Complete) {
		for (size_t i = 0; i < cnt; i++) dst.push_back(buffRtn[i]);
	}
	return true;
}

//-----------------------------------------------------------------------------
// Codec::Encoder
//-----------------------------------------------------------------------------
bool Codec::Encoder::Encode(Binary& dst, const char* src)
{
	UInt8 buffRtn[BuffSize];
	size_t cnt = 0;
	for (const char* p = src; *p != '\0'; p++) {
		Codec::Result rslt = FeedChar(*p, buffRtn, &cnt);
		if (rslt == Codec::Result::Complete) {
			for (size_t i = 0; i < cnt; i++) dst.push_back(buffRtn[i]);
		} else if (rslt == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "failed to encode a string");
			return false;
		}
	}
	if (Flush(buffRtn, &cnt) == Codec::Result::Complete) {
		for (size_t i = 0; i < cnt; i++) dst.push_back(buffRtn[i]);
	}
	return true;
}

//-----------------------------------------------------------------------------
// Codec_Dumb
//-----------------------------------------------------------------------------
Codec::Result Codec_Dumb::Decoder::FeedData(UInt8 data, char* buffRtn, size_t* pCnt)
{
	if (GetDelcrFlag() && data == '\r') return Codec::Result::None;
	buffRtn[0] = static_cast<char>(data);
	*pCnt = 1;
	return Codec::Result::Complete;
}

Codec::Result Codec_Dumb::Encoder::FeedChar(char ch, UInt8* buffRtn, size_t* pCnt)
{
	if (GetAddcrFlag() && ch == '\n') {
		buffRtn[0] = '\r', buffRtn[1] = '\n';
		*pCnt = 2;
	} else {
		buffRtn[0] = static_cast<UInt8>(ch);
		*pCnt = 1;
	}
	return Codec::Result::Complete;
}

//-----------------------------------------------------------------------------
// Codec_UTF
//-----------------------------------------------------------------------------
Codec::Result Codec_UTF::Decoder::FeedUTF32(UInt32 codeUTF32, char* buffRtn, size_t* pCnt)
{
	if ((codeUTF32 & ~0x7f) == 0) {
		buffRtn[0] = static_cast<char>(codeUTF32);
		*pCnt = 1;
		return Codec::Result::Complete;
	}
	char buffTmp[BuffSize];
	buffTmp[0] = 0x80 | static_cast<char>(codeUTF32 & 0x3f); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x1f) == 0) {
		buffRtn[0] = 0xc0 | static_cast<char>(codeUTF32);
		buffRtn[1] = buffTmp[0];
		*pCnt = 2;
		return Codec::Result::Complete;
	}
	buffTmp[1] = 0x80 | static_cast<char>(codeUTF32 & 0x3f); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x0f) == 0) {
		buffRtn[0] = 0xe0 | static_cast<char>(codeUTF32);
		buffRtn[1] = buffTmp[1];
		buffRtn[2] = buffTmp[0];
		*pCnt = 3;
		return Codec::Result::Complete;
	}
	buffTmp[2] = 0x80 | static_cast<char>(codeUTF32 & 0x3f); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x07) == 0) {
		buffRtn[0] = 0xf0 | static_cast<char>(codeUTF32);
		buffRtn[1] = buffTmp[2];
		buffRtn[2] = buffTmp[1];
		buffRtn[3] = buffTmp[0];
		*pCnt = 4;
		return Codec::Result::Complete;
	}
	buffTmp[3] = 0x80 | static_cast<char>(codeUTF32 & 0x3f); codeUTF32 >>= 6;
	if ((codeUTF32 & ~0x03) == 0) {
		buffRtn[0] = 0xf8 | static_cast<char>(codeUTF32);
		buffRtn[1] = buffTmp[3];
		buffRtn[2] = buffTmp[2];
		buffRtn[3] = buffTmp[1];
		buffRtn[4] = buffTmp[0];
		*pCnt = 5;
		return Codec::Result::Complete;
	}
	buffTmp[4] = 0x80 | static_cast<char>(codeUTF32 & 0x3f); codeUTF32 >>= 6;
	buffRtn[0] = 0xfc | static_cast<char>(codeUTF32);
	buffRtn[1] = buffTmp[4];
	buffRtn[2] = buffTmp[3];
	buffRtn[3] = buffTmp[2];
	buffRtn[4] = buffTmp[1];
	buffRtn[5] = buffTmp[0];
	*pCnt = 6;
	return Codec::Result::Complete;
}

Codec::Result Codec_UTF::Encoder::FeedChar(char ch, UInt8* buffRtn, size_t* pCnt)
{
	if (ch == '\n') {
		if (GetAddcrFlag()) {
			buffRtn[0] = '\r';
			buffRtn[1] = '\n';
			*pCnt = 2;
		} else {
			buffRtn[0] = ch;
			*pCnt = 1;
		}
		return Codec::Result::Complete;
	}
	Codec::Result rtn = Codec::Result::None;
	UChar _ch = static_cast<UChar>(ch);
	if ((_ch & 0x80) == 0x00) {
		rtn = FeedUTF32(_ch, buffRtn, pCnt);
		_cntChars = 0;
	} else if ((_ch & 0xc0) == 0x80) {
		if (_cntChars == 1) {
			_codeUTF32 = (_codeUTF32 << 6) | (_ch & 0x3f);
			rtn = FeedUTF32(_codeUTF32, buffRtn, pCnt);
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
Codec::Result Codec_SBCS::Decoder::FeedData(UInt8 data, char* buffRtn, size_t* pCnt)
{
	if (GetDelcrFlag() && data == '\r') return Codec::Result::None;
	buffRtn[0] = static_cast<UChar>(_tblToUTF16[data]);
	*pCnt = 1;
	return (buffRtn[0] == '\0')? Result::Error : Result::Complete;
}

Codec::Result Codec_SBCS::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt)
{
	auto pPair = _mapToSBCS.find(static_cast<UInt16>(codeUTF32));
	if (pPair == _mapToSBCS.end()) return Result::Error;
	buffRtn[0] = pPair->second;
	*pCnt = 1;
	return Result::Complete;
}

//-----------------------------------------------------------------------------
// CodecFactory_SBCS
//-----------------------------------------------------------------------------
CodecFactory_SBCS::CodecFactory_SBCS(String name, const UInt16* tblToUTF16) :
	CodecFactory(std::move(name)), _tblToUTF16(tblToUTF16)
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
Codec::Result Codec_DBCS::Decoder::FeedData(UInt8 data, char* buffRtn, size_t* pCnt)
{
	if (GetDelcrFlag() && data == '\r') return Codec::Result::None;
	//UChar _ch = data;
	UInt32 codeUTF32 = 0x00000000;
	if (_codeDBCS == 0x0000) {
		if (IsLeadByte(data)) {
			_codeDBCS = data;
			return Result::None;
		}
		codeUTF32 = DBCSToUTF16(data);
	} else {
		_codeDBCS = (_codeDBCS << 8) | data;
		codeUTF32 = DBCSToUTF16(_codeDBCS);
		_codeDBCS = 0x0000;
	}
	if (GetDelcrFlag() && codeUTF32 == '\r') return Result::None;
	return FeedUTF32(codeUTF32, buffRtn, pCnt);
}

Codec::Result Codec_DBCS::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt)
{
	UInt16 codeDBCS = UTF16ToDBCS(static_cast<UInt16>(codeUTF32));
	if (codeDBCS == 0x0000) {
		buffRtn[0] = '\0';
		*pCnt = 1;
		return Result::Error;
	} else if ((codeDBCS & ~0xff) == 0) {
		UInt8 data = static_cast<UInt8>(codeDBCS & 0xff);
		if (GetAddcrFlag() && data == '\n') {
			buffRtn[0] = '\r';
			buffRtn[1] = '\n';
			*pCnt = 2;
		} else {
			buffRtn[0] = data;
			*pCnt = 1;
		}
	} else {
		buffRtn[0] = static_cast<UInt8>(codeDBCS >> 8);
		buffRtn[1] = static_cast<UInt8>(codeDBCS & 0xff);
		*pCnt = 2;
	}
	return Result::Complete;
}

}
