//==============================================================================
// VType_wxTreeItemId.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wxTreeItemId, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxTreeItemId, `en)}

${help.ComposeMethodHelp(wxTreeItemId, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TreeItemId#IsOk()
Gurax_DeclareMethodAlias(wxTreeItemId, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTreeItemId, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.TreeItemId#Unset()
Gurax_DeclareMethodAlias(wxTreeItemId, Unset_gurax, "Unset")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTreeItemId, Unset_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Unset();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTreeItemId
//------------------------------------------------------------------------------
VType_wxTreeItemId VTYPE_wxTreeItemId("TreeItemId");

void VType_wxTreeItemId::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTreeItemId, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxTreeItemId, Unset_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTreeItemId
//------------------------------------------------------------------------------
VType& Value_wxTreeItemId::vtype = VTYPE_wxTreeItemId;

String Value_wxTreeItemId::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TreeItemId");
}

Gurax_EndModuleScope(wx)
