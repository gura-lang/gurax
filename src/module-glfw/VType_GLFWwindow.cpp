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
void Value_GLFWwindow::callback_ErrorCallback(int error_code, const char* description)
{
}

void Value_GLFWwindow::callback_WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	Value_GLFWwindow& valueThis = GetValue(window);
	const Function* pFunc = valueThis.GetFunc_WindowPosCallback();
	if (!pFunc) return;
	RefPtr<Frame> pFrame(pFunc->LockFrameOuter());
	RefPtr<Argument> pArgument(new Argument(*pFunc, DeclCallable::Flag::CutExtraArgs));
	ArgFeeder args(*pArgument);
	args.FeedValue(*pFrame, new Value_Number(xpos));
	args.FeedValue(*pFrame, new Value_Number(ypos));
	if (Error::IsIssued()) return;
	Value::Delete(pFunc->Eval(valueThis.GetProcessor(), *pArgument));
}

void Value_GLFWwindow::callback_WindowSizeCallback(GLFWwindow* window, int width, int height)
{
}

void Value_GLFWwindow::callback_WindowCloseCallback(GLFWwindow* window)
{
}

void Value_GLFWwindow::callback_WindowRefreshCallback(GLFWwindow* window)
{
}

void Value_GLFWwindow::callback_WindowFocusCallback(GLFWwindow* window, int focused)
{
}

void Value_GLFWwindow::callback_WindowIconifyCallback(GLFWwindow* window, int iconified)
{
}

void Value_GLFWwindow::callback_WindowMaximizeCallback(GLFWwindow* window, int maximized)
{
}

void Value_GLFWwindow::callback_FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
}

void Value_GLFWwindow::callback_WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
}

void Value_GLFWwindow::callback_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void Value_GLFWwindow::callback_CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
}

void Value_GLFWwindow::callback_CursorEnterCallback(GLFWwindow* window, int entered)
{
}

void Value_GLFWwindow::callback_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void Value_GLFWwindow::callback_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Value_GLFWwindow::callback_CharCallback(GLFWwindow* window, unsigned int codepoint)
{
}

void Value_GLFWwindow::callback_CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
}

void Value_GLFWwindow::callback_DropCallback(GLFWwindow* window, int path_count, const char* paths[])
{
}

void Value_GLFWwindow::callback_MonitorCallback(GLFWmonitor* monitor, int event)
{
}

void Value_GLFWwindow::callback_JoystickCallback(int jid, int event)
{
}


Gurax_EndModuleScope(glfw)
