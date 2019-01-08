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
	RefPtr<Expr> pExpr;
	if (pToken1->IsType(TokenType::Number)) {
		DBGPARSER(::printf("Reduce: Expr -> Object(number)\n"));
		pExpr.reset(new Expr_Object(new Object_number(String::ToNumber(pToken1->GetValue()))));
		//pExprEx->SetScript(pToken1->GetStringSTL());
	} else if (pToken1->IsType(TokenType::String)) {
		DBGPARSER(::printf("Reduce: Expr -> Object(string)\n"));
		pExpr.reset(new Expr_Object(new Object_string(pToken1->GetValueReferable()->Reference())));
#if 0
	} else if (pToken1->IsType(TokenType::Binary)) {
		DBGPARSER(::printf("Reduce: Expr -> Binary\n"));
		pExpr.reset(new Expr_Value(Value(new Object_binary(env,
						   Binary(pToken1->GetString(), pToken1->GetStringSize()), false)));
	} else if (pToken1->IsType(TokenType::EmbedString)) {
		DBGPARSER(::printf("Reduce: Expr -> EmbedString\n"));
		AutoPtr<Template> pTemplate(new Template());
		bool autoIndentFlag = true;
		bool appendLastEOLFlag = false;
		if (!pTemplate->Parse(env, pToken1->GetString(), nullptr,
							  autoIndentFlag, appendLastEOLFlag)) goto error_done;
		pExpr.reset(new Expr_EmbedString(pTemplate.release(), pToken1->GetStringSTL()));
#endif
	} else if (pToken1->IsType(TokenType::Symbol)) {
		DBGPARSER(::printf("Reduce: Expr -> Symbol\n"));
		pExpr.reset(new Expr_Identifier(Symbol::Add(pToken1->GetValue())));
	} else if (pToken1->IsType(TokenType::Add)) {
		DBGPARSER(::printf("Reduce: Expr -> '+'\n"));
		pExpr.reset(new Expr_Identifier(Gurax_SymbolMark(Add)));
	} else if (pToken1->IsType(TokenType::Mul)) {
		DBGPARSER(::printf("Reduce: Expr -> '*'\n"));
		pExpr.reset(new Expr_Identifier(Gurax_SymbolMark(Mul)));
	} else if (pToken1->IsType(TokenType::Question)) {
		DBGPARSER(::printf("Reduce: Expr -> '?'\n"));
		pExpr.reset(new Expr_Identifier(Gurax_SymbolMark(Question)));
	} else if (pToken1->IsType(TokenType::Sub)) {
		DBGPARSER(::printf("Reduce: Expr -> '-'\n"));
		pExpr.reset(new Expr_Identifier(Gurax_SymbolMark(Sub)));
#if 0
	} else if (pToken1->IsType(TokenType::NumberSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr -> Suffixed\n"));
		pExpr.reset(new Expr_Suffixed(pToken1->GetStringSTL(), true, Symbol::Add(pToken1->GetSuffix())));
	} else if (pToken1->IsType(TokenType::StringSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr -> Suffixed\n"));
		pExpr.reset(new Expr_Suffixed(pToken1->GetStringSTL(), false, Symbol::Add(pToken1->GetSuffix())));
#endif
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, "unexpected token: %s", pToken1->GetSymbol());
		return false;
	}
	SetSourceInfo(pExpr, lineNoTop, lineNoBtm);
	tokenStack.push_back(new Token(pExpr.release()));
	return true;
}

bool Parser::ReduceTwoTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s\n", pToken1->GetSymbol(), pToken2->GetSymbol());
#if 0
	int lineNoTop = token1.GetLineNo();
	int lineNoBtm = pToken2->GetLineNo();
	if (token1.IsType(TokenType::LParenthesis)) {
		if (pToken2->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr -> '(' ')'\n"));
			Expr_Iterer *pExprIterer =
						dynamic_cast<Expr_Iterer *>(token1.GetExpr());
			if (pExprIterer == nullptr) {
				pExprIterer = new Expr_Iterer();
			}
			pExpr = pExprIterer;
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '(' -> '(' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (token1.IsType(TokenType::LBracket)) {
		if (pToken2->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> '[' ']'\n"));
			Expr_Lister *pExprLister =
						dynamic_cast<Expr_Lister *>(token1.GetExpr());
			if (pExprLister == nullptr) {
				pExprLister = new Expr_Lister();
			}
			pExpr = pExprLister;
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '[' -> '[' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (token1.IsType(TokenType::LBrace)) {
		if (pToken2->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> '{' '}'\n"));
			Expr_Block *pExprBlock =
						dynamic_cast<Expr_Block *>(token1.GetExpr());
			if (pExprBlock == nullptr) {
				pExprBlock = new Expr_Block();
			}
			pExpr = pExprBlock;
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '{' -> '{' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (token1.IsType(TokenType::LBlockParam)) {
		if (pToken2->IsType(TokenType::RBlockParam)) {
			// this is a special case of reducing
			DBGPARSER(::printf("do (Reduce: Expr -> '|' '|') "
					"and then attach the Expr to the preceeding LBrace\n"));
			Expr_Lister *pExprBlockParam = dynamic_cast<Expr_Lister *>(token1.GetExpr());
			if (pExprBlockParam == nullptr) {
				pExprBlockParam = new Expr_Lister();
			}
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			Token &tokenPrev = _tokenStack.Peek(0);
			if (tokenPrev.IsType(TokenType::LBrace)) {
				Expr_Block *pExprBlock =
							dynamic_cast<Expr_Block *>(tokenPrev.GetExpr());
				if (pExprBlock == nullptr) {
					pExprBlock = new Expr_Block();
					tokenPrev.SetExpr(pExprBlock);
				}
				pExprBlock->SetExprOwnerParam(pExprBlockParam->GetExprOwner().Reference());
				Expr::Delete(pExprBlockParam);
			} else {
				Expr::Delete(pExprBlockParam);
				SetError(ERR_SyntaxError, "invalid placement of block parameter");
				goto error_done;
			}
			return true;
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '|' -> '|' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (token1.IsType(TokenType::Expr) && pToken2->IsType(TokenType::Symbol)) {
		// this is a special case of reducing
		DBGPARSER(::printf("Reduce: Expr Expr -> Expr Symbol\n"));
		const Symbol *pSymbol = Symbol::Add(pToken2->GetString());
		pExpr = new Expr_Identifier(pSymbol);
		int lineNoTop = _tokenStack.Peek(0).GetLineNo();
		_tokenStack.pop_back();
		pExpr->SetSourceInfo(_pSourceName->Reference(), lineNoTop, lineNoBtm);
		_tokenStack.push_back(Token(TokenType::Expr, pExpr));
		return true;
	} else if (pToken2->IsType(TokenType::Expr)) {
		if (token1.IsType(TokenType::Quote)) {
			DBGPARSER(::printf("Reduce: Expr -> '`' Expr\n"));
			pExpr = new Expr_Quote(pToken2->GetExpr());
		} else if (token1.IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr -> '+' Expr\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Pos), pToken2->GetExpr());
		} else if (token1.IsType(TokenType::Sub)) {
			DBGPARSER(::printf("Reduce: Expr -> '-' Expr\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Neg), pToken2->GetExpr());
		} else if (token1.IsType(TokenType::Inv)) {
			DBGPARSER(::printf("Reduce: Expr -> '~' Expr\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Inv), pToken2->GetExpr());
		} else if (token1.IsType(TokenType::Not)) {
			DBGPARSER(::printf("Reduce: Expr -> '!' Expr\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Not), pToken2->GetExpr());
		} else if (token1.IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr -> '%%%%' Expr\n"));
			if (pToken2->GetExpr()->IsBlock()) {
				// %{..}
				Expr *pExprCar = new Expr_Identifier(Symbol::Percnt);
				Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
				pExpr = CreateCaller(env, pExprCar, nullptr, pExprBlock, nullptr);
				if (pExpr == nullptr) goto error_done;
			} else {
				pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Mod), pToken2->GetExpr());
			}
		} else if (token1.IsType(TokenType::ModMod)) {
			DBGPARSER(::printf("Reduce: Expr -> '%%%%' Expr\n"));
			if (pToken2->GetExpr()->IsBlock()) {
				// %%{..}
				Expr *pExprCar = new Expr_Identifier(Symbol::PercntPercnt);
				Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
				pExpr = CreateCaller(env, pExprCar, nullptr, pExprBlock, nullptr);
				if (pExpr == nullptr) goto error_done;
			} else {
				SetError_InvalidToken(__LINE__);
				goto error_done;
			}
		} else if (token1.IsType(TokenType::And)) {
			DBGPARSER(::printf("Reduce: Expr -> '&' Expr\n"));
			if (pToken2->GetExpr()->IsBlock()) {
				// &{..}
				Expr *pExprCar = new Expr_Identifier(Symbol::Amp);
				Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
				pExpr = CreateCaller(env, pExprCar, nullptr, pExprBlock, nullptr);
				if (pExpr == nullptr) goto error_done;
			} else {
				pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_And), pToken2->GetExpr());
			}
		} else if (token1.IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr -> '*' Expr\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Mul), pToken2->GetExpr());
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (token1.IsType(TokenType::Expr)) {
		if (pToken2->IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '+'\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_PostPos), token1.GetExpr());
		} else if (pToken2->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '*'\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Each), token1.GetExpr());
		} else if (pToken2->IsType(TokenType::Question)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '?'\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_Question), token1.GetExpr());
		} else if (pToken2->IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '%%'\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_PostMod), token1.GetExpr());
		} else if (pToken2->IsType(TokenType::Seq)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr ..\n"));
			pExpr = new Expr_UnaryOp(env.GetOperator(OPTYPE_SeqInf), token1.GetExpr());
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else {
		SetError_InvalidToken(__LINE__);
		goto error_done;
	}
#endif
	return true;
}

bool Parser::ReduceThreeTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken3 = tokenStack.Pop();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s %s\n", pToken1->GetSymbol(), pToken2->GetSymbol(), pToken3->GetSymbol());
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken3->GetLineNoBtm();
	RefPtr<Expr> pExpr;
	if (pToken1->IsType(TokenType::Expr) && pToken3->IsType(TokenType::Expr)) {
		RefPtr<Expr> pExprLeft = pToken1->GetExpr()->Reference();
		RefPtr<Expr> pExprRight = pToken3->GetExpr()->Reference();
		if (pToken2->IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr + Expr\n"));
			//pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Add), pExprLeft, pExprRight);
#if 0
		} else if (pToken2->IsType(TokenType::Sub)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr - Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Sub), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr * Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Mul), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Div)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr / Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Div), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr %% Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Mod), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::ModMod)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr %%%% Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_ModMod), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Dot)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |.| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Dot), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Cross)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |^| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Cross), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Gear)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |*| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Gear), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Concat)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |+| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Concat), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Difference)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |-| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Difference), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Intersection)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |&| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Intersection), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Union)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr ||| Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Union), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Pow)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr ** Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Pow), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Eq)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr == Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Eq), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Ne)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr != Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Ne), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Lt)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr < Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Lt), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Gt)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr > Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Gt), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Le)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr <= Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Le), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Ge)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr >= Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Ge), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Cmp)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr <=> Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Cmp), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Contains)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr in Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Contains), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Assign)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr = Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, nullptr);
		} else if (pToken2->IsType(TokenType::AssignAdd)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr += Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Add));
		} else if (pToken2->IsType(TokenType::AssignSub)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr -= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Sub));
		} else if (pToken2->IsType(TokenType::AssignMul)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr *= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Mul));
		} else if (pToken2->IsType(TokenType::AssignDiv)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr /= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Div));
		} else if (pToken2->IsType(TokenType::AssignMod)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr %%= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Mod));
		} else if (pToken2->IsType(TokenType::AssignPow)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr **= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Pow));
		} else if (pToken2->IsType(TokenType::AssignOr)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr |= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Or));
		} else if (pToken2->IsType(TokenType::AssignAnd)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr &= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_And));
		} else if (pToken2->IsType(TokenType::AssignXor)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr ^= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Xor));
		} else if (pToken2->IsType(TokenType::AssignShl)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr <<= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Shl));
		} else if (pToken2->IsType(TokenType::AssignShr)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr >>= Expr\n"));
			pExpr = new Expr_Assign(pExprLeft, pExprRight, env.GetOperator(OPTYPE_Shr));
		} else if (pToken2->IsType(TokenType::Pair)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr => Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Pair), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Colon) || pToken2->IsType(TokenType::ColonAfterSuffix)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr : Expr\n"));
			Expr *pExprDst = pExprLeft;
			if (pExprDst->IsUnaryOpSuffix()) {
				pExprDst = dynamic_cast<Expr_UnaryOp *>(pExprDst)->GetChild();
			}
			if (pExprDst->IsIndexer()) {
				pExprDst = dynamic_cast<Expr_Indexer *>(pExprDst)->GetCar();
			}
			if (pExprRight->IsIdentifier()) {
				const Symbol *pSymbol = dynamic_cast<Expr_Identifier *>(pExprRight)->GetSymbol();
				bool optAttrFlag = false;
				SymbolList *pAttrFront = nullptr;
				if (pExprDst->IsIdentifier()) {
					Expr_Identifier *pExprIdentifier =
									dynamic_cast<Expr_Identifier *>(pExprDst);
					optAttrFlag = pExprIdentifier->AddAttr(pSymbol);
					pAttrFront = &pExprIdentifier->GetAttrFront();
				} else if (pExprDst->IsCaller()) {
					Expr_Caller *pExprCaller = dynamic_cast<Expr_Caller *>(pExprDst);
					Expr_Caller *pExprTrailer = pExprCaller->GetLastTrailer();
					optAttrFlag = pExprTrailer->AddAttr(pSymbol);
					pAttrFront = &pExprTrailer->GetAttrFront();
				} else {
					SetError_InvalidToken(__LINE__);
					goto error_done;
				}
				if (optAttrFlag && pAttrFront->empty()) pAttrFront->push_back(pSymbol);
				pExpr = pExprLeft;
				Expr::Delete(pExprRight);
			} else if (pExprRight->IsMember()) {
				Expr_Member *pExprMember = dynamic_cast<Expr_Member *>(pExprRight);
				SymbolList *pAttrFront = nullptr;
				if (pExprDst->IsIdentifier()) {
					Expr_Identifier *pExprIdentifierDst =
									dynamic_cast<Expr_Identifier *>(pExprDst);
					pAttrFront = &pExprIdentifierDst->GetAttrFront();
					const Expr_Identifier *pExprIdentifier = pExprMember->GetSelector();
					pExprIdentifierDst->AddAttrs(pExprIdentifier->GetAttrs());
					pExprIdentifierDst->AddAttrsOpt(pExprIdentifier->GetAttrsOpt());
				} else if (pExprDst->IsCaller()) {
					Expr_Caller *pExprCaller = dynamic_cast<Expr_Caller *>(pExprDst);
					Expr_Caller *pExprTrailer = pExprCaller->GetLastTrailer();
					pAttrFront = &pExprTrailer->GetAttrFront();
					const Expr_Identifier *pExprIdentifier = pExprMember->GetSelector();
					pExprTrailer->AddAttrs(pExprIdentifier->GetAttrs());
					pExprTrailer->AddAttrsOpt(pExprIdentifier->GetAttrsOpt());
				} else {
					SetError_InvalidToken(__LINE__);
					goto error_done;
				}
				if (!pAttrFront->empty()) {
					sig.SetError(ERR_SyntaxError,
							"value type must be specified as a first attribute");
					goto error_done;
				}
				if (!pAttrFront->AddFromExpr(pExprRight)) {
					sig.SetError(ERR_SyntaxError, "invalid declaration of value type");
					goto error_done;
				}
				pExpr = pExprLeft;
				Expr::Delete(pExprRight);
			} else if (pExprRight->IsLister()) {
				ExprList &exprList =
							dynamic_cast<Expr_Lister *>(pExprRight)->GetExprOwner();
				if (pExprDst->IsIdentifier()) {
					sig.SetError(ERR_TypeError,
									"identifiers cannot declare optional attributes");
					goto error_done;
				} else if (pExprDst->IsCaller()) {
					Expr_Caller *pExprCaller = dynamic_cast<Expr_Caller *>(pExprDst);
					pExprCaller = pExprCaller->GetLastTrailer();
					foreach (ExprList, ppExpr, exprList) {
						Expr *pExpr = *ppExpr;
						if (!pExpr->IsIdentifier()) {
							SetError_InvalidToken(__LINE__);
							goto error_done;
						}
						const Symbol *pSymbol =
								dynamic_cast<Expr_Identifier *>(pExpr)->GetSymbol();
						pExprCaller->AddAttrOpt(pSymbol);
					}
				} else {
					SetError_InvalidToken(__LINE__);
					goto error_done;
				}
				pExpr = pExprLeft;
				Expr::Delete(pExprRight);
			} else {
				SetError_InvalidToken(__LINE__);
				goto error_done;
			}
		} else if (pToken2->IsType(TokenType::Period)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr . Expr\n"));
			if (!pExprRight->IsIdentifier()) {
				SetError_InvalidToken(__LINE__);
				goto error_done;
			}
			pExpr = new Expr_Member(pExprLeft, dynamic_cast<Expr_Identifier *>(pExprRight),
									Expr_Member::MODE_Normal);
		} else if (pToken2->IsType(TokenType::ColonColon)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr :: Expr\n"));
			if (!pExprRight->IsIdentifier()) {
				SetError_InvalidToken(__LINE__);
				goto error_done;
			}
			pExpr = new Expr_Member(pExprLeft, dynamic_cast<Expr_Identifier *>(pExprRight),
									Expr_Member::MODE_MapToList);
		} else if (pToken2->IsType(TokenType::ColonAsterisk)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr :* Expr\n"));
			if (!pExprRight->IsIdentifier()) {
				SetError_InvalidToken(__LINE__);
				goto error_done;
			}
			pExpr = new Expr_Member(pExprLeft, dynamic_cast<Expr_Identifier *>(pExprRight),
									Expr_Member::MODE_MapToIter);
		} else if (pToken2->IsType(TokenType::ColonAnd)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr :& Expr\n"));
			if (!pExprRight->IsIdentifier()) {
				SetError_InvalidToken(__LINE__);
				goto error_done;
			}
			pExpr = new Expr_Member(pExprLeft, dynamic_cast<Expr_Identifier *>(pExprRight),
									Expr_Member::MODE_MapAlong);
		} else if (pToken2->IsType(TokenType::OrOr)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr || Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_OrOr), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::AndAnd)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr && Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_AndAnd), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Or)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr | Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Or), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::And)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr & Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_And), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Xor)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr ^ Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Xor), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Shl)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr << Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Shl), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Shr)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr >> Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Shr), pExprLeft, pExprRight);
		} else if (pToken2->IsType(TokenType::Seq)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr .. Expr\n"));
			pExpr = new Expr_BinaryOp(env.GetOperator(OPTYPE_Seq), pExprLeft, pExprRight);
#endif
		} else {
			IssueError(ErrorType::SyntaxError, pToken2,
					   "unexpected token for binary operator: %s", pToken2->GetSymbol());
			return false;
		}
	}
#if 0
	if (pToken1->IsType(TokenType::LParenthesis) && pToken2->IsType(TokenType::Expr)) {
		Expr_Iterer *pExprIterer = dynamic_cast<Expr_Iterer *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr -> '(' Expr ')'\n"));
			if (pExprIterer == nullptr) {
				pExpr = pToken2->GetExpr();	// treat expr as non-list
			} else {
				if (!EmitExpr(pExprIterer->GetExprOwner(), pExprIterer, pToken2->GetExpr())) return false;
				pExpr = pExprIterer;
			}
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '(' -> '(' Expr ','\n"));
			if (pExprIterer == nullptr) {
				pExprIterer = new Expr_Iterer();
				pToken1->SetExpr(pExprIterer);
			}
			if (!EmitExpr(pExprIterer->GetExprOwner(), pExprIterer, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::LBracket) && pToken2->IsType(TokenType::Expr)) {
		Expr_Lister *pExprLister = dynamic_cast<Expr_Lister *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> '[' Expr ']'\n"));
			if (pExprLister == nullptr) {
				pExprLister = new Expr_Lister();
			}
			if (!EmitExpr(pExprLister->GetExprOwner(), pExprLister, pToken2->GetExpr())) return false;
			pExpr = pExprLister;
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '[' -> '[' Expr ','\n"));
			if (pExprLister == nullptr) {
				pExprLister = new Expr_Lister();
				pToken1->SetExpr(pExprLister);
			}
			if (!EmitExpr(pExprLister->GetExprOwner(), pExprLister, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LParenthesis)) {
		if (pToken3->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '(' ')'\n"));
			Expr_Lister *pExprLister = dynamic_cast<Expr_Lister *>(pToken2->GetExpr());
			if (pExprLister == nullptr) {
				pExprLister = new Expr_Lister();
			}
			Expr_Caller *pExprCaller =
				CreateCaller(env, pToken1->GetExpr(), pExprLister, nullptr, nullptr);
			if (pExprCaller == nullptr) goto error_done;
			pExpr = pExprCaller;
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: Expr '(' -> Expr '(' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LBrace)) {
		if (pToken3->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '{' '}'\n"));
			Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
			if (pToken1->GetExpr()->IsCaller()) {
				Expr_Caller *pExprCaller = dynamic_cast<Expr_Caller *>(pToken1->GetExpr());
				if (pExprBlock == nullptr) {
					pExprBlock = new Expr_Block();
				}
				pExprCaller->GetLastTrailer()->SetBlock(pExprBlock);
				pExpr = pExprCaller;
			} else {
				if (pExprBlock == nullptr) {
					pExprBlock = new Expr_Block();
				}
				Expr_Caller *pExprCaller =
					CreateCaller(env, pToken1->GetExpr(), nullptr, pExprBlock, nullptr);
				if (pExprCaller == nullptr) goto error_done;
				pExpr = pExprCaller;
			}
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: Expr '{' -> Expr '{' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LBracket)) {
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '[' ']'\n"));
			Expr *pExprTgt = pToken1->GetExpr();
			Expr_Lister *pExprLister = dynamic_cast<Expr_Lister *>(pToken2->GetExpr());
			if (pExprLister == nullptr) {
				pExprLister = new Expr_Lister();
			}
			pExpr = new Expr_Indexer(pExprTgt, pExprLister);
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: Expr '[' -> Expr '[' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::LBrace) && pToken2->IsType(TokenType::Expr)) {
		Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> '{' Expr '}'\n"));
			if (pExprBlock == nullptr) {
				pExprBlock = new Expr_Block();
			}
			if (!EmitExpr(pExprBlock->GetExprOwner(), pExprBlock, pToken2->GetExpr())) return false;
			pExpr = pExprBlock;
		} else if (pToken3->IsType(TokenType::Comma) ||
					pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '{' -> '{' Expr ','\n"));
			if (pExprBlock == nullptr) {
				pExprBlock = new Expr_Block();
				pToken1->SetExpr(pExprBlock);
			}
			if (!EmitExpr(pExprBlock->GetExprOwner(), pExprBlock, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::LBlockParam) && pToken2->IsType(TokenType::Expr)) {
		Expr_Lister *pExprBlockParam = dynamic_cast<Expr_Lister *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RBlockParam)) {
			// this is a special case of reducing
			DBGPARSER(::printf("do (Reduce: Expr -> '|' Expr '|') "
					"and then attach the Expr to the preceeding LBrace\n"));
			if (pExprBlockParam == nullptr) {
				pExprBlockParam = new Expr_Lister();
			}
			if (!EmitExpr(pExprBlockParam->GetExprOwner(), pExprBlockParam, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			Token &tokenPrev = _tokenStack.Peek(0);
			if (tokenPrev.IsType(TokenType::LBrace)) {
				Expr_Block *pExprBlock =
							dynamic_cast<Expr_Block *>(tokenPrev.GetExpr());
				if (pExprBlock == nullptr) {
					pExprBlock = new Expr_Block();
					tokenPrev.SetExpr(pExprBlock);
				}
				pExprBlock->SetExprOwnerParam(pExprBlockParam->GetExprOwner().Reference());
				Expr::Delete(pExprBlockParam);
			} else {
				Expr::Delete(pExprBlockParam);
				SetError(ERR_SyntaxError, "invalid placement of block parameter");
				goto error_done;
			}
			return true;
		} else if (pToken3->IsType(TokenType::Comma) ||
					pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '|' -> '|' Expr ','\n"));
			if (pExprBlockParam == nullptr) {
				pExprBlockParam = new Expr_Lister();
				pToken1->SetExpr(pExprBlockParam);
			}
			if (!EmitExpr(pExprBlockParam->GetExprOwner(), pExprBlockParam, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			SetError_InvalidToken(__LINE__);
			goto error_done;
		}
	} else {
		SetError_InvalidToken(__LINE__);
		goto error_done;
	}
#endif
	SetSourceInfo(pExpr, lineNoTop, lineNoBtm);
	tokenStack.push_back(new Token(pExpr.release()));
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
