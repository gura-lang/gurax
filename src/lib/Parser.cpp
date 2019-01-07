//==============================================================================
// Parser.cpp
//==============================================================================
#include "stdafx.h"

//#define DBGPARSER(x)
#define DBGPARSER(x) x

namespace Gurax {

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
Parser::Parser(String pathNameSrc) : _pTokenizer(new Tokenizer(*this, std::move(pathNameSrc)))
{
}

void Parser::FeedToken(RefPtr<Token> pToken)
{
	TokenStack& tokenStack = _pTokenizer->GetTokenStack();
	::printf("FeedToken(%s)\n", pToken->GetSymbol());
	for (;;) {
		TokenStack::reverse_iterator ppTokenTop = tokenStack.SeekTerminal(tokenStack.rbegin());
		//::printf("%s  << %s\n",
		//				_tokenStack.ToString().c_str(), token.GetTypeSymbol());
		Token::Precedence prec = Token::LookupPrec(**ppTokenTop, *pToken);
		if ((*ppTokenTop)->IsType(TokenType::Begin) && pToken->IsSeparatorToken()) {
			size_t cntToken = tokenStack.size();
			if (cntToken == 1) {
				// nothing to do
			} else if (cntToken == 2 && tokenStack.back()->IsType(TokenType::Expr)) {
				RefPtr<Token> pTokenPrev = tokenStack.Pop();
				Expr* pExpr = pTokenPrev->GetExpr()->Reference();
#if 0
				if (_enablePreparatorFlag && !pExpr->Prepare(env)) {
					tokenStack.Initialize();
				}
#endif
				if (pToken->IsType(TokenType::Semicolon)) pExpr->SetSilentFlag(true);
				if (!_pExprOwner) {
					Expr::Delete(pExpr);
				} else if (!EmitExpr(*_pExprOwner, _pExprParent, pExpr)) {
					tokenStack.Initialize();
				}
			} else {
				// something's wrong
				IssueError(ErrorType::SyntaxError, pToken, "syntax error (%d)", __LINE__);
				tokenStack.Initialize();
			}
			break;
		} else if (prec == Token::Precedence::LT || prec == Token::Precedence::EQ) {
			Token *pTokenLast = tokenStack.back();
			// concatenation of two sequences of string, binary and embed-string
			if (pTokenLast->IsType(TokenType::String) && pToken->IsType(TokenType::String)) {
				pTokenLast->AppendValue(pToken->GetValueSTL());
			} else if (pTokenLast->IsType(TokenType::Binary) && pToken->IsType(TokenType::Binary)) {
				pTokenLast->AppendValue(pToken->GetValueSTL());
			} else if (pTokenLast->IsType(TokenType::EmbedString) && pToken->IsType(TokenType::EmbedString)) {
				pTokenLast->AppendValue(pToken->GetValueSTL());
			} else {
				tokenStack.push_back(pToken->Reference());
			}
			break;
		} else if (prec == Token::Precedence::GT) {
			TokenStack::reverse_iterator ppTokenLeft;
			TokenStack::reverse_iterator ppTokenRight = ppTokenTop;
			while (1) {
				ppTokenLeft = tokenStack.SeekTerminal(ppTokenRight + 1);
				if (Token::LookupPrec(**ppTokenLeft, **ppTokenRight) == Token::Precedence::LT) {
					ppTokenLeft--;
					break;
				}
				ppTokenRight = ppTokenLeft;
			}
			size_t cntToken = std::distance(tokenStack.rbegin(), ppTokenLeft) + 1;
			bool rtn;
			switch (cntToken) {
			case 1: rtn = ReduceOneToken();		break;
			case 2: rtn = ReduceTwoTokens();	break;
			case 3: rtn = ReduceThreeTokens();	break;
			case 4: rtn = ReduceFourTokens();	break;
			case 5: rtn = ReduceFiveTokens();	break;
			default:
				IssueError(ErrorType::SyntaxError, pToken, "syntax error (%d)", __LINE__);
				rtn = false;
				break;
			}
			if (!rtn) {
				tokenStack.Initialize();
				break;
			}
		} else if (pToken->IsCloseToken()) {
			IssueError(ErrorType::SyntaxError, pToken, "unmatched closing character");
			tokenStack.Initialize();
			break;
		} else {
			IssueError(ErrorType::SyntaxError, pToken, "syntax error (%d)", __LINE__);
			tokenStack.Initialize();
			break;
		}
	}
}

bool Parser::EmitExpr(ExprOwner& exprOwner, const Expr* pExprParent, Expr* pExpr)
{
	return true;
}

bool Parser::ReduceOneToken()
{
	TokenStack& tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s\n", pToken1->GetSymbol());
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken1->GetLineNoBtm();
	Expr* pExpr = nullptr;
	if (pToken1->IsType(TokenType::Number)) {
		DBGPARSER(::printf("Reduce: Expr -> Object(number)\n"));
		pExpr = new Expr_Object(new Object_number(String::ToNumber(pToken1->GetValue())));
		//pExprEx->SetScript(pToken1->GetStringSTL());
	} else if (pToken1->IsType(TokenType::String)) {
		DBGPARSER(::printf("Reduce: Expr -> Object(string)\n"));
		pExpr = new Expr_Object(new Object_string(pToken1->GetValueReferable()->Reference()));
#if 0
	} else if (pToken1->IsType(TokenType::Binary)) {
		DBGPARSER(::printf("Reduce: Expr -> Binary\n"));
		pExpr = new Expr_Value(Value(new Object_binary(env,
						   Binary(pToken1->GetString(), pToken1->GetStringSize()), false)));
	} else if (pToken1->IsType(TokenType::EmbedString)) {
		DBGPARSER(::printf("Reduce: Expr -> EmbedString\n"));
		AutoPtr<Template> pTemplate(new Template());
		bool autoIndentFlag = true;
		bool appendLastEOLFlag = false;
		if (!pTemplate->Parse(env, pToken1->GetString(), nullptr,
							  autoIndentFlag, appendLastEOLFlag)) goto error_done;
		pExpr = new Expr_EmbedString(pTemplate.release(), pToken1->GetStringSTL());
#endif
	} else if (pToken1->IsType(TokenType::Symbol)) {
		DBGPARSER(::printf("Reduce: Expr -> Symbol\n"));
		pExpr = new Expr_Identifier(Symbol::Add(pToken1->GetValue()));
#if 0
	} else if (pToken1->IsType(TokenType::NumberSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr -> Suffixed\n"));
		pExpr = new Expr_Suffixed(pToken1->GetStringSTL(), true, Symbol::Add(pToken1->GetSuffix()));
	} else if (pToken1->IsType(TokenType::StringSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr -> Suffixed\n"));
		pExpr = new Expr_Suffixed(pToken1->GetStringSTL(), false, Symbol::Add(pToken1->GetSuffix()));
	} else if (pToken1->IsType(TokenType::Add)) {
		DBGPARSER(::printf("Reduce: Expr -> '+'\n"));
		pExpr = new Expr_Identifier(Symbol::Plus);
	} else if (pToken1->IsType(TokenType::Mul)) {
		DBGPARSER(::printf("Reduce: Expr -> '*'\n"));
		pExpr = new Expr_Identifier(Symbol::Ast);
	} else if (pToken1->IsType(TokenType::Question)) {
		DBGPARSER(::printf("Reduce: Expr -> '?'\n"));
		pExpr = new Expr_Identifier(Symbol::Quest);
	} else if (pToken1->IsType(TokenType::Sub)) {
		DBGPARSER(::printf("Reduce: Expr -> '-'\n"));
		pExpr = new Expr_Identifier(Symbol::Hyphen);
#endif
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, "unexpected token: %s", pToken1->GetSymbol());
		return false;
	}
	pExpr->SetSourceInfo(_pTokenizer->GetPathNameSrcReferable()->Reference(), lineNoTop, lineNoBtm);
	tokenStack.push_back(new Token(pExpr));
	return true;
}

bool Parser::ReduceTwoTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s\n", pToken1->GetSymbol(), pToken2->GetSymbol());
	return true;
}

bool Parser::ReduceThreeTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken3 = tokenStack.Pop();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s %s\n", pToken1->GetSymbol(), pToken2->GetSymbol(), pToken3->GetSymbol());
	return true;
}

bool Parser::ReduceFourTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken4 = tokenStack.Pop();
	RefPtr<Token> pToken3 = tokenStack.Pop();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s %s %s\n",
			 pToken1->GetSymbol(), pToken2->GetSymbol(), pToken3->GetSymbol(), pToken4->GetSymbol());
	return true;
}

bool Parser::ReduceFiveTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken5 = tokenStack.Pop();
	RefPtr<Token> pToken4 = tokenStack.Pop();
	RefPtr<Token> pToken3 = tokenStack.Pop();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s %s %s %s\n",
			 pToken1->GetSymbol(), pToken2->GetSymbol(), pToken3->GetSymbol(),
			 pToken4->GetSymbol(), pToken5->GetSymbol());
	return true;
}

void Parser::IssueError(const ErrorType& errorType, const Token* pToken, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	Error::IssueV(errorType, _pTokenizer->GetPathNameSrcReferable()->Reference(),
				  pToken->GetLineNoTop(), pToken->GetLineNoBtm(), format, ap);
}

void Parser::IssueError(const ErrorType& errorType, const RefPtr<Token>& pToken, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	Error::IssueV(errorType, _pTokenizer->GetPathNameSrcReferable()->Reference(),
				  pToken->GetLineNoTop(), pToken->GetLineNoBtm(), format, ap);
}

}
