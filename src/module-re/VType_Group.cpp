//==============================================================================
// VType_Group.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(re.Group, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(re.Group, `en)}

${help.ComposeMethodHelp(re.Group, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// re.Group#begin
Gurax_DeclareProperty_R(Group, begin)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Group, begin)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Group& group = valueThis.GetGroup();
	return new Value_Number(group.GetPosBegin());
}

// re.Group#end
Gurax_DeclareProperty_R(Group, end)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Group, end)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Group& group = valueThis.GetGroup();
	return new Value_Number(group.GetPosEnd());
}

// re.Group#string
Gurax_DeclareProperty_R(Group, string)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Group, string)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Group& group = valueThis.GetGroup();
	return new Value_String(group.GetString());
}

//------------------------------------------------------------------------------
// VType_Group
//------------------------------------------------------------------------------
VType_Group VTYPE_Group("Group");

void VType_Group::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Group, begin));
	Assign(Gurax_CreateProperty(Group, end));
	Assign(Gurax_CreateProperty(Group, string));
}

//------------------------------------------------------------------------------
// Value_Group
//------------------------------------------------------------------------------
VType& Value_Group::vtype = VTYPE_Group;

String Value_Group::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetGroup().ToString(ss));
}

Gurax_EndModuleScope(re)
