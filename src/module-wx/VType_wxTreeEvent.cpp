﻿//==============================================================================
// VType_wxTreeEvent.cpp
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

${help.ComposePropertyHelp(wx.TreeEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.TreeEvent, `en)}

${help.ComposeMethodHelp(wx.TreeEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TreeEvent#GetItem() {block?}
Gurax_DeclareMethodAlias(wxTreeEvent, GetItem_gurax, "GetItem")
{
	Declare(VTYPE_wxTreeItemId, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, GetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTreeItemId(
		pEntity_gurax->GetItem()));
}

// wx.TreeEvent#GetKeyCode()
Gurax_DeclareMethodAlias(wxTreeEvent, GetKeyCode_gurax, "GetKeyCode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, GetKeyCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetKeyCode();
	return new Gurax::Value_Number(rtn);
}

// wx.TreeEvent#GetLabel()
Gurax_DeclareMethodAlias(wxTreeEvent, GetLabel_gurax, "GetLabel")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, GetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLabel();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.TreeEvent#GetOldItem() {block?}
Gurax_DeclareMethodAlias(wxTreeEvent, GetOldItem_gurax, "GetOldItem")
{
	Declare(VTYPE_wxTreeItemId, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, GetOldItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTreeItemId(
		pEntity_gurax->GetOldItem()));
}

// wx.TreeEvent#GetPoint() {block?}
Gurax_DeclareMethodAlias(wxTreeEvent, GetPoint_gurax, "GetPoint")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, GetPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPoint()));
}

// wx.TreeEvent#IsEditCancelled()
Gurax_DeclareMethodAlias(wxTreeEvent, IsEditCancelled_gurax, "IsEditCancelled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, IsEditCancelled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEditCancelled();
	return new Gurax::Value_Bool(rtn);
}

// wx.TreeEvent#SetToolTip(tooltip as String)
Gurax_DeclareMethodAlias(wxTreeEvent, SetToolTip_gurax, "SetToolTip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tooltip", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxTreeEvent, SetToolTip_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* tooltip = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetToolTip(tooltip);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTreeEvent
//------------------------------------------------------------------------------
VType_wxTreeEvent VTYPE_wxTreeEvent("TreeEvent");

void VType_wxTreeEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTreeEvent, GetItem_gurax));
	Assign(Gurax_CreateMethod(wxTreeEvent, GetKeyCode_gurax));
	Assign(Gurax_CreateMethod(wxTreeEvent, GetLabel_gurax));
	Assign(Gurax_CreateMethod(wxTreeEvent, GetOldItem_gurax));
	Assign(Gurax_CreateMethod(wxTreeEvent, GetPoint_gurax));
	Assign(Gurax_CreateMethod(wxTreeEvent, IsEditCancelled_gurax));
	Assign(Gurax_CreateMethod(wxTreeEvent, SetToolTip_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTreeEvent
//------------------------------------------------------------------------------
VType& Value_wxTreeEvent::vtype = VTYPE_wxTreeEvent;
EventValueFactoryDeriv<Value_wxTreeEvent> Value_wxTreeEvent::eventValueFactory;

String Value_wxTreeEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TreeEvent");
}

Gurax_EndModuleScope(wx)
