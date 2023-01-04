﻿//==============================================================================
// VType_wxGridCellTextEditor.cpp
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

${help.ComposePropertyHelp(wx.GridCellTextEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellTextEditor, `en)}

${help.ComposeMethodHelp(wx.GridCellTextEditor, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GridCellTextEditor, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GridCellTextEditor, `ja)}

${help.ComposeMethodHelp(wx.GridCellTextEditor, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellTextEditor(maxChars? as Number) {block?}
Gurax_DeclareConstructorAlias(GridCellTextEditor_gurax, "GridCellTextEditor")
{
	Declare(VTYPE_wxGridCellTextEditor, Flag::None);
	DeclareArg("maxChars", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(GridCellTextEditor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool maxChars_validFlag = args_gurax.IsValid();
	size_t maxChars = maxChars_validFlag? args_gurax.PickNumber<size_t>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellTextEditor(
		wxGridCellTextEditor(maxChars)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellTextEditor#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellTextEditor, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellTextEditor, SetParameters_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* params = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetParameters(params);
	return Gurax::Value::nil();
}

// wx.GridCellTextEditor#SetValidator(validator as wx.Validator)
Gurax_DeclareMethodAlias(wxGridCellTextEditor, SetValidator_gurax, "SetValidator")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellTextEditor, SetValidator_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxValidator& value_validator = args_gurax.Pick<Value_wxValidator>();
	const wxValidator& validator = value_validator.GetEntity();
	// Function body
	pEntity_gurax->SetValidator(validator);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellTextEditor
//------------------------------------------------------------------------------
VType_wxGridCellTextEditor VTYPE_wxGridCellTextEditor("GridCellTextEditor");

void VType_wxGridCellTextEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGridCellEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellTextEditor_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellTextEditor, SetParameters_gurax));
	Assign(Gurax_CreateMethod(wxGridCellTextEditor, SetValidator_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellTextEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellTextEditor::vtype = VTYPE_wxGridCellTextEditor;

String Value_wxGridCellTextEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellTextEditor");
}

Gurax_EndModuleScope(wx)
