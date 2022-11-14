﻿//==============================================================================
// VType_wxGridCellBoolRenderer.cpp
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

${help.ComposePropertyHelp(wx.GridCellBoolRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellBoolRenderer, `en)}

${help.ComposeMethodHelp(wx.GridCellBoolRenderer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellBoolRenderer() {block?}
Gurax_DeclareConstructorAlias(GridCellBoolRenderer_gurax, "GridCellBoolRenderer")
{
	Declare(VTYPE_wxGridCellBoolRenderer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.GridCellBoolRenderer.
)**");
}

Gurax_ImplementConstructorEx(GridCellBoolRenderer_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxGridCellBoolRenderer* pEntity_gurax = new wxGridCellBoolRenderer();
	RefPtr<Value_wxGridCellBoolRenderer> pValue_gurax(new Value_wxGridCellBoolRenderer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellBoolRenderer
//------------------------------------------------------------------------------
VType_wxGridCellBoolRenderer VTYPE_wxGridCellBoolRenderer("GridCellBoolRenderer");

void VType_wxGridCellBoolRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellRenderer, Flag::Mutable, Gurax_CreateConstructor(GridCellBoolRenderer_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellBoolRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellBoolRenderer::vtype = VTYPE_wxGridCellBoolRenderer;

String Value_wxGridCellBoolRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellBoolRenderer");
}

Gurax_EndModuleScope(wx)
