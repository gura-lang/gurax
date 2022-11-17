//==============================================================================
// module-glfw.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_H
#define GURAX_MODULE_GLFW_H
#include <gurax.h>
#include <GLFW/glfw3.h>
#include "Util.h"
#include "Consts.h"
#include "Functions.h"
#include "VType_GLFWcursor.h"
#include "VType_GLFWgammaramp.h"
#include "VType_GLFWimage.h"
#include "VType_GLFWmonitor.h"
#include "VType_GLFWvidmode.h"
#include "VType_GLFWwindow.h"

Gurax_BeginModuleHeader(glfw)

extern RefPtr<Processor> g_pProcessor_ErrorCallback;
extern RefPtr<Function> g_pFunc_ErrorCallback;
void callback_ErrorCallback(int error_code, const char* description);

extern RefPtr<Processor> g_pProcessor_MonitorCallback;
extern RefPtr<Function> g_pFunc_MonitorCallback;
void callback_MonitorCallback(GLFWmonitor* monitor, int event);

Gurax_EndModuleHeader(glfw)

#endif
