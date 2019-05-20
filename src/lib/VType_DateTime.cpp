//==============================================================================
// VType_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
	// Assignment of property
	Assign(Gurax_CreateProperty(DateTime, year));
}

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------

}
