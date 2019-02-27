//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

#define Gurax_DeclareFunctionAlias(name, strName) \
class Function_##name : public Function { \
public: \
	Function_##name(const char* name_ = strName); \
	virtual Value* Eval(const Argument& argument) const override; \
}; \
Function_##name::Function_##name(const char* name_) : Function(name_) \

#define Gurax_DeclareFunction(name) Gurax_DeclareFunctionAlias(name, #name)

#define Gurax_ImplementFunction(name) \
Value* Function_##name::Eval(const Argument& argument) const

#define Gurax_AssignFunction(name) \
frame.AssignFunction(new Function_##name())

#define Gurax_DeclareStatementAlias(name, strName) \
class Statement_##name : public Function { \
public: \
	Statement_##name(const char* name_ = strName); \
	virtual void Compose(Composer& composer, const Expr_Caller* pExprCaller) const override; \
}; \
Statement_##name::Statement_##name(const char* name_) : Function(name_) \

#define Gurax_DeclareStatement(name) Gurax_DeclareStatementAlias(name, #name)

#define Gurax_ImplementStatement(name) \
void Statement_##name::Compose(Composer& composer, const Expr_Caller* pExprCaller) const

#define Gurax_AssignStatement(name) \
frame.AssignFunction(new Statement_##name())

// if (cond) {block}
Gurax_DeclareStatementAlias(if_, "if")
{
}

Gurax_ImplementStatement(if_)
{
	do {
		const Expr* pExpr = pExprCaller->GetExprCdrHead();
		pExpr->Compose(composer);
	} while (0);
	auto pPUnit = composer.Add_BranchIfNot(pExprCaller);
	pExprCaller->GetExprBlock()->Compose(composer);
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

// repeat (cond) {block}
Gurax_DeclareStatement(repeat)
{
}

Gurax_ImplementStatement(repeat)
{
	do {
		const Expr* pExpr = pExprCaller->GetExprCdrHead();
		pExpr->Compose(composer);
	} while (0);
	auto pPUnit = composer.Add_BranchIfNot(pExprCaller);
	pExprCaller->GetExprBlock()->Compose(composer);
	composer.Add_Jump(pExprCaller, nullptr);
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

// Print(str:String):void
Gurax_DeclareFunction(Print)
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::OccurPattern::Once, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Print)
{
	ArgAccessor args(argument);
	const char* str = args.GetString();
	Stream::COut->Print(str);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	Gurax_AssignStatement(if_);
	Gurax_AssignStatement(repeat);
	Gurax_AssignFunction(Print);
}

}
