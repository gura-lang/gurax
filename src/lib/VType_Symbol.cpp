//==============================================================================
// VType_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Symbol
//------------------------------------------------------------------------------
VType_Symbol VTYPE_Symbol("Symbol");

void VType_Symbol::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

Value* VType_Symbol::DoCastFrom(const Value& value) const
{
	if (value.IsType(VTYPE_Expr)) {
		const Expr& expr = dynamic_cast<const Value_Expr&>(value).GetExpr();
		if (expr.IsType<Expr_Identifier>()) {
			const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(expr);
			if (exprEx.IsPureSymbol()) {
				return new Value_Symbol(exprEx.GetSymbol());
			}
		}
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Symbol
//------------------------------------------------------------------------------

}
