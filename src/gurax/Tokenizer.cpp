//==============================================================================
// Tokenizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// MagicCommentParser
//-----------------------------------------------------------------------------
MagicCommentParser::MagicCommentParser() : _stat(Stat::Start)
{
}

MagicCommentParser::~MagicCommentParser()
{
}

bool MagicCommentParser::ParseChar(char ch)
{
	bool rtn = false;
	if (_stat == Stat::Idle) {
		// nothing to do
	} else if (_stat == Stat::Start) {
		if (String::IsAlpha(ch)) {
			_field += ch;
		} else if (ch == ':' || ch == '=') {
			if (_field.size() >= 6 && ::strcmp(_field.c_str() + _field.size() - 6, "coding") == 0) {
				_stat = Stat::SkipSpace;
			} else {
				_field.clear();
			}
		} else {
			_field.clear();
		}
	} else if (_stat == Stat::SkipSpace) {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.' || ch == '-' || ch == '_') {
			_field.clear();
			_field += ch;
			_stat = Stat::CodingName;
		} else {
			_stat = Stat::Start;
		}
	} else if (_stat == Stat::CodingName) {
		if (String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.' || ch == '-' || ch == '_') {
			_field += ch;
		} else {
			rtn = true;
			_stat = Stat::Idle;
		}
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
Tokenizer::Tokenizer(const String &sourceName, int cntLineStart, bool enablePreparatorFlag)
	//_stat(Stat::BOF), _lineHeadFlag(true),
	//_appearShebangFlag(false), _blockParamFlag(false),
	//_cntLine(cntLineStart), _cntCol(0), _commentNestLevel(0),
	//_pSourceName(new StringShared(sourceName)),
	//_pExprOwner(nullptr), _pExprParent(nullptr),
	//_pTokenInfoPrev(&TOKEN_Unknown),
	//_lineNoTop(0), _lineNoOfTokenPrev(0),
	//_enablePreparatorFlag(enablePreparatorFlag), _interactiveFlag(false)
	//_pTokenWatcher(nullptr)
{
}

bool Tokenizer::ParseChar(char ch)
{
#if 0
	if (ch == '\r') return true;
	if (_lineHeadFlag) {
		if (IsWhite(ch)) {
			_strIndent.push_back(ch);
		} else {
			_lineHeadFlag = false;
		}
	}
	Gurax_BeginPushbackRegionEx(char, 8, ch);
	switch (_stat) {
	case Stat::BOF: {
		if (ch == '\xef') {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::BOF_2nd;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::BOF_2nd: {
		if (ch == '\xbb') {
			_field.push_back(ch);
			_stat = Stat::BOF_3rd;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Symbol;
		}
		break;
	}
	case Stat::BOF_3rd: {
		if (ch == '\xbf') {
			_stat = Stat::Start;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Symbol;
		}
		break;
	}
	case Stat::Start: {
		if (ch == '0') {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::NumberPre;
		} else if (IsDigit(ch)) {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::Number;
		} else if (ch == '.') {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::NumberAfterPeriod;
		} else if (IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
				_stat = Stat::White;
			}
		} else if (IsSymbolFirstChar(ch)) {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::Symbol;
		} else if (ch == '"' || ch == '\'') {
			_stringInfo.chBorder = ch;
			_stringInfo.rawFlag = false;
			_stringInfo.binaryFlag = false;
			_stringInfo.wiseFlag = false;
			_stringInfo.embedFlag = false;
			_field.clear();
			if (IsTokenWatched()) {
				_strSource.clear();
				_strSource.push_back(ch);
			}
			_stat = Stat::StringFirst;
		} else if (ch == '\\') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
			}
			_stat = Stat::Escape;
		} else if (ch == '\n') {
			FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '#') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
			}
			if (sig.IsSignalled()) {
				_stat = Stat::Error;
			} else if (_cntLine == 0) {
				_stat = Stat::CommentLineTop;
			} else if (_cntLine == 1 && _appearShebangFlag) {
				_stat = Stat::MagicCommentLine;
			} else {
				_stat = Stat::CommentLine;
			}
		} else if (ch == '{') {
			FeedToken(env, Token(TOKEN_LBrace, GetLineNo()));
			if (IsTokenWatched()) {
				_field.clear();
				_lineNoTop = GetLineNo();
			}
			_stat = sig.IsSignalled()? Stat::Error : Stat::AfterLBrace;
		} else if (ch == '(') {
			FeedToken(env, Token(TOKEN_LParenthesis, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '[') {
			FeedToken(env, Token(TOKEN_LBracket, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '|' && _blockParamFlag && _tokenStack.CheckBlockParamEnd()) {
			_blockParamFlag = false;
			FeedToken(env, Token(TOKEN_RBlockParam, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '`') {
			FeedToken(env, Token(TOKEN_Quote, GetLineNo()));
			_stat = Stat::Start;
		} else if (ch == ':') {
			_stat = Stat::Colon;
		} else {
			size_t i = 0;
			static const struct {
				int ch;
				const TokenInfo *pTokenInfo;
			} tbl[] = {
				{ '?',	&TOKEN_Question,	},
				{ '+',	&TOKEN_DoubleChars,	},
				{ '-',	&TOKEN_DoubleChars,	},
				{ '*',	&TOKEN_DoubleChars,	},
				{ '/',	&TOKEN_DoubleChars,	},
				{ '%',	&TOKEN_DoubleChars,	},
				{ '=',	&TOKEN_DoubleChars,	},
				{ '<',	&TOKEN_DoubleChars,	},
				{ '>',	&TOKEN_DoubleChars,	},
				{ '!',	&TOKEN_DoubleChars,	}, // see also Stat::Symbol
				{ '|',	&TOKEN_DoubleChars,	},
				{ '&',	&TOKEN_DoubleChars,	},
				{ '^',	&TOKEN_DoubleChars,	},
				{ '~',	&TOKEN_Inv,			},
				{ ',',	&TOKEN_Comma,		},
				{ ';',	&TOKEN_Semicolon,	},
				{ ')',	&TOKEN_RParenthesis,},
				{ '}',	&TOKEN_RBrace,		},
				{ ']',	&TOKEN_RBracket,	},
				{ '\0',	&TOKEN_EOF,			},
			};
			for (i = 0; i < ArraySizeOf(tbl); i++) {
				if (tbl[i].ch == ch) break;
			}
			if (i >= ArraySizeOf(tbl)) {
				SetError(ERR_SyntaxError, "unexpected character '%c' (%d)", ch, ch);
				_stat = Stat::Error;
			} else if (tbl[i].pTokenInfo->IsIdentical(TOKEN_DoubleChars)) {
				_field.clear();
				_field.push_back(ch);
				_stat = Stat::DoubleChars;
			} else if (_tokenStack.back().IsType(TOKEN_Quote)) {
				_field.clear();
				_field.push_back(ch);
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
				if (sig.IsSignalled()) _stat = Stat::Error;
			} else {
				FeedToken(env, Token(*tbl[i].pTokenInfo, GetLineNo()));
				if (sig.IsSignalled()) _stat = Stat::Error;
			}
		}
		break;
	}
	case Stat::White: {
		if (IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			_field.push_back(ch);
		} else {
			_pTokenWatcher->FeedToken(env, Token(TOKEN_Space, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::DoubleChars: {
		// this state comes from Stat::Start and Stat::Symbol
		static const struct {
			int chFirst;
			const TokenInfo *pTokenInfo;
			struct {
				int chSecond;
				const TokenInfo *pTokenInfo;
			} tblCand[10];
		} tbl[] = {
			{ '+', &TOKEN_Add, {
				{ '=', &TOKEN_AssignAdd		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '-', &TOKEN_Sub, {
				{ '=', &TOKEN_AssignSub		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '*', &TOKEN_Mul, {
				{ '=', &TOKEN_AssignMul		},
				{ '*', &TOKEN_TripleChars	},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '/', &TOKEN_Div, {
				{ '=', &TOKEN_AssignDiv		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '%', &TOKEN_Mod, {
				{ '=', &TOKEN_AssignMod		},
				{ '%', &TOKEN_ModMod		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '=', &TOKEN_Assign, {
				{ '=', &TOKEN_Eq 			},
				{ '>', &TOKEN_Pair			},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '<', &TOKEN_Lt, {
				{ '=', &TOKEN_TripleChars	},
				{ '<', &TOKEN_TripleChars	},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '>', &TOKEN_Gt, {
				{ '=', &TOKEN_Ge			},
				{ '>', &TOKEN_TripleChars	},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '!', &TOKEN_Not, {
				{ '=', &TOKEN_Ne			},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '|', &TOKEN_Or, {
				{ '=', &TOKEN_AssignOr 		},
				{ '|', &TOKEN_TripleChars	},
				{ '.', &TOKEN_TripleChars	},
				{ '^', &TOKEN_TripleChars	},
				{ '*', &TOKEN_TripleChars	},
				{ '+', &TOKEN_TripleChars	},
				{ '-', &TOKEN_TripleChars	},
				{ '&', &TOKEN_TripleChars	},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '&', &TOKEN_And, {
				{ '=', &TOKEN_AssignAnd		},
				{ '&', &TOKEN_AndAnd		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ '^', &TOKEN_Xor, {
				{ '=', &TOKEN_AssignXor		},
				{ '\0', &TOKEN_Unknown		}, } },
		};
		int chFirst = _field[0];
		if (chFirst == '/' && ch == '*') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(chFirst);
				_field.push_back(ch);
				_lineNoTop = GetLineNo();
			}
			_commentNestLevel = 1;
			_stat = Stat::CommentBlock;
		} else if (chFirst == '/' && ch == '/') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(chFirst);
				_field.push_back(ch);
			}
			if (_cntLine == 0 || (_cntLine == 1 && _appearShebangFlag)) {
				_stat = Stat::MagicCommentLine;
			} else {
				_stat = Stat::CommentLine;
			}
		} else if (chFirst == '*' && ch == '/') {
			SetError(ERR_SyntaxError, "unmatching comment description");
			_stat = Stat::Error;
		} else {
			_stat = Stat::Start;
			for (size_t i = 0; i < ArraySizeOf(tbl); i++) {
				if (tbl[i].chFirst != chFirst) continue;
				const TokenInfo *pTokenInfo = tbl[i].pTokenInfo;
				bool pushbackFlag = true;
				for (size_t j = 0; j < ArraySizeOf(tbl[i].tblCand); j++) {
					if (tbl[i].tblCand[j].chSecond == '\0') break;
					if (tbl[i].tblCand[j].chSecond == ch) {
						_field.push_back(ch);
						pTokenInfo = tbl[i].tblCand[j].pTokenInfo;
						pushbackFlag = false;
						break;
					}
				}
				if (pTokenInfo->IsIdentical(TOKEN_TripleChars)) {
					_stat = Stat::TripleChars;
				} else if (_tokenStack.back().IsType(TOKEN_Quote)) {
					FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
					if (sig.IsSignalled()) _stat = Stat::Error;
				} else {
					FeedToken(env, Token(*pTokenInfo, GetLineNo()));
					if (sig.IsSignalled()) _stat = Stat::Error;
				}
				if (pushbackFlag) Gurax_PushbackEx(ch);
				break;
			}
			// tables have a bug if i reaches at ArraySizeOf(tbl)
		}
		break;
	}
	case Stat::TripleChars: {
		static const struct {
			const char *strFirst;
			const TokenInfo *pTokenInfo;
			bool pushbackSecondFlag;
			struct {
				int chThird;
				const TokenInfo *pTokenInfo;
			} tblCand[5];
		} tbl[] = {
			{ "**", &TOKEN_Pow, false, {
				{ '=', &TOKEN_AssignPow		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "<=", &TOKEN_Le, false, {
				{ '>', &TOKEN_Cmp			},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "<<", &TOKEN_Shl, false, {
				{ '=', &TOKEN_AssignShl		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ ">>", &TOKEN_Shr, false, {
				{ '=', &TOKEN_AssignShr		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "|.", &TOKEN_Or, true, {
				{ '|', &TOKEN_Dot			},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "|^", &TOKEN_Or, true, {
				{ '|', &TOKEN_Cross			},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "|*", &TOKEN_Or, true, {
				{ '|', &TOKEN_Gear			},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "|+", &TOKEN_Or, true, {
				{ '|', &TOKEN_Concat		},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "|-", &TOKEN_Or, true, {
				{ '|', &TOKEN_Difference	},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "|&", &TOKEN_Or, true, {
				{ '|', &TOKEN_Intersection	},
				{ '\0', &TOKEN_Unknown		}, } },
			{ "||", &TOKEN_OrOr, false, {
				{ '|', &TOKEN_Union			},
				{ '\0', &TOKEN_Unknown		}, } },
		};
		_stat = Stat::Start;
		for (size_t i = 0; i < ArraySizeOf(tbl); i++) {
			if (_field.compare(tbl[i].strFirst) != 0) continue;
			const TokenInfo *pTokenInfo = tbl[i].pTokenInfo;
			bool pushbackFlag = true;
			bool pushbackSecondFlag = tbl[i].pushbackSecondFlag;
			for (size_t j = 0; j < ArraySizeOf(tbl[i].tblCand); j++) {
				if (tbl[i].tblCand[j].chThird == '\0') break;
				if (tbl[i].tblCand[j].chThird == ch) {
					_field.push_back(ch);
					pTokenInfo = tbl[i].tblCand[j].pTokenInfo;
					pushbackFlag = false;
					pushbackSecondFlag = false;
					break;
				}
			}
			if (_tokenStack.back().IsType(TOKEN_Quote)) {
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
				if (sig.IsSignalled()) _stat = Stat::Error;
			} else {
				FeedToken(env, Token(*pTokenInfo, GetLineNo()));
				if (sig.IsSignalled()) _stat = Stat::Error;
			}
			if (pushbackFlag) Gurax_PushbackEx(ch);
			if (pushbackSecondFlag) Gurax_PushbackEx(_field[1]);
			break;
		}
		// tables have a bug if i reaches at ArraySizeOf(tbl)
		break;
	}
	case Stat::Escape: {
		if (ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Escape, GetLineNo(), _field));
			}
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		} else if (ch == '\n') {
			if (IsTokenWatched()) {
				_field.push_back(ch);
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Escape, GetLineNo(), _field));
			}
			_stat = Stat::Start;
		} else if (IsWhite(ch)) {
			if (IsTokenWatched()) {
				_field.push_back(ch);
			}
		} else {
			SetError(ERR_SyntaxError, "invalid escape character");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::Colon: {
		if (ch == ':') {
			FeedToken(env, Token(TOKEN_ColonColon, GetLineNo()));
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else if (ch == '*') {
			FeedToken(env, Token(TOKEN_ColonAsterisk, GetLineNo()));
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else if (ch == '&') {
			FeedToken(env, Token(TOKEN_ColonAnd, GetLineNo()));
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else {
			const TokenInfo *pTokenInfo = _tokenStack.back().IsSuffixToken()?
									&TOKEN_ColonAfterSuffix : &TOKEN_Colon;
			FeedToken(env, Token(*pTokenInfo, GetLineNo()));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Error: {
		InitStack();
		_blockParamFlag = false;
		Gurax_PushbackEx(ch);
		_stat = Stat::ErrorRecovery;
		break;
	}
	case Stat::ErrorRecovery: {
		if (ch == '\n' || ch == '\0') {
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		} else {
			// nothing to do
		}
		break;
	}
	case Stat::AfterLBrace: {
		if (ch == '|') {
			if (IsTokenWatched() && !_field.empty()) {
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Space, _lineNoTop, _field));
			}
			FeedToken(env, Token(TOKEN_LBlockParam, GetLineNo()));
			if (sig.IsSignalled()) {
				_stat = Stat::Error;
			} else {
				_blockParamFlag = true;
				_stat = Stat::Start;
			}
		} else if (ch == '\n' || IsWhite(ch)) {
			if (IsTokenWatched()) _field.push_back(ch);
		} else {
			if (IsTokenWatched() && !_field.empty()) {
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Space, _lineNoTop, _field));
			}
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::NumberPre: {
		if (ch == 'x' || ch == 'X') {
			_field.push_back(ch);
			_stat = Stat::NumberHex;
		} else if (ch == 'b' || ch == 'B') {
			_field.push_back(ch);
			_stat = Stat::NumberBin;
		} else if(IsOctDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::NumberOct;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Number;
		}
		break;
	}
	case Stat::NumberHex: {
		if (IsHexDigit(ch)) {
			_field.push_back(ch);
		} else if (_field.size() <= 2) {
			SetError(ERR_SyntaxError, "wrong format of hexadecimal number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberOct: {
		if (IsOctDigit(ch)) {
			_field.push_back(ch);
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberBin: {
		if (IsBinDigit(ch)) {
			_field.push_back(ch);
		} else if (_field.size() <= 2) {
			SetError(ERR_SyntaxError, "wrong format of binary number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberAfterPeriod: {
		if (ch == '.') {
			if (_tokenStack.back().IsType(TOKEN_Quote)) {
				_field.push_back(ch);
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
			} else {
				FeedToken(env, Token(TOKEN_Seq, GetLineNo()));
			}
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else if (IsDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::Number;
		} else {
			FeedToken(env, Token(TOKEN_Period, GetLineNo()));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Number: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
		} else if (ch == '.') {
			size_t pos = _field.find('.');
			if (pos == _field.length() - 1) {
				_field.resize(pos);
				FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
				if (!sig.IsSignalled()) {
					FeedToken(env, Token(TOKEN_Seq, GetLineNo()));
				}
				_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
			} else if (pos == String::npos) {
				_field.push_back(ch);
			} else {
				SetError(ERR_SyntaxError, "period has already been scanned");
				_stat = Stat::Error;
			}
		} else if (ch == 'e' || ch == 'E') {
			_field.push_back(ch);
			_stat = Stat::NumberExpAfterE;
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberExpAfterE: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::NumberExp;
		} else if (ch == '+' || ch == '-') {
			_field.push_back(ch);
			_stat = Stat::NumberExpAfterSign;
		} else {
			SetError(ERR_SyntaxError, "wrong exponential expression");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberExpAfterSign: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::NumberExp;
		} else {
			SetError(ERR_SyntaxError, "wrong exponential expression");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberExp: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberSuffixed: {
		if (IsSymbolChar(ch)) {
			_suffix.push_back(ch);
		} else {
			if (IsTokenWatched()) {
				FeedToken(env, Token(TOKEN_NumberSuffixed, GetLineNo(),
									 _field, _suffix, _field + _suffix));
			} else {
				FeedToken(env, Token(TOKEN_NumberSuffixed, GetLineNo(), _field, _suffix));
			}
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Symbol: {
		if (IsSymbolChar(ch)) {
			_field.push_back(ch);
		} else if (ch == '!') {
			_stat = Stat::SymbolExclamation;
		} else if ((ch == '"' || ch == '\'') && CheckStringPrefix(_stringInfo, _field)) {
			_stringInfo.chBorder = ch;
			if (IsTokenWatched()) {
				_strSource.clear();
				_strSource += _field;
				_strSource.push_back(ch);
			}
			_field.clear();
			_stat = Stat::StringFirst;
		} else {
			if (_field == "in" && !_tokenStack.back().IsType(TOKEN_Quote)) {
				FeedToken(env, Token(TOKEN_Contains, GetLineNo()));
			} else {
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
			}
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::SymbolExclamation: {
		if (ch == '=' || ch == '!') {
			FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
			if (sig.IsSignalled()) {
				_stat = Stat::Error;
			} else {
				_field.clear();
				_field.push_back('!');
				Gurax_PushbackEx(ch);
				_stat = Stat::DoubleChars;
			}
		} else {
			_field.push_back('!');
			Gurax_PushbackEx(ch);
			_stat = Stat::Symbol;
		}
		break;
	}
	case Stat::CommentLineTop: {
		if (ch == '!') {
			if (IsTokenWatched()) _field.push_back(ch);
			_appearShebangFlag = true;
			_stat = Stat::ShebangLine;
		} else {
			_stat = Stat::MagicCommentLine;
			Gurax_PushbackEx(ch);
		}
		break;
	}
	case Stat::MagicCommentLine: {
		if (_magicCommentParser.ParseChar(ch)) {
			const char *encoding = _magicCommentParser.GetEncoding();
			sig.SetSignal(SIGTYPE_DetectEncoding, Value(encoding));
		}
		if (ch == '\n' || ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(
					env, Token(TOKEN_CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			_stat = Stat::Start;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case Stat::ShebangLine: {
		if (ch == '\n' || ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(
					env, Token(TOKEN_CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			_stat = Stat::Start;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case Stat::CommentLine: {
		if (ch == '\n' || ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(
					env, Token(TOKEN_CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			_stat = Stat::Start;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case Stat::CommentBlock: {
		if (ch == '*') {
			if (IsTokenWatched()) _field.push_back(ch);
			_stat = Stat::CommentBlockEnd;
		} else if (ch == '/') {
			if (IsTokenWatched()) _field.push_back(ch);
			_stat = Stat::CommentBlockNest;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case Stat::CommentBlockEnd: {
		if (ch == '/') {
			if (IsTokenWatched()) _field.push_back(ch);
			_commentNestLevel--;
			if (_commentNestLevel > 0) {
				_stat = Stat::CommentBlock;
			} else {
				if (IsTokenWatched()) {
					_pTokenWatcher->FeedToken(
						env, Token(TOKEN_CommentBlock, _lineNoTop, _field));
				}
				_stat = Stat::Start;
			}
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::CommentBlock;
		}
		break;
	}
	case Stat::CommentBlockNest: {
		if (ch == '*') {
			if (IsTokenWatched()) _field.push_back(ch);
			_commentNestLevel++;
			_stat = Stat::CommentBlock;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::CommentBlock;
		}
		break;
	}
	case Stat::StringFirst: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::StringSecond;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::String;
		}
		break;
	}
	case Stat::StringSecond: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			if (_stringInfo.wiseFlag) {
				_stringInfo.strIndentRef = _strIndent;
				_stat = Stat::MStringWise;
			} else {
				_stat = Stat::MString;
			}
		} else if (IsSymbolFirstChar(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::StringSuffixed;
		} else {
			const TokenInfo *pTokenInfo = GetTokenInfoForString(_stringInfo);
			FeedToken(env, Token(*pTokenInfo, GetLineNo(), _field, "", _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::String: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::StringPost;
		} else if (ch == '\\') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.statRtn = Stat::String;
			_stat = Stat::StringEsc;
		} else if (ch == '\0' || ch == '\n') {
			SetError(ERR_SyntaxError, "string is not terminated correctly");
			_stat = Stat::Error;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_field.push_back(ch);
		}
		break;
	}
	case Stat::MStringWise: {
		if (ch == '\n') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::MStringLineHead;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::MString: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::MStringEndFirst;
		} else if (ch == '\\') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.statRtn = Stat::MString;
			_stat = Stat::StringEsc;
		} else if (ch == '\0') {
			SetError(ERR_SyntaxError, "string is not terminated correctly");
			_stat = Stat::Error;
		} else if (ch == '\n' && _stringInfo.wiseFlag) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_field.push_back(ch);
			_stat = Stat::MStringLineHead;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_field.push_back(ch);
		}
		break;
	}
	case Stat::MStringLineHead: {
		if (IsWhite(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			if (_strIndent.size() == _stringInfo.strIndentRef.size()) {
				if (_strIndent != _stringInfo.strIndentRef) {
					_field += _strIndent;
				}
				_stat = Stat::MString;
			}
		} else {
			_field += _strIndent;
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::StringEsc: {
		if (_stringInfo.rawFlag) {
			if (IsTokenWatched()) {
				_strSource.push_back(ch);
			}
			_field.push_back('\\');
			_field.push_back(ch);
			_stat = _stringInfo.statRtn;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
			if (ch == '\n') {
				_stat = _stringInfo.statRtn;
			} else if (ch == 'x') {
				_stringInfo.accum = 0x00;
				_stringInfo.cntRest = 2;
				_stat = Stat::StringEscHex;
			} else if (IsOctDigit(ch)) {
				_stringInfo.accum = ConvOctDigit(ch);
				_stringInfo.cntRest = 2;
				_stat = Stat::StringEscOct;
			} else if (ch == 'u') {
				_stringInfo.accum = 0x0000;
				_stringInfo.cntRest = 4;
				_stat = Stat::StringEscUnicode;
			} else if (ch == 'U') {
				_stringInfo.accum = 0x00000000;
				_stringInfo.cntRest = 8;
				_stat = Stat::StringEscUnicode;
			} else {
				_field.push_back(GetEscaped(ch));
				_stat = _stringInfo.statRtn;
			}
		}
		break;
	}
	case Stat::StringEscHex: {
		if (IsHexDigit(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.accum = (_stringInfo.accum << 4) + ConvHexDigit(ch);
			_stringInfo.cntRest--;
			if (_stringInfo.cntRest <= 0) {
				_field.push_back(static_cast<char>(_stringInfo.accum));
				_stat = _stringInfo.statRtn;
			}
		} else {
			SetError(ERR_SyntaxError, "invalid hex expression in string");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::StringEscOct: {
		if (IsOctDigit(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.accum = (_stringInfo.accum << 3) + ConvOctDigit(ch);
			_stringInfo.cntRest--;
			if (_stringInfo.cntRest <= 0) {
				_field.push_back(static_cast<char>(_stringInfo.accum));
				_stat = _stringInfo.statRtn;
			}
		} else {
			SetError(ERR_SyntaxError, "invalid oct expression in string");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::StringEscUnicode: {
		if (IsHexDigit(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.accum = (_stringInfo.accum << 4) + ConvHexDigit(ch);
			_stringInfo.cntRest--;
			if (_stringInfo.cntRest <= 0) {
				AppendUTF32(_field, _stringInfo.accum);
				_stat = _stringInfo.statRtn;
			}
		} else {
			SetError(ERR_SyntaxError, "invalid Unicode code point in string");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::StringInCommentBlock: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::CommentBlock;
		} else if (ch == '\\') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::StringEscInCommentBlock;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
		}
		break;
	}
	case Stat::StringEscInCommentBlock: {
		if (IsTokenWatched()) _strSource.push_back(ch);
		_stat = Stat::StringInCommentBlock;
		break;
	}
	case Stat::MStringEndFirst: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::MStringEndSecond;
		} else {
			if (IsTokenWatched()) _strSource.push_back(_stringInfo.chBorder);
			_field.push_back(_stringInfo.chBorder);
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::MStringEndSecond: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = Stat::StringPost;
		} else {
			if (IsTokenWatched()) {
				_strSource.push_back(_stringInfo.chBorder);
				_strSource.push_back(_stringInfo.chBorder);
			}
			_field.push_back(_stringInfo.chBorder);
			_field.push_back(_stringInfo.chBorder);
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::StringPost: {
		if (IsSymbolFirstChar(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::StringSuffixed;
		} else {
			const TokenInfo *pTokenInfo = GetTokenInfoForString(_stringInfo);
			FeedToken(env, Token(*pTokenInfo, GetLineNo(), _field, "", _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::StringSuffixed: {
		if (IsSymbolChar(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.push_back(ch);
		} else {
			FeedToken(env, Token(TOKEN_StringSuffixed, GetLineNo(), _field, _suffix, _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::RecoverConsole: {
		if (ch == '\n') {
			_stat = Stat::BOF;
			_lineHeadFlag = true;
			InitStack();
		}
		break;
	}
	}
	Gurax_EndPushbackRegionEx();
	if (ch == '\n') {
		_lineHeadFlag = true;
		_strIndent.clear();
		_cntLine++;
		_cntCol = 0;
	} else {
		_cntCol++;
	}
	return sig.IsNoSignalled();
#endif
	return false;
}

}
