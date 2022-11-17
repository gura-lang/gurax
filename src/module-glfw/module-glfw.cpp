//==============================================================================
// module-glfw.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(glfw)

//------------------------------------------------------------------------------
// Callback function
//------------------------------------------------------------------------------
RefPtr<Processor> g_pProcessor_ErrorCallback;
RefPtr<Function> g_pFunc_ErrorCallback;

void callback_ErrorCallback(int error_code, const char* description)
{
	Function* pFunc = g_pFunc_ErrorCallback.get();
	if (!pFunc) return;
	RefPtr<Frame> pFrame(pFunc->LockFrameOuter());
	RefPtr<Argument> pArgument(new Argument(*g_pProcessor_ErrorCallback, *pFunc, DeclCallable::Flag::CutExtraArgs));
	ArgFeeder args(*pArgument, *pFrame);
	args.FeedValues(new Value_Number(error_code), new Value_String(description));
	if (Error::IsIssued()) return;
	Value::Delete(pFunc->Eval(*g_pProcessor_ErrorCallback, *pArgument));
}

RefPtr<Processor> g_pProcessor_MonitorCallback;
RefPtr<Function> g_pFunc_MonitorCallback;

void callback_MonitorCallback(GLFWmonitor* monitor, int event)
{
	Function* pFunc = g_pFunc_MonitorCallback.get();
	if (!pFunc) return;
	RefPtr<Frame> pFrame(pFunc->LockFrameOuter());
	RefPtr<Argument> pArgument(new Argument(*g_pProcessor_MonitorCallback, *pFunc, DeclCallable::Flag::CutExtraArgs));
	ArgFeeder args(*pArgument, *pFrame);
	args.FeedValues(Value_GLFWmonitor::GetValue(monitor).Reference(), new Value_Number(event));
	if (Error::IsIssued()) return;
	Value::Delete(pFunc->Eval(*g_pProcessor_MonitorCallback, *pArgument));
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
	Assign(VTYPE_GLFWcursor);
	Assign(VTYPE_GLFWgammaramp);
	Assign(VTYPE_GLFWimage);
	Assign(VTYPE_GLFWmonitor);
	Assign(VTYPE_GLFWvidmode);
	Assign(VTYPE_GLFWwindow);
	// Assignment of function
	AssignConsts(GetFrame());
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(glfw)
