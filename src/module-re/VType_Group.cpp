//==============================================================================
// VType_Group.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// re.Group#begin
Gurax_DeclareProperty_R(Group, begin)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Group, begin));
	Assign(Gurax_CreateProperty(Group, end));
	Assign(Gurax_CreateProperty(Group, string));
}

//------------------------------------------------------------------------------
// Value_Group
//------------------------------------------------------------------------------
VType& Value_Group::vtype = VTYPE_Group;

Gurax_EndModuleScope(re)
