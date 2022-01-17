//==============================================================================
// Operators.cpp
//==============================================================================
#include "stdafx.h"
Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
Gurax_ImplementOpBinary(Eq, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Add, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL - elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxPoint, wxSize)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueL);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxPoint, wxSize)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueL);
	auto elemResult = elemL - elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxSize, wxPoint)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxSize, wxPoint)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL - elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Div, wxPoint, Number)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueL);
	auto elemResult = elemL / elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Mul, wxPoint, Number)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueL);
	auto elemResult = elemL * elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Mul, Number, wxSize)
{
	const auto& elemL = Value_Number::GetNumber<int>(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueL);
	auto elemResult = elemL * elemR;
	return new Value_wxSize(elemResult);
}

Gurax_ImplementOpUnary(Neg, wxPoint)
{
	const auto& elem = Value_wxPoint::GetEntity(value);
	auto elemResult = -elem;
	return new Value_wxPoint(elemResult);
}

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignOperators(Frame& frame)
{
	Gurax_AssignOpBinary(Eq, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Ne, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Add, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Sub, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Add, wxPoint, wxSize);
	Gurax_AssignOpBinary(Sub, wxPoint, wxSize);
	Gurax_AssignOpBinary(Add, wxSize, wxPoint);
	Gurax_AssignOpBinary(Sub, wxSize, wxPoint);
	Gurax_AssignOpBinary(Div, wxPoint, Number);
	Gurax_AssignOpBinary(Mul, wxPoint, Number);
	Gurax_AssignOpBinary(Mul, Number, wxSize);
	Gurax_AssignOpUnary(Neg, wxPoint);
}

Gurax_EndModuleScope(wx)
