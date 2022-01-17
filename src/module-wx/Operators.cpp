//==============================================================================
// Operators.cpp
//==============================================================================
#include "stdafx.h"
Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
Gurax_ImplementOpBinary(Add, wxPoint, wxPoint)
{
	const auto& elemL = Value_wxPoint::GetEntity(valueL);
	const auto& elemR = Value_wxPoint::GetEntity(valueL);
	auto elemResult = elemL + elemR;
	return new Value_wxPoint(elemResult);
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
	//frame.Assign(Gurax_CreateFunction(Add_gurax));
	//frame.Assign(Gurax_CreateFunction(Neg_gurax));
}

Gurax_EndModuleScope(wx)
