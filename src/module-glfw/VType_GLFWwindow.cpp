//==============================================================================
// VType_GLFWwindow.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

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
// VType_GLFWwindow
//------------------------------------------------------------------------------
VType_GLFWwindow VTYPE_GLFWwindow("GLFWwindow");

void VType_GLFWwindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_GLFWwindow
//------------------------------------------------------------------------------
VType& Value_GLFWwindow::vtype = VTYPE_GLFWwindow;

String Value_GLFWwindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWwindow");
}

Gurax_EndModuleScope(glfw)
