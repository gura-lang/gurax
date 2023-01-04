﻿//==============================================================================
// VType_wxGridCellEnumEditor.cpp
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

${help.ComposePropertyHelp(wx.GridCellEnumEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellEnumEditor, `en)}

${help.ComposeMethodHelp(wx.GridCellEnumEditor, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GridCellEnumEditor, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GridCellEnumEditor, `ja)}

${help.ComposeMethodHelp(wx.GridCellEnumEditor, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellEnumEditor(choices? as String) {block?}
Gurax_DeclareConstructorAlias(GridCellEnumEditor_gurax, "GridCellEnumEditor")
{
	Declare(VTYPE_wxGridCellEnumEditor, Flag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(GridCellEnumEditor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* choices = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellEnumEditor(
		wxGridCellEnumEditor(choices)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellEnumEditor
//------------------------------------------------------------------------------
VType_wxGridCellEnumEditor VTYPE_wxGridCellEnumEditor("GridCellEnumEditor");

void VType_wxGridCellEnumEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGridCellChoiceEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellEnumEditor_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellEnumEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellEnumEditor::vtype = VTYPE_wxGridCellEnumEditor;

String Value_wxGridCellEnumEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellEnumEditor");
}

Gurax_EndModuleScope(wx)
