//==============================================================================
// VType_GLFWmonitor.cpp
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
// glfw.GLFWmonitor() {block?}
Gurax_DeclareConstructor(GLFWmonitor)
{
	Declare(VTYPE_GLFWmonitor, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `glfw.GLFWmonitor` instance.");
}

Gurax_ImplementConstructor(GLFWmonitor)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	GLFWmonitor* pGLFWmonitor = ::getmonitor(new GLFWmonitor());
	return argument.ReturnValue(processor, new Value_GLFWmonitor(pGLFWmonitor.release()));
}
#endif

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// glfw.GLFWmonitor#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GLFWmonitor, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(GLFWmonitor, MethodSkeleton)
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
// glfw.GLFWmonitor#propSkeleton
Gurax_DeclareProperty_R(GLFWmonitor, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(GLFWmonitor, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GLFWmonitor
//------------------------------------------------------------------------------
VType_GLFWmonitor VTYPE_GLFWmonitor("GLFWmonitor");

void VType_GLFWmonitor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(GLFWmonitor, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GLFWmonitor, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GLFWmonitor
//------------------------------------------------------------------------------
VType& Value_GLFWmonitor::vtype = VTYPE_GLFWmonitor;

String Value_GLFWmonitor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWmonitor");
}

Gurax_EndModuleScope(glfw)
