﻿//==============================================================================
// VType_wxVariant.cpp
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

${help.ComposePropertyHelp(wx.Variant, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Variant, `en)}

${help.ComposeMethodHelp(wx.Variant, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Variant, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Variant, `ja)}

${help.ComposeMethodHelp(wx.Variant, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Variant(value as Any, name? as String) {block?}
Gurax_DeclareConstructorAlias(Variant_gurax, "Variant")
{
	Declare(VTYPE_wxVariant, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Variant_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::Value& value = args_gurax.PickValue();
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	if (value.IsType(VTYPE_String)) {
		return new Value_wxVariant(wxVariant(Value_String::GetString(value), name));
	}
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxVariant
//------------------------------------------------------------------------------
VType_wxVariant VTYPE_wxVariant("Variant");

void VType_wxVariant::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Variant_gurax));
	// Assignment of method
}

Value* VType_wxVariant::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		return new Value_wxVariant(wxVariant(Value_String::GetString(value)));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_wxVariant
//------------------------------------------------------------------------------
VType& Value_wxVariant::vtype = VTYPE_wxVariant;

String Value_wxVariant::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Variant");
}

Gurax_EndModuleScope(wx)
