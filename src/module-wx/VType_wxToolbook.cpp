﻿//==============================================================================
// VType_wxToolbook.cpp
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

${help.ComposePropertyHelp(wx.Toolbook, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Toolbook, `en)}

${help.ComposeMethodHelp(wx.Toolbook, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Toolbook(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(Toolbook_gurax, "Toolbook")
{
	Declare(VTYPE_wxToolbook, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.Toolbook.
)**");
}

Gurax_ImplementConstructorEx(Toolbook_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	auto pEntity_gurax = new Value_wxToolbook::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxToolbook> pValue_gurax(new Value_wxToolbook(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxToolbook
//------------------------------------------------------------------------------
VType_wxToolbook VTYPE_wxToolbook("Toolbook");

void VType_wxToolbook::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBookCtrlBase, Flag::Mutable, Gurax_CreateConstructor(Toolbook_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxToolbook
//------------------------------------------------------------------------------
VType& Value_wxToolbook::vtype = VTYPE_wxToolbook;

String Value_wxToolbook::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Toolbook");
}

//------------------------------------------------------------------------------
// Value_wxToolbook::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
