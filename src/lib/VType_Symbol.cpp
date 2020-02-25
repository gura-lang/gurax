//==============================================================================
// VType_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

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
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Implementation of operator
	Gurax_AssignOpBinary(Eq, Symbol, Symbol);
}

Value* VType_Symbol::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Expr)) {
		const Symbol* pSymbol = dynamic_cast<const Value_Expr&>(value).GetExpr().GetPureSymbol();
		if (pSymbol) return new Value_Symbol(pSymbol);
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Symbol
//------------------------------------------------------------------------------
VType& Value_Symbol::vtype = VTYPE_Symbol;

bool Value_Symbol::IsEqualTo(const Value* pValue) const
{
	if (IsSameType(pValue)) {
		return GetSymbol()->IsEqualTo(dynamic_cast<const Value_Symbol*>(pValue)->GetSymbol());
	} else if (pValue->IsType(VTYPE_Expr)) {
		return dynamic_cast<const Value_Expr*>(pValue)->GetExpr().IsPureSymbol(GetSymbol());
	}
	return false;
}

bool Value_Symbol::IsLessThan(const Value* pValue) const
{
	return IsSameType(pValue)?
		GetSymbol()->IsLessThan_UniqId(Value_Symbol::GetSymbol(*pValue)) :
		GetVType().IsLessThan(pValue->GetVType());
}

}
