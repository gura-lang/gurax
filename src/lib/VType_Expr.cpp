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
	return expr.DoEval(processor);
}

// Expr#PrintPUnit():void
Gurax_DeclareMethod(Expr, PrintPUnit)
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethod(Expr, PrintPUnit)
{
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	expr.PrintPUnit();
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

void VType_Expr::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
	// Assignment of method
	Assign(Gurax_CreateMethod(Expr, Eval));
	Assign(Gurax_CreateMethod(Expr, PrintPUnit));
}

//------------------------------------------------------------------------------
// Value_Expr
//------------------------------------------------------------------------------
String Value_Expr::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":`(";
	str += GetExpr().ToString(StringStyle().Cram());
	str += ")";
	if (GetExpr().GetPUnitTop()) {
		str.Printf(":PUnit#%zu", GetExpr().GetPUnitTop()->GetSeqId());
	}
	str += ">";
	return str;
}

String Value_Expr::ToStringDetail(const StringStyle& ss) const
{
	return GetExpr().ToString(ss);
}

}
