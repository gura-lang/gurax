//==============================================================================
// VType_PropHandler.cpp
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
// PropHandler#IsSet(symbol:Symbol)
Gurax_DeclareMethod(PropHandler, IsSet)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns `true` if the property handler is declared with the flag specified by `symbol`.\n");
}

Gurax_ImplementMethod(PropHandler, IsSet)
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
	return new Value_Bool(valueThis.GetPropHandler().IsSet(flags));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// PropHandler#symbol
Gurax_DeclareProperty_R(PropHandler, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The property's symbol.");
}

Gurax_ImplementPropertyGetter(PropHandler, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetPropHandler().GetSymbol());
}

// PropHandler#vtype
Gurax_DeclareProperty_R(PropHandler, vtype)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The property's value type.");
}

Gurax_ImplementPropertyGetter(PropHandler, vtype)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_VType(valueThis.GetPropHandler().GetVType());
}

// PropHandler#isOfClass
Gurax_DeclareProperty_R(PropHandler, isOfClass)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the property belongs to a class.");
}

Gurax_ImplementPropertyGetter(PropHandler, isOfClass)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetPropHandler().IsSet(PropHandler::Flag::OfClass));
}

// PropHandler#isOfInstance
Gurax_DeclareProperty_R(PropHandler, isOfInstance)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the property belongs to an instance.");
}

Gurax_ImplementPropertyGetter(PropHandler, isOfInstance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetPropHandler().IsSet(PropHandler::Flag::OfInstance));
}

//------------------------------------------------------------------------------
// VType_PropHandler
//------------------------------------------------------------------------------
VType_PropHandler VTYPE_PropHandler("PropHandler");

void VType_PropHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(PropHandler, IsSet));
	// Assignment of property
	Assign(Gurax_CreateProperty(PropHandler, symbol));
	Assign(Gurax_CreateProperty(PropHandler, vtype));
	Assign(Gurax_CreateProperty(PropHandler, isOfClass));
	Assign(Gurax_CreateProperty(PropHandler, isOfInstanced));
}

//------------------------------------------------------------------------------
// Value_PropHandler
//------------------------------------------------------------------------------
VType& Value_PropHandler::vtype = VTYPE_PropHandler;

String Value_PropHandler::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetPropHandler().ToString(ss);
	str += ">";
	return str;
}

String Value_PropHandler::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

void Value_PropHandler::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Help* pHelp = GetHelpHolder()->Lookup(pLangCode);
	if (pHelp) Basement::Inst.Present(processor, pHelp->GetDocReferable().Reference());
}

//------------------------------------------------------------------------------
// Iterator_PropHandler
//------------------------------------------------------------------------------
Iterator_PropHandler::Iterator_PropHandler(PropHandlerOwner* pPropHandlerOwner) :
	_pPropHandlerOwner(pPropHandlerOwner), _idx(0)
{}

size_t Iterator_PropHandler::GetLength() const
{
	return GetPropHandlerOwner().size();
}

Value* Iterator_PropHandler::DoNextValue()
{
	if (_idx >= GetPropHandlerOwner().size()) return nullptr;
	const PropHandler* pPropHandler = GetPropHandlerOwner()[_idx++];
	return new Value_PropHandler(pPropHandler->Reference());
}

String Iterator_PropHandler::ToString(const StringStyle& ss) const
{
	String str;
	str += "PropHandler";
	return str;
}

}
