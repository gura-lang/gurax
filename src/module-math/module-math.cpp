//==============================================================================
// module-math.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(math)

//------------------------------------------------------------------------------
// Function_Unary
//------------------------------------------------------------------------------
class Function_Unary : public Function {
private:
	const Operator* _pOperator;
public:
	Function_Unary(const Operator* pOperator);
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const override;
};

Function_Unary::Function_Unary(const Operator* pOperator) :
	Function(Function::Type::Statement, pOperator->GetSymbol()), _pOperator(pOperator)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
}

void Function_Unary::DoCompose(Composer& composer, Expr_Caller& exprCaller) const
{
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	pExprCdr->ComposeOrNil(composer);							// [Any]
	composer.Add_UnaryOp(_pOperator, &exprCaller);
}

//------------------------------------------------------------------------------
// Function_Binary
//------------------------------------------------------------------------------
class Function_Binary : public Function {
private:
	const Operator* _pOperator;
public:
	Function_Binary(const Operator* pOperator);
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const override;
};

Function_Binary::Function_Binary(const Operator* pOperator) :
	Function(Function::Type::Statement, pOperator->GetSymbol()), _pOperator(pOperator)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("valueL", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("valueR", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

void Function_Binary::DoCompose(Composer& composer, Expr_Caller& exprCaller) const
{
	Expr* pExprCdr = exprCaller.GetExprCdrFirst();
	pExprCdr->ComposeOrNil(composer);							// [Any]
	pExprCdr = pExprCdr->GetExprNext();
	pExprCdr->ComposeOrNil(composer);							// [Any]
	composer.Add_BinaryOp(_pOperator, &exprCaller);
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// math.e:Number
Gurax_DeclareModuleProperty_R(e)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementModulePropertyGetter(e)
{
	static Value* pValue = nullptr;
	if (!pValue) pValue = new Value_Number(Math::E);
	return pValue->Reference();
}

// math.pi:Number
Gurax_DeclareModuleProperty_R(pi)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementModulePropertyGetter(pi)
{
	static Value* pValue = nullptr;
	if (!pValue) pValue = new Value_Number(Math::PI);
	return pValue->Reference();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	// Assignment of function
	Assign(new Function_Unary(Operator::math_Abs));
	Assign(new Function_Unary(Operator::math_Acos));
	Assign(new Function_Unary(Operator::math_Arg));
	Assign(new Function_Unary(Operator::math_Asin));
	Assign(new Function_Unary(Operator::math_Atan));
	Assign(new Function_Binary(Operator::math_Atan2));
	Assign(new Function_Unary(Operator::math_Ceil));
	Assign(new Function_Unary(Operator::math_Conj));
	Assign(new Function_Unary(Operator::math_Cos));
	Assign(new Function_Unary(Operator::math_Cosh));
	Assign(new Function_Unary(Operator::math_Covariance));
	Assign(new Function_Unary(Operator::math_Cross));
	Assign(new Function_Unary(Operator::math_Delta));
	Assign(new Function_Unary(Operator::math_Dot));
	Assign(new Function_Unary(Operator::math_Exp));
	Assign(new Function_Unary(Operator::math_Floor));
	Assign(new Function_Binary(Operator::math_Hypot));
	Assign(new Function_Unary(Operator::math_Imag));
	Assign(new Function_Unary(Operator::math_Log));
	Assign(new Function_Unary(Operator::math_Log10));
	Assign(new Function_Unary(Operator::math_Norm));
	Assign(new Function_Unary(Operator::math_Real));
	Assign(new Function_Unary(Operator::math_Relu));
	Assign(new Function_Unary(Operator::math_Sigmoid));
	Assign(new Function_Unary(Operator::math_Sin));
	Assign(new Function_Unary(Operator::math_Sinh));
	Assign(new Function_Unary(Operator::math_Sqrt));
	Assign(new Function_Unary(Operator::math_Tan));
	Assign(new Function_Unary(Operator::math_Tanh));
	Assign(new Function_Unary(Operator::math_Unitstep));
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(e));
	Assign(Gurax_CreateModuleProperty(pi));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(math)
