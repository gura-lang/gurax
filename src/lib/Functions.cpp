//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
// if (`cond) {`block}
Gurax_DeclareStatementAlias(if_, "if")
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(if_)
{
	SymbolList symbols;
	if (const Expr* pExprError = pExprCaller->GetTrailerSymbols(symbols)) {
		Error::IssueWith(ErrorType::SyntaxError, pExprError,
						 "invalid format of if-elsif-else sequence");
		return;
	}
	if (!symbols.empty()) {
		auto ppSymbol = symbols.begin();
		for ( ; ppSymbol + 1 != symbols.end(); ppSymbol++) {
			const Symbol* pSymbol = *ppSymbol;
			if (!pSymbol->IsIdentical(Gurax_Symbol(elsif))) {
				Error::IssueWith(ErrorType::SyntaxError, pExprCaller,
								 "invalid format of if-elsif-else sequence");
				return;
			}
		}
		const Symbol* pSymbol = *ppSymbol;
		if (!(pSymbol->IsIdentical(Gurax_Symbol(elsif)) || pSymbol->IsIdentical(Gurax_Symbol(else_)))) {
			Error::IssueWith(ErrorType::SyntaxError, pExprCaller,
							 "invalid format of if-elsif-else sequence");
			return;
		}
	}
	if (pExprCaller->CountExprCdr() != 1) {
		Error::IssueWith(ErrorType::ArgumentError, pExprCaller,
						 "if-statement takes one argument");
		return;
	}
	pExprCaller->GetExprCdrFirst()->Compose(composer);					// [ValueBool]
	if (pExprCaller->HasExprTrailer()) {
		if (pExprCaller->GetExprOfBlock()->HasExprElem()) {
			auto pPUnit1 = composer.AddF_JumpIfNot(pExprCaller);		// []
			pExprCaller->GetExprOfBlock()->Compose(composer);			// [Value]
			auto pPUnit2 = composer.AddF_Jump(pExprCaller);				// [Value]
			pPUnit1->SetPUnitBranch(composer.PeekPUnitCont());
			pExprCaller->GetExprTrailer()->Compose(composer);			// [Value]
			pPUnit2->SetPUnitCont(composer.PeekPUnitCont());
		} else {
			auto pPUnit = composer.AddF_NilJumpIf(pExprCaller);			// [] or [nil]
			pExprCaller->GetExprTrailer()->Compose(composer);			// [Value]
			pPUnit->SetPUnitBranch(composer.PeekPUnitCont());
		}
	} else {
		if (pExprCaller->GetExprOfBlock()->HasExprElem()) {
			auto pPUnit = composer.AddF_NilJumpIfNot(pExprCaller);		// [] or [nil]
			pExprCaller->GetExprOfBlock()->Compose(composer);			// [Value]
			pPUnit->SetPUnitBranch(composer.PeekPUnitCont());
		} else {
			composer.Add_PopValueToDiscard(pExprCaller);				// []
			composer.Add_Value(pExprCaller, Value::nil());				// [nil]
		}
	}
}

// elsif (`cond) {`block}
Gurax_DeclareStatementAlias(elsif, "elsif")
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::Trailer);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(elsif)
{
	if (pExprCaller->CountExprCdr() != 1) {
		Error::IssueWith(ErrorType::ArgumentError, pExprCaller,
						 "elsif-statement takes one argument");
		return;
	}
	pExprCaller->GetExprCdrFirst()->Compose(composer);					// [ValueBool]
	if (pExprCaller->HasExprTrailer()) {
		if (pExprCaller->GetExprOfBlock()->HasExprElem()) {
			auto pPUnit1 = composer.AddF_JumpIfNot(pExprCaller);		// []
			pExprCaller->GetExprOfBlock()->Compose(composer);			// [Value]
			auto pPUnit2 = composer.AddF_Jump(pExprCaller);				// [Value]
			pPUnit1->SetPUnitBranch(composer.PeekPUnitCont());
			pExprCaller->GetExprTrailer()->Compose(composer);			// [Value]
			pPUnit2->SetPUnitCont(composer.PeekPUnitCont());
		} else {
			auto pPUnit = composer.AddF_NilJumpIf(pExprCaller);			// [] or [nil]
			pExprCaller->GetExprTrailer()->Compose(composer);			// [Value]
			pPUnit->SetPUnitBranch(composer.PeekPUnitCont());
		}
	} else {
		if (pExprCaller->GetExprOfBlock()->HasExprElem()) {
			auto pPUnit = composer.AddF_NilJumpIfNot(pExprCaller);		// [] or [nil]
			pExprCaller->GetExprOfBlock()->Compose(composer);			// [Value]
			pPUnit->SetPUnitBranch(composer.PeekPUnitCont());
		} else {
			composer.Add_PopValueToDiscard(pExprCaller);				// []
			composer.Add_Value(pExprCaller, Value::nil());				// [nil]
		}
	}
}

// else ():trailer {`block}
Gurax_DeclareStatementAlias(else_, "else")
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::Trailer);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(else_)
{
	if (pExprCaller->CountExprCdr() != 0) {
		Error::IssueWith(ErrorType::ArgumentError, pExprCaller,
						 "else-statement takes no argument");
		return;
	}
	if (pExprCaller->HasExprTrailer()) {
		Error::IssueWith(ErrorType::SyntaxError, pExprCaller,
						 "invalid format of if-elsif-else sequence");
		return;
	}
	if (pExprCaller->GetExprOfBlock()->HasExprElem()) {
		pExprCaller->GetExprOfBlock()->Compose(composer);				// [Value]
	} else {
		composer.Add_Value(pExprCaller, Value::nil());					// [nil]
	}
}

// while (`cond) {`block}
Gurax_DeclareStatementAlias(while_, "while")
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(while_)
{
	if (pExprCaller->CountExprCdr() != 1) {
		Error::IssueWith(ErrorType::ArgumentError, pExprCaller,
						 "while-statement takes one argument");
		return;
	}
	const DeclArgOwner& declArgOwner = pExprCaller->GetExprOfBlock()->GetDeclCallable().GetDeclArgOwner();
	if (declArgOwner.empty()) {
		composer.Add_Value(pExprCaller, Value::nil());					// [ValueLast=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		pExprCaller->GetExprCdrFirst()->Compose(composer);				// [ValueLast ValueBool]
		auto pPUnit = composer.AddF_JumpIfNot(pExprCaller);				// [ValueLast]
		composer.Add_PopValueToDiscard(pExprCaller);					// []
		pExprCaller->GetExprOfBlock()->Compose(composer);				// [ValueLast]
		composer.Add_Jump(pExprCaller, pPUnitLoop);
		pPUnit->SetPUnitBranch(composer.PeekPUnitCont());
	} else if (declArgOwner.size() == 1) {
		DeclArgOwner::const_iterator ppDeclArg = declArgOwner.begin();
		composer.Add_PushFrame_Block(pExprCaller);
		composer.Add_Value(pExprCaller, Value::Zero());					// [ValueIdx=0 ValueLast=nil]
		composer.Add_Value(pExprCaller, Value::nil());					// [ValueIdx ValueLast=nil]
		const PUnit* pPUnitLoop = composer.PeekPUnitCont();
		pExprCaller->GetExprCdrFirst()->Compose(composer);				// [ValueIdx ValueLast ValueBool]
		auto pPUnit = composer.AddF_JumpIfNot(pExprCaller);				// [ValueIdx ValueLast]
		composer.Add_PopValueToDiscard(pExprCaller);					// [ValueIdx]
		composer.Add_AssignToDeclArg(pExprCaller, (*ppDeclArg)->Reference()); // [ValueIdx]
		composer.Add_Add(pExprCaller, 1);								// [ValueIdx=ValueIdx+1]
		pExprCaller->GetExprOfBlock()->Compose(composer);				// [ValueIdx ValueLast]
		composer.Add_Jump(pExprCaller, pPUnitLoop);
		pPUnit->SetPUnitBranch(composer.PeekPUnitCont());
		composer.Add_RemoveValue(pExprCaller, 1);						// [ValueLast]
		composer.Add_PopFrame(pExprCaller);
	} else {
		Error::IssueWith(ErrorType::ArgumentError, pExprCaller,
						 "invalid number of block parameters");
		return;
	}
}

// repeat (cnt?:number) {block}
Gurax_DeclareFunction(repeat)
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
	DeclareArg("cnt", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
}

Gurax_ImplementFunction(repeat)
{
	// Arguments
	ArgPicker args(argument);
	int cnt = args.IsDefined()? args.PickInt() : -1;
	// Block
	RefPtr<Argument> pArgOfBlock;
	RefPtr<Function> pFuncOfBlock(argument.CreateFunctionOfBlock(processor, pArgOfBlock));
	// Function body
	if (cnt < 0) {
		for (int i = 0; ; ++i) {
			ArgFeeder args(*pArgOfBlock);
			if (args.IsValid()) args.FeedValue(new Value_Number(i));
			pFuncOfBlock->DoEvalVoid(processor, *pArgOfBlock);
			if (Error::IsIssued()) return Value::nil();
		}
	} else {
		for (int i = 0; i < cnt; ++i) {
			ArgFeeder args(*pArgOfBlock);
			if (args.IsValid()) args.FeedValue(new Value_Number(i));
			pFuncOfBlock->DoEvalVoid(processor, *pArgOfBlock);
			if (Error::IsIssued()) return Value::nil();
		}
	}
	return Value::nil();
}

// Print(str*:String):void
Gurax_DeclareFunction(Print)
{
	DeclareCaller(VTYPE_Nil, DeclCallable::Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Print)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	Stream::COut->Print(valueList);
	return Value::nil();
}

// Printf(format:String, values*):void
Gurax_DeclareFunction(Printf)
{
	DeclareCaller(VTYPE_Nil, DeclCallable::Flag::None);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Printf)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	Stream::COut->PrintFmt(format, values);
	return Value::nil();
}

// Println(objs*):void
Gurax_DeclareFunction(Println)
{
	DeclareCaller(VTYPE_Nil, DeclCallable::Flag::None);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Println)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	Stream::COut->Println(values);
	return Value::nil();
}

void Functions::PrepareBasic(Frame& frame)
{
	Gurax_AssignStatement(if_);
	Gurax_AssignStatement(elsif);
	Gurax_AssignStatement(else_);
	Gurax_AssignStatement(while_);
	Gurax_AssignFunction(repeat);
	Gurax_AssignFunction(Print);
	Gurax_AssignFunction(Printf);
	Gurax_AssignFunction(Println);
}

}
