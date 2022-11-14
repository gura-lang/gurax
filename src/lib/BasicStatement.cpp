//==============================================================================
// BasicStatement.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// BasicStatement
//------------------------------------------------------------------------------
// cond (`cond, `exprTrue, `exprFalse?)
Gurax_DeclareStatement(cond)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, ArgOccur::Once, ArgFlag::None);
	DeclareArg("exprTrue", VTYPE_Quote, ArgOccur::Once, ArgFlag::None);
	DeclareArg("exprFalse", VTYPE_Quote, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Evaluates `exprTrue` and returns its result if `cond` is determined as `true`, and does `exprFalse` otherwise.
If `exprFalse` is omitted, it returns `nil` when `cond` turns out to be `false`.

This statement has the same behavior as `if` being used like below:

    if (cond) {exprTrue} else {exprFalse}
)**");
}

Gurax_ImplementStatement(cond)
{
	Expr* pExprCond = exprCaller.GetExprParamFirst();
	Expr* pExprTrue = pExprCond->GetExprNext();
	Expr* pExprFalse = pExprTrue->GetExprNext();
	pExprCond->ComposeOrNil(composer);											// [Bool]
	if (pExprFalse) {	// cond (cond, exprTrue, exprFalse)
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(PUnit::BranchMode::Empty, exprCaller);			// []
		pExprTrue->ComposeOrNil(composer);										// [Any]
		PUnit* pPUnitOfBranch2 = composer.PeekPUnitCont();
		composer.Add_Jump(exprCaller);											// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
		pExprFalse->ComposeOrNil(composer);										// [Any]
		pPUnitOfBranch2->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else {			// cond (cond, exprTrue)
		PUnit* pPUnitOfBranch1 = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(PUnit::BranchMode::Nil, exprCaller);				// [] or [nil]
		pExprTrue->ComposeOrNil(composer);										// [Any]
		pPUnitOfBranch1->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	composer.Add_NoOperation(exprCaller);										// [Any]
}

// if (`cond) {`block}
Gurax_DeclareStatementAlias(if_, "if")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Specifies an \"if\" block within a sequence of `if-elsif-else`.

If the result of `cond` is determined as `true`, the block would be executed,
and its evaluation result would become the returned value of the statement.

Otherwise, if the statement is followed by a trailer such as `elsif` and `else`, that would be evaluated.
If no trailer exists, the satement returns `nil` value.
)**");
}

Gurax_ImplementStatement(if_)
{
	using ExprsElsif = std::vector<Expr_Caller*>;
	using PUnitsOfBranch = std::vector<PUnit*>;
	ExprsElsif exprsElsif;
	Expr_Caller* pExprElse = nullptr;
	PUnitsOfBranch punitsOfBranch;
	for (Expr_Caller* pExpr = exprCaller.GetExprTrailer(); pExpr;
										pExpr = pExpr->GetExprTrailer()) {
		if (pExpr->IsStatement(Gurax_Symbol(elsif))) {
			exprsElsif.push_back(pExpr);
		} else if (pExpr->IsStatement(Gurax_Symbol(else_))) {
			if (pExprElse) {
				Error::IssueWith(ErrorType::SyntaxError, *pExpr,
					"else statement can appear once in try-catch-else-finally sequence");
				return;
			}
			pExprElse = pExpr;
		} else {
			Error::IssueWith(ErrorType::SyntaxError, *pExpr,
				"invalid format of if-elsif-else sequence");
			return;
		}
	}
	exprCaller.GetExprParamFirst()->ComposeOrNil(composer);						// [Bool]
	if (exprCaller.HasExprTrailer()) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(PUnit::BranchMode::Empty, exprCaller);			// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);					// [Any]
		punitsOfBranch.push_back(composer.PeekPUnitCont());
		composer.Add_Jump(exprCaller);											// [Any]
		pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		for (auto ppExprElsif = exprsElsif.begin();
							ppExprElsif != exprsElsif.end(); ppExprElsif++) {
			Expr_Caller* pExprElsif = *ppExprElsif;
			pExprElsif->GetExprParamFirst()->ComposeOrNil(composer);				// [Bool]
			if (pExprElse || ppExprElsif + 1 != exprsElsif.end()) {
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_JumpIfNot(PUnit::BranchMode::Empty, *pExprElsif);	// []
				pExprElsif->GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
				punitsOfBranch.push_back(composer.PeekPUnitCont());
				composer.Add_Jump(*pExprElsif);									// [Any]
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			} else {
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_JumpIfNot(PUnit::BranchMode::Nil, *pExprElsif);	// [] or [nil]
				pExprElsif->GetExprOfBlock()->ComposeOrNil(composer);			// [Any]
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
			}
		}
		if (pExprElse) {
			pExprElse->GetExprOfBlock()->ComposeOrNil(composer);				// [Any]
		}
		for (PUnit* pPUnitOfBranch : punitsOfBranch) {
			pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
		}
	} else {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_JumpIfNot(PUnit::BranchMode::Nil, exprCaller);				// [] or [nil]
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);					// [Any]
		pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	composer.Add_NoOperation(exprCaller);										// [Any]
}

// elsif (`cond) {`block}
Gurax_DeclareStatementAlias(elsif, "elsif")
{
	Declare(VTYPE_Any, Flag::Trailer);
	DeclareArg("cond", VTYPE_Quote, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Specifies an \"elsif\" block within a sequence of `if-elsif-else`.

If the result of `cond` is determined as `true`, the block would be executed,
and its evaluation result would become the returned value of the statement.

Otherwise, if the statement is followed by a trailer such as `elsif` and `else`, that would be evaluated.
If no trailer exists, the statement returns `nil` value.
)**");
}

Gurax_ImplementStatement(elsif)
{
}

// else ():trailer {`block}
Gurax_DeclareStatementAlias(else_, "else")
{
	Declare(VTYPE_Any, Flag::Trailer);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Specifies an \"else\" block within a sequence of `if-elsif-else` or `try-catch-else-finally`.
)**");
}

Gurax_ImplementStatement(else_)
{
}

// end ():trailer:endMarker
Gurax_DeclareStatement(end)
{
	Declare(VTYPE_Any, Flag::Trailer | Flag::EndMarker);
	AddHelp(Gurax_Symbol(en), u8R"**(
Specify an end of a block sequence like a closing brace bracket.

This function is supposed to be used in a template
with functions or statements that takes a block.

Example:

    ${for (i in 0..10)}
      ${if (i % 2 == 0)}
        ${i} is even
      ${else}
        ${i} is odd
      ${end}
    ${end}
)**");
}

Gurax_ImplementStatement(end)
{
}

// try {`block}
Gurax_DeclareStatementAlias(try_, "try")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Specifies a range of code in which exceptions could be caught
by following `catch` statement.
)**");
}

Gurax_ImplementStatement(try_)
{
	using ExprsCatch = std::vector<Expr_Caller*>;
	using PUnitsOfBranch = std::vector<PUnit*>;
	ExprsCatch exprsCatch;
	Expr_Caller* pExprCatchAny = nullptr;
	Expr_Caller* pExprElse = nullptr;
	Expr_Caller* pExprFinally = nullptr;
	PUnitsOfBranch punitsOfBranch;
	for (Expr_Caller* pExpr = exprCaller.GetExprTrailer(); pExpr;
										pExpr = pExpr->GetExprTrailer()) {
		if (pExpr->IsStatement(Gurax_Symbol(catch_))) {
			if (pExpr->HasExprParam()) {
				exprsCatch.push_back(pExpr);
			} else if (pExprCatchAny) {
				Error::IssueWith(ErrorType::SyntaxError, *pExpr,
					"catch-any statement can appear once in try-catch-else-finally sequence");
				return;
			} else {
				pExprCatchAny = pExpr;
			}
		} else if (pExpr->IsStatement(Gurax_Symbol(else_))) {
			if (pExprElse) {
				Error::IssueWith(ErrorType::SyntaxError, *pExpr,
					"else statement can appear once in try-catch-else-finally sequence");
				return;
			}
			pExprElse = pExpr;
		} else if (pExpr->IsStatement(Gurax_Symbol(finally))) {
			if (pExprFinally) {
				Error::IssueWith(ErrorType::SyntaxError, *pExpr,
					"finally statement can appear once in try-catch-else-finally sequence");
				return;
			}
			pExprFinally = pExpr;
		} else {
			Error::IssueWith(ErrorType::SyntaxError, *pExpr,
				"invalid format of try-catch-else-finally sequence");
			return;
		}
	}
	if (!exprCaller.HasExprTrailer()) {
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);					// [Any]
		return;
	}
	PUnit* pPUnitFinally = nullptr;
	PUnit* pPUnitOfBranch_Catch = composer.PeekPUnitCont();
	composer.Add_TryBlockBegin(exprCaller);										// [Any]
	if (pExprFinally) {
		pPUnitFinally = composer.PeekPUnitCont();								// [Any]
		composer.Add_ProcessSequence(exprCaller);
		composer.FlushDiscard();												// [Any]
		composer.Add_Return(exprCaller);
		pPUnitOfBranch_Catch->SetPUnitCont(composer.PeekPUnitCont());
	}
	composer.BeginTryBlock(pPUnitFinally);
	exprCaller.GetExprOfBlock()->ComposeOrNil(composer);						// [Any]
	if (pExprElse) {
		composer.Add_TryBlockEnd(exprCaller);									// [Any] or []
		composer.FlushDiscard();												// []
		pExprElse->GetExprOfBlock()->ComposeOrNil(composer);
		if (pExprFinally) composer.FlushDiscard();								// [Any] or []
		punitsOfBranch.push_back(composer.PeekPUnitCont());
		composer.Add_Jump(exprCaller);											// [Any]
	} else {
		punitsOfBranch.push_back(composer.PeekPUnitCont());
		composer.Add_TryBlockEnd(exprCaller);									// [Any] or []
	}
	pPUnitOfBranch_Catch->SetPUnitBranchDest(composer.PeekPUnitCont());
	for (Expr_Caller* pExprCatch : exprsCatch) {
		const DeclArgOwner& declArgsOfBlock =
				pExprCatch->GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
		if (declArgsOfBlock.size() > 1) {
			Error::IssueWith(ErrorType::ArgumentError, exprCaller, "invalid number of block parameters");
			goto errorDone;
		}
		const DeclArg* pDeclArg = declArgsOfBlock.empty()? nullptr : declArgsOfBlock.front();
		composer.Add_Value(Value::nil(), exprCaller);							// [nil]
		Expr* pExprParam = pExprCatch->GetExprParamFirst();
		for ( ; pExprParam; pExprParam = pExprParam->GetExprNext()) {
			pExprParam->ComposeOrNil(composer);									// [nil .. Any]
			composer.Add_Cast(VTYPE_ErrorType, *pExprParam);						// [nil .. ErrorType]
		}
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_JumpIfNoCatch(PUnit::BranchMode::Empty, *pExprCatch);		// [Error] or []
		if (pDeclArg) {
			composer.Add_PushFrame<Frame_Block>(*pExprCatch);
			composer.Add_AssignToDeclArg(pDeclArg->Reference(), *pExprCatch);
			composer.FlushDiscard();											// []
			pExprCatch->GetExprOfBlock()->ComposeOrNil(composer);
			if (pExprFinally) composer.FlushDiscard();							// [Any] or []
			composer.Add_PopFrame(*pExprCatch);
		} else {
			composer.FlushDiscard();
			pExprCatch->GetExprOfBlock()->ComposeOrNil(composer);
			if (pExprFinally) composer.FlushDiscard();							// [Any] or []
		}
		punitsOfBranch.push_back(composer.PeekPUnitCont());
		composer.Add_Jump(*pExprCatch);											// [Any]
		pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	if (pExprCatchAny) {
		const DeclArgOwner& declArgsOfBlock =
				pExprCatchAny->GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
		if (declArgsOfBlock.size() > 1) {
			Error::IssueWith(ErrorType::ArgumentError, exprCaller, "invalid number of block parameters");
			goto errorDone;
		}
		const DeclArg* pDeclArg = declArgsOfBlock.empty()? nullptr : declArgsOfBlock.front();
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_JumpIfNoCatchAny(PUnit::BranchMode::Nil, *pExprCatchAny);	// [Error] or [nil]
		if (pDeclArg) {
			composer.Add_PushFrame<Frame_Block>(*pExprCatchAny);
			composer.Add_AssignToDeclArg(pDeclArg->Reference(), *pExprCatchAny);
			composer.FlushDiscard();											// []
			pExprCatchAny->GetExprOfBlock()->ComposeOrNil(composer);
			if (pExprFinally) composer.FlushDiscard();							// [Any] or []
			composer.Add_PopFrame(*pExprCatchAny);
		} else {
			composer.FlushDiscard();
			pExprCatchAny->GetExprOfBlock()->ComposeOrNil(composer);
			if (pExprFinally) composer.FlushDiscard();							// [Any] or []
		}
		pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	} else {
		composer.Add_FailCatch(Value::nil(), exprCaller);						// [nil]
	}
	for (PUnit* pPUnitOfBranch : punitsOfBranch) {
		pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	}
	if (pExprFinally) {
		pPUnitFinally->SetPUnitBranchDest(composer.PeekPUnitCont());
		pExprFinally->SetPUnitFirst(composer.PeekPUnitCont());
		composer.BeginFinallyBlock(); // prevent inifite loop when "return" appears
		pExprFinally->GetExprOfBlock()->ComposeOrNil(composer);					// [Any]
		composer.EndFinallyBlock();
		pPUnitFinally->SetPUnitSentinel(composer.PeekPUnitCont());
		pExprFinally->SetPUnitEnd(composer.PeekPUnitCont());
	}
	composer.Add_NoOperation(exprCaller);										// [Any]
errorDone:
	composer.EndTryBlock();
}

// catch(errorType?:ErrorType) {`block}
Gurax_DeclareStatementAlias(catch_, "catch")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("errorType", VTYPE_ErrorType, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Executes the block when an exception that matches specified `errorType` occurs
in the preceding `try` statement.
If `errorType` is omitted, all exceptions that are not caught until here
will be handled.
)**");
}

Gurax_ImplementStatement(catch_)
{
}

// finally {`block}
Gurax_DeclareStatement(finally)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementStatement(finally)
{
}

// for (`cond+) {`block}
Gurax_DeclareStatementAlias(for_, "for")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Repeats evaluating `block` while all of the specified `cond` provide items.
The expression of `cond` is like `a in A` where `a` represents a variable name
and A a list or an iterator that provides one value at each loop.

Example:

    for (fruit in ['apple', 'grape', 'banana']) {
        Println(fruit)
    }

Two or more expressions of `cond` can also be specified:

    for (fruit in ['apple', 'grape', 'banana'], person in ['Thomas', 'Jane', 'Adam']) {
        Println(fruit, ' for ', person)
    }

The repetition continues until the shortest list or iterator expires.
The following example evaluates the loop twice:

    for (fruit in ['apple', 'grape', 'banana'], person in ['Thomas', 'Jane']) {
        Println(fruit, ' for ', person)
    }
)**");
}

Gurax_ImplementStatement(for_)
{
	RefPtr<DeclArgOwner> pDeclArgOwner(new DeclArgOwner());
	for (Expr* pExpr = exprCaller.GetExprParamFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
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
		RefPtr<DeclArg> pDeclArg(DeclArg::CreateFromExpr(pExprEx->GetExprLeft()));
		if (!pDeclArg) return;
		pDeclArgOwner->push_back(pDeclArg.release());
		pExprEx->GetExprRight().ComposeOrNil(composer);							// [Any]
		composer.Add_GenIterator(exprCaller);									// [Iterator]
	}
	size_t nIterators = pDeclArgOwner->size();
	bool iterFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(iter));
	bool xiterFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xiter));
	if (iterFlag || xiterFlag) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(exprCaller);
		composer.ComposeAsSequence(*exprCaller.GetExprOfBlock());
		composer.Add_SequenceEnd(*exprCaller.GetExprOfBlock());
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		composer.Add_GenIterator_for(
			exprCaller.GetExprOfBlock()->Reference(), pDeclArgOwner.release(), xiterFlag, exprCaller);	// [Iterator]
	} else {	
		const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
		bool listFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(list));
		bool xlistFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
		bool createListFlag = listFlag || xlistFlag;
		if (declArgsOfBlock.empty()) {
			composer.Add_PushFrame<Frame_Block>(exprCaller);
			if (createListFlag) {
				composer.Add_CreateList(32, exprCaller);						// [Iterator1..n List=[]]
				PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator1..n List]
				PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator1..n List]
				pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_ForEach(1, pDeclArgOwner.release(), exprCaller);	// [Iterator1..n List]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n List Elem]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValues(1, nIterators, exprCaller);			// [List]
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [Iterator1..n Last=nil]
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_ForEach(1, pDeclArgOwner.release(), exprCaller);	// [Iterator1..n Last]
				composer.Add_DiscardValue(exprCaller);							// [Iterator1..n]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Last]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValues(1, nIterators, exprCaller);			// [Last]
			}
			composer.Add_PopFrame(exprCaller);
		} else if (declArgsOfBlock.size() == 1) {
			auto ppDeclArg = declArgsOfBlock.begin();
			composer.Add_PushFrame<Frame_Block>(exprCaller);
			composer.Add_GenIterator_Counter(exprCaller);						// [Iterator1..n Iterator]
			if (createListFlag) {
				composer.Add_CreateList(32, exprCaller);						// [Iterator1..n Iterator List=[]]
				PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator1..n Iterator List]
				PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator1..n Iterator List]
				pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_ForEach(2, pDeclArgOwner.release(), exprCaller);	// [Iterator1..n Iterator List]
				composer.Add_EvalIterator(1, false, exprCaller);				// [Iterator1..n Iterator List Idx]
				composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), exprCaller);
				composer.FlushDiscard();										// [Iterator1..n Iterator List]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Iterator List Elem]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValues(1, nIterators + 1, exprCaller);		// [List]
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [Iterator1..n Iterator Last=nil]
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_ForEach(2, pDeclArgOwner.release(), exprCaller);	// [Iterator1..n Iterator Last]
				composer.Add_DiscardValue(exprCaller);							// [Iterator1..n Iterator]
				composer.Add_EvalIterator(0, false, exprCaller);				// [Iterator1..n Iterator Idx]
				composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), exprCaller);
				composer.FlushDiscard();										// [Iterator1..n Iterator]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator1..n Iterator Last]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValues(1, nIterators + 1, exprCaller);		// [Last]
			}
			composer.Add_PopFrame(exprCaller);
		} else {
			Error::IssueWith(ErrorType::ArgumentError, exprCaller,
							 "invalid number of block parameters");
			return;
		}
	}
}

// while (`cond) {`block}
Gurax_DeclareStatementAlias(while_, "while")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cond", VTYPE_Quote, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(
Repeats evaluating `block` while the result of `cond` is judged as `true`.

Example:

    n = 0
    while (n < 10) {
        Println(n)
        n += 1
    }
)**");
}

Gurax_ImplementStatement(while_)
{
	bool iterFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(iter));
	bool xiterFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xiter));
	if (iterFlag || xiterFlag) {
		Expr& exprCriteria = *exprCaller.GetExprParamFirst();
		Expr_Block& exprOfBlock = *exprCaller.GetExprOfBlock();
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(exprCaller);
		composer.ComposeAsSequence(exprCriteria);
		composer.Add_SequenceEnd(exprCriteria);
		composer.ComposeAsSequence(exprOfBlock);
		composer.Add_SequenceEnd(exprOfBlock);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		composer.Add_GenIterator_while(
			exprCriteria.Reference(), exprOfBlock.Reference(), xiterFlag, exprCaller);	// [Iterator]
	} else {	
		const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
		bool listFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(list));
		bool xlistFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
		bool createListFlag = listFlag || xlistFlag;
		if (declArgsOfBlock.empty()) {
			if (createListFlag) {
				composer.Add_CreateList(32, exprCaller);						// [List=[]]
				PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [List]
				PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [List]
				pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
				exprCaller.GetExprParamFirst()->ComposeOrNil(composer);			// [List Bool]
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_JumpIfNot(PUnit::BranchMode::Empty, exprCaller);	// [List]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [List Elem]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_NoOperation(exprCaller);
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [Last=nil]
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				exprCaller.GetExprParamFirst()->ComposeOrNil(composer);			// [Last Bool]
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_JumpIfNot(PUnit::BranchMode::Empty, exprCaller);	// [Last]
				composer.Add_DiscardValue(exprCaller);							// []
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Last]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_NoOperation(exprCaller);
			}
		} else if (declArgsOfBlock.size() == 1) {
			auto ppDeclArg = declArgsOfBlock.begin();
			composer.Add_PushFrame<Frame_Block>(exprCaller);
			composer.Add_GenIterator_Counter(exprCaller);						// [Iterator]
			if (createListFlag) {
				composer.Add_CreateList(32, exprCaller);						// [Iterator List=[]]
				PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator List]
				PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator List]
				pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
				exprCaller.GetExprParamFirst()->ComposeOrNil(composer);			// [Iterator List Bool]
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_JumpIfNot(PUnit::BranchMode::Empty, exprCaller);	// [Iterator List]
				composer.Add_EvalIterator(1, false, exprCaller);				// [Iterator List Idx]
				composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), exprCaller);
				composer.FlushDiscard();										// [Iterator List]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator List Elem]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValue(1, exprCaller);						// [Last]
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [Iterator Last=nil]
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				exprCaller.GetExprParamFirst()->ComposeOrNil(composer);			// [Iterator Last Bool]
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_JumpIfNot(PUnit::BranchMode::Empty, exprCaller);	// [Iterator Last]
				composer.Add_DiscardValue(exprCaller);							// [Iterator]
				composer.Add_EvalIterator(0, false, exprCaller);				// [Iterator Idx]
				composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), exprCaller);
				composer.FlushDiscard();										// [Iterator]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValue(1, exprCaller);						// [Last]
			}
			composer.Add_PopFrame(exprCaller);
		} else {
			Error::IssueWith(ErrorType::ArgumentError, exprCaller,
							 "invalid number of block parameters");
			return;
		}
	}
}

// repeat (cnt?:number) {block}
Gurax_DeclareStatement(repeat)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Repeats evaluating `block` for `cnt` times.
)**");
}

Gurax_ImplementStatement(repeat)
{
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	bool iterFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(iter));
	bool xiterFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xiter));
	if (iterFlag || xiterFlag) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(exprCaller);
		composer.ComposeAsSequence(*exprCaller.GetExprOfBlock());
		composer.Add_SequenceEnd(*exprCaller.GetExprOfBlock());
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
			composer.Add_Cast(VTYPE_Number, exprCaller);						// [Number]
			composer.Add_GenIterator_repeat(
				exprCaller.GetExprOfBlock()->Reference(), true, xiterFlag, exprCaller);	// [Iterator]
		} else {
			composer.Add_GenIterator_repeat(
				exprCaller.GetExprOfBlock()->Reference(), false, xiterFlag, exprCaller); // [Iterator]
		}
	} else {
		const DeclArgOwner& declArgsOfBlock = exprCaller.GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
		bool listFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(list));
		bool xlistFlag = exprCaller.GetAttr().IsSet(Gurax_Symbol(xlist));
		bool createListFlag = listFlag || xlistFlag;
		if (declArgsOfBlock.empty()) {
			if (pExprParam) {
				pExprParam->ComposeOrNil(composer);								// [Any]
				composer.Add_Cast(VTYPE_Number, exprCaller);					// [Number]
				composer.Add_GenIterator_Range(exprCaller);						// [Iterator]
			} else {
				composer.Add_GenIterator_Counter(exprCaller);					// [Iterator]
			}
			if (createListFlag) {
				composer.Add_CreateList(32, exprCaller);						// [Iterator List=[]]
				PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator List]
				PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator List]
				pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_EvalIterator(1, false, exprCaller);
				composer.FlushDiscard();										// [Iterator List]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator List Elem]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValue(1, exprCaller);						// [List]
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [Iteartor Last=nil]
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_EvalIterator(1, false, exprCaller);
				composer.FlushDiscard();										// [Iterator Last]
				composer.Add_DiscardValue(exprCaller);							// [Iterator]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValue(1, exprCaller);						// [Last]
			}
		} else if (declArgsOfBlock.size() == 1) {
			auto ppDeclArg = declArgsOfBlock.begin();
			composer.Add_PushFrame<Frame_Block>(exprCaller);
			if (pExprParam) {
				pExprParam->ComposeOrNil(composer);								// [Any]
				composer.Add_Cast(VTYPE_Number, exprCaller);					// [Number]
				composer.Add_GenIterator_Range(exprCaller);						// [Iterator]
			} else {
				composer.Add_GenIterator_Counter(exprCaller);					// [Iterator]
			}
			if (createListFlag) {
				composer.Add_CreateList(32, exprCaller);						// [Iterator List=[]]
				PUnit* pPUnitOfSkipFirst = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfBreak = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator List]
				PUnit* pPUnitOfBreakBranch = composer.PeekPUnitCont();
				composer.Add_Jump(exprCaller);
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				composer.Add_ListElem(0, xlistFlag, false, exprCaller);			// [Iterator List]
				pPUnitOfSkipFirst->SetPUnitBranchDest(composer.PeekPUnitCont());
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_EvalIterator(1, false, exprCaller);				// [Iterator List idx]
				composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), exprCaller);
				composer.FlushDiscard();										// [Iterator List]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator List Elem]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);					// [Iterator List]
				pPUnitOfBreakBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValue(1, exprCaller);						// [List]
				composer.Add_PopFrame(exprCaller);								// [List]
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [Iteartor Last=nil]
				PUnit* pPUnitOfLoop = composer.PeekPUnitCont();
				PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
				composer.Add_EvalIterator(1, false, exprCaller);				// [Iterator Last idx]
				composer.Add_AssignToDeclArg((*ppDeclArg)->Reference(), exprCaller);
				composer.FlushDiscard();										// [Iterator Last]
				composer.Add_DiscardValue(exprCaller);							// [Iterator]
				composer.BeginRepeaterBlock(pPUnitOfLoop, pPUnitOfBranch, nullptr);
				exprCaller.GetExprOfBlock()->ComposeOrNil(composer);			// [Iterator Last]
				composer.EndRepeaterBlock();
				composer.Add_Jump(pPUnitOfLoop, exprCaller);					// [Iterator Last]
				pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
				composer.Add_RemoveValue(1, exprCaller);						// [Last]
				composer.Add_PopFrame(exprCaller);								// [Last]
			}
		} else {
			Error::IssueWith(ErrorType::ArgumentError, exprCaller,
							 "invalid number of block parameters");
			return;
		}
	}
}

// break(value?)
Gurax_DeclareStatementAlias(break_, "break")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Exits the most inside loop such as `for`, `while` and `repeat`.
)**");
}

Gurax_ImplementStatement(break_)
{
	if (!composer.HasValidRepeaterInfo()) {
		Error::IssueWith(ErrorType::ContextError, exprCaller,
						 "break-statement can only be used in a loop");
		return;
	}
	const Composer::RepeaterInfo& repeaterInfo = composer.GetRepeaterInfoCur();
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	if (repeaterInfo.GetPUnitOfBreak()) {
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
		} else {
			composer.Add_Value(Value::undefined(), exprCaller);					// [undefined]
		}
		composer.Add_Break(repeaterInfo.GetPUnitOfBreak(), false, exprCaller);	// [Any or undefined]
	} else if (repeaterInfo.GetPUnitOfBranch()) {
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
		} else {
			composer.Add_Value(Value::nil(), exprCaller);						// [nil]
		}
		composer.Add_Break(repeaterInfo.GetPUnitOfBranch(), true, exprCaller);	// [Any or nil]
	} else { // both PUnitOfBreak and PUnitOfBranch are nullptr
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
		} else {
			composer.Add_Value(Value::undefined(), exprCaller);					// [undefined]
		}
		composer.Add_Break(nullptr, false, exprCaller);							// [Any or undefined]
	}
}

// continue(value?)
Gurax_DeclareStatementAlias(continue_, "continue")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementStatement(continue_)
{
	if (!composer.HasValidRepeaterInfo()) {
		Error::IssueWith(ErrorType::ContextError, exprCaller,
						 "continue-statement can only be used in a loop");
		return;
	}
	const Composer::RepeaterInfo& repeaterInfo = composer.GetRepeaterInfoCur();
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	if (repeaterInfo.GetPUnitOfLoop()) {
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
		} else {
			composer.Add_Value(Value::nil(), exprCaller);						// [nil]
		}
		composer.Add_Continue(repeaterInfo.GetPUnitOfLoop(), exprCaller);		// [Any or nil]
	} else {
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
		} else {
			composer.Add_Value(Value::undefined(), exprCaller);					// [undefined]
		}
		composer.Add_Continue(nullptr, exprCaller);								// [Any or undefined]
	}
}

// return(value?)
Gurax_DeclareStatementAlias(return_, "return")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementStatement(return_)
{
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	if (composer.HasValidTryInfo()) {
		const Composer::TryInfo& tryInfo = composer.GetTryInfoCur();
		if (tryInfo.IsWithinFinally()) {
			Error::IssueWith(ErrorType::UnimplementedError, exprCaller,
					"return statement within finally is not allowed");
		} else {
			if (pExprParam) {
				pExprParam->ComposeOrNil(composer);								// [Any]
			} else {
				composer.Add_Value(Value::nil(), exprCaller);					// [nil]
			}
			if (const PUnit* pPUnitOfFinally = tryInfo.GetPUnitOfFinally()) {
				composer.Add_Jump(pPUnitOfFinally, exprCaller);
			} else {
				composer.Add_Return(exprCaller);
			}
		}
	} else {
		if (pExprParam) {
			pExprParam->ComposeOrNil(composer);									// [Any]
		} else {
			composer.Add_Value(Value::nil(), exprCaller);						// [nil]
		}
		composer.Add_Return(exprCaller);
	}
}

// import(`name):[binary,overwrite] {`block?}
Gurax_DeclareStatement(import)
{
	Declare(VTYPE_Module, Flag::None);
	DeclareArg("name", VTYPE_Quote, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(binary));
	DeclareAttrOpt(Gurax_Symbol(overwrite));
	DeclareBlock(BlkOccur::ZeroOrOnce, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementStatement(import)
{
	Expr* pExprArg = exprCaller.GetExprParamFirst();
	const Attribute& attr = exprCaller.GetAttr();
	bool symbolForModuleFlag = true;
	if (pExprArg->IsType<Expr_UnaryOp>()) {
		Expr_UnaryOp* pExprEx = dynamic_cast<Expr_UnaryOp*>(pExprArg);
		if (pExprEx->GetOperator()->IsType(OpType::Neg)) {
			pExprArg = &pExprEx->GetExprChild();
			symbolForModuleFlag = false;
		}
	}
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromExpr(*pExprArg));
	if (!pDottedSymbol) {
		Error::IssueWith(ErrorType::SyntaxError, *pExprArg,
								"invalid format of dotted-symbol");
		return;
	}
	bool binaryFlag = attr.IsSet(Gurax_Symbol(binary));
	bool mixInFlag = false;
	bool overwriteFlag = attr.IsSet(Gurax_Symbol(overwrite));
	std::unique_ptr<SymbolList> pSymbolList(new SymbolList());
	if (exprCaller.HasExprOfBlock()) {
		const Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
		for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
			if (!pExpr->IsType<Expr_Identifier>()) {
				Error::IssueWith(ErrorType::ImportError, *pExpr,
							 "the block of import statement must contain symbols");
				return;
			}
			const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol();
			if (pSymbolList->DoesContain(pSymbol)) {
				Error::IssueWith(ErrorType::ImportError, *pExpr,
							 "duplicated symbol in the import's block: %s", pSymbol->GetName());
				return;
			}
			pSymbolList->push_back(pSymbol);
		}
		mixInFlag = pSymbolList->DoesContain(Gurax_SymbolMark(Mul));
	}
	composer.Add_Import(pDottedSymbol.release(), pSymbolList.release(),
						binaryFlag, mixInFlag, overwriteFlag, symbolForModuleFlag, exprCaller);
}

// scope(scp?:Scope) {`block}
Gurax_DeclareStatement(scope)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("scp", VTYPE_Scope, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
}

Gurax_ImplementStatement(scope)
{
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	if (pExprParam) {
		pExprParam->ComposeOrNil(composer);										// [Any]
		composer.Add_Cast(VTYPE_Scope, exprCaller);								// [Frame]
		composer.Add_PushFrameFromStack(exprCaller);							// []
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);					// [Any]
		composer.Add_PopFrame(exprCaller);										// [Any]
	} else {	
		composer.Add_PushFrame<Frame_Scope>(exprCaller);
		exprCaller.GetExprOfBlock()->ComposeOrNil(composer);					// [Any]
		composer.Add_PopFrame(exprCaller);										// [Any]
	}
}

// class(parent?:VType) {`block}
Gurax_DeclareStatementAlias(class_, "class")
{
	Declare(VTYPE_VType, Flag::None);
	DeclareArg("parent", VTYPE_VType, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementStatement(class_)
{
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	if (pExprParam) {
		pExprParam->ComposeOrNil(composer);										// [Any]
		composer.Add_Cast(VTYPE_VType, exprCaller);								// [VTypeInh]
		composer.Add_CreateVType(true, exprCaller);								// [VType]
	} else {
		composer.Add_CreateVType(false, exprCaller);							// [VType]
	}
	exprCaller.GetExprOfBlock()->GetExprLinkElem().ComposeWithinClass(composer, nullptr, false); // [VType]
}

// struct {`block}
Gurax_DeclareStatementAlias(struct_, "struct")
{
	Declare(VTYPE_VType, Flag::None);
	DeclareBlock(BlkOccur::Once, BlkFlag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementStatement(struct_)
{
	composer.Add_CreateVType(false, exprCaller);								// [VType]
	exprCaller.GetExprOfBlock()->GetExprLinkElem().ComposeWithinClass(composer, nullptr, true); // [VType]
	composer.Add_CompleteStruct(exprCaller);									// [VType]
}

void BasicStatement::Prepare(Frame& frame)
{
	frame.Assign(Gurax_CreateStatement(cond));
	frame.Assign(Gurax_CreateStatement(if_));
	frame.Assign(Gurax_CreateStatement(elsif));
	frame.Assign(Gurax_CreateStatement(else_));
	frame.Assign(Gurax_CreateStatement(end));
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
	frame.Assign(Gurax_CreateStatement(struct_));
}

}
