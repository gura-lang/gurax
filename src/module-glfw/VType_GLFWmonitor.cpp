//==============================================================================
// VType_GLFWmonitor.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glfw.GLFWmonitor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glfw.GLFWmonitor, `en)}

${help.ComposeMethodHelp(glfw.GLFWmonitor, `en)}
)**";

//------------------------------------------------------------------------------
// VType_GLFWmonitor
//------------------------------------------------------------------------------
VType_GLFWmonitor VTYPE_GLFWmonitor("GLFWmonitor");

void VType_GLFWmonitor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_GLFWmonitor
//------------------------------------------------------------------------------
VType& Value_GLFWmonitor::vtype = VTYPE_GLFWmonitor;

String Value_GLFWmonitor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWmonitor");
}

Gurax_EndModuleScope(glfw)
