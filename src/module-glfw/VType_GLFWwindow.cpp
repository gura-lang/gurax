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
// Implementation of constructor
//------------------------------------------------------------------------------
#if 0
// glfw.GLFWwindow() {block?}
Gurax_DeclareConstructor(GLFWwindow)
{
	Declare(VTYPE_GLFWwindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `glfw.GLFWwindow` instance.");
}

Gurax_ImplementConstructor(GLFWwindow)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<GLFWwindow> pGLFWwindow(new GLFWwindow());
	return argument.ReturnValue(processor, new Value_GLFWwindow(pGLFWwindow.release()));
}
#endif

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
#if 0
// glfw.glfwCreateWindow(width:Number, height:Number, title:String,
//                       monitor?:glfw.GLFWmonitor, share?:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwCreateWindow)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("share", VTYPE_GLFWwindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateWindow)
{
	// Arguments
	ArgPicker args(argument);
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	const char* title = args.PickString();
	GLFWmonitor* monitor = args.IsValid()? args.Pick<Value_GLFWmonitor>().GetEntity() : nullptr;
	GLFWwindow* share = args.IsValid()? args.Pick<Value_GLFWwindow>().GetEntity() : nullptr;
	// Function body
	GLFWwindow* rtn = ::glfwCreateWindow(width, height, title, monitor, share);
	if (!rtn) {
		IssueError();
		return Value::nil();
	}
	return new Value_GLFWwindow(rtn);
}
#endif

// glfw.glfwMakeContextCurrent(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwMakeContextCurrent)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwMakeContextCurrent)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	::glfwMakeContextCurrent(window);
	return Value::nil();
}

// glfw.glfwSwapBuffers(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwSwapBuffers)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSwapBuffers)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	::glfwSwapBuffers(window);
	return Value::nil();
}

#if 0
// glfw.glfwWindowShouldClose(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwWindowShouldClose)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowShouldClose)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	return new Value_Bool(::glfwWindowShouldClose(window) == GLFW_TRUE);
}
#endif

// glfw.glfwPollEvents()
Gurax_DeclareFunction(glfwPollEvents)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwPollEvents)
{
	// Function body
	::glfwPollEvents();
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// glfw.GLFWwindow#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GLFWwindow, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(GLFWwindow, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// glfw.GLFWwindow#propSkeleton
Gurax_DeclareProperty_R(GLFWwindow, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(GLFWwindow, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

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
	// Assignment of function
	//frameOuter.Assign(Gurax_CreateFunction(glfwCreateWindow));
	frameOuter.Assign(Gurax_CreateFunction(glfwMakeContextCurrent));
	frameOuter.Assign(Gurax_CreateFunction(glfwSwapBuffers));
	//frameOuter.Assign(Gurax_CreateFunction(glfwWindowShouldClose));
	frameOuter.Assign(Gurax_CreateFunction(glfwPollEvents));
	// Assignment of method
	Assign(Gurax_CreateMethod(GLFWwindow, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GLFWwindow, propSkeleton));
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
