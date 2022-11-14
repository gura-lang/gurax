﻿//==============================================================================
// VType_wxGridCellNumberEditor.cpp
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

${help.ComposePropertyHelp(wx.GridCellNumberEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellNumberEditor, `en)}

${help.ComposeMethodHelp(wx.GridCellNumberEditor, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellNumberEditor(min? as Number, max? as Number) {block?}
Gurax_DeclareConstructorAlias(GridCellNumberEditor_gurax, "GridCellNumberEditor")
{
	Declare(VTYPE_wxGridCellNumberEditor, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.GridCellNumberEditor.
)**");
}

Gurax_ImplementConstructorEx(GridCellNumberEditor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool min_validFlag = args_gurax.IsValid();
	int min = min_validFlag? args_gurax.PickNumber<int>() : -1;
	bool max_validFlag = args_gurax.IsValid();
	int max = max_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellNumberEditor(
		wxGridCellNumberEditor(min, max)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellNumberEditor#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellNumberEditor, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxGridCellNumberEditor, SetParameters_gurax, processor_gurax, argument_gurax)
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellNumberEditor
//------------------------------------------------------------------------------
VType_wxGridCellNumberEditor VTYPE_wxGridCellNumberEditor("GridCellNumberEditor");

void VType_wxGridCellNumberEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellTextEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellNumberEditor_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellNumberEditor, SetParameters_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellNumberEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellNumberEditor::vtype = VTYPE_wxGridCellNumberEditor;

String Value_wxGridCellNumberEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellNumberEditor");
}

Gurax_EndModuleScope(wx)
