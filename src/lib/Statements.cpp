//==============================================================================
// Statements.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Statements
//------------------------------------------------------------------------------
// if (`cond) {`block}
Gurax_DeclareStatementAlias(if_, "if")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(if_)
{
	SymbolList symbols;
	if (const Expr* pExprError = exprCaller.GetTrailerSymbols(symbols)) {
		Error::IssueWith(ErrorType::SyntaxError, *pExprError,
						 "invalid format of if-elsif-else sequence");
		return;
	}
	if (!symbols.empty()) {
		auto ppSymbol = symbols.begin();
		for ( ; ppSymbol + 1 != symbols.end(); ppSymbol++) {
			const Symbol* pSymbol = *ppSymbol;
			if (!pSymbol->IsIdentical(Gurax_Symbol(elsif))) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "invalid format of if-elsif-else sequence");
				return;
			}
		}
		const Symbol* pSymbol = *ppSymbol;
		if (!(pSymbol->IsIdentical(Gurax_Symbol(elsif)) || pSymbol->IsIdentical(Gurax_Symbol(else_)))) {
			Error::IssueWith(ErrorType::SyntaxError, exprCaller,
							 "invalid format of if-elsif-else sequence");
			return;
		}
	}
	if (exprCaller.CountExprCdr() != 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "if-statement takes one argument");
		return;
	}
	exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);				// [Bool]
	if (exprCaller.HasExprTrailer()) {
		auto pPUnitBranch1 = composer.Add_JumpIfNot(exprCaller);		// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		auto pPUnitBranch2 = composer.Add_Jump(exprCaller);				// [Any]
		pPUnitBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		exprCaller.GetExprTrailer()->ComposeOrNil(composer);			// [Any]
		pPUnitBranch2->SetPUnitCont(composer.PeekPUnitCont());
	} else {
		auto pPUnitBranch1 = composer.Add_NilJumpIfNot(exprCaller);		// [] or [nil]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		pPUnitBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	composer.Add_NoOperation(exprCaller);								// [Any]
}

// elsif (`cond) {`block}
Gurax_DeclareStatementAlias(elsif, "elsif")
{
	Declare(VTYPE_Any, Flag::Trailer);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(elsif)
{
	if (exprCaller.CountExprCdr() != 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "elsif-statement takes one argument");
		return;
	}
	exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);				// [Bool]
	if (exprCaller.HasExprTrailer()) {
		auto pPUnitBranch1 = composer.Add_JumpIfNot(exprCaller);		// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		auto pPUnitBranch2 = composer.Add_Jump(exprCaller);				// [Any]
		pPUnitBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		exprCaller.GetExprTrailer()->ComposeOrNil(composer);			// [Any]
		pPUnitBranch2->SetPUnitCont(composer.PeekPUnitCont());
	} else {
		auto pPUnitBranch1 = composer.Add_NilJumpIfNot(exprCaller);		// [] or [nil]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		pPUnitBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
}

// else ():trailer {`block}
Gurax_DeclareStatementAlias(else_, "else")
{
	Declare(VTYPE_Any, Flag::Trailer);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(else_)
{
	if (exprCaller.CountExprCdr() != 0) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "else-statement takes no argument");
		return;
	}
	if (exprCaller.HasExprTrailer()) {
		Error::IssueWith(ErrorType::SyntaxError, exprCaller,
						 "invalid format of if-elsif-else sequence");
		return;
	}
	exprCaller.GetExprOfBlock()->ComposeOrNil(composer);				// [Any]
}

// for (`cond) {`block}
Gurax_DeclareStatementAlias(for_, "for")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(for_)
{
	if (exprCaller.CountExprCdr() < 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "for-statement takes more than one argument");
		return;
	}
	std::unique_ptr<DeclArgOwner> pDeclArgs(new DeclArgOwner());
	for (Expr* pExpr = exprCaller.GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (!pExpr->IsType<Expr_BinaryOp>()) {
			Error::IssueWith(ErrorType::ArgumentError, *pExpr,
							 "invalid argument for for-statement");
			return;
		}
		Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
		if (!pExprEx->GetOperator()->IsType(OpType::Contains)) {
			Error::IssueWith(ErrorType::ArgumentError, *pExpr,
							 "invalid argument for for-statement");
			return;
		}
		RefPtr<DeclArg> pDeclArg(DeclArg::CreateFromExpr(*pExprEx->GetExprLeft()));
		if (!pDeclArg) return;
		pDeclArgs->push_back(pDeclArg.release());
		pExprEx->GetExprRight()->ComposeOrNil(composer);				// [Any]
		composer.Add_GenIterator(exprCaller);							// [Iterator]
	}
	size_t nIterators = pDeclArgs->size();
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	bool createListFlag =
		exprCaller.GetAttr().IsSet(Gurax_Symbol(list)) ||
		exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
	if (declArgsOfBlock.empty() && !createListFlag) {
		composer.Add_PushFrame_Block(exprCaller);
		composer.Add_Value(exprCaller, Value::nil());					// [Iterator1..n Last=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		auto pPUnitBranch = composer.Add_ForEach(
			exprCaller, 1, pDeclArgs.release());						// [Iterator1..n Last]
		composer.Add_PopValue(exprCaller);								// [Iterator1..n]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Last]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_RemoveValues(exprCaller, 1, nIterators);			// [Last]
		composer.Add_PopFrame(exprCaller);
	} else if (declArgsOfBlock.empty() && createListFlag) {
		composer.Add_PushFrame_Block(exprCaller);
		composer.Add_CreateList(exprCaller, 32);						// [Iterator1..n List]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		auto pPUnitBranch = composer.Add_ForEach(
			exprCaller, 1, pDeclArgs.release());						// [Iterator1..n List]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n List Elem]
		composer.Add_ListElem(exprCaller, 0);							// [Iterator1..n List]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_RemoveValues(exprCaller, 1, nIterators);			// [List]
		composer.Add_PopFrame(exprCaller);
	} else if (declArgsOfBlock.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgsOfBlock.begin();
		composer.Add_PushFrame_Block(exprCaller);
		composer.Add_GenCounterIterator(exprCaller);					// [Iterator1..n Iterator]
		composer.Add_Value(exprCaller, Value::nil());					// [Iterator1..n Iterator Last=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		auto pPUnitBranch = composer.Add_ForEach(
			exprCaller, 2, pDeclArgs.release());						// [Iterator1..n Iterator Last]
		composer.Add_PopValue(exprCaller);								// [Iterator1..n Iterator]
		composer.Add_EvalIterator(exprCaller, 0)->
			SetPUnitBranchDest(composer.PeekPUnitCont());				// [Iterator1..n Iterator Idx]
		composer.Add_AssignToDeclArg(
			exprCaller, (*ppDeclArg)->Reference());
		composer.Flush(true);											// [Iterator1..n Iterator]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Iterator Last]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_RemoveValues(exprCaller, 1, nIterators + 1);		// [Last]
		composer.Add_PopFrame(exprCaller);
	} else {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "invalid number of block parameters");
		return;
	}
}

// while (`cond) {`block}
Gurax_DeclareStatementAlias(while_, "while")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(while_)
{
	if (exprCaller.CountExprCdr() != 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "while-statement takes one argument");
		return;
	}
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	if (declArgsOfBlock.empty()) {
		composer.Add_Value(exprCaller, Value::nil());					// [Last=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);			// [Last Bool]
		auto pPUnitBranch = composer.Add_JumpIfNot(exprCaller);			// [Last]
		composer.Add_PopValue(exprCaller);								// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Last]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_NoOperation(exprCaller);
	} else if (declArgsOfBlock.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgsOfBlock.begin();
		composer.Add_PushFrame_Block(exprCaller);
		composer.Add_GenCounterIterator(exprCaller);					// [Iterator]
		composer.Add_Value(exprCaller, Value::nil());					// [Iterator Last=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);			// [Iterator Last Bool]
		auto pPUnitBranch = composer.Add_JumpIfNot(exprCaller);			// [Iterator Last]
		composer.Add_PopValue(exprCaller);								// [Iterator]
		composer.Add_EvalIterator(exprCaller, 0);						// [Iterator Idx]
		composer.Add_AssignToDeclArg(
			exprCaller, (*ppDeclArg)->Reference());
		composer.Flush(true);											// [Iterator]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_RemoveValue(exprCaller, 1);						// [Last]
		composer.Add_PopFrame(exprCaller);
	} else {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "invalid number of block parameters");
		return;
	}
}

// repeat (cnt?:number) {block}
Gurax_DeclareStatement(repeat)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cnt", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
}

Gurax_ImplementStatement(repeat)
{
	if (exprCaller.CountExprCdr() > 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "repeat-statement takes zero or one argument");
		return;
	}
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	if (declArgsOfBlock.empty()) {
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
			composer.Add_Cast(exprCaller, VTYPE_Number);				// [Number]
			composer.Add_GenRangeIterator(exprCaller);					// [Iterator]
		} else {
			composer.Add_GenCounterIterator(exprCaller);				// [Iterator]
		}
		composer.Add_Value(exprCaller, Value::nil());					// [Iteartor Last=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		auto pPUnitBranch = composer.Add_EvalIterator(exprCaller, 1);
		composer.Flush(true);											// [Iterator Last]
		composer.Add_PopValue(exprCaller);								// [Iterator]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_RemoveValue(exprCaller, 1);						// [Last]
	} else if (declArgsOfBlock.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgsOfBlock.begin();
		composer.Add_PushFrame_Block(exprCaller);
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
			composer.Add_Cast(exprCaller, VTYPE_Number);				// [Number]
			composer.Add_GenRangeIterator(exprCaller);					// [Iterator]
		} else {
			composer.Add_GenCounterIterator(exprCaller);				// [Iterator]
		}
		composer.Add_Value(exprCaller, Value::nil());					// [Iteartor Last=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		auto pPUnitBranch = composer.Add_EvalIterator(exprCaller, 1);	// [Iterator Last idx]
		composer.Add_AssignToDeclArg(exprCaller, (*ppDeclArg)->Reference());
		composer.Flush(true);											// [Iterator Last]
		composer.Add_PopValue(exprCaller);								// [Iterator]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
		composer.Add_Jump(exprCaller, pPUnitLoop);
		pPUnitBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_RemoveValue(exprCaller, 1);						// [Last]
		composer.Add_PopFrame(exprCaller);
	} else {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "invalid number of block parameters");
		return;
	}
}

// break(value?)
Gurax_DeclareStatementAlias(break_, "break")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementStatement(break_)
{
	if (exprCaller.CountExprCdr() > 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "break-statement takes zero or one argument");
		return;
	}
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (pExprCdr) {
		composer.Add_PopValue(exprCaller);
		pExprCdr->ComposeOrNil(composer);							// [Any]
	}
	composer.Add_Break(exprCaller);
}

// continue(value?)
Gurax_DeclareStatementAlias(continue_, "continue")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementStatement(continue_)
{
	if (exprCaller.CountExprCdr() > 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "continue-statement takes zero or one argument");
		return;
	}
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (pExprCdr) {
		composer.Add_PopValue(exprCaller);
		pExprCdr->ComposeOrNil(composer);							// [Any]
	}
	composer.Add_Continue(exprCaller);
}

// return(value?)
Gurax_DeclareStatementAlias(return_, "return")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementStatement(return_)
{
	if (exprCaller.CountExprCdr() > 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "return-statement takes zero or one argument");
		return;
	}
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (pExprCdr) {
		composer.Add_PopValue(exprCaller);
		pExprCdr->ComposeOrNil(composer);							// [Any]
	}
	composer.Add_Return(exprCaller);
}

void Statements::PrepareBasic(Frame& frame)
{
	frame.Assign(Gurax_CreateStatement(if_));
	frame.Assign(Gurax_CreateStatement(elsif));
	frame.Assign(Gurax_CreateStatement(else_));
	frame.Assign(Gurax_CreateStatement(for_));
	frame.Assign(Gurax_CreateStatement(while_));
	frame.Assign(Gurax_CreateStatement(repeat));
	frame.Assign(Gurax_CreateStatement(break_));
	frame.Assign(Gurax_CreateStatement(continue_));
	frame.Assign(Gurax_CreateStatement(return_));
}

}
