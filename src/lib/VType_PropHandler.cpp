//==============================================================================
// VType_PropHandler.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(PropHandler, symbol));
}

//------------------------------------------------------------------------------
// Value_PropHandler
//------------------------------------------------------------------------------
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

}
