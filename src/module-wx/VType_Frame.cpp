//==============================================================================
// VType_Frame.cpp
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
Gurax_DeclareConstructor(Frame)
{
	Declare(VTYPE_Frame, Flag::None);
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
		"Creates a `wx.Frame` instance.");
}

Gurax_ImplementConstructor(Frame)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_wxWindow>().GetEntity() : nullptr;
	wxWindowID id = args.PickNumber<wxWindowID>();
	const char* title = args.PickString();
	const wxPoint& pos = args.IsValid()? args.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args.IsValid()? args.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args.IsValid()? args.PickString() : wxFrameNameStr;
	// Function body
	auto pEntity = new Value_Frame::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_Frame> pValue(new Value_Frame(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Frame#CreateStatusBar(number? as Number, style? as Number, id? as Number, name? as String)
Gurax_DeclareMethod(Frame, CreateStatusBar)
{
	Declare(VTYPE_Frame, Flag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Frame, CreateStatusBar)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	int number = args.IsValid()? args.PickNumber<int>() : 1;
	long style = args.IsValid()? args.PickNumber<long>() : wxSTB_DEFAULT_STYLE;
	wxWindowID id = args.IsValid()? args.PickNumber<wxWindowID>() : 0;
	const char* name = args.IsValid()? args.PickString() : wxToolBarNameStr;
	// Function body
	wxStatusBar* rtn = pEntity->CreateStatusBar(number, style, id, name);
	return new Value_StatusBar(rtn);
}

// wx.Frame#SetMenuBar(menuBar as wx.MenuBar)
Gurax_DeclareMethod(Frame, SetMenuBar)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("menuBar", VTYPE_MenuBar, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Frame, SetMenuBar)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	wxMenuBar* menuBar = args.Pick<Value_MenuBar>().GetEntity();
	// Function body
	pEntity->SetMenuBar(menuBar);
	return Value::nil();
}

// wx.Frame#SetStatusText(text as String, number? as Number)
Gurax_DeclareMethod(Frame, SetStatusText)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Frame, SetStatusText)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	const char* text = args.PickString();
	int number = args.IsValid()? args.PickNumber<int>() : 0;
	// Function body
	pEntity->SetStatusText(text, number);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
VType_Frame VTYPE_Frame("Frame");

void VType_Frame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Frame));
	// Assignment of method
	Assign(Gurax_CreateMethod(Frame, CreateStatusBar));
	Assign(Gurax_CreateMethod(Frame, SetMenuBar));
	Assign(Gurax_CreateMethod(Frame, SetStatusText));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Frame, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------
VType& Value_Frame::vtype = VTYPE_Frame;

String Value_Frame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Frame");
}

//------------------------------------------------------------------------------
// Value_Frame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
