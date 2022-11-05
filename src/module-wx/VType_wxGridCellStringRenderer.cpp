//==============================================================================
// VType_wxGridCellStringRenderer.cpp
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

${help.ComposePropertyHelp(wx.GridCellStringRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellStringRenderer, `en)}

${help.ComposeMethodHelp(wx.GridCellStringRenderer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellStringRenderer() {block?}
Gurax_DeclareConstructorAlias(GridCellStringRenderer_gurax, "GridCellStringRenderer")
{
	Declare(VTYPE_wxGridCellStringRenderer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellStringRenderer.");
}

Gurax_ImplementConstructorEx(GridCellStringRenderer_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxGridCellStringRenderer* pEntity_gurax = new wxGridCellStringRenderer();
	RefPtr<Value_wxGridCellStringRenderer> pValue_gurax(new Value_wxGridCellStringRenderer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellStringRenderer
//------------------------------------------------------------------------------
VType_wxGridCellStringRenderer VTYPE_wxGridCellStringRenderer("GridCellStringRenderer");

void VType_wxGridCellStringRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellRenderer, Flag::Mutable, Gurax_CreateConstructor(GridCellStringRenderer_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellStringRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellStringRenderer::vtype = VTYPE_wxGridCellStringRenderer;

String Value_wxGridCellStringRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellStringRenderer");
}

Gurax_EndModuleScope(wx)
