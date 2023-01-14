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
	Operator* _pOperator;
public:
	Function_Unary(Operator* pOperator);
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const override;
};

Function_Unary::Function_Unary(Operator* pOperator) :
	Function(Function::Type::Statement, pOperator->GetSymbol(), Flag::None), _pOperator(pOperator)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
}

Value* Function_Unary::DoEval(Processor& processor, Argument& argument) const
{
	// Arguments
	ArgPicker args(argument);
	Value& value = args.PickValue();
	// Function body
	return _pOperator->EvalUnary(processor, value);
}

void Function_Unary::DoCompose(Composer& composer, Expr_Caller& exprCaller) const
{
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	pExprParam->ComposeOrNil(composer);											// [Any]
	composer.Add_UnaryOp(_pOperator, exprCaller);
}

//------------------------------------------------------------------------------
// Function_Binary
//------------------------------------------------------------------------------
class Function_Binary : public Function {
private:
	Operator* _pOperator;
public:
	Function_Binary(Operator* pOperator);
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const override;
};

Function_Binary::Function_Binary(Operator* pOperator) :
	Function(Function::Type::Statement, pOperator->GetSymbol(), Flag::None), _pOperator(pOperator)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("valueL", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("valueR", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Value* Function_Binary::DoEval(Processor& processor, Argument& argument) const
{
	// Arguments
	ArgPicker args(argument);
	Value& valueL = args.PickValue();
	Value& valueR = args.PickValue();
	// Function body
	return _pOperator->EvalBinary(processor, valueL, valueR);
}

void Function_Binary::DoCompose(Composer& composer, Expr_Caller& exprCaller) const
{
	Expr* pExprParam = exprCaller.GetExprParamFirst();
	pExprParam->ComposeOrNil(composer);											// [Any]
	pExprParam = pExprParam->GetExprNext();
	pExprParam->ComposeOrNil(composer);											// [Any]
	composer.Add_BinaryOp(_pOperator, exprCaller);
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// math.e as Number
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

// math.pi as Number
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
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
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
