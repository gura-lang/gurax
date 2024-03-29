﻿//==============================================================================
// VType_wxHeaderColumnSimple.cpp
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

${help.ComposePropertyHelp(wx.HeaderColumnSimple, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HeaderColumnSimple, `en)}

${help.ComposeMethodHelp(wx.HeaderColumnSimple, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HeaderColumnSimple, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HeaderColumnSimple, `ja)}

${help.ComposeMethodHelp(wx.HeaderColumnSimple, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.HeaderColumnSimple(title as String, width? as Number, align? as Number, flags? as Number) {block?}
Gurax_DeclareConstructorAlias(HeaderColumnSimple_gurax, "HeaderColumnSimple")
{
	Declare(VTYPE_wxHeaderColumnSimple, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("align", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(HeaderColumnSimple_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString title(args_gurax.PickString());
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : wxCOL_WIDTH_DEFAULT;
	bool align_validFlag = args_gurax.IsValid();
	wxAlignment align = align_validFlag? args_gurax.PickNumber<wxAlignment>() : wxALIGN_NOT;
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : wxCOL_DEFAULT_FLAGS;
	// Function body
	auto pEntity_gurax = new wxHeaderColumnSimple(title, width, align, flags);
	RefPtr<Value_wxHeaderColumnSimple> pValue_gurax(new Value_wxHeaderColumnSimple(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HeaderColumnSimple#SetTitle(title as String)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetTitle_gurax, "SetTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString title(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetTitle(title);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#GetTitle()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, GetTitle_gurax, "GetTitle")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, GetTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetTitle();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.HeaderColumnSimple#SetBitmap(bitmap as wx.Bitmap)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetBitmap_gurax, "SetBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	// Function body
	pEntity_gurax->SetBitmap(bitmap);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#GetBitmap() {block?}
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, GetBitmap_gurax, "GetBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, GetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(pEntity_gurax->GetBitmap()));
}

// wx.HeaderColumnSimple#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetWidth(width);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#GetWidth()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderColumnSimple#SetMinWidth(minWidth as Number)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetMinWidth_gurax, "SetMinWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minWidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetMinWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minWidth = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinWidth(minWidth);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#GetMinWidth()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, GetMinWidth_gurax, "GetMinWidth")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, GetMinWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMinWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderColumnSimple#SetAlignment(align as Number)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetAlignment_gurax, "SetAlignment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("align", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxAlignment align = args_gurax.PickNumber<wxAlignment>();
	// Function body
	pEntity_gurax->SetAlignment(align);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#GetAlignment()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, GetAlignment_gurax, "GetAlignment")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, GetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxAlignment rtn = pEntity_gurax->GetAlignment();
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderColumnSimple#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFlags(flags);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#GetFlags()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, GetFlags_gurax, "GetFlags")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, GetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderColumnSimple#IsSortKey()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, IsSortKey_gurax, "IsSortKey")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, IsSortKey_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSortKey();
	return new Gurax::Value_Bool(rtn);
}

// wx.HeaderColumnSimple#SetSortOrder(ascending as Bool)
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, SetSortOrder_gurax, "SetSortOrder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ascending", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, SetSortOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool ascending = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetSortOrder(ascending);
	return Gurax::Value::nil();
}

// wx.HeaderColumnSimple#IsSortOrderAscending()
Gurax_DeclareMethodAlias(wxHeaderColumnSimple, IsSortOrderAscending_gurax, "IsSortOrderAscending")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderColumnSimple, IsSortOrderAscending_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSortOrderAscending();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHeaderColumnSimple
//------------------------------------------------------------------------------
VType_wxHeaderColumnSimple VTYPE_wxHeaderColumnSimple("HeaderColumnSimple");

void VType_wxHeaderColumnSimple::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxSettableHeaderColumn, Flag::Mutable, Gurax_CreateConstructor(HeaderColumnSimple_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetTitle_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, GetTitle_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, GetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetMinWidth_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, GetMinWidth_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, GetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, GetFlags_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, IsSortKey_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, SetSortOrder_gurax));
	Assign(Gurax_CreateMethod(wxHeaderColumnSimple, IsSortOrderAscending_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHeaderColumnSimple
//------------------------------------------------------------------------------
VType& Value_wxHeaderColumnSimple::vtype = VTYPE_wxHeaderColumnSimple;

String Value_wxHeaderColumnSimple::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HeaderColumnSimple");
}

Gurax_EndModuleScope(wx)
