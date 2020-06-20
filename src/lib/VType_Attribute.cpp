//==============================================================================
// VType_Attribute.cpp
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
// Implementation of method
//------------------------------------------------------------------------------
// Attribute#EachSymbol() {block?}
Gurax_DeclareMethod(Attribute, EachSymbol)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns each symbol in the attribute.");
}

Gurax_ImplementMethod(Attribute, EachSymbol)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Attribute::Iterator_EachSymbol(
								attr.Reference(), attr.GetSymbols()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Attribute#EachSymbolOpt() {block?}
Gurax_DeclareMethod(Attribute, EachSymbolOpt)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns each optional symbol in the attribute.");
}

Gurax_ImplementMethod(Attribute, EachSymbolOpt)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Attribute::Iterator_EachSymbol(
								attr.Reference(), attr.GetSymbolsOpt()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//------------------------------------------------------------------------------
// VType_Attribute
//------------------------------------------------------------------------------
VType_Attribute VTYPE_Attribute("Attribute");

void VType_Attribute::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Attribute, EachSymbol));
	Assign(Gurax_CreateMethod(Attribute, EachSymbolOpt));
}

//------------------------------------------------------------------------------
// VType_Attribute::Iterator_EachSymbol
//------------------------------------------------------------------------------

Value* VType_Attribute::Iterator_EachSymbol::DoNextValue()
{
	if (_idx >= GetSymbolList().size()) return nullptr;
	const Symbol* pSymbol = GetSymbolList()[_idx++];
	return new Value_Symbol(pSymbol);
}

String VType_Attribute::Iterator_EachSymbol::ToString(const StringStyle& ss) const
{
	return String().Format("Attribute.EachSymbol:n=%zu", GetSymbolList().size());
}

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------
VType& Value_Attribute::vtype = VTYPE_Attribute;

String Value_Attribute::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetAttr().ToString(ss));
}

}
