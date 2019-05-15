//==============================================================================
// VType_Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(Expr, children)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An iterator that returns `Expr` instance of the child elements.\n");
}

Gurax_ImplementPropertyGetter(Expr, children)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Iterator> pIterator(valueThis.GetExpr().EachChild());
	if (pIterator) return new Value_Iterator(pIterator.release());
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Expr#EachPUnit()
Gurax_DeclareMethod(Expr, EachPUnit)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns an iterator that enumerates `PUnit` instances stored in the target `Expr`.\n");
}

Gurax_ImplementMethod(Expr, EachPUnit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Function body
	RefPtr<Iterator> pIterator(expr.EachPUnit());
	return new Value_Iterator(pIterator.release());
}

// Expr#Eval()
Gurax_DeclareMethod(Expr, Eval)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Evaluates the target `Expr` and returns its result value.");
}

Gurax_ImplementMethod(Expr, Eval)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Function body
	Value* pValue = processor.ProcessExpr(expr);
	processor.ClearEvent();
	return pValue;
}

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

void VType_Expr::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Expr, children));
	// Assignment of method
	Assign(Gurax_CreateMethod(Expr, EachPUnit));
	Assign(Gurax_CreateMethod(Expr, Eval));
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
	if (GetExpr().GetPUnitFirst()) {
		str.Printf(":PUnit#%zu", GetExpr().GetPUnitFirst()->GetSeqId());
	}
	str += ">";
	return str;
}

String Value_Expr::ToStringDetail(const StringStyle& ss) const
{
	return GetExpr().ToString(ss);
}

}
