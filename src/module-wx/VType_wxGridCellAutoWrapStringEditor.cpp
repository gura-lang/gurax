//==============================================================================
// VType_wxGridCellAutoWrapStringEditor.cpp
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

${help.ComposePropertyHelp(wx.GridCellAutoWrapStringEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellAutoWrapStringEditor, `en)}

${help.ComposeMethodHelp(wx.GridCellAutoWrapStringEditor, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellAutoWrapStringEditor() {block?}
Gurax_DeclareConstructorAlias(GridCellAutoWrapStringEditor_gurax, "GridCellAutoWrapStringEditor")
{
	Declare(VTYPE_wxGridCellAutoWrapStringEditor, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridCellAutoWrapStringEditor.");
}

Gurax_ImplementConstructorEx(GridCellAutoWrapStringEditor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellAutoWrapStringEditor(
		wxGridCellAutoWrapStringEditor()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellAutoWrapStringEditor
//------------------------------------------------------------------------------
VType_wxGridCellAutoWrapStringEditor VTYPE_wxGridCellAutoWrapStringEditor("GridCellAutoWrapStringEditor");

void VType_wxGridCellAutoWrapStringEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellTextEditor, Flag::Mutable, Gurax_CreateConstructor(GridCellAutoWrapStringEditor_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellAutoWrapStringEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellAutoWrapStringEditor::vtype = VTYPE_wxGridCellAutoWrapStringEditor;

String Value_wxGridCellAutoWrapStringEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellAutoWrapStringEditor");
}

Gurax_EndModuleScope(wx)
