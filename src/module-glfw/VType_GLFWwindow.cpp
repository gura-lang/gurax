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
