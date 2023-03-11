﻿//==============================================================================
// VType_wxStaticBox.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.StaticBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StaticBox, `en)}

${help.ComposeMethodHelp(wx.StaticBox, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.StaticBox, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.StaticBox, `ja)}

${help.ComposeMethodHelp(wx.StaticBox, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StaticBox(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(StaticBox_gurax, "StaticBox")
{
	Declare(VTYPE_wxStaticBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(StaticBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStaticBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxStaticBox::EntityT(parent, id, label, pos, size, style, name);
	RefPtr<Value_wxStaticBox> pValue_gurax(new Value_wxStaticBox(pEntity_gurax));
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
// VType_wxStaticBox
//------------------------------------------------------------------------------
VType_wxStaticBox VTYPE_wxStaticBox("StaticBox");

void VType_wxStaticBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StaticBox_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxStaticBox
//------------------------------------------------------------------------------
VType& Value_wxStaticBox::vtype = VTYPE_wxStaticBox;

String Value_wxStaticBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StaticBox");
}

//------------------------------------------------------------------------------
// Value_wxStaticBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
