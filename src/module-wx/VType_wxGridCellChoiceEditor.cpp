﻿//==============================================================================
// VType_wxGridCellChoiceEditor.cpp
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

${help.ComposePropertyHelp(wx.GridCellChoiceEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellChoiceEditor, `en)}

${help.ComposeMethodHelp(wx.GridCellChoiceEditor, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellChoiceEditor(choices[] as String, allowOthers? as Bool) {block?}
Gurax_DeclareConstructorAlias(GridCellChoiceEditor_gurax, "GridCellChoiceEditor")
{
	Declare(VTYPE_wxGridCellChoiceEditor, Flag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("allowOthers", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.GridCellChoiceEditor.
)**");
}

Gurax_ImplementConstructorEx(GridCellChoiceEditor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString choices = Util::CreateArrayString(args_gurax.PickList());
	bool allowOthers = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellChoiceEditor(
		wxGridCellChoiceEditor(choices, allowOthers)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellChoiceEditor#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellChoiceEditor, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGridCellChoiceEditor, SetParameters_gurax, processor_gurax, argument_gurax)
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
// VType_wxGridCellChoiceEditor
//------------------------------------------------------------------------------
VType_wxGridCellChoiceEditor VTYPE_wxGridCellChoiceEditor("GridCellChoiceEditor");

void VType_wxGridCellChoiceEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellChoiceEditor_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellChoiceEditor, SetParameters_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellChoiceEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellChoiceEditor::vtype = VTYPE_wxGridCellChoiceEditor;

String Value_wxGridCellChoiceEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellChoiceEditor");
}

Gurax_EndModuleScope(wx)
