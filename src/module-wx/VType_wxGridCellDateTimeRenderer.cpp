//==============================================================================
// VType_wxGridCellDateTimeRenderer.cpp
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
// wx.GridCellDateTimeRenderer(outformat? as String, informat? as String) {block?}
Gurax_DeclareConstructorAlias(GridCellDateTimeRenderer_gurax, "GridCellDateTimeRenderer")
{
	Declare(VTYPE_wxGridCellDateTimeRenderer, Flag::None);
	DeclareArg("outformat", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("informat", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellDateTimeRenderer.");
}

Gurax_ImplementConstructorEx(GridCellDateTimeRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* outformat = args_gurax.IsValid()? args_gurax.PickString() : wxDefaultDateTimeFormat;
	const char* informat = args_gurax.IsValid()? args_gurax.PickString() : wxDefaultDateTimeFormat;
	// Function body
	wxGridCellDateTimeRenderer* pEntity_gurax = new wxGridCellDateTimeRenderer(outformat, informat);
	RefPtr<Value_wxGridCellDateTimeRenderer> pValue_gurax(new Value_wxGridCellDateTimeRenderer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellDateTimeRenderer#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellDateTimeRenderer, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridCellDateTimeRenderer, SetParameters_gurax, processor_gurax, argument_gurax)
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
// VType_wxGridCellDateTimeRenderer
//------------------------------------------------------------------------------
VType_wxGridCellDateTimeRenderer VTYPE_wxGridCellDateTimeRenderer("GridCellDateTimeRenderer");

void VType_wxGridCellDateTimeRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellDateRenderer, Flag::Mutable, Gurax_CreateConstructor(GridCellDateTimeRenderer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellDateTimeRenderer, SetParameters_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellDateTimeRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellDateTimeRenderer::vtype = VTYPE_wxGridCellDateTimeRenderer;

String Value_wxGridCellDateTimeRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellDateTimeRenderer");
}

Gurax_EndModuleScope(wx)
