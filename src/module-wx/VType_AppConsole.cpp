//==============================================================================
// VType_AppConsole.cpp
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
	Declare(VTYPE_AppConsole, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.AppConsole` instance.");
}

Gurax_ImplementConstructor(AppConsole)
{
	// Function body
	auto pEntity = new Value_AppConsole::EntityT();
	RefPtr<Value_AppConsole> pValue(new Value_AppConsole(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// wx.AppConsole#propSkeleton
Gurax_DeclareProperty_R(AppConsole, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(AppConsole, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_AppConsole
//------------------------------------------------------------------------------
VType_AppConsole VTYPE_AppConsole("AppConsole");

void VType_AppConsole::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(AppConsole));
	// Assignment of method
	//Assign(Gurax_CreateMethod(AppConsole, OnInit));
	// Assignment of property
	Assign(Gurax_CreateProperty(AppConsole, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_AppConsole
//------------------------------------------------------------------------------
VType& Value_AppConsole::vtype = VTYPE_AppConsole;

String Value_AppConsole::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AppConsole");
}


//------------------------------------------------------------------------------
// Value_AppConsole::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
