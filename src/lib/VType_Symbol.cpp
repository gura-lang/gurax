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

${help.ComposePropertyHelp(Symbol, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Symbol, `en)}

${help.ComposeMethodHelp(Symbol, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Symbol(name as String):map {block?}
Gurax_DeclareConstructor(Symbol)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Symbol` instance.
)**");
}

Gurax_ImplementConstructor(Symbol)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	return argument.ReturnValue(processor, new Value_Symbol(Symbol::Add(name)));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Symbol#symbolName
Gurax_DeclareProperty_R(Symbol, symbolName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The name of the symbol.
)**");
}

Gurax_ImplementPropertyGetter(Symbol, symbolName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetSymbol()->GetName());
}

// Symbol#uniqId
Gurax_DeclareProperty_R(Symbol, uniqId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The unique ID of the symbol.
)**");
}

Gurax_ImplementPropertyGetter(Symbol, uniqId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSymbol()->GetUniqId());
}

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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Symbol));
	// Assignment of property
	Assign(Gurax_CreateProperty(Symbol, symbolName));
	Assign(Gurax_CreateProperty(Symbol, uniqId));
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

bool Value_Symbol::IsEqualTo(const Value& value) const
{
	if (IsSameType(value)) {
		return GetSymbol()->IsEqualTo(dynamic_cast<const Value_Symbol&>(value).GetSymbol());
	} else if (value.IsType(VTYPE_Expr)) {
		return dynamic_cast<const Value_Expr&>(value).GetExpr().HasPureSymbol(GetSymbol());
	}
	return false;
}

bool Value_Symbol::IsLessThan(const Value& value) const
{
	return IsSameType(value)?
		GetSymbol()->IsLessThan_UniqId(Value_Symbol::GetSymbol(value)) :
		GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
}

String Value_Symbol::ToString(const StringStyle& ss) const
{
	String strEntity = GetSymbol()->ToString(ss);
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

}
