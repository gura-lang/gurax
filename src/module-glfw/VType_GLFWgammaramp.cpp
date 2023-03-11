//==============================================================================
// VType_GLFWgammaramp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glfw.GLFWgammaramp, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glfw.GLFWgammaramp, `en)}

${help.ComposeMethodHelp(glfw.GLFWgammaramp, `en)}
)""";

//------------------------------------------------------------------------------
// VType_GLFWgammaramp
//------------------------------------------------------------------------------
VType_GLFWgammaramp VTYPE_GLFWgammaramp("GLFWgammaramp");

void VType_GLFWgammaramp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_GLFWgammaramp
//------------------------------------------------------------------------------
VType& Value_GLFWgammaramp::vtype = VTYPE_GLFWgammaramp;

String Value_GLFWgammaramp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWgammaramp");
}

Gurax_EndModuleScope(glfw)
