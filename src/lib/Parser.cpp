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
				RefPtr<Expr> pExpr(pTokenPrev->GetExpr()->Reference());
#if 0
				if (_enablePreparatorFlag && !pExpr->Prepare(env)) {
					tokenStack.Initialize();
				}
#endif
				if (pToken->IsType(TokenType::Semicolon)) pExpr->SetSilentFlag(true);
				if (_pExprOwner) _pExprOwner->push_back(pExpr.release());
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

bool Parser::ReduceOneToken()
{
	TokenStack& tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken = tokenStack.Pop();
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
		pExprGen.reset(new Expr_Object(new Object_binary(
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
	RefPtr<Expr> pExprGen;
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken2->GetLineNoBtm();
	if (pToken1->IsType(TokenType::LParenthesis)) {
		if (pToken2->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Iterer) -> '(' ')'\n"));
			pExprGen.reset(new Expr_Iterer(pToken1->GetExprOwner().Reference()));
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
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
			pExprGen.reset(new Expr_Lister(pToken1->GetExprOwner().Reference()));
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '[' -> '[' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBrace)) {
		ExprOwner& exprOwner = pToken1->GetExprOwner();
		if (pToken2->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> '{' '}'\n"));
			RefPtr<Expr_Block> pExprBlock(new Expr_Block(exprOwner.Reference()));
			if (pToken1->HasExprOwnerEx()) {
				pExprBlock->SetExprOwnerParam(pToken1->GetExprOwnerEx().Reference());
			}
			pExprGen.reset(pExprBlock.release());
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '{' -> '{' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBlockParam)) {
		ExprOwner& exprOwner = pToken1->GetExprOwner();
		if (pToken2->IsType(TokenType::RBlockParam)) {
			DBGPARSER(::printf("do (Reduce: (none) -> '|' '|') "
							   "and then attach the Expr owner to the preceeding LBrace\n"));
			Token* pTokenPrev = tokenStack.Peek(0);
			if (pTokenPrev->IsType(TokenType::LBrace)) {
				pTokenPrev->SetExprOwnerEx(exprOwner.Reference());
			} else {
				IssueError(ErrorType::SyntaxError, pToken1, pToken2, "block parameter should be placed in a block");
				return false;
			}
			return true;
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '|' -> '|' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "unclosed block parameter");
			return false;
		}
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
		} else if (pToken1->IsType(TokenType::Mod)) {
			if (pToken2->GetExpr()->IsType<Expr_Block>()) {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> '%%' Expr(Block)\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(new Expr_Identifier(Gurax_SymbolMark(Mod)));
				pExprCaller->SetExprOwnerCdr(dynamic_cast<Expr_Block *>(pToken2->GetExpr())->ReleaseExprOwnerElem());
				pExprGen.reset(pExprCaller.release());
			} else {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '%%' Expr\n"));
				pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Mod));
			}
		} else if (pToken1->IsType(TokenType::ModMod)) {
			if (pToken2->GetExpr()->IsType<Expr_Block>()) {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> '%%%%' Expr(Block)\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(new Expr_Identifier(Gurax_SymbolMark(ModMod)));
				pExprCaller->SetExprOwnerCdr(dynamic_cast<Expr_Block *>(pToken2->GetExpr())->ReleaseExprOwnerElem());
				pExprGen.reset(pExprCaller.release());
			} else {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '%%%%' Expr\n"));
				pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::ModMod));
			}
		} else if (pToken1->IsType(TokenType::And)) {
			if (pToken2->GetExpr()->IsType<Expr_Block>()) {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '&' Expr(Block)\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(new Expr_Identifier(Gurax_SymbolMark(And)));
				pExprCaller->SetExprOwnerCdr(dynamic_cast<Expr_Block *>(pToken2->GetExpr())->ReleaseExprOwnerElem());
				pExprGen.reset(pExprCaller.release());
			} else {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '&' Expr\n"));
				pExprGen = new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::And);
			}
		} else if (pToken1->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '*' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Mul));
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr)) {
		if (pToken2->IsType(TokenType::Symbol)) {
			DBGPARSER(::printf("Reduce: Expr Expr(Identifier) -> Expr Symbol\n"));
			tokenStack.Push(pToken1->Reference());
			pExprGen.reset(new Expr_Identifier(Symbol::Add(pToken2->GetValue())));
			lineNoTop = pToken2->GetLineNoTop();
		} else if (pToken2->IsType(TokenType::Add)) {
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
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken3->GetLineNoBtm();
	MemberMode memberMode;
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
		} else if ((memberMode =
					pToken2->IsType(TokenType::Period)?			MemberMode::Normal :
					pToken2->IsType(TokenType::ColonColon)?		MemberMode::MapToList :
					pToken2->IsType(TokenType::ColonAsterisk)?	MemberMode::MapToIter :
					pToken2->IsType(TokenType::ColonAnd)?		MemberMode::MapAlong :
					MemberMode::None) != MemberMode::None) {
			if (!pExprRight->IsType<Expr_Identifier>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3,
						   "identifier is expected as a member selector", __LINE__);
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Member) -> Expr . Expr(Identifier)\n"));
			pExprGen.reset(new Expr_Member(pExprLeft.release(),
										   dynamic_cast<Expr_Identifier *>(pExprRight.release()),
										   memberMode));
		} else if (pToken2->IsType(TokenType::Colon) || pToken2->IsType(TokenType::ColonAfterSuffix)) {
			Expr* pExprDst = pExprLeft.get();
			if (pExprDst->IsType<Expr_UnaryOp>()) {
				pExprDst = dynamic_cast<Expr_UnaryOp*>(pExprDst)->GetExprChild();
			}
			if (pExprDst->IsType<Expr_Indexer>()) {
				pExprDst = dynamic_cast<Expr_Indexer*>(pExprDst)->GetExprCar();
			}
			if (pExprRight->IsType<Expr_Identifier>()) {
				const Symbol* pSymbol = dynamic_cast<Expr_Identifier*>(pExprRight.get())->GetSymbol();
				if (pExprDst->IsType<Expr_Identifier>()) {
					DBGPARSER(::printf("Reduce: Expr(Identifier) -> Expr(Identifier) : Expr(Identifier)\n"));
					Expr_Identifier* pExprIdentifier = dynamic_cast<Expr_Identifier*>(pExprDst);
					pExprIdentifier->GetAttr().AddSymbol(pSymbol);
				} else if (pExprDst->IsType<Expr_Caller>()) {
					DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) : Expr(Identifier)\n"));
					Expr_Caller* pExprCaller = dynamic_cast<Expr_Caller*>(pExprDst)->GetExprTrailerLast();
					pExprCaller->GetAttr().AddSymbol(pSymbol);
				} else {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							   "attributes can only be specified for identifier and caller", __LINE__);
					return false;
				}
				pExprGen.reset(pExprLeft->Reference());
			} else if (pExprRight->IsType<Expr_Member>()) {
				Attribute* pAttrDst = nullptr;
				if (pExprDst->IsType<Expr_Identifier>()) {
					DBGPARSER(::printf("Reduce: Expr(Identifier) -> Expr(Identifier) : Expr(Member)\n"));
					pAttrDst = &dynamic_cast<Expr_Identifier*>(pExprDst)->GetAttr();
				} else if (pExprDst->IsType<Expr_Caller>()) {
					DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) : Expr(Member)\n"));
					pAttrDst = &dynamic_cast<Expr_Caller*>(pExprDst)->GetExprTrailerLast()->GetAttr();
				} else {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							   "attribute can only be specified for identifier and caller", __LINE__);
					return false;
				}
				if (pAttrDst->IsDottedSymbolSet()) {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							"dotted-symbol must be specified as a first attribute");
					return false;
				}
				do {
					RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
					if (!pDottedSymbol->AppendFromExpr(pExprRight.get())) {
						IssueError(ErrorType::SyntaxError, pToken1, pToken3,
								   "invalid format of dotted-symbol");
						return false;
					}
					pAttrDst->SetDottedSymbol(pDottedSymbol.release());
				} while (0);
				Expr_Member* pExprMember = dynamic_cast<Expr_Member*>(pExprRight.get());
				if (pExprMember->GetExprRight()->IsType<Expr_Identifier>()) {
					pAttrDst->AddAttribute(dynamic_cast<Expr_Identifier*>(pExprMember->GetExprRight())->GetAttr());
				}
				pExprGen.reset(pExprLeft->Reference());
			} else if (pExprRight->IsType<Expr_Lister>()) {
				Attribute* pAttrDst = nullptr;
				if (pExprDst->IsType<Expr_Identifier>()) {
					DBGPARSER(::printf("Reduce: Expr(Identifier) -> Expr(Identifier) : Expr(Lister)\n"));
					pAttrDst = &dynamic_cast<Expr_Identifier*>(pExprDst)->GetAttr();
				} else if (pExprDst->IsType<Expr_Caller>()) {
					DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) : Expr(Lister)\n"));
					pAttrDst = &dynamic_cast<Expr_Caller*>(pExprDst)->GetExprTrailerLast()->GetAttr();
				} else {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							   "optional attributes can only be specified for identifier and caller", __LINE__);
					return false;
				}
				const ExprList& exprsElem = dynamic_cast<Expr_Lister*>(pExprRight.get())->GetExprsElem();
				for (const Expr* pExprElem : exprsElem) {
					if (!pExprElem->IsType<Expr_Identifier>()) {
						IssueError(ErrorType::SyntaxError, pToken1, pToken3,
								   "list of optional attributes can only contain identifiers");
						return false;
					}
					pAttrDst->AddSymbolOpt(dynamic_cast<const Expr_Identifier*>(pExprElem)->GetSymbol());
				}
				pExprGen.reset(pExprLeft->Reference());
			} else {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3, "invalid format of attribute");
				return false;
			}
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3,
					   "unexpected token for binary operator: %s", pToken2->GetSymbol());
			return false;
		}
	} else if (pToken1->IsType(TokenType::LParenthesis) && pToken2->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken1->GetExprOwner();
		if (pToken3->IsType(TokenType::RParenthesis)) {
			if (pToken1->GetItererFlag()) {
				DBGPARSER(::printf("Reduce: Expr(Iterer) -> '(' Expr ')'\n"));
				exprOwner.push_back(pToken2->GetExpr()->Reference());
				pExprGen.reset(new Expr_Iterer(exprOwner.Reference()));
			} else {
				DBGPARSER(::printf("Reduce: Expr -> '(' Expr ')'\n"));
				pExprGen.reset(exprOwner.front()->Reference());	// simply removes parenthesis
			}
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '(' -> '(' Expr ','\n"));
			pToken1->SetItererFlag(true);
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed parenthesis");
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBracket) && pToken2->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken1->GetExprOwner();
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> '[' Expr ']'\n"));
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			pExprGen.reset(new Expr_Lister(exprOwner.Reference()));
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '[' -> '[' Expr ','\n"));
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed bracket");
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LParenthesis)) {
		ExprOwner& exprOwner = pToken2->GetExprOwner();
		if (pToken3->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '(' ')'\n"));
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken1->GetExpr()->Reference());
			pExprCaller->SetExprOwnerCdr(exprOwner.Reference());
			pExprGen.reset(pExprCaller.release());
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr '(' -> Expr '(' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed parenthesis");
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LBrace)) {
		ExprOwner& exprOwner = pToken2->GetExprOwner();
		if (pToken3->IsType(TokenType::RBrace)) {
			if (pToken1->GetExpr()->IsType<Expr_Caller>()) {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) '{' '}'\n"));
				Expr_Caller* pExprCaller = dynamic_cast<Expr_Caller *>(pToken1->GetExpr());
				pExprCaller->GetExprTrailerLast()->SetExprOwnerElemBlock(exprOwner.Reference());
				tokenStack.Push(pToken1->Reference());
				return true;
			} else {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '{' '}'\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(pToken1->GetExpr()->Reference());
				pExprCaller->SetExprOwnerElemBlock(exprOwner.Reference());
				pExprGen.reset(pExprCaller.release());
			}
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr '{' -> Expr '{' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed bracket");
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LBracket)) {
		ExprOwner& exprOwner = pToken2->GetExprOwner();
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr(Indexer) -> Expr '[' ']'\n"));
			RefPtr<Expr_Indexer> pExprIndexer(new Expr_Indexer());
			pExprIndexer->SetExprCar(pToken1->GetExpr()->Reference());
			pExprIndexer->SetExprOwnerCdr(exprOwner.Reference());
			pExprGen.reset(pExprIndexer.release());
		} else if (pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr '[' -> Expr '[' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed bracket");
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBrace) && pToken2->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken1->GetExprOwner();
		if (pToken3->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr(Block) -> '{' Expr '}'\n"));
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			RefPtr<Expr_Block> pExprBlock(new Expr_Block(exprOwner.Reference()));
			if (pToken1->HasExprOwnerEx()) {
				pExprBlock->SetExprOwnerParam(pToken1->GetExprOwnerEx().Reference());
			}
			pExprGen.reset(pExprBlock.release());
		} else if (pToken3->IsType(TokenType::Comma) ||
					pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '{' -> '{' Expr ','\n"));
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed brace");
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBlockParam) && pToken2->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken1->GetExprOwner();
		if (pToken3->IsType(TokenType::RBlockParam)) {
			DBGPARSER(::printf("do (Reduce: (none) -> '|' Expr '|') "
					"and then attach the Expr owner to the preceeding LBrace\n"));
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			Token* pTokenPrev = tokenStack.Peek(0);
			if (pTokenPrev->IsType(TokenType::LBrace)) {
				pTokenPrev->SetExprOwnerEx(exprOwner.Reference());
			} else {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3, "invalid placement of block parameter");
				return false;
			}
			return true;
		} else if (pToken3->IsType(TokenType::Comma) ||
				   pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '|' -> '|' Expr ','\n"));
			exprOwner.push_back(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			return false;
		}
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
		return false;
	}
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
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken4->GetLineNoBtm();
	RefPtr<Expr> pExprGen;
	if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
		pToken3->IsType(TokenType::LParenthesis)) {
		ExprOwner& exprOwner = pToken3->GetExprOwner();
		if (pToken4->IsType(TokenType::RParenthesis)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken4, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '(' ')'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller *>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken2->GetExpr()->Reference());
			pExprCaller->SetExprOwnerCdr(exprOwner.Reference());
			pExprLeader->AppendExprTrailer(pExprCaller.release());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else if (pToken4->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr Expr '(' -> Expr Expr '(' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			tokenStack.Push(pToken3->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
			   pToken3->IsType(TokenType::LBrace)) {
		ExprOwner& exprOwner = pToken3->GetExprOwner();
		if (pToken4->IsType(TokenType::RBrace)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken4, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '{' '}'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller *>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller;
			if (pToken2->GetExpr()->IsType<Expr_Caller>()) {
				pExprCaller.reset(dynamic_cast<Expr_Caller *>(pToken2->GetExpr()->Reference()));
			} else {
				pExprCaller.reset(new Expr_Caller());
				pExprCaller->SetExprCar(pToken2->GetExpr()->Reference());
			}
			pExprCaller->GetExprTrailerLast()->SetExprOwnerElemBlock(exprOwner.Reference());
			pExprLeader->AppendExprTrailer(pExprCaller.release());
			tokenStack.Push(pToken1->Reference());
		} else if (pToken4->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr Expr '{' -> Expr Expr '{' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			tokenStack.Push(pToken3->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) &&
			   pToken2->IsType(TokenType::LParenthesis) && pToken3->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken2->GetExprOwner();
		exprOwner.push_back(pToken3->GetExpr()->Reference());
		if (pToken4->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '(' Expr ')'\n"));
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken1->GetExpr()->Reference());
			pExprCaller->SetExprOwnerCdr(exprOwner.Reference());
			pExprGen.reset(pExprCaller.release());
		} else if (pToken4->IsType(TokenType::Comma) || pToken4->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr '(' -> Expr '(' Expr ','\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) &&
			   pToken2->IsType(TokenType::LBrace) && pToken3->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken2->GetExprOwner();
		exprOwner.push_back(pToken3->GetExpr()->Reference());
		if (pToken4->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '{' Expr '}'\n"));
			RefPtr<Expr_Caller> pExprCaller;
			if (pToken1->GetExpr()->IsType<Expr_Caller>()) {
				pExprCaller.reset(dynamic_cast<Expr_Caller *>(pToken2->GetExpr()->Reference()));
			} else {
				pExprCaller.reset(new Expr_Caller());
				pExprCaller->SetExprCar(pToken1->GetExpr()->Reference());
			}
			pExprCaller->GetExprTrailerLast()->SetExprOwnerElemBlock(exprOwner.Reference());
			pExprGen.reset(pExprCaller.release());
		} else if (pToken4->IsType(TokenType::Comma) ||
					pToken4->IsType(TokenType::Semicolon) || pToken4->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr '{' -> Expr '{' Expr ','\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) &&
			   pToken2->IsType(TokenType::LBracket) && pToken3->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken2->GetExprOwner();
		exprOwner.push_back(pToken3->GetExpr()->Reference());
		if (pToken4->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr(Indexer) -> Expr '[' Expr ']'\n"));
			RefPtr<Expr_Indexer> pExprIndexer(new Expr_Indexer());
			pExprIndexer->SetExprCar(pToken1->GetExpr()->Reference());
			pExprIndexer->SetExprOwnerCdr(exprOwner.Reference());
			pExprGen.reset(pExprIndexer.release());
		} else if (pToken4->IsType(TokenType::Comma) || pToken4->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr '[' -> Expr '[' Expr ','\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "syntax error (%d)", __LINE__);
			return false;
		}
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, pToken4, "syntax error (%d)", __LINE__);
		return false;
	}
	SetSourceInfo(pExprGen, lineNoTop, lineNoBtm);
	tokenStack.Push(new Token(pExprGen.release()));
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
	if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
		pToken3->IsType(TokenType::LParenthesis) && pToken4->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken3->GetExprOwner();
		exprOwner.push_back(pToken4->GetExpr()->Reference());
		if (pToken5->IsType(TokenType::RParenthesis)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken5, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '(' Expr ')'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller*>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken2->GetExpr()->Reference());
			pExprCaller->SetExprOwnerCdr(exprOwner.Reference());
			pExprLeader->AppendExprTrailer(pExprCaller.release());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else if (pToken5->IsType(TokenType::Comma) || pToken5->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr Expr '(' -> Expr Expr '(' Expr ','\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken5, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
			   pToken3->IsType(TokenType::LBrace) && pToken4->IsType(TokenType::Expr)) {
		ExprOwner& exprOwner = pToken3->GetExprOwner();
		exprOwner.push_back(pToken4->GetExpr()->Reference());
		if (pToken5->IsType(TokenType::RBrace)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken5, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '{' Expr '}'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller *>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller;
			if (pToken2->GetExpr()->IsType<Expr_Caller>()) {
				pExprCaller.reset(dynamic_cast<Expr_Caller *>(pToken2->GetExpr()->Reference()));
			} else {
				pExprCaller.reset(new Expr_Caller());
				pExprCaller->SetExprCar(pToken2->GetExpr()->Reference());
			}
			pExprCaller->SetExprOwnerElemBlock(exprOwner.Reference());
			pExprLeader->AppendExprTrailer(pExprCaller.release());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else if (pToken5->IsType(TokenType::Comma) ||
					pToken5->IsType(TokenType::Semicolon) || pToken5->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr Expr '{' -> Expr Expr '{' Expr ','\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			tokenStack.Push(pToken3->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken4, "syntax error (%d)", __LINE__);
			return false;
		}
	} else {
		IssueError(ErrorType::SyntaxError, pToken1, pToken4, "syntax error (%d)", __LINE__);
		return false;
	}
	// never reaches here.
}

bool Parser::EmitExpr(ExprOwner& exprOwner, Expr* pExpr)
{
	if (pExpr->IsType<Expr_Caller>()) {
		Expr_Caller* pExprCaller = dynamic_cast<Expr_Caller*>(pExpr);
		if (!pExprCaller->IsTrailer() || exprOwner.empty()) {
			// nothing to do
		} else if (exprOwner.back()->IsType<Expr_Caller>()) {
			dynamic_cast<Expr_Caller *>(exprOwner.back())->GetExprTrailerLast()->SetExprTrailer(pExprCaller);
			return true;
		} else {
			Expr::Delete(pExpr);
			Error::Issue(ErrorType::SyntaxError, _pTokenizer->GetPathNameSrcReferable()->Reference(),
						 pExpr->GetLineNoTop(), pExpr->GetLineNoBtm(),
						 "trailer must be placed after a caller expression");
			return false;
		}
	}
	exprOwner.push_back(pExpr);
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
