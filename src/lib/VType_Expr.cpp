//==============================================================================
// VType_Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Expr#Eval()
Gurax_DeclareMethod(Expr, Eval)
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethod(Expr, Eval)
{
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	if (!expr.GetPUnitTop()) return Value::nil();
	processor.PushPUnit(nullptr);	// push a terminator so that Return exits the loop
	processor.Run(expr.GetPUnitTop());
	if (Error::IsIssued()) return Value::nil();
	return processor.PopValue();
}

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

void VType_Expr::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
	Assign(Gurax_CreateMethod(Expr, Eval));
}

//------------------------------------------------------------------------------
// Value_Expr
//------------------------------------------------------------------------------

}
