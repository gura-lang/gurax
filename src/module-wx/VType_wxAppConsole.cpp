//==============================================================================
// VType_wxAppConsole.cpp
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
// wx.AppConsole() {block?}
Gurax_DeclareConstructor(AppConsole)
{
	Declare(VTYPE_wxAppConsole, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.AppConsole` instance.");
}

Gurax_ImplementConstructor(AppConsole)
{
	// Function body
	auto pEntity = new Value_wxAppConsole::EntityT();
	RefPtr<Value_wxAppConsole> pValue(new Value_wxAppConsole(pEntity));
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
// VType_wxAppConsole
//------------------------------------------------------------------------------
VType_wxAppConsole VTYPE_wxAppConsole("AppConsole");

void VType_wxAppConsole::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(AppConsole));
	// Assignment of method
	//Assign(Gurax_CreateMethod(AppConsole, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(AppConsole, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxAppConsole
//------------------------------------------------------------------------------
VType& Value_wxAppConsole::vtype = VTYPE_wxAppConsole;

String Value_wxAppConsole::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AppConsole");
}


//------------------------------------------------------------------------------
// Value_wxAppConsole::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
