//==============================================================================
// VType_GLFWcursor.cpp
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
// VType_GLFWcursor
//------------------------------------------------------------------------------
VType_GLFWcursor VTYPE_GLFWcursor("GLFWcursor");

void VType_GLFWcursor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_GLFWcursor
//------------------------------------------------------------------------------
VType& Value_GLFWcursor::vtype = VTYPE_GLFWcursor;

String Value_GLFWcursor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWcursor");
}

Gurax_EndModuleScope(glfw)
