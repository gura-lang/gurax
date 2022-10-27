//==============================================================================
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellEnumEditor.");
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
