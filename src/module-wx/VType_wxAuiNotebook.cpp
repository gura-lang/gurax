﻿//==============================================================================
// VType_wxAuiNotebook.cpp
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

${help.ComposePropertyHelp(wx.AuiNotebook, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AuiNotebook, `en)}

${help.ComposeMethodHelp(wx.AuiNotebook, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.AuiNotebook(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(AuiNotebook_gurax, "AuiNotebook")
{
	Declare(VTYPE_wxAuiNotebook, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.AuiNotebook.
)**");
}

Gurax_ImplementConstructorEx(AuiNotebook_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxAUI_NB_DEFAULT_STYLE;
	// Function body
	auto pEntity_gurax = new Value_wxAuiNotebook::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxAuiNotebook> pValue_gurax(new Value_wxAuiNotebook(pEntity_gurax));
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
// VType_wxAuiNotebook
//------------------------------------------------------------------------------
VType_wxAuiNotebook VTYPE_wxAuiNotebook("AuiNotebook");

void VType_wxAuiNotebook::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBookCtrlBase, Flag::Mutable, Gurax_CreateConstructor(AuiNotebook_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiNotebook
//------------------------------------------------------------------------------
VType& Value_wxAuiNotebook::vtype = VTYPE_wxAuiNotebook;

String Value_wxAuiNotebook::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiNotebook");
}

//------------------------------------------------------------------------------
// Value_wxAuiNotebook::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
