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
// wx.Control(parent:nil as wx.Window, id as Number, title as String, pos as wx.Point, size as wx.Size, style as Number, name as String) {block?}
Gurax_DeclareConstructorAlias(Control_gurax, "Control")
{
	Declare(VTYPE_wxControl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Control.");
}

Gurax_ImplementConstructorEx(Control_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	int id = args_gurax.PickNumber<int>();
	const char* title = args_gurax.PickString();
	wxPoint& pos = args_gurax.Pick<Value_wxPoint>().GetEntity();
	wxSize& size = args_gurax.Pick<Value_wxSize>().GetEntity();
	int style = args_gurax.PickNumber<int>();
	const char* name = args_gurax.PickString();
	// Function body
	auto pEntity_gurax = new Value_wxControl::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxControl> pValue_gurax(new Value_wxControl(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
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
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Control_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxControl
//------------------------------------------------------------------------------
VType& Value_wxControl::vtype = VTYPE_wxControl;

String Value_wxControl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Control");
}

Gurax_EndModuleScope(wx)
