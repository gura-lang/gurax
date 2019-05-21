//==============================================================================
// VType_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// DateTime()
Gurax_DeclareFunction(DateTime)
{
	Declare(VTYPE_DateTime, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(DateTime)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	return new Value_DateTime(new DateTime());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// DateTime#year
Gurax_DeclareProperty_RW(DateTime, year)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The year value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetYear());
}

Gurax_ImplementPropertySetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetYear(Value_Number::GetInt16(value));
}

//------------------------------------------------------------------------------
// VType_DateTime
//------------------------------------------------------------------------------
VType_DateTime VTYPE_DateTime("DateTime");

void VType_DateTime::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(DateTime));
	// Assignment of property
	Assign(Gurax_CreateProperty(DateTime, year));
}

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------
String Value_DateTime::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetDateTime().ToString(ss);
	str += ">";
	return str;
}

String Value_DateTime::ToStringDetail(const StringStyle& ss) const
{
	return GetDateTime().ToString(ss);
}

}
