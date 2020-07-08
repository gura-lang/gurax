//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(opengl)

// opengl.glewInit()
Gurax_DeclareFunction(glewInit)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewInit)
{
	// Function body
	GLenum rtn = glewInit();
	return new Value_Number(rtn);
}

// opengl.glewIsSupported(name:String)
Gurax_DeclareFunction(glewIsSupported)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewIsSupported)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	GLboolean rtn = glewIsSupported(name);
	return new Value_Bool(!!rtn);
}

// opengl.glewGetExtension(name:String)
Gurax_DeclareFunction(glewGetExtension)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewGetExtension)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	GLboolean rtn = glewGetExtension(name);
	return new Value_Bool(!!rtn);
}

// opengl.glewGetErrorString(error:Number)
Gurax_DeclareFunction(glewGetErrorString)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("error", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewGetErrorString)
{
	// Arguments
	ArgPicker args(argument);
	GLenum error = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetErrorString(error);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glewGetString(name:Number)
Gurax_DeclareFunction(glewGetString)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewGetString)
{
	// Arguments
	ArgPicker args(argument);
	GLenum name = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetString(name);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glAccum(op:Number, value:Number)
Gurax_DeclareFunction(glAccum)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("op", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glAccum)
{
	// Arguments
	ArgPicker args(argument);
	GLenum op = args.PickNumber<GLenum>();
	GLfloat value = args.PickNumber<GLfloat>();
	// Function body
	glAccum(op, value);
	return Value::nil();
}

// opengl.glAlphaFunc(func:Number, ref:Number)
Gurax_DeclareFunction(glAlphaFunc)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glAlphaFunc)
{
	// Arguments
	ArgPicker args(argument);
	GLenum func = args.PickNumber<GLenum>();
	GLclampf ref = args.PickNumber<GLclampf>();
	// Function body
	glAlphaFunc(func, ref);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(glewInit));
	frame.Assign(Gurax_CreateFunction(glewIsSupported));
	frame.Assign(Gurax_CreateFunction(glewGetExtension));
	frame.Assign(Gurax_CreateFunction(glewGetErrorString));
	frame.Assign(Gurax_CreateFunction(glewGetString));
	frame.Assign(Gurax_CreateFunction(glAccum));
	frame.Assign(Gurax_CreateFunction(glAlphaFunc));
}

Gurax_EndModuleScope(opengl)
