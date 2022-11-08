//==============================================================================
// VType_wxFrame.cpp
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

${help.ComposePropertyHelp(wx.Frame, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Frame, `en)}

${help.ComposeMethodHelp(wx.Frame, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Frame(parent:nil as wx.Window, id as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(Frame_gurax, "Frame")
{
	Declare(VTYPE_wxFrame, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Frame.");
}

Gurax_ImplementConstructorEx(Frame_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* title = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFrameNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxFrame::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxFrame> pValue_gurax(new Value_wxFrame(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Frame#Centre(direction? as Number)
Gurax_DeclareMethodAlias(wxFrame, Centre_gurax, "Centre")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, Centre_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	pEntity_gurax->Centre(direction);
	return Gurax::Value::nil();
}

// wx.Frame#Create(parent as wx.Window, id as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxFrame, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* title = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFrameNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, title, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.Frame#CreateStatusBar(number? as Number, style? as Number, id? as Number, name? as String) {block?}
Gurax_DeclareMethodAlias(wxFrame, CreateStatusBar_gurax, "CreateStatusBar")
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, CreateStatusBar_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSTB_DEFAULT_STYLE;
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStatusBarNameStr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStatusBar(
		pEntity_gurax->CreateStatusBar(number, style, id, name)));
}

// wx.Frame#CreateToolBar(style? as Number, id? as Number, name? as String) {block?}
Gurax_DeclareMethodAlias(wxFrame, CreateToolBar_gurax, "CreateToolBar")
{
	Declare(VTYPE_wxToolBar, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, CreateToolBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxTB_DEFAULT_STYLE;
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxToolBarNameStr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolBar(
		pEntity_gurax->CreateToolBar(style, id, name)));
}

// wx.Frame#GetClientAreaOrigin() {block?}
Gurax_DeclareMethodAlias(wxFrame, GetClientAreaOrigin_gurax, "GetClientAreaOrigin")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, GetClientAreaOrigin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetClientAreaOrigin()));
}

// wx.Frame#GetMenuBar() {block?}
Gurax_DeclareMethodAlias(wxFrame, GetMenuBar_gurax, "GetMenuBar")
{
	Declare(VTYPE_wxMenuBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, GetMenuBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenuBar(
		pEntity_gurax->GetMenuBar()));
}

// wx.Frame#GetStatusBar() {block?}
Gurax_DeclareMethodAlias(wxFrame, GetStatusBar_gurax, "GetStatusBar")
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, GetStatusBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStatusBar(
		pEntity_gurax->GetStatusBar()));
}

// wx.Frame#GetStatusBarPane()
Gurax_DeclareMethodAlias(wxFrame, GetStatusBarPane_gurax, "GetStatusBarPane")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, GetStatusBarPane_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetStatusBarPane();
	return new Gurax::Value_Number(rtn);
}

// wx.Frame#GetToolBar() {block?}
Gurax_DeclareMethodAlias(wxFrame, GetToolBar_gurax, "GetToolBar")
{
	Declare(VTYPE_wxToolBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, GetToolBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolBar(
		pEntity_gurax->GetToolBar()));
}

// wx.Frame#ProcessCommand(id as Number)
Gurax_DeclareMethodAlias(wxFrame, ProcessCommand_gurax, "ProcessCommand")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, ProcessCommand_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ProcessCommand(id);
	return new Gurax::Value_Bool(rtn);
}

// wx.Frame#SetMenuBar(menuBar as wx.MenuBar)
Gurax_DeclareMethodAlias(wxFrame, SetMenuBar_gurax, "SetMenuBar")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("menuBar", VTYPE_wxMenuBar, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, SetMenuBar_gurax, processor_gurax, argument_gurax)
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

// wx.Frame#SetStatusBar(statusBar as wx.StatusBar)
Gurax_DeclareMethodAlias(wxFrame, SetStatusBar_gurax, "SetStatusBar")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("statusBar", VTYPE_wxStatusBar, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, SetStatusBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxStatusBar& value_statusBar = args_gurax.Pick<Value_wxStatusBar>();
	wxStatusBar* statusBar = value_statusBar.GetEntityPtr();
	// Function body
	pEntity_gurax->SetStatusBar(statusBar);
	return Gurax::Value::nil();
}

// wx.Frame#SetStatusBarPane(n as Number)
Gurax_DeclareMethodAlias(wxFrame, SetStatusBarPane_gurax, "SetStatusBarPane")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, SetStatusBarPane_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetStatusBarPane(n);
	return Gurax::Value::nil();
}

// wx.Frame#SetStatusText(text as String, number? as Number)
Gurax_DeclareMethodAlias(wxFrame, SetStatusText_gurax, "SetStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, SetStatusText_gurax, processor_gurax, argument_gurax)
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

// wx.Frame#SetStatusWidths(widths_field[] as Number)
Gurax_DeclareMethodAlias(wxFrame, SetStatusWidths_gurax, "SetStatusWidths")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("widths_field", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, SetStatusWidths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto widths_field = args_gurax.PickNumList<int>();
	// Function body
	pEntity_gurax->SetStatusWidths(widths_field.sizeT<int>(), widths_field.data());
	return Value::nil();
}

// wx.Frame#SetToolBar(toolBar as wx.ToolBar)
Gurax_DeclareMethodAlias(wxFrame, SetToolBar_gurax, "SetToolBar")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("toolBar", VTYPE_wxToolBar, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, SetToolBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxToolBar& value_toolBar = args_gurax.Pick<Value_wxToolBar>();
	wxToolBar* toolBar = value_toolBar.GetEntityPtr();
	// Function body
	pEntity_gurax->SetToolBar(toolBar);
	return Gurax::Value::nil();
}

// wx.Frame#PushStatusText(text as String, number? as Number)
Gurax_DeclareMethodAlias(wxFrame, PushStatusText_gurax, "PushStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, PushStatusText_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->PushStatusText(text, number);
	return Gurax::Value::nil();
}

// wx.Frame#PopStatusText(number? as Number)
Gurax_DeclareMethodAlias(wxFrame, PopStatusText_gurax, "PopStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFrame, PopStatusText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool number_validFlag = args_gurax.IsValid();
	int number = number_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->PopStatusText(number);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFrame
//------------------------------------------------------------------------------
VType_wxFrame VTYPE_wxFrame("Frame");

void VType_wxFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxTopLevelWindow, Flag::Mutable, Gurax_CreateConstructor(Frame_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFrame, Centre_gurax));
	Assign(Gurax_CreateMethod(wxFrame, Create_gurax));
	Assign(Gurax_CreateMethod(wxFrame, CreateStatusBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, CreateToolBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, GetClientAreaOrigin_gurax));
	Assign(Gurax_CreateMethod(wxFrame, GetMenuBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, GetStatusBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, GetStatusBarPane_gurax));
	Assign(Gurax_CreateMethod(wxFrame, GetToolBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, ProcessCommand_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetMenuBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetStatusBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetStatusBarPane_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetStatusText_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetStatusWidths_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetToolBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, PushStatusText_gurax));
	Assign(Gurax_CreateMethod(wxFrame, PopStatusText_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFrame
//------------------------------------------------------------------------------
VType& Value_wxFrame::vtype = VTYPE_wxFrame;

String Value_wxFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Frame");
}

//------------------------------------------------------------------------------
// Value_wxFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
