//==============================================================================
// VType_GLFWimage.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(GLFWimage)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(GLFWimage)}

${help.ComposeMethodHelp(GLFWimage)}
)**";

//------------------------------------------------------------------------------
// VType_GLFWimage
//------------------------------------------------------------------------------
VType_GLFWimage VTYPE_GLFWimage("GLFWimage");

void VType_GLFWimage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_GLFWimage
//------------------------------------------------------------------------------
VType& Value_GLFWimage::vtype = VTYPE_GLFWimage;

String Value_GLFWimage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWimage");
}

Gurax_EndModuleScope(glfw)
