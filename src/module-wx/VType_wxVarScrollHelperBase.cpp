//==============================================================================
// VType_wxVarScrollHelperBase.cpp
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

${help.ComposePropertyHelp(wxVarScrollHelperBase)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxVarScrollHelperBase)}

${help.ComposeMethodHelp(wxVarScrollHelperBase)}
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
// VType_wxVarScrollHelperBase
//------------------------------------------------------------------------------
VType_wxVarScrollHelperBase VTYPE_wxVarScrollHelperBase("VarScrollHelperBase");

void VType_wxVarScrollHelperBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxVarScrollHelperBase
//------------------------------------------------------------------------------
VType& Value_wxVarScrollHelperBase::vtype = VTYPE_wxVarScrollHelperBase;

String Value_wxVarScrollHelperBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VarScrollHelperBase");
}

Gurax_EndModuleScope(wx)
