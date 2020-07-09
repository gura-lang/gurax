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

// opengl.glColor3ub(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3ub)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3ub)
{
	// Arguments
	ArgPicker args(argument);
	GLubyte red = args.PickNumber<GLubyte>();
	GLubyte green = args.PickNumber<GLubyte>();
	GLubyte blue = args.PickNumber<GLubyte>();
	// Function body
	glColor3ub(red, green, blue);
	return Value::nil();
}

// opengl.glColor3ubv(v[]:Number)
Gurax_DeclareFunction(glColor3ubv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3ubv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glColor3ubv(v);
	return Value::nil();
}

// opengl.glColor3ui(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3ui)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3ui)
{
	// Arguments
	ArgPicker args(argument);
	GLuint red = args.PickNumber<GLuint>();
	GLuint green = args.PickNumber<GLuint>();
	GLuint blue = args.PickNumber<GLuint>();
	// Function body
	glColor3ui(red, green, blue);
	return Value::nil();
}

// opengl.glColor3uiv(v[]:Number)
Gurax_DeclareFunction(glColor3uiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3uiv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glColor3uiv(v);
	return Value::nil();
}

// opengl.glColor3us(red:Number, green:Number, blue:Number)
Gurax_DeclareFunction(glColor3us)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3us)
{
	// Arguments
	ArgPicker args(argument);
	GLushort red = args.PickNumber<GLushort>();
	GLushort green = args.PickNumber<GLushort>();
	GLushort blue = args.PickNumber<GLushort>();
	// Function body
	glColor3us(red, green, blue);
	return Value::nil();
}

// opengl.glColor3usv(v[]:Number)
Gurax_DeclareFunction(glColor3usv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3usv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glColor3usv(v);
	return Value::nil();
}

// opengl.glColor4b(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4b)
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

Gurax_ImplementFunction(glColor4b)
{
	// Arguments
	ArgPicker args(argument);
	GLbyte red = args.PickNumber<GLbyte>();
	GLbyte green = args.PickNumber<GLbyte>();
	GLbyte blue = args.PickNumber<GLbyte>();
	GLbyte alpha = args.PickNumber<GLbyte>();
	// Function body
	glColor4b(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4bv(v[]:Number)
Gurax_DeclareFunction(glColor4bv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4bv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glColor4bv(v);
	return Value::nil();
}

// opengl.glColor4d(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4d)
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

Gurax_ImplementFunction(glColor4d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble red = args.PickNumber<GLdouble>();
	GLdouble green = args.PickNumber<GLdouble>();
	GLdouble blue = args.PickNumber<GLdouble>();
	GLdouble alpha = args.PickNumber<GLdouble>();
	// Function body
	glColor4d(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4dv(v[]:Number)
Gurax_DeclareFunction(glColor4dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glColor4dv(v);
	return Value::nil();
}

// opengl.glColor4f(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4f)
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

Gurax_ImplementFunction(glColor4f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat red = args.PickNumber<GLfloat>();
	GLfloat green = args.PickNumber<GLfloat>();
	GLfloat blue = args.PickNumber<GLfloat>();
	GLfloat alpha = args.PickNumber<GLfloat>();
	// Function body
	glColor4f(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4fv(v[]:Number)
Gurax_DeclareFunction(glColor4fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glColor4fv(v);
	return Value::nil();
}

// opengl.glColor4i(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4i)
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

Gurax_ImplementFunction(glColor4i)
{
	// Arguments
	ArgPicker args(argument);
	GLint red = args.PickNumber<GLint>();
	GLint green = args.PickNumber<GLint>();
	GLint blue = args.PickNumber<GLint>();
	GLint alpha = args.PickNumber<GLint>();
	// Function body
	glColor4i(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4iv(v[]:Number)
Gurax_DeclareFunction(glColor4iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glColor4iv(v);
	return Value::nil();
}

// opengl.glColor4s(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4s)
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

Gurax_ImplementFunction(glColor4s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort red = args.PickNumber<GLshort>();
	GLshort green = args.PickNumber<GLshort>();
	GLshort blue = args.PickNumber<GLshort>();
	GLshort alpha = args.PickNumber<GLshort>();
	// Function body
	glColor4s(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4sv(v[]:Number)
Gurax_DeclareFunction(glColor4sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glColor4sv(v);
	return Value::nil();
}

// opengl.glColor4ub(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4ub)
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

Gurax_ImplementFunction(glColor4ub)
{
	// Arguments
	ArgPicker args(argument);
	GLubyte red = args.PickNumber<GLubyte>();
	GLubyte green = args.PickNumber<GLubyte>();
	GLubyte blue = args.PickNumber<GLubyte>();
	GLubyte alpha = args.PickNumber<GLubyte>();
	// Function body
	glColor4ub(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4ubv(v[]:Number)
Gurax_DeclareFunction(glColor4ubv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4ubv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glColor4ubv(v);
	return Value::nil();
}

// opengl.glColor4ui(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4ui)
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

Gurax_ImplementFunction(glColor4ui)
{
	// Arguments
	ArgPicker args(argument);
	GLuint red = args.PickNumber<GLuint>();
	GLuint green = args.PickNumber<GLuint>();
	GLuint blue = args.PickNumber<GLuint>();
	GLuint alpha = args.PickNumber<GLuint>();
	// Function body
	glColor4ui(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4uiv(v[]:Number)
Gurax_DeclareFunction(glColor4uiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4uiv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glColor4uiv(v);
	return Value::nil();
}

// opengl.glColor4us(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunction(glColor4us)
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

Gurax_ImplementFunction(glColor4us)
{
	// Arguments
	ArgPicker args(argument);
	GLushort red = args.PickNumber<GLushort>();
	GLushort green = args.PickNumber<GLushort>();
	GLushort blue = args.PickNumber<GLushort>();
	GLushort alpha = args.PickNumber<GLushort>();
	// Function body
	glColor4us(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColor4usv(v[]:Number)
Gurax_DeclareFunction(glColor4usv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4usv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glColor4usv(v);
	return Value::nil();
}

// opengl.glColorMask(red:Bool, green:Bool, blue:Bool, alpha:Bool)
Gurax_DeclareFunction(glColorMask)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColorMask)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean red = static_cast<GLboolean>(args.PickBool());
	GLboolean green = static_cast<GLboolean>(args.PickBool());
	GLboolean blue = static_cast<GLboolean>(args.PickBool());
	GLboolean alpha = static_cast<GLboolean>(args.PickBool());
	// Function body
	glColorMask(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glColorMaterial(face:Number, mode:Number)
Gurax_DeclareFunction(glColorMaterial)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColorMaterial)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glColorMaterial(face, mode);
	return Value::nil();
}

// opengl.glCopyPixels(x:Number, y:Number, width:Number, height:Number, type:Number)
Gurax_DeclareFunction(glCopyPixels)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCopyPixels)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLenum type = args.PickNumber<GLenum>();
	// Function body
	glCopyPixels(x, y, width, height, type);
	return Value::nil();
}

// opengl.glCopyTexImage1D(target:Number, level:Number, internalFormat:Number, x:Number, y:Number, width:Number, border:Number)
Gurax_DeclareFunction(glCopyTexImage1D)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalFormat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCopyTexImage1D)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLenum internalFormat = args.PickNumber<GLenum>();
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLint border = args.PickNumber<GLint>();
	// Function body
	glCopyTexImage1D(target, level, internalFormat, x, y, width, border);
	return Value::nil();
}

// opengl.glCopyTexImage2D(target:Number, level:Number, internalFormat:Number, x:Number, y:Number, width:Number, height:Number, border:Number)
Gurax_DeclareFunction(glCopyTexImage2D)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalFormat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCopyTexImage2D)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLenum internalFormat = args.PickNumber<GLenum>();
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLint border = args.PickNumber<GLint>();
	// Function body
	glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border);
	return Value::nil();
}

// opengl.glCopyTexSubImage1D(target:Number, level:Number, xoffset:Number, x:Number, y:Number, width:Number)
Gurax_DeclareFunction(glCopyTexSubImage1D)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCopyTexSubImage1D)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	// Function body
	glCopyTexSubImage1D(target, level, xoffset, x, y, width);
	return Value::nil();
}

// opengl.glCopyTexSubImage2D(target:Number, level:Number, xoffset:Number, yoffset:Number, x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunction(glCopyTexSubImage2D)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCopyTexSubImage2D)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLint yoffset = args.PickNumber<GLint>();
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	// Function body
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	return Value::nil();
}

// opengl.glCullFace(mode:Number)
Gurax_DeclareFunction(glCullFace)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCullFace)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glCullFace(mode);
	return Value::nil();
}

// opengl.glDeleteLists(list:Number, range:Number)
Gurax_DeclareFunction(glDeleteLists)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteLists)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	GLsizei range = args.PickNumber<GLsizei>();
	// Function body
	glDeleteLists(list, range);
	return Value::nil();
}

// opengl.glDepthFunc(func:Number)
Gurax_DeclareFunction(glDepthFunc)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDepthFunc)
{
	// Arguments
	ArgPicker args(argument);
	GLenum func = args.PickNumber<GLenum>();
	// Function body
	glDepthFunc(func);
	return Value::nil();
}

// opengl.glDepthMask(flag:Bool)
Gurax_DeclareFunction(glDepthMask)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDepthMask)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean flag = static_cast<GLboolean>(args.PickBool());
	// Function body
	glDepthMask(flag);
	return Value::nil();
}

// opengl.glDepthRange(zNear:Number, zFar:Number)
Gurax_DeclareFunction(glDepthRange)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("zNear", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zFar", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDepthRange)
{
	// Arguments
	ArgPicker args(argument);
	GLclampd zNear = args.PickNumber<GLclampd>();
	GLclampd zFar = args.PickNumber<GLclampd>();
	// Function body
	glDepthRange(zNear, zFar);
	return Value::nil();
}

// opengl.glDisable(cap:Number)
Gurax_DeclareFunction(glDisable)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDisable)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	glDisable(cap);
	return Value::nil();
}

// opengl.glDisableClientState(array:Number)
Gurax_DeclareFunction(glDisableClientState)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDisableClientState)
{
	// Arguments
	ArgPicker args(argument);
	GLenum array = args.PickNumber<GLenum>();
	// Function body
	glDisableClientState(array);
	return Value::nil();
}

// opengl.glDrawArrays(mode:Number, first:Number, count:Number)
Gurax_DeclareFunction(glDrawArrays)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawArrays)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLint first = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	// Function body
	glDrawArrays(mode, first, count);
	return Value::nil();
}

// opengl.glDrawBuffer(mode:Number)
Gurax_DeclareFunction(glDrawBuffer)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawBuffer)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glDrawBuffer(mode);
	return Value::nil();
}

// opengl.glEdgeFlag(flag:Bool)
Gurax_DeclareFunction(glEdgeFlag)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEdgeFlag)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean flag = static_cast<GLboolean>(args.PickBool());
	// Function body
	glEdgeFlag(flag);
	return Value::nil();
}

// opengl.glEdgeFlagv(flag[]:Bool)
Gurax_DeclareFunction(glEdgeFlagv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEdgeFlagv)
{
	// Arguments
	ArgPicker args(argument);
	auto flag = args.PickListT<GLboolean>([](Value& value) { return value.GetBool()? GL_TRUE : GL_FALSE; });
	// Function body
	glEdgeFlagv(flag);
	return Value::nil();
}

// opengl.glEnable(cap:Number)
Gurax_DeclareFunction(glEnable)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnable)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	glEnable(cap);
	return Value::nil();
}

// opengl.glEnableClientState(array:Number)
Gurax_DeclareFunction(glEnableClientState)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnableClientState)
{
	// Arguments
	ArgPicker args(argument);
	GLenum array = args.PickNumber<GLenum>();
	// Function body
	glEnableClientState(array);
	return Value::nil();
}

// opengl.glEnd()
Gurax_DeclareFunction(glEnd)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnd)
{
	// Function body
	glEnd();
	return Value::nil();
}

// opengl.glEndList()
Gurax_DeclareFunction(glEndList)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEndList)
{
	// Function body
	glEndList();
	return Value::nil();
}

// opengl.glEvalCoord1d(u:Number)
Gurax_DeclareFunction(glEvalCoord1d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble u = args.PickNumber<GLdouble>();
	// Function body
	glEvalCoord1d(u);
	return Value::nil();
}

// opengl.glEvalCoord1dv(u[]:Number)
Gurax_DeclareFunction(glEvalCoord1dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1dv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLdouble>();
	// Function body
	glEvalCoord1dv(u);
	return Value::nil();
}

// opengl.glEvalCoord1f(u:Number)
Gurax_DeclareFunction(glEvalCoord1f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat u = args.PickNumber<GLfloat>();
	// Function body
	glEvalCoord1f(u);
	return Value::nil();
}

// opengl.glEvalCoord1fv(u[]:Number)
Gurax_DeclareFunction(glEvalCoord1fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1fv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLfloat>();
	// Function body
	glEvalCoord1fv(u);
	return Value::nil();
}

// opengl.glEvalCoord2d(u:Number, v:Number)
Gurax_DeclareFunction(glEvalCoord2d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble u = args.PickNumber<GLdouble>();
	GLdouble v = args.PickNumber<GLdouble>();
	// Function body
	glEvalCoord2d(u, v);
	return Value::nil();
}

// opengl.glEvalCoord2dv(u[]:Number)
Gurax_DeclareFunction(glEvalCoord2dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLdouble>();
	// Function body
	glEvalCoord2dv(u);
	return Value::nil();
}

// opengl.glEvalCoord2f(u:Number, v:Number)
Gurax_DeclareFunction(glEvalCoord2f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat u = args.PickNumber<GLfloat>();
	GLfloat v = args.PickNumber<GLfloat>();
	// Function body
	glEvalCoord2f(u, v);
	return Value::nil();
}

// opengl.glEvalCoord2fv(u[]:Number)
Gurax_DeclareFunction(glEvalCoord2fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLfloat>();
	// Function body
	glEvalCoord2fv(u);
	return Value::nil();
}

// opengl.glEvalMesh1(mode:Number, i1:Number, i2:Number)
Gurax_DeclareFunction(glEvalMesh1)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalMesh1)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLint i1 = args.PickNumber<GLint>();
	GLint i2 = args.PickNumber<GLint>();
	// Function body
	glEvalMesh1(mode, i1, i2);
	return Value::nil();
}

// opengl.glEvalMesh2(mode:Number, i1:Number, i2:Number, j1:Number, j2:Number)
Gurax_DeclareFunction(glEvalMesh2)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("j1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("j2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalMesh2)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLint i1 = args.PickNumber<GLint>();
	GLint i2 = args.PickNumber<GLint>();
	GLint j1 = args.PickNumber<GLint>();
	GLint j2 = args.PickNumber<GLint>();
	// Function body
	glEvalMesh2(mode, i1, i2, j1, j2);
	return Value::nil();
}

// opengl.glEvalPoint1(i:Number)
Gurax_DeclareFunction(glEvalPoint1)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalPoint1)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	// Function body
	glEvalPoint1(i);
	return Value::nil();
}

// opengl.glEvalPoint2(i:Number, j:Number)
Gurax_DeclareFunction(glEvalPoint2)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("j", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalPoint2)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	GLint j = args.PickNumber<GLint>();
	// Function body
	glEvalPoint2(i, j);
	return Value::nil();
}

// opengl.glFinish()
Gurax_DeclareFunction(glFinish)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFinish)
{
	// Function body
	glFinish();
	return Value::nil();
}

// opengl.glFlush()
Gurax_DeclareFunction(glFlush)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFlush)
{
	// Function body
	glFlush();
	return Value::nil();
}

// opengl.glFogf(pname:Number, param:Number)
Gurax_DeclareFunction(glFogf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glFogf(pname, param);
	return Value::nil();
}

// opengl.glFogfv(pname:Number, params[]:Number)
Gurax_DeclareFunction(glFogfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glFogfv(pname, params);
	return Value::nil();
}

// opengl.glFogi(pname:Number, param:Number)
Gurax_DeclareFunction(glFogi)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogi)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glFogi(pname, param);
	return Value::nil();
}

// opengl.glFogiv(pname:Number, params[]:Number)
Gurax_DeclareFunction(glFogiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogiv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glFogiv(pname, params);
	return Value::nil();
}

// opengl.glFrontFace(mode:Number)
Gurax_DeclareFunction(glFrontFace)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFrontFace)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glFrontFace(mode);
	return Value::nil();
}

// opengl.glFrustum(left:Number, right:Number, bottom:Number, top:Number, zNear:Number, zFar:Number)
Gurax_DeclareFunction(glFrustum)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bottom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("top", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zNear", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zFar", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFrustum)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble left = args.PickNumber<GLdouble>();
	GLdouble right = args.PickNumber<GLdouble>();
	GLdouble bottom = args.PickNumber<GLdouble>();
	GLdouble top = args.PickNumber<GLdouble>();
	GLdouble zNear = args.PickNumber<GLdouble>();
	GLdouble zFar = args.PickNumber<GLdouble>();
	// Function body
	glFrustum(left, right, bottom, top, zNear, zFar);
	return Value::nil();
}

// opengl.glGenLists(range:Number)
Gurax_DeclareFunction(glGenLists)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGenLists)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei range = args.PickNumber<GLsizei>();
	// Function body
	GLuint rtn = glGenLists(range);
	return new Value_Number(rtn);
}

// opengl.glGetError()
Gurax_DeclareFunction(glGetError)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGetError)
{
	// Function body
	GLenum rtn = glGetError();
	return new Value_Number(rtn);
}

// opengl.glGetString(name:Number)
Gurax_DeclareFunction(glGetString)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGetString)
{
	// Arguments
	ArgPicker args(argument);
	GLenum name = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glGetString(name);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glHint(target:Number, mode:Number)
Gurax_DeclareFunction(glHint)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glHint)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glHint(target, mode);
	return Value::nil();
}

// opengl.glIndexMask(mask:Number)
Gurax_DeclareFunction(glIndexMask)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexMask)
{
	// Arguments
	ArgPicker args(argument);
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glIndexMask(mask);
	return Value::nil();
}

// opengl.glIndexd(c:Number)
Gurax_DeclareFunction(glIndexd)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexd)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble c = args.PickNumber<GLdouble>();
	// Function body
	glIndexd(c);
	return Value::nil();
}

// opengl.glIndexdv(c[]:Number)
Gurax_DeclareFunction(glIndexdv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexdv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLdouble>();
	// Function body
	glIndexdv(c);
	return Value::nil();
}

// opengl.glIndexf(c:Number)
Gurax_DeclareFunction(glIndexf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexf)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat c = args.PickNumber<GLfloat>();
	// Function body
	glIndexf(c);
	return Value::nil();
}

// opengl.glIndexfv(c[]:Number)
Gurax_DeclareFunction(glIndexfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexfv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLfloat>();
	// Function body
	glIndexfv(c);
	return Value::nil();
}

// opengl.glIndexi(c:Number)
Gurax_DeclareFunction(glIndexi)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexi)
{
	// Arguments
	ArgPicker args(argument);
	GLint c = args.PickNumber<GLint>();
	// Function body
	glIndexi(c);
	return Value::nil();
}

// opengl.glIndexiv(c[]:Number)
Gurax_DeclareFunction(glIndexiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexiv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLint>();
	// Function body
	glIndexiv(c);
	return Value::nil();
}

// opengl.glIndexs(c:Number)
Gurax_DeclareFunction(glIndexs)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexs)
{
	// Arguments
	ArgPicker args(argument);
	GLshort c = args.PickNumber<GLshort>();
	// Function body
	glIndexs(c);
	return Value::nil();
}

// opengl.glIndexsv(c[]:Number)
Gurax_DeclareFunction(glIndexsv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexsv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLshort>();
	// Function body
	glIndexsv(c);
	return Value::nil();
}

// opengl.glIndexub(c:Number)
Gurax_DeclareFunction(glIndexub)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexub)
{
	// Arguments
	ArgPicker args(argument);
	GLubyte c = args.PickNumber<GLubyte>();
	// Function body
	glIndexub(c);
	return Value::nil();
}

// opengl.glIndexubv(c[]:Number)
Gurax_DeclareFunction(glIndexubv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexubv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLubyte>();
	// Function body
	glIndexubv(c);
	return Value::nil();
}

// opengl.glInitNames()
Gurax_DeclareFunction(glInitNames)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glInitNames)
{
	// Function body
	glInitNames();
	return Value::nil();
}

// opengl.glIsEnabled(cap:Number)
Gurax_DeclareFunction(glIsEnabled)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsEnabled)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	GLboolean rtn = glIsEnabled(cap);
	return new Value_Bool(!!rtn);
}

// opengl.glIsList(list:Number)
Gurax_DeclareFunction(glIsList)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsList)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsList(list);
	return new Value_Bool(!!rtn);
}

// opengl.glIsTexture(texture:Number)
Gurax_DeclareFunction(glIsTexture)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsTexture)
{
	// Arguments
	ArgPicker args(argument);
	GLuint texture = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsTexture(texture);
	return new Value_Bool(!!rtn);
}

// opengl.glLightModelf(pname:Number, param:Number)
Gurax_DeclareFunction(glLightModelf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModelf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glLightModelf(pname, param);
	return Value::nil();
}

// opengl.glLightModelfv(pname:Number, params[]:Number)
Gurax_DeclareFunction(glLightModelfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModelfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glLightModelfv(pname, params);
	return Value::nil();
}

// opengl.glLightModeli(pname:Number, param:Number)
Gurax_DeclareFunction(glLightModeli)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModeli)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glLightModeli(pname, param);
	return Value::nil();
}

// opengl.glLightModeliv(pname:Number, params[]:Number)
Gurax_DeclareFunction(glLightModeliv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModeliv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glLightModeliv(pname, params);
	return Value::nil();
}

// opengl.glLightf(light:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glLightf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum light = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glLightf(light, pname, param);
	return Value::nil();
}

// opengl.glLightfv(light:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glLightfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum light = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glLightfv(light, pname, params);
	return Value::nil();
}

// opengl.glLighti(light:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glLighti)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLighti)
{
	// Arguments
	ArgPicker args(argument);
	GLenum light = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glLighti(light, pname, param);
	return Value::nil();
}

// opengl.glLightiv(light:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glLightiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightiv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum light = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glLightiv(light, pname, params);
	return Value::nil();
}

// opengl.glLineStipple(factor:Number, pattern:Number)
Gurax_DeclareFunction(glLineStipple)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pattern", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLineStipple)
{
	// Arguments
	ArgPicker args(argument);
	GLint factor = args.PickNumber<GLint>();
	GLushort pattern = args.PickNumber<GLushort>();
	// Function body
	glLineStipple(factor, pattern);
	return Value::nil();
}

// opengl.glLineWidth(width:Number)
Gurax_DeclareFunction(glLineWidth)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLineWidth)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat width = args.PickNumber<GLfloat>();
	// Function body
	glLineWidth(width);
	return Value::nil();
}

// opengl.glListBase(base:Number)
Gurax_DeclareFunction(glListBase)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glListBase)
{
	// Arguments
	ArgPicker args(argument);
	GLuint base = args.PickNumber<GLuint>();
	// Function body
	glListBase(base);
	return Value::nil();
}

// opengl.glLoadIdentity()
Gurax_DeclareFunction(glLoadIdentity)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadIdentity)
{
	// Function body
	glLoadIdentity();
	return Value::nil();
}

// opengl.glLoadMatrixd(m[]:Number)
Gurax_DeclareFunction(glLoadMatrixd)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadMatrixd)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glLoadMatrixd(m);
	return Value::nil();
}

// opengl.glLoadMatrixf(m[]:Number)
Gurax_DeclareFunction(glLoadMatrixf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadMatrixf)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glLoadMatrixf(m);
	return Value::nil();
}

// opengl.glLoadName(name:Number)
Gurax_DeclareFunction(glLoadName)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadName)
{
	// Arguments
	ArgPicker args(argument);
	GLuint name = args.PickNumber<GLuint>();
	// Function body
	glLoadName(name);
	return Value::nil();
}

// opengl.glLogicOp(opcode:Number)
Gurax_DeclareFunction(glLogicOp)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("opcode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLogicOp)
{
	// Arguments
	ArgPicker args(argument);
	GLenum opcode = args.PickNumber<GLenum>();
	// Function body
	glLogicOp(opcode);
	return Value::nil();
}

// opengl.glMap1d(target:Number, u1:Number, u2:Number, stride:Number, order:Number, points[]:Number)
Gurax_DeclareFunction(glMap1d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMap1d)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLdouble u1 = args.PickNumber<GLdouble>();
	GLdouble u2 = args.PickNumber<GLdouble>();
	GLint stride = args.PickNumber<GLint>();
	GLint order = args.PickNumber<GLint>();
	auto points = args.PickNumList<GLdouble>();
	// Function body
	glMap1d(target, u1, u2, stride, order, points);
	return Value::nil();
}

// opengl.glMap1f(target:Number, u1:Number, u2:Number, stride:Number, order:Number, points[]:Number)
Gurax_DeclareFunction(glMap1f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMap1f)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLfloat u1 = args.PickNumber<GLfloat>();
	GLfloat u2 = args.PickNumber<GLfloat>();
	GLint stride = args.PickNumber<GLint>();
	GLint order = args.PickNumber<GLint>();
	auto points = args.PickNumList<GLfloat>();
	// Function body
	glMap1f(target, u1, u2, stride, order, points);
	return Value::nil();
}

// opengl.glMap2d(target:Number, u1:Number, u2:Number, ustride:Number, uorder:Number, v1:Number, v2:Number, vstride:Number, vorder:Number, points[]:Number)
Gurax_DeclareFunction(glMap2d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ustride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("uorder", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vstride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vorder", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMap2d)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLdouble u1 = args.PickNumber<GLdouble>();
	GLdouble u2 = args.PickNumber<GLdouble>();
	GLint ustride = args.PickNumber<GLint>();
	GLint uorder = args.PickNumber<GLint>();
	GLdouble v1 = args.PickNumber<GLdouble>();
	GLdouble v2 = args.PickNumber<GLdouble>();
	GLint vstride = args.PickNumber<GLint>();
	GLint vorder = args.PickNumber<GLint>();
	auto points = args.PickNumList<GLdouble>();
	// Function body
	glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
	return Value::nil();
}

// opengl.glMap2f(target:Number, u1:Number, u2:Number, ustride:Number, uorder:Number, v1:Number, v2:Number, vstride:Number, vorder:Number, points[]:Number)
Gurax_DeclareFunction(glMap2f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ustride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("uorder", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vstride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vorder", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMap2f)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLfloat u1 = args.PickNumber<GLfloat>();
	GLfloat u2 = args.PickNumber<GLfloat>();
	GLint ustride = args.PickNumber<GLint>();
	GLint uorder = args.PickNumber<GLint>();
	GLfloat v1 = args.PickNumber<GLfloat>();
	GLfloat v2 = args.PickNumber<GLfloat>();
	GLint vstride = args.PickNumber<GLint>();
	GLint vorder = args.PickNumber<GLint>();
	auto points = args.PickNumList<GLfloat>();
	// Function body
	glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
	return Value::nil();
}

// opengl.glMapGrid1d(un:Number, u1:Number, u2:Number)
Gurax_DeclareFunction(glMapGrid1d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMapGrid1d)
{
	// Arguments
	ArgPicker args(argument);
	GLint un = args.PickNumber<GLint>();
	GLdouble u1 = args.PickNumber<GLdouble>();
	GLdouble u2 = args.PickNumber<GLdouble>();
	// Function body
	glMapGrid1d(un, u1, u2);
	return Value::nil();
}

// opengl.glMapGrid1f(un:Number, u1:Number, u2:Number)
Gurax_DeclareFunction(glMapGrid1f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMapGrid1f)
{
	// Arguments
	ArgPicker args(argument);
	GLint un = args.PickNumber<GLint>();
	GLfloat u1 = args.PickNumber<GLfloat>();
	GLfloat u2 = args.PickNumber<GLfloat>();
	// Function body
	glMapGrid1f(un, u1, u2);
	return Value::nil();
}

// opengl.glMapGrid2d(un:Number, u1:Number, u2:Number, vn:Number, v1:Number, v2:Number)
Gurax_DeclareFunction(glMapGrid2d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMapGrid2d)
{
	// Arguments
	ArgPicker args(argument);
	GLint un = args.PickNumber<GLint>();
	GLdouble u1 = args.PickNumber<GLdouble>();
	GLdouble u2 = args.PickNumber<GLdouble>();
	GLint vn = args.PickNumber<GLint>();
	GLdouble v1 = args.PickNumber<GLdouble>();
	GLdouble v2 = args.PickNumber<GLdouble>();
	// Function body
	glMapGrid2d(un, u1, u2, vn, v1, v2);
	return Value::nil();
}

// opengl.glMapGrid2f(un:Number, u1:Number, u2:Number, vn:Number, v1:Number, v2:Number)
Gurax_DeclareFunction(glMapGrid2f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMapGrid2f)
{
	// Arguments
	ArgPicker args(argument);
	GLint un = args.PickNumber<GLint>();
	GLfloat u1 = args.PickNumber<GLfloat>();
	GLfloat u2 = args.PickNumber<GLfloat>();
	GLint vn = args.PickNumber<GLint>();
	GLfloat v1 = args.PickNumber<GLfloat>();
	GLfloat v2 = args.PickNumber<GLfloat>();
	// Function body
	glMapGrid2f(un, u1, u2, vn, v1, v2);
	return Value::nil();
}

// opengl.glMaterialf(face:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glMaterialf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMaterialf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glMaterialf(face, pname, param);
	return Value::nil();
}

// opengl.glMaterialfv(face:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glMaterialfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMaterialfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glMaterialfv(face, pname, params);
	return Value::nil();
}

// opengl.glMateriali(face:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glMateriali)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMateriali)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glMateriali(face, pname, param);
	return Value::nil();
}

// opengl.glMaterialiv(face:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glMaterialiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMaterialiv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glMaterialiv(face, pname, params);
	return Value::nil();
}

// opengl.glMatrixMode(mode:Number)
Gurax_DeclareFunction(glMatrixMode)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMatrixMode)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glMatrixMode(mode);
	return Value::nil();
}

// opengl.glMultMatrixd(m[]:Number)
Gurax_DeclareFunction(glMultMatrixd)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultMatrixd)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glMultMatrixd(m);
	return Value::nil();
}

// opengl.glMultMatrixf(m[]:Number)
Gurax_DeclareFunction(glMultMatrixf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultMatrixf)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glMultMatrixf(m);
	return Value::nil();
}

// opengl.glNewList(list:Number, mode:Number)
Gurax_DeclareFunction(glNewList)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNewList)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glNewList(list, mode);
	return Value::nil();
}

// opengl.glNormal3b(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunction(glNormal3b)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3b)
{
	// Arguments
	ArgPicker args(argument);
	GLbyte nx = args.PickNumber<GLbyte>();
	GLbyte ny = args.PickNumber<GLbyte>();
	GLbyte nz = args.PickNumber<GLbyte>();
	// Function body
	glNormal3b(nx, ny, nz);
	return Value::nil();
}

// opengl.glNormal3bv(v[]:Number)
Gurax_DeclareFunction(glNormal3bv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3bv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glNormal3bv(v);
	return Value::nil();
}

// opengl.glNormal3d(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunction(glNormal3d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble nx = args.PickNumber<GLdouble>();
	GLdouble ny = args.PickNumber<GLdouble>();
	GLdouble nz = args.PickNumber<GLdouble>();
	// Function body
	glNormal3d(nx, ny, nz);
	return Value::nil();
}

// opengl.glNormal3dv(v[]:Number)
Gurax_DeclareFunction(glNormal3dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glNormal3dv(v);
	return Value::nil();
}

// opengl.glNormal3f(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunction(glNormal3f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat nx = args.PickNumber<GLfloat>();
	GLfloat ny = args.PickNumber<GLfloat>();
	GLfloat nz = args.PickNumber<GLfloat>();
	// Function body
	glNormal3f(nx, ny, nz);
	return Value::nil();
}

// opengl.glNormal3fv(v[]:Number)
Gurax_DeclareFunction(glNormal3fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glNormal3fv(v);
	return Value::nil();
}

// opengl.glNormal3i(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunction(glNormal3i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3i)
{
	// Arguments
	ArgPicker args(argument);
	GLint nx = args.PickNumber<GLint>();
	GLint ny = args.PickNumber<GLint>();
	GLint nz = args.PickNumber<GLint>();
	// Function body
	glNormal3i(nx, ny, nz);
	return Value::nil();
}

// opengl.glNormal3iv(v[]:Number)
Gurax_DeclareFunction(glNormal3iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glNormal3iv(v);
	return Value::nil();
}

// opengl.glNormal3s(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunction(glNormal3s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort nx = args.PickNumber<GLshort>();
	GLshort ny = args.PickNumber<GLshort>();
	GLshort nz = args.PickNumber<GLshort>();
	// Function body
	glNormal3s(nx, ny, nz);
	return Value::nil();
}

// opengl.glNormal3sv(v[]:Number)
Gurax_DeclareFunction(glNormal3sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glNormal3sv(v);
	return Value::nil();
}

// opengl.glOrtho(left:Number, right:Number, bottom:Number, top:Number, zNear:Number, zFar:Number)
Gurax_DeclareFunction(glOrtho)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bottom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("top", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zNear", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zFar", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glOrtho)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble left = args.PickNumber<GLdouble>();
	GLdouble right = args.PickNumber<GLdouble>();
	GLdouble bottom = args.PickNumber<GLdouble>();
	GLdouble top = args.PickNumber<GLdouble>();
	GLdouble zNear = args.PickNumber<GLdouble>();
	GLdouble zFar = args.PickNumber<GLdouble>();
	// Function body
	glOrtho(left, right, bottom, top, zNear, zFar);
	return Value::nil();
}

// opengl.glPassThrough(token:Number)
Gurax_DeclareFunction(glPassThrough)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("token", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPassThrough)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat token = args.PickNumber<GLfloat>();
	// Function body
	glPassThrough(token);
	return Value::nil();
}

// opengl.glPixelMapfv(map:Number, mapsize:Number, values[]:Number)
Gurax_DeclareFunction(glPixelMapfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelMapfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum map = args.PickNumber<GLenum>();
	GLsizei mapsize = args.PickNumber<GLsizei>();
	auto values = args.PickNumList<GLfloat>();
	// Function body
	glPixelMapfv(map, mapsize, values);
	return Value::nil();
}

// opengl.glPixelMapuiv(map:Number, mapsize:Number, values[]:Number)
Gurax_DeclareFunction(glPixelMapuiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelMapuiv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum map = args.PickNumber<GLenum>();
	GLsizei mapsize = args.PickNumber<GLsizei>();
	auto values = args.PickNumList<GLuint>();
	// Function body
	glPixelMapuiv(map, mapsize, values);
	return Value::nil();
}

// opengl.glPixelMapusv(map:Number, mapsize:Number, values[]:Number)
Gurax_DeclareFunction(glPixelMapusv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelMapusv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum map = args.PickNumber<GLenum>();
	GLsizei mapsize = args.PickNumber<GLsizei>();
	auto values = args.PickNumList<GLushort>();
	// Function body
	glPixelMapusv(map, mapsize, values);
	return Value::nil();
}

// opengl.glPixelStoref(pname:Number, param:Number)
Gurax_DeclareFunction(glPixelStoref)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelStoref)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glPixelStoref(pname, param);
	return Value::nil();
}

// opengl.glPixelStorei(pname:Number, param:Number)
Gurax_DeclareFunction(glPixelStorei)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelStorei)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glPixelStorei(pname, param);
	return Value::nil();
}

// opengl.glPixelTransferf(pname:Number, param:Number)
Gurax_DeclareFunction(glPixelTransferf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelTransferf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glPixelTransferf(pname, param);
	return Value::nil();
}

// opengl.glPixelTransferi(pname:Number, param:Number)
Gurax_DeclareFunction(glPixelTransferi)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelTransferi)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glPixelTransferi(pname, param);
	return Value::nil();
}

// opengl.glPixelZoom(xfactor:Number, yfactor:Number)
Gurax_DeclareFunction(glPixelZoom)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelZoom)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat xfactor = args.PickNumber<GLfloat>();
	GLfloat yfactor = args.PickNumber<GLfloat>();
	// Function body
	glPixelZoom(xfactor, yfactor);
	return Value::nil();
}

// opengl.glPointSize(size:Number)
Gurax_DeclareFunction(glPointSize)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPointSize)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat size = args.PickNumber<GLfloat>();
	// Function body
	glPointSize(size);
	return Value::nil();
}

// opengl.glPolygonMode(face:Number, mode:Number)
Gurax_DeclareFunction(glPolygonMode)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPolygonMode)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glPolygonMode(face, mode);
	return Value::nil();
}

// opengl.glPolygonOffset(factor:Number, units:Number)
Gurax_DeclareFunction(glPolygonOffset)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("units", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPolygonOffset)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat factor = args.PickNumber<GLfloat>();
	GLfloat units = args.PickNumber<GLfloat>();
	// Function body
	glPolygonOffset(factor, units);
	return Value::nil();
}

// opengl.glPolygonStipple(mask[]:Number)
Gurax_DeclareFunction(glPolygonStipple)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPolygonStipple)
{
	// Arguments
	ArgPicker args(argument);
	auto mask = args.PickNumList<GLubyte>();
	// Function body
	glPolygonStipple(mask);
	return Value::nil();
}

// opengl.glPopAttrib()
Gurax_DeclareFunction(glPopAttrib)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopAttrib)
{
	// Function body
	glPopAttrib();
	return Value::nil();
}

// opengl.glPopClientAttrib()
Gurax_DeclareFunction(glPopClientAttrib)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopClientAttrib)
{
	// Function body
	glPopClientAttrib();
	return Value::nil();
}

// opengl.glPopMatrix()
Gurax_DeclareFunction(glPopMatrix)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopMatrix)
{
	// Function body
	glPopMatrix();
	return Value::nil();
}

// opengl.glPopName()
Gurax_DeclareFunction(glPopName)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopName)
{
	// Function body
	glPopName();
	return Value::nil();
}

// opengl.glPrioritizeTextures(n:Number, textures[]:Number, priorities[]:Number)
Gurax_DeclareFunction(glPrioritizeTextures)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textures", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("priorities", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPrioritizeTextures)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	auto textures = args.PickNumList<GLuint>();
	auto priorities = args.PickNumList<GLclampf>();
	// Function body
	glPrioritizeTextures(n, textures, priorities);
	return Value::nil();
}

// opengl.glPushAttrib(mask:Number)
Gurax_DeclareFunction(glPushAttrib)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushAttrib)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glPushAttrib(mask);
	return Value::nil();
}

// opengl.glPushClientAttrib(mask:Number)
Gurax_DeclareFunction(glPushClientAttrib)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushClientAttrib)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glPushClientAttrib(mask);
	return Value::nil();
}

// opengl.glPushMatrix()
Gurax_DeclareFunction(glPushMatrix)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushMatrix)
{
	// Function body
	glPushMatrix();
	return Value::nil();
}

// opengl.glPushName(name:Number)
Gurax_DeclareFunction(glPushName)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushName)
{
	// Arguments
	ArgPicker args(argument);
	GLuint name = args.PickNumber<GLuint>();
	// Function body
	glPushName(name);
	return Value::nil();
}

// opengl.glRasterPos2d(x:Number, y:Number)
Gurax_DeclareFunction(glRasterPos2d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	// Function body
	glRasterPos2d(x, y);
	return Value::nil();
}

// opengl.glRasterPos2dv(v[]:Number)
Gurax_DeclareFunction(glRasterPos2dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos2dv(v);
	return Value::nil();
}

// opengl.glRasterPos2f(x:Number, y:Number)
Gurax_DeclareFunction(glRasterPos2f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	// Function body
	glRasterPos2f(x, y);
	return Value::nil();
}

// opengl.glRasterPos2fv(v[]:Number)
Gurax_DeclareFunction(glRasterPos2fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos2fv(v);
	return Value::nil();
}

// opengl.glRasterPos2i(x:Number, y:Number)
Gurax_DeclareFunction(glRasterPos2i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2i)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	// Function body
	glRasterPos2i(x, y);
	return Value::nil();
}

// opengl.glRasterPos2iv(v[]:Number)
Gurax_DeclareFunction(glRasterPos2iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos2iv(v);
	return Value::nil();
}

// opengl.glRasterPos2s(x:Number, y:Number)
Gurax_DeclareFunction(glRasterPos2s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	// Function body
	glRasterPos2s(x, y);
	return Value::nil();
}

// opengl.glRasterPos2sv(v[]:Number)
Gurax_DeclareFunction(glRasterPos2sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos2sv(v);
	return Value::nil();
}

// opengl.glRasterPos3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glRasterPos3d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glRasterPos3d(x, y, z);
	return Value::nil();
}

// opengl.glRasterPos3dv(v[]:Number)
Gurax_DeclareFunction(glRasterPos3dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos3dv(v);
	return Value::nil();
}

// opengl.glRasterPos3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glRasterPos3f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glRasterPos3f(x, y, z);
	return Value::nil();
}

// opengl.glRasterPos3fv(v[]:Number)
Gurax_DeclareFunction(glRasterPos3fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos3fv(v);
	return Value::nil();
}

// opengl.glRasterPos3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glRasterPos3i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3i)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLint z = args.PickNumber<GLint>();
	// Function body
	glRasterPos3i(x, y, z);
	return Value::nil();
}

// opengl.glRasterPos3iv(v[]:Number)
Gurax_DeclareFunction(glRasterPos3iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos3iv(v);
	return Value::nil();
}

// opengl.glRasterPos3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glRasterPos3s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	// Function body
	glRasterPos3s(x, y, z);
	return Value::nil();
}

// opengl.glRasterPos3sv(v[]:Number)
Gurax_DeclareFunction(glRasterPos3sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos3sv(v);
	return Value::nil();
}

// opengl.glRasterPos4d(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glRasterPos4d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	GLdouble w = args.PickNumber<GLdouble>();
	// Function body
	glRasterPos4d(x, y, z, w);
	return Value::nil();
}

// opengl.glRasterPos4dv(v[]:Number)
Gurax_DeclareFunction(glRasterPos4dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos4dv(v);
	return Value::nil();
}

// opengl.glRasterPos4f(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glRasterPos4f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	GLfloat w = args.PickNumber<GLfloat>();
	// Function body
	glRasterPos4f(x, y, z, w);
	return Value::nil();
}

// opengl.glRasterPos4fv(v[]:Number)
Gurax_DeclareFunction(glRasterPos4fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos4fv(v);
	return Value::nil();
}

// opengl.glRasterPos4i(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glRasterPos4i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4i)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLint z = args.PickNumber<GLint>();
	GLint w = args.PickNumber<GLint>();
	// Function body
	glRasterPos4i(x, y, z, w);
	return Value::nil();
}

// opengl.glRasterPos4iv(v[]:Number)
Gurax_DeclareFunction(glRasterPos4iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos4iv(v);
	return Value::nil();
}

// opengl.glRasterPos4s(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glRasterPos4s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	GLshort w = args.PickNumber<GLshort>();
	// Function body
	glRasterPos4s(x, y, z, w);
	return Value::nil();
}

// opengl.glRasterPos4sv(v[]:Number)
Gurax_DeclareFunction(glRasterPos4sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos4sv(v);
	return Value::nil();
}

// opengl.glReadBuffer(mode:Number)
Gurax_DeclareFunction(glReadBuffer)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glReadBuffer)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glReadBuffer(mode);
	return Value::nil();
}

// opengl.glRectd(x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunction(glRectd)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectd)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x1 = args.PickNumber<GLdouble>();
	GLdouble y1 = args.PickNumber<GLdouble>();
	GLdouble x2 = args.PickNumber<GLdouble>();
	GLdouble y2 = args.PickNumber<GLdouble>();
	// Function body
	glRectd(x1, y1, x2, y2);
	return Value::nil();
}

// opengl.glRectdv(v1[]:Number, v2[]:Number)
Gurax_DeclareFunction(glRectdv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectdv)
{
	// Arguments
	ArgPicker args(argument);
	auto v1 = args.PickNumList<GLdouble>();
	auto v2 = args.PickNumList<GLdouble>();
	// Function body
	glRectdv(v1, v2);
	return Value::nil();
}

// opengl.glRectf(x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunction(glRectf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectf)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x1 = args.PickNumber<GLfloat>();
	GLfloat y1 = args.PickNumber<GLfloat>();
	GLfloat x2 = args.PickNumber<GLfloat>();
	GLfloat y2 = args.PickNumber<GLfloat>();
	// Function body
	glRectf(x1, y1, x2, y2);
	return Value::nil();
}

// opengl.glRectfv(v1[]:Number, v2[]:Number)
Gurax_DeclareFunction(glRectfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectfv)
{
	// Arguments
	ArgPicker args(argument);
	auto v1 = args.PickNumList<GLfloat>();
	auto v2 = args.PickNumList<GLfloat>();
	// Function body
	glRectfv(v1, v2);
	return Value::nil();
}

// opengl.glRecti(x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunction(glRecti)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRecti)
{
	// Arguments
	ArgPicker args(argument);
	GLint x1 = args.PickNumber<GLint>();
	GLint y1 = args.PickNumber<GLint>();
	GLint x2 = args.PickNumber<GLint>();
	GLint y2 = args.PickNumber<GLint>();
	// Function body
	glRecti(x1, y1, x2, y2);
	return Value::nil();
}

// opengl.glRectiv(v1[]:Number, v2[]:Number)
Gurax_DeclareFunction(glRectiv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectiv)
{
	// Arguments
	ArgPicker args(argument);
	auto v1 = args.PickNumList<GLint>();
	auto v2 = args.PickNumList<GLint>();
	// Function body
	glRectiv(v1, v2);
	return Value::nil();
}

// opengl.glRects(x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunction(glRects)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRects)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x1 = args.PickNumber<GLshort>();
	GLshort y1 = args.PickNumber<GLshort>();
	GLshort x2 = args.PickNumber<GLshort>();
	GLshort y2 = args.PickNumber<GLshort>();
	// Function body
	glRects(x1, y1, x2, y2);
	return Value::nil();
}

// opengl.glRectsv(v1[]:Number, v2[]:Number)
Gurax_DeclareFunction(glRectsv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectsv)
{
	// Arguments
	ArgPicker args(argument);
	auto v1 = args.PickNumList<GLshort>();
	auto v2 = args.PickNumList<GLshort>();
	// Function body
	glRectsv(v1, v2);
	return Value::nil();
}

// opengl.glRenderMode(mode:Number)
Gurax_DeclareFunction(glRenderMode)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRenderMode)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	GLint rtn = glRenderMode(mode);
	return new Value_Number(rtn);
}

// opengl.glRotated(angle:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glRotated)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRotated)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble angle = args.PickNumber<GLdouble>();
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glRotated(angle, x, y, z);
	return Value::nil();
}

// opengl.glRotatef(angle:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glRotatef)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRotatef)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat angle = args.PickNumber<GLfloat>();
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glRotatef(angle, x, y, z);
	return Value::nil();
}

// opengl.glScaled(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glScaled)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glScaled)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glScaled(x, y, z);
	return Value::nil();
}

// opengl.glScalef(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glScalef)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glScalef)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glScalef(x, y, z);
	return Value::nil();
}

// opengl.glScissor(x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunction(glScissor)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glScissor)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	// Function body
	glScissor(x, y, width, height);
	return Value::nil();
}

// opengl.glShadeModel(mode:Number)
Gurax_DeclareFunction(glShadeModel)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glShadeModel)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glShadeModel(mode);
	return Value::nil();
}

// opengl.glStencilFunc(func:Number, ref:Number, mask:Number)
Gurax_DeclareFunction(glStencilFunc)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilFunc)
{
	// Arguments
	ArgPicker args(argument);
	GLenum func = args.PickNumber<GLenum>();
	GLint ref = args.PickNumber<GLint>();
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glStencilFunc(func, ref, mask);
	return Value::nil();
}

// opengl.glStencilMask(mask:Number)
Gurax_DeclareFunction(glStencilMask)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilMask)
{
	// Arguments
	ArgPicker args(argument);
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glStencilMask(mask);
	return Value::nil();
}

// opengl.glStencilOp(fail:Number, zfail:Number, zpass:Number)
Gurax_DeclareFunction(glStencilOp)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zfail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zpass", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilOp)
{
	// Arguments
	ArgPicker args(argument);
	GLenum fail = args.PickNumber<GLenum>();
	GLenum zfail = args.PickNumber<GLenum>();
	GLenum zpass = args.PickNumber<GLenum>();
	// Function body
	glStencilOp(fail, zfail, zpass);
	return Value::nil();
}

// opengl.glTexCoord1d(s:Number)
Gurax_DeclareFunction(glTexCoord1d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble s = args.PickNumber<GLdouble>();
	// Function body
	glTexCoord1d(s);
	return Value::nil();
}

// opengl.glTexCoord1dv(v[]:Number)
Gurax_DeclareFunction(glTexCoord1dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord1dv(v);
	return Value::nil();
}

// opengl.glTexCoord1f(s:Number)
Gurax_DeclareFunction(glTexCoord1f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat s = args.PickNumber<GLfloat>();
	// Function body
	glTexCoord1f(s);
	return Value::nil();
}

// opengl.glTexCoord1fv(v[]:Number)
Gurax_DeclareFunction(glTexCoord1fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord1fv(v);
	return Value::nil();
}

// opengl.glTexCoord1i(s:Number)
Gurax_DeclareFunction(glTexCoord1i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1i)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	// Function body
	glTexCoord1i(s);
	return Value::nil();
}

// opengl.glTexCoord1iv(v[]:Number)
Gurax_DeclareFunction(glTexCoord1iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord1iv(v);
	return Value::nil();
}

// opengl.glTexCoord1s(s:Number)
Gurax_DeclareFunction(glTexCoord1s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort s = args.PickNumber<GLshort>();
	// Function body
	glTexCoord1s(s);
	return Value::nil();
}

// opengl.glTexCoord1sv(v[]:Number)
Gurax_DeclareFunction(glTexCoord1sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord1sv(v);
	return Value::nil();
}

// opengl.glTexCoord2d(s:Number, t:Number)
Gurax_DeclareFunction(glTexCoord2d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble s = args.PickNumber<GLdouble>();
	GLdouble t = args.PickNumber<GLdouble>();
	// Function body
	glTexCoord2d(s, t);
	return Value::nil();
}

// opengl.glTexCoord2dv(v[]:Number)
Gurax_DeclareFunction(glTexCoord2dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord2dv(v);
	return Value::nil();
}

// opengl.glTexCoord2f(s:Number, t:Number)
Gurax_DeclareFunction(glTexCoord2f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat s = args.PickNumber<GLfloat>();
	GLfloat t = args.PickNumber<GLfloat>();
	// Function body
	glTexCoord2f(s, t);
	return Value::nil();
}

// opengl.glTexCoord2fv(v[]:Number)
Gurax_DeclareFunction(glTexCoord2fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord2fv(v);
	return Value::nil();
}

// opengl.glTexCoord2i(s:Number, t:Number)
Gurax_DeclareFunction(glTexCoord2i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2i)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	GLint t = args.PickNumber<GLint>();
	// Function body
	glTexCoord2i(s, t);
	return Value::nil();
}

// opengl.glTexCoord2iv(v[]:Number)
Gurax_DeclareFunction(glTexCoord2iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord2iv(v);
	return Value::nil();
}

// opengl.glTexCoord2s(s:Number, t:Number)
Gurax_DeclareFunction(glTexCoord2s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort s = args.PickNumber<GLshort>();
	GLshort t = args.PickNumber<GLshort>();
	// Function body
	glTexCoord2s(s, t);
	return Value::nil();
}

// opengl.glTexCoord2sv(v[]:Number)
Gurax_DeclareFunction(glTexCoord2sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord2sv(v);
	return Value::nil();
}

// opengl.glTexCoord3d(s:Number, t:Number, r:Number)
Gurax_DeclareFunction(glTexCoord3d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble s = args.PickNumber<GLdouble>();
	GLdouble t = args.PickNumber<GLdouble>();
	GLdouble r = args.PickNumber<GLdouble>();
	// Function body
	glTexCoord3d(s, t, r);
	return Value::nil();
}

// opengl.glTexCoord3dv(v[]:Number)
Gurax_DeclareFunction(glTexCoord3dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord3dv(v);
	return Value::nil();
}

// opengl.glTexCoord3f(s:Number, t:Number, r:Number)
Gurax_DeclareFunction(glTexCoord3f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat s = args.PickNumber<GLfloat>();
	GLfloat t = args.PickNumber<GLfloat>();
	GLfloat r = args.PickNumber<GLfloat>();
	// Function body
	glTexCoord3f(s, t, r);
	return Value::nil();
}

// opengl.glTexCoord3fv(v[]:Number)
Gurax_DeclareFunction(glTexCoord3fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord3fv(v);
	return Value::nil();
}

// opengl.glTexCoord3i(s:Number, t:Number, r:Number)
Gurax_DeclareFunction(glTexCoord3i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3i)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	GLint t = args.PickNumber<GLint>();
	GLint r = args.PickNumber<GLint>();
	// Function body
	glTexCoord3i(s, t, r);
	return Value::nil();
}

// opengl.glTexCoord3iv(v[]:Number)
Gurax_DeclareFunction(glTexCoord3iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord3iv(v);
	return Value::nil();
}

// opengl.glTexCoord3s(s:Number, t:Number, r:Number)
Gurax_DeclareFunction(glTexCoord3s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort s = args.PickNumber<GLshort>();
	GLshort t = args.PickNumber<GLshort>();
	GLshort r = args.PickNumber<GLshort>();
	// Function body
	glTexCoord3s(s, t, r);
	return Value::nil();
}

// opengl.glTexCoord3sv(v[]:Number)
Gurax_DeclareFunction(glTexCoord3sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord3sv(v);
	return Value::nil();
}

// opengl.glTexCoord4d(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunction(glTexCoord4d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble s = args.PickNumber<GLdouble>();
	GLdouble t = args.PickNumber<GLdouble>();
	GLdouble r = args.PickNumber<GLdouble>();
	GLdouble q = args.PickNumber<GLdouble>();
	// Function body
	glTexCoord4d(s, t, r, q);
	return Value::nil();
}

// opengl.glTexCoord4dv(v[]:Number)
Gurax_DeclareFunction(glTexCoord4dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord4dv(v);
	return Value::nil();
}

// opengl.glTexCoord4f(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunction(glTexCoord4f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat s = args.PickNumber<GLfloat>();
	GLfloat t = args.PickNumber<GLfloat>();
	GLfloat r = args.PickNumber<GLfloat>();
	GLfloat q = args.PickNumber<GLfloat>();
	// Function body
	glTexCoord4f(s, t, r, q);
	return Value::nil();
}

// opengl.glTexCoord4fv(v[]:Number)
Gurax_DeclareFunction(glTexCoord4fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord4fv(v);
	return Value::nil();
}

// opengl.glTexCoord4i(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunction(glTexCoord4i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4i)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	GLint t = args.PickNumber<GLint>();
	GLint r = args.PickNumber<GLint>();
	GLint q = args.PickNumber<GLint>();
	// Function body
	glTexCoord4i(s, t, r, q);
	return Value::nil();
}

// opengl.glTexCoord4iv(v[]:Number)
Gurax_DeclareFunction(glTexCoord4iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord4iv(v);
	return Value::nil();
}

// opengl.glTexCoord4s(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunction(glTexCoord4s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort s = args.PickNumber<GLshort>();
	GLshort t = args.PickNumber<GLshort>();
	GLshort r = args.PickNumber<GLshort>();
	GLshort q = args.PickNumber<GLshort>();
	// Function body
	glTexCoord4s(s, t, r, q);
	return Value::nil();
}

// opengl.glTexCoord4sv(v[]:Number)
Gurax_DeclareFunction(glTexCoord4sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord4sv(v);
	return Value::nil();
}

// opengl.glTexEnvf(target:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexEnvf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnvf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glTexEnvf(target, pname, param);
	return Value::nil();
}

// opengl.glTexEnvfv(target:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexEnvfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnvfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glTexEnvfv(target, pname, params);
	return Value::nil();
}

// opengl.glTexEnvi(target:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexEnvi)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnvi)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glTexEnvi(target, pname, param);
	return Value::nil();
}

// opengl.glTexEnviv(target:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexEnviv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnviv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glTexEnviv(target, pname, params);
	return Value::nil();
}

// opengl.glTexGend(coord:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexGend)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGend)
{
	// Arguments
	ArgPicker args(argument);
	GLenum coord = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLdouble param = args.PickNumber<GLdouble>();
	// Function body
	glTexGend(coord, pname, param);
	return Value::nil();
}

// opengl.glTexGendv(coord:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexGendv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGendv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum coord = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLdouble>();
	// Function body
	glTexGendv(coord, pname, params);
	return Value::nil();
}

// opengl.glTexGenf(coord:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexGenf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGenf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum coord = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glTexGenf(coord, pname, param);
	return Value::nil();
}

// opengl.glTexGenfv(coord:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexGenfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGenfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum coord = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glTexGenfv(coord, pname, params);
	return Value::nil();
}

// opengl.glTexGeni(coord:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexGeni)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGeni)
{
	// Arguments
	ArgPicker args(argument);
	GLenum coord = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glTexGeni(coord, pname, param);
	return Value::nil();
}

// opengl.glTexGeniv(coord:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexGeniv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGeniv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum coord = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glTexGeniv(coord, pname, params);
	return Value::nil();
}

// opengl.glTexParameterf(target:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexParameterf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameterf)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glTexParameterf(target, pname, param);
	return Value::nil();
}

// opengl.glTexParameterfv(target:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexParameterfv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameterfv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glTexParameterfv(target, pname, params);
	return Value::nil();
}

// opengl.glTexParameteri(target:Number, pname:Number, param:Number)
Gurax_DeclareFunction(glTexParameteri)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameteri)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glTexParameteri(target, pname, param);
	return Value::nil();
}

// opengl.glTexParameteriv(target:Number, pname:Number, params[]:Number)
Gurax_DeclareFunction(glTexParameteriv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameteriv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glTexParameteriv(target, pname, params);
	return Value::nil();
}

// opengl.glTranslated(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glTranslated)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTranslated)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glTranslated(x, y, z);
	return Value::nil();
}

// opengl.glTranslatef(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glTranslatef)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTranslatef)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glTranslatef(x, y, z);
	return Value::nil();
}

// opengl.glVertex2d(x:Number, y:Number)
Gurax_DeclareFunction(glVertex2d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	// Function body
	glVertex2d(x, y);
	return Value::nil();
}

// opengl.glVertex2dv(v[]:Number)
Gurax_DeclareFunction(glVertex2dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex2dv(v);
	return Value::nil();
}

// opengl.glVertex2f(x:Number, y:Number)
Gurax_DeclareFunction(glVertex2f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	// Function body
	glVertex2f(x, y);
	return Value::nil();
}

// opengl.glVertex2fv(v[]:Number)
Gurax_DeclareFunction(glVertex2fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex2fv(v);
	return Value::nil();
}

// opengl.glVertex2i(x:Number, y:Number)
Gurax_DeclareFunction(glVertex2i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2i)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	// Function body
	glVertex2i(x, y);
	return Value::nil();
}

// opengl.glVertex2iv(v[]:Number)
Gurax_DeclareFunction(glVertex2iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex2iv(v);
	return Value::nil();
}

// opengl.glVertex2s(x:Number, y:Number)
Gurax_DeclareFunction(glVertex2s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	// Function body
	glVertex2s(x, y);
	return Value::nil();
}

// opengl.glVertex2sv(v[]:Number)
Gurax_DeclareFunction(glVertex2sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex2sv(v);
	return Value::nil();
}

// opengl.glVertex3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glVertex3d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glVertex3d(x, y, z);
	return Value::nil();
}

// opengl.glVertex3dv(v[]:Number)
Gurax_DeclareFunction(glVertex3dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex3dv(v);
	return Value::nil();
}

// opengl.glVertex3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glVertex3f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glVertex3f(x, y, z);
	return Value::nil();
}

// opengl.glVertex3fv(v[]:Number)
Gurax_DeclareFunction(glVertex3fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex3fv(v);
	return Value::nil();
}

// opengl.glVertex3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glVertex3i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3i)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLint z = args.PickNumber<GLint>();
	// Function body
	glVertex3i(x, y, z);
	return Value::nil();
}

// opengl.glVertex3iv(v[]:Number)
Gurax_DeclareFunction(glVertex3iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex3iv(v);
	return Value::nil();
}

// opengl.glVertex3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunction(glVertex3s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	// Function body
	glVertex3s(x, y, z);
	return Value::nil();
}

// opengl.glVertex3sv(v[]:Number)
Gurax_DeclareFunction(glVertex3sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex3sv(v);
	return Value::nil();
}

// opengl.glVertex4d(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glVertex4d)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	GLdouble w = args.PickNumber<GLdouble>();
	// Function body
	glVertex4d(x, y, z, w);
	return Value::nil();
}

// opengl.glVertex4dv(v[]:Number)
Gurax_DeclareFunction(glVertex4dv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex4dv(v);
	return Value::nil();
}

// opengl.glVertex4f(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glVertex4f)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	GLfloat w = args.PickNumber<GLfloat>();
	// Function body
	glVertex4f(x, y, z, w);
	return Value::nil();
}

// opengl.glVertex4fv(v[]:Number)
Gurax_DeclareFunction(glVertex4fv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex4fv(v);
	return Value::nil();
}

// opengl.glVertex4i(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glVertex4i)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4i)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLint z = args.PickNumber<GLint>();
	GLint w = args.PickNumber<GLint>();
	// Function body
	glVertex4i(x, y, z, w);
	return Value::nil();
}

// opengl.glVertex4iv(v[]:Number)
Gurax_DeclareFunction(glVertex4iv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex4iv(v);
	return Value::nil();
}

// opengl.glVertex4s(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunction(glVertex4s)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	GLshort w = args.PickNumber<GLshort>();
	// Function body
	glVertex4s(x, y, z, w);
	return Value::nil();
}

// opengl.glVertex4sv(v[]:Number)
Gurax_DeclareFunction(glVertex4sv)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex4sv(v);
	return Value::nil();
}

// opengl.glViewport(x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunction(glViewport)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glViewport)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	// Function body
	glViewport(x, y, width, height);
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
	frame.Assign(Gurax_CreateFunction(glColor3ub));
	frame.Assign(Gurax_CreateFunction(glColor3ubv));
	frame.Assign(Gurax_CreateFunction(glColor3ui));
	frame.Assign(Gurax_CreateFunction(glColor3uiv));
	frame.Assign(Gurax_CreateFunction(glColor3us));
	frame.Assign(Gurax_CreateFunction(glColor3usv));
	frame.Assign(Gurax_CreateFunction(glColor4b));
	frame.Assign(Gurax_CreateFunction(glColor4bv));
	frame.Assign(Gurax_CreateFunction(glColor4d));
	frame.Assign(Gurax_CreateFunction(glColor4dv));
	frame.Assign(Gurax_CreateFunction(glColor4f));
	frame.Assign(Gurax_CreateFunction(glColor4fv));
	frame.Assign(Gurax_CreateFunction(glColor4i));
	frame.Assign(Gurax_CreateFunction(glColor4iv));
	frame.Assign(Gurax_CreateFunction(glColor4s));
	frame.Assign(Gurax_CreateFunction(glColor4sv));
	frame.Assign(Gurax_CreateFunction(glColor4ub));
	frame.Assign(Gurax_CreateFunction(glColor4ubv));
	frame.Assign(Gurax_CreateFunction(glColor4ui));
	frame.Assign(Gurax_CreateFunction(glColor4uiv));
	frame.Assign(Gurax_CreateFunction(glColor4us));
	frame.Assign(Gurax_CreateFunction(glColor4usv));
	frame.Assign(Gurax_CreateFunction(glColorMask));
	frame.Assign(Gurax_CreateFunction(glColorMaterial));
	frame.Assign(Gurax_CreateFunction(glCopyPixels));
	frame.Assign(Gurax_CreateFunction(glCopyTexImage1D));
	frame.Assign(Gurax_CreateFunction(glCopyTexImage2D));
	frame.Assign(Gurax_CreateFunction(glCopyTexSubImage1D));
	frame.Assign(Gurax_CreateFunction(glCopyTexSubImage2D));
	frame.Assign(Gurax_CreateFunction(glCullFace));
	frame.Assign(Gurax_CreateFunction(glDeleteLists));
	frame.Assign(Gurax_CreateFunction(glDepthFunc));
	frame.Assign(Gurax_CreateFunction(glDepthMask));
	frame.Assign(Gurax_CreateFunction(glDepthRange));
	frame.Assign(Gurax_CreateFunction(glDisable));
	frame.Assign(Gurax_CreateFunction(glDisableClientState));
	frame.Assign(Gurax_CreateFunction(glDrawArrays));
	frame.Assign(Gurax_CreateFunction(glDrawBuffer));
	frame.Assign(Gurax_CreateFunction(glEdgeFlag));
	frame.Assign(Gurax_CreateFunction(glEdgeFlagv));
	frame.Assign(Gurax_CreateFunction(glEnable));
	frame.Assign(Gurax_CreateFunction(glEnableClientState));
	frame.Assign(Gurax_CreateFunction(glEnd));
	frame.Assign(Gurax_CreateFunction(glEndList));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1d));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1dv));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1f));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1fv));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2d));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2dv));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2f));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2fv));
	frame.Assign(Gurax_CreateFunction(glEvalMesh1));
	frame.Assign(Gurax_CreateFunction(glEvalMesh2));
	frame.Assign(Gurax_CreateFunction(glEvalPoint1));
	frame.Assign(Gurax_CreateFunction(glEvalPoint2));
	frame.Assign(Gurax_CreateFunction(glFinish));
	frame.Assign(Gurax_CreateFunction(glFlush));
	frame.Assign(Gurax_CreateFunction(glFogf));
	frame.Assign(Gurax_CreateFunction(glFogfv));
	frame.Assign(Gurax_CreateFunction(glFogi));
	frame.Assign(Gurax_CreateFunction(glFogiv));
	frame.Assign(Gurax_CreateFunction(glFrontFace));
	frame.Assign(Gurax_CreateFunction(glFrustum));
	frame.Assign(Gurax_CreateFunction(glGenLists));
	frame.Assign(Gurax_CreateFunction(glGetError));
	frame.Assign(Gurax_CreateFunction(glGetString));
	frame.Assign(Gurax_CreateFunction(glHint));
	frame.Assign(Gurax_CreateFunction(glIndexMask));
	frame.Assign(Gurax_CreateFunction(glIndexd));
	frame.Assign(Gurax_CreateFunction(glIndexdv));
	frame.Assign(Gurax_CreateFunction(glIndexf));
	frame.Assign(Gurax_CreateFunction(glIndexfv));
	frame.Assign(Gurax_CreateFunction(glIndexi));
	frame.Assign(Gurax_CreateFunction(glIndexiv));
	frame.Assign(Gurax_CreateFunction(glIndexs));
	frame.Assign(Gurax_CreateFunction(glIndexsv));
	frame.Assign(Gurax_CreateFunction(glIndexub));
	frame.Assign(Gurax_CreateFunction(glIndexubv));
	frame.Assign(Gurax_CreateFunction(glInitNames));
	frame.Assign(Gurax_CreateFunction(glIsEnabled));
	frame.Assign(Gurax_CreateFunction(glIsList));
	frame.Assign(Gurax_CreateFunction(glIsTexture));
	frame.Assign(Gurax_CreateFunction(glLightModelf));
	frame.Assign(Gurax_CreateFunction(glLightModelfv));
	frame.Assign(Gurax_CreateFunction(glLightModeli));
	frame.Assign(Gurax_CreateFunction(glLightModeliv));
	frame.Assign(Gurax_CreateFunction(glLightf));
	frame.Assign(Gurax_CreateFunction(glLightfv));
	frame.Assign(Gurax_CreateFunction(glLighti));
	frame.Assign(Gurax_CreateFunction(glLightiv));
	frame.Assign(Gurax_CreateFunction(glLineStipple));
	frame.Assign(Gurax_CreateFunction(glLineWidth));
	frame.Assign(Gurax_CreateFunction(glListBase));
	frame.Assign(Gurax_CreateFunction(glLoadIdentity));
	frame.Assign(Gurax_CreateFunction(glLoadMatrixd));
	frame.Assign(Gurax_CreateFunction(glLoadMatrixf));
	frame.Assign(Gurax_CreateFunction(glLoadName));
	frame.Assign(Gurax_CreateFunction(glLogicOp));
	frame.Assign(Gurax_CreateFunction(glMap1d));
	frame.Assign(Gurax_CreateFunction(glMap1f));
	frame.Assign(Gurax_CreateFunction(glMap2d));
	frame.Assign(Gurax_CreateFunction(glMap2f));
	frame.Assign(Gurax_CreateFunction(glMapGrid1d));
	frame.Assign(Gurax_CreateFunction(glMapGrid1f));
	frame.Assign(Gurax_CreateFunction(glMapGrid2d));
	frame.Assign(Gurax_CreateFunction(glMapGrid2f));
	frame.Assign(Gurax_CreateFunction(glMaterialf));
	frame.Assign(Gurax_CreateFunction(glMaterialfv));
	frame.Assign(Gurax_CreateFunction(glMateriali));
	frame.Assign(Gurax_CreateFunction(glMaterialiv));
	frame.Assign(Gurax_CreateFunction(glMatrixMode));
	frame.Assign(Gurax_CreateFunction(glMultMatrixd));
	frame.Assign(Gurax_CreateFunction(glMultMatrixf));
	frame.Assign(Gurax_CreateFunction(glNewList));
	frame.Assign(Gurax_CreateFunction(glNormal3b));
	frame.Assign(Gurax_CreateFunction(glNormal3bv));
	frame.Assign(Gurax_CreateFunction(glNormal3d));
	frame.Assign(Gurax_CreateFunction(glNormal3dv));
	frame.Assign(Gurax_CreateFunction(glNormal3f));
	frame.Assign(Gurax_CreateFunction(glNormal3fv));
	frame.Assign(Gurax_CreateFunction(glNormal3i));
	frame.Assign(Gurax_CreateFunction(glNormal3iv));
	frame.Assign(Gurax_CreateFunction(glNormal3s));
	frame.Assign(Gurax_CreateFunction(glNormal3sv));
	frame.Assign(Gurax_CreateFunction(glOrtho));
	frame.Assign(Gurax_CreateFunction(glPassThrough));
	frame.Assign(Gurax_CreateFunction(glPixelMapfv));
	frame.Assign(Gurax_CreateFunction(glPixelMapuiv));
	frame.Assign(Gurax_CreateFunction(glPixelMapusv));
	frame.Assign(Gurax_CreateFunction(glPixelStoref));
	frame.Assign(Gurax_CreateFunction(glPixelStorei));
	frame.Assign(Gurax_CreateFunction(glPixelTransferf));
	frame.Assign(Gurax_CreateFunction(glPixelTransferi));
	frame.Assign(Gurax_CreateFunction(glPixelZoom));
	frame.Assign(Gurax_CreateFunction(glPointSize));
	frame.Assign(Gurax_CreateFunction(glPolygonMode));
	frame.Assign(Gurax_CreateFunction(glPolygonOffset));
	frame.Assign(Gurax_CreateFunction(glPolygonStipple));
	frame.Assign(Gurax_CreateFunction(glPopAttrib));
	frame.Assign(Gurax_CreateFunction(glPopClientAttrib));
	frame.Assign(Gurax_CreateFunction(glPopMatrix));
	frame.Assign(Gurax_CreateFunction(glPopName));
	frame.Assign(Gurax_CreateFunction(glPrioritizeTextures));
	frame.Assign(Gurax_CreateFunction(glPushAttrib));
	frame.Assign(Gurax_CreateFunction(glPushClientAttrib));
	frame.Assign(Gurax_CreateFunction(glPushMatrix));
	frame.Assign(Gurax_CreateFunction(glPushName));
	frame.Assign(Gurax_CreateFunction(glRasterPos2d));
	frame.Assign(Gurax_CreateFunction(glRasterPos2dv));
	frame.Assign(Gurax_CreateFunction(glRasterPos2f));
	frame.Assign(Gurax_CreateFunction(glRasterPos2fv));
	frame.Assign(Gurax_CreateFunction(glRasterPos2i));
	frame.Assign(Gurax_CreateFunction(glRasterPos2iv));
	frame.Assign(Gurax_CreateFunction(glRasterPos2s));
	frame.Assign(Gurax_CreateFunction(glRasterPos2sv));
	frame.Assign(Gurax_CreateFunction(glRasterPos3d));
	frame.Assign(Gurax_CreateFunction(glRasterPos3dv));
	frame.Assign(Gurax_CreateFunction(glRasterPos3f));
	frame.Assign(Gurax_CreateFunction(glRasterPos3fv));
	frame.Assign(Gurax_CreateFunction(glRasterPos3i));
	frame.Assign(Gurax_CreateFunction(glRasterPos3iv));
	frame.Assign(Gurax_CreateFunction(glRasterPos3s));
	frame.Assign(Gurax_CreateFunction(glRasterPos3sv));
	frame.Assign(Gurax_CreateFunction(glRasterPos4d));
	frame.Assign(Gurax_CreateFunction(glRasterPos4dv));
	frame.Assign(Gurax_CreateFunction(glRasterPos4f));
	frame.Assign(Gurax_CreateFunction(glRasterPos4fv));
	frame.Assign(Gurax_CreateFunction(glRasterPos4i));
	frame.Assign(Gurax_CreateFunction(glRasterPos4iv));
	frame.Assign(Gurax_CreateFunction(glRasterPos4s));
	frame.Assign(Gurax_CreateFunction(glRasterPos4sv));
	frame.Assign(Gurax_CreateFunction(glReadBuffer));
	frame.Assign(Gurax_CreateFunction(glRectd));
	frame.Assign(Gurax_CreateFunction(glRectdv));
	frame.Assign(Gurax_CreateFunction(glRectf));
	frame.Assign(Gurax_CreateFunction(glRectfv));
	frame.Assign(Gurax_CreateFunction(glRecti));
	frame.Assign(Gurax_CreateFunction(glRectiv));
	frame.Assign(Gurax_CreateFunction(glRects));
	frame.Assign(Gurax_CreateFunction(glRectsv));
	frame.Assign(Gurax_CreateFunction(glRenderMode));
	frame.Assign(Gurax_CreateFunction(glRotated));
	frame.Assign(Gurax_CreateFunction(glRotatef));
	frame.Assign(Gurax_CreateFunction(glScaled));
	frame.Assign(Gurax_CreateFunction(glScalef));
	frame.Assign(Gurax_CreateFunction(glScissor));
	frame.Assign(Gurax_CreateFunction(glShadeModel));
	frame.Assign(Gurax_CreateFunction(glStencilFunc));
	frame.Assign(Gurax_CreateFunction(glStencilMask));
	frame.Assign(Gurax_CreateFunction(glStencilOp));
	frame.Assign(Gurax_CreateFunction(glTexCoord1d));
	frame.Assign(Gurax_CreateFunction(glTexCoord1dv));
	frame.Assign(Gurax_CreateFunction(glTexCoord1f));
	frame.Assign(Gurax_CreateFunction(glTexCoord1fv));
	frame.Assign(Gurax_CreateFunction(glTexCoord1i));
	frame.Assign(Gurax_CreateFunction(glTexCoord1iv));
	frame.Assign(Gurax_CreateFunction(glTexCoord1s));
	frame.Assign(Gurax_CreateFunction(glTexCoord1sv));
	frame.Assign(Gurax_CreateFunction(glTexCoord2d));
	frame.Assign(Gurax_CreateFunction(glTexCoord2dv));
	frame.Assign(Gurax_CreateFunction(glTexCoord2f));
	frame.Assign(Gurax_CreateFunction(glTexCoord2fv));
	frame.Assign(Gurax_CreateFunction(glTexCoord2i));
	frame.Assign(Gurax_CreateFunction(glTexCoord2iv));
	frame.Assign(Gurax_CreateFunction(glTexCoord2s));
	frame.Assign(Gurax_CreateFunction(glTexCoord2sv));
	frame.Assign(Gurax_CreateFunction(glTexCoord3d));
	frame.Assign(Gurax_CreateFunction(glTexCoord3dv));
	frame.Assign(Gurax_CreateFunction(glTexCoord3f));
	frame.Assign(Gurax_CreateFunction(glTexCoord3fv));
	frame.Assign(Gurax_CreateFunction(glTexCoord3i));
	frame.Assign(Gurax_CreateFunction(glTexCoord3iv));
	frame.Assign(Gurax_CreateFunction(glTexCoord3s));
	frame.Assign(Gurax_CreateFunction(glTexCoord3sv));
	frame.Assign(Gurax_CreateFunction(glTexCoord4d));
	frame.Assign(Gurax_CreateFunction(glTexCoord4dv));
	frame.Assign(Gurax_CreateFunction(glTexCoord4f));
	frame.Assign(Gurax_CreateFunction(glTexCoord4fv));
	frame.Assign(Gurax_CreateFunction(glTexCoord4i));
	frame.Assign(Gurax_CreateFunction(glTexCoord4iv));
	frame.Assign(Gurax_CreateFunction(glTexCoord4s));
	frame.Assign(Gurax_CreateFunction(glTexCoord4sv));
	frame.Assign(Gurax_CreateFunction(glTexEnvf));
	frame.Assign(Gurax_CreateFunction(glTexEnvfv));
	frame.Assign(Gurax_CreateFunction(glTexEnvi));
	frame.Assign(Gurax_CreateFunction(glTexEnviv));
	frame.Assign(Gurax_CreateFunction(glTexGend));
	frame.Assign(Gurax_CreateFunction(glTexGendv));
	frame.Assign(Gurax_CreateFunction(glTexGenf));
	frame.Assign(Gurax_CreateFunction(glTexGenfv));
	frame.Assign(Gurax_CreateFunction(glTexGeni));
	frame.Assign(Gurax_CreateFunction(glTexGeniv));
	frame.Assign(Gurax_CreateFunction(glTexParameterf));
	frame.Assign(Gurax_CreateFunction(glTexParameterfv));
	frame.Assign(Gurax_CreateFunction(glTexParameteri));
	frame.Assign(Gurax_CreateFunction(glTexParameteriv));
	frame.Assign(Gurax_CreateFunction(glTranslated));
	frame.Assign(Gurax_CreateFunction(glTranslatef));
	frame.Assign(Gurax_CreateFunction(glVertex2d));
	frame.Assign(Gurax_CreateFunction(glVertex2dv));
	frame.Assign(Gurax_CreateFunction(glVertex2f));
	frame.Assign(Gurax_CreateFunction(glVertex2fv));
	frame.Assign(Gurax_CreateFunction(glVertex2i));
	frame.Assign(Gurax_CreateFunction(glVertex2iv));
	frame.Assign(Gurax_CreateFunction(glVertex2s));
	frame.Assign(Gurax_CreateFunction(glVertex2sv));
	frame.Assign(Gurax_CreateFunction(glVertex3d));
	frame.Assign(Gurax_CreateFunction(glVertex3dv));
	frame.Assign(Gurax_CreateFunction(glVertex3f));
	frame.Assign(Gurax_CreateFunction(glVertex3fv));
	frame.Assign(Gurax_CreateFunction(glVertex3i));
	frame.Assign(Gurax_CreateFunction(glVertex3iv));
	frame.Assign(Gurax_CreateFunction(glVertex3s));
	frame.Assign(Gurax_CreateFunction(glVertex3sv));
	frame.Assign(Gurax_CreateFunction(glVertex4d));
	frame.Assign(Gurax_CreateFunction(glVertex4dv));
	frame.Assign(Gurax_CreateFunction(glVertex4f));
	frame.Assign(Gurax_CreateFunction(glVertex4fv));
	frame.Assign(Gurax_CreateFunction(glVertex4i));
	frame.Assign(Gurax_CreateFunction(glVertex4iv));
	frame.Assign(Gurax_CreateFunction(glVertex4s));
	frame.Assign(Gurax_CreateFunction(glVertex4sv));
	frame.Assign(Gurax_CreateFunction(glViewport));
}

Gurax_EndModuleScope(opengl)
