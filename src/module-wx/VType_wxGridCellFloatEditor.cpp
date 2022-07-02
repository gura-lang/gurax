//==============================================================================
// VType_wxGridCellFloatEditor.cpp
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
// wx.GridCellFloatEditor(width? as Number, precision? as Number, format? as Number) {block?}
Gurax_DeclareConstructorAlias(GridCellFloatEditor_gurax, "GridCellFloatEditor")
{
	Declare(VTYPE_wxGridCellFloatEditor, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("precision", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellFloatEditor.");
}

Gurax_ImplementConstructorEx(GridCellFloatEditor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : -1;
	bool precision_validFlag = args_gurax.IsValid();
	int precision = precision_validFlag? args_gurax.PickNumber<int>() : -1;
	bool format_validFlag = args_gurax.IsValid();
	int format = format_validFlag? args_gurax.PickNumber<int>() : wxGRID_FLOAT_FORMAT_DEFAULT;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellFloatEditor(
		wxGridCellFloatEditor(width, precision, format)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellFloatEditor#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellFloatEditor, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridCellFloatEditor, SetParameters_gurax, processor_gurax, argument_gurax)
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
// VType_wxGridCellFloatEditor
//------------------------------------------------------------------------------
VType_wxGridCellFloatEditor VTYPE_wxGridCellFloatEditor("GridCellFloatEditor");

void VType_wxGridCellFloatEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellTextEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellFloatEditor_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellFloatEditor, SetParameters_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellFloatEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellFloatEditor::vtype = VTYPE_wxGridCellFloatEditor;

String Value_wxGridCellFloatEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellFloatEditor");
}

Gurax_EndModuleScope(wx)
