//==============================================================================
// Parser.cpp
//==============================================================================
#include "stdafx.h"

#define DBGPARSER(x)
//#define DBGPARSER(x) x

namespace Gurax {

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
Parser::Parser(StringReferable* pPathNameSrc, Expr_Collector* pExprRoot) :
	_pTokenizer(new Tokenizer(*this, pPathNameSrc)), _pExprRoot(pExprRoot)
{
}

Expr_Collector* Parser::ParseStream(Stream& stream)
{
	RefPtr<Parser> pParser(new Parser(stream.GetIdentifier()));
	if (!pParser->FeedStream(stream) || !pParser->Finish()) return nullptr;
	return pParser->GetExprRoot().Reference();
}

Expr_Collector* Parser::ParseString(const char* str)
{
	RefPtr<Parser> pParser(new Parser("*string*"));
	if (!pParser->FeedString(str) || !pParser->Finish()) return nullptr;
	return pParser->GetExprRoot().Reference();
}

bool Parser::FeedStream(Stream& stream)
{
	for (;;) {
		char ch = stream.GetChar();
		if (!ch) break;
		FeedChar(ch);
		if (!Error::IsIssued()) {
			// nothing to do
		} else if (Error::GetLastError()->GetErrorType().IsIdentical(ErrorType::DetectEncoding)) {
			String codecName = Error::GetLastError()->GetText();
			Error::Clear();
			RefPtr<Codec> pCodec(Codec::Create(codecName.c_str(), true, false));
			if (!pCodec) return false;
			stream.SetCodec(pCodec.release());
		} else {		
			return false;
		}
	}
	return true;
}

bool Parser::FeedString(const char* str)
{
	for (const char* p = str; *p; p++) {
		FeedChar(*p);
		if (!Error::IsIssued()) {
			// nothing to do
		} else if (Error::GetLastError()->GetErrorType().IsIdentical(ErrorType::DetectEncoding)) {
			Error::Clear();
		} else {		
			return false;
		}
	}
	return true;
}

bool Parser::FeedString(const char* str, size_t len)
{
	for (const char* p = str; len > 0; p++, len--) {
		FeedChar(*p);
		if (!Error::IsIssued()) {
			// nothing to do
		} else if (Error::GetLastError()->GetErrorType().IsIdentical(ErrorType::DetectEncoding)) {
			Error::Clear();
		} else {		
			return false;
		}
	}
	return true;
}

bool Parser::Flush()
{
	FeedChar('\0');
	return !Error::IsIssued();
}

bool Parser::Finish()
{
	if (!Flush()) return false;
	GetExprRoot().Prepare();
	return !Error::IsIssued();
}

void Parser::FeedToken(RefPtr<Token> pToken)
{
	TokenStack& tokenStack = _pTokenizer->GetTokenStack();
	//::printf("FeedToken(%s)\n", pToken->GetSymbol());
	for (;;) {
		TokenStack::reverse_iterator ppTokenTop = tokenStack.SeekTerminal(tokenStack.rbegin());
		DBGPARSER(::printf("%s  << %s\n", tokenStack.ToString().c_str(), pToken->GetSymbol()));
		Precedence prec = Token::LookupPrec(**ppTokenTop, *pToken);
		if ((*ppTokenTop)->IsType(TokenType::Begin) && pToken->IsSeparatorToken()) {
			size_t cntToken = tokenStack.size();
			if (cntToken == 1) {
				// nothing to do
			} else if (cntToken == 2 && tokenStack.back()->IsType(TokenType::Expr)) {
				RefPtr<Token> pTokenPrev(tokenStack.Pop());
				RefPtr<Expr> pExpr(pTokenPrev->GetExpr()->Reference());
				//if (_enablePreparatorFlag && !pExpr->Prepare(env)) {}
				if (pToken->IsType(TokenType::Semicolon)) pExpr->SetSilentFlag(true);
				GetExprRoot().AddExprElem(pExpr.release());
			} else {
				// something's wrong
				IssueError(ErrorType::SyntaxError, pToken, "syntax error (%d)", __LINE__);
			}
			break;
		} else if (prec == Precedence::LT || prec == Precedence::EQ) {
			Token *pTokenLast = tokenStack.back();
			// concatenation of two sequences of string, binary and embed-string
			if (pTokenLast->IsType(TokenType::String) && pToken->IsType(TokenType::String)) {
				pTokenLast->AppendSegment(pToken->GetSegmentSTL());
			} else if (pTokenLast->IsType(TokenType::Binary) && pToken->IsType(TokenType::Binary)) {
				pTokenLast->AppendBinary(pToken->GetBinary());
			} else if (pTokenLast->IsType(TokenType::Template) && pToken->IsType(TokenType::Template)) {
				pTokenLast->AppendSegment(pToken->GetSegmentSTL());
			} else if (pTokenLast->IsType(TokenType::TmplEmbedded) && pToken->IsType(TokenType::TmplEmbedded)) {
				pTokenLast->AppendSegment(pToken->GetSegmentSTL());
			} else {
				tokenStack.Push(pToken->Reference());
			}
			break;
		} else if (prec == Precedence::GT) {
			TokenStack::reverse_iterator ppTokenLeft;
			TokenStack::reverse_iterator ppTokenRight = ppTokenTop;
			while (1) {
				ppTokenLeft = tokenStack.SeekTerminal(ppTokenRight + 1);
				if (Token::LookupPrec(**ppTokenLeft, **ppTokenRight) == Precedence::LT) {
					ppTokenLeft--;
					break;
				}
				ppTokenRight = ppTokenLeft;
			}
			size_t cntToken = std::distance(tokenStack.rbegin(), ppTokenLeft) + 1;
			bool rslt;
			switch (cntToken) {
			case 1: rslt = ReduceOneToken();	break;
			case 2: rslt = ReduceTwoTokens();	break;
			case 3: rslt = ReduceThreeTokens();	break;
			case 4: rslt = ReduceFourTokens();	break;
			case 5: rslt = ReduceFiveTokens();	break;
			default:
				IssueError(ErrorType::SyntaxError, pToken, "syntax error (%d)", __LINE__);
				rslt = false;
				break;
			}
			if (!rslt) break;
		} else if (pToken->IsCloseToken()) {
			IssueError(ErrorType::SyntaxError, pToken, "unmatched closing character");
			break;
		} else {
			IssueError(ErrorType::SyntaxError, pToken, "syntax error (%d)", __LINE__);
			break;
		}
	}
}

bool Parser::ReduceOneToken()
{
	TokenStack& tokenStack = _pTokenizer->GetTokenStack();
	RefPtr<Token> pToken(tokenStack.Pop());
	int lineNoTop = pToken->GetLineNoTop();
	int lineNoBtm = pToken->GetLineNoBtm();
	RefPtr<Expr> pExprGen;
	if (pToken->IsType(TokenType::Number)) {
		DBGPARSER(::printf("Reduce: Expr(Value) -> Number\n"));
		bool successFlag = false;
		Double num = String::ToDouble(pToken->GetSegment(), &successFlag);
		if (!successFlag) {
			String::IssueError_InvalidFormatOfNumber();
			return false;
		}
		pExprGen.reset(
			new Expr_Value(new Value_Number(num), pToken->GetSegmentReferable().Reference()));
	} else if (pToken->IsType(TokenType::String)) {
		DBGPARSER(::printf("Reduce: Expr(String) -> String\n"));
		pExprGen.reset(new Expr_String(pToken->GetSegmentReferable().Reference()));
	} else if (pToken->IsType(TokenType::Binary)) {
		DBGPARSER(::printf("Reduce: Expr(Value) -> Binary\n"));
		pExprGen.reset(new Expr_Value(new Value_Binary(pToken->GetBinaryReferable().Reference())));
	} else if (pToken->IsType(TokenType::Template)) {
		DBGPARSER(::printf("Reduce: Expr(Template) -> Template\n"));
		pExprGen.reset(new Expr_Template(pToken->GetSegmentReferable().Reference(), false));
	} else if (pToken->IsType(TokenType::TmplEmbedded)) {
		DBGPARSER(::printf("Reduce: Expr(Template) -> TmplEmbedded\n"));
		pExprGen.reset(new Expr_Template(pToken->GetSegmentReferable().Reference(), true));
	} else if (pToken->IsType(TokenType::Symbol)) {
		DBGPARSER(::printf("Reduce: Expr(Identifer) -> Symbol\n"));
		pExprGen.reset(new Expr_Identifier(Symbol::Add(pToken->GetSegment())));
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
		pExprGen.reset(new Expr_Suffixed(pToken->GetSegmentReferable().Reference(),
							Symbol::Add(pToken->GetSuffix()), SuffixMgr::Mode::Number));
	} else if (pToken->IsType(TokenType::StringSuffixed)) {
		DBGPARSER(::printf("Reduce: Expr(Suffixed) -> StringSuffixed\n"));
		pExprGen.reset(new Expr_Suffixed(pToken->GetSegmentReferable().Reference(),
							Symbol::Add(pToken->GetSuffix()), SuffixMgr::Mode::String));
	} else if (pToken->IsType(TokenType::BinarySuffixed)) {
		DBGPARSER(::printf("Reduce: Expr(Suffixed) -> BinarySuffixed\n"));
		pExprGen.reset(new Expr_Suffixed(pToken->GetSegmentReferable().Reference(),
							Symbol::Add(pToken->GetSuffix()), SuffixMgr::Mode::Binary));
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
	RefPtr<Token> pToken2(tokenStack.Pop());
	RefPtr<Token> pToken1(tokenStack.Pop());
	RefPtr<Expr> pExprGen;
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken2->GetLineNoBtm();
	if (pToken1->IsType(TokenType::LParenthesis)) {
		if (pToken2->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Tuple) -> '(' ')'\n"));
			pExprGen.reset(new Expr_Tuple(pToken1->GetExprLink().Reference()));
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
			pExprGen.reset(new Expr_Lister(pToken1->GetExprLink().Reference()));
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '[' -> '[' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBrace)) {
		ExprLink& exprLink = pToken1->GetExprLink();
		if (pToken2->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr -> '{' '}'\n"));
			RefPtr<Expr_Block> pExprOfBlock(new Expr_Block(exprLink.Reference()));
			if (pToken1->HasExprLinkEx()) {
				pExprOfBlock->SetExprLinkParam(pToken1->GetExprLinkEx().Reference());
			}
			pExprGen.reset(pExprOfBlock.release());
		} else if (pToken2->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '{' -> '{' EndOfLine\n"));
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBlockParam)) {
		ExprLink& exprLink = pToken1->GetExprLink();
		if (pToken2->IsType(TokenType::RBlockParam)) {
			DBGPARSER(::printf("do (Reduce: (none) -> '|' '|') "
							"and then attach the Expr owner to the preceeding LBrace\n"));
			Token* pTokenPrev = tokenStack.Peek(0);
			if (pTokenPrev->IsType(TokenType::LBrace)) {
				pTokenPrev->SetExprLinkEx(exprLink.Reference());
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
		} else if (pToken1->IsType(TokenType::Question)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '?' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Question));
		} else if (pToken1->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '*' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::PreMul));
		} else if (pToken1->IsType(TokenType::Xor)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '^' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::PreXor));
		} else if (pToken1->IsType(TokenType::Quote)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '`' Expr\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::Quote));
		} else if (pToken1->IsType(TokenType::Mod)) {
			if (pToken2->GetExpr()->IsType<Expr_Block>()) {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> '%%' Expr(Block)\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(new Expr_Identifier(Gurax_SymbolMark(Mod)));
				pExprCaller->SetExprOfBlock(dynamic_cast<Expr_Block*>(pToken2->GetExpr()->Reference()));
				pExprGen.reset(pExprCaller.release());
			} else {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '%%' Expr\n"));
				pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::PreMod));
			}
		} else if (pToken1->IsType(TokenType::ModMod)) {
			if (pToken2->GetExpr()->IsType<Expr_Block>()) {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> '%%%%' Expr(Block)\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(new Expr_Identifier(Gurax_SymbolMark(ModMod)));
				pExprCaller->SetExprOfBlock(dynamic_cast<Expr_Block*>(pToken2->GetExpr()->Reference()));
				pExprGen.reset(pExprCaller.release());
			} else {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '%%%%' Expr\n"));
				pExprGen.reset(new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::PreModMod));
			}
		} else if (pToken1->IsType(TokenType::And)) {
			if (pToken2->GetExpr()->IsType<Expr_Block>()) {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '&' Expr(Block)\n"));
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
				pExprCaller->SetExprCar(new Expr_Identifier(Gurax_SymbolMark(And)));
				pExprCaller->SetExprOfBlock(dynamic_cast<Expr_Block*>(pToken2->GetExpr()->Reference()));
				pExprGen.reset(pExprCaller.release());
			} else {
				DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> '&' Expr\n"));
				pExprGen = new Expr_UnaryOp(pToken2->GetExpr()->Reference(), Operator::PreAnd);
			}
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken2, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr)) {
		if (pToken2->IsType(TokenType::Symbol)) {
			DBGPARSER(::printf("Reduce: Expr Expr(Identifier) -> Expr Symbol\n"));
			tokenStack.Push(pToken1->Reference());
			pExprGen.reset(new Expr_Identifier(Symbol::Add(pToken2->GetSegment())));
			lineNoTop = pToken2->GetLineNoTop();
		} else if (pToken2->IsType(TokenType::Add)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '+'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostPos));
		} else if (pToken2->IsType(TokenType::Mod)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '%%'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostMod));
		} else if (pToken2->IsType(TokenType::ModMod)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '%%%%'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostModMod));
		} else if (pToken2->IsType(TokenType::Mul)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '*'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostMul));
		} else if (pToken2->IsType(TokenType::Question)) {
			DBGPARSER(::printf("Reduce: Expr(UnaryOp) -> Expr '?'\n"));
			pExprGen.reset(new Expr_UnaryOp(pToken1->GetExpr()->Reference(), Operator::PostQuestion));
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
	RefPtr<Token> pToken3(tokenStack.Pop());
	RefPtr<Token> pToken2(tokenStack.Pop());
	RefPtr<Token> pToken1(tokenStack.Pop());
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken3->GetLineNoBtm();
	MemberMode memberMode;
	RefPtr<Expr> pExprGen;
	if (pToken1->IsType(TokenType::Expr) && pToken3->IsType(TokenType::Expr)) {
		RefPtr<Expr> pExprLeft(pToken1->GetExpr()->Reference());
		RefPtr<Expr> pExprRight(pToken3->GetExpr()->Reference());
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
		} else if (pToken2->IsType(TokenType::As)) {
			DBGPARSER(::printf("Reduce: Expr(BinaryOp) -> Expr as Expr\n"));
			pExprGen.reset(new Expr_BinaryOp(pExprLeft.release(), pExprRight.release(), Operator::As));
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
			RefPtr<Expr_Identifier> pExprEx(dynamic_cast<Expr_Identifier*>(pExprRight.release()));
			pExprGen.reset(new Expr_Member(pExprLeft.release(), pExprEx->GetSymbol(),
											pExprEx->GetAttr().Reference(), memberMode));
		} else if (pToken2->IsType(TokenType::Colon) || pToken2->IsType(TokenType::ColonAfterSuffix)) {
			Expr* pExprDst = pExprLeft.get();
			if (pExprDst->IsType<Expr_UnaryOp>()) {
				// In thc case that an identifier has an operator applied like "x+:attr",
				// the attribute should be appended to the identifier.
				pExprDst = &dynamic_cast<Expr_UnaryOp*>(pExprDst)->GetExprChild();
			}
			if (pExprRight->IsType<Expr_Identifier>()) {
				DBGPARSER(::printf("Reduce: Expr -> Expr : Expr(Identifier)\n"));
				Attribute* pAttrDst = pExprDst->GetAttrToAppend();
				if (!pAttrDst) {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							"attributes can only be specified for identifier, caller and indexer", __LINE__);
					return false;
				}
				pAttrDst->AddSymbol(dynamic_cast<Expr_Identifier*>(pExprRight.get())->GetSymbol());
				pExprGen.reset(pExprLeft->Reference());
			} else if (pExprRight->IsType<Expr_Lister>()) {
				DBGPARSER(::printf("Reduce: Expr -> Expr : Expr(Lister)\n"));
				Attribute* pAttrDst = pExprDst->GetAttrToAppend();
				if (!pAttrDst) {
					IssueError(ErrorType::SyntaxError, pToken1, pToken3,
							"optional attributes can only be specified for identifier, caller and indexer", __LINE__);
					return false;
				}
				const Expr* pExprElem = dynamic_cast<Expr_Lister*>(pExprRight.get())->GetExprElemFirst();
				for ( ; pExprElem; pExprElem = pExprElem->GetExprNext()) {
					if (!pExprElem->IsType<Expr_Identifier>()) {
						IssueError(ErrorType::SyntaxError, pToken1, pToken3,
								"list of optional attributes can only contain identifiers");
						return false;
					}
					const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExprElem);
					if (pExprIdentifier->HasAttr()) {
						IssueError(ErrorType::SyntaxError, pToken1, pToken3,
								"optional attributes must be separated with comma");
						return false;
					}
					pAttrDst->AddSymbolOpt(pExprIdentifier->GetSymbol());
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
		ExprLink& exprLink = pToken1->GetExprLink();
		if (pToken3->IsType(TokenType::RParenthesis)) {
			if (pToken1->GetTupleFlag()) {
				DBGPARSER(::printf("Reduce: Expr(Tuple) -> '(' Expr ')'\n"));
				exprLink.AddExpr(pToken2->GetExpr()->Reference());
				pExprGen.reset(new Expr_Tuple(exprLink.Reference()));
			} else {
				DBGPARSER(::printf("Reduce: Expr -> '(' Expr ')'\n"));
				pExprGen.reset(pToken2->GetExpr()->Reference());	// simply removes parenthesis
			}
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '(' -> '(' Expr ','\n"));
			pToken1->SetTupleFlag(true);
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed parenthesis");
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBracket) && pToken2->IsType(TokenType::Expr)) {
		ExprLink& exprLink = pToken1->GetExprLink();
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr -> '[' Expr ']'\n"));
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
			pExprGen.reset(new Expr_Lister(exprLink.Reference()));
		} else if (pToken3->IsType(TokenType::Comma) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '[' -> '[' Expr ','\n"));
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed bracket");
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::LParenthesis)) {
		ExprLink& exprLink = pToken2->GetExprLink();
		if (pToken3->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '(' ')'\n"));
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken1->GetExpr()->Reference());
			pExprCaller->SetExprLinkParam(exprLink.Reference());
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
		if (pToken3->IsType(TokenType::RBrace)) {
			if (pToken1->GetExpr()->IsType<Expr_Caller>()) {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) '{' '}'\n"));
				Expr_Caller* pExprCaller = dynamic_cast<Expr_Caller*>(pToken1->GetExpr());
				pExprCaller->GetExprTrailerLast().SetExprOfBlock(CreateExprOfBlock(pToken2));
				tokenStack.Push(pToken1->Reference());
				return true;
			} else {
				DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '{' '}'\n"));
				Expr* pExpr = pToken1->GetExpr();
				RefPtr<Expr_Caller> pExprCaller(new Expr_Caller(Attribute::Reference(pExpr->GetAttrToAppend())));
				pExpr->ResetAttrToAppend();
				pExprCaller->SetExprCar(pExpr->Reference());
				pExprCaller->SetExprOfBlock(CreateExprOfBlock(pToken2));
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
		ExprLink& exprLink = pToken2->GetExprLink();
		if (pToken3->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr(Indexer) -> Expr '[' ']'\n"));
			RefPtr<Expr_Indexer> pExprIndexer(new Expr_Indexer());
			pExprIndexer->SetExprCar(pToken1->GetExpr()->Reference());
			pExprIndexer->SetExprLinkParam(exprLink.Reference());
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
		ExprLink& exprLink = pToken1->GetExprLink();
		if (pToken3->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr(Block) -> '{' Expr '}'\n"));
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
			pExprGen.reset(CreateExprOfBlock(pToken1));
		} else if (pToken3->IsType(TokenType::Comma) ||
					pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '{' -> '{' Expr ','\n"));
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken3, "unclosed brace");
			return false;
		}
	} else if (pToken1->IsType(TokenType::LBlockParam) && pToken2->IsType(TokenType::Expr)) {
		ExprLink& exprLink = pToken1->GetExprLink();
		if (pToken3->IsType(TokenType::RBlockParam)) {
			DBGPARSER(::printf("do (Reduce: (none) -> '|' Expr '|') "
					"and then attach the Expr owner to the preceeding LBrace\n"));
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
			Token* pTokenPrev = tokenStack.Peek(0);
			if (pTokenPrev->IsType(TokenType::LBrace)) {
				pTokenPrev->SetExprLinkEx(exprLink.Reference());
			} else {
				IssueError(ErrorType::SyntaxError, pToken1, pToken3, "invalid placement of block parameter");
				return false;
			}
			return true;
		} else if (pToken3->IsType(TokenType::Comma) ||
				pToken3->IsType(TokenType::Semicolon) || pToken3->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: '|' -> '|' Expr ','\n"));
			exprLink.AddExpr(pToken2->GetExpr()->Reference());
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
	RefPtr<Token> pToken4(tokenStack.Pop());
	RefPtr<Token> pToken3(tokenStack.Pop());
	RefPtr<Token> pToken2(tokenStack.Pop());
	RefPtr<Token> pToken1(tokenStack.Pop());
	int lineNoTop = pToken1->GetLineNoTop();
	int lineNoBtm = pToken4->GetLineNoBtm();
	RefPtr<Expr> pExprGen;
	if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
		pToken3->IsType(TokenType::LParenthesis)) {
		ExprLink& exprLink = pToken3->GetExprLink();
		if (pToken4->IsType(TokenType::RParenthesis)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken4, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '(' ')'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller*>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken2->GetExpr()->Reference());
			pExprCaller->SetExprLinkParam(exprLink.Reference());
			pExprLeader->GetExprTrailerLast().SetExprTrailer(pExprCaller.release());
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
		if (pToken4->IsType(TokenType::RBrace)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken4, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '{' '}'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller*>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller;
			if (pToken2->GetExpr()->IsType<Expr_Caller>()) {
				pExprCaller.reset(dynamic_cast<Expr_Caller*>(pToken2->GetExpr()->Reference()));
			} else {
				Expr* pExpr = pToken2->GetExpr();
				pExprCaller.reset(new Expr_Caller(Attribute::Reference(pExpr->GetAttrToAppend())));
				pExpr->ResetAttrToAppend();
				pExprCaller->SetExprCar(pExpr->Reference());
			}
			pExprCaller->GetExprTrailerLast().SetExprOfBlock(CreateExprOfBlock(pToken3));
			pExprLeader->GetExprTrailerLast().SetExprTrailer(pExprCaller.release());
			tokenStack.Push(pToken1->Reference());
			return true;
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
		ExprLink& exprLink = pToken2->GetExprLink();
		exprLink.AddExpr(pToken3->GetExpr()->Reference());
		if (pToken4->IsType(TokenType::RParenthesis)) {
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '(' Expr ')'\n"));
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken1->GetExpr()->Reference());
			pExprCaller->SetExprLinkParam(exprLink.Reference());
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
		ExprLink& exprLink = pToken2->GetExprLink();
		exprLink.AddExpr(pToken3->GetExpr()->Reference());
		if (pToken4->IsType(TokenType::RBrace)) {
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr '{' Expr '}'\n"));
			RefPtr<Expr_Caller> pExprCaller;
			if (pToken1->GetExpr()->IsType<Expr_Caller>()) {
				pExprCaller.reset(dynamic_cast<Expr_Caller*>(pToken1->GetExpr()->Reference()));
			} else {
				Expr* pExpr = pToken1->GetExpr();
				pExprCaller.reset(new Expr_Caller(Attribute::Reference(pExpr->GetAttrToAppend())));
				pExpr->ResetAttrToAppend();
				pExprCaller->SetExprCar(pExpr->Reference());
			}
			pExprCaller->GetExprTrailerLast().SetExprOfBlock(CreateExprOfBlock(pToken2));
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
		ExprLink& exprLink = pToken2->GetExprLink();
		exprLink.AddExpr(pToken3->GetExpr()->Reference());
		if (pToken4->IsType(TokenType::RBracket)) {
			DBGPARSER(::printf("Reduce: Expr(Indexer) -> Expr '[' Expr ']'\n"));
			RefPtr<Expr_Indexer> pExprIndexer(new Expr_Indexer());
			pExprIndexer->SetExprCar(pToken1->GetExpr()->Reference());
			pExprIndexer->SetExprLinkParam(exprLink.Reference());
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
	RefPtr<Token> pToken5(tokenStack.Pop());
	RefPtr<Token> pToken4(tokenStack.Pop());
	RefPtr<Token> pToken3(tokenStack.Pop());
	RefPtr<Token> pToken2(tokenStack.Pop());
	RefPtr<Token> pToken1(tokenStack.Pop());
	if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
		pToken3->IsType(TokenType::LParenthesis) && pToken4->IsType(TokenType::Expr)) {
		ExprLink& exprLink = pToken3->GetExprLink();
		exprLink.AddExpr(pToken4->GetExpr()->Reference());
		if (pToken5->IsType(TokenType::RParenthesis)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken5, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '(' Expr ')'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller*>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(pToken2->GetExpr()->Reference());
			pExprCaller->SetExprLinkParam(exprLink.Reference());
			pExprLeader->GetExprTrailerLast().SetExprTrailer(pExprCaller.release());
			tokenStack.Push(pToken1->Reference());
			return true;
		} else if (pToken5->IsType(TokenType::Comma) || pToken5->IsType(TokenType::EndOfLine)) {
			DBGPARSER(::printf("Reduce: Expr Expr '(' -> Expr Expr '(' Expr ','\n"));
			tokenStack.Push(pToken1->Reference());
			tokenStack.Push(pToken2->Reference());
			tokenStack.Push(pToken3->Reference());
			return true;
		} else {
			IssueError(ErrorType::SyntaxError, pToken1, pToken5, "syntax error (%d)", __LINE__);
			return false;
		}
	} else if (pToken1->IsType(TokenType::Expr) && pToken2->IsType(TokenType::Expr) &&
			pToken3->IsType(TokenType::LBrace) && pToken4->IsType(TokenType::Expr)) {
		ExprLink& exprLink = pToken3->GetExprLink();
		exprLink.AddExpr(pToken4->GetExpr()->Reference());
		if (pToken5->IsType(TokenType::RBrace)) {
			if (!pToken1->GetExpr()->IsType<Expr_Caller>()) {
				IssueError(ErrorType::SyntaxError, pToken1, pToken5, "trailer must follow after caller");
				return false;
			}
			DBGPARSER(::printf("Reduce: Expr(Caller) -> Expr(Caller) Expr '{' Expr '}'\n"));
			Expr_Caller* pExprLeader = dynamic_cast<Expr_Caller*>(pToken1->GetExpr());
			RefPtr<Expr_Caller> pExprCaller;
			if (pToken2->GetExpr()->IsType<Expr_Caller>()) {
				pExprCaller.reset(dynamic_cast<Expr_Caller*>(pToken2->GetExpr()->Reference()));
			} else {
				Expr* pExpr = pToken2->GetExpr();
				pExprCaller.reset(new Expr_Caller(Attribute::Reference(pExpr->GetAttrToAppend())));
				pExpr->ResetAttrToAppend();
				pExprCaller->SetExprCar(pExpr->Reference());
			}
			pExprCaller->SetExprOfBlock(CreateExprOfBlock(pToken3));
			pExprLeader->GetExprTrailerLast().SetExprTrailer(pExprCaller.release());
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

Expr_Block* Parser::CreateExprOfBlock(RefPtr<Token>& pToken)
{
	RefPtr<Expr_Block> pExprOfBlock(new Expr_Block(pToken->GetExprLink().Reference()));
	if (pToken->HasExprLinkEx()) {
		pExprOfBlock->SetExprLinkParam(pToken->GetExprLinkEx().Reference());
	}
	return pExprOfBlock.release();
}

}
