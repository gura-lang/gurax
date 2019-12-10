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
	// Assignment of property
	Assign(Gurax_CreateProperty(PropHandler, symbol));
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
