//==============================================================================
// VType_GLFWcursor.cpp
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
// glfw.GLFWcursor() {block?}
Gurax_DeclareConstructor(GLFWcursor)
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `glfw.GLFWcursor` instance.");
}

Gurax_ImplementConstructor(GLFWcursor)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	GLFWcursor* pGLFWcursor = ::getcursor(new GLFWcursor());
	return argument.ReturnValue(processor, new Value_GLFWcursor(pGLFWcursor.release()));
}
#endif

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// glfw.GLFWcursor#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GLFWcursor, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(GLFWcursor, MethodSkeleton)
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
// glfw.GLFWcursor#propSkeleton
Gurax_DeclareProperty_R(GLFWcursor, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(GLFWcursor, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GLFWcursor
//------------------------------------------------------------------------------
VType_GLFWcursor VTYPE_GLFWcursor("GLFWcursor");

void VType_GLFWcursor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(GLFWcursor, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GLFWcursor, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GLFWcursor
//------------------------------------------------------------------------------
VType& Value_GLFWcursor::vtype = VTYPE_GLFWcursor;

String Value_GLFWcursor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWcursor");
}

Gurax_EndModuleScope(glfw)
