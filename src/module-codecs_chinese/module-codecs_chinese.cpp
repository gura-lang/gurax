//==============================================================================
// module-codecs_chinese.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs_chinese)

//-----------------------------------------------------------------------------
// Codec_CP936
//-----------------------------------------------------------------------------
class Codec_CP936 : public Codec_DBCS {
public:
	class Decoder : public Codec_DBCS::Decoder {
	public:
		Decoder(bool delcrFlag) : Codec_DBCS::Decoder(delcrFlag) {}
		virtual bool IsLeadByte(UChar ch) { return ch > 0x80; }
		virtual UInt16 DBCSToUTF16(UInt16 codeDBCS) {
			return CP936ToUTF16(codeDBCS);
		}
	};
	class Encoder : public Codec_DBCS::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_DBCS::Encoder(addcrFlag) {}
		virtual UInt16 UTF16ToDBCS(UInt16 codeUTF16) {
			return UTF16ToCP936(codeUTF16);
		}
	};
};

//-----------------------------------------------------------------------------
// Codec_CP950
//-----------------------------------------------------------------------------
class Codec_CP950 : public Codec_DBCS {
public:
	class Decoder : public Codec_DBCS::Decoder {
	public:
		Decoder(bool delcrFlag) : Codec_DBCS::Decoder(delcrFlag) {}
		virtual UInt16 DBCSToUTF16(UInt16 codeDBCS) {
			return CP950ToUTF16(codeDBCS);
		}
	};
	class Encoder : public Codec_DBCS::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_DBCS::Encoder(addcrFlag) {}
		virtual UInt16 UTF16ToDBCS(UInt16 codeUTF16) {
			return UTF16ToCP950(codeUTF16);
		}
	};
};

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
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP936>("cp936"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP936>("gb2312"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP936>("gbk"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP950>("cp950"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP950>("big5"));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_chinese)
