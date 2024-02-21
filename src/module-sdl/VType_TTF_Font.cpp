//==============================================================================
// VType_TTF_Font.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.TTF_Font, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.TTF_Font, `en)}

${help.ComposeMethodHelp(sdl.TTF_Font, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_TTF_Font
//------------------------------------------------------------------------------
VType_TTF_Font VTYPE_TTF_Font("TTF_Font");

void VType_TTF_Font::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(TTF_Font, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(TTF_Font, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_TTF_Font
//------------------------------------------------------------------------------
VType& Value_TTF_Font::vtype = VTYPE_TTF_Font;

String Value_TTF_Font::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.TTF_Font");
}

Gurax_EndModuleScope(sdl)
