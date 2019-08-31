//==============================================================================
// VType_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Symbol == Symbol
Gurax_ImplementOpBinary(Eq, Symbol, Symbol)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(pSymbolL->IsIdentical(pSymbolR));
}

//------------------------------------------------------------------------------
// VType_Symbol
//------------------------------------------------------------------------------
VType_Symbol VTYPE_Symbol("Symbol");

void VType_Symbol::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Implementation of operator
	Gurax_AssignOpBinary(Eq, Symbol, Symbol);
}

Value* VType_Symbol::DoCastFrom(const Value& value, DeclArg::Flags flags) const
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
VType& Value_Symbol::vtype = VTYPE_Symbol;

}
