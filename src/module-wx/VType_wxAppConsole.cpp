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
Gurax_DeclareConstructorAlias(AppConsole_gurax, "AppConsole")
{
	Declare(VTYPE_wxAppConsole, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.AppConsole.");
}

Gurax_ImplementConstructorEx(AppConsole_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxAppConsole::EntityT();
	RefPtr<Value_wxAppConsole> pValue_gurax(new Value_wxAppConsole(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
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
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(AppConsole_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAppConsole
//------------------------------------------------------------------------------
VType& Value_wxAppConsole::vtype = VTYPE_wxAppConsole;

String Value_wxAppConsole::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AppConsole");
}

Gurax_EndModuleScope(wx)
