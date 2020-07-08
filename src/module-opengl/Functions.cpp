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

// opengl.glArrayElement(i:Number)
Gurax_DeclareFunction(glArrayElement)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glArrayElement)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	// Function body
	glArrayElement(i);
	return Value::nil();
}

// opengl.glBegin(mode:Number)
Gurax_DeclareFunction(glBegin)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBegin)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glBegin(mode);
	return Value::nil();
}

// opengl.glBindTexture(target:Number, texture:Number)
Gurax_DeclareFunction(glBindTexture)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBindTexture)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLuint texture = args.PickNumber<GLuint>();
	// Function body
	glBindTexture(target, texture);
	return Value::nil();
}

// opengl.glBlendFunc(sfactor:Number, dfactor:Number)
Gurax_DeclareFunction(glBlendFunc)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendFunc)
{
	// Arguments
	ArgPicker args(argument);
	GLenum sfactor = args.PickNumber<GLenum>();
	GLenum dfactor = args.PickNumber<GLenum>();
	// Function body
	glBlendFunc(sfactor, dfactor);
	return Value::nil();
}

// opengl.glCallList(list:Number)
Gurax_DeclareFunction(glCallList)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCallList)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	// Function body
	glCallList(list);
	return Value::nil();
}

// opengl.glClear(mask:Number)
Gurax_DeclareFunction(glClear)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClear)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glClear(mask);
	return Value::nil();
}

// opengl.glClearAccum(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glClearAccum)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearAccum)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat red = args.PickNumber<GLfloat>();
	GLfloat green = args.PickNumber<GLfloat>();
	GLfloat blue = args.PickNumber<GLfloat>();
	GLfloat alpha = args.PickNumber<GLfloat>();
	// Function body
	glClearAccum(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glClearColor(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glClearColor)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearColor)
{
	// Arguments
	ArgPicker args(argument);
	GLclampf red = args.PickNumber<GLclampf>();
	GLclampf green = args.PickNumber<GLclampf>();
	GLclampf blue = args.PickNumber<GLclampf>();
	GLclampf alpha = args.PickNumber<GLclampf>();
	// Function body
	glClearColor(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glClearDepth(depth:Number)
Gurax_DeclareFunction(glClearDepth)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearDepth)
{
	// Arguments
	ArgPicker args(argument);
	GLclampd depth = args.PickNumber<GLclampd>();
	// Function body
	glClearDepth(depth);
	return Value::nil();
}

// opengl.glClearIndex(c:Number)
Gurax_DeclareFunction(glClearIndex)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearIndex)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat c = args.PickNumber<GLfloat>();
	// Function body
	glClearIndex(c);
	return Value::nil();
}

// opengl.glClearStencil(s:Number)
Gurax_DeclareFunction(glClearStencil)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearStencil)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	// Function body
	glClearStencil(s);
	return Value::nil();
}

// opengl.glColor3b(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3b)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3b)
{
	// Arguments
	ArgPicker args(argument);
	GLbyte red = args.PickNumber<GLbyte>();
	GLbyte green = args.PickNumber<GLbyte>();
	GLbyte blue = args.PickNumber<GLbyte>();
	// Function body
	glColor3b(red, green, blue);
	return Value::nil();
}

// opengl.glColor3bv(v[]:Number)
Gurax_DeclareFunction(glColor3bv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3bv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glColor3bv(v);
	return Value::nil();
}

// opengl.glColor3d(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble red = args.PickNumber<GLdouble>();
	GLdouble green = args.PickNumber<GLdouble>();
	GLdouble blue = args.PickNumber<GLdouble>();
	// Function body
	glColor3d(red, green, blue);
	return Value::nil();
}

// opengl.glColor3dv(v[]:Number)
Gurax_DeclareFunction(glColor3dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glColor3dv(v);
	return Value::nil();
}

// opengl.glColor3f(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat red = args.PickNumber<GLfloat>();
	GLfloat green = args.PickNumber<GLfloat>();
	GLfloat blue = args.PickNumber<GLfloat>();
	// Function body
	glColor3f(red, green, blue);
	return Value::nil();
}

// opengl.glColor3fv(v[]:Number)
Gurax_DeclareFunction(glColor3fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glColor3fv(v);
	return Value::nil();
}

// opengl.glColor3i(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3i)
{
	// Arguments
	ArgPicker args(argument);
	GLint red = args.PickNumber<GLint>();
	GLint green = args.PickNumber<GLint>();
	GLint blue = args.PickNumber<GLint>();
	// Function body
	glColor3i(red, green, blue);
	return Value::nil();
}

// opengl.glColor3iv(v[]:Number)
Gurax_DeclareFunction(glColor3iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glColor3iv(v);
	return Value::nil();
}

// opengl.glColor3s(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort red = args.PickNumber<GLshort>();
	GLshort green = args.PickNumber<GLshort>();
	GLshort blue = args.PickNumber<GLshort>();
	// Function body
	glColor3s(red, green, blue);
	return Value::nil();
}

// opengl.glColor3sv(v[]:Number)
Gurax_DeclareFunction(glColor3sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glColor3sv(v);
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
	frame.Assign(Gurax_CreateFunction(glArrayElement));
	frame.Assign(Gurax_CreateFunction(glBegin));
	frame.Assign(Gurax_CreateFunction(glBindTexture));
	frame.Assign(Gurax_CreateFunction(glBlendFunc));
	frame.Assign(Gurax_CreateFunction(glCallList));
	frame.Assign(Gurax_CreateFunction(glClear));
	frame.Assign(Gurax_CreateFunction(glClearAccum));
	frame.Assign(Gurax_CreateFunction(glClearColor));
	frame.Assign(Gurax_CreateFunction(glClearDepth));
	frame.Assign(Gurax_CreateFunction(glClearIndex));
	frame.Assign(Gurax_CreateFunction(glClearStencil));
	frame.Assign(Gurax_CreateFunction(glColor3b));
	frame.Assign(Gurax_CreateFunction(glColor3bv));
	frame.Assign(Gurax_CreateFunction(glColor3d));
	frame.Assign(Gurax_CreateFunction(glColor3dv));
	frame.Assign(Gurax_CreateFunction(glColor3f));
	frame.Assign(Gurax_CreateFunction(glColor3fv));
	frame.Assign(Gurax_CreateFunction(glColor3i));
	frame.Assign(Gurax_CreateFunction(glColor3iv));
	frame.Assign(Gurax_CreateFunction(glColor3s));
	frame.Assign(Gurax_CreateFunction(glColor3sv));
}

Gurax_EndModuleScope(opengl)
