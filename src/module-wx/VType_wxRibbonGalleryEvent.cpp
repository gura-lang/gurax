﻿//==============================================================================
// VType_wxRibbonGalleryEvent.cpp
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

${help.ComposePropertyHelp(wx.RibbonGalleryEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonGalleryEvent, `en)}

${help.ComposeMethodHelp(wx.RibbonGalleryEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonGalleryEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonGalleryEvent, `ja)}

${help.ComposeMethodHelp(wx.RibbonGalleryEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonGalleryEvent#GetGallery() {block?}
Gurax_DeclareMethodAlias(wxRibbonGalleryEvent, GetGallery_gurax, "GetGallery")
{
	Declare(VTYPE_wxRibbonGallery, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGalleryEvent, GetGallery_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGallery(pEntity_gurax->GetGallery()));
}

// wx.RibbonGalleryEvent#GetGalleryItem() {block?}
Gurax_DeclareMethodAlias(wxRibbonGalleryEvent, GetGalleryItem_gurax, "GetGalleryItem")
{
	Declare(VTYPE_wxRibbonGalleryItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGalleryEvent, GetGalleryItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGalleryItem(pEntity_gurax->GetGalleryItem()));
}

// wx.RibbonGalleryEvent#SetGallery(gallery as wx.RibbonGallery)
Gurax_DeclareMethodAlias(wxRibbonGalleryEvent, SetGallery_gurax, "SetGallery")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gallery", VTYPE_wxRibbonGallery, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGalleryEvent, SetGallery_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGallery& value_gallery = args_gurax.Pick<Value_wxRibbonGallery>();
	wxRibbonGallery* gallery = value_gallery.GetEntityPtr();
	// Function body
	pEntity_gurax->SetGallery(gallery);
	return Gurax::Value::nil();
}

// wx.RibbonGalleryEvent#SetGalleryItem(item as wx.RibbonGalleryItem)
Gurax_DeclareMethodAlias(wxRibbonGalleryEvent, SetGalleryItem_gurax, "SetGalleryItem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonGalleryItem, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGalleryEvent, SetGalleryItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGalleryItem& value_item = args_gurax.Pick<Value_wxRibbonGalleryItem>();
	wxRibbonGalleryItem* item = value_item.GetEntityPtr();
	// Function body
	pEntity_gurax->SetGalleryItem(item);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonGalleryEvent
//------------------------------------------------------------------------------
VType_wxRibbonGalleryEvent VTYPE_wxRibbonGalleryEvent("RibbonGalleryEvent");

void VType_wxRibbonGalleryEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonGalleryEvent, GetGallery_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGalleryEvent, GetGalleryItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGalleryEvent, SetGallery_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGalleryEvent, SetGalleryItem_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonGalleryEvent
//------------------------------------------------------------------------------
VType& Value_wxRibbonGalleryEvent::vtype = VTYPE_wxRibbonGalleryEvent;
EventValueFactoryDeriv<Value_wxRibbonGalleryEvent> Value_wxRibbonGalleryEvent::eventValueFactory;

String Value_wxRibbonGalleryEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonGalleryEvent");
}

Gurax_EndModuleScope(wx)
