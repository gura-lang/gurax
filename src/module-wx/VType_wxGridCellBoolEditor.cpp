//==============================================================================
// VType_wxGridCellBoolEditor.cpp
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

${help.ComposePropertyHelp(wxGridCellBoolEditor)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxGridCellBoolEditor)}

${help.ComposeMethodHelp(wxGridCellBoolEditor)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellBoolEditor() {block?}
Gurax_DeclareConstructorAlias(GridCellBoolEditor_gurax, "GridCellBoolEditor")
{
	Declare(VTYPE_wxGridCellBoolEditor, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellBoolEditor.");
}

Gurax_ImplementConstructorEx(GridCellBoolEditor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellBoolEditor(
		wxGridCellBoolEditor()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellBoolEditor.IsTrueValue(value as String)
Gurax_DeclareClassMethodAlias(wxGridCellBoolEditor, IsTrueValue_gurax, "IsTrueValue")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxGridCellBoolEditor, IsTrueValue_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* value = args_gurax.PickString();
	// Function body
	bool rtn = wxGridCellBoolEditor::IsTrueValue(value);
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellBoolEditor.UseStringValues(valueTrue? as String, valueFalse? as String)
Gurax_DeclareClassMethodAlias(wxGridCellBoolEditor, UseStringValues_gurax, "UseStringValues")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("valueTrue", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("valueFalse", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxGridCellBoolEditor, UseStringValues_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* valueTrue = args_gurax.IsValid()? args_gurax.PickString() : "1";
	const char* valueFalse = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	wxGridCellBoolEditor::UseStringValues(valueTrue, valueFalse);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellBoolEditor
//------------------------------------------------------------------------------
VType_wxGridCellBoolEditor VTYPE_wxGridCellBoolEditor("GridCellBoolEditor");

void VType_wxGridCellBoolEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellBoolEditor_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellBoolEditor, IsTrueValue_gurax));
	Assign(Gurax_CreateMethod(wxGridCellBoolEditor, UseStringValues_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellBoolEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellBoolEditor::vtype = VTYPE_wxGridCellBoolEditor;

String Value_wxGridCellBoolEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellBoolEditor");
}

Gurax_EndModuleScope(wx)
