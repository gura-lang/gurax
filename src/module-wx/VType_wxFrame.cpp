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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
	long style = args_gurax.IsValid()? args_gurax.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFrameNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxFrame::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxFrame> pValue_gurax(new Value_wxFrame(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Frame#CreateStatusBar(number? as Number, style? as Number, id? as Number, name? as String)
Gurax_DeclareMethodAlias(wxFrame, CreateStatusBar_gurax, "CreateStatusBar")
{
	Declare(VTYPE_wxFrame, Flag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
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
	int number = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 1;
	long style = args_gurax.IsValid()? args_gurax.PickNumber<long>() : wxSTB_DEFAULT_STYLE;
	wxWindowID id = args_gurax.IsValid()? args_gurax.PickNumber<wxWindowID>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStatusBarNameStr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFrame(
		pEntity_gurax->CreateStatusBar(number, style, id, name)));
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
	int number = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->SetStatusText(text, number);
	return Gurax::Value::nil();
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
	wxMenuBar* menuBar = args_gurax.Pick<Value_wxMenuBar>().GetEntityPtr();
	// Function body
	pEntity_gurax->SetMenuBar(menuBar);
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Frame_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFrame, CreateStatusBar_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetStatusText_gurax));
	Assign(Gurax_CreateMethod(wxFrame, SetMenuBar_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFrame
//------------------------------------------------------------------------------
VType& Value_wxFrame::vtype = VTYPE_wxFrame;

String Value_wxFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Frame");
}

Gurax_EndModuleScope(wx)
