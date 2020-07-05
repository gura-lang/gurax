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

//------------------------------------------------------------------------------
// Callback Function
//------------------------------------------------------------------------------
void Value_GLFWwindow::callback_errorfun(int error_code, const char* description)
{
}

void Value_GLFWwindow::callback_windowposfun(GLFWwindow* window, int xpos, int ypos)
{
	Value_GLFWwindow* pValueThis = GetValue(window);
	if (const Function* pFunc = pValueThis->GetFunc_windowposfun()) {
		RefPtr<Frame> pFrame(pFunc->LockFrameOuter());
		RefPtr<Argument> pArgument(new Argument(*pFunc));
		ArgFeeder args(*pArgument);
		args.FeedValue(*pFrame, new Value_Number(xpos));
		args.FeedValue(*pFrame, new Value_Number(ypos));
		if (Error::IsIssued()) return;
		Value::Delete(pFunc->Eval(pValueThis->GetProcessor(), *pArgument));
	}
}

void Value_GLFWwindow::callback_windowsizefun(GLFWwindow* window, int width, int height)
{
}

void Value_GLFWwindow::callback_windowclosefun(GLFWwindow* window)
{
}

void Value_GLFWwindow::callback_windowrefreshfun(GLFWwindow* window)
{
}

void Value_GLFWwindow::callback_windowfocusfun(GLFWwindow* window, int focused)
{
}

void Value_GLFWwindow::callback_windowiconifyfun(GLFWwindow* window, int iconified)
{
}

void Value_GLFWwindow::callback_windowmaximizefun(GLFWwindow* window, int maximized)
{
}

void Value_GLFWwindow::callback_framebuffersizefun(GLFWwindow* window, int width, int height)
{
}

void Value_GLFWwindow::callback_windowcontentscalefun(GLFWwindow* window, float xscale, float yscale)
{
}

void Value_GLFWwindow::callback_mousebuttonfun(GLFWwindow* window, int button, int action, int mods)
{
}

void Value_GLFWwindow::callback_cursorposfun(GLFWwindow* window, double xpos, double ypos)
{
}

void Value_GLFWwindow::callback_cursorenterfun(GLFWwindow* window, int entered)
{
}

void Value_GLFWwindow::callback_scrollfun(GLFWwindow* window, double xoffset, double yoffset)
{
}

void Value_GLFWwindow::callback_keyfun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Value_GLFWwindow::callback_charfun(GLFWwindow* window, unsigned int codepoint)
{
}

void Value_GLFWwindow::callback_charmodsfun(GLFWwindow* window, unsigned int codepoint, int mods)
{
}

void Value_GLFWwindow::callback_dropfun(GLFWwindow* window, int path_count, const char* paths[])
{
}

void Value_GLFWwindow::callback_monitorfun(GLFWmonitor* monitor, int event)
{
}

void Value_GLFWwindow::callback_joystickfun(int jid, int event)
{
}


Gurax_EndModuleScope(glfw)
