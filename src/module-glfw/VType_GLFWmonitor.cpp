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

${help.ComposePropertyHelp(GLFWmonitor)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(GLFWmonitor)}

${help.ComposeMethodHelp(GLFWmonitor)}
)**";

//------------------------------------------------------------------------------
// VType_GLFWmonitor
//------------------------------------------------------------------------------
VType_GLFWmonitor VTYPE_GLFWmonitor("GLFWmonitor");

void VType_GLFWmonitor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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
