//==============================================================================
// VType_wxAuiNotebookEvent.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAuiNotebookEvent
//------------------------------------------------------------------------------
VType_wxAuiNotebookEvent VTYPE_wxAuiNotebookEvent("AuiNotebookEvent");

void VType_wxAuiNotebookEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBookCtrlEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiNotebookEvent
//------------------------------------------------------------------------------
VType& Value_wxAuiNotebookEvent::vtype = VTYPE_wxAuiNotebookEvent;
EventValueFactoryDeriv<Value_wxAuiNotebookEvent> Value_wxAuiNotebookEvent::eventValueFactory;

String Value_wxAuiNotebookEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiNotebookEvent");
}

Gurax_EndModuleScope(wx)
