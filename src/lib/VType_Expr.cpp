//==============================================================================
// VType_Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

// Expr#Eval()
Gurax_DeclareMethod(Expr, Eval)
{
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
}

Gurax_ImplementMethod(Expr, Eval)
{
	::printf("%s\n", argument.GetValueThis().ToString().c_str());
	return Value::nil();
}

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
