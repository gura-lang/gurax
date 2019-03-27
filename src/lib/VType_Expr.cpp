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

// Expr#PrintPUnit(indent?:String):void
Gurax_DeclareMethod(Expr, PrintPUnit)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("indent", VTYPE_String, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementMethod(Expr, PrintPUnit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Arguments
	ArgPicker args(argument);
	const char* indent = args.IsDefined()? args.PickString() : "";
	// Function body
	expr.PrintPUnit(StringStyle().SetMargin(indent));
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
