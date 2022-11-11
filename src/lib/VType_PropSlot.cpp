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

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// PropSlot#__help__(lang? as Symbol) {block?}
Gurax_DeclareMethod(PropSlot, __help__)
{
	Declare(VTYPE_Help, Flag::Map);
	DeclareArg("lang", VTYPE_Symbol, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(PropSlot, __help__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	RefPtr<Value> pValueRtn(Value::nil());
	const Help* pHelp = valueThis.GetPropSlot().GetHelpHolder().LookupLoose(pLangCode);
	if (pHelp) pValueRtn.reset(new Value_Help(pHelp->Reference()));
	return argument.ReturnValue(processor, pValueRtn.release());
}

// PropSlot#IsSet(symbol:Symbol)
Gurax_DeclareMethod(PropSlot, IsSet)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns `true` if the property handler is declared with the flag specified by `symbol`.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"The property's name.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The property's symbol.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The property's value type.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the property belongs to a class.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the property belongs to an instance.");
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(PropSlot, __help__));
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
