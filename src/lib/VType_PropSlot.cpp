//==============================================================================
// VType_PropSlot.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(PropSlot, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(PropSlot, `en)}

${help.ComposeMethodHelp(PropSlot, `en)}
)**";

// PropSlot#IsSet(symbol:Symbol)
Gurax_DeclareMethod(PropSlot, IsSet)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the property handler is declared with the flag specified by `symbol`.
)**");
}

Gurax_ImplementMethod(PropSlot, IsSet)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	DeclArg::Flags flags = DeclArg::SymbolToFlag(args.PickSymbol());
	if (flags == DeclArg::Flag::None) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for flag");
		return Value::nil();
	}
	// Function body
	return new Value_Bool(valueThis.GetPropSlot().IsSet(flags));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// PropSlot#name
Gurax_DeclareProperty_R(PropSlot, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The property's name.
)**");
}

Gurax_ImplementPropertyGetter(PropSlot, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetPropSlot().GetName());
}

// PropSlot#symbol
Gurax_DeclareProperty_R(PropSlot, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The property's symbol.
)**");
}

Gurax_ImplementPropertyGetter(PropSlot, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetPropSlot().GetSymbol());
}

// PropSlot#vtype
Gurax_DeclareProperty_R(PropSlot, vtype)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The property's value type.
)**");
}

Gurax_ImplementPropertyGetter(PropSlot, vtype)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_VType(valueThis.GetPropSlot().GetVType());
}

// PropSlot#isOfClass
Gurax_DeclareProperty_R(PropSlot, isOfClass)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the property belongs to a class.
)**");
}

Gurax_ImplementPropertyGetter(PropSlot, isOfClass)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetPropSlot().IsSet(PropSlot::Flag::OfClass));
}

// PropSlot#isOfInstance
Gurax_DeclareProperty_R(PropSlot, isOfInstance)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the property belongs to an instance.
)**");
}

Gurax_ImplementPropertyGetter(PropSlot, isOfInstance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetPropSlot().IsSet(PropSlot::Flag::OfInstance));
}

//------------------------------------------------------------------------------
// VType_PropSlot
//------------------------------------------------------------------------------
VType_PropSlot VTYPE_PropSlot("PropSlot");

void VType_PropSlot::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(PropSlot, IsSet));
	// Assignment of property
	Assign(Gurax_CreateProperty(PropSlot, name));
	Assign(Gurax_CreateProperty(PropSlot, symbol));
	Assign(Gurax_CreateProperty(PropSlot, vtype));
	Assign(Gurax_CreateProperty(PropSlot, isOfClass));
	Assign(Gurax_CreateProperty(PropSlot, isOfInstance));
}

//------------------------------------------------------------------------------
// Value_PropSlot
//------------------------------------------------------------------------------
VType& Value_PropSlot::vtype = VTYPE_PropSlot;

String Value_PropSlot::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPropSlot().ToString(ss));
}

void Value_PropSlot::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Help* pHelp = GetHelpHolder(false)->LookupLoose(pLangCode);
	if (pHelp) Basement::Inst.Present(processor, pHelp->GetDocReferable().Reference());
}

//------------------------------------------------------------------------------
// Iterator_PropSlot
//------------------------------------------------------------------------------
Iterator_PropSlot::Iterator_PropSlot(PropSlotOwner* pPropSlotOwner) :
	_pPropSlotOwner(pPropSlotOwner), _idx(0)
{}

size_t Iterator_PropSlot::GetLength() const
{
	return GetPropSlotOwner().size();
}

Value* Iterator_PropSlot::DoNextValue()
{
	if (_idx >= GetPropSlotOwner().size()) return nullptr;
	const PropSlot* pPropSlot = GetPropSlotOwner()[_idx++];
	return new Value_PropSlot(pPropSlot->Reference());
}

String Iterator_PropSlot::ToString(const StringStyle& ss) const
{
	String str;
	str += "PropSlot";
	return str;
}

}
