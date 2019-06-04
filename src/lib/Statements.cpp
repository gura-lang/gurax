//==============================================================================
// Statements.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Statements
//------------------------------------------------------------------------------
// cond (`cond, `exprTrue, `exprFalse?)
Gurax_DeclareStatement(cond)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("exprTrue", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("exprFalse", VTYPE_Quote, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Evaluates `exprTrue` and returns its result if `cond` is determined as `true`, and does `exprFalse` otherwise.\n"
		"If `exprFalse` is omitted, it returns `nil` when `cond` turns out to be `false`.\n"
		"\n"
		"This statement behaves the same as `if` being used like below:\n"
		"\n"
		"    if (cond) {exprTrue) else {exprFalse}\n");
}

Gurax_ImplementStatement(cond)
{
	Expr* pExprCond = exprCaller.GetExprCdrFirst();
	Expr* pExprTrue = pExprCond->GetExprNext();
	Expr* pExprFalse = pExprTrue->GetExprNext();
	pExprCond->ComposeOrNil(composer);									// [Bool]
	if (pExprFalse) {	// cond (cond, exprTrue, exprFalse)
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(&exprCaller);								// []
		pExprTrue->ComposeOrNil(composer);								// [Any]
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_Jump(&exprCaller);									// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		pExprFalse->ComposeOrNil(composer);								// [Any]
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else {			// cond (cond, exprTrue)
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_NilJumpIfNot(&exprCaller);							// [] or [nil]
		pExprTrue->ComposeOrNil(composer);								// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	composer.Add_NoOperation(&exprCaller);								// [Any]
}

// if (`cond) {`block}
Gurax_DeclareStatementAlias(if_, "if")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
	AddHelp(
		Gurax_Symbol(en),
		"Specifies an \"if\" block within a sequence of `if-elsif-else`.\n"
		"\n"
		"If the result of `cond` is determined as `true`, the block would be executed,\n"
		"and its evaluation result would become the returned value of the statement.\n"
		"\n"
		"Otherwise, if the statement is followed by a trailer such as `elsif` and `else`, that would be evaluated.\n"
		"If no trailer exists, the satement returns `nil` value.\n");
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
	exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);				// [Bool]
	if (exprCaller.HasExprTrailer()) {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(&exprCaller);							// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_Jump(&exprCaller);									// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		exprCaller.GetExprTrailer()->ComposeOrNil(composer);			// [Any]
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_NilJumpIfNot(&exprCaller);							// [] or [nil]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	composer.Add_NoOperation(&exprCaller);								// [Any]
}

// elsif (`cond) {`block}
Gurax_DeclareStatementAlias(elsif, "elsif")
{
	Declare(VTYPE_Any, Flag::Trailer);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
	AddHelp(
		Gurax_Symbol(en),
		"Specifies an \"elsif\" block within a sequence of `if-elsif-else`.\n"
		"\n"
		"If the result of `cond` is determined as `true`, the block would be executed,\n"
		"and its evaluation result would become the returned value of the statement.\n"
		"\n"
		"Otherwise, if the statement is followed by a trailer such as `elsif` and `else`, that would be evaluated.\n"
		"If no trailer exists, the statement returns `nil` value.\n");
}

Gurax_ImplementStatement(elsif)
{
	exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);				// [Bool]
	if (exprCaller.HasExprTrailer()) {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(&exprCaller);								// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_Jump(&exprCaller);									// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		exprCaller.GetExprTrailer()->ComposeOrNil(composer);			// [Any]
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_NilJumpIfNot(&exprCaller);							// [] or [nil]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
}

// else ():trailer {`block}
Gurax_DeclareStatementAlias(else_, "else")
{
	Declare(VTYPE_Any, Flag::Trailer);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
	AddHelp(
		Gurax_Symbol(en),
		"Specifies an \"else\" block within a sequence of `if-elsif-else` or `try-catch-else-finally`.\n");
}

Gurax_ImplementStatement(else_)
{
	if (exprCaller.HasExprTrailer()) {
		Error::IssueWith(ErrorType::SyntaxError, exprCaller,
						 "invalid format of if-elsif-else sequence");
		return;
	}
	exprCaller.GetExprOfBlock()->ComposeOrNil(composer);				// [Any]
}

// try {`block}
Gurax_DeclareStatementAlias(try_, "try")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(try_)
{
	SymbolList symbols;
	if (const Expr* pExprError = exprCaller.GetTrailerSymbols(symbols)) {
		Error::IssueWith(ErrorType::SyntaxError, *pExprError,
						 "invalid format of try-catch-else-finally sequence");
		return;
	}
	if (!symbols.empty()) {
		auto ppSymbol = symbols.begin();
		for ( ; ppSymbol + 1 != symbols.end(); ppSymbol++) {
			const Symbol* pSymbol = *ppSymbol;
			if (!(pSymbol->IsIdentical(Gurax_Symbol(catch_)) || pSymbol->IsIdentical(Gurax_Symbol(else_)))) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "invalid format of try-catch-else-finally sequence");
				return;
			}
		}
		const Symbol* pSymbol = *ppSymbol;
		if (!(pSymbol->IsIdentical(Gurax_Symbol(catch_)) || pSymbol->IsIdentical(Gurax_Symbol(else_)) ||
			  pSymbol->IsIdentical(Gurax_Symbol(finally)))) {
			Error::IssueWith(ErrorType::SyntaxError, exprCaller,
							 "invalid format of try-catch-else-finally sequence");
			return;
		}
	}
	if (exprCaller.HasExprTrailer()) {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_BeginTryBlock(&exprCaller);						// [Any]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_EndTryBlock(&exprCaller);							// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		exprCaller.GetExprTrailer()->ComposeOrNil(composer);			// [Any]
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
		composer.Add_NoOperation(&exprCaller);							// [Any]
	} else {
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
	}
}

// catch(errorType?:ErrorType) {`block}
Gurax_DeclareStatementAlias(catch_, "catch")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("errorType", VTYPE_ErrorType, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(catch_)
{
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	if (declArgsOfBlock.size() > 1) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "invalid number of block parameters");
		return;
	}
	const DeclArg* pDeclArg = declArgsOfBlock.empty()? nullptr : declArgsOfBlock.front();
	if (exprCaller.GetExprCdrFirst()) {
		exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);				// [Any]
		composer.Add_Cast(VTYPE_ErrorType, false, &exprCaller);				// [ErrorType]
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNoCatch(&exprCaller);							// [Error] or []
		if (pDeclArg) {
			composer.Add_PushFrame<Frame_Block>(&exprCaller);
			composer.Add_AssignToDeclArg(pDeclArg->Reference(), &exprCaller);
			composer.FlushDiscard();										// []
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
			composer.Add_PopFrame(&exprCaller);
		} else {
			composer.FlushDiscard();
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		}
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_Jump(&exprCaller);										// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		if (exprCaller.HasExprTrailer()) {
			exprCaller.GetExprTrailer()->ComposeOrNil(composer);			// [Any]
		} else {
			composer.Add_Miscatch(Value::nil(), &exprCaller);				// [nil]
		}
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else if (exprCaller.HasExprTrailer()) {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNoCatchAny(&exprCaller);							// [Error] or []
		if (pDeclArg) {
			composer.Add_PushFrame<Frame_Block>(&exprCaller);
			composer.Add_AssignToDeclArg(pDeclArg->Reference(), &exprCaller);
			composer.FlushDiscard();										// []
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
			composer.Add_PopFrame(&exprCaller);
		} else {
			composer.FlushDiscard();
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		}
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_Jump(&exprCaller);										// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		exprCaller.GetExprTrailer()->ComposeOrNil(composer);				// [Any]
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else {
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_NilJumpIfNoCatchAny(&exprCaller);						// [Error] or [nil]
		if (pDeclArg) {
			composer.Add_PushFrame<Frame_Block>(&exprCaller);
			composer.Add_AssignToDeclArg(pDeclArg->Reference(), &exprCaller);
			composer.FlushDiscard();										// []
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
			composer.Add_PopFrame(&exprCaller);
		} else {
			composer.FlushDiscard();
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
		}
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
}

// finally {`block}
Gurax_DeclareStatement(finally)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(finally)
{
}

// for (`cond+) {`block}
Gurax_DeclareStatementAlias(for_, "for")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::OnceOrMore, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(for_)
{
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
		pExprEx->GetExprRight()->ComposeOrNil(composer);					// [Any]
		composer.Add_GenIterator(&exprCaller);								// [Iterator]
	}
	size_t nIterators = pDeclArgs->size();
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	bool listFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(list));
	bool xlistFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
	bool createListFlag = listFlag || xlistFlag;
	if (declArgsOfBlock.empty()) {
		composer.Add_PushFrame<Frame_Block>(&exprCaller);
		if (createListFlag) {
			composer.Add_CreateList(32, &exprCaller);						// [Iterator1..n List=[]]
			PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator1..n List]
			PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator1..n List]
			pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_ForEach(1, pDeclArgs.release(), &exprCaller);		// [Iterator1..n List]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n List Elem]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValues(1, nIterators, &exprCaller);			// [List]
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);					// [Iterator1..n Last=nil]
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_ForEach(1, pDeclArgs.release(), &exprCaller);		// [Iterator1..n Last]
			composer.Add_DiscardValue(&exprCaller);							// [Iterator1..n]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Last]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValues(1, nIterators, &exprCaller);			// [Last]
		}
		composer.Add_PopFrame(&exprCaller);
	} else if (declArgsOfBlock.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgsOfBlock.begin();
		composer.Add_PushFrame<Frame_Block>(&exprCaller);
		composer.Add_GenCounterIterator(&exprCaller);						// [Iterator1..n Iterator]
		if (createListFlag) {
			composer.Add_CreateList(32, &exprCaller);						// [Iterator1..n Iterator List=[]]
			PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator1..n Iterator List]
			PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator1..n Iterator List]
			pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_ForEach(2, pDeclArgs.release(), &exprCaller);		// [Iterator1..n Iterator List]
			composer.Add_EvalIterator(1, &exprCaller);						// [Iterator1..n Iterator List Idx]
			composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), &exprCaller);
			composer.FlushDiscard();										// [Iterator1..n Iterator List]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Iterator List Elem]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValues(1, nIterators + 1, &exprCaller);		// [List]
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);					// [Iterator1..n Iterator Last=nil]
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_ForEach(2, pDeclArgs.release(), &exprCaller);		// [Iterator1..n Iterator Last]
			composer.Add_DiscardValue(&exprCaller);							// [Iterator1..n Iterator]
			composer.Add_EvalIterator(0, &exprCaller);						// [Iterator1..n Iterator Idx]
			composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), &exprCaller);
			composer.FlushDiscard();										// [Iterator1..n Iterator]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Iterator Last]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValues(1, nIterators + 1, &exprCaller);		// [Last]
		}
		composer.Add_PopFrame(&exprCaller);
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
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	bool listFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(list));
	bool xlistFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
	bool createListFlag = listFlag || xlistFlag;
	if (declArgsOfBlock.empty()) {
		if (createListFlag) {
			composer.Add_CreateList(32, &exprCaller);						// [List=[]]
			PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [List]
			PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [List]
			pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
			exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);			// [List Bool]
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_JumpIfNot(&exprCaller);								// [List]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [List Elem]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_NoOperation(&exprCaller);
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);					// [Last=nil]
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);			// [Last Bool]
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_JumpIfNot(&exprCaller);								// [Last]
			composer.Add_DiscardValue(&exprCaller);							// []
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Last]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_NoOperation(&exprCaller);
		}
	} else if (declArgsOfBlock.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgsOfBlock.begin();
		composer.Add_PushFrame<Frame_Block>(&exprCaller);
		composer.Add_GenCounterIterator(&exprCaller);						// [Iterator]
		if (createListFlag) {
			composer.Add_CreateList(32, &exprCaller);						// [Iterator List=[]]
			PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator List]
			PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator List]
			pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
			exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);			// [Iterator List Bool]
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_JumpIfNot(&exprCaller);								// [Iterator List]
			composer.Add_EvalIterator(1, &exprCaller);						// [Iterator List Idx]
			composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), &exprCaller);
			composer.FlushDiscard();										// [Iterator List]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator List Elem]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValue(1, &exprCaller);						// [Last]
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);					// [Iterator Last=nil]
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			exprCaller.GetExprCdrFirst()->ComposeOrNil(composer);			// [Iterator Last Bool]
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_JumpIfNot(&exprCaller);								// [Iterator Last]
			composer.Add_DiscardValue(&exprCaller);							// [Iterator]
			composer.Add_EvalIterator(0, &exprCaller);						// [Iterator Idx]
			composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), &exprCaller);
			composer.FlushDiscard();										// [Iterator]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValue(1, &exprCaller);						// [Last]
		}
		composer.Add_PopFrame(&exprCaller);
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
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	bool listFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(list));
	bool xlistFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
	bool createListFlag = listFlag || xlistFlag;
	if (declArgsOfBlock.empty()) {
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);								// [Any]
			composer.Add_Cast(VTYPE_Number, false, &exprCaller);				// [Number]
			composer.Add_GenRangeIterator(&exprCaller);						// [Iterator]
		} else {
			composer.Add_GenCounterIterator(&exprCaller);					// [Iterator]
		}
		if (createListFlag) {
			composer.Add_CreateList(32, &exprCaller);						// [Iterator List=[]]
			PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator List]
			PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator List]
			pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_EvalIterator(1, &exprCaller);
			composer.FlushDiscard();										// [Iterator List]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator List Elem]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValue(1, &exprCaller);						// [List]
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);					// [Iteartor Last=nil]
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_EvalIterator(1, &exprCaller);
			composer.FlushDiscard();										// [Iterator Last]
			composer.Add_DiscardValue(&exprCaller);							// [Iterator]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValue(1, &exprCaller);						// [Last]
		}
	} else if (declArgsOfBlock.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgsOfBlock.begin();
		composer.Add_PushFrame<Frame_Block>(&exprCaller);
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);								// [Any]
			composer.Add_Cast(VTYPE_Number, false, &exprCaller);				// [Number]
			composer.Add_GenRangeIterator(&exprCaller);						// [Iterator]
		} else {
			composer.Add_GenCounterIterator(&exprCaller);					// [Iterator]
		}
		if (createListFlag) {
			composer.Add_CreateList(32, &exprCaller);						// [Iterator List=[]]
			PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator List]
			PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
			composer.Add_Jump(&exprCaller);
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			composer.Add_ListElem(0, xlistFlag, &exprCaller);				// [Iterator List]
			pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_EvalIterator(1, &exprCaller);						// [Iterator List idx]
			composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), &exprCaller);
			composer.FlushDiscard();										// [Iterator List]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator List Elem]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValue(1, &exprCaller);						// [List]
			composer.Add_PopFrame(&exprCaller);
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);					// [Iteartor Last=nil]
			PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
			PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
			composer.Add_EvalIterator(1, &exprCaller);						// [Iterator Last idx]
			composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), &exprCaller);
			composer.FlushDiscard();										// [Iterator Last]
			composer.Add_DiscardValue(&exprCaller);							// [Iterator]
			composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
			exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
			composer.EndRepeaterBlock();
			composer.Add_Jump(pPUnitOfLoop, &exprCaller);
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			composer.Add_RemoveValue(1, &exprCaller);						// [Last]
			composer.Add_PopFrame(&exprCaller);
		}
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
}

Gurax_ImplementStatement(break_)
{
	if (!composer.HasValidRepeaterInfo()) {
		Error::IssueWith(ErrorType::ContextError, exprCaller,
						 "break-statement can be used in a loop");
		return;
	}
	const Composer::RepeaterInfo& repeaterInfo = composer.GetRepeaterInfoCur();
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (repeaterInfo.GetPUnitOfBreak()) {
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
		} else {
			composer.Add_Value(Value::undefined(), &exprCaller);			// [undefined]
		}
		composer.Add_Break(repeaterInfo.GetPUnitOfBreak(), false, &exprCaller);
	} else if (repeaterInfo.GetPUnitOfBranch()) {
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);				// [nil]
		}
		composer.Add_Break(repeaterInfo.GetPUnitOfBranch(), true, &exprCaller);
	} else { // both PUnitOfBreak and PUnitOfBranch are nullptr
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
		} else {
			composer.Add_Value(Value::undefined(), &exprCaller);			// [undefined]
		}
		composer.Add_Break(nullptr, false, &exprCaller);
	}
}

// continue(value?)
Gurax_DeclareStatementAlias(continue_, "continue")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementStatement(continue_)
{
	if (!composer.HasValidRepeaterInfo()) {
		Error::IssueWith(ErrorType::ContextError, exprCaller,
						 "continue-statement can be used in a loop");
		return;
	}
	const Composer::RepeaterInfo& repeaterInfo = composer.GetRepeaterInfoCur();
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (repeaterInfo.GetPUnitOfLoop()) {
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
		} else {
			composer.Add_Value(Value::nil(), &exprCaller);				// [nil]
		}
		composer.Add_Continue(repeaterInfo.GetPUnitOfLoop(), &exprCaller);
	} else {
		if (pExprCdr) {
			pExprCdr->ComposeOrNil(composer);							// [Any]
		} else {
			composer.Add_Value(Value::undefined(), &exprCaller);			// [undefined]
		}
		composer.Add_Continue(repeaterInfo.GetPUnitOfLoop(), &exprCaller);
	}
}

// return(value?)
Gurax_DeclareStatementAlias(return_, "return")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementStatement(return_)
{
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (pExprCdr) {
		pExprCdr->ComposeOrNil(composer);							// [Any]
	} else {
		composer.Add_Value(Value::nil(), &exprCaller);				// [nil]
	}
	composer.Add_Return(&exprCaller);
}

// import(`name) {`block?}
Gurax_DeclareStatement(import)
{
	Declare(VTYPE_Module, Flag::None);
	DeclareArg("name", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(import)
{
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromExpr(*pExprCdr));
	if (!pDottedSymbol) {
		Error::Issue(ErrorType::SyntaxError, "invalid format of dotted-symbol");
		return;
	}
	bool mixInFlag = false;
	std::unique_ptr<SymbolList> pSymbolList(new SymbolList());
	if (exprCaller.HasExprOfBlock()) {
		const Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
		for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
			if (!pExpr->IsType<Expr_Identifier>()) {
				Error::Issue(ErrorType::ImportError,
							 "the block of import statement must contain symbols");
				return;
			}
			const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol();
			if (pSymbolList->DoesContain(pSymbol)) {
				Error::Issue(ErrorType::ImportError,
							 "duplicated symbol in the import's block: %s", pSymbol->GetName());
				return;
			}
			pSymbolList->push_back(pSymbol);
		}
		mixInFlag = pSymbolList->DoesContain(Gurax_SymbolMark(Mul));
	}
	composer.Add_Import(pDottedSymbol.release(), pSymbolList.release(), mixInFlag, &exprCaller);
}

// scope(frame?:Frame) {`block}
Gurax_DeclareStatement(scope)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("frame", VTYPE_Frame, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(scope)
{
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	if (pExprCdr) {
		pExprCdr->ComposeOrNil(composer);									// [Any]
		composer.Add_Cast(VTYPE_Frame, false, &exprCaller);					// [Frame]
		composer.Add_PushFrameFromStack(&exprCaller);
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);				// [Any]
		composer.Add_PopFrame(&exprCaller);
	} else {	
		composer.Add_PushFrame<Frame_Scope>(&exprCaller);
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);				// [Any]
		composer.Add_PopFrame(&exprCaller);
	}
}

// class(parent?:VType) {`block}
Gurax_DeclareStatementAlias(class_, "class")
{
	Declare(VTYPE_VType, Flag::None);
	DeclareArg("parent", VTYPE_VType, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(class_)
{
	composer.Add_CreateVType(&exprCaller);									// [VType]
}

void Statements::AssignToBasement(Frame& frame)
{
	frame.Assign(Gurax_CreateStatement(cond));
	frame.Assign(Gurax_CreateStatement(if_));
	frame.Assign(Gurax_CreateStatement(elsif));
	frame.Assign(Gurax_CreateStatement(else_));
	frame.Assign(Gurax_CreateStatement(try_));
	frame.Assign(Gurax_CreateStatement(catch_));
	frame.Assign(Gurax_CreateStatement(finally));
	frame.Assign(Gurax_CreateStatement(for_));
	frame.Assign(Gurax_CreateStatement(while_));
	frame.Assign(Gurax_CreateStatement(repeat));
	frame.Assign(Gurax_CreateStatement(break_));
	frame.Assign(Gurax_CreateStatement(continue_));
	frame.Assign(Gurax_CreateStatement(return_));
	frame.Assign(Gurax_CreateStatement(import));
	frame.Assign(Gurax_CreateStatement(scope));
	frame.Assign(Gurax_CreateStatement(class_));
}

}
