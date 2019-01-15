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
				tokenStack.Push(pToken->Reference());
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
	RefPtr<Token> pToken = tokenStack.Pop();
	::printf("%s\n", pToken->GetSymbol());
	int lineNoTop = pToken->GetLineNoTop();
	int lineNoBtm = pToken->GetLineNoBtm();
	RefPtr<Expr> pExprGen;
	if (pToken->IsType(TokenType::Number)) {
		DBGPARSER(::printf("Reduce: Expr(Object) -> Object(number)\n"));
		pExprGen.reset(new Expr_Object(new Object_number(String::ToNumber(pToken->GetValue()))));
		//pExprEx->SetScript(pToken->GetStringSTL());
	} else if (pToken->IsType(TokenType::String)) {
		DBGPARSER(::printf("Reduce: Expr(Object) -> Object(string)\n"));
		pExprGen.reset(new Expr_Object(new Object_string(pToken->GetValueReferable()->Reference())));
#if 0
	} else if (pToken->IsType(TokenType::Binary)) {
		DBGPARSER(::printf("Reduce: Expr(Object) -> Binary\n"));
		pExprGen.reset(new Expr_Value(Value(new Object_binary(env,
						   Binary(pToken->GetString(), pToken->GetStringSize()), false)));
	} else if (pToken->IsType(TokenType::EmbedString)) {
		DBGPARSER(::printf("Reduce: Expr -> EmbedString\n"));
		AutoPtr<Template> pTemplate(new Template());
		bool autoIndentFlag = true;
		bool appendLastEOLFlag = false;
		if (!pTemplate->Parse(env, pToken->GetString(), nullptr,
							  autoIndentFlag, appendLastEOLFlag)) goto error_done;
		pExprGen.reset(new Expr_EmbedString(pTemplate.release(), pToken->GetStringSTL()));
#endif
	} else if (pToken->IsType(TokenType::Symbol)) {
		DBGPARSER(::printf("Reduce: Expr(Identifer) -> Symbol\n"));
		pExprGen.reset(new Expr_Identifier(Symbol::Add(pToken->GetValue())));
	} else if (pToken->IsType(TokenType::Add)) {
		DBGPARSER(::printf("Reduce: Expr(Identifer) -> '+'\n"));
		pExprGen.reset(new Expr_Identifier(Gurax_SymbolMark(Add)));
	} else if (pToken->IsType(TokenType::Mul)) {
		DBGPARSER(::printf("Reduce: Expr(Identifer) -> '*'\n"));
		pExprGen.reset(new Expr_Identifier(Gurax_SymbolMark(Mul)));
	} else if (pToken->IsType(TokenType::Question)) {
		DBGPARSER(::printf("Reduce: Expr(Identifer) -> '?'\n"));
		pExprGen.reset(new Expr_Identifier(Gurax_SymbolMark(Question)));
	} else if (pToken->IsType(TokenType::Sub)) {
		DBGPARSER(::printf("Reduce: Expr(Identifer) -> '-'\n"));
		pExprGen.reset(new Expr_Identifier(Gurax_SymbolMark(Sub)));
	} else if (pToken->IsType(TokenType::NumberSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr(Suffixed) -> NumberSuffixed\n"));
		pExprGen.reset(new Expr_Suffixed(pToken->GetValueReferable()->Reference(),
									  Symbol::Add(pToken->GetSuffix()), true));
	} else if (pToken->IsType(TokenType::StringSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr(Suffixed) -> SuffixedSuffixed\n"));
		pExprGen.reset(new Expr_Suffixed(pToken->GetValueReferable()->Reference(),
									  Symbol::Add(pToken->GetSuffix()), false));
	} else {
		IssueError(ErrorType::SyntaxError, pToken, "unexpected token: %s", pToken->GetSymbol());
		return false;
	}
	SetSourceInfo(pExprGen, lineNoTop, lineNoBtm);
	tokenStack.Push(new Token(pExprGen.release()));
	return true;
}

bool Parser::ReduceTwoTokens()
{
	TokenStack &tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken2 = tokenStack.Pop();
	RefPtr<Token> pToken1 = tokenStack.Pop();
	::printf("%s %s\n", pToken1->GetSymbol(), pToken2->GetSymbol());
	RefPtr<Expr> pExprGen;
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken2->GetLineNoBtm();
	if (pToken1->IsType(TokenType::LParenthesis)) {
		if (pToken2->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Iterer) -> '(' ')'\n"));
			pExprGen.reset(Expr::Reference(pToken1->GetExpr()));
			if (!pExprGen) pExprGen.reset(new Expr_Iterer());
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '(' -> '(' EndOfLine\n"));
			tokenStack.Push(pToken1.release());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBracket)) {
		if (pToken2->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr(Lister) -> '[' ']'\n"));
			pExprGen.reset(Expr::Reference(pToken1->GetExpr()));
			if (!pExprGen) pExprGen.reset(new Expr_Lister());
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '[' -> '[' EndOfLine\n"));
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBrace)) {
		if (pToken2->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> '{' '}'\n"));
			pExprGen.reset(Expr::Reference(pToken1->GetExpr()));
			if (!pExprGen) pExprGen.reset(new Expr_Block());
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '{' -> '{' EndOfLine\n"));
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
#if 0
	} else if (pToken1->IsType(TokenType::LBlockParam)) {
		if (pToken2->IsType(TokenType::RBlockParam)) {
			// this is a special case of reducing
			DBGPARSER(::printf("do (Reduce: Expr -> '|' '|') "
					"and then attach the Expr to the preceeding LBrace\n"));
			Expr_Lister *pExprBlockParam = dynamic_cast<Expr_Lister *>(pToken1->GetExpr());
			if (!pExprBlockParam) {
				pExprBlockParam = new Expr_Lister();
			}
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			Token &tokenPrev = _tokenStack.Peek(0);
			if (tokenPrev.IsType(TokenType::LBrace)) {
				Expr_Block *pExprBlock =
							dynamic_cast<Expr_Block *>(tokenPrev.GetExpr());
				if (!pExprBlock) {
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
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Symbol)) {
		// this is a special case of reducing
		DBGPARSER(::printf("Reduce: Expr Expr -> Expr Symbol\n"));
		const Symbol *pSymbol = Symbol::Add(pToken2->GetString());
		pExprGen = new Expr_Identifier(pSymbol);
		int lineNoTop = _tokenStack.Peek(0).GetLineNo();
		_tokenStack.pop_back();
		pExprGen->SetSourceInfo(_pSourceName->Reference(), lineNoTop, lineNoBtm);
		_tokenStack.Push(Token(TokenType::Expr, pExprGen));
		return true;
#endif
	} else if (pToken2->IsType(TokenType::Expr)) {
		if (pToken1->IsType(TokenType::Inv)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '~' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Inv));
		} else if (pToken1->IsType(TokenType::Sub)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '-' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Neg));
		} else if (pToken1->IsType(TokenType::Not)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '!' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Not));
		} else if (pToken1->IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '+' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Pos));
		} else if (pToken1->IsType(TokenType::Quote)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '`' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Quote));
#if 0
		} else if (pToken1->IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '%%%%' Expr\n"));
			if (pToken2->GetExpr()->IsBlock()) {
				// %{..}
				Expr *pExprCar = new Expr_Identifier(Symbol::Percnt);
				Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
				pExprGen = CreateCaller(env, pExprCar, nullptr, pExprBlock, nullptr);
				if (!pExprGen) goto error_done;
			} else {
				pExprGen = new Expr_UnaryOp(env.GetOperator(OPTYPE_Mod), pToken2->GetExpr());
			}
		} else if (pToken1->IsType(TokenType::ModMod)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '%%%%' Expr\n"));
			if (pToken2->GetExpr()->IsBlock()) {
				// %%{..}
				Expr *pExprCar = new Expr_Identifier(Symbol::PercntPercnt);
				Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
				pExprGen = CreateCaller(env, pExprCar, nullptr, pExprBlock, nullptr);
				if (!pExprGen) goto error_done;
			} else {
				IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
				goto error_done;
			}
		} else if (pToken1->IsType(TokenType::And)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '&' Expr\n"));
			if (pToken2->GetExpr()->IsBlock()) {
				// &{..}
				Expr *pExprCar = new Expr_Identifier(Symbol::Amp);
				Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
				pExprGen = CreateCaller(env, pExprCar, nullptr, pExprBlock, nullptr);
				if (!pExprGen) goto error_done;
			} else {
				pExprGen = new Expr_UnaryOp(env.GetOperator(OPTYPE_And), pToken2->GetExpr());
			}
		} else if (pToken1->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '*' Expr\n"));
			pExprGen = new Expr_UnaryOp(env.GetOperator(OPTYPE_Mul), pToken2->GetExpr());
#endif
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr)) {
		if (pToken2->IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '+'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostPos));
		} else if (pToken2->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '*'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostMul));
		} else if (pToken2->IsType(TokenType::Question)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '?'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostQuestion));
		} else if (pToken2->IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '%%'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostMod));
		} else if (pToken2->IsType(TokenType::Seq)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr ..\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostSeq));
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
		return false;
	}
	SetSourceInfo(pExprGen, lineNoTop, lineNoBtm);
	tokenStack.Push(new Token(pExprGen.release()));
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
	RefPtr<Expr> pExprGen;
	if (pToken1->IsType(TokenType::Expr) && pToken3->IsType(TokenType::Expr)) {
		RefPtr<Expr> pExprLeft = pToken1->GetExpr()->Reference();
		RefPtr<Expr> pExprRight = pToken3->GetExpr()->Reference();
		if (pToken2->IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr + Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Add));
		} else if (pToken2->IsType(TokenType::Sub)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr - Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Sub));
		} else if (pToken2->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr * Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Mul));
		} else if (pToken2->IsType(TokenType::Div)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr / Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Div));
		} else if (pToken2->IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr %% Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Mod));
		} else if (pToken2->IsType(TokenType::ModMod)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr %%%% Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::ModMod));
		} else if (pToken2->IsType(TokenType::Dot)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr |.| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Dot));
		} else if (pToken2->IsType(TokenType::Cross)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr |^| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Cross));
		} else if (pToken2->IsType(TokenType::Gear)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr |*| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Gear));
		} else if (pToken2->IsType(TokenType::Concat)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr |+| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Concat));
		} else if (pToken2->IsType(TokenType::Difference)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr |-| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Difference));
		} else if (pToken2->IsType(TokenType::Intersection)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr |&| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Intersection));
		} else if (pToken2->IsType(TokenType::Union)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr ||| Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Union));
		} else if (pToken2->IsType(TokenType::Pow)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr ** Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Pow));
		} else if (pToken2->IsType(TokenType::Eq)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr == Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Eq));
		} else if (pToken2->IsType(TokenType::Ne)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr != Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Ne));
		} else if (pToken2->IsType(TokenType::Lt)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr < Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Lt));
		} else if (pToken2->IsType(TokenType::Gt)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr > Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Gt));
		} else if (pToken2->IsType(TokenType::Le)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr <= Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Le));
		} else if (pToken2->IsType(TokenType::Ge)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr >= Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Ge));
		} else if (pToken2->IsType(TokenType::Cmp)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr <=> Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Cmp));
		} else if (pToken2->IsType(TokenType::Contains)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr in Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Contains));
		} else if (pToken2->IsType(TokenType::Pair)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr => Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Pair));
		} else if (pToken2->IsType(TokenType::OrOr)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr || Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::OrOr));
		} else if (pToken2->IsType(TokenType::AndAnd)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr && Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::AndAnd));
		} else if (pToken2->IsType(TokenType::Or)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr | Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Or));
		} else if (pToken2->IsType(TokenType::And)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr & Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::And));
		} else if (pToken2->IsType(TokenType::Xor)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr ^ Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Xor));
		} else if (pToken2->IsType(TokenType::Shl)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr << Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Shl));
		} else if (pToken2->IsType(TokenType::Shr)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr >> Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Shr));
		} else if (pToken2->IsType(TokenType::Seq)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr .. Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::Seq));
		} else if (pToken2->IsType(TokenType::Assign)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr = Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), nullptr));
		} else if (pToken2->IsType(TokenType::AssignAdd)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr += Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Add));
		} else if (pToken2->IsType(TokenType::AssignSub)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr -= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Sub));
		} else if (pToken2->IsType(TokenType::AssignMul)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr *= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Mul));
		} else if (pToken2->IsType(TokenType::AssignDiv)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr /= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Div));
		} else if (pToken2->IsType(TokenType::AssignMod)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr %%= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Mod));
		} else if (pToken2->IsType(TokenType::AssignPow)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr **= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Pow));
		} else if (pToken2->IsType(TokenType::AssignOr)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr |= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Or));
		} else if (pToken2->IsType(TokenType::AssignAnd)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr &= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::And));
		} else if (pToken2->IsType(TokenType::AssignXor)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr ^= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Xor));
		} else if (pToken2->IsType(TokenType::AssignShl)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr <<= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Shl));
		} else if (pToken2->IsType(TokenType::AssignShr)) {
			DBGPARSER(::printf("Reduce: Expr(Assign) -> Expr >>= Expr\n"));
			pExprGen.reset(new Expr_Assign(pExprLeft.release(), pExprRight.release(), Operator::Shr));
		} else if (pToken2->IsType(TokenType::Period)) {
			DBGPARSER(::printf("Reduce: Expr(Member) -> Expr . Expr\n"));
			if (!pExprRight->IsType<Expr_Identifier>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3,
						   "identifier is expected as a member selector", __LINE__);
				return false;
			}
			pExprGen.reset(new Expr_Member(pExprLeft.release(), dynamic_cast<Expr_Identifier *>(pExprRight.release()),
										MemberMode::Normal));
		} else if (pToken2->IsType(TokenType::ColonColon)) {
			DBGPARSER(::printf("Reduce: Expr(Member) -> Expr :: Expr\n"));
			if (!pExprRight->IsType<Expr_Identifier>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3,
						   "identifier is expected as a member selector", __LINE__);
				return false;
			}
			pExprGen.reset(new Expr_Member(pExprLeft.release(), dynamic_cast<Expr_Identifier *>(pExprRight.release()),
										MemberMode::MapToList));
		} else if (pToken2->IsType(TokenType::ColonAsterisk)) {
			DBGPARSER(::printf("Reduce: Expr(Member) -> Expr :* Expr\n"));
			if (!pExprRight->IsType<Expr_Identifier>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3,
						   "identifier is expected as a member selector", __LINE__);
				return false;
			}
			pExprGen.reset(new Expr_Member(pExprLeft.release(), dynamic_cast<Expr_Identifier *>(pExprRight.release()),
										MemberMode::MapToIter));
		} else if (pToken2->IsType(TokenType::ColonAnd)) {
			DBGPARSER(::printf("Reduce: Expr(Member) -> Expr :& Expr\n"));
			if (!pExprRight->IsType<Expr_Identifier>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3,
						   "identifier is expected as a member selector", __LINE__);
				return false;
			}
			pExprGen.reset(new Expr_Member(pExprLeft.release(), dynamic_cast<Expr_Identifier *>(pExprRight.release()),
										MemberMode::MapAlong));
		} else if (pToken2->IsType(TokenType::Colon) || pToken2->IsType(TokenType::ColonAfterSuffix)) {
			Expr* pExprDst = pExprLeft.get();
			if (pExprDst->IsType<Expr_UnaryOp>()) {
				Expr_UnaryOp* pExprEx = dynamic_cast<Expr_UnaryOp*>(pExprDst);
				//if (!pExprEx->GetOperator()->IsOpPostUnary()) {}
				pExprDst = pExprEx->GetChild();
			}
			if (pExprDst->IsType<Expr_Indexer>()) {
				pExprDst = dynamic_cast<Expr_Indexer*>(pExprDst)->GetCar();
			}
			if (pExprRight->IsType<Expr_Identifier>()) {
				const Symbol* pSymbol = dynamic_cast<Expr_Identifier*>(pExprRight.get())->GetSymbol();
				if (pExprDst->IsType<Expr_Identifier>()) {
					DBGPARSER(::printf("Reduce: Expr(Identifier) -> Expr(Identifier) : Expr(Identifier)\n"));
					Expr_Identifier* pExprIdentifier = dynamic_cast<Expr_Identifier*>(pExprDst);
					pExprIdentifier->GetAttr().AddSymbol(pSymbol);
				} else if (pExprDst->IsType<Expr_Caller>()) {
					DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) : Expr(Identifier)\n"));
					Expr_Caller* pExprCaller = dynamic_cast<Expr_Caller*>(pExprDst)->GetLastTrailer();
					pExprCaller->GetAttr().AddSymbol(pSymbol);
				} else {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							   "attribute can be specified only for identifier and caller", __LINE__);
					return false;
				}
				pExprGen.reset(pExprLeft->Reference());
#if 0
			} else if (pExprRight->IsMember()) {
				DBGPARSER(::printf("Reduce: Expr -> Expr : Expr(Member)\n"));
				Expr_Member* pExprMember = dynamic_cast<Expr_Member*>(pExprRight);
				SymbolList* pAttrFront = nullptr;
				if (pExprDst->IsIdentifier()) {
					Expr_Identifier* pExprIdentifierDst =
									dynamic_cast<Expr_Identifier*>(pExprDst);
					pAttrFront = &pExprIdentifierDst->GetAttrFront();
					const Expr_Identifier *pExprIdentifier = pExprMember->GetSelector();
					pExprIdentifierDst->AddAttrs(pExprIdentifier->GetAttrs());
					pExprIdentifierDst->AddAttrsOpt(pExprIdentifier->GetAttrsOpt());
				} else if (pExprDst->IsCaller()) {
					Expr_Caller* pExprCaller = dynamic_cast<Expr_Caller*>(pExprDst);
					Expr_Caller* pExprTrailer = pExprCaller->GetLastTrailer();
					pAttrFront = &pExprTrailer->GetAttrFront();
					const Expr_Identifier* pExprIdentifier = pExprMember->GetSelector();
					pExprTrailer->AddAttrs(pExprIdentifier->GetAttrs());
					pExprTrailer->AddAttrsOpt(pExprIdentifier->GetAttrsOpt());
				} else {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
					goto error_done;
				}
				if (!pAttrFront->empty()) {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							"value type must be specified as a first attribute");
					goto error_done;
				}
				if (!pAttrFront->AddFromExpr(pExprRight)) {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							   "invalid declaration of value type");
					goto error_done;
				}
				pExprGen = pExprLeft;
			} else if (pExprRight->IsLister()) {
				DBGPARSER(::printf("Reduce: Expr -> Expr : Expr(Lister)\n"));
				ExprList& exprList = dynamic_cast<Expr_Lister*>(pExprRight)->GetExprOwner();
				if (pExprDst->IsIdentifier()) {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							   "identifiers cannot declare optional attributes");
					goto error_done;
				} else if (pExprDst->IsCaller()) {
					Expr_Caller *pExprCaller = dynamic_cast<Expr_Caller *>(pExprDst);
					pExprCaller = pExprCaller->GetLastTrailer();
					for (Expr* pExpr : exprList) {
						if (!pExpr->IsIdentifier()) {
							IssueError(ErrorType::SyntaxError, pToken1, pToken3,
									   "a list of optional attributes can only contain identifiers");
							return false;
						}
						const Symbol* pSymbol = dynamic_cast<Expr_Identifier*>(pExpr)->GetSymbol();
						pExprCaller->AddAttrOpt(pSymbol);
					}
				} else {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
					goto error_done;
				}
				pExprGen = pExprLeft;
#endif
			} else {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
				return false;
			}
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3,
					   "unexpected token for binary operator: %s", pToken2->GetSymbol());
			return false;
		}
	}
#if 0
	if (pToken1->IsType(TokenType::LParenthesis) && pToken2->IsType(TokenType::Expr)) {
		Expr_Iterer *pExprIterer = dynamic_cast<Expr_Iterer *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr -> '(' Expr ')'\n"));
			if (!pExprIterer) {
				pExprGen = pToken2->GetExpr();	// treat expr as non-list
			} else {
				if (!EmitExpr(pExprIterer->GetExprOwner(), pExprIterer, pToken2->GetExpr())) return false;
				pExprGen = pExprIterer;
			}
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '(' -> '(' Expr ','\n"));
			if (!pExprIterer) {
				pExprIterer = new Expr_Iterer();
				pToken1->SetExpr(pExprIterer);
			}
			if (!EmitExpr(pExprIterer->GetExprOwner(), pExprIterer, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::LBracket) && pToken2->IsType(TokenType::Expr)) {
		Expr_Lister *pExprLister = dynamic_cast<Expr_Lister *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> '[' Expr ']'\n"));
			if (!pExprLister) {
				pExprLister = new Expr_Lister();
			}
			if (!EmitExpr(pExprLister->GetExprOwner(), pExprLister, pToken2->GetExpr())) return false;
			pExprGen = pExprLister;
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '[' -> '[' Expr ','\n"));
			if (!pExprLister) {
				pExprLister = new Expr_Lister();
				pToken1->SetExpr(pExprLister);
			}
			if (!EmitExpr(pExprLister->GetExprOwner(), pExprLister, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LParenthesis)) {
		if (pToken3->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '(' ')'\n"));
			Expr_Lister *pExprLister = dynamic_cast<Expr_Lister *>(pToken2->GetExpr());
			if (!pExprLister) {
				pExprLister = new Expr_Lister();
			}
			Expr_Caller *pExprCaller =
				CreateCaller(env, pToken1->GetExpr(), pExprLister, nullptr, nullptr);
			if (!pExprCaller) goto error_done;
			pExprGen = pExprCaller;
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: Expr '(' -> Expr '(' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LBrace)) {
		if (pToken3->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '{' '}'\n"));
			Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken2->GetExpr());
			if (pToken1->GetExpr()->IsCaller()) {
				Expr_Caller *pExprCaller = dynamic_cast<Expr_Caller *>(pToken1->GetExpr());
				if (!pExprBlock) {
					pExprBlock = new Expr_Block();
				}
				pExprCaller->GetLastTrailer()->SetBlock(pExprBlock);
				pExprGen = pExprCaller;
			} else {
				if (!pExprBlock) {
					pExprBlock = new Expr_Block();
				}
				Expr_Caller *pExprCaller =
					CreateCaller(env, pToken1->GetExpr(), nullptr, pExprBlock, nullptr);
				if (!pExprCaller) goto error_done;
				pExprGen = pExprCaller;
			}
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: Expr '{' -> Expr '{' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LBracket)) {
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> Expr '[' ']'\n"));
			Expr *pExprTgt = pToken1->GetExpr();
			Expr_Lister *pExprLister = dynamic_cast<Expr_Lister *>(pToken2->GetExpr());
			if (!pExprLister) {
				pExprLister = new Expr_Lister();
			}
			pExprGen = new Expr_Indexer(pExprTgt, pExprLister);
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: Expr '[' -> Expr '[' EndOfLine\n"));
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::LBrace) && pToken2->IsType(TokenType::Expr)) {
		Expr_Block *pExprBlock = dynamic_cast<Expr_Block *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> '{' Expr '}'\n"));
			if (!pExprBlock) {
				pExprBlock = new Expr_Block();
			}
			if (!EmitExpr(pExprBlock->GetExprOwner(), pExprBlock, pToken2->GetExpr())) return false;
			pExprGen = pExprBlock;
		} else if (pToken3->IsType(TokenType::Comma) ||
					pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			// this is a special case of reducing
			DBGPARSER(::printf("Reduce: '{' -> '{' Expr ','\n"));
			if (!pExprBlock) {
				pExprBlock = new Expr_Block();
				pToken1->SetExpr(pExprBlock);
			}
			if (!EmitExpr(pExprBlock->GetExprOwner(), pExprBlock, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else if (pToken1->IsType(TokenType::LBlockParam) && pToken2->IsType(TokenType::Expr)) {
		Expr_Lister *pExprBlockParam = dynamic_cast<Expr_Lister *>(pToken1->GetExpr());
		if (pToken3->IsType(TokenType::RBlockParam)) {
			// this is a special case of reducing
			DBGPARSER(::printf("do (Reduce: Expr -> '|' Expr '|') "
					"and then attach the Expr to the preceeding LBrace\n"));
			if (!pExprBlockParam) {
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
				if (!pExprBlock) {
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
			if (!pExprBlockParam) {
				pExprBlockParam = new Expr_Lister();
				pToken1->SetExpr(pExprBlockParam);
			}
			if (!EmitExpr(pExprBlockParam->GetExprOwner(), pExprBlockParam, pToken2->GetExpr())) return false;
			_tokenStack.pop_back();
			_tokenStack.pop_back();
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			goto error_done;
		}
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
		goto error_done;
	}
#endif
	SetSourceInfo(pExprGen, lineNoTop, lineNoBtm);
	tokenStack.Push(new Token(pExprGen.release()));
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

void Parser::IssueError(const ErrorType& errorType, const Token* pTokenTop, const Token* pTokenBtm,
						const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	Error::IssueV(errorType, _pTokenizer->GetPathNameSrcReferable()->Reference(),
				  pTokenTop->GetLineNoTop(), pTokenBtm->GetLineNoBtm(), format, ap);
}

void Parser::IssueError(const ErrorType& errorType, const RefPtr<Token>& pTokenTop, const RefPtr<Token>& pTokenBtm,
						const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	Error::IssueV(errorType, _pTokenizer->GetPathNameSrcReferable()->Reference(),
				  pTokenTop->GetLineNoTop(), pTokenBtm->GetLineNoBtm(), format, ap);
}

}
