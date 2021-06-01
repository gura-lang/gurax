//==============================================================================
// VType_wxPanel.cpp
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
// wx.Panel(parent:nil as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructor(Panel)
{
	Declare(VTYPE_wxPanel, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Panel` instance.");
}

Gurax_ImplementConstructor(Panel)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	wxWindowID id = args.IsValid()? args.PickNumber<wxWindowID>() : wxID_ANY;
	const char* title = args.PickString();
	const wxPoint& pos = args.IsValid()? args.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args.IsValid()? args.PickNumber<long>() : wxTAB_TRAVERSAL;
	const char* name = args.IsValid()? args.PickString() : wxPanelNameStr;
	// Function body
	auto pEntity = new Value_wxPanel::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxPanel> pValue(new Value_wxPanel(pEntity));
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
// VType_wxPanel
//------------------------------------------------------------------------------
VType_wxPanel VTYPE_wxPanel("Panel");

void VType_wxPanel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Panel));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Panel, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Panel, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxPanel
//------------------------------------------------------------------------------
VType& Value_wxPanel::vtype = VTYPE_wxPanel;

String Value_wxPanel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Panel");
}

//------------------------------------------------------------------------------
// Value_wxPanel::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
