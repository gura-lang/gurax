//==============================================================================
// module-codecs_basic.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs_basic)

//-----------------------------------------------------------------------------
// Codec_UTF16
//-----------------------------------------------------------------------------
template<Endian endian>
class Codec_UTF16 : public Codec_UTF {
public:
	class Decoder : public Codec_UTF::Decoder {
	private:
		size_t _nChars;
		UInt16 _codeUTF16;
	public:
		Decoder(bool delcrFlag) : Codec_UTF::Decoder(delcrFlag), _nChars(0), _codeUTF16(0) {}
		virtual Result FeedData(UInt8 data, char* buffRtn, size_t* pCnt) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF16, UInt8* buffRtn, size_t* pCnt) override;
	};
};

template<Endian endian>
Codec::Result Codec_UTF16<endian>::Decoder::FeedData(UInt8 data, char* buffRtn, size_t* pCnt)
{
	if (GetDelcrFlag() && data == '\r') return Codec::Result::None;
	if constexpr (endian == Endian::Little) {
		_codeUTF16 = (_codeUTF16 >> 8) + (static_cast<UInt16>(data) << 8);
	} else { // endian == Endian::Big
		_codeUTF16 = (_codeUTF16 << 8) + data;
	}
	_nChars++;
	if (_nChars < 2) return Codec::Result::None;
	UInt32 codeUTF32 = _codeUTF16;
	Codec::Result rtn = FeedUTF32(codeUTF32, buffRtn, pCnt);
	_nChars = 0, _codeUTF16 = 0;
	return rtn;
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
		UInt16 codePair1 = 0xd800 + static_cast<UInt16>((codeUTF32 - 0x10000) >> 16) +
								static_cast<UInt16>(codeUTF32 >> 10);
		UInt16 codePair2 = 0xdc00 + static_cast<UInt16>(codeUTF32 & 0x03ff);
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
		virtual Result FeedData(UInt8 data, char* buffRtn, size_t* pCnt) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt) override;
	};
};

template<Endian endian>
Codec::Result Codec_UTF32<endian>::Decoder::FeedData(UInt8 data, char* buffRtn, size_t* pCnt)
{
	if (GetDelcrFlag() && data == '\r') return Codec::Result::None;
	if constexpr (endian == Endian::Little) {
		_codeUTF32 = (_codeUTF32 >> 8) + (static_cast<UInt32>(data) << 24);
	} else { // endian == Endian::Big
		_codeUTF32 = (_codeUTF32 << 8) + data;
	}
	_nChars++;
	if (_nChars < 4) return Codec::Result::None;
	Codec::Result rtn = FeedUTF32(_codeUTF32, buffRtn, pCnt);
	_nChars = 0, _codeUTF32 = 0;
	return rtn;
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
	CodecFactory::Register(new CodecFactory_Generic<Codec_Dumb>("utf8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_Dumb>("utf-8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_Dumb>("utf_8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Little> >("utf32le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf32be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Little> >("utf-32le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf-32be"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Little> >("utf_32le"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_UTF32<Endian::Big> >("utf_32be"));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_basic)
