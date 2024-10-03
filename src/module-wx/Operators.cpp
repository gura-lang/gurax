//==============================================================================
// Operators.cpp
//==============================================================================
#include "stdafx.h"
Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
Gurax_ImplementOpUnary(Neg, wxRealPoint)
{
	const auto& elem = Value_wxRealPoint::GetEntity(value);
	auto elemResult = -elem;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpUnary(Neg, wxPoint)
{
	const auto& elem = Value_wxPoint::GetEntity(value);
	auto elemResult = -elem;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxSize, wxSize)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxSize(elemResult);
}

Gurax_ImplementOpBinary(Add, wxRect, wxRect)
{
	const auto& elemL = Value_wxRect::GetEntity(valueL);
	const auto& elemR = Value_wxRect::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxRect(elemResult);
}

Gurax_ImplementOpBinary(Add, wxRealPoint, wxRealPoint)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_wxRealPoint::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxRealPoint, wxSize)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxSize, wxRealPoint)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxRealPoint::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxPoint, wxSize)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxSize, wxPoint)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Add, wxDateTime, wxDateSpan)
{
	const auto& elemL = Value_wxDateTime::GetEntity(valueL);
	const auto& elemR = Value_wxDateSpan::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxDateTime(elemResult);
}

Gurax_ImplementOpBinary(Add, wxDateTime, wxTimeSpan)
{
	const auto& elemL = Value_wxDateTime::GetEntity(valueL);
	const auto& elemR = Value_wxTimeSpan::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxDateTime(elemResult);
}

Gurax_ImplementOpBinary(Add, wxDateSpan, wxDateSpan)
{
	const auto& elemL = Value_wxDateSpan::GetEntity(valueL);
	const auto& elemR = Value_wxDateSpan::GetEntity(valueR);
	auto elemResult = elemL + elemR;
	return new Value_wxDateSpan(elemResult);
}

Gurax_ImplementOpBinary(Div, wxSize, Number)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL / elemR;
	return new Value_wxSize(elemResult);
}

Gurax_ImplementOpBinary(Div, wxRealPoint, Number)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL / elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Div, wxPoint, Number)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL / elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxVideoMode, wxVideoMode)
{
	const auto& elemL = Value_wxVideoMode::GetEntity(valueL);
	const auto& elemR = Value_wxVideoMode::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxSize, wxSize)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxRect, wxRect)
{
	const auto& elemL = Value_wxRect::GetEntity(valueL);
	const auto& elemR = Value_wxRect::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxRealPoint, wxRealPoint)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_wxRealPoint::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxGBPosition, wxGBPosition)
{
	const auto& elemL = Value_wxGBPosition::GetEntity(valueL);
	const auto& elemR = Value_wxGBPosition::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Eq, wxDateSpan, wxDateSpan)
{
	const auto& elemL = Value_wxDateSpan::GetEntity(valueL);
	const auto& elemR = Value_wxDateSpan::GetEntity(valueR);
	auto elemResult = elemL == elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Mul, wxSize, Number)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL * elemR;
	return new Value_wxSize(elemResult);
}

Gurax_ImplementOpBinary(Mul, Number, wxSize)
{
	const auto& elemL = Value_Number::GetNumber<int>(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL * elemR;
	return new Value_wxSize(elemResult);
}

Gurax_ImplementOpBinary(Mul, wxRect, wxRect)
{
	const auto& elemL = Value_wxRect::GetEntity(valueL);
	const auto& elemR = Value_wxRect::GetEntity(valueR);
	auto elemResult = elemL * elemR;
	return new Value_wxRect(elemResult);
}

Gurax_ImplementOpBinary(Mul, wxRealPoint, Number)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL * elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Mul, wxPoint, Number)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL * elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Mul, wxDateSpan, Number)
{
	const auto& elemL = Value_wxDateSpan::GetEntity(valueL);
	const auto& elemR = Value_Number::GetNumber<int>(valueR);
	auto elemResult = elemL * elemR;
	return new Value_wxDateSpan(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxVideoMode, wxVideoMode)
{
	const auto& elemL = Value_wxVideoMode::GetEntity(valueL);
	const auto& elemR = Value_wxVideoMode::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxSize, wxSize)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxRect, wxRect)
{
	const auto& elemL = Value_wxRect::GetEntity(valueL);
	const auto& elemR = Value_wxRect::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxRealPoint, wxRealPoint)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_wxRealPoint::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxGBPosition, wxGBPosition)
{
	const auto& elemL = Value_wxGBPosition::GetEntity(valueL);
	const auto& elemR = Value_wxGBPosition::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Ne, wxDateSpan, wxDateSpan)
{
	const auto& elemL = Value_wxDateSpan::GetEntity(valueL);
	const auto& elemR = Value_wxDateSpan::GetEntity(valueR);
	auto elemResult = elemL != elemR;
	return new Gurax::Value_Bool(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxSize, wxSize)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxSize(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxRealPoint, wxRealPoint)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_wxRealPoint::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxRealPoint, wxSize)
{
	const auto& elemL = Value_wxRealPoint::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxSize, wxRealPoint)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxRealPoint::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxRealPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxPoint, wxSize)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxSize::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxSize, wxPoint)
{
	const auto& elemL = Value_wxSize::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxPoint(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxDateTime, wxDateSpan)
{
	const auto& elemL = Value_wxDateTime::GetEntity(valueL);
	const auto& elemR = Value_wxDateSpan::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxDateTime(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxDateTime, wxTimeSpan)
{
	const auto& elemL = Value_wxDateTime::GetEntity(valueL);
	const auto& elemR = Value_wxTimeSpan::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxDateTime(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxDateTime, wxDateTime)
{
	const auto& elemL = Value_wxDateTime::GetEntity(valueL);
	const auto& elemR = Value_wxDateTime::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxTimeSpan(elemResult);
}

Gurax_ImplementOpBinary(Sub, wxDateSpan, wxDateSpan)
{
	const auto& elemL = Value_wxDateSpan::GetEntity(valueL);
	const auto& elemR = Value_wxDateSpan::GetEntity(valueR);
	auto elemResult = elemL - elemR;
	return new Value_wxDateSpan(elemResult);
}

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignOperators(Frame& frame)
{
	Gurax_AssignOpUnary(Neg, wxRealPoint);
	Gurax_AssignOpUnary(Neg, wxPoint);
	Gurax_AssignOpBinary(Add, wxSize, wxSize);
	Gurax_AssignOpBinary(Add, wxRect, wxRect);
	Gurax_AssignOpBinary(Add, wxRealPoint, wxRealPoint);
	Gurax_AssignOpBinary(Add, wxRealPoint, wxSize);
	Gurax_AssignOpBinary(Add, wxSize, wxRealPoint);
	Gurax_AssignOpBinary(Add, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Add, wxPoint, wxSize);
	Gurax_AssignOpBinary(Add, wxSize, wxPoint);
	Gurax_AssignOpBinary(Add, wxDateTime, wxDateSpan);
	Gurax_AssignOpBinary(Add, wxDateTime, wxTimeSpan);
	Gurax_AssignOpBinary(Add, wxDateSpan, wxDateSpan);
	Gurax_AssignOpBinary(Div, wxSize, Number);
	Gurax_AssignOpBinary(Div, wxRealPoint, Number);
	Gurax_AssignOpBinary(Div, wxPoint, Number);
	Gurax_AssignOpBinary(Eq, wxVideoMode, wxVideoMode);
	Gurax_AssignOpBinary(Eq, wxSize, wxSize);
	Gurax_AssignOpBinary(Eq, wxRect, wxRect);
	Gurax_AssignOpBinary(Eq, wxRealPoint, wxRealPoint);
	Gurax_AssignOpBinary(Eq, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Eq, wxGBPosition, wxGBPosition);
	Gurax_AssignOpBinary(Eq, wxDateSpan, wxDateSpan);
	Gurax_AssignOpBinary(Mul, wxSize, Number);
	Gurax_AssignOpBinary(Mul, Number, wxSize);
	Gurax_AssignOpBinary(Mul, wxRect, wxRect);
	Gurax_AssignOpBinary(Mul, wxRealPoint, Number);
	Gurax_AssignOpBinary(Mul, wxPoint, Number);
	Gurax_AssignOpBinary(Mul, wxDateSpan, Number);
	Gurax_AssignOpBinary(Ne, wxVideoMode, wxVideoMode);
	Gurax_AssignOpBinary(Ne, wxSize, wxSize);
	Gurax_AssignOpBinary(Ne, wxRect, wxRect);
	Gurax_AssignOpBinary(Ne, wxRealPoint, wxRealPoint);
	Gurax_AssignOpBinary(Ne, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Ne, wxGBPosition, wxGBPosition);
	Gurax_AssignOpBinary(Ne, wxDateSpan, wxDateSpan);
	Gurax_AssignOpBinary(Sub, wxSize, wxSize);
	Gurax_AssignOpBinary(Sub, wxRealPoint, wxRealPoint);
	Gurax_AssignOpBinary(Sub, wxRealPoint, wxSize);
	Gurax_AssignOpBinary(Sub, wxSize, wxRealPoint);
	Gurax_AssignOpBinary(Sub, wxPoint, wxPoint);
	Gurax_AssignOpBinary(Sub, wxPoint, wxSize);
	Gurax_AssignOpBinary(Sub, wxSize, wxPoint);
	Gurax_AssignOpBinary(Sub, wxDateTime, wxDateSpan);
	Gurax_AssignOpBinary(Sub, wxDateTime, wxTimeSpan);
	Gurax_AssignOpBinary(Sub, wxDateTime, wxDateTime);
	Gurax_AssignOpBinary(Sub, wxDateSpan, wxDateSpan);
}

Gurax_EndModuleScope(wx)
