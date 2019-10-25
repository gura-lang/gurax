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
		virtual Result FeedChar(char ch, char& chConv);
	};
	class Encoder : public Codec_UTF::Encoder {
	private:
		Mode _mode;
	public:
		Encoder(bool addcrFlag) :
			Codec_UTF::Encoder(addcrFlag), _mode(Mode::ASCII) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, char& chConv);
	};
};

Codec::Result Codec_JIS::Decoder::FeedChar(char ch, char& chConv)
{
	if (_stat == Stat::Start) {
		if (ch == 0x1b) {
			_codeJIS = 0x0000;
			_stat = Stat::Escape;
			return Result::None;
		}
	} else if (_stat == Stat::Escape) {
		if (ch == '$') {
			_stat = Stat::Dollar;
		} else if (ch == '&') {
			_stat = Stat::Ampersand;
		} else if (ch == '(') {
			_stat = Stat::LParenthesis;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Dollar) {
		if (ch == '@') {
			_mode = Mode::JISC;
			_stat = Stat::Start;
		} else if (ch == 'B') {
			_mode = Mode::JISX1983;
			_stat = Stat::Start;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Ampersand) {
		if (ch == '@') {
			_stat = Stat::JISX1990;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::LParenthesis) {
		if (ch == 'B') {
			_mode = Mode::ASCII;
			_stat = Stat::Start;
		} else if (ch == 'J') {
			_mode = Mode::JISROMA;
			_stat = Stat::Start;
		} else if (ch == 'I') {
			_mode = Mode::JISKANA;
			_stat = Stat::Start;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::JISX1990) {
		if (ch == 0x1b) {
			_stat = Stat::Escape2nd;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Escape2nd) {
		if (ch == '$') {
			_stat = Stat::Dollar2nd;
		} else {
			return Result::Error;
		}
		return Result::None;
	} else if (_stat == Stat::Dollar2nd) {
		if (ch == 'B') {
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
			_codeJIS = ch;
			return Result::None;
		}
		_codeJIS = (_codeJIS << 8) | ch;
		codeCP932 = JISToCP932(_codeJIS);
	} else if (_mode == Mode::ASCII) {
		codeCP932 = ch;
	} else if (_mode == Mode::JISROMA) {
		codeCP932 = ch;	// incorrect process
	} else if (_mode == Mode::JISKANA) {
		if (0x20 < ch && ch < 0x60) {
			codeCP932 = static_cast<UChar>(ch) + 0x80;
		} else {
			return Result::Error;
		}
	}
	if (GetDelcrFlag() && codeCP932 == '\r') return Result::None;
	UInt32 codeUTF32 = CP932ToUTF16(codeCP932);
	_codeJIS = 0x0000;
	return FeedUTF32(codeUTF32, chConv);
}

Codec::Result Codec_JIS::Encoder::FeedUTF32(UInt32 codeUTF32, char& chConv)
{
	UInt16 codeCP932 = UTF16ToCP932(static_cast<UInt16>(codeUTF32));
	if (codeCP932 < 0x80) {
		char ch = static_cast<char>(codeCP932 & 0xff);
		if (_mode == Mode::ASCII) {
			if (GetAddcrFlag() && ch == '\n') {
				StoreChar('\n');
				chConv = '\r';
			} else {
				chConv = ch;
			}
		} else {
			if (GetAddcrFlag() && ch == '\n') {
				StoreChar('\n');
				StoreChar('\r');
			} else {
				StoreChar(ch);
			}
			StoreChar('B');
			StoreChar('(');
			chConv = 0x1b;
			_mode = Mode::ASCII;
		}
	} else if (0xa0 < codeCP932 && codeCP932 < 0xe0) {
		if (_mode != Mode::JISKANA) {
			StoreChar('I');
			StoreChar('(');
			chConv = 0x1b;
			_mode = Mode::JISKANA;
		}
		chConv = static_cast<UChar>(codeCP932 - 0x80);
	} else if (codeCP932 < 0x100) {
		return Result::Error;
	} else {
		UInt16 codeJIS = CP932ToJIS(codeCP932);
		if (codeJIS == 0x0000) {
			chConv = '\0';
			return Result::Error;
		}
		if (_mode == Mode::JISC) {
			StoreChar(static_cast<char>(codeJIS & 0xff));
			chConv = static_cast<char>(codeJIS >> 8);
		} else {
			StoreChar(static_cast<char>(codeJIS & 0xff));
			StoreChar(static_cast<char>(codeJIS >> 8));
			StoreChar('@');
			StoreChar('$');
			chConv = 0x1b;
			_mode = Mode::JISC;
		}
	}
	return Result::Complete;
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	// Registration of CodecFactory
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("cp932"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("shift_jis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_CP932>("ms_kanji"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_EUCJP>("euc-jp"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_JIS>("jis"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_JIS>("iso-2022-jp"));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_japanese)
