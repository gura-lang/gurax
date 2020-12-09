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
		virtual Result FeedData(UInt8 data, char& chConv) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF16, UInt8& chConv) override;
	};
};

template<Endian endian>
Codec::Result Codec_UTF16<endian>::Decoder::FeedData(UInt8 data, char& chConv)
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
	Codec::Result rtn = FeedUTF32(codeUTF32, chConv);
	_nChars = 0, _codeUTF16 = 0;
	return rtn;
}

template<Endian endian>
Codec::Result Codec_UTF16<endian>::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8& dataConv)
{
	if (GetAddcrFlag() && codeUTF32 == '\n') {
		if constexpr (endian == Endian::Little) {
			StoreData('\0');	// 7th
			StoreData('\n');	// 4th
			StoreData('\0');	// 1st
			dataConv = '\r';	// 0th
		} else {
			StoreData('\n');	// 7th
			StoreData('\0');	// 4th
			StoreData('\r');	// 3rd
			dataConv = '\0';	// 0th
		}
	} else {
		if constexpr (endian == Endian::Little) {
			StoreData(static_cast<UInt8>(codeUTF32 >> 8));	// 1st
			dataConv = static_cast<UInt8>(codeUTF32 >> 0);	// 0th
		} else {
			StoreData(static_cast<UInt8>(codeUTF32 >> 0));	// 3rd
			StoreData(static_cast<UInt8>(codeUTF32 >> 8));	// 2nd
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
		virtual Result FeedData(UInt8 data, char& chConv) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, UInt8& chConv) override;
	};
};

template<Endian endian>
Codec::Result Codec_UTF32<endian>::Decoder::FeedData(UInt8 data, char& chConv)
{
	if (GetDelcrFlag() && data == '\r') return Codec::Result::None;
	if constexpr (endian == Endian::Little) {
		_codeUTF32 = (_codeUTF32 >> 8) + (static_cast<UInt32>(data) << 24);
	} else { // endian == Endian::Big
		_codeUTF32 = (_codeUTF32 << 8) + data;
	}
	_nChars++;
	if (_nChars < 4) return Codec::Result::None;
	Codec::Result rtn = FeedUTF32(_codeUTF32, chConv);
	_nChars = 0, _codeUTF32 = 0;
	return rtn;
}

template<Endian endian>
Codec::Result Codec_UTF32<endian>::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8& dataConv)
{
	if (GetAddcrFlag() && codeUTF32 == '\n') {
		if constexpr (endian == Endian::Little) {
			StoreData('\0');	// 7th
			StoreData('\0');	// 6th
			StoreData('\0');	// 5th
			StoreData('\n');	// 4th
			StoreData('\0');	// 3rd
			StoreData('\0');	// 2nd
			StoreData('\0');	// 1st
			dataConv = '\r';	// 0th
		} else {
			StoreData('\n');	// 7th
			StoreData('\0');	// 6th
			StoreData('\0');	// 5th
			StoreData('\0');	// 4th
			StoreData('\r');	// 3rd
			StoreData('\0');	// 2nd
			StoreData('\0');	// 1st
			dataConv = '\0';	// 0th
		}
	} else {
		if constexpr (endian == Endian::Little) {
			StoreData(static_cast<UInt8>(codeUTF32 >> 24));	// 3rd
			StoreData(static_cast<UInt8>(codeUTF32 >> 16));	// 2nd
			StoreData(static_cast<UInt8>(codeUTF32 >> 8));	// 1st
			dataConv = static_cast<UInt8>(codeUTF32 >> 0);	// 0th
		} else {
			StoreData(static_cast<UInt8>(codeUTF32 >> 0));	// 3rd
			StoreData(static_cast<UInt8>(codeUTF32 >> 8));	// 2nd
			StoreData(static_cast<UInt8>(codeUTF32 >> 16));	// 1st
			dataConv = static_cast<UInt8>(codeUTF32 >> 24);	// 0th
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
