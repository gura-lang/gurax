//==============================================================================
// VType_Control.cpp
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
/*
// wx.Control(parent:nil as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructor(Control)
{
	Declare(VTYPE_Control, Flag::None);
	DeclareArg("parent", VTYPE_Window, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Point, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_Size, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Control` instance.");
}

Gurax_ImplementConstructor(Control)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_Window>().GetEntity() : nullptr;
	wxWindowID id = args.PickNumber<wxWindowID>();
	const char* title = args.PickString();
	const wxPoint& pos = args.IsValid()? args.Pick<Value_Point>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_Size>().GetEntity() : wxDefaultSize;
	long style = args.IsValid()? args.PickNumber<long>() : wxDEFAULT_Control_STYLE;
	const char* name = args.IsValid()? args.PickString() : wxControlNameStr;
	// Function body
	auto pEntity = new Value_Control::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_Control> pValue(new Value_Control(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}
*/

// wx.Control() {block?}
Gurax_DeclareConstructor(Control)
{
	Declare(VTYPE_Control, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Control` instance.");
}

Gurax_ImplementConstructor(Control)
{
	// Function body
	auto pEntity = new Value_Control::EntityT();
	RefPtr<Value_Control> pValue(new Value_Control(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Control
//------------------------------------------------------------------------------
VType_Control VTYPE_Control("Control");

void VType_Control::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Window, Flag::Mutable, Gurax_CreateConstructor(Control));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Control, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Control, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Control
//------------------------------------------------------------------------------
VType& Value_Control::vtype = VTYPE_Control;

String Value_Control::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Control");
}

//------------------------------------------------------------------------------
// Value_Control::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
