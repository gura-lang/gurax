﻿//==============================================================================
// VType_wxRibbonControl.cpp
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

${help.ComposePropertyHelp(wx.RibbonControl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonControl, `en)}

${help.ComposeMethodHelp(wx.RibbonControl, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonControl, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonControl, `ja)}

${help.ComposeMethodHelp(wx.RibbonControl, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RibbonControl(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(RibbonControl_gurax, "RibbonControl")
{
	Declare(VTYPE_wxRibbonControl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(RibbonControl_gurax, processor_gurax, argument_gurax)
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
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxControlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxRibbonControl::EntityT(parent, id, pos, size, style, validator, name);
	RefPtr<Value_wxRibbonControl> pValue_gurax(new Value_wxRibbonControl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonControl#SetArtProvider(art as wx.RibbonArtProvider)
Gurax_DeclareMethodAlias(wxRibbonControl, SetArtProvider_gurax, "SetArtProvider")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("art", VTYPE_wxRibbonArtProvider, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonControl, SetArtProvider_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonArtProvider& value_art = args_gurax.Pick<Value_wxRibbonArtProvider>();
	wxRibbonArtProvider* art = value_art.GetEntityPtr();
	// Function body
	pEntity_gurax->SetArtProvider(art);
	return Gurax::Value::nil();
}

// wx.RibbonControl#GetArtProvider() {block?}
Gurax_DeclareMethodAlias(wxRibbonControl, GetArtProvider_gurax, "GetArtProvider")
{
	Declare(VTYPE_wxRibbonArtProvider, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonControl, GetArtProvider_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonArtProvider(
		pEntity_gurax->GetArtProvider()));
}

// wx.RibbonControl#IsSizingContinuous()
Gurax_DeclareMethodAlias(wxRibbonControl, IsSizingContinuous_gurax, "IsSizingContinuous")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonControl, IsSizingContinuous_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSizingContinuous();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonControl#GetNextSmallerSize(direction as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonControl, GetNextSmallerSize_gurax, "GetNextSmallerSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonControl, GetNextSmallerSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxOrientation direction = args_gurax.PickNumber<wxOrientation>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetNextSmallerSize(direction)));
}

// wx.RibbonControl#GetNextLargerSize(direction as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonControl, GetNextLargerSize_gurax, "GetNextLargerSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonControl, GetNextLargerSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxOrientation direction = args_gurax.PickNumber<wxOrientation>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetNextLargerSize(direction)));
}

// wx.RibbonControl#Realize()
Gurax_DeclareMethodAlias(wxRibbonControl, Realize_gurax, "Realize")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonControl, Realize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Realize();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonControl#Realise()
Gurax_DeclareMethodAlias(wxRibbonControl, Realise_gurax, "Realise")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonControl, Realise_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Realise();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonControl#GetAncestorRibbonBar() {block?}
Gurax_DeclareMethodAlias(wxRibbonControl, GetAncestorRibbonBar_gurax, "GetAncestorRibbonBar")
{
	Declare(VTYPE_wxRibbonBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonControl, GetAncestorRibbonBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonBar(
		pEntity_gurax->GetAncestorRibbonBar()));
}

// wx.RibbonControl#GetBestSizeForParentSize(parentSize as wx.Size) {block?}
Gurax_DeclareMethodAlias(wxRibbonControl, GetBestSizeForParentSize_gurax, "GetBestSizeForParentSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("parentSize", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonControl, GetBestSizeForParentSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_parentSize = args_gurax.Pick<Value_wxSize>();
	const wxSize& parentSize = value_parentSize.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetBestSizeForParentSize(parentSize)));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonControl
//------------------------------------------------------------------------------
VType_wxRibbonControl VTYPE_wxRibbonControl("RibbonControl");

void VType_wxRibbonControl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(RibbonControl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonControl, SetArtProvider_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, GetArtProvider_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, IsSizingContinuous_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, GetNextSmallerSize_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, GetNextLargerSize_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, Realize_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, Realise_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, GetAncestorRibbonBar_gurax));
	Assign(Gurax_CreateMethod(wxRibbonControl, GetBestSizeForParentSize_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonControl
//------------------------------------------------------------------------------
VType& Value_wxRibbonControl::vtype = VTYPE_wxRibbonControl;

String Value_wxRibbonControl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonControl");
}

//------------------------------------------------------------------------------
// Value_wxRibbonControl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
