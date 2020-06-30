//==============================================================================
// VType_GLFWimage.cpp
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
// glfw.GLFWimage() {block?}
Gurax_DeclareConstructor(GLFWimage)
{
	Declare(VTYPE_GLFWimage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `glfw.GLFWimage` instance.");
}

Gurax_ImplementConstructor(GLFWimage)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	GLFWimage* pGLFWimage = ::getimage(new GLFWimage());
	return argument.ReturnValue(processor, new Value_GLFWimage(pGLFWimage.release()));
}
#endif

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// glfw.GLFWimage#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GLFWimage, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(GLFWimage, MethodSkeleton)
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
// glfw.GLFWimage#propSkeleton
Gurax_DeclareProperty_R(GLFWimage, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(GLFWimage, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GLFWimage
//------------------------------------------------------------------------------
VType_GLFWimage VTYPE_GLFWimage("GLFWimage");

void VType_GLFWimage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(GLFWimage, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GLFWimage, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GLFWimage
//------------------------------------------------------------------------------
VType& Value_GLFWimage::vtype = VTYPE_GLFWimage;

String Value_GLFWimage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "GLFWimage");
}

Gurax_EndModuleScope(glfw)
