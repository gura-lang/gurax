//==============================================================================
// VType_wxGridCellEnumRenderer.cpp
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

${help.ComposePropertyHelp(wx.GridCellEnumRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellEnumRenderer, `en)}

${help.ComposeMethodHelp(wx.GridCellEnumRenderer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellEnumRenderer(choices? as String) {block?}
Gurax_DeclareConstructorAlias(GridCellEnumRenderer_gurax, "GridCellEnumRenderer")
{
	Declare(VTYPE_wxGridCellEnumRenderer, Flag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellEnumRenderer.");
}

Gurax_ImplementConstructorEx(GridCellEnumRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* choices = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	wxGridCellEnumRenderer* pEntity_gurax = new wxGridCellEnumRenderer(choices);
	RefPtr<Value_wxGridCellEnumRenderer> pValue_gurax(new Value_wxGridCellEnumRenderer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellEnumRenderer#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellEnumRenderer, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridCellEnumRenderer, SetParameters_gurax, processor_gurax, argument_gurax)
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
// VType_wxGridCellEnumRenderer
//------------------------------------------------------------------------------
VType_wxGridCellEnumRenderer VTYPE_wxGridCellEnumRenderer("GridCellEnumRenderer");

void VType_wxGridCellEnumRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellStringRenderer, Flag::Mutable, Gurax_CreateConstructor(GridCellEnumRenderer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellEnumRenderer, SetParameters_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellEnumRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellEnumRenderer::vtype = VTYPE_wxGridCellEnumRenderer;

String Value_wxGridCellEnumRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellEnumRenderer");
}

Gurax_EndModuleScope(wx)
