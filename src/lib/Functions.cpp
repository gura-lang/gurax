//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

#define Gurax_DeclareFunctionAlias(name, strName) \
class Function_##name : public Function { \
public: \
	Function_##name(const char* name_ = strName); \
	virtual Value* Eval(Frame& frame, const Argument& argument) const override; \
}; \
Function_##name::Function_##name(const char* name_) : Function(Function::Type::Function, name_) \

#define Gurax_DeclareFunction(name) Gurax_DeclareFunctionAlias(name, #name)

#define Gurax_ImplementFunction(name) \
Value* Function_##name::Eval(Frame& frame, const Argument& argument) const

#define Gurax_AssignFunction(name) \
frame.AssignFunction(new Function_##name())

#define Gurax_DeclareStatementAlias(name, strName) \
class Statement_##name : public Function { \
public: \
	Statement_##name(const char* name_ = strName); \
	virtual void Compose(Composer& composer, const Expr_Caller* pExprCaller) const override; \
}; \
Statement_##name::Statement_##name(const char* name_) : Function(Function::Type::Statement, name_) \

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

// while (cond) {block}
Gurax_DeclareStatementAlias(while_, "while")
{
}

Gurax_ImplementStatement(while_)
{
	size_t pos = composer.MarkPUnit();
	do {
		const Expr* pExpr = pExprCaller->GetExprCdrHead();
		pExpr->Compose(composer);
	} while (0);
	auto pPUnit = composer.Add_BranchIfNot(pExprCaller);
	pExprCaller->GetExprBlock()->Compose(composer);
	composer.Add_Jump(pExprCaller, composer.GetPUnitAt(pos));
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

// Print(str*:String):void
Gurax_DeclareFunction(Print)
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
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
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
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
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
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
