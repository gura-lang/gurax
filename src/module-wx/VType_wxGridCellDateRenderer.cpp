﻿//==============================================================================
// VType_wxGridCellDateRenderer.cpp
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

${help.ComposePropertyHelp(wx.GridCellDateRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellDateRenderer, `en)}

${help.ComposeMethodHelp(wx.GridCellDateRenderer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellDateRenderer(outformat? as String) {block?}
Gurax_DeclareConstructorAlias(GridCellDateRenderer_gurax, "GridCellDateRenderer")
{
	Declare(VTYPE_wxGridCellDateRenderer, Flag::None);
	DeclareArg("outformat", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.GridCellDateRenderer.
)**");
}

Gurax_ImplementConstructorEx(GridCellDateRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* outformat = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	wxGridCellDateRenderer* pEntity_gurax = new wxGridCellDateRenderer(outformat);
	RefPtr<Value_wxGridCellDateRenderer> pValue_gurax(new Value_wxGridCellDateRenderer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellDateRenderer#SetParameters(params as String)
Gurax_DeclareMethodAlias(wxGridCellDateRenderer, SetParameters_gurax, "SetParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("params", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxGridCellDateRenderer, SetParameters_gurax, processor_gurax, argument_gurax)
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
// VType_wxGridCellDateRenderer
//------------------------------------------------------------------------------
VType_wxGridCellDateRenderer VTYPE_wxGridCellDateRenderer("GridCellDateRenderer");

void VType_wxGridCellDateRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellStringRenderer, Flag::Mutable, Gurax_CreateConstructor(GridCellDateRenderer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellDateRenderer, SetParameters_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellDateRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellDateRenderer::vtype = VTYPE_wxGridCellDateRenderer;

String Value_wxGridCellDateRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellDateRenderer");
}

Gurax_EndModuleScope(wx)
