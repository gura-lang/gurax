//==============================================================================
// VType_Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.Info, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.Info, `en)}

${help.ComposeMethodHelp(curl.Info, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Info
//------------------------------------------------------------------------------
VType_Info VTYPE_Info("Info");

void VType_Info::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Info, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Info, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Info
//------------------------------------------------------------------------------
VType& Value_Info::vtype = VTYPE_Info;

String Value_Info::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetInfo().ToString(ss));
}

Value* Value_Info::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetInfo().GetProperty(pSymbol);
}

Gurax_EndModuleScope(curl)
