//==============================================================================
// VType_GLFWwindow.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glfw.GLFWwindow, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glfw.GLFWwindow, `en)}

${help.ComposeMethodHelp(glfw.GLFWwindow, `en)}
)""";

//------------------------------------------------------------------------------
// VType_GLFWwindow
//------------------------------------------------------------------------------
VType_GLFWwindow VTYPE_GLFWwindow("GLFWwindow");

void VType_GLFWwindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
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
// Callback function
//------------------------------------------------------------------------------
template<typename... T_Args> void callback_Window(Processor& processor, const Function* pFunc, T_Args... pValues)
{
	if (!pFunc) return;
	RefPtr<Frame> pFrame(pFunc->LockFrameOuter());
	RefPtr<Argument> pArgument(new Argument(processor, *pFunc, DeclCallable::Flag::CutExtraArgs));
	ArgFeeder args(*pArgument, *pFrame);
	args.FeedValues(processor, pValues...);
	if (Error::IsIssued()) return;
	Value::Delete(pFunc->Eval(processor, *pArgument));
}

void Value_GLFWwindow::callback_WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowPosCallback(),
		valueThis.Reference(), new Value_Number(xpos), new Value_Number(ypos));
}

void Value_GLFWwindow::callback_WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowSizeCallback(),
		valueThis.Reference(), new Value_Number(width), new Value_Number(height));
}

void Value_GLFWwindow::callback_WindowCloseCallback(GLFWwindow* window)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowCloseCallback(),
		valueThis.Reference());
}

void Value_GLFWwindow::callback_WindowRefreshCallback(GLFWwindow* window)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowRefreshCallback(),
		valueThis.Reference());
}

void Value_GLFWwindow::callback_WindowFocusCallback(GLFWwindow* window, int focused)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowFocusCallback(),
		valueThis.Reference(), new Value_Number(focused));
}

void Value_GLFWwindow::callback_WindowIconifyCallback(GLFWwindow* window, int iconified)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowIconifyCallback(),
		valueThis.Reference(), new Value_Bool(iconified != 0));
}

void Value_GLFWwindow::callback_WindowMaximizeCallback(GLFWwindow* window, int maximized)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowMaximizeCallback(),
		valueThis.Reference(), new Value_Bool(maximized != 0));
}

void Value_GLFWwindow::callback_FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_FramebufferSizeCallback(),
		valueThis.Reference(), new Value_Number(width), new Value_Number(height));
}

void Value_GLFWwindow::callback_WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_WindowContentScaleCallback(),
		valueThis.Reference(), new Value_Number(xscale), new Value_Number(yscale));
}

void Value_GLFWwindow::callback_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_MouseButtonCallback(),
		valueThis.Reference(), new Value_Number(button), new Value_Number(action), new Value_Number(mods));
}

void Value_GLFWwindow::callback_CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_CursorPosCallback(),
		valueThis.Reference(), new Value_Number(xpos), new Value_Number(ypos));
}

void Value_GLFWwindow::callback_CursorEnterCallback(GLFWwindow* window, int entered)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_CursorEnterCallback(),
		valueThis.Reference(), new Value_Bool(entered != 0));
}

void Value_GLFWwindow::callback_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_ScrollCallback(),
		valueThis.Reference(), new Value_Number(xoffset), new Value_Number(yoffset));
}

void Value_GLFWwindow::callback_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_KeyCallback(),
		valueThis.Reference(), new Value_Number(key), new Value_Number(scancode), new Value_Number(action), new Value_Number(mods));
}

void Value_GLFWwindow::callback_CharCallback(GLFWwindow* window, unsigned int codepoint)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_CharCallback(),
		valueThis.Reference(), new Value_Number(codepoint));
}

void Value_GLFWwindow::callback_CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_CharModsCallback(),
		valueThis.Reference(), new Value_Number(codepoint), new Value_Number(mods));
}

void Value_GLFWwindow::callback_DropCallback(GLFWwindow* window, int path_count, const char* paths[])
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(path_count);
	for (int i = 0; i < path_count; i++) {
		pValueOwner->push_back(new Value_String(paths[i]));
	}
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	callback_Window(valueThis.GetProcessor(), valueThis.GetFunc_DropCallback(),
		valueThis.Reference(), new Value_List(pValueOwner.release()));
}

void Value_GLFWwindow::callback_JoystickCallback(int jid, int event)
{
}


Gurax_EndModuleScope(glfw)
