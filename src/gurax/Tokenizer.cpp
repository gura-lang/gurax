//==============================================================================
// Tokenizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// MagicCommentParser
//-----------------------------------------------------------------------------
MagicCommentParser::MagicCommentParser() : _stat(STAT_Start)
{
}

MagicCommentParser::~MagicCommentParser()
{
}

bool MagicCommentParser::ParseChar(char ch)
{
	bool rtn = false;
	if (_stat == STAT_Idle) {
		// nothing to do
	} else if (_stat == STAT_Start) {
		if (String::IsAlpha(ch)) {
			_field += ch;
		} else if (ch == ':' || ch == '=') {
			if (_field.size() >= 6 && ::strcmp(_field.c_str() + _field.size() - 6, "coding") == 0) {
				_stat = STAT_SkipSpace;
			} else {
				_field.clear();
			}
		} else {
			_field.clear();
		}
	} else if (_stat == STAT_SkipSpace) {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.' || ch == '-' || ch == '_') {
			_field.clear();
			_field += ch;
			_stat = STAT_CodingName;
		} else {
			_stat = STAT_Start;
		}
	} else if (_stat == STAT_CodingName) {
		if (String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.' || ch == '-' || ch == '_') {
			_field += ch;
		} else {
			rtn = true;
			_stat = STAT_Idle;
		}
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
Tokenizer::Tokenizer(const String &sourceName, int cntLineStart, bool enablePreparatorFlag)
	//_stat(STAT_BOF), _lineHeadFlag(true),
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
	case STAT_BOF: {
		if (ch == '\xef') {
			_field.clear();
			_field.push_back(ch);
			_stat = STAT_BOF_2nd;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_Start;
		}
		break;
	}
	case STAT_BOF_2nd: {
		if (ch == '\xbb') {
			_field.push_back(ch);
			_stat = STAT_BOF_3rd;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_Symbol;
		}
		break;
	}
	case STAT_BOF_3rd: {
		if (ch == '\xbf') {
			_stat = STAT_Start;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_Symbol;
		}
		break;
	}
	case STAT_Start: {
		if (ch == '0') {
			_field.clear();
			_field.push_back(ch);
			_stat = STAT_NumberPre;
		} else if (IsDigit(ch)) {
			_field.clear();
			_field.push_back(ch);
			_stat = STAT_Number;
		} else if (ch == '.') {
			_field.clear();
			_field.push_back(ch);
			_stat = STAT_NumberAfterPeriod;
		} else if (IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
				_stat = STAT_White;
			}
		} else if (IsSymbolFirstChar(ch)) {
			_field.clear();
			_field.push_back(ch);
			_stat = STAT_Symbol;
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
			_stat = STAT_StringFirst;
		} else if (ch == '\\') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
			}
			_stat = STAT_Escape;
		} else if (ch == '\n') {
			FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			if (sig.IsSignalled()) _stat = STAT_Error;
		} else if (ch == '#') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
			}
			if (sig.IsSignalled()) {
				_stat = STAT_Error;
			} else if (_cntLine == 0) {
				_stat = STAT_CommentLineTop;
			} else if (_cntLine == 1 && _appearShebangFlag) {
				_stat = STAT_MagicCommentLine;
			} else {
				_stat = STAT_CommentLine;
			}
		} else if (ch == '{') {
			FeedToken(env, Token(TOKEN_LBrace, GetLineNo()));
			if (IsTokenWatched()) {
				_field.clear();
				_lineNoTop = GetLineNo();
			}
			_stat = sig.IsSignalled()? STAT_Error : STAT_AfterLBrace;
		} else if (ch == '(') {
			FeedToken(env, Token(TOKEN_LParenthesis, GetLineNo()));
			if (sig.IsSignalled()) _stat = STAT_Error;
		} else if (ch == '[') {
			FeedToken(env, Token(TOKEN_LBracket, GetLineNo()));
			if (sig.IsSignalled()) _stat = STAT_Error;
		} else if (ch == '|' && _blockParamFlag && _tokenStack.CheckBlockParamEnd()) {
			_blockParamFlag = false;
			FeedToken(env, Token(TOKEN_RBlockParam, GetLineNo()));
			if (sig.IsSignalled()) _stat = STAT_Error;
		} else if (ch == '`') {
			FeedToken(env, Token(TOKEN_Quote, GetLineNo()));
			_stat = STAT_Start;
		} else if (ch == ':') {
			_stat = STAT_Colon;
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
				{ '!',	&TOKEN_DoubleChars,	}, // see also STAT_Symbol
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
				_stat = STAT_Error;
			} else if (tbl[i].pTokenInfo->IsIdentical(TOKEN_DoubleChars)) {
				_field.clear();
				_field.push_back(ch);
				_stat = STAT_DoubleChars;
			} else if (_tokenStack.back().IsType(TOKEN_Quote)) {
				_field.clear();
				_field.push_back(ch);
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
				if (sig.IsSignalled()) _stat = STAT_Error;
			} else {
				FeedToken(env, Token(*tbl[i].pTokenInfo, GetLineNo()));
				if (sig.IsSignalled()) _stat = STAT_Error;
			}
		}
		break;
	}
	case STAT_White: {
		if (IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			_field.push_back(ch);
		} else {
			_pTokenWatcher->FeedToken(env, Token(TOKEN_Space, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = STAT_Start;
		}
		break;
	}
	case STAT_DoubleChars: {
		// this state comes from STAT_Start and STAT_Symbol
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
			_stat = STAT_CommentBlock;
		} else if (chFirst == '/' && ch == '/') {
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(chFirst);
				_field.push_back(ch);
			}
			if (_cntLine == 0 || (_cntLine == 1 && _appearShebangFlag)) {
				_stat = STAT_MagicCommentLine;
			} else {
				_stat = STAT_CommentLine;
			}
		} else if (chFirst == '*' && ch == '/') {
			SetError(ERR_SyntaxError, "unmatching comment description");
			_stat = STAT_Error;
		} else {
			_stat = STAT_Start;
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
					_stat = STAT_TripleChars;
				} else if (_tokenStack.back().IsType(TOKEN_Quote)) {
					FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
					if (sig.IsSignalled()) _stat = STAT_Error;
				} else {
					FeedToken(env, Token(*pTokenInfo, GetLineNo()));
					if (sig.IsSignalled()) _stat = STAT_Error;
				}
				if (pushbackFlag) Gurax_PushbackEx(ch);
				break;
			}
			// tables have a bug if i reaches at ArraySizeOf(tbl)
		}
		break;
	}
	case STAT_TripleChars: {
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
		_stat = STAT_Start;
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
				if (sig.IsSignalled()) _stat = STAT_Error;
			} else {
				FeedToken(env, Token(*pTokenInfo, GetLineNo()));
				if (sig.IsSignalled()) _stat = STAT_Error;
			}
			if (pushbackFlag) Gurax_PushbackEx(ch);
			if (pushbackSecondFlag) Gurax_PushbackEx(_field[1]);
			break;
		}
		// tables have a bug if i reaches at ArraySizeOf(tbl)
		break;
	}
	case STAT_Escape: {
		if (ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Escape, GetLineNo(), _field));
			}
			Gurax_PushbackEx(ch);
			_stat = STAT_Start;
		} else if (ch == '\n') {
			if (IsTokenWatched()) {
				_field.push_back(ch);
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Escape, GetLineNo(), _field));
			}
			_stat = STAT_Start;
		} else if (IsWhite(ch)) {
			if (IsTokenWatched()) {
				_field.push_back(ch);
			}
		} else {
			SetError(ERR_SyntaxError, "invalid escape character");
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_Colon: {
		if (ch == ':') {
			FeedToken(env, Token(TOKEN_ColonColon, GetLineNo()));
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		} else if (ch == '*') {
			FeedToken(env, Token(TOKEN_ColonAsterisk, GetLineNo()));
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		} else if (ch == '&') {
			FeedToken(env, Token(TOKEN_ColonAnd, GetLineNo()));
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		} else {
			const TokenInfo *pTokenInfo = _tokenStack.back().IsSuffixToken()?
									&TOKEN_ColonAfterSuffix : &TOKEN_Colon;
			FeedToken(env, Token(*pTokenInfo, GetLineNo()));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_Error: {
		InitStack();
		_blockParamFlag = false;
		Gurax_PushbackEx(ch);
		_stat = STAT_ErrorRecovery;
		break;
	}
	case STAT_ErrorRecovery: {
		if (ch == '\n' || ch == '\0') {
			Gurax_PushbackEx(ch);
			_stat = STAT_Start;
		} else {
			// nothing to do
		}
		break;
	}
	case STAT_AfterLBrace: {
		if (ch == '|') {
			if (IsTokenWatched() && !_field.empty()) {
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Space, _lineNoTop, _field));
			}
			FeedToken(env, Token(TOKEN_LBlockParam, GetLineNo()));
			if (sig.IsSignalled()) {
				_stat = STAT_Error;
			} else {
				_blockParamFlag = true;
				_stat = STAT_Start;
			}
		} else if (ch == '\n' || IsWhite(ch)) {
			if (IsTokenWatched()) _field.push_back(ch);
		} else {
			if (IsTokenWatched() && !_field.empty()) {
				_pTokenWatcher->FeedToken(env, Token(TOKEN_Space, _lineNoTop, _field));
			}
			Gurax_PushbackEx(ch);
			_stat = STAT_Start;
		}
		break;
	}
	case STAT_NumberPre: {
		if (ch == 'x' || ch == 'X') {
			_field.push_back(ch);
			_stat = STAT_NumberHex;
		} else if (ch == 'b' || ch == 'B') {
			_field.push_back(ch);
			_stat = STAT_NumberBin;
		} else if(IsOctDigit(ch)) {
			_field.push_back(ch);
			_stat = STAT_NumberOct;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_Number;
		}
		break;
	}
	case STAT_NumberHex: {
		if (IsHexDigit(ch)) {
			_field.push_back(ch);
		} else if (_field.size() <= 2) {
			SetError(ERR_SyntaxError, "wrong format of hexadecimal number");
			Gurax_PushbackEx(ch);
			_stat = STAT_Error;
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_NumberOct: {
		if (IsOctDigit(ch)) {
			_field.push_back(ch);
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_NumberBin: {
		if (IsBinDigit(ch)) {
			_field.push_back(ch);
		} else if (_field.size() <= 2) {
			SetError(ERR_SyntaxError, "wrong format of binary number");
			Gurax_PushbackEx(ch);
			_stat = STAT_Error;
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_NumberAfterPeriod: {
		if (ch == '.') {
			if (_tokenStack.back().IsType(TOKEN_Quote)) {
				_field.push_back(ch);
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
			} else {
				FeedToken(env, Token(TOKEN_Seq, GetLineNo()));
			}
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		} else if (IsDigit(ch)) {
			_field.push_back(ch);
			_stat = STAT_Number;
		} else {
			FeedToken(env, Token(TOKEN_Period, GetLineNo()));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_Number: {
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
				_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
			} else if (pos == String::npos) {
				_field.push_back(ch);
			} else {
				SetError(ERR_SyntaxError, "period has already been scanned");
				_stat = STAT_Error;
			}
		} else if (ch == 'e' || ch == 'E') {
			_field.push_back(ch);
			_stat = STAT_NumberExpAfterE;
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_NumberExpAfterE: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
			_stat = STAT_NumberExp;
		} else if (ch == '+' || ch == '-') {
			_field.push_back(ch);
			_stat = STAT_NumberExpAfterSign;
		} else {
			SetError(ERR_SyntaxError, "wrong exponential expression");
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_NumberExpAfterSign: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
			_stat = STAT_NumberExp;
		} else {
			SetError(ERR_SyntaxError, "wrong exponential expression");
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_NumberExp: {
		if (IsDigit(ch)) {
			_field.push_back(ch);
		} else if (IsSymbolFirstChar(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_NumberSuffixed;
		} else {
			FeedToken(env, Token(TOKEN_Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_NumberSuffixed: {
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
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_Symbol: {
		if (IsSymbolChar(ch)) {
			_field.push_back(ch);
		} else if (ch == '!') {
			_stat = STAT_SymbolExclamation;
		} else if ((ch == '"' || ch == '\'') && CheckStringPrefix(_stringInfo, _field)) {
			_stringInfo.chBorder = ch;
			if (IsTokenWatched()) {
				_strSource.clear();
				_strSource += _field;
				_strSource.push_back(ch);
			}
			_field.clear();
			_stat = STAT_StringFirst;
		} else {
			if (_field == "in" && !_tokenStack.back().IsType(TOKEN_Quote)) {
				FeedToken(env, Token(TOKEN_Contains, GetLineNo()));
			} else {
				FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
			}
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_SymbolExclamation: {
		if (ch == '=' || ch == '!') {
			FeedToken(env, Token(TOKEN_Symbol, GetLineNo(), _field));
			if (sig.IsSignalled()) {
				_stat = STAT_Error;
			} else {
				_field.clear();
				_field.push_back('!');
				Gurax_PushbackEx(ch);
				_stat = STAT_DoubleChars;
			}
		} else {
			_field.push_back('!');
			Gurax_PushbackEx(ch);
			_stat = STAT_Symbol;
		}
		break;
	}
	case STAT_CommentLineTop: {
		if (ch == '!') {
			if (IsTokenWatched()) _field.push_back(ch);
			_appearShebangFlag = true;
			_stat = STAT_ShebangLine;
		} else {
			_stat = STAT_MagicCommentLine;
			Gurax_PushbackEx(ch);
		}
		break;
	}
	case STAT_MagicCommentLine: {
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
			_stat = STAT_Start;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case STAT_ShebangLine: {
		if (ch == '\n' || ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(
					env, Token(TOKEN_CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			_stat = STAT_Start;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case STAT_CommentLine: {
		if (ch == '\n' || ch == '\0') {
			if (IsTokenWatched()) {
				_pTokenWatcher->FeedToken(
					env, Token(TOKEN_CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(env, Token(TOKEN_EOL, GetLineNo()));
			_stat = STAT_Start;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case STAT_CommentBlock: {
		if (ch == '*') {
			if (IsTokenWatched()) _field.push_back(ch);
			_stat = STAT_CommentBlockEnd;
		} else if (ch == '/') {
			if (IsTokenWatched()) _field.push_back(ch);
			_stat = STAT_CommentBlockNest;
		} else {
			if (IsTokenWatched()) _field.push_back(ch);
		}
		break;
	}
	case STAT_CommentBlockEnd: {
		if (ch == '/') {
			if (IsTokenWatched()) _field.push_back(ch);
			_commentNestLevel--;
			if (_commentNestLevel > 0) {
				_stat = STAT_CommentBlock;
			} else {
				if (IsTokenWatched()) {
					_pTokenWatcher->FeedToken(
						env, Token(TOKEN_CommentBlock, _lineNoTop, _field));
				}
				_stat = STAT_Start;
			}
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_CommentBlock;
		}
		break;
	}
	case STAT_CommentBlockNest: {
		if (ch == '*') {
			if (IsTokenWatched()) _field.push_back(ch);
			_commentNestLevel++;
			_stat = STAT_CommentBlock;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_CommentBlock;
		}
		break;
	}
	case STAT_StringFirst: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_StringSecond;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_String;
		}
		break;
	}
	case STAT_StringSecond: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			if (_stringInfo.wiseFlag) {
				_stringInfo.strIndentRef = _strIndent;
				_stat = STAT_MStringWise;
			} else {
				_stat = STAT_MString;
			}
		} else if (IsSymbolFirstChar(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_StringSuffixed;
		} else {
			const TokenInfo *pTokenInfo = GetTokenInfoForString(_stringInfo);
			FeedToken(env, Token(*pTokenInfo, GetLineNo(), _field, "", _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_String: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_StringPost;
		} else if (ch == '\\') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.statRtn = STAT_String;
			_stat = STAT_StringEsc;
		} else if (ch == '\0' || ch == '\n') {
			SetError(ERR_SyntaxError, "string is not terminated correctly");
			_stat = STAT_Error;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_field.push_back(ch);
		}
		break;
	}
	case STAT_MStringWise: {
		if (ch == '\n') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_MStringLineHead;
		} else {
			Gurax_PushbackEx(ch);
			_stat = STAT_MString;
		}
		break;
	}
	case STAT_MString: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_MStringEndFirst;
		} else if (ch == '\\') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stringInfo.statRtn = STAT_MString;
			_stat = STAT_StringEsc;
		} else if (ch == '\0') {
			SetError(ERR_SyntaxError, "string is not terminated correctly");
			_stat = STAT_Error;
		} else if (ch == '\n' && _stringInfo.wiseFlag) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_field.push_back(ch);
			_stat = STAT_MStringLineHead;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_field.push_back(ch);
		}
		break;
	}
	case STAT_MStringLineHead: {
		if (IsWhite(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			if (_strIndent.size() == _stringInfo.strIndentRef.size()) {
				if (_strIndent != _stringInfo.strIndentRef) {
					_field += _strIndent;
				}
				_stat = STAT_MString;
			}
		} else {
			_field += _strIndent;
			Gurax_PushbackEx(ch);
			_stat = STAT_MString;
		}
		break;
	}
	case STAT_StringEsc: {
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
				_stat = STAT_StringEscHex;
			} else if (IsOctDigit(ch)) {
				_stringInfo.accum = ConvOctDigit(ch);
				_stringInfo.cntRest = 2;
				_stat = STAT_StringEscOct;
			} else if (ch == 'u') {
				_stringInfo.accum = 0x0000;
				_stringInfo.cntRest = 4;
				_stat = STAT_StringEscUnicode;
			} else if (ch == 'U') {
				_stringInfo.accum = 0x00000000;
				_stringInfo.cntRest = 8;
				_stat = STAT_StringEscUnicode;
			} else {
				_field.push_back(GetEscaped(ch));
				_stat = _stringInfo.statRtn;
			}
		}
		break;
	}
	case STAT_StringEscHex: {
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
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_StringEscOct: {
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
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_StringEscUnicode: {
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
			_stat = STAT_Error;
		}
		break;
	}
	case STAT_StringInCommentBlock: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_CommentBlock;
		} else if (ch == '\\') {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_StringEscInCommentBlock;
		} else {
			if (IsTokenWatched()) _strSource.push_back(ch);
		}
		break;
	}
	case STAT_StringEscInCommentBlock: {
		if (IsTokenWatched()) _strSource.push_back(ch);
		_stat = STAT_StringInCommentBlock;
		break;
	}
	case STAT_MStringEndFirst: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_MStringEndSecond;
		} else {
			if (IsTokenWatched()) _strSource.push_back(_stringInfo.chBorder);
			_field.push_back(_stringInfo.chBorder);
			Gurax_PushbackEx(ch);
			_stat = STAT_MString;
		}
		break;
	}
	case STAT_MStringEndSecond: {
		if (ch == _stringInfo.chBorder) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_stat = STAT_StringPost;
		} else {
			if (IsTokenWatched()) {
				_strSource.push_back(_stringInfo.chBorder);
				_strSource.push_back(_stringInfo.chBorder);
			}
			_field.push_back(_stringInfo.chBorder);
			_field.push_back(_stringInfo.chBorder);
			Gurax_PushbackEx(ch);
			_stat = STAT_MString;
		}
		break;
	}
	case STAT_StringPost: {
		if (IsSymbolFirstChar(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = STAT_StringSuffixed;
		} else {
			const TokenInfo *pTokenInfo = GetTokenInfoForString(_stringInfo);
			FeedToken(env, Token(*pTokenInfo, GetLineNo(), _field, "", _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_StringSuffixed: {
		if (IsSymbolChar(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.push_back(ch);
		} else {
			FeedToken(env, Token(TOKEN_StringSuffixed, GetLineNo(), _field, _suffix, _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? STAT_Error : STAT_Start;
		}
		break;
	}
	case STAT_RecoverConsole: {
		if (ch == '\n') {
			_stat = STAT_BOF;
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
