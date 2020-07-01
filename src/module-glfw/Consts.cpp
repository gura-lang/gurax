//==============================================================================
// Consts.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

void AssignConsts(Frame& frame)
{
	// Assignment of value
	AssignGLFWConst(frame, GLFW_FOCUSED);
	AssignGLFWConst(frame, GLFW_ICONIFIED);
	AssignGLFWConst(frame, GLFW_RESIZABLE);
	AssignGLFWConst(frame, GLFW_VISIBLE);
	AssignGLFWConst(frame, GLFW_DECORATED);
	AssignGLFWConst(frame, GLFW_AUTO_ICONIFY);
	AssignGLFWConst(frame, GLFW_FLOATING);
	AssignGLFWConst(frame, GLFW_MAXIMIZED);
	AssignGLFWConst(frame, GLFW_CENTER_CURSOR);
	AssignGLFWConst(frame, GLFW_TRANSPARENT_FRAMEBUFFER);
	AssignGLFWConst(frame, GLFW_HOVERED);
	AssignGLFWConst(frame, GLFW_FOCUS_ON_SHOW);
	AssignGLFWConst(frame, GLFW_RED_BITS);
	AssignGLFWConst(frame, GLFW_GREEN_BITS);
	AssignGLFWConst(frame, GLFW_BLUE_BITS);
	AssignGLFWConst(frame, GLFW_ALPHA_BITS);
	AssignGLFWConst(frame, GLFW_DEPTH_BITS);
	AssignGLFWConst(frame, GLFW_STENCIL_BITS);
	AssignGLFWConst(frame, GLFW_ACCUM_RED_BITS);
	AssignGLFWConst(frame, GLFW_ACCUM_GREEN_BITS);
	AssignGLFWConst(frame, GLFW_ACCUM_BLUE_BITS);
	AssignGLFWConst(frame, GLFW_ACCUM_ALPHA_BITS);
	AssignGLFWConst(frame, GLFW_AUX_BUFFERS);
	AssignGLFWConst(frame, GLFW_STEREO);
	AssignGLFWConst(frame, GLFW_SAMPLES);
	AssignGLFWConst(frame, GLFW_SRGB_CAPABLE);
	AssignGLFWConst(frame, GLFW_REFRESH_RATE);
	AssignGLFWConst(frame, GLFW_DOUBLEBUFFER);
	AssignGLFWConst(frame, GLFW_CLIENT_API);
	AssignGLFWConst(frame, GLFW_CONTEXT_VERSION_MAJOR);
	AssignGLFWConst(frame, GLFW_CONTEXT_VERSION_MINOR);
	AssignGLFWConst(frame, GLFW_CONTEXT_REVISION);
	AssignGLFWConst(frame, GLFW_CONTEXT_ROBUSTNESS);
	AssignGLFWConst(frame, GLFW_OPENGL_FORWARD_COMPAT);
	AssignGLFWConst(frame, GLFW_OPENGL_DEBUG_CONTEXT);
	AssignGLFWConst(frame, GLFW_OPENGL_PROFILE);
	AssignGLFWConst(frame, GLFW_CONTEXT_RELEASE_BEHAVIOR);
	AssignGLFWConst(frame, GLFW_CONTEXT_NO_ERROR);
	AssignGLFWConst(frame, GLFW_CONTEXT_CREATION_API);
	AssignGLFWConst(frame, GLFW_SCALE_TO_MONITOR);
	AssignGLFWConst(frame, GLFW_COCOA_RETINA_FRAMEBUFFER);
	AssignGLFWConst(frame, GLFW_COCOA_FRAME_NAME);
	AssignGLFWConst(frame, GLFW_COCOA_GRAPHICS_SWITCHING);
	AssignGLFWConst(frame, GLFW_X11_CLASS_NAME);
	AssignGLFWConst(frame, GLFW_X11_INSTANCE_NAME);
}

Gurax_EndModuleScope(glfw)
