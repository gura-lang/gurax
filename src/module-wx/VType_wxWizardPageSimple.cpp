//==============================================================================
// VType_wxWizardPageSimple.cpp
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

${help.ComposePropertyHelp(wx.WizardPageSimple, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.WizardPageSimple, `en)}

${help.ComposeMethodHelp(wx.WizardPageSimple, `en)}
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
// VType_wxWizardPageSimple
//------------------------------------------------------------------------------
VType_wxWizardPageSimple VTYPE_wxWizardPageSimple("WizardPageSimple");

void VType_wxWizardPageSimple::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWizardPage, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxWizardPageSimple
//------------------------------------------------------------------------------
VType& Value_wxWizardPageSimple::vtype = VTYPE_wxWizardPageSimple;

String Value_wxWizardPageSimple::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.WizardPageSimple");
}

//------------------------------------------------------------------------------
// Value_wxWizardPageSimple::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
