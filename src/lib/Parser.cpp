//==============================================================================
// Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
Parser::Parser(String pathNameSrc) : _pTokenizer(new Tokenizer(*this, std::move(pathNameSrc)))
{
}

void Parser::FeedToken(UniquePtr<Token> pToken)
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	//::printf("FeedToken(%s)\n", token.GetSymbol());
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
				UniquePtr<Token> pToken(tokenStack.Pop());
				Expr* pExpr = pToken->GetExpr()->Reference();
#if 0
				if (_enablePreparatorFlag && !pExpr->Prepare(env)) {
					tokenStack.Initialize();
				}
#endif
				if (pToken->IsType(TokenType::Semicolon)) pExpr->SetSilentFlag(true);
				if (_pExprOwner == nullptr) {
					Expr::Delete(pExpr);
				} else if (!EmitExpr(*_pExprOwner, _pExprParent, pExpr)) {
					tokenStack.Initialize();
				}
			} else {
				// something's wrong
				IssueError(ErrorType::SyntaxError, "syntax error (%d)", __LINE__);
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
			if (cntToken == 1) {
				rtn = ReduceOneToken();
			} else if (cntToken == 2) {
				rtn = ReduceTwoTokens();
			} else if (cntToken == 3) {
				rtn = ReduceThreeTokens();
			} else if (cntToken == 4) {
				rtn = ReduceFourTokens();
			} else if (cntToken == 5) {
				rtn = ReduceFiveTokens();
			} else {
				IssueError(ErrorType::SyntaxError, "syntax error (%d)", __LINE__);
				rtn = false;
			}
			if (!rtn) {
				tokenStack.Initialize();
				break;
			}
		} else if (pToken->IsCloseToken()) {
			IssueError(ErrorType::SyntaxError, "unmatched closing character");
			tokenStack.Initialize();
			break;
		} else {
			IssueError(ErrorType::SyntaxError, "syntax error (%d)", __LINE__);
			tokenStack.Initialize();
			break;
		}
	}
	//return env.IsNoSignalled();
}

bool Parser::EmitExpr(ExprOwner& exprOwner, const Expr* pExprParent, Expr* pExpr)
{
	return true;
}

bool Parser::ReduceOneToken()
{
	return true;
}

bool Parser::ReduceTwoTokens()
{
	return true;
}

bool Parser::ReduceThreeTokens()
{
	return true;
}

bool Parser::ReduceFourTokens()
{
	return true;
}

bool Parser::ReduceFiveTokens()
{
	return true;
}

void Parser::IssueError(const ErrorType& errorType, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	Error::IssueV(errorType, _pTokenizer->GetPathNameSrcShared(), _pTokenizer->GetLineNo(), format, ap);
}

}
