//==============================================================================
// VType_wxAuiMDIChildFrame.cpp
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
// wx.AuiMDIChildFrame(parent as wx.AuiMDIParentFrame, winid as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(AuiMDIChildFrame_gurax, "AuiMDIChildFrame")
{
	Declare(VTYPE_wxAuiMDIChildFrame, Flag::None);
	DeclareArg("parent", VTYPE_wxAuiMDIParentFrame, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.AuiMDIChildFrame.");
}

Gurax_ImplementConstructorEx(AuiMDIChildFrame_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAuiMDIParentFrame& value_parent = args_gurax.Pick<Value_wxAuiMDIParentFrame>();
	wxAuiMDIParentFrame* parent = value_parent.GetEntityPtr();
	wxWindowID winid = args_gurax.PickNumber<wxWindowID>();
	const char* title = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFrameNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxAuiMDIChildFrame::EntityT(parent, winid, title, pos, size, style, name);
	RefPtr<Value_wxAuiMDIChildFrame> pValue_gurax(new Value_wxAuiMDIChildFrame(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AuiMDIChildFrame#Create(parent as wx.AuiMDIParentFrame, winid as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxAuiMDIParentFrame, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAuiMDIParentFrame& value_parent = args_gurax.Pick<Value_wxAuiMDIParentFrame>();
	wxAuiMDIParentFrame* parent = value_parent.GetEntityPtr();
	wxWindowID winid = args_gurax.PickNumber<wxWindowID>();
	const char* title = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFrameNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, winid, title, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#SetMenuBar(menuBar as wx.MenuBar)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetMenuBar_gurax, "SetMenuBar")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("menuBar", VTYPE_wxMenuBar, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetMenuBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMenuBar& value_menuBar = args_gurax.Pick<Value_wxMenuBar>();
	wxMenuBar* menuBar = value_menuBar.GetEntityPtr();
	// Function body
	pEntity_gurax->SetMenuBar(menuBar);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#GetMenuBar() {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetMenuBar_gurax, "GetMenuBar")
{
	Declare(VTYPE_wxMenuBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetMenuBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenuBar(
		pEntity_gurax->GetMenuBar()));
}

// wx.AuiMDIChildFrame#SetTitle(title as String)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetTitle_gurax, "SetTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetTitle(title);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#GetTitle()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetTitle_gurax, "GetTitle")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetTitle();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.AuiMDIChildFrame#SetIcons(icons as wx.IconBundle)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetIcons_gurax, "SetIcons")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icons", VTYPE_wxIconBundle, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetIcons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIconBundle& value_icons = args_gurax.Pick<Value_wxIconBundle>();
	const wxIconBundle& icons = value_icons.GetEntity();
	// Function body
	pEntity_gurax->SetIcons(icons);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#GetIcons() {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetIcons_gurax, "GetIcons")
{
	Declare(VTYPE_wxIconBundle, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetIcons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIconBundle(
		pEntity_gurax->GetIcons()));
}

// wx.AuiMDIChildFrame#SetIcon(icon as wx.Icon)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetIcon_gurax, "SetIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icon", VTYPE_wxIcon, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIcon& value_icon = args_gurax.Pick<Value_wxIcon>();
	const wxIcon& icon = value_icon.GetEntity();
	// Function body
	pEntity_gurax->SetIcon(icon);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#GetIcon() {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetIcon_gurax, "GetIcon")
{
	Declare(VTYPE_wxIcon, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIcon(
		pEntity_gurax->GetIcon()));
}

// wx.AuiMDIChildFrame#Activate()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Activate_gurax, "Activate")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Activate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Activate();
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#Destroy()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Destroy_gurax, "Destroy")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Destroy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Destroy();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#Show(show? as Bool)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Show_gurax, "Show")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Show_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->Show(show);
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#CreateStatusBar(number? as Number, style? as Number, winid? as Number, name? as String) {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, CreateStatusBar_gurax, "CreateStatusBar")
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, CreateStatusBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool number_validFlag = args_gurax.IsValid();
	int number = number_validFlag? args_gurax.PickNumber<int>() : 1;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 1;
	bool winid_validFlag = args_gurax.IsValid();
	wxWindowID winid = winid_validFlag? args_gurax.PickNumber<wxWindowID>() : 1;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStatusBar(
		pEntity_gurax->CreateStatusBar(number, style, winid, name)));
}

// wx.AuiMDIChildFrame#GetStatusBar() {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetStatusBar_gurax, "GetStatusBar")
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetStatusBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStatusBar(
		pEntity_gurax->GetStatusBar()));
}

// wx.AuiMDIChildFrame#SetStatusText(text as String, number? as Number)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetStatusText_gurax, "SetStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetStatusText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	bool number_validFlag = args_gurax.IsValid();
	int number = number_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->SetStatusText(text, number);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#SetStatusWidths(widths_field[] as Number)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetStatusWidths_gurax, "SetStatusWidths")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("widths_field", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetStatusWidths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto widths_field = args_gurax.PickNumList<int>();
	// Function body
	pEntity_gurax->SetStatusWidths(widths_field.sizeT<int>(), widths_field);
	return Value::nil();
}

// wx.AuiMDIChildFrame#CreateToolBar(style as Number, winid as Number, name as String) {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, CreateToolBar_gurax, "CreateToolBar")
{
	Declare(VTYPE_wxToolBar, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, CreateToolBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long style = args_gurax.PickNumber<long>();
	wxWindowID winid = args_gurax.PickNumber<wxWindowID>();
	const char* name = args_gurax.PickString();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolBar(
		pEntity_gurax->CreateToolBar(style, winid, name)));
}

// wx.AuiMDIChildFrame#GetToolBar() {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetToolBar_gurax, "GetToolBar")
{
	Declare(VTYPE_wxToolBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetToolBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolBar(
		pEntity_gurax->GetToolBar()));
}

// wx.AuiMDIChildFrame#Maximize(maximize? as Bool)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Maximize_gurax, "Maximize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("maximize", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Maximize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool maximize = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Maximize(maximize);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#Restore()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Restore_gurax, "Restore")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Restore_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Restore();
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#Iconize(iconize? as Bool)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, Iconize_gurax, "Iconize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("iconize", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, Iconize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool iconize = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Iconize(iconize);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#IsMaximized()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, IsMaximized_gurax, "IsMaximized")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, IsMaximized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsMaximized();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#IsIconized()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, IsIconized_gurax, "IsIconized")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, IsIconized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsIconized();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#ShowFullScreen(show as Bool, style as Number)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, ShowFullScreen_gurax, "ShowFullScreen")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, ShowFullScreen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.PickBool();
	long style = args_gurax.PickNumber<long>();
	// Function body
	bool rtn = pEntity_gurax->ShowFullScreen(show, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#IsFullScreen()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, IsFullScreen_gurax, "IsFullScreen")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, IsFullScreen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsFullScreen();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#IsTopLevel()
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, IsTopLevel_gurax, "IsTopLevel")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, IsTopLevel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsTopLevel();
	return new Gurax::Value_Bool(rtn);
}

// wx.AuiMDIChildFrame#SetMDIParentFrame(parent as wx.AuiMDIParentFrame)
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, SetMDIParentFrame_gurax, "SetMDIParentFrame")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("parent", VTYPE_wxAuiMDIParentFrame, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, SetMDIParentFrame_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAuiMDIParentFrame& value_parent = args_gurax.Pick<Value_wxAuiMDIParentFrame>();
	wxAuiMDIParentFrame* parent = value_parent.GetEntityPtr();
	// Function body
	pEntity_gurax->SetMDIParentFrame(parent);
	return Gurax::Value::nil();
}

// wx.AuiMDIChildFrame#GetMDIParentFrame() {block?}
Gurax_DeclareMethodAlias(wxAuiMDIChildFrame, GetMDIParentFrame_gurax, "GetMDIParentFrame")
{
	Declare(VTYPE_wxAuiMDIParentFrame, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAuiMDIChildFrame, GetMDIParentFrame_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxAuiMDIParentFrame(
		pEntity_gurax->GetMDIParentFrame()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAuiMDIChildFrame
//------------------------------------------------------------------------------
VType_wxAuiMDIChildFrame VTYPE_wxAuiMDIChildFrame("AuiMDIChildFrame");

void VType_wxAuiMDIChildFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxFrame, Flag::Mutable, Gurax_CreateConstructor(AuiMDIChildFrame_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Create_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetMenuBar_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetMenuBar_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetTitle_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetTitle_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetIcons_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetIcons_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetIcon_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetIcon_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Activate_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Destroy_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Show_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, CreateStatusBar_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetStatusBar_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetStatusText_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetStatusWidths_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, CreateToolBar_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetToolBar_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Maximize_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Restore_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, Iconize_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, IsMaximized_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, IsIconized_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, ShowFullScreen_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, IsFullScreen_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, IsTopLevel_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, SetMDIParentFrame_gurax));
	Assign(Gurax_CreateMethod(wxAuiMDIChildFrame, GetMDIParentFrame_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAuiMDIChildFrame
//------------------------------------------------------------------------------
VType& Value_wxAuiMDIChildFrame::vtype = VTYPE_wxAuiMDIChildFrame;

String Value_wxAuiMDIChildFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiMDIChildFrame");
}

//------------------------------------------------------------------------------
// Value_wxAuiMDIChildFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
