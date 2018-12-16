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
#if 0
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
			} else if (cntToken == 2 && tokenStack[1]->IsType(TokenType::Expr)) {
				Expr *pExpr = tokenStack[1]->GetExpr();
				if (_enablePreparatorFlag && !pExpr->Prepare(env)) {
					InitStack();
				} else {
					tokenStack.pop_back();
					if (token.IsType(TOKEN_Semicolon)) pExpr->SetSilentFlag(true);
					if (_pExprOwner == nullptr) {
						Expr::Delete(pExpr);
					} else if (!EmitExpr(*_pExprOwner, _pExprParent, pExpr)) {
						InitStack();
					}
				}
			} else {
				// something's wrong
				SetError_InvalidToken(__LINE__);
				InitStack();
			}
			break;
		} else if (prec == Token::PREC_LT || prec == Token::PREC_EQ) {
			Token &tokenLast = tokenStack.back();
			// concatenation of two sequences of string, binary and embed-string
			if (tokenLast.IsType(TOKEN_String) && token.IsType(TOKEN_String)) {
				tokenLast.AddString(token.GetStringSTL());
			} else if (tokenLast.IsType(TOKEN_Binary) && token.IsType(TOKEN_Binary)) {
				tokenLast.AddString(token.GetStringSTL());
			} else if (tokenLast.IsType(TOKEN_EmbedString) && token.IsType(TOKEN_EmbedString)) {
				tokenLast.AddString(token.GetStringSTL());
			} else {
				tokenStack.push_back(token);
			}
			break;
		} else if (prec == Token::PREC_GT) {
			TokenStack::reverse_iterator pTokenLeft;
			TokenStack::reverse_iterator pTokenRight = pTokenTop;
			while (1) {
				pTokenLeft = tokenStack.SeekTerminal(pTokenRight + 1);
				if (Token::LookupPrec(*pTokenLeft, *pTokenRight) == Token::PREC_LT) {
					pTokenLeft--;
					break;
				}
				pTokenRight = pTokenLeft;
			}
			size_t cntToken = std::distance(tokenStack.rbegin(), pTokenLeft) + 1;
			bool rtn;
			if (cntToken == 1) {
				rtn = ReduceOneToken(env);
			} else if (cntToken == 2) {
				rtn = ReduceTwoTokens(env);
			} else if (cntToken == 3) {
				rtn = ReduceThreeTokens(env);
			} else if (cntToken == 4) {
				rtn = ReduceFourTokens(env);
			} else if (cntToken == 5) {
				rtn = ReduceFiveTokens(env);
			} else {
				SetError_InvalidToken(__LINE__);
				rtn = false;
			}
			if (!rtn) {
				InitStack();
				break;
			}
		} else if (token.IsCloseToken()) {
			SetError(ERR_SyntaxError, "unmatched closing character");
			InitStack();
			break;
		} else {
			SetError_InvalidToken(__LINE__);
			InitStack();
			break;
		}
	}
	//return env.IsNoSignalled();
#endif
}

}
