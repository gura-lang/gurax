//==============================================================================
// VType_wxAuiManager.cpp
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
// wx.AuiManager(managed_wnd? as wx.Window, flags? as Number) {block?}
Gurax_DeclareConstructorAlias(AuiManager_gurax, "AuiManager")
{
	Declare(VTYPE_wxAuiManager, Flag::None);
	DeclareArg("managed_wnd", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.AuiManager.");
}

Gurax_ImplementConstructorEx(AuiManager_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* managed_wnd = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool flags_validFlag = args_gurax.IsValid();
	unsigned int flags = flags_validFlag? args_gurax.PickNumber<unsigned int>() : wxAUI_MGR_DEFAULT;
	// Function body
	auto pEntity_gurax = new Value_wxAuiManager::EntityT(managed_wnd, flags);
	RefPtr<Value_wxAuiManager> pValue_gurax(new Value_wxAuiManager(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AuiManager#DetachPane(window as wx.Window)
Gurax_DeclareMethodAlias(wxAuiManager, DetachPane_gurax, "DetachPane")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, DetachPane_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->DetachPane(window);
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiManager#GetArtProvider() {block?}
Gurax_DeclareMethodAlias(wxAuiManager, GetArtProvider_gurax, "GetArtProvider")
{
	Declare(VTYPE_wxAuiDockArt, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, GetArtProvider_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxAuiDockArt(
		pEntity_gurax->GetArtProvider()));
}

// wx.AuiManager#GetFlags()
Gurax_DeclareMethodAlias(wxAuiManager, GetFlags_gurax, "GetFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, GetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.AuiManager#GetManagedWindow() {block?}
Gurax_DeclareMethodAlias(wxAuiManager, GetManagedWindow_gurax, "GetManagedWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, GetManagedWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetManagedWindow()));
}

// wx.AuiManager#HideHint()
Gurax_DeclareMethodAlias(wxAuiManager, HideHint_gurax, "HideHint")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, HideHint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->HideHint();
	return Gurax::Value::nil();
}

// wx.AuiManager#LoadPerspective(perspective as String, update? as Bool)
Gurax_DeclareMethodAlias(wxAuiManager, LoadPerspective_gurax, "LoadPerspective")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("perspective", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("update", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, LoadPerspective_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* perspective = args_gurax.PickString();
	bool update = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->LoadPerspective(perspective, update);
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiManager#SavePerspective()
Gurax_DeclareMethodAlias(wxAuiManager, SavePerspective_gurax, "SavePerspective")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, SavePerspective_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->SavePerspective();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.AuiManager#SetArtProvider(art_provider as wx.AuiDockArt)
Gurax_DeclareMethodAlias(wxAuiManager, SetArtProvider_gurax, "SetArtProvider")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("art_provider", VTYPE_wxAuiDockArt, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, SetArtProvider_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAuiDockArt& value_art_provider = args_gurax.Pick<Value_wxAuiDockArt>();
	wxAuiDockArt* art_provider = value_art_provider.GetEntityPtr();
	// Function body
	pEntity_gurax->SetArtProvider(art_provider);
	return Gurax::Value::nil();
}

// wx.AuiManager#SetDockSizeConstraint(widthpct as Number, heightpct as Number)
Gurax_DeclareMethodAlias(wxAuiManager, SetDockSizeConstraint_gurax, "SetDockSizeConstraint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("widthpct", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("heightpct", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, SetDockSizeConstraint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double widthpct = args_gurax.PickNumber<double>();
	double heightpct = args_gurax.PickNumber<double>();
	// Function body
	pEntity_gurax->SetDockSizeConstraint(widthpct, heightpct);
	return Gurax::Value::nil();
}

// wx.AuiManager#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxAuiManager, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, SetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int flags = args_gurax.PickNumber<unsigned int>();
	// Function body
	pEntity_gurax->SetFlags(flags);
	return Gurax::Value::nil();
}

// wx.AuiManager#SetManagedWindow(managed_wnd as wx.Window)
Gurax_DeclareMethodAlias(wxAuiManager, SetManagedWindow_gurax, "SetManagedWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("managed_wnd", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, SetManagedWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_managed_wnd = args_gurax.Pick<Value_wxWindow>();
	wxWindow* managed_wnd = value_managed_wnd.GetEntityPtr();
	// Function body
	pEntity_gurax->SetManagedWindow(managed_wnd);
	return Gurax::Value::nil();
}

// wx.AuiManager#ShowHint(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxAuiManager, ShowHint_gurax, "ShowHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, ShowHint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	// Function body
	pEntity_gurax->ShowHint(rect);
	return Gurax::Value::nil();
}

// wx.AuiManager#UnInit()
Gurax_DeclareMethodAlias(wxAuiManager, UnInit_gurax, "UnInit")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, UnInit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UnInit();
	return Gurax::Value::nil();
}

// wx.AuiManager#Update()
Gurax_DeclareMethodAlias(wxAuiManager, Update_gurax, "Update")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiManager, Update_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Update();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAuiManager
//------------------------------------------------------------------------------
VType_wxAuiManager VTYPE_wxAuiManager("AuiManager");

void VType_wxAuiManager::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(AuiManager_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAuiManager, DetachPane_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, GetArtProvider_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, GetFlags_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, GetManagedWindow_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, HideHint_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, LoadPerspective_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, SavePerspective_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, SetArtProvider_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, SetDockSizeConstraint_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, SetManagedWindow_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, ShowHint_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, UnInit_gurax));
	Assign(Gurax_CreateMethod(wxAuiManager, Update_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAuiManager
//------------------------------------------------------------------------------
VType& Value_wxAuiManager::vtype = VTYPE_wxAuiManager;

String Value_wxAuiManager::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiManager");
}

//------------------------------------------------------------------------------
// Value_wxAuiManager::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
