//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glu)

// glu.gluErrorString(errCode as Number)
Gurax_DeclareFunctionAlias(gluErrorString_gurax, "gluErrorString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("errCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluErrorString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum errCode = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = gluErrorString(errCode);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
}

// glu.gluGetString(name as Number)
Gurax_DeclareFunctionAlias(gluGetString_gurax, "gluGetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluGetString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum name = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = gluGetString(name);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
}

// glu.gluOrtho2D(left as Number, right as Number, bottom as Number, top as Number)
Gurax_DeclareFunctionAlias(gluOrtho2D_gurax, "gluOrtho2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bottom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("top", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluOrtho2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble left = args_gurax.PickNumber<GLdouble>();
	GLdouble right = args_gurax.PickNumber<GLdouble>();
	GLdouble bottom = args_gurax.PickNumber<GLdouble>();
	GLdouble top = args_gurax.PickNumber<GLdouble>();
	// Function body
	gluOrtho2D(left, right, bottom, top);
	return Gurax::Value::nil();
}

// glu.gluPerspective(fovy as Number, aspect as Number, zNear as Number, zFar as Number)
Gurax_DeclareFunctionAlias(gluPerspective_gurax, "gluPerspective")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fovy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("aspect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zNear", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zFar", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluPerspective_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble fovy = args_gurax.PickNumber<GLdouble>();
	GLdouble aspect = args_gurax.PickNumber<GLdouble>();
	GLdouble zNear = args_gurax.PickNumber<GLdouble>();
	GLdouble zFar = args_gurax.PickNumber<GLdouble>();
	// Function body
	gluPerspective(fovy, aspect, zNear, zFar);
	return Gurax::Value::nil();
}

// glu.gluLookAt(eyex as Number, eyey as Number, eyez as Number, centerx as Number, centery as Number, centerz as Number, upx as Number, upy as Number, upz as Number)
Gurax_DeclareFunctionAlias(gluLookAt_gurax, "gluLookAt")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("eyex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("eyey", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("eyez", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("centerx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("centery", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("centerz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("upx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("upy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("upz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluLookAt_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble eyex = args_gurax.PickNumber<GLdouble>();
	GLdouble eyey = args_gurax.PickNumber<GLdouble>();
	GLdouble eyez = args_gurax.PickNumber<GLdouble>();
	GLdouble centerx = args_gurax.PickNumber<GLdouble>();
	GLdouble centery = args_gurax.PickNumber<GLdouble>();
	GLdouble centerz = args_gurax.PickNumber<GLdouble>();
	GLdouble upx = args_gurax.PickNumber<GLdouble>();
	GLdouble upy = args_gurax.PickNumber<GLdouble>();
	GLdouble upz = args_gurax.PickNumber<GLdouble>();
	// Function body
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	return Gurax::Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(gluErrorString_gurax));
	frame.Assign(Gurax_CreateFunction(gluGetString_gurax));
	frame.Assign(Gurax_CreateFunction(gluOrtho2D_gurax));
	frame.Assign(Gurax_CreateFunction(gluPerspective_gurax));
	frame.Assign(Gurax_CreateFunction(gluLookAt_gurax));
}

Gurax_EndModuleScope(glu)
