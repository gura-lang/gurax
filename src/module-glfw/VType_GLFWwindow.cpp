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
	// Assignment of value
	AssignGLFWConst(frameOuter, GLFW_FOCUSED);
	AssignGLFWConst(frameOuter, GLFW_ICONIFIED);
	AssignGLFWConst(frameOuter, GLFW_RESIZABLE);
	AssignGLFWConst(frameOuter, GLFW_VISIBLE);
	AssignGLFWConst(frameOuter, GLFW_DECORATED);
	AssignGLFWConst(frameOuter, GLFW_AUTO_ICONIFY);
	AssignGLFWConst(frameOuter, GLFW_FLOATING);
	AssignGLFWConst(frameOuter, GLFW_MAXIMIZED);
	AssignGLFWConst(frameOuter, GLFW_CENTER_CURSOR);
	AssignGLFWConst(frameOuter, GLFW_TRANSPARENT_FRAMEBUFFER);
	AssignGLFWConst(frameOuter, GLFW_HOVERED);
	AssignGLFWConst(frameOuter, GLFW_FOCUS_ON_SHOW);
	AssignGLFWConst(frameOuter, GLFW_RED_BITS);
	AssignGLFWConst(frameOuter, GLFW_GREEN_BITS);
	AssignGLFWConst(frameOuter, GLFW_BLUE_BITS);
	AssignGLFWConst(frameOuter, GLFW_ALPHA_BITS);
	AssignGLFWConst(frameOuter, GLFW_DEPTH_BITS);
	AssignGLFWConst(frameOuter, GLFW_STENCIL_BITS);
	AssignGLFWConst(frameOuter, GLFW_ACCUM_RED_BITS);
	AssignGLFWConst(frameOuter, GLFW_ACCUM_GREEN_BITS);
	AssignGLFWConst(frameOuter, GLFW_ACCUM_BLUE_BITS);
	AssignGLFWConst(frameOuter, GLFW_ACCUM_ALPHA_BITS);
	AssignGLFWConst(frameOuter, GLFW_AUX_BUFFERS);
	AssignGLFWConst(frameOuter, GLFW_STEREO);
	AssignGLFWConst(frameOuter, GLFW_SAMPLES);
	AssignGLFWConst(frameOuter, GLFW_SRGB_CAPABLE);
	AssignGLFWConst(frameOuter, GLFW_REFRESH_RATE);
	AssignGLFWConst(frameOuter, GLFW_DOUBLEBUFFER);
	AssignGLFWConst(frameOuter, GLFW_CLIENT_API);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_VERSION_MAJOR);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_VERSION_MINOR);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_REVISION);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_ROBUSTNESS);
	AssignGLFWConst(frameOuter, GLFW_OPENGL_FORWARD_COMPAT);
	AssignGLFWConst(frameOuter, GLFW_OPENGL_DEBUG_CONTEXT);
	AssignGLFWConst(frameOuter, GLFW_OPENGL_PROFILE);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_RELEASE_BEHAVIOR);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_NO_ERROR);
	AssignGLFWConst(frameOuter, GLFW_CONTEXT_CREATION_API);
	AssignGLFWConst(frameOuter, GLFW_SCALE_TO_MONITOR);
	AssignGLFWConst(frameOuter, GLFW_COCOA_RETINA_FRAMEBUFFER);
	AssignGLFWConst(frameOuter, GLFW_COCOA_FRAME_NAME);
	AssignGLFWConst(frameOuter, GLFW_COCOA_GRAPHICS_SWITCHING);
	AssignGLFWConst(frameOuter, GLFW_X11_CLASS_NAME);
	AssignGLFWConst(frameOuter, GLFW_X11_INSTANCE_NAME);
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
