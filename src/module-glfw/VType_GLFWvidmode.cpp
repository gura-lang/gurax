//==============================================================================
// VType_GLFWvidmode.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glfw.GLFWvidmode, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glfw.GLFWvidmode, `en)}

${help.ComposeMethodHelp(glfw.GLFWvidmode, `en)}
)**";

//------------------------------------------------------------------------------
// VType_GLFWvidmode
//------------------------------------------------------------------------------
VType_GLFWvidmode VTYPE_GLFWvidmode("GLFWvidmode");

void VType_GLFWvidmode::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_GLFWvidmode
//------------------------------------------------------------------------------
VType& Value_GLFWvidmode::vtype = VTYPE_GLFWvidmode;

String Value_GLFWvidmode::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWvidmode");
}

Gurax_EndModuleScope(glfw)
