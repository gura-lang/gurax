//==============================================================================
// VType_wxControl.cpp
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
	Declare(VTYPE_wxControl, Flag::None);
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
		"Creates a `wx.Control` instance.");
}

Gurax_ImplementConstructor(Control)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_wxWindow>().GetEntity() : nullptr;
	wxWindowID id = args.PickNumber<wxWindowID>();
	const char* title = args.PickString();
	const wxPoint& pos = args.IsValid()? args.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args.IsValid()? args.PickNumber<long>() : wxDEFAULT_wxControl_STYLE;
	const char* name = args.IsValid()? args.PickString() : wxControlNameStr;
	// Function body
	auto pEntity = new Value_wxControl::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxControl> pValue(new Value_wxControl(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}
*/

// wx.Control() {block?}
Gurax_DeclareConstructor(Control)
{
	Declare(VTYPE_wxControl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Control` instance.");
}

Gurax_ImplementConstructor(Control)
{
	// Function body
	auto pEntity = new Value_wxControl::EntityT();
	RefPtr<Value_wxControl> pValue(new Value_wxControl(pEntity));
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
// VType_wxControl
//------------------------------------------------------------------------------
VType_wxControl VTYPE_wxControl("Control");

void VType_wxControl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Control));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Control, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Control, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxControl
//------------------------------------------------------------------------------
VType& Value_wxControl::vtype = VTYPE_wxControl;

String Value_wxControl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Control");
}

//------------------------------------------------------------------------------
// Value_wxControl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
