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
Function_##name::Function_##name(const char* name_) : Function(Function::Type::Function, name_) \

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

// repeat (cond) {block}
Gurax_DeclareStatement(repeat)
{
}

Gurax_ImplementStatement(repeat)
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
	ArgAccessor args(argument);
	const ValueList& valueList = args.GetList();
	for (auto pValue : valueList) {
		const char* str = dynamic_cast<Value_String*>(pValue)->GetString();
		Stream::COut->Print(str);
	}
	return Value::nil();
}

// Printf(format:String, arg*):void
Gurax_DeclareFunction(Printf)
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("arg", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Printf)
{
	ArgAccessor args(argument);
	const char* format = args.GetString();
	const ValueList& valueList = args.GetList();
	Stream::COut->PrintFmt(format, valueList);
	return Value::nil();
}

// Println(str*:String):void
Gurax_DeclareFunction(Println)
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Println)
{
	ArgAccessor args(argument);
	const ValueList& valueList = args.GetList();
	for (auto pValue : valueList) {
		const char* str = dynamic_cast<Value_String*>(pValue)->GetString();
		Stream::COut->Print(str);
	}
	Stream::COut->Println();
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	Gurax_AssignStatement(if_);
	Gurax_AssignStatement(repeat);
	Gurax_AssignFunction(Print);
	Gurax_AssignFunction(Printf);
	Gurax_AssignFunction(Println);
}

}
