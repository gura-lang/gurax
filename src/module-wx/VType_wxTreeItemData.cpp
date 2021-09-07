//==============================================================================
// VType_wxTreeItemData.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.TreeItemData() {block?} {block?}
Gurax_DeclareConstructorAlias(TreeItemData_gurax, "TreeItemData")
{
	Declare(VTYPE_wxTreeItemData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.TreeItemData.");
}

Gurax_ImplementConstructorEx(TreeItemData_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTreeItemData(
		wxTreeItemData()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TreeItemData#GetId() {block?}
Gurax_DeclareMethodAlias(wxTreeItemData, GetId_gurax, "GetId")
{
	Declare(VTYPE_wxTreeItemId, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTreeItemData, GetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTreeItemId(
		pEntity_gurax->GetId()));
}

// wx.TreeItemData#SetId(id as wx.TreeItemId)
Gurax_DeclareMethodAlias(wxTreeItemData, SetId_gurax, "SetId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_wxTreeItemId, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTreeItemData, SetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxTreeItemId& value_id = args_gurax.Pick<Value_wxTreeItemId>();
	const wxTreeItemId& id = value_id.GetEntity();
	// Function body
	pEntity_gurax->SetId(id);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTreeItemData
//------------------------------------------------------------------------------
VType_wxTreeItemData VTYPE_wxTreeItemData("TreeItemData");

void VType_wxTreeItemData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(TreeItemData_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTreeItemData, GetId_gurax));
	Assign(Gurax_CreateMethod(wxTreeItemData, SetId_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTreeItemData
//------------------------------------------------------------------------------
VType& Value_wxTreeItemData::vtype = VTYPE_wxTreeItemData;

String Value_wxTreeItemData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TreeItemData");
}

Gurax_EndModuleScope(wx)
