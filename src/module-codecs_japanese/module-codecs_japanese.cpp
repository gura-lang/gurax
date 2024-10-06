//==============================================================================
// module-codecs_japanese.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs_japanese)

//-----------------------------------------------------------------------------
// Codec_CP932
//-----------------------------------------------------------------------------
class Codec_CP932 : public Codec_DBCS {
public:
	class Decoder : public Codec_DBCS::Decoder {
	public:
		Decoder(bool delcrFlag) : Codec_DBCS::Decoder(delcrFlag) {}
		virtual bool IsLeadByte(UChar ch) { return String::IsSJISFirst(ch); }
		virtual UInt16 DBCSToUTF16(UInt16 codeDBCS) { return CP932ToUTF16(codeDBCS); }
	};
	class Encoder : public Codec_DBCS::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_DBCS::Encoder(addcrFlag) {}
		virtual UInt16 UTF16ToDBCS(UInt16 codeUTF16) { return UTF16ToCP932(codeUTF16); }
	};
};

//-----------------------------------------------------------------------------
// Codec_EUCJP
//-----------------------------------------------------------------------------
class Codec_EUCJP : public Codec_DBCS {
public:
	class Decoder : public Codec_DBCS::Decoder {
	public:
		Decoder(bool delcrFlag) : Codec_DBCS::Decoder(delcrFlag) {}
		virtual UInt16 DBCSToUTF16(UInt16 codeDBCS) {
			UInt16 codeCP932 = EUCJPToCP932(codeDBCS);
			return CP932ToUTF16(codeCP932);
		}
	};
	class Encoder : public Codec_DBCS::Encoder {
	public:
		Encoder(bool addcrFlag) : Codec_DBCS::Encoder(addcrFlag) {}
		virtual UInt16 UTF16ToDBCS(UInt16 codeUTF16) {
			UInt16 codeCP932 = UTF16ToCP932(codeUTF16);
			return CP932ToEUCJP(codeCP932);
		}
	};
};

//-----------------------------------------------------------------------------
// Codec_JIS
//-----------------------------------------------------------------------------
class Codec_JIS : public Codec_UTF {
public:
	enum class Mode {
		JISC,
		JISX1983,
		JISX1990,
		ASCII,
		JISROMA,
		JISKANA,
	};
	class Decoder : public Codec_UTF::Decoder {
	public:
		enum class Stat {
			Start,
			Escape,
			Dollar, Ampersand, LParenthesis,
			JISX1990,
			Escape2nd, Dollar2nd,
		};
	private:
		Mode _mode;
		Stat _stat;
		UInt16 _codeJIS;
	public:
		Decoder(bool delcrFlag) :
			Codec_UTF::Decoder(delcrFlag),
			_mode(Mode::ASCII), _stat(Stat::Start), _codeJIS(0x0000) {}
		virtual Result FeedData(UInt8 data, UInt32* pCodeUTF32);
	};
	class Encoder : public Codec_UTF::Encoder {
	private:
		Mode _mode;
	public:
		Encoder(bool addcrFlag) :
			Codec_UTF::Encoder(addcrFlag), _mode(Mode::ASCII) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt);
	};
};

Codec::Result Codec_JIS::Decoder::FeedData(UInt8 data, UInt32* pCodeUTF32)
{
	if (_stat == Stat::Start) {
		if (data == 0x1b) {
			_codeJIS = 0x0000;
			_stat = Stat::Escape;
			return Result::None;
		}
	} else if (_stat == Stat::Escape) {
		if (data == '$') {
			_stat = Stat::Dollar;
		} else if (data == '&') {
			_stat = Stat::Ampersand;
		} else if (data == '(') {
			_stat = Stat::LParenthesis;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Dollar) {
		if (data == '@') {
			_mode = Mode::JISC;
			_stat = Stat::Start;
		} else if (data == 'B') {
			_mode = Mode::JISX1983;
			_stat = Stat::Start;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Ampersand) {
		if (data == '@') {
			_stat = Stat::JISX1990;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::LParenthesis) {
		if (data == 'B') {
			_mode = Mode::ASCII;
			_stat = Stat::Start;
		} else if (data == 'J') {
			_mode = Mode::JISROMA;
			_stat = Stat::Start;
		} else if (data == 'I') {
			_mode = Mode::JISKANA;
			_stat = Stat::Start;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::JISX1990) {
		if (data == 0x1b) {
			_stat = Stat::Escape2nd;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Escape2nd) {
		if (data == '$') {
			_stat = Stat::Dollar2nd;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Dollar2nd) {
		if (data == 'B') {
			_mode = Mode::JISX1990;
			_stat = Stat::Start;
		} else {
			return Result::Error;
		}
		return Result::None;
	}
	UInt16 codeCP932 = 0x0000;
	if (_mode == Mode::JISC || _mode == Mode::JISX1983 || _mode == Mode::JISX1990) {
		if (_codeJIS == 0x0000) {
			_codeJIS = data;
			return Result::None;
		}
		_codeJIS = (_codeJIS << 8) | data;
		codeCP932 = JISToCP932(_codeJIS);
	} else if (_mode == Mode::ASCII) {
		codeCP932 = data;
	} else if (_mode == Mode::JISROMA) {
		codeCP932 = data;	// incorrect process
	} else if (_mode == Mode::JISKANA) {
		if (0x20 < data && data < 0x60) {
			codeCP932 = static_cast<UChar>(data) + 0x80;
		} else {
			return Result::Error;
		}
	}
	if (GetDelcrFlag() && codeCP932 == '\r') return Result::None;
	*pCodeUTF32 = CP932ToUTF16(codeCP932);
	_codeJIS = 0x0000;
	return Result::Complete;
}

Codec::Result Codec_JIS::Encoder::FeedUTF32(UInt32 codeUTF32, UInt8* buffRtn, size_t* pCnt)
{
	UInt16 codeCP932 = UTF16ToCP932(static_cast<UInt16>(codeUTF32));
	if (codeCP932 < 0x80) {
		char ch = static_cast<char>(codeCP932 & 0xff);
		if (_mode == Mode::ASCII) {
			if (GetAddcrFlag() && ch == '\n') {
				buffRtn[0] = '\r';
				buffRtn[1] = '\n';
				*pCnt = 2;
			} else {
				buffRtn[0] = ch;
				*pCnt = 1;
			}
		} else {
			buffRtn[0] = 0x1b;
			buffRtn[1] = '(';
			buffRtn[2] = 'B';
			if (GetAddcrFlag() && ch == '\n') {
				buffRtn[3] = '\r';
				buffRtn[4] = '\n';
				*pCnt = 5;
			} else {
				buffRtn[3] = ch;
				*pCnt = 4;
			}
			_mode = Mode::ASCII;
		}
	} else if (0xa0 < codeCP932 && codeCP932 < 0xe0) {
		if (_mode != Mode::JISKANA) {
			buffRtn[0] = 0x1b;
			buffRtn[1] = '(';
			buffRtn[2] = 'I';
			buffRtn[3] = static_cast<UChar>(codeCP932 - 0x80);
			*pCnt = 4;
			_mode = Mode::JISKANA;
		} else {
			buffRtn[0] = static_cast<UChar>(codeCP932 - 0x80);
			*pCnt = 1;
		}
	} else if (codeCP932 < 0x100) {
		return Result::Error;
	} else {
		UInt16 codeJIS = CP932ToJIS(codeCP932);
		if (codeJIS == 0x0000) {
			buffRtn[0] = '\0';
			*pCnt = 1;
			return Result::Error;
		}
		if (_mode == Mode::JISC) {
			buffRtn[0] = static_cast<UInt8>(codeJIS >> 8);
			buffRtn[1] = static_cast<UInt8>(codeJIS & 0xff);
			*pCnt = 2;
		} else {
			buffRtn[0] = 0x1b;
			buffRtn[1] = '$';
			buffRtn[2] = '@';
			buffRtn[3] = static_cast<UInt8>(codeJIS >> 8);
			buffRtn[4] = static_cast<UInt8>(codeJIS & 0xff);
			*pCnt = 5;
			_mode = Mode::JISC;
		}
	}
	return Result::Complete;
}

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// codecs.japanese.ConvUTF32ToSJIS(code as Number):map
Gurax_DeclareFunction(ConvUTF32ToSJIS)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Convert a code of UTF32 to Shift JIS.
)""");
}

Gurax_ImplementFunction(ConvUTF32ToSJIS)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 code = args.PickNumber<UInt32>();
	// Function body
	return new Value_Number(UTF16ToCP932(code));
}

// codecs.japanese.ConvUTF32ToJIS(code as Number):map
Gurax_DeclareFunction(ConvUTF32ToJIS)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Convert a code of UTF32 to JIS.
)""");
}

Gurax_ImplementFunction(ConvUTF32ToJIS)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 code = args.PickNumber<UInt32>();
	// Function body
	return new Value_Number(CP932ToJIS(UTF16ToCP932(code)));
}

// codecs.japanese.ConvUTF32ToEUCJP(code as Number):map
Gurax_DeclareFunction(ConvUTF32ToEUCJP)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Convert a code of UTF32 to EUC-JP.
)""");
}

Gurax_ImplementFunction(ConvUTF32ToEUCJP)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 code = args.PickNumber<UInt32>();
	// Function body
	return new Value_Number(CP932ToEUCJP(UTF16ToCP932(code)));
}

// codecs.japanese.ConvSJISToUTF32(code as Number):map
Gurax_DeclareFunction(ConvSJISToUTF32)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Convert a code of Shift JIS to UTF32.
)""");
}

Gurax_ImplementFunction(ConvSJISToUTF32)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 code = args.PickNumber<UInt32>();
	// Function body
	return new Value_Number(CP932ToUTF16(code));
}


// codecs.japanese.ConvJISToUTF32(code as Number):map
Gurax_DeclareFunction(ConvJISToUTF32)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Convert a code of JIS to UTF32.
)""");
}

Gurax_ImplementFunction(ConvJISToUTF32)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 code = args.PickNumber<UInt32>();
	// Function body
	return new Value_Number(CP932ToUTF16(JISToCP932(code)));
}

// codecs.japanese.ConvEUCJPToUTF32(code as Number):map
Gurax_DeclareFunction(ConvEUCJPToUTF32)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Convert a code of EUC-JP to UTF32.
)""");
}

Gurax_ImplementFunction(ConvEUCJPToUTF32)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 code = args.PickNumber<UInt32>();
	// Function body
	return new Value_Number(CP932ToUTF16(EUCJPToCP932(code)));
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
	// Assignment of function
	Assign(Gurax_CreateFunction(ConvUTF32ToSJIS));
	Assign(Gurax_CreateFunction(ConvUTF32ToJIS));
	Assign(Gurax_CreateFunction(ConvUTF32ToEUCJP));
	Assign(Gurax_CreateFunction(ConvSJISToUTF32));
	Assign(Gurax_CreateFunction(ConvJISToUTF32));
	Assign(Gurax_CreateFunction(ConvEUCJPToUTF32));
	// Registration of CodecFactory
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("cp932"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("sjis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("shiftjis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("shift-jis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("shift_jis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("ms-kanji"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("ms_kanji"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_EUCJP>("eucjp"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_EUCJP>("euc-jp"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_EUCJP>("euc_jp"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_JIS>("jis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_JIS>("iso-2022-jp"));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_japanese)
