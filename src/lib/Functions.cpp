//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

// if (`cond) {`block}
Gurax_DeclareStatementAlias(if_, "if")
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
	DeclareArg("cond", VTYPE_Quote, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(if_)
{
	if (pExprCaller->CountExprCdr() != 1) {
		Error::Issue(ErrorType::ArgumentError, "if-statement takes one argument");
		return;
	}
	do {
		const Expr* pExpr = pExprCaller->GetExprCdrHead();
		pExpr->Compose(composer);									// [ValueBool]
	} while (0);
	if (pExprCaller->GetExprBlock()->HasExprElem()) {
		auto pPUnit = composer.AddF_NilBranchIfNot(pExprCaller);	// [] or [nil]
		pExprCaller->GetExprBlock()->Compose(composer);				// [Value]
		pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
	} else {
		composer.Add_PopToDiscard(pExprCaller);						// []
		composer.Add_Value(pExprCaller, Value::nil());				// [nil]
	}
}

// repeat (cnt?:number) {`block}
Gurax_DeclareStatement(repeat)
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
	DeclareArg("repeat", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
}

Gurax_ImplementStatement(repeat)
{
	size_t nArgs = pExprCaller->CountExprCdr();
	if (pExprCaller->CountExprCdr() > 1) {
		Error::Issue(ErrorType::ArgumentError, "repeat-statement takes zero or one argument");
		return;
	}
	if (nArgs == 0) {
		composer.Add_Value(pExprCaller, Value::nil());					// [ValueLast=nil]
		size_t pos = composer.MarkPUnit();
		composer.AddF_PopToDiscard(pExprCaller);						// []
		pExprCaller->GetExprBlock()->Compose(composer);					// [ValueLast]
		composer.AddF_Jump(pExprCaller, composer.GetPUnitAt(pos));
	} else if (nArgs == 1) {
		composer.Add_Value(pExprCaller, Value::nil());					// [ValueLast=nil]
		size_t pos = composer.MarkPUnit();
		do {
			const Expr* pExpr = pExprCaller->GetExprCdrHead();
			pExpr->Compose(composer);									// [ValueLast Value]
			composer.Add_Cast(pExprCaller, VTYPE_Number);				// [ValueLast ValueCount]
		} while (0);

		auto pPUnit = composer.AddF_BranchIfNot(pExprCaller);			// [ValueLast]

		composer.AddF_PopToDiscard(pExprCaller);						// []
		if (pExprCaller->GetExprBlock()->HasExprParam()) {
			// processing of block parameter here
		}
		pExprCaller->GetExprBlock()->Compose(composer);					// [ValueLast]
		composer.AddF_Jump(pExprCaller, composer.GetPUnitAt(pos));
		pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
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
		Error::Issue(ErrorType::ArgumentError, "while-statement takes one argument");
		return;
	}
	if (pExprCaller->GetExprBlock()->HasExprParam()) {
		composer.Add_Value(pExprCaller, Value::Zero());					// [ValueIdx=0 ValueLast=nil]
		composer.Add_Value(pExprCaller, Value::nil());					// [ValueIdx ValueLast=nil]
		size_t pos = composer.MarkPUnit();
		do {
			const Expr* pExpr = pExprCaller->GetExprCdrHead();
			pExpr->Compose(composer);									// [ValueIdx ValueLast ValueBool]
		} while (0);
		auto pPUnit = composer.AddF_BranchIfNot(pExprCaller);			// [ValueIdx ValueLast]
		composer.AddF_PopToDiscard(pExprCaller);						// [ValueIdx]
		
		pExprCaller->GetExprBlock()->Compose(composer);					// [ValueIdx ValueLast]
		composer.AddF_Jump(pExprCaller, composer.GetPUnitAt(pos));
		pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
		// delete ValueIdx here
	} else {
		composer.Add_Value(pExprCaller, Value::nil());					// [ValueLast=nil]
		size_t pos = composer.MarkPUnit();
		do {
			const Expr* pExpr = pExprCaller->GetExprCdrHead();
			pExpr->Compose(composer);									// [ValueLast ValueBool]
		} while (0);
		auto pPUnit = composer.AddF_BranchIfNot(pExprCaller);			// [ValueLast]
		composer.AddF_PopToDiscard(pExprCaller);						// []
		pExprCaller->GetExprBlock()->Compose(composer);					// [ValueLast]
		composer.AddF_Jump(pExprCaller, composer.GetPUnitAt(pos));
		pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
	}
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
	ArgAccessor args(argument);
	const ValueList& valueList = args.GetList();
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
	ArgAccessor args(argument);
	const char* format = args.GetString();
	const ValueList& valueList = args.GetList();
	// Function body
	Stream::COut->PrintFmt(format, valueList);
	return Value::nil();
}

// Println(objs*):void
Gurax_DeclareFunction(Println)
{
	DeclareCaller(VTYPE_Nil, DeclCallable::Flag::None);
	DeclareArg("objs", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Println)
{
	// Arguments
	ArgAccessor args(argument);
	const ValueList& valueList = args.GetList();
	// Function body
	Stream::COut->Println(valueList);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	Gurax_AssignStatement(if_);
	Gurax_AssignStatement(while_);
	Gurax_AssignFunction(Print);
	Gurax_AssignFunction(Printf);
	Gurax_AssignFunction(Println);
}

}
