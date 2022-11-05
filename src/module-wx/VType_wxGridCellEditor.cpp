//==============================================================================
// VType_wxGridCellEditor.cpp
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

${help.ComposePropertyHelp(wxGridCellEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxGridCellEditor, `en)}

${help.ComposeMethodHelp(wxGridCellEditor, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellEditor
//------------------------------------------------------------------------------
VType_wxGridCellEditor VTYPE_wxGridCellEditor("GridCellEditor");

void VType_wxGridCellEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxClientDataContainer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellEditor
//------------------------------------------------------------------------------
VType& Value_wxGridCellEditor::vtype = VTYPE_wxGridCellEditor;

String Value_wxGridCellEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellEditor");
}

Gurax_EndModuleScope(wx)
