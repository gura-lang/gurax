//==============================================================================
// VType_wxAuiManagerEvent.cpp
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

${help.ComposePropertyHelp(wx.AuiManagerEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AuiManagerEvent, `en)}

${help.ComposeMethodHelp(wx.AuiManagerEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AuiManagerEvent#CanVeto()
Gurax_DeclareMethodAlias(wxAuiManagerEvent, CanVeto_gurax, "CanVeto")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, CanVeto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanVeto();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiManagerEvent#GetButton()
Gurax_DeclareMethodAlias(wxAuiManagerEvent, GetButton_gurax, "GetButton")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, GetButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetButton();
	return new Gurax::Value_Number(rtn);
}

// wx.AuiManagerEvent#GetDC() {block?}
Gurax_DeclareMethodAlias(wxAuiManagerEvent, GetDC_gurax, "GetDC")
{
	Declare(VTYPE_wxDC, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, GetDC_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDC(
		*pEntity_gurax->GetDC()));
}

// wx.AuiManagerEvent#GetVeto()
Gurax_DeclareMethodAlias(wxAuiManagerEvent, GetVeto_gurax, "GetVeto")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, GetVeto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetVeto();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiManagerEvent#GetManager() {block?}
Gurax_DeclareMethodAlias(wxAuiManagerEvent, GetManager_gurax, "GetManager")
{
	Declare(VTYPE_wxAuiManager, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, GetManager_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxAuiManager(
		pEntity_gurax->GetManager()));
}

// wx.AuiManagerEvent#SetButton(button as Number)
Gurax_DeclareMethodAlias(wxAuiManagerEvent, SetButton_gurax, "SetButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, SetButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetButton(button);
	return Gurax::Value::nil();
}

// wx.AuiManagerEvent#SetCanVeto(can_veto as Bool)
Gurax_DeclareMethodAlias(wxAuiManagerEvent, SetCanVeto_gurax, "SetCanVeto")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("can_veto", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, SetCanVeto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool can_veto = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetCanVeto(can_veto);
	return Gurax::Value::nil();
}

// wx.AuiManagerEvent#SetDC(pdc as wx.DC)
Gurax_DeclareMethodAlias(wxAuiManagerEvent, SetDC_gurax, "SetDC")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pdc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, SetDC_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_pdc = args_gurax.Pick<Value_wxDC>();
	wxDC* pdc = value_pdc.GetEntityPtr();
	// Function body
	pEntity_gurax->SetDC(pdc);
	return Gurax::Value::nil();
}

// wx.AuiManagerEvent#SetManager(manager as wx.AuiManager)
Gurax_DeclareMethodAlias(wxAuiManagerEvent, SetManager_gurax, "SetManager")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("manager", VTYPE_wxAuiManager, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, SetManager_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAuiManager& value_manager = args_gurax.Pick<Value_wxAuiManager>();
	wxAuiManager* manager = value_manager.GetEntityPtr();
	// Function body
	pEntity_gurax->SetManager(manager);
	return Gurax::Value::nil();
}

// wx.AuiManagerEvent#Veto(veto? as Bool)
Gurax_DeclareMethodAlias(wxAuiManagerEvent, Veto_gurax, "Veto")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("veto", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManagerEvent, Veto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool veto = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Veto(veto);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAuiManagerEvent
//------------------------------------------------------------------------------
VType_wxAuiManagerEvent VTYPE_wxAuiManagerEvent("AuiManagerEvent");

void VType_wxAuiManagerEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, CanVeto_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, GetButton_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, GetDC_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, GetVeto_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, GetManager_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, SetButton_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, SetCanVeto_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, SetDC_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, SetManager_gurax));
	Assign(Gurax_CreateMethod(wxAuiManagerEvent, Veto_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAuiManagerEvent
//------------------------------------------------------------------------------
VType& Value_wxAuiManagerEvent::vtype = VTYPE_wxAuiManagerEvent;
EventValueFactoryDeriv<Value_wxAuiManagerEvent> Value_wxAuiManagerEvent::eventValueFactory;

String Value_wxAuiManagerEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiManagerEvent");
}

Gurax_EndModuleScope(wx)
