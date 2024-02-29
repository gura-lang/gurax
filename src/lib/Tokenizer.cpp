//==============================================================================
// Tokenizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
Tokenizer::Tokenizer(TokenWatcher& tokenWatcher, StringReferable* pPathNameSrc) :
	_tokenWatcher(tokenWatcher), _pPathNameSrc(pPathNameSrc), _pTokenStack(new TokenStack())
{
	_pTokenStack->Initialize();
	_segment.reserve(1024 * 64);
	_suffix.reserve(128);
	_source.reserve(1024 * 64);
}

void Tokenizer::RecoverError()
{
	_pTokenStack->Initialize();
	_stat = Stat::BOF;
	_lineHeadFlag = true;
	_cntCol = 0;
}

void Tokenizer::FeedChar(char ch)
{
	if (ch == '\r') return;
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
			_segment.clear();
			_segment.push_back(ch);
			_stat = Stat::BOF_2nd;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::BOF_2nd: {
		if (ch == '\xbb') {
			_segment.push_back(ch);
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
		_lineNoTop = _lineNoBodyTop = GetLineNo();
		if (ch == '0') {
			_segment.clear();
			_segment.push_back(ch);
			_stat = Stat::NumberPre;
		} else if (String::IsDigit(ch)) {
			_segment.clear();
			_segment.push_back(ch);
			_stat = Stat::Number;
		} else if (ch == '.') {
			_segment.clear();
			_segment.push_back(ch);
			_stat = Stat::NumberAfterPeriod;
		} else if (String::IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			if (_verboseFlag) {
				_segment.clear();
				_segment.push_back(ch);
				_stat = Stat::White;
			}
		} else if (String::IsSymbolFirst(ch)) {
			_segment.clear();
			_segment.push_back(ch);
			_stat = Stat::Symbol;
		} else if (ch == '"' || ch == '\'') {
			_stringInfo.chBorder = ch;
			_stringInfo.rawFlag = false;
			_stringInfo.wiseFlag = false;
			_stringInfo.type = StringType::String;
			_segment.clear();
			if (_verboseFlag) {
				_source.clear();
				_source.push_back(ch);
			}
			_stat = Stat::StringFirst;
		} else if (ch == '\\') {
			if (_verboseFlag) {
				_segment.clear();
				_segment.push_back(ch);
			}
			_stat = Stat::Escape;
		} else if (ch == '\n') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::EndOfLine, _lineNoTop, lineNo));
			if (Error::IsIssued()) _stat = Stat::Error;
		} else if (ch == '#') {
			if (_verboseFlag) {
				_segment.clear();
				_segment.push_back(ch);
			}
			if (Error::IsIssued()) {
				_stat = Stat::Error;
			} else if (_cntLine == 0) {
				_stat = Stat::CommentLineTop;
			} else if (_cntLine == 1 && _appearShebangFlag) {
				_stat = Stat::MagicCommentLine;
			} else {
				_stat = Stat::CommentLine;
			}
		} else if (ch == '{') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::LBrace, _lineNoTop, lineNo, new ExprLink()));
			if (_verboseFlag) {
				_segment.clear();
			}
			_stat = Error::IsIssued()? Stat::Error : Stat::AfterLBrace;
		} else if (ch == '(') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::LParenthesis, _lineNoTop, lineNo, new ExprLink()));
			if (Error::IsIssued()) _stat = Stat::Error;
		} else if (ch == '[') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::LBracket, _lineNoTop, lineNo, new ExprLink()));
			if (Error::IsIssued()) _stat = Stat::Error;
		} else if (ch == '|' && _blockParamFlag && GetTokenStack().CheckBlockParamEnd()) {
			int lineNo = GetLineNo();
			_blockParamFlag = false;
			_tokenWatcher.FeedToken(new Token(TokenType::RBlockParam, _lineNoTop, lineNo));
			if (Error::IsIssued()) _stat = Stat::Error;
		} else if (ch == '`') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Quote, _lineNoTop, lineNo));
			_stat = Stat::Start;
		} else if (ch == ':') {
			_stat = Stat::Colon;
		} else {
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
			auto pEntry = std::begin(tbl);
			for ( ; pEntry != std::end(tbl); pEntry++) if (pEntry->ch == ch) break;
			if (pEntry == std::end(tbl)) {
				IssueError(ErrorType::SyntaxError, "unexpected character '%c' (%d)", ch, ch);
				_stat = Stat::Error;
			} else if (pEntry->pTokenType->IsIdentical(TokenType::DoubleChars)) {
				_segment.clear();
				_segment.push_back(ch);
				_stat = Stat::DoubleChars;
			} else if (GetTokenStack().back()->IsType(TokenType::Quote)) {
				int lineNo = GetLineNo();
				_segment.clear();
				_segment.push_back(ch);
				_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
				if (Error::IsIssued()) _stat = Stat::Error;
			} else {
				int lineNo = GetLineNo();
				_tokenWatcher.FeedToken(new Token(*pEntry->pTokenType, _lineNoTop, lineNo));
				if (Error::IsIssued()) _stat = Stat::Error;
			}
		}
		break;
	}
	case Stat::White: {
		if (String::IsWhite(ch) || ch == '\x0c') { // code 0x0c is page-break
			_segment.push_back(ch);
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Space, _lineNoTop, lineNo, _segment));
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
		int chFirst = _segment[0];
		if (chFirst == '/' && ch == '*') {
			if (_verboseFlag) {
				_segment.clear();
				_segment.push_back(chFirst);
				_segment.push_back(ch);
			}
			_commentNestLevel = 1;
			_stat = Stat::CommentBlock;
		} else if (chFirst == '/' && ch == '/') {
			if (_verboseFlag) {
				_segment.clear();
				_segment.push_back(chFirst);
				_segment.push_back(ch);
			}
			if (_cntLine == 0 || (_cntLine == 1 && _appearShebangFlag)) {
				_stat = Stat::MagicCommentLine;
			} else {
				_stat = Stat::CommentLine;
			}
		} else if (chFirst == '*' && ch == '/') {
			IssueError(ErrorType::SyntaxError, "unmatching comment description");
			_stat = Stat::Error;
		} else {
			_stat = Stat::Start;
			for (const auto& entry : tbl) {
				if (entry.chFirst != chFirst) continue;
				const TokenType *pTokenType = entry.pTokenType;
				bool pushbackFlag = true;
				for (const auto& entryCand : entry.tblCand) {
					if (entryCand.chSecond == '\0') break;
					if (entryCand.chSecond == ch) {
						_segment.push_back(ch);
						pTokenType = entryCand.pTokenType;
						pushbackFlag = false;
						break;
					}
				}
				if (pTokenType->IsIdentical(TokenType::TripleChars)) {
					_stat = Stat::TripleChars;
				} else if (GetTokenStack().back()->IsType(TokenType::Quote)) {
					int lineNo = GetLineNo();
					_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
					if (Error::IsIssued()) _stat = Stat::Error;
				} else {
					int lineNo = GetLineNo();
					_tokenWatcher.FeedToken(new Token(*pTokenType, _lineNoTop, lineNo));
					if (Error::IsIssued()) _stat = Stat::Error;
				}
				if (pushbackFlag) Gurax_PushbackEx(ch);
				break;
			}
			// the table has a bug if the loop reaches at the end
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
		for (const auto& entry : tbl) {
			if (_segment.compare(entry.strFirst) != 0) continue;
			const TokenType *pTokenType = entry.pTokenType;
			bool pushbackFlag = true;
			bool pushbackSecondFlag = entry.pushbackSecondFlag;
			for (const auto& entryCand : entry.tblCand) {
				if (entryCand.chThird == '\0') break;
				if (entryCand.chThird == ch) {
					_segment.push_back(ch);
					pTokenType = entryCand.pTokenType;
					pushbackFlag = false;
					pushbackSecondFlag = false;
					break;
				}
			}
			if (GetTokenStack().back()->IsType(TokenType::Quote)) {
				int lineNo = GetLineNo();
				_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
				if (Error::IsIssued()) _stat = Stat::Error;
			} else {
				int lineNo = GetLineNo();
				_tokenWatcher.FeedToken(new Token(*pTokenType, _lineNoTop, lineNo));
				if (Error::IsIssued()) _stat = Stat::Error;
			}
			if (pushbackFlag) Gurax_PushbackEx(ch);
			if (pushbackSecondFlag) Gurax_PushbackEx(_segment[1]);
			break;
		}
		// the table has a bug if the loop reaches at the end
		break;
	}
	case Stat::Escape: {
		if (ch == '\0') {
			if (_verboseFlag) {
				int lineNo = GetLineNo();
				_tokenWatcher.FeedToken(new Token(TokenType::Escape, _lineNoTop, lineNo, _segment));
			}
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		} else if (ch == '\n') {
			if (_verboseFlag) {
				int lineNo = GetLineNo();
				_segment.push_back(ch);
				_tokenWatcher.FeedToken(new Token(TokenType::Escape, _lineNoTop, lineNo, _segment));
			}
			_stat = Stat::Start;
		} else if (String::IsWhite(ch)) {
			if (_verboseFlag) {
				_segment.push_back(ch);
			}
		} else {
			IssueError(ErrorType::SyntaxError, "invalid escape character");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::Colon: {
		if (ch == ':') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::ColonColon, _lineNoTop, lineNo));
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		} else if (ch == '*') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::ColonAsterisk, _lineNoTop, lineNo));
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		} else if (ch == '&') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::ColonAnd, _lineNoTop, lineNo));
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		} else {
			int lineNo = GetLineNo();
			const TokenType *pTokenType = GetTokenStack().back()->IsSuffixToken()?
									&TokenType::ColonAfterSuffix : &TokenType::Colon;
			_tokenWatcher.FeedToken(new Token(*pTokenType, _lineNoTop, lineNo));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Error: {
		GetTokenStack().Initialize();
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
			int lineNo = GetLineNo();
			if (_verboseFlag && !_segment.empty()) {
				_tokenWatcher.FeedToken(new Token(TokenType::Space, _lineNoTop, lineNo, _segment));
			}
			_tokenWatcher.FeedToken(new Token(TokenType::LBlockParam, _lineNoTop, lineNo, new ExprLink()));
			if (Error::IsIssued()) {
				_stat = Stat::Error;
			} else {
				_blockParamFlag = true;
				_stat = Stat::Start;
			}
		} else if (ch == '\n' || String::IsWhite(ch)) {
			if (_verboseFlag) _segment.push_back(ch);
		} else {
			int lineNo = GetLineNo();
			if (_verboseFlag && !_segment.empty()) {
				_tokenWatcher.FeedToken(new Token(TokenType::Space, _lineNoTop, lineNo, _segment));
			}
			Gurax_PushbackEx(ch);
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::NumberPre: {
		if (ch == 'x' || ch == 'X') {
			_segment.push_back(ch);
			_stat = Stat::NumberHex;
		} else if (ch == 'b' || ch == 'B') {
			_segment.push_back(ch);
			_stat = Stat::NumberBin;
		} else if(String::IsOctDigit(ch)) {
			_segment.push_back(ch);
			_stat = Stat::NumberOct;
		} else if (ch == '_') {
			_stat = Stat::NumberOct;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Number;
		}
		break;
	}
	case Stat::NumberHex: {
		if (String::IsHexDigit(ch)) {
			_segment.push_back(ch);
		} else if (ch == '_') {
			_stat = Stat::NumberHexUBar;
		} else if (_segment.size() <= 2) {
			IssueError(ErrorType::SyntaxError, "wrong format of hexadecimal number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Number, _lineNoTop, lineNo, _segment));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberHexUBar: {
		if (String::IsHexDigit(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::NumberHex;
		} else if (ch == '_') {
			// nothing to do
		} else {
			IssueError(ErrorType::SyntaxError, "wrong format of hexadecimal number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberOct: {
		if (String::IsOctDigit(ch)) {
			_segment.push_back(ch);
		} else if (ch == '_') {
			_stat = Stat::NumberOctUBar;
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Number, _lineNoTop, lineNo, _segment));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberOctUBar: {
		if (String::IsOctDigit(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::NumberOct;
		} else if (ch == '_') {
			// nothing to do
		} else {
			IssueError(ErrorType::SyntaxError, "wrong format of octal number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberBin: {
		if (String::IsBinDigit(ch)) {
			_segment.push_back(ch);
		} else if (ch == '_') {
			_stat = Stat::NumberBinUBar;
		} else if (_segment.size() <= 2) {
			IssueError(ErrorType::SyntaxError, "wrong format of binary number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Number, _lineNoTop, lineNo, _segment));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberBinUBar: {
		if (String::IsBinDigit(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::NumberBin;
		} else if (ch == '_') {
			// nothing to do
		} else {
			IssueError(ErrorType::SyntaxError, "wrong format of binary number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::Number: {
		if (String::IsDigit(ch)) {
			_segment.push_back(ch);
		} else if (ch == '_') {
			_stat = Stat::NumberUBar;
		} else if (ch == '.') {
			size_t pos = _segment.find('.');
			if (pos == _segment.length() - 1) {
				int lineNo = GetLineNo();
				_segment.resize(pos);
				_tokenWatcher.FeedToken(new Token(TokenType::Number, _lineNoTop, lineNo, _segment));
				if (!Error::IsIssued()) {
					_tokenWatcher.FeedToken(new Token(TokenType::Seq, _lineNoTop, lineNo));
				}
				_stat = Error::IsIssued()? Stat::Error : Stat::Start;
			} else if (pos == String::npos) {
				_segment.push_back(ch);
			} else {
				IssueError(ErrorType::SyntaxError, "period has already been scanned");
				_stat = Stat::Error;
			}
		} else if (ch == 'e' || ch == 'E') {
			_segment.push_back(ch);
			_stat = Stat::NumberExpAfterE;
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Number, _lineNoTop, lineNo, _segment));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberUBar: {
		if (String::IsDigit(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::Number;
		} else if (ch == '_') {
			// nothing to do
		} else {
			IssueError(ErrorType::SyntaxError, "wrong format of number");
			Gurax_PushbackEx(ch);
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberAfterPeriod: {
		if (ch == '.') {
			if (GetTokenStack().back()->IsType(TokenType::Quote)) {
				int lineNo = GetLineNo();
				_segment.push_back(ch);
				_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
			} else {
				int lineNo = GetLineNo();
				_tokenWatcher.FeedToken(new Token(TokenType::Seq, _lineNoTop, lineNo));
			}
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		} else if (String::IsDigit(ch)) {
			_segment.push_back(ch);
			_stat = Stat::Number;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Period, _lineNoTop, lineNo));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberExpAfterE: {
		if (String::IsDigit(ch)) {
			_segment.push_back(ch);
			_stat = Stat::NumberExp;
		} else if (ch == '+' || ch == '-') {
			_segment.push_back(ch);
			_stat = Stat::NumberExpAfterSign;
		} else {
			IssueError(ErrorType::SyntaxError, "wrong exponential expression");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberExpAfterSign: {
		if (String::IsDigit(ch)) {
			_segment.push_back(ch);
			_stat = Stat::NumberExp;
		} else {
			IssueError(ErrorType::SyntaxError, "wrong exponential expression");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::NumberExp: {
		if (String::IsDigit(ch)) {
			_segment.push_back(ch);
		} else if (String::IsSymbolFirst(ch)) {
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::NumberSuffixed;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Number, _lineNoTop, lineNo, _segment));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::NumberSuffixed: {
		if (String::IsSymbolFollower(ch)) {
			_suffix.push_back(ch);
		} else {
			int lineNo = GetLineNo();
			if (_verboseFlag) {
				_tokenWatcher.FeedToken(new Token(TokenType::NumberSuffixed, _lineNoTop, lineNo,
												_segment, _suffix, _segment + _suffix));
			} else {
				_tokenWatcher.FeedToken(new Token(TokenType::NumberSuffixed, _lineNoTop, lineNo,
												_segment, _suffix));
			}
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::Symbol: {
		if (String::IsSymbolFollower(ch)) {
			_segment.push_back(ch);
		} else if (ch == '!') {
			_stat = Stat::SymbolExclamation;
		} else if (ch == '"' || ch == '\'') {
			if (CheckStringPrefix(_stringInfo, _segment)) {
				_stringInfo.chBorder = ch;
				if (_verboseFlag) {
					_source.clear();
					_source += _segment;
					_source.push_back(ch);
				}
				_segment.clear();
				_stat = Stat::StringFirst;
			} else {
				IssueError(ErrorType::SyntaxError, "invalid format of prefix");
				_stat = Stat::Error;
			}
		} else {
			int lineNo = GetLineNo();
			if (GetTokenStack().back()->IsType(TokenType::Quote)) {
				_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
			} else if (_segment == "in") {
				_tokenWatcher.FeedToken(new Token(TokenType::Contains, _lineNoTop, lineNo));
			} else if (_segment == "as") {
				_tokenWatcher.FeedToken(new Token(TokenType::As, _lineNoTop, lineNo));
			} else {
				_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
			}
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::SymbolExclamation: {
		if (ch == '=' || ch == '!') {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::Symbol, _lineNoTop, lineNo, _segment));
			if (Error::IsIssued()) {
				_stat = Stat::Error;
			} else {
				_segment.clear();
				_segment.push_back('!');
				Gurax_PushbackEx(ch);
				_stat = Stat::DoubleChars;
			}
		} else {
			_segment.push_back('!');
			Gurax_PushbackEx(ch);
			_stat = Stat::Symbol;
		}
		break;
	}
	case Stat::CommentLineTop: {
		if (ch == '!') {
			if (_verboseFlag) _segment.push_back(ch);
			_appearShebangFlag = true;
			_stat = Stat::ShebangLine;
		} else {
			_stat = Stat::MagicCommentLine;
			Gurax_PushbackEx(ch);
		}
		break;
	}
	case Stat::MagicCommentLine: {
		if (_magicCommentParser.FeedChar(ch)) {
			const char* encoding = _magicCommentParser.GetEncoding();
			IssueError(ErrorType::DetectEncoding, "%s", encoding);
			Gurax_PushbackEx(ch);
		} else if (ch == '\n' || ch == '\0') {
			int lineNo = GetLineNo();
			if (_verboseFlag) {
				_tokenWatcher.FeedToken(new Token(TokenType::CommentLine, _lineNoTop, lineNo, _segment));
			}
			if (ch == '\n') _tokenWatcher.FeedToken(new Token(TokenType::EndOfLine, _lineNoTop, lineNo));
			_stat = Stat::Start;
		} else {
			if (_verboseFlag) _segment.push_back(ch);
		}
		break;
	}
	case Stat::ShebangLine: {
		if (ch == '\n' || ch == '\0') {
			int lineNo = GetLineNo();
			if (_verboseFlag) {
				_tokenWatcher.FeedToken(new Token(TokenType::CommentLine, _lineNoTop, lineNo, _segment));
			}
			if (ch == '\n') _tokenWatcher.FeedToken(new Token(TokenType::EndOfLine, _lineNoTop, lineNo));
			_stat = Stat::Start;
		} else {
			if (_verboseFlag) _segment.push_back(ch);
		}
		break;
	}
	case Stat::CommentLine: {
		if (ch == '\n' || ch == '\0') {
			int lineNo = GetLineNo();
			if (_verboseFlag) {
				_tokenWatcher.FeedToken(new Token(TokenType::CommentLine, _lineNoTop, lineNo, _segment));
			}
			if (ch == '\n') _tokenWatcher.FeedToken(new Token(TokenType::EndOfLine, _lineNoTop, lineNo));
			_stat = Stat::Start;
		} else {
			if (_verboseFlag) _segment.push_back(ch);
		}
		break;
	}
	case Stat::CommentBlock: {
		if (ch == '*') {
			if (_verboseFlag) _segment.push_back(ch);
			_stat = Stat::CommentBlockEnd;
		} else if (ch == '/') {
			if (_verboseFlag) _segment.push_back(ch);
			_stat = Stat::CommentBlockNest;
		} else {
			if (_verboseFlag) _segment.push_back(ch);
		}
		break;
	}
	case Stat::CommentBlockEnd: {
		if (ch == '/') {
			if (_verboseFlag) _segment.push_back(ch);
			_commentNestLevel--;
			if (_commentNestLevel > 0) {
				_stat = Stat::CommentBlock;
			} else {
				int lineNo = GetLineNo();
				if (_verboseFlag) {
					_tokenWatcher.FeedToken(new Token(TokenType::CommentBlock, _lineNoTop, lineNo, _segment));
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
			if (_verboseFlag) _segment.push_back(ch);
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
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::StringSecond;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::String;
		}
		break;
	}
	case Stat::StringSecond: {
		if (ch == _stringInfo.chBorder) {
			if (_verboseFlag) _source.push_back(ch);
			if (_stringInfo.wiseFlag) {
				_stringInfo.strIndentRef = _strIndent;
				_stat = Stat::MStringWise;
			} else {
				_stat = Stat::MString;
			}
		} else if (String::IsSymbolFirst(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::StringSuffixed;
		} else {
			int lineNo = GetLineNo();
			if (_stringInfo.type == StringType::Binary) {
				RefPtr<BinaryReferable> pBuff(new BinaryReferable(_segment));
				pBuff->GetBinary().SetWritableFlag(false);
				_tokenWatcher.FeedToken(new Token(TokenType::Binary, _lineNoTop, lineNo,
												pBuff.release(), _source));
			} else if (_stringInfo.type == StringType::BinaryWritable) {
				_tokenWatcher.FeedToken(new Token(TokenType::Binary, _lineNoTop, lineNo,
												new BinaryReferable(_segment), _source));
			} else if (_stringInfo.type == StringType::Template) {
				_tokenWatcher.FeedToken(new Token(TokenType::Template, _lineNoTop, lineNo,
												_segment, "", _source));
			} else if (_stringInfo.type == StringType::TmplEmbedded) {
				_tokenWatcher.FeedToken(new Token(TokenType::TmplEmbedded, _lineNoTop, lineNo,
												_segment, "", _source));
			} else {
				_tokenWatcher.FeedToken(new Token(TokenType::String, _lineNoTop, lineNo,
												_segment, "", _source));
			}
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::String: {
		if (ch == _stringInfo.chBorder) {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::StringPost;
		} else if (ch == '\\') {
			if (_verboseFlag) _source.push_back(ch);
			_stringInfo.statRtn = Stat::String;
			_stat = Stat::StringEsc;
		} else if (ch == '\0' || ch == '\n') {
			IssueError(ErrorType::SyntaxError, "string is not terminated correctly");
			_stat = Stat::Error;
		} else {
			if (_verboseFlag) _source.push_back(ch);
			_segment.push_back(ch);
		}
		break;
	}
	case Stat::MStringWise: {
		if (ch == '\n') {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::MStringLineHead;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::MString: {
		if (ch == _stringInfo.chBorder) {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::MStringEndFirst;
		} else if (ch == '\\') {
			if (_verboseFlag) _source.push_back(ch);
			_stringInfo.statRtn = Stat::MString;
			_stat = Stat::StringEsc;
		} else if (ch == '\0') {
			IssueError(ErrorType::SyntaxError, "string is not terminated correctly");
			_stat = Stat::Error;
		} else if (ch == '\n' && _stringInfo.wiseFlag) {
			if (_verboseFlag) _source.push_back(ch);
			_segment.push_back(ch);
			_stat = Stat::MStringLineHead;
		} else {
			if (_verboseFlag) _source.push_back(ch);
			_segment.push_back(ch);
		}
		break;
	}
	case Stat::MStringLineHead: {
		if (String::IsWhite(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			if (_strIndent.size() == _stringInfo.strIndentRef.size()) {
				if (_strIndent != _stringInfo.strIndentRef) {
					_segment += _strIndent;
				}
				_stat = Stat::MString;
			}
		} else {
			_segment += _strIndent;
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::StringEsc: {
		if (_stringInfo.rawFlag) {
			if (_verboseFlag) {
				_source.push_back(ch);
			}
			_segment.push_back('\\');
			_segment.push_back(ch);
			_stat = _stringInfo.statRtn;
		} else {
			if (_verboseFlag) _source.push_back(ch);
			if (ch == '\n') {
				_stat = _stringInfo.statRtn;
			} else if (ch == 'x') {
				_stringInfo.accum = 0x00;
				_stringInfo.cntRest = 2;
				_stat = Stat::StringEscHex;
			} else if (String::IsOctDigit(ch)) {
				_stringInfo.accum = String::ConvOctDigit(ch);
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
				_segment.push_back(String::ToEscaped(ch));
				_stat = _stringInfo.statRtn;
			}
		}
		break;
	}
	case Stat::StringEscHex: {
		if (String::IsHexDigit(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			_stringInfo.accum = (_stringInfo.accum << 4) + String::ConvHexDigit(ch);
			_stringInfo.cntRest--;
			if (_stringInfo.cntRest <= 0) {
				_segment.push_back(static_cast<char>(_stringInfo.accum));
				_stat = _stringInfo.statRtn;
			}
		} else {
			IssueError(ErrorType::SyntaxError, "invalid hex expression in string");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::StringEscOct: {
		if (String::IsOctDigit(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			_stringInfo.accum = (_stringInfo.accum << 3) + String::ConvOctDigit(ch);
			_stringInfo.cntRest--;
			if (_stringInfo.cntRest <= 0) {
				_segment.push_back(static_cast<char>(_stringInfo.accum));
				_stat = _stringInfo.statRtn;
			}
		} else {
			IssueError(ErrorType::SyntaxError, "invalid oct expression in string");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::StringEscUnicode: {
		if (String::IsHexDigit(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			_stringInfo.accum = (_stringInfo.accum << 4) + String::ConvHexDigit(ch);
			_stringInfo.cntRest--;
			if (_stringInfo.cntRest <= 0) {
				_segment.AppendUTF32(_stringInfo.accum);
				_stat = _stringInfo.statRtn;
			}
		} else {
			IssueError(ErrorType::SyntaxError, "invalid Unicode code point in string");
			_stat = Stat::Error;
		}
		break;
	}
	case Stat::StringInCommentBlock: {
		if (ch == _stringInfo.chBorder) {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::CommentBlock;
		} else if (ch == '\\') {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::StringEscInCommentBlock;
		} else {
			if (_verboseFlag) _source.push_back(ch);
		}
		break;
	}
	case Stat::StringEscInCommentBlock: {
		if (_verboseFlag) _source.push_back(ch);
		_stat = Stat::StringInCommentBlock;
		break;
	}
	case Stat::MStringEndFirst: {
		if (ch == _stringInfo.chBorder) {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::MStringEndSecond;
		} else {
			if (_verboseFlag) _source.push_back(_stringInfo.chBorder);
			_segment.push_back(_stringInfo.chBorder);
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::MStringEndSecond: {
		if (ch == _stringInfo.chBorder) {
			if (_verboseFlag) _source.push_back(ch);
			_stat = Stat::StringPost;
		} else {
			if (_verboseFlag) {
				_source.push_back(_stringInfo.chBorder);
				_source.push_back(_stringInfo.chBorder);
			}
			_segment.push_back(_stringInfo.chBorder);
			_segment.push_back(_stringInfo.chBorder);
			Gurax_PushbackEx(ch);
			_stat = Stat::MString;
		}
		break;
	}
	case Stat::StringPost: {
		if (String::IsSymbolFirst(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			_suffix.clear();
			_suffix.push_back(ch);
			_stat = Stat::StringSuffixed;
		} else {
			int lineNo = GetLineNo();
			if (_stringInfo.type == StringType::Binary) {
				RefPtr<BinaryReferable> pBuff(new BinaryReferable(_segment));
				pBuff->GetBinary().SetWritableFlag(false);
				_tokenWatcher.FeedToken(new Token(TokenType::Binary, _lineNoTop, lineNo,
												pBuff.release(), _source));
			} else if (_stringInfo.type == StringType::BinaryWritable) {
				_tokenWatcher.FeedToken(new Token(TokenType::Binary, _lineNoTop, lineNo,
												new BinaryReferable(_segment), _source));
			} else if (_stringInfo.type == StringType::Template) {
				_tokenWatcher.FeedToken(new Token(TokenType::Template, _lineNoTop, lineNo,
												_segment, "", _source));
			} else if (_stringInfo.type == StringType::TmplEmbedded) {
				_tokenWatcher.FeedToken(new Token(TokenType::TmplEmbedded, _lineNoTop, lineNo,
												_segment, "", _source));
			} else {
				_tokenWatcher.FeedToken(new Token(TokenType::String, _lineNoTop, lineNo,
												_segment, "", _source));
			}
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::StringSuffixed: {
		if (String::IsSymbolFollower(ch)) {
			if (_verboseFlag) _source.push_back(ch);
			_suffix.push_back(ch);
		} else if (_stringInfo.type == StringType::Binary) {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::BinarySuffixed, _lineNoTop, lineNo,
											_segment, _suffix, _source));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		} else if (_stringInfo.type == StringType::BinaryWritable) {
			IssueError(ErrorType::SyntaxError, "binary literal can not be specified with suffix");
			_stat = Stat::Error;
		} else if (_stringInfo.type == StringType::Template) {
			IssueError(ErrorType::SyntaxError, "template literal can not be specified with suffix");
			_stat = Stat::Error;
		} else if (_stringInfo.type == StringType::TmplEmbedded) {
			IssueError(ErrorType::SyntaxError, "embedded literal can not be specified with suffix");
			_stat = Stat::Error;
		} else {
			int lineNo = GetLineNo();
			_tokenWatcher.FeedToken(new Token(TokenType::StringSuffixed, _lineNoTop, lineNo,
											_segment, _suffix, _source));
			Gurax_PushbackEx(ch);
			_stat = Error::IsIssued()? Stat::Error : Stat::Start;
		}
		break;
	}
	case Stat::RecoverConsole: {
		if (ch == '\n') {
			_stat = Stat::BOF;
			_lineHeadFlag = true;
			GetTokenStack().Initialize();
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
}

bool Tokenizer::CheckStringPrefix(StringInfo& stringInfo, const String& field)
{
	stringInfo.rawFlag = false;
	stringInfo.wiseFlag = false;
	stringInfo.type = StringType::String;
	for (const char ch : field) {
		if (ch == 'r') {
			if (stringInfo.rawFlag) return false;
			stringInfo.rawFlag = true;
		} else if (ch == 'R') {
			if (stringInfo.rawFlag) return false;
			stringInfo.rawFlag = true;
			stringInfo.wiseFlag = true;
		} else if (ch == 'b') {
			if (stringInfo.type != StringType::String) return false;
			stringInfo.type = StringType::Binary;
		} else if (ch == 'B') {
			if (stringInfo.type != StringType::String) return false;
			stringInfo.type = StringType::BinaryWritable;
		} else if (ch == 't') {
			if (stringInfo.type != StringType::String) return false;
			stringInfo.type = StringType::Template;
		} else if (ch == 'e') {
			if (stringInfo.type != StringType::String) return false;
			stringInfo.type = StringType::TmplEmbedded;
		} else {
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Tokenizer::MagicCommentParser
//-----------------------------------------------------------------------------
bool Tokenizer::MagicCommentParser::FeedChar(char ch)
{
	bool rtn = false;
	switch (_stat) {
	case Stat::Idle: {
		// nothing to do
		break;
	}
	case Stat::Start: {
		if (String::IsAlpha(ch)) {
			_segment += ch;
		} else if (ch == ':' || ch == '=') {
			if (_segment.size() >= 6 && ::strcmp(_segment.c_str() + _segment.size() - 6, "coding") == 0) {
				_stat = Stat::SkipSpace;
			} else {
				_segment.clear();
			}
		} else {
			_segment.clear();
		}
		break;
	}
	case Stat::SkipSpace: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.' || ch == '-' || ch == '_') {
			_segment.clear();
			_segment += ch;
			_stat = Stat::CodingName;
		} else {
			_stat = Stat::Start;
		}
		break;
	}
	case Stat::CodingName: {
		if (String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.' || ch == '-' || ch == '_') {
			_segment += ch;
		} else {
			rtn = true;
			_stat = Stat::Idle;
		}
		break;
	}
	}
	return rtn;
}

}
