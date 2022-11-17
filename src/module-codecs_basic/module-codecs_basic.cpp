//==============================================================================
// module-codecs_basic.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs_basic)

//-----------------------------------------------------------------------------
// Codec_UTF8
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Codec_UTF8 : public Codec {
public:
	using Codec::Codec;
public:
	class GURAX_DLLDECLARE Decoder : public Codec::Decoder {
	private:
		UInt32 _codeUTF32;
		size_t _nFollowers;
	public:
		explicit Decoder(bool delcrFlag) :
				Codec::Decoder(delcrFlag), _codeUTF32(0), _nFollowers(0) {}
		virtual Result FeedData(UInt8 data, UInt32* pCodeUTF32) override;
	};
	class GURAX_DLLDECLARE Encoder : public Codec::Encoder {
	public:
		explicit Encoder(bool addcrFlag) : Codec::Encoder(addcrFlag) {}
		virtual Result FeedChar(char ch, UInt8* buffRtn, size_t* pCnt) override;
	};
};

Codec::Result Codec_UTF8::Decoder::FeedData(UInt8 data, UInt32* pCodeUTF32)
{
	if (GetDelcrFlag() && data == '\r') return Result::None;
	Codec::Result rtn = Result::None;
	if ((data & 0x80) == 0x00) {
		*pCodeUTF32 = data;
		rtn = Result::Complete;
	} else if (_nFollowers > 0) {
		if ((data & 0xc0) == 0x80) {
			_codeUTF32 = (_codeUTF32 << 6) | (data & 0x3f);
		} else {
			_codeUTF32 <<= 6;
		}
		_nFollowers--;
		if (_nFollowers == 0) {
			*pCodeUTF32 = _codeUTF32;
			rtn = Result::Complete;
		}
	} else if ((data & 0xe0) == 0xc0) {
		_codeUTF32 = data & 0x1f;
		_nFollowers = 1;
	} else if ((data & 0xf0) == 0xe0) {
		_codeUTF32 = data & 0x0f;
		_nFollowers = 2;
	} else if ((data & 0xf8) == 0xf0) {
		_codeUTF32 = data & 0x07;
		_nFollowers = 3;
	} else if ((data & 0xfc) == 0xf8) {
		_codeUTF32 = data & 0x03;
		_nFollowers = 4;
	} else {
		_codeUTF32 = data & 0x01;
		_nFollowers = 5;
	}
	return rtn;
}

Codec::Result Codec_UTF8::Encoder::FeedChar(char ch, UInt8* buffRtn, size_t* pCnt)
{
	if (GetAddcrFlag() && ch == '\n') {
		buffRtn[0] = '\r', buffRtn[1] = '\n';
		*pCnt = 2;
	} else {
		buffRtn[0] = static_cast<UInt8>(ch);
		*pCnt = 1;
	}
	return Result::Complete;
}

//-----------------------------------------------------------------------------
// Codec_UTF16
//-----------------------------------------------------------------------------
template<Endian endian>
class Codec_UTF16 : public Codec_UTF {
public:
	class Decoder : public Codec_UTF::Decoder {
	private:
		size_t _nChars;
		UInt32 _codeUTF16;
		UInt32 _codeUTF16Pair;
	public:
		Decoder(bool delcrFlag) : Codec_UTF::Decoder(delcrFlag),
							_nChars(0), _codeUTF16(0), _codeUTF16Pair(0) {}
		virtual Result FeedData(UInt8 data, UInt32* pCodeUTF32) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF16, UInt8* buffRtn, size_t* pCnt) override;
	};
};

template<Endian endian>
Codec::Result Codec_UTF16<endian>::Decoder::FeedData(UInt8 data, UInt32* pCodeUTF32)
{
	if constexpr (endian == Endian::Little) {
		_codeUTF16 = (_codeUTF16 >> 8) + (static_cast<UInt32>(data) << 8);
	} else { // endian == Endian::Big
		_codeUTF16 = (_codeUTF16 << 8) + data;
	}
	_nChars++;
	if (_nChars < 2) return Result::None;
	UInt32 codeUTF16 = _codeUTF16;
	_nChars = 0, _codeUTF16 = 0;;
	if (codeUTF16 == 0xfeff || (GetDelcrFlag() && codeUTF16 == '\r')) {
		return Codec::Result::None;
	} else if (_codeUTF16Pair) {
		*pCodeUTF32 = ((_codeUTF16Pair & 0x03ff) << 10) + (codeUTF16 & 0x03ff) + 0x10000;
		_codeUTF16Pair = 0;
		return Result::Complete;
	} else if ((codeUTF16 & 0xf800) == 0xd800) {
		_codeUTF16Pair = codeUTF16;
		return Result::None;
	} else {
		*pCodeUTF32 = codeUTF16;
		return Result::Complete;
	}
}

template<Endian endian>
Codec::Result Codec_UTF16<endian>::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt)
{
	if (GetAddcrFlag() && codeUTF32 == '\n') {
		if constexpr (endian == Endian::Little) {
			buffRtn[0] = '\r';
			buffRtn[1] = '\0';
			buffRtn[2] = '\n';
			buffRtn[3] = '\0';
			*pCnt = 4;
		} else { // endian == Endian::Big
			buffRtn[0] = '\0';
			buffRtn[1] = '\r';
			buffRtn[2] = '\0';
			buffRtn[3] = '\n';
			*pCnt = 4;
		}
	} else if (0x00010000 <= codeUTF32 && codeUTF32 <= 0x0010ffff) {
		UInt32 codePair1 = 0xd800 + ((codeUTF32 - 0x10000) >> 10);
		UInt32 codePair2 = 0xdc00 + (codeUTF32 & 0x03ff);
		if constexpr (endian == Endian::Little) {
			buffRtn[0] = static_cast<UInt8>(codePair1 >> 0);
			buffRtn[1] = static_cast<UInt8>(codePair1 >> 8);
			buffRtn[2] = static_cast<UInt8>(codePair2 >> 0);
			buffRtn[3] = static_cast<UInt8>(codePair2 >> 8);
			*pCnt = 4;
		} else { // endian == Endian::Big
			buffRtn[0] = static_cast<UInt8>(codePair1 >> 8);
			buffRtn[1] = static_cast<UInt8>(codePair1 >> 0);
			buffRtn[2] = static_cast<UInt8>(codePair2 >> 8);
			buffRtn[3] = static_cast<UInt8>(codePair2 >> 0);
			*pCnt = 4;
		}
	} else {
		if constexpr (endian == Endian::Little) {
			buffRtn[0] = static_cast<UInt8>(codeUTF32 >> 0);
			buffRtn[1] = static_cast<UInt8>(codeUTF32 >> 8);
			*pCnt = 2;
		} else { // endian == Endian::Big
			buffRtn[0] = static_cast<UInt8>(codeUTF32 >> 8);
			buffRtn[1] = static_cast<UInt8>(codeUTF32 >> 0);
			*pCnt = 2;
		}
	}
	return Result::Complete;
}

//-----------------------------------------------------------------------------
// Codec_UTF32
//-----------------------------------------------------------------------------
template<Endian endian>
class Codec_UTF32 : public Codec_UTF {
public:
	class Decoder : public Codec_UTF::Decoder {
	private:
		size_t _nChars;
		UInt32 _codeUTF32;
	public:
		Decoder(bool delcrFlag) : Codec_UTF::Decoder(delcrFlag), _nChars(0), _codeUTF32(0) {}
		virtual Result FeedData(UInt8 data, UInt32* pCodeUTF32) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt) override;
	};
};

template<Endian endian>
Codec::Result Codec_UTF32<endian>::Decoder::FeedData(UInt8 data, UInt32* pCodeUTF32)
{
	if constexpr (endian == Endian::Little) {
		_codeUTF32 = (_codeUTF32 >> 8) + (static_cast<UInt32>(data) << 24);
	} else { // endian == Endian::Big
		_codeUTF32 = (_codeUTF32 << 8) + data;
	}
	_nChars++;
	if (_nChars < 4) return Result::None;
	UInt32 codeUTF32 = _codeUTF32;
	_nChars = 0, _codeUTF32 = 0;
	if (codeUTF32 == 0xfeff || (GetDelcrFlag() && codeUTF32 == '\r')) {
		return Codec::Result::None;
	} else {
		*pCodeUTF32 = codeUTF32;
		return Result::Complete;
	}
}

template<Endian endian>
Codec::Result Codec_UTF32<endian>::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt)
{
	if (GetAddcrFlag() && codeUTF32 == '\n') {
		if constexpr (endian == Endian::Little) {
			buffRtn[0] = '\r';
			buffRtn[1] = '\0';
			buffRtn[2] = '\0';
			buffRtn[3] = '\0';
			buffRtn[4] = '\n';
			buffRtn[5] = '\0';
			buffRtn[6] = '\0';
			buffRtn[7] = '\0';
			*pCnt = 8;
		} else {
			buffRtn[0] = '\0';
			buffRtn[1] = '\0';
			buffRtn[2] = '\0';
			buffRtn[3] = '\r';
			buffRtn[4] = '\0';
			buffRtn[5] = '\0';
			buffRtn[6] = '\0';
			buffRtn[7] = '\n';
			*pCnt = 8;
		}
	} else {
		if constexpr (endian == Endian::Little) {
			buffRtn[0] = static_cast<UInt8>(codeUTF32 >> 0);
			buffRtn[1] = static_cast<UInt8>(codeUTF32 >> 8);
			buffRtn[2] = static_cast<UInt8>(codeUTF32 >> 16);
			buffRtn[3] = static_cast<UInt8>(codeUTF32 >> 24);
			*pCnt = 4;
		} else {
			buffRtn[0] = static_cast<UInt8>(codeUTF32 >> 24);
			buffRtn[1] = static_cast<UInt8>(codeUTF32 >> 16);
			buffRtn[2] = static_cast<UInt8>(codeUTF32 >> 8);
			buffRtn[3] = static_cast<UInt8>(codeUTF32 >> 0);
			*pCnt = 4;
		}
	}
	return Result::Complete;
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Registration of CodecFactory
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF8>("utf8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF8>("utf-8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF8>("utf_8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Big> >("utf16"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Big> >("utf16be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Big> >("utf-16be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Big> >("utf_16be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Little> >("utf16le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Little> >("utf-16le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF16<Endian::Little> >("utf_16le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf32"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf32be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf-32be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf_32be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Little> >("utf32le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Little> >("utf-32le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Little> >("utf_32le"));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_basic)
