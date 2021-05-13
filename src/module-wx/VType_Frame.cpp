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
		"Creates a `wx.Frame` instance.");
}

Gurax_ImplementConstructor(Frame)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_Window>().GetEntity() : nullptr;
	wxWindowID id = args.PickNumber<wxWindowID>();
	const char* title = args.PickString();
	const wxPoint& pos = args.IsValid()? args.Pick<Value_Point>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_Size>().GetEntity() : wxDefaultSize;
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
	Declare(VTYPE_Window, Flag::Mutable, Gurax_CreateConstructor(Frame));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Frame, OnInit));
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
