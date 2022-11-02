//==============================================================================
// VType_wxNavigationKeyEvent.cpp
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

${help.ComposePropertyHelp(wxNavigationKeyEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxNavigationKeyEvent)}

${help.ComposeMethodHelp(wxNavigationKeyEvent)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.NavigationKeyEvent#GetCurrentFocus() {block?}
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, GetCurrentFocus_gurax, "GetCurrentFocus")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, GetCurrentFocus_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetCurrentFocus()));
}

// wx.NavigationKeyEvent#GetDirection()
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, GetDirection_gurax, "GetDirection")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, GetDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetDirection();
	return new Gurax::Value_Bool(rtn);
}

// wx.NavigationKeyEvent#IsFromTab()
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, IsFromTab_gurax, "IsFromTab")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, IsFromTab_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsFromTab();
	return new Gurax::Value_Bool(rtn);
}

// wx.NavigationKeyEvent#IsWindowChange()
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, IsWindowChange_gurax, "IsWindowChange")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, IsWindowChange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsWindowChange();
	return new Gurax::Value_Bool(rtn);
}

// wx.NavigationKeyEvent#SetCurrentFocus(currentFocus as wx.Window)
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, SetCurrentFocus_gurax, "SetCurrentFocus")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("currentFocus", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, SetCurrentFocus_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_currentFocus = args_gurax.Pick<Value_wxWindow>();
	wxWindow* currentFocus = value_currentFocus.GetEntityPtr();
	// Function body
	pEntity_gurax->SetCurrentFocus(currentFocus);
	return Gurax::Value::nil();
}

// wx.NavigationKeyEvent#SetDirection(direction as Bool)
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, SetDirection_gurax, "SetDirection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("direction", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, SetDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetDirection(direction);
	return Gurax::Value::nil();
}

// wx.NavigationKeyEvent#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, SetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetFlags(flags);
	return Gurax::Value::nil();
}

// wx.NavigationKeyEvent#SetFromTab(fromTab as Bool)
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, SetFromTab_gurax, "SetFromTab")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fromTab", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, SetFromTab_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool fromTab = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetFromTab(fromTab);
	return Gurax::Value::nil();
}

// wx.NavigationKeyEvent#SetWindowChange(windowChange as Bool)
Gurax_DeclareMethodAlias(wxNavigationKeyEvent, SetWindowChange_gurax, "SetWindowChange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("windowChange", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNavigationKeyEvent, SetWindowChange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool windowChange = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetWindowChange(windowChange);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxNavigationKeyEvent
//------------------------------------------------------------------------------
VType_wxNavigationKeyEvent VTYPE_wxNavigationKeyEvent("NavigationKeyEvent");

void VType_wxNavigationKeyEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, GetCurrentFocus_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, GetDirection_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, IsFromTab_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, IsWindowChange_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, SetCurrentFocus_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, SetDirection_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, SetFromTab_gurax));
	Assign(Gurax_CreateMethod(wxNavigationKeyEvent, SetWindowChange_gurax));
}

//------------------------------------------------------------------------------
// Value_wxNavigationKeyEvent
//------------------------------------------------------------------------------
VType& Value_wxNavigationKeyEvent::vtype = VTYPE_wxNavigationKeyEvent;
EventValueFactoryDeriv<Value_wxNavigationKeyEvent> Value_wxNavigationKeyEvent::eventValueFactory;

String Value_wxNavigationKeyEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.NavigationKeyEvent");
}

Gurax_EndModuleScope(wx)
