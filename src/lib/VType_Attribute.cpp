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

${help.ComposePropertyHelp(Attribute, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Attribute, `en)}

${help.ComposeMethodHelp(Attribute, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Attribute#Each() {block?}
Gurax_DeclareMethod(Attribute, Each)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that returns each symbol in the attribute.
)**");
}

Gurax_ImplementMethod(Attribute, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Function body
	RefPtr<Iterator> pIterator(
		new VType_Attribute::Iterator_Each(attr.Reference(), attr.GetSymbols()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Attribute#EachOpt() {block?}
Gurax_DeclareMethod(Attribute, EachOpt)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that returns each optional symbol in the attribute.
)**");
}

Gurax_ImplementMethod(Attribute, EachOpt)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Function body
	RefPtr<Iterator> pIterator(
		new VType_Attribute::Iterator_Each(attr.Reference(), attr.GetSymbolsOpt()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Attribute#IsEmpty()
Gurax_DeclareMethod(Attribute, IsEmpty)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the attribute is empty.
)**");
}

Gurax_ImplementMethod(Attribute, IsEmpty)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Function body
	return new Value_Bool(attr.IsEmpty());
}

// Attribute#IsSet(symbol:Symbol)
Gurax_DeclareMethod(Attribute, IsSet)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the specified symbol is set in the attribute.
)**");
}

Gurax_ImplementMethod(Attribute, IsSet)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Argument
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	return new Value_Bool(attr.IsSet(pSymbol));
}

// Attribute#IsSetOpt(symbol:Symbol)
Gurax_DeclareMethod(Attribute, IsSetOpt)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the specified symbol is set as an optional symbol in the attribute.
)**");
}

Gurax_ImplementMethod(Attribute, IsSetOpt)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Attribute& attr = valueThis.GetAttr();
	// Argument
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	return new Value_Bool(attr.IsSetOpt(pSymbol));
}

//------------------------------------------------------------------------------
// VType_Attribute
//------------------------------------------------------------------------------
VType_Attribute VTYPE_Attribute("Attribute");

void VType_Attribute::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Attribute, Each));
	Assign(Gurax_CreateMethod(Attribute, EachOpt));
	Assign(Gurax_CreateMethod(Attribute, IsEmpty));
	Assign(Gurax_CreateMethod(Attribute, IsSet));
	Assign(Gurax_CreateMethod(Attribute, IsSetOpt));
}

//------------------------------------------------------------------------------
// VType_Attribute::Iterator_Each
//------------------------------------------------------------------------------
Value* VType_Attribute::Iterator_Each::DoNextValue()
{
	if (_idx >= GetSymbolList().size()) return nullptr;
	const Symbol* pSymbol = GetSymbolList()[_idx++];
	return new Value_Symbol(pSymbol);
}

String VType_Attribute::Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("Attribute.Each:n=%zu", GetSymbolList().size());
}

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------
VType& Value_Attribute::vtype = VTYPE_Attribute;

String Value_Attribute::ToString(const StringStyle& ss) const
{
	String strEntity = GetAttr().ToString(ss);
	if (!ss.IsUnbracket()) strEntity = String().Format("(%s)", strEntity.c_str()); 
	return ToStringGeneric(ss, strEntity);
}

}
