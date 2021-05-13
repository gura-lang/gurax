//==============================================================================
// VType_StatusBar.cpp
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
// wx.StatusBar() {block?}
Gurax_DeclareConstructor(StatusBar)
{
	Declare(VTYPE_StatusBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.StatusBar` instance.");
}

Gurax_ImplementConstructor(StatusBar)
{
	// Function body
	auto pEntity = new Value_StatusBar::EntityT();
	RefPtr<Value_StatusBar> pValue(new Value_StatusBar(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_StatusBar
//------------------------------------------------------------------------------
VType_StatusBar VTYPE_StatusBar("StatusBar");

void VType_StatusBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Control, Flag::Mutable, Gurax_CreateConstructor(StatusBar));
	// Assignment of method
	//Assign(Gurax_CreateMethod(StatusBar, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(StatusBar, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_StatusBar
//------------------------------------------------------------------------------
VType& Value_StatusBar::vtype = VTYPE_StatusBar;

String Value_StatusBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StatusBar");
}

//------------------------------------------------------------------------------
// Value_StatusBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
