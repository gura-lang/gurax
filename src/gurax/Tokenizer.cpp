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
		if (String::IsWhite(ch)) {
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
		} else if (String::IsDigit(ch)) {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::Number;
		} else if (ch == '.') {
			_field.clear();
			_field.push_back(ch);
			_stat = Stat::NumberAfterPeriod;
		} else if (String::IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			if (IsTokenWatched()) {
				_field.clear();
				_field.push_back(ch);
				_stat = Stat::White;
			}
		} else if (String::IsSymbolFirst(ch)) {
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
			FeedToken(Token(TokenType::EOL, GetLineNo()));
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
			FeedToken(Token(TokenType::LBrace, GetLineNo()));
			if (IsTokenWatched()) {
				_field.clear();
				_lineNoTop = GetLineNo();
			}
			_stat = sig.IsSignalled()? Stat::Error : Stat::AfterLBrace;
		} else if (ch == '(') {
			FeedToken(Token(TokenType::LParenthesis, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '[') {
			FeedToken(Token(TokenType::LBracket, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '|' && _blockParamFlag && _tokenStack.CheckBlockParamEnd()) {
			_blockParamFlag = false;
			FeedToken(Token(TokenType::RBlockParam, GetLineNo()));
			if (sig.IsSignalled()) _stat = Stat::Error;
		} else if (ch == '`') {
			FeedToken(Token(TokenType::Quote, GetLineNo()));
			_stat = Stat::Start;
		} else if (ch == ':') {
			_stat = Stat::Colon;
		} else {
			size_t i = 0;
			static const struct {
				int ch;
				const TokenType *pTokenType;
			} tbl[] = {
				{ '?',	&TokenType::Question,		},
				{ '+',	&TokenType::DoubleChars,	},
				{ '-',	&TokenType::DoubleChars,	},
				{ '*',	&TokenType::DoubleChars,	},
				{ '/',	&TokenType::DoubleChars,	},
				{ '%',	&TokenType::DoubleChars,	},
				{ '=',	&TokenType::DoubleChars,	},
				{ '<',	&TokenType::DoubleChars,	},
				{ '>',	&TokenType::DoubleChars,	},
				{ '!',	&TokenType::DoubleChars,	}, // see also Stat::Symbol
				{ '|',	&TokenType::DoubleChars,	},
				{ '&',	&TokenType::DoubleChars,	},
				{ '^',	&TokenType::DoubleChars,	},
				{ '~',	&TokenType::Inv,			},
				{ ',',	&TokenType::Comma,			},
				{ ';',	&TokenType::Semicolon,		},
				{ ')',	&TokenType::RParenthesis,	},
				{ '}',	&TokenType::RBrace,			},
				{ ']',	&TokenType::RBracket,		},
				{ '\0',	&TokenType::EndOfFile,		},
			};
			for (i = 0; i < ArraySizeOf(tbl); i++) {
				if (tbl[i].ch == ch) break;
			}
			if (i >= ArraySizeOf(tbl)) {
				SetError(ERR_SyntaxError, "unexpected character '%c' (%d)", ch, ch);
				_stat = Stat::Error;
			} else if (tbl[i].pTokenType->IsIdentical(TokenType::DoubleChars)) {
				_field.clear();
				_field.push_back(ch);
				_stat = Stat::DoubleChars;
			} else if (_tokenStack.back().IsType(TokenType::Quote)) {
				_field.clear();
				_field.push_back(ch);
				FeedToken(Token(TokenType::Symbol, GetLineNo(), _field));
				if (sig.IsSignalled()) _stat = Stat::Error;
			} else {
				FeedToken(Token(*tbl[i].pTokenType, GetLineNo()));
				if (sig.IsSignalled()) _stat = Stat::Error;
			}
		}
		break;
	}
	case Stat::White: {
		if (String::IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			_field.push_back(ch);
		} else {
			_pTokenWatcher->FeedToken(Token(TokenType::Space, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::DoubleChars: {
		// this state comes from Stat::Start and Stat::Symbol
		static const struct {
			int chFirst;
			const TokenType *pTokenType;
			struct {
				int chSecond;
				const TokenType *pTokenType;
			} tblCand[10];
		} tbl[] = {
			{ '+', &TokenType::Add, {
				{ '=', &TokenType::AssignAdd	},
				{ '\0', &TokenType::Unknown		} } },
			{ '-', &TokenType::Sub, {
				{ '=', &TokenType::AssignSub	},
				{ '\0', &TokenType::Unknown		} } },
			{ '*', &TokenType::Mul, {
				{ '=', &TokenType::AssignMul	},
				{ '*', &TokenType::TripleChars	},
				{ '\0', &TokenType::Unknown		} } },
			{ '/', &TokenType::Div, {
				{ '=', &TokenType::AssignDiv	},
				{ '\0', &TokenType::Unknown		} } },
			{ '%', &TokenType::Mod, {
				{ '=', &TokenType::AssignMod	},
				{ '%', &TokenType::ModMod		},
				{ '\0', &TokenType::Unknown		} } },
			{ '=', &TokenType::Assign, {
				{ '=', &TokenType::Eq 			},
				{ '>', &TokenType::Pair			},
				{ '\0', &TokenType::Unknown		} } },
			{ '<', &TokenType::Lt, {
				{ '=', &TokenType::TripleChars	},
				{ '<', &TokenType::TripleChars	},
				{ '\0', &TokenType::Unknown		} } },
			{ '>', &TokenType::Gt, {
				{ '=', &TokenType::Ge			},
				{ '>', &TokenType::TripleChars	},
				{ '\0', &TokenType::Unknown		} } },
			{ '!', &TokenType::Not, {
				{ '=', &TokenType::Ne			},
				{ '\0', &TokenType::Unknown		} } },
			{ '|', &TokenType::Or, {
				{ '=', &TokenType::AssignOr 	},
				{ '|', &TokenType::TripleChars	},
				{ '.', &TokenType::TripleChars	},
				{ '^', &TokenType::TripleChars	},
				{ '*', &TokenType::TripleChars	},
				{ '+', &TokenType::TripleChars	},
				{ '-', &TokenType::TripleChars	},
				{ '&', &TokenType::TripleChars	},
				{ '\0', &TokenType::Unknown		} } },
			{ '&', &TokenType::And, {
				{ '=', &TokenType::AssignAnd	},
				{ '&', &TokenType::AndAnd		},
				{ '\0', &TokenType::Unknown		} } },
			{ '^', &TokenType::Xor, {
				{ '=', &TokenType::AssignXor	},
				{ '\0', &TokenType::Unknown		} } },
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
				const TokenType *pTokenType = tbl[i].pTokenType;
				bool pushbackFlag = true;
				for (size_t j = 0; j < ArraySizeOf(tbl[i].tblCand); j++) {
					if (tbl[i].tblCand[j].chSecond == '\0') break;
					if (tbl[i].tblCand[j].chSecond == ch) {
						_field.push_back(ch);
						pTokenType = tbl[i].tblCand[j].pTokenType;
						pushbackFlag = false;
						break;
					}
				}
				if (pTokenType->IsIdentical(TokenType::TripleChars)) {
					_stat = Stat::TripleChars;
				} else if (_tokenStack.back().IsType(TokenType::Quote)) {
					FeedToken(Token(TokenType::Symbol, GetLineNo(), _field));
					if (sig.IsSignalled()) _stat = Stat::Error;
				} else {
					FeedToken(Token(*pTokenType, GetLineNo()));
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
			const TokenType *pTokenType;
			bool pushbackSecondFlag;
			struct {
				int chThird;
				const TokenType *pTokenType;
			} tblCand[5];
		} tbl[] = {
			{ "**", &TokenType::Pow, false, {
				{ '=', &TokenType::AssignPow	},
				{ '\0', &TokenType::Unknown		} } },
			{ "<=", &TokenType::Le, false, {
				{ '>', &TokenType::Cmp			},
				{ '\0', &TokenType::Unknown		} } },
			{ "<<", &TokenType::Shl, false, {
				{ '=', &TokenType::AssignShl	},
				{ '\0', &TokenType::Unknown		} } },
			{ ">>", &TokenType::Shr, false, {
				{ '=', &TokenType::AssignShr	},
				{ '\0', &TokenType::Unknown		} } },
			{ "|.", &TokenType::Or, true, {
				{ '|', &TokenType::Dot			},
				{ '\0', &TokenType::Unknown		} } },
			{ "|^", &TokenType::Or, true, {
				{ '|', &TokenType::Cross		},
				{ '\0', &TokenType::Unknown		} } },
			{ "|*", &TokenType::Or, true, {
				{ '|', &TokenType::Gear			},
				{ '\0', &TokenType::Unknown		} } },
			{ "|+", &TokenType::Or, true, {
				{ '|', &TokenType::Concat		},
				{ '\0', &TokenType::Unknown		} } },
			{ "|-", &TokenType::Or, true, {
				{ '|', &TokenType::Difference	},
				{ '\0', &TokenType::Unknown		} } },
			{ "|&", &TokenType::Or, true, {
				{ '|', &TokenType::Intersection	},
				{ '\0', &TokenType::Unknown		} } },
			{ "||", &TokenType::OrOr, false, {
				{ '|', &TokenType::Union		},
				{ '\0', &TokenType::Unknown		} } },
		};
		_stat = Stat::Start;
		for (size_t i = 0; i < ArraySizeOf(tbl); i++) {
			if (_field.compare(tbl[i].strFirst) != 0) continue;
			const TokenType *pTokenType = tbl[i].pTokenType;
			bool pushbackFlag = true;
			bool pushbackSecondFlag = tbl[i].pushbackSecondFlag;
			for (size_t j = 0; j < ArraySizeOf(tbl[i].tblCand); j++) {
				if (tbl[i].tblCand[j].chThird == '\0') break;
				if (tbl[i].tblCand[j].chThird == ch) {
					_field.push_back(ch);
					pTokenType = tbl[i].tblCand[j].pTokenType;
					pushbackFlag = false;
					pushbackSecondFlag = false;
					break;
				}
			}
			if (_tokenStack.back().IsType(TokenType::Quote)) {
				FeedToken(Token(TokenType::Symbol, GetLineNo(), _field));
				if (sig.IsSignalled()) _stat = Stat::Error;
			} else {
				FeedToken(Token(*pTokenType, GetLineNo()));
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
				_pTokenWatcher->FeedToken(Token(TokenType::Escape, GetLineNo(), _field));
			}
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		} else if (ch == '\n') {
			if (IsTokenWatched()) {
				_field.push_back(ch);
				_pTokenWatcher->FeedToken(Token(TokenType::Escape, GetLineNo(), _field));
			}
			_stat = Stat::Start;
		} else if (String::IsWhite(ch)) {
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
			FeedToken(Token(TokenType::ColonColon, GetLineNo()));
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else if (ch == '*') {
			FeedToken(Token(TokenType::ColonAsterisk, GetLineNo()));
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else if (ch == '&') {
			FeedToken(Token(TokenType::ColonAnd, GetLineNo()));
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else {
			const TokenType *pTokenType = _tokenStack.back().IsSuffixToken()?
									&TokenType::ColonAfterSuffix : &TokenType::Colon;
			FeedToken(Token(*pTokenType, GetLineNo()));
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
				_pTokenWatcher->FeedToken(Token(TokenType::Space, _lineNoTop, _field));
			}
			FeedToken(Token(TokenType::LBlockParam, GetLineNo()));
			if (sig.IsSignalled()) {
				_stat = Stat::Error;
			} else {
				_blockParamFlag = true;
				_stat = Stat::Start;
			}
		} else if (ch == '\n' || String::IsWhite(ch)) {
			if (IsTokenWatched()) _field.push_back(ch);
		} else {
			if (IsTokenWatched() && !_field.empty()) {
				_pTokenWatcher->FeedToken(Token(TokenType::Space, _lineNoTop, _field));
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
		} else if(String::IsOctDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::NumberOct;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Number;
		}
		break;
	}
	case Stat::NumberHex: {
		if (String::IsHexDigit(ch)) {
			_field.push_back(ch);
		} else if (_field.size() <= 2) {
			SetError(ERR_SyntaxError, "wrong format of hexadecimal number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(Token(TokenType::Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberOct: {
		if (String::IsOctDigit(ch)) {
			_field.push_back(ch);
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(Token(TokenType::Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberBin: {
		if (String::IsBinDigit(ch)) {
			_field.push_back(ch);
		} else if (_field.size() <= 2) {
			SetError(ERR_SyntaxError, "wrong format of binary number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(Token(TokenType::Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberAfterPeriod: {
		if (ch == '.') {
			if (_tokenStack.back().IsType(TokenType::Quote)) {
				_field.push_back(ch);
				FeedToken(Token(TokenType::Symbol, GetLineNo(), _field));
			} else {
				FeedToken(Token(TokenType::Seq, GetLineNo()));
			}
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		} else if (String::IsDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::Number;
		} else {
			FeedToken(Token(TokenType::Period, GetLineNo()));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Number: {
		if (String::IsDigit(ch)) {
			_field.push_back(ch);
		} else if (ch == '.') {
			size_t pos = _field.find('.');
			if (pos == _field.length() - 1) {
				_field.resize(pos);
				FeedToken(Token(TokenType::Number, GetLineNo(), _field));
				if (!sig.IsSignalled()) {
					FeedToken(Token(TokenType::Seq, GetLineNo()));
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
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(Token(TokenType::Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberExpAfterE: {
		if (String::IsDigit(ch)) {
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
		if (String::IsDigit(ch)) {
			_field.push_back(ch);
			_stat = Stat::NumberExp;
		} else {
			SetError(ERR_SyntaxError, "wrong exponential expression");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberExp: {
		if (String::IsDigit(ch)) {
			_field.push_back(ch);
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			FeedToken(Token(TokenType::Number, GetLineNo(), _field));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberSuffixed: {
		if (String::IsSymbolFollower(ch)) {
			_suffix.push_back(ch);
		} else {
			if (IsTokenWatched()) {
				FeedToken(Token(TokenType::NumberSuffixed, GetLineNo(),
									 _field, _suffix, _field + _suffix));
			} else {
				FeedToken(Token(TokenType::NumberSuffixed, GetLineNo(), _field, _suffix));
			}
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Symbol: {
		if (String::IsSymbolFollower(ch)) {
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
			if (_field == "in" && !_tokenStack.back().IsType(TokenType::Quote)) {
				FeedToken(Token(TokenType::Contains, GetLineNo()));
			} else {
				FeedToken(Token(TokenType::Symbol, GetLineNo(), _field));
			}
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::SymbolExclamation: {
		if (ch == '=' || ch == '!') {
			FeedToken(Token(TokenType::Symbol, GetLineNo(), _field));
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
					env, Token(TokenType::CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(Token(TokenType::EOL, GetLineNo()));
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
					env, Token(TokenType::CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(Token(TokenType::EOL, GetLineNo()));
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
					env, Token(TokenType::CommentLine, GetLineNo(), _field));
			}
			if (ch == '\n') FeedToken(Token(TokenType::EOL, GetLineNo()));
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
						env, Token(TokenType::CommentBlock, _lineNoTop, _field));
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
		} else if (String::IsSymbolFirst(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::StringSuffixed;
		} else {
			const TokenType *pTokenType = GetTokenTypeForString(_stringInfo);
			FeedToken(Token(*pTokenType, GetLineNo(), _field, "", _strSource));
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
		if (String::IsWhite(ch)) {
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
			} else if (String::IsOctDigit(ch)) {
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
		if (String::IsHexDigit(ch)) {
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
		if (String::IsOctDigit(ch)) {
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
		if (String::IsHexDigit(ch)) {
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
		if (String::IsSymbolFirst(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::StringSuffixed;
		} else {
			const TokenType *pTokenType = GetTokenTypeForString(_stringInfo);
			FeedToken(Token(*pTokenType, GetLineNo(), _field, "", _strSource));
			Gurax_PushbackEx(ch);
			_stat = sig.IsSignalled()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::StringSuffixed: {
		if (String::IsSymbolFollower(ch)) {
			if (IsTokenWatched()) _strSource.push_back(ch);
			_suffix.push_back(ch);
		} else {
			FeedToken(Token(TokenType::StringSuffixed, GetLineNo(), _field, _suffix, _strSource));
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
