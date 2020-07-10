//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(opengl)

// opengl.glewInit()
Gurax_DeclareFunctionAlias(gurax_glewInit, "glewInit")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glewInit)
{
	// Function body
	GLenum rtn = glewInit();
	return new Value_Number(rtn);
}

// opengl.glewIsSupported(name:String)
Gurax_DeclareFunctionAlias(gurax_glewIsSupported, "glewIsSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glewIsSupported)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	GLboolean rtn = glewIsSupported(name);
	return new Value_Bool(!!rtn);
}

// opengl.glewGetExtension(name:String)
Gurax_DeclareFunctionAlias(gurax_glewGetExtension, "glewGetExtension")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glewGetExtension)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	GLboolean rtn = glewGetExtension(name);
	return new Value_Bool(!!rtn);
}

// opengl.glewGetErrorString(error:Number)
Gurax_DeclareFunctionAlias(gurax_glewGetErrorString, "glewGetErrorString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("error", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glewGetErrorString)
{
	// Arguments
	ArgPicker args(argument);
	GLenum error = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetErrorString(error);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glewGetString(name:Number)
Gurax_DeclareFunctionAlias(gurax_glewGetString, "glewGetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glewGetString)
{
	// Arguments
	ArgPicker args(argument);
	GLenum name = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetString(name);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glAccum(op:Number, value:Number)
Gurax_DeclareFunctionAlias(gurax_glAccum, "glAccum")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("op", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glAccum)
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
Gurax_DeclareFunctionAlias(gurax_glAlphaFunc, "glAlphaFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glAlphaFunc)
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
Gurax_DeclareFunctionAlias(gurax_glArrayElement, "glArrayElement")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glArrayElement)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	// Function body
	glArrayElement(i);
	return Value::nil();
}

// opengl.glBegin(mode:Number)
Gurax_DeclareFunctionAlias(gurax_glBegin, "glBegin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glBegin)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glBegin(mode);
	return Value::nil();
}

// opengl.glBindTexture(target:Number, texture:Number)
Gurax_DeclareFunctionAlias(gurax_glBindTexture, "glBindTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glBindTexture)
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
Gurax_DeclareFunctionAlias(gurax_glBlendFunc, "glBlendFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glBlendFunc)
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
Gurax_DeclareFunctionAlias(gurax_glCallList, "glCallList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glCallList)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	// Function body
	glCallList(list);
	return Value::nil();
}

// opengl.glClear(mask:Number)
Gurax_DeclareFunctionAlias(gurax_glClear, "glClear")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glClear)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glClear(mask);
	return Value::nil();
}

// opengl.glClearAccum(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glClearAccum, "glClearAccum")
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

Gurax_ImplementFunction(gurax_glClearAccum)
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
Gurax_DeclareFunctionAlias(gurax_glClearColor, "glClearColor")
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

Gurax_ImplementFunction(gurax_glClearColor)
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
Gurax_DeclareFunctionAlias(gurax_glClearDepth, "glClearDepth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glClearDepth)
{
	// Arguments
	ArgPicker args(argument);
	GLclampd depth = args.PickNumber<GLclampd>();
	// Function body
	glClearDepth(depth);
	return Value::nil();
}

// opengl.glClearIndex(c:Number)
Gurax_DeclareFunctionAlias(gurax_glClearIndex, "glClearIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glClearIndex)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat c = args.PickNumber<GLfloat>();
	// Function body
	glClearIndex(c);
	return Value::nil();
}

// opengl.glClearStencil(s:Number)
Gurax_DeclareFunctionAlias(gurax_glClearStencil, "glClearStencil")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glClearStencil)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	// Function body
	glClearStencil(s);
	return Value::nil();
}

// opengl.glClipPlane(plane:Number, equation[]:Number)
Gurax_DeclareFunctionAlias(gurax_glClipPlane, "glClipPlane")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("plane", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("equation", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glClipPlane)
{
	// Arguments
	ArgPicker args(argument);
	GLenum plane = args.PickNumber<GLenum>();
	auto equation = args.PickNumList<GLdouble>();
	// Function body
	glClipPlane(plane, equation);
	return Value::nil();
}

// opengl.glColor3b(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3b, "glColor3b")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3b)
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
Gurax_DeclareFunctionAlias(gurax_glColor3bv, "glColor3bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3bv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glColor3bv(v);
	return Value::nil();
}

// opengl.glColor3d(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3d, "glColor3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3d)
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
Gurax_DeclareFunctionAlias(gurax_glColor3dv, "glColor3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glColor3dv(v);
	return Value::nil();
}

// opengl.glColor3f(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3f, "glColor3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3f)
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
Gurax_DeclareFunctionAlias(gurax_glColor3fv, "glColor3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glColor3fv(v);
	return Value::nil();
}

// opengl.glColor3i(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3i, "glColor3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3i)
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
Gurax_DeclareFunctionAlias(gurax_glColor3iv, "glColor3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glColor3iv(v);
	return Value::nil();
}

// opengl.glColor3s(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3s, "glColor3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3s)
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
Gurax_DeclareFunctionAlias(gurax_glColor3sv, "glColor3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glColor3sv(v);
	return Value::nil();
}

// opengl.glColor3ub(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3ub, "glColor3ub")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3ub)
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
Gurax_DeclareFunctionAlias(gurax_glColor3ubv, "glColor3ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3ubv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glColor3ubv(v);
	return Value::nil();
}

// opengl.glColor3ui(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3ui, "glColor3ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3ui)
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
Gurax_DeclareFunctionAlias(gurax_glColor3uiv, "glColor3uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3uiv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glColor3uiv(v);
	return Value::nil();
}

// opengl.glColor3us(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(gurax_glColor3us, "glColor3us")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3us)
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
Gurax_DeclareFunctionAlias(gurax_glColor3usv, "glColor3usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor3usv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glColor3usv(v);
	return Value::nil();
}

// opengl.glColor4b(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4b, "glColor4b")
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

Gurax_ImplementFunction(gurax_glColor4b)
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
Gurax_DeclareFunctionAlias(gurax_glColor4bv, "glColor4bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4bv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glColor4bv(v);
	return Value::nil();
}

// opengl.glColor4d(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4d, "glColor4d")
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

Gurax_ImplementFunction(gurax_glColor4d)
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
Gurax_DeclareFunctionAlias(gurax_glColor4dv, "glColor4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glColor4dv(v);
	return Value::nil();
}

// opengl.glColor4f(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4f, "glColor4f")
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

Gurax_ImplementFunction(gurax_glColor4f)
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
Gurax_DeclareFunctionAlias(gurax_glColor4fv, "glColor4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glColor4fv(v);
	return Value::nil();
}

// opengl.glColor4i(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4i, "glColor4i")
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

Gurax_ImplementFunction(gurax_glColor4i)
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
Gurax_DeclareFunctionAlias(gurax_glColor4iv, "glColor4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glColor4iv(v);
	return Value::nil();
}

// opengl.glColor4s(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4s, "glColor4s")
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

Gurax_ImplementFunction(gurax_glColor4s)
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
Gurax_DeclareFunctionAlias(gurax_glColor4sv, "glColor4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glColor4sv(v);
	return Value::nil();
}

// opengl.glColor4ub(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4ub, "glColor4ub")
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

Gurax_ImplementFunction(gurax_glColor4ub)
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
Gurax_DeclareFunctionAlias(gurax_glColor4ubv, "glColor4ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4ubv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glColor4ubv(v);
	return Value::nil();
}

// opengl.glColor4ui(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4ui, "glColor4ui")
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

Gurax_ImplementFunction(gurax_glColor4ui)
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
Gurax_DeclareFunctionAlias(gurax_glColor4uiv, "glColor4uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4uiv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glColor4uiv(v);
	return Value::nil();
}

// opengl.glColor4us(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(gurax_glColor4us, "glColor4us")
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

Gurax_ImplementFunction(gurax_glColor4us)
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
Gurax_DeclareFunctionAlias(gurax_glColor4usv, "glColor4usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColor4usv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glColor4usv(v);
	return Value::nil();
}

// opengl.glColorMask(red:Bool, green:Bool, blue:Bool, alpha:Bool)
Gurax_DeclareFunctionAlias(gurax_glColorMask, "glColorMask")
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

Gurax_ImplementFunction(gurax_glColorMask)
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
Gurax_DeclareFunctionAlias(gurax_glColorMaterial, "glColorMaterial")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glColorMaterial)
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
Gurax_DeclareFunctionAlias(gurax_glCopyPixels, "glCopyPixels")
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

Gurax_ImplementFunction(gurax_glCopyPixels)
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
Gurax_DeclareFunctionAlias(gurax_glCopyTexImage1D, "glCopyTexImage1D")
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

Gurax_ImplementFunction(gurax_glCopyTexImage1D)
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
Gurax_DeclareFunctionAlias(gurax_glCopyTexImage2D, "glCopyTexImage2D")
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

Gurax_ImplementFunction(gurax_glCopyTexImage2D)
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
Gurax_DeclareFunctionAlias(gurax_glCopyTexSubImage1D, "glCopyTexSubImage1D")
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

Gurax_ImplementFunction(gurax_glCopyTexSubImage1D)
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
Gurax_DeclareFunctionAlias(gurax_glCopyTexSubImage2D, "glCopyTexSubImage2D")
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

Gurax_ImplementFunction(gurax_glCopyTexSubImage2D)
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
Gurax_DeclareFunctionAlias(gurax_glCullFace, "glCullFace")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glCullFace)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glCullFace(mode);
	return Value::nil();
}

// opengl.glDeleteLists(list:Number, range:Number)
Gurax_DeclareFunctionAlias(gurax_glDeleteLists, "glDeleteLists")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDeleteLists)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	GLsizei range = args.PickNumber<GLsizei>();
	// Function body
	glDeleteLists(list, range);
	return Value::nil();
}

// opengl.glDeleteTextures(textures[]:Number)
Gurax_DeclareFunctionAlias(gurax_glDeleteTextures, "glDeleteTextures")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("textures", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDeleteTextures)
{
	// Arguments
	ArgPicker args(argument);
	auto textures = args.PickNumList<GLuint>();
	// Function body
	glDeleteTextures(textures.sizeT<GLsizei>(), textures);
	return Value::nil();
}

// opengl.glDepthFunc(func:Number)
Gurax_DeclareFunctionAlias(gurax_glDepthFunc, "glDepthFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDepthFunc)
{
	// Arguments
	ArgPicker args(argument);
	GLenum func = args.PickNumber<GLenum>();
	// Function body
	glDepthFunc(func);
	return Value::nil();
}

// opengl.glDepthMask(flag:Bool)
Gurax_DeclareFunctionAlias(gurax_glDepthMask, "glDepthMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDepthMask)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean flag = static_cast<GLboolean>(args.PickBool());
	// Function body
	glDepthMask(flag);
	return Value::nil();
}

// opengl.glDepthRange(zNear:Number, zFar:Number)
Gurax_DeclareFunctionAlias(gurax_glDepthRange, "glDepthRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("zNear", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zFar", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDepthRange)
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
Gurax_DeclareFunctionAlias(gurax_glDisable, "glDisable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDisable)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	glDisable(cap);
	return Value::nil();
}

// opengl.glDisableClientState(array:Number)
Gurax_DeclareFunctionAlias(gurax_glDisableClientState, "glDisableClientState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDisableClientState)
{
	// Arguments
	ArgPicker args(argument);
	GLenum array = args.PickNumber<GLenum>();
	// Function body
	glDisableClientState(array);
	return Value::nil();
}

// opengl.glDrawArrays(mode:Number, first:Number, count:Number)
Gurax_DeclareFunctionAlias(gurax_glDrawArrays, "glDrawArrays")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDrawArrays)
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
Gurax_DeclareFunctionAlias(gurax_glDrawBuffer, "glDrawBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glDrawBuffer)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glDrawBuffer(mode);
	return Value::nil();
}

// opengl.glEdgeFlag(flag:Bool)
Gurax_DeclareFunctionAlias(gurax_glEdgeFlag, "glEdgeFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEdgeFlag)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean flag = static_cast<GLboolean>(args.PickBool());
	// Function body
	glEdgeFlag(flag);
	return Value::nil();
}

// opengl.glEdgeFlagv(flag[]:Bool)
Gurax_DeclareFunctionAlias(gurax_glEdgeFlagv, "glEdgeFlagv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEdgeFlagv)
{
	// Arguments
	ArgPicker args(argument);
	auto flag = args.PickListT<GLboolean>([](Value& value) { return value.GetBool()? GL_TRUE : GL_FALSE; });
	// Function body
	glEdgeFlagv(flag);
	return Value::nil();
}

// opengl.glEnable(cap:Number)
Gurax_DeclareFunctionAlias(gurax_glEnable, "glEnable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEnable)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	glEnable(cap);
	return Value::nil();
}

// opengl.glEnableClientState(array:Number)
Gurax_DeclareFunctionAlias(gurax_glEnableClientState, "glEnableClientState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEnableClientState)
{
	// Arguments
	ArgPicker args(argument);
	GLenum array = args.PickNumber<GLenum>();
	// Function body
	glEnableClientState(array);
	return Value::nil();
}

// opengl.glEnd()
Gurax_DeclareFunctionAlias(gurax_glEnd, "glEnd")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEnd)
{
	// Function body
	glEnd();
	return Value::nil();
}

// opengl.glEndList()
Gurax_DeclareFunctionAlias(gurax_glEndList, "glEndList")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEndList)
{
	// Function body
	glEndList();
	return Value::nil();
}

// opengl.glEvalCoord1d(u:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalCoord1d, "glEvalCoord1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord1d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble u = args.PickNumber<GLdouble>();
	// Function body
	glEvalCoord1d(u);
	return Value::nil();
}

// opengl.glEvalCoord1dv(u[]:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalCoord1dv, "glEvalCoord1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord1dv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLdouble>();
	// Function body
	glEvalCoord1dv(u);
	return Value::nil();
}

// opengl.glEvalCoord1f(u:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalCoord1f, "glEvalCoord1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord1f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat u = args.PickNumber<GLfloat>();
	// Function body
	glEvalCoord1f(u);
	return Value::nil();
}

// opengl.glEvalCoord1fv(u[]:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalCoord1fv, "glEvalCoord1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord1fv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLfloat>();
	// Function body
	glEvalCoord1fv(u);
	return Value::nil();
}

// opengl.glEvalCoord2d(u:Number, v:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalCoord2d, "glEvalCoord2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord2d)
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
Gurax_DeclareFunctionAlias(gurax_glEvalCoord2dv, "glEvalCoord2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLdouble>();
	// Function body
	glEvalCoord2dv(u);
	return Value::nil();
}

// opengl.glEvalCoord2f(u:Number, v:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalCoord2f, "glEvalCoord2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord2f)
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
Gurax_DeclareFunctionAlias(gurax_glEvalCoord2fv, "glEvalCoord2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalCoord2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLfloat>();
	// Function body
	glEvalCoord2fv(u);
	return Value::nil();
}

// opengl.glEvalMesh1(mode:Number, i1:Number, i2:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalMesh1, "glEvalMesh1")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalMesh1)
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
Gurax_DeclareFunctionAlias(gurax_glEvalMesh2, "glEvalMesh2")
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

Gurax_ImplementFunction(gurax_glEvalMesh2)
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
Gurax_DeclareFunctionAlias(gurax_glEvalPoint1, "glEvalPoint1")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalPoint1)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	// Function body
	glEvalPoint1(i);
	return Value::nil();
}

// opengl.glEvalPoint2(i:Number, j:Number)
Gurax_DeclareFunctionAlias(gurax_glEvalPoint2, "glEvalPoint2")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("j", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glEvalPoint2)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	GLint j = args.PickNumber<GLint>();
	// Function body
	glEvalPoint2(i, j);
	return Value::nil();
}

// opengl.glFeedbackBuffer(size:Number, type:Number)
Gurax_DeclareFunctionAlias(gurax_glFeedbackBuffer, "glFeedbackBuffer")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFeedbackBuffer)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei size = args.PickNumber<GLsizei>();
	GLenum type = args.PickNumber<GLenum>();
	// Function body
	std::unique_ptr<GLfloat []> buffer(new GLfloat [size]);
	glFeedbackBuffer(size, type, buffer.get());
	return Value_List::Create(buffer.get(), size);
}

// opengl.glFinish()
Gurax_DeclareFunctionAlias(gurax_glFinish, "glFinish")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFinish)
{
	// Function body
	glFinish();
	return Value::nil();
}

// opengl.glFlush()
Gurax_DeclareFunctionAlias(gurax_glFlush, "glFlush")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFlush)
{
	// Function body
	glFlush();
	return Value::nil();
}

// opengl.glFogf(pname:Number, param:Number)
Gurax_DeclareFunctionAlias(gurax_glFogf, "glFogf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFogf)
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
Gurax_DeclareFunctionAlias(gurax_glFogfv, "glFogfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFogfv)
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
Gurax_DeclareFunctionAlias(gurax_glFogi, "glFogi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFogi)
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
Gurax_DeclareFunctionAlias(gurax_glFogiv, "glFogiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFogiv)
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
Gurax_DeclareFunctionAlias(gurax_glFrontFace, "glFrontFace")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glFrontFace)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glFrontFace(mode);
	return Value::nil();
}

// opengl.glFrustum(left:Number, right:Number, bottom:Number, top:Number, zNear:Number, zFar:Number)
Gurax_DeclareFunctionAlias(gurax_glFrustum, "glFrustum")
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

Gurax_ImplementFunction(gurax_glFrustum)
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
Gurax_DeclareFunctionAlias(gurax_glGenLists, "glGenLists")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glGenLists)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei range = args.PickNumber<GLsizei>();
	// Function body
	GLuint rtn = glGenLists(range);
	return new Value_Number(rtn);
}

// opengl.glGenTextures(n:Number)
Gurax_DeclareFunctionAlias(gurax_glGenTextures, "glGenTextures")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glGenTextures)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	// Function body
	std::unique_ptr<GLuint []> textures(new GLuint [n]);
	glGenTextures(n, textures.get());
	return Value_List::Create(textures.get(), n);
}

// opengl.glGetError()
Gurax_DeclareFunctionAlias(gurax_glGetError, "glGetError")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glGetError)
{
	// Function body
	GLenum rtn = glGetError();
	return new Value_Number(rtn);
}

// opengl.glGetString(name:Number)
Gurax_DeclareFunctionAlias(gurax_glGetString, "glGetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glGetString)
{
	// Arguments
	ArgPicker args(argument);
	GLenum name = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glGetString(name);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glHint(target:Number, mode:Number)
Gurax_DeclareFunctionAlias(gurax_glHint, "glHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glHint)
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
Gurax_DeclareFunctionAlias(gurax_glIndexMask, "glIndexMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexMask)
{
	// Arguments
	ArgPicker args(argument);
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glIndexMask(mask);
	return Value::nil();
}

// opengl.glIndexd(c:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexd, "glIndexd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexd)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble c = args.PickNumber<GLdouble>();
	// Function body
	glIndexd(c);
	return Value::nil();
}

// opengl.glIndexdv(c[]:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexdv, "glIndexdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexdv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLdouble>();
	// Function body
	glIndexdv(c);
	return Value::nil();
}

// opengl.glIndexf(c:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexf, "glIndexf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexf)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat c = args.PickNumber<GLfloat>();
	// Function body
	glIndexf(c);
	return Value::nil();
}

// opengl.glIndexfv(c[]:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexfv, "glIndexfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexfv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLfloat>();
	// Function body
	glIndexfv(c);
	return Value::nil();
}

// opengl.glIndexi(c:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexi, "glIndexi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexi)
{
	// Arguments
	ArgPicker args(argument);
	GLint c = args.PickNumber<GLint>();
	// Function body
	glIndexi(c);
	return Value::nil();
}

// opengl.glIndexiv(c[]:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexiv, "glIndexiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexiv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLint>();
	// Function body
	glIndexiv(c);
	return Value::nil();
}

// opengl.glIndexs(c:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexs, "glIndexs")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexs)
{
	// Arguments
	ArgPicker args(argument);
	GLshort c = args.PickNumber<GLshort>();
	// Function body
	glIndexs(c);
	return Value::nil();
}

// opengl.glIndexsv(c[]:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexsv, "glIndexsv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexsv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLshort>();
	// Function body
	glIndexsv(c);
	return Value::nil();
}

// opengl.glIndexub(c:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexub, "glIndexub")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexub)
{
	// Arguments
	ArgPicker args(argument);
	GLubyte c = args.PickNumber<GLubyte>();
	// Function body
	glIndexub(c);
	return Value::nil();
}

// opengl.glIndexubv(c[]:Number)
Gurax_DeclareFunctionAlias(gurax_glIndexubv, "glIndexubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIndexubv)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLubyte>();
	// Function body
	glIndexubv(c);
	return Value::nil();
}

// opengl.glInitNames()
Gurax_DeclareFunctionAlias(gurax_glInitNames, "glInitNames")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glInitNames)
{
	// Function body
	glInitNames();
	return Value::nil();
}

// opengl.glIsEnabled(cap:Number)
Gurax_DeclareFunctionAlias(gurax_glIsEnabled, "glIsEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIsEnabled)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	GLboolean rtn = glIsEnabled(cap);
	return new Value_Bool(!!rtn);
}

// opengl.glIsList(list:Number)
Gurax_DeclareFunctionAlias(gurax_glIsList, "glIsList")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIsList)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsList(list);
	return new Value_Bool(!!rtn);
}

// opengl.glIsTexture(texture:Number)
Gurax_DeclareFunctionAlias(gurax_glIsTexture, "glIsTexture")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glIsTexture)
{
	// Arguments
	ArgPicker args(argument);
	GLuint texture = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsTexture(texture);
	return new Value_Bool(!!rtn);
}

// opengl.glLightModelf(pname:Number, param:Number)
Gurax_DeclareFunctionAlias(gurax_glLightModelf, "glLightModelf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightModelf)
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
Gurax_DeclareFunctionAlias(gurax_glLightModelfv, "glLightModelfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightModelfv)
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
Gurax_DeclareFunctionAlias(gurax_glLightModeli, "glLightModeli")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightModeli)
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
Gurax_DeclareFunctionAlias(gurax_glLightModeliv, "glLightModeliv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightModeliv)
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
Gurax_DeclareFunctionAlias(gurax_glLightf, "glLightf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightf)
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
Gurax_DeclareFunctionAlias(gurax_glLightfv, "glLightfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightfv)
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
Gurax_DeclareFunctionAlias(gurax_glLighti, "glLighti")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLighti)
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
Gurax_DeclareFunctionAlias(gurax_glLightiv, "glLightiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLightiv)
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
Gurax_DeclareFunctionAlias(gurax_glLineStipple, "glLineStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pattern", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLineStipple)
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
Gurax_DeclareFunctionAlias(gurax_glLineWidth, "glLineWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLineWidth)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat width = args.PickNumber<GLfloat>();
	// Function body
	glLineWidth(width);
	return Value::nil();
}

// opengl.glListBase(base:Number)
Gurax_DeclareFunctionAlias(gurax_glListBase, "glListBase")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glListBase)
{
	// Arguments
	ArgPicker args(argument);
	GLuint base = args.PickNumber<GLuint>();
	// Function body
	glListBase(base);
	return Value::nil();
}

// opengl.glLoadIdentity()
Gurax_DeclareFunctionAlias(gurax_glLoadIdentity, "glLoadIdentity")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLoadIdentity)
{
	// Function body
	glLoadIdentity();
	return Value::nil();
}

// opengl.glLoadMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glLoadMatrixd, "glLoadMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLoadMatrixd)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glLoadMatrixd(m);
	return Value::nil();
}

// opengl.glLoadMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glLoadMatrixf, "glLoadMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLoadMatrixf)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glLoadMatrixf(m);
	return Value::nil();
}

// opengl.glLoadName(name:Number)
Gurax_DeclareFunctionAlias(gurax_glLoadName, "glLoadName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLoadName)
{
	// Arguments
	ArgPicker args(argument);
	GLuint name = args.PickNumber<GLuint>();
	// Function body
	glLoadName(name);
	return Value::nil();
}

// opengl.glLogicOp(opcode:Number)
Gurax_DeclareFunctionAlias(gurax_glLogicOp, "glLogicOp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("opcode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLogicOp)
{
	// Arguments
	ArgPicker args(argument);
	GLenum opcode = args.PickNumber<GLenum>();
	// Function body
	glLogicOp(opcode);
	return Value::nil();
}

// opengl.glMap1d(target:Number, u1:Number, u2:Number, stride:Number, order:Number, points[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMap1d, "glMap1d")
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

Gurax_ImplementFunction(gurax_glMap1d)
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
Gurax_DeclareFunctionAlias(gurax_glMap1f, "glMap1f")
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

Gurax_ImplementFunction(gurax_glMap1f)
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
Gurax_DeclareFunctionAlias(gurax_glMap2d, "glMap2d")
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

Gurax_ImplementFunction(gurax_glMap2d)
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
Gurax_DeclareFunctionAlias(gurax_glMap2f, "glMap2f")
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

Gurax_ImplementFunction(gurax_glMap2f)
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
Gurax_DeclareFunctionAlias(gurax_glMapGrid1d, "glMapGrid1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMapGrid1d)
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
Gurax_DeclareFunctionAlias(gurax_glMapGrid1f, "glMapGrid1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMapGrid1f)
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
Gurax_DeclareFunctionAlias(gurax_glMapGrid2d, "glMapGrid2d")
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

Gurax_ImplementFunction(gurax_glMapGrid2d)
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
Gurax_DeclareFunctionAlias(gurax_glMapGrid2f, "glMapGrid2f")
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

Gurax_ImplementFunction(gurax_glMapGrid2f)
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
Gurax_DeclareFunctionAlias(gurax_glMaterialf, "glMaterialf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMaterialf)
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
Gurax_DeclareFunctionAlias(gurax_glMaterialfv, "glMaterialfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMaterialfv)
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
Gurax_DeclareFunctionAlias(gurax_glMateriali, "glMateriali")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMateriali)
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
Gurax_DeclareFunctionAlias(gurax_glMaterialiv, "glMaterialiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMaterialiv)
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
Gurax_DeclareFunctionAlias(gurax_glMatrixMode, "glMatrixMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMatrixMode)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glMatrixMode(mode);
	return Value::nil();
}

// opengl.glMultMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultMatrixd, "glMultMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultMatrixd)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glMultMatrixd(m);
	return Value::nil();
}

// opengl.glMultMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultMatrixf, "glMultMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultMatrixf)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glMultMatrixf(m);
	return Value::nil();
}

// opengl.glNewList(list:Number, mode:Number)
Gurax_DeclareFunctionAlias(gurax_glNewList, "glNewList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNewList)
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
Gurax_DeclareFunctionAlias(gurax_glNormal3b, "glNormal3b")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3b)
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
Gurax_DeclareFunctionAlias(gurax_glNormal3bv, "glNormal3bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3bv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glNormal3bv(v);
	return Value::nil();
}

// opengl.glNormal3d(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(gurax_glNormal3d, "glNormal3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3d)
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
Gurax_DeclareFunctionAlias(gurax_glNormal3dv, "glNormal3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glNormal3dv(v);
	return Value::nil();
}

// opengl.glNormal3f(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(gurax_glNormal3f, "glNormal3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3f)
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
Gurax_DeclareFunctionAlias(gurax_glNormal3fv, "glNormal3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glNormal3fv(v);
	return Value::nil();
}

// opengl.glNormal3i(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(gurax_glNormal3i, "glNormal3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3i)
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
Gurax_DeclareFunctionAlias(gurax_glNormal3iv, "glNormal3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glNormal3iv(v);
	return Value::nil();
}

// opengl.glNormal3s(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(gurax_glNormal3s, "glNormal3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3s)
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
Gurax_DeclareFunctionAlias(gurax_glNormal3sv, "glNormal3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glNormal3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glNormal3sv(v);
	return Value::nil();
}

// opengl.glOrtho(left:Number, right:Number, bottom:Number, top:Number, zNear:Number, zFar:Number)
Gurax_DeclareFunctionAlias(gurax_glOrtho, "glOrtho")
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

Gurax_ImplementFunction(gurax_glOrtho)
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
Gurax_DeclareFunctionAlias(gurax_glPassThrough, "glPassThrough")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("token", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPassThrough)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat token = args.PickNumber<GLfloat>();
	// Function body
	glPassThrough(token);
	return Value::nil();
}

// opengl.glPixelMapfv(map:Number, mapsize:Number, values[]:Number)
Gurax_DeclareFunctionAlias(gurax_glPixelMapfv, "glPixelMapfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelMapfv)
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
Gurax_DeclareFunctionAlias(gurax_glPixelMapuiv, "glPixelMapuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelMapuiv)
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
Gurax_DeclareFunctionAlias(gurax_glPixelMapusv, "glPixelMapusv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelMapusv)
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
Gurax_DeclareFunctionAlias(gurax_glPixelStoref, "glPixelStoref")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelStoref)
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
Gurax_DeclareFunctionAlias(gurax_glPixelStorei, "glPixelStorei")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelStorei)
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
Gurax_DeclareFunctionAlias(gurax_glPixelTransferf, "glPixelTransferf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelTransferf)
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
Gurax_DeclareFunctionAlias(gurax_glPixelTransferi, "glPixelTransferi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelTransferi)
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
Gurax_DeclareFunctionAlias(gurax_glPixelZoom, "glPixelZoom")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPixelZoom)
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
Gurax_DeclareFunctionAlias(gurax_glPointSize, "glPointSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPointSize)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat size = args.PickNumber<GLfloat>();
	// Function body
	glPointSize(size);
	return Value::nil();
}

// opengl.glPolygonMode(face:Number, mode:Number)
Gurax_DeclareFunctionAlias(gurax_glPolygonMode, "glPolygonMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPolygonMode)
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
Gurax_DeclareFunctionAlias(gurax_glPolygonOffset, "glPolygonOffset")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("units", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPolygonOffset)
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
Gurax_DeclareFunctionAlias(gurax_glPolygonStipple, "glPolygonStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPolygonStipple)
{
	// Arguments
	ArgPicker args(argument);
	auto mask = args.PickNumList<GLubyte>();
	// Function body
	glPolygonStipple(mask);
	return Value::nil();
}

// opengl.glPopAttrib()
Gurax_DeclareFunctionAlias(gurax_glPopAttrib, "glPopAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPopAttrib)
{
	// Function body
	glPopAttrib();
	return Value::nil();
}

// opengl.glPopClientAttrib()
Gurax_DeclareFunctionAlias(gurax_glPopClientAttrib, "glPopClientAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPopClientAttrib)
{
	// Function body
	glPopClientAttrib();
	return Value::nil();
}

// opengl.glPopMatrix()
Gurax_DeclareFunctionAlias(gurax_glPopMatrix, "glPopMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPopMatrix)
{
	// Function body
	glPopMatrix();
	return Value::nil();
}

// opengl.glPopName()
Gurax_DeclareFunctionAlias(gurax_glPopName, "glPopName")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPopName)
{
	// Function body
	glPopName();
	return Value::nil();
}

// opengl.glPrioritizeTextures(n:Number, textures[]:Number, priorities[]:Number)
Gurax_DeclareFunctionAlias(gurax_glPrioritizeTextures, "glPrioritizeTextures")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textures", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("priorities", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPrioritizeTextures)
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
Gurax_DeclareFunctionAlias(gurax_glPushAttrib, "glPushAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPushAttrib)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glPushAttrib(mask);
	return Value::nil();
}

// opengl.glPushClientAttrib(mask:Number)
Gurax_DeclareFunctionAlias(gurax_glPushClientAttrib, "glPushClientAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPushClientAttrib)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glPushClientAttrib(mask);
	return Value::nil();
}

// opengl.glPushMatrix()
Gurax_DeclareFunctionAlias(gurax_glPushMatrix, "glPushMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPushMatrix)
{
	// Function body
	glPushMatrix();
	return Value::nil();
}

// opengl.glPushName(name:Number)
Gurax_DeclareFunctionAlias(gurax_glPushName, "glPushName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glPushName)
{
	// Arguments
	ArgPicker args(argument);
	GLuint name = args.PickNumber<GLuint>();
	// Function body
	glPushName(name);
	return Value::nil();
}

// opengl.glRasterPos2d(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos2d, "glRasterPos2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2d)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos2dv, "glRasterPos2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos2dv(v);
	return Value::nil();
}

// opengl.glRasterPos2f(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos2f, "glRasterPos2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2f)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos2fv, "glRasterPos2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos2fv(v);
	return Value::nil();
}

// opengl.glRasterPos2i(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos2i, "glRasterPos2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2i)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos2iv, "glRasterPos2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos2iv(v);
	return Value::nil();
}

// opengl.glRasterPos2s(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos2s, "glRasterPos2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2s)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos2sv, "glRasterPos2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos2sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos2sv(v);
	return Value::nil();
}

// opengl.glRasterPos3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos3d, "glRasterPos3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3d)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos3dv, "glRasterPos3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos3dv(v);
	return Value::nil();
}

// opengl.glRasterPos3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos3f, "glRasterPos3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3f)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos3fv, "glRasterPos3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos3fv(v);
	return Value::nil();
}

// opengl.glRasterPos3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos3i, "glRasterPos3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3i)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos3iv, "glRasterPos3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos3iv(v);
	return Value::nil();
}

// opengl.glRasterPos3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos3s, "glRasterPos3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3s)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos3sv, "glRasterPos3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos3sv(v);
	return Value::nil();
}

// opengl.glRasterPos4d(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos4d, "glRasterPos4d")
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

Gurax_ImplementFunction(gurax_glRasterPos4d)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos4dv, "glRasterPos4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos4dv(v);
	return Value::nil();
}

// opengl.glRasterPos4f(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos4f, "glRasterPos4f")
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

Gurax_ImplementFunction(gurax_glRasterPos4f)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos4fv, "glRasterPos4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos4fv(v);
	return Value::nil();
}

// opengl.glRasterPos4i(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos4i, "glRasterPos4i")
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

Gurax_ImplementFunction(gurax_glRasterPos4i)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos4iv, "glRasterPos4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos4iv(v);
	return Value::nil();
}

// opengl.glRasterPos4s(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glRasterPos4s, "glRasterPos4s")
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

Gurax_ImplementFunction(gurax_glRasterPos4s)
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
Gurax_DeclareFunctionAlias(gurax_glRasterPos4sv, "glRasterPos4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRasterPos4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos4sv(v);
	return Value::nil();
}

// opengl.glReadBuffer(mode:Number)
Gurax_DeclareFunctionAlias(gurax_glReadBuffer, "glReadBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glReadBuffer)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glReadBuffer(mode);
	return Value::nil();
}

// opengl.glRectd(x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunctionAlias(gurax_glRectd, "glRectd")
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

Gurax_ImplementFunction(gurax_glRectd)
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
Gurax_DeclareFunctionAlias(gurax_glRectdv, "glRectdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRectdv)
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
Gurax_DeclareFunctionAlias(gurax_glRectf, "glRectf")
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

Gurax_ImplementFunction(gurax_glRectf)
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
Gurax_DeclareFunctionAlias(gurax_glRectfv, "glRectfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRectfv)
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
Gurax_DeclareFunctionAlias(gurax_glRecti, "glRecti")
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

Gurax_ImplementFunction(gurax_glRecti)
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
Gurax_DeclareFunctionAlias(gurax_glRectiv, "glRectiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRectiv)
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
Gurax_DeclareFunctionAlias(gurax_glRects, "glRects")
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

Gurax_ImplementFunction(gurax_glRects)
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
Gurax_DeclareFunctionAlias(gurax_glRectsv, "glRectsv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRectsv)
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
Gurax_DeclareFunctionAlias(gurax_glRenderMode, "glRenderMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glRenderMode)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	GLint rtn = glRenderMode(mode);
	return new Value_Number(rtn);
}

// opengl.glRotated(angle:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glRotated, "glRotated")
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

Gurax_ImplementFunction(gurax_glRotated)
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
Gurax_DeclareFunctionAlias(gurax_glRotatef, "glRotatef")
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

Gurax_ImplementFunction(gurax_glRotatef)
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
Gurax_DeclareFunctionAlias(gurax_glScaled, "glScaled")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glScaled)
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
Gurax_DeclareFunctionAlias(gurax_glScalef, "glScalef")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glScalef)
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
Gurax_DeclareFunctionAlias(gurax_glScissor, "glScissor")
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

Gurax_ImplementFunction(gurax_glScissor)
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
Gurax_DeclareFunctionAlias(gurax_glShadeModel, "glShadeModel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glShadeModel)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glShadeModel(mode);
	return Value::nil();
}

// opengl.glStencilFunc(func:Number, ref:Number, mask:Number)
Gurax_DeclareFunctionAlias(gurax_glStencilFunc, "glStencilFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glStencilFunc)
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
Gurax_DeclareFunctionAlias(gurax_glStencilMask, "glStencilMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glStencilMask)
{
	// Arguments
	ArgPicker args(argument);
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glStencilMask(mask);
	return Value::nil();
}

// opengl.glStencilOp(fail:Number, zfail:Number, zpass:Number)
Gurax_DeclareFunctionAlias(gurax_glStencilOp, "glStencilOp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zfail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zpass", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glStencilOp)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord1d, "glTexCoord1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1d)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble s = args.PickNumber<GLdouble>();
	// Function body
	glTexCoord1d(s);
	return Value::nil();
}

// opengl.glTexCoord1dv(v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1dv, "glTexCoord1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord1dv(v);
	return Value::nil();
}

// opengl.glTexCoord1f(s:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1f, "glTexCoord1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1f)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat s = args.PickNumber<GLfloat>();
	// Function body
	glTexCoord1f(s);
	return Value::nil();
}

// opengl.glTexCoord1fv(v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1fv, "glTexCoord1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord1fv(v);
	return Value::nil();
}

// opengl.glTexCoord1i(s:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1i, "glTexCoord1i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1i)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	// Function body
	glTexCoord1i(s);
	return Value::nil();
}

// opengl.glTexCoord1iv(v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1iv, "glTexCoord1iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord1iv(v);
	return Value::nil();
}

// opengl.glTexCoord1s(s:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1s, "glTexCoord1s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1s)
{
	// Arguments
	ArgPicker args(argument);
	GLshort s = args.PickNumber<GLshort>();
	// Function body
	glTexCoord1s(s);
	return Value::nil();
}

// opengl.glTexCoord1sv(v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord1sv, "glTexCoord1sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord1sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord1sv(v);
	return Value::nil();
}

// opengl.glTexCoord2d(s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord2d, "glTexCoord2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2d)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord2dv, "glTexCoord2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord2dv(v);
	return Value::nil();
}

// opengl.glTexCoord2f(s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord2f, "glTexCoord2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2f)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord2fv, "glTexCoord2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord2fv(v);
	return Value::nil();
}

// opengl.glTexCoord2i(s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord2i, "glTexCoord2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2i)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord2iv, "glTexCoord2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord2iv(v);
	return Value::nil();
}

// opengl.glTexCoord2s(s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord2s, "glTexCoord2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2s)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord2sv, "glTexCoord2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord2sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord2sv(v);
	return Value::nil();
}

// opengl.glTexCoord3d(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord3d, "glTexCoord3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3d)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord3dv, "glTexCoord3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord3dv(v);
	return Value::nil();
}

// opengl.glTexCoord3f(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord3f, "glTexCoord3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3f)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord3fv, "glTexCoord3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord3fv(v);
	return Value::nil();
}

// opengl.glTexCoord3i(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord3i, "glTexCoord3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3i)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord3iv, "glTexCoord3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord3iv(v);
	return Value::nil();
}

// opengl.glTexCoord3s(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord3s, "glTexCoord3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3s)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord3sv, "glTexCoord3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord3sv(v);
	return Value::nil();
}

// opengl.glTexCoord4d(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord4d, "glTexCoord4d")
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

Gurax_ImplementFunction(gurax_glTexCoord4d)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord4dv, "glTexCoord4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord4dv(v);
	return Value::nil();
}

// opengl.glTexCoord4f(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord4f, "glTexCoord4f")
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

Gurax_ImplementFunction(gurax_glTexCoord4f)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord4fv, "glTexCoord4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord4fv(v);
	return Value::nil();
}

// opengl.glTexCoord4i(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord4i, "glTexCoord4i")
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

Gurax_ImplementFunction(gurax_glTexCoord4i)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord4iv, "glTexCoord4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord4iv(v);
	return Value::nil();
}

// opengl.glTexCoord4s(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glTexCoord4s, "glTexCoord4s")
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

Gurax_ImplementFunction(gurax_glTexCoord4s)
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
Gurax_DeclareFunctionAlias(gurax_glTexCoord4sv, "glTexCoord4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexCoord4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord4sv(v);
	return Value::nil();
}

// opengl.glTexEnvf(target:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(gurax_glTexEnvf, "glTexEnvf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexEnvf)
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
Gurax_DeclareFunctionAlias(gurax_glTexEnvfv, "glTexEnvfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexEnvfv)
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
Gurax_DeclareFunctionAlias(gurax_glTexEnvi, "glTexEnvi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexEnvi)
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
Gurax_DeclareFunctionAlias(gurax_glTexEnviv, "glTexEnviv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexEnviv)
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
Gurax_DeclareFunctionAlias(gurax_glTexGend, "glTexGend")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexGend)
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
Gurax_DeclareFunctionAlias(gurax_glTexGendv, "glTexGendv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexGendv)
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
Gurax_DeclareFunctionAlias(gurax_glTexGenf, "glTexGenf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexGenf)
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
Gurax_DeclareFunctionAlias(gurax_glTexGenfv, "glTexGenfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexGenfv)
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
Gurax_DeclareFunctionAlias(gurax_glTexGeni, "glTexGeni")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexGeni)
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
Gurax_DeclareFunctionAlias(gurax_glTexGeniv, "glTexGeniv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexGeniv)
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
Gurax_DeclareFunctionAlias(gurax_glTexParameterf, "glTexParameterf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexParameterf)
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
Gurax_DeclareFunctionAlias(gurax_glTexParameterfv, "glTexParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexParameterfv)
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
Gurax_DeclareFunctionAlias(gurax_glTexParameteri, "glTexParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexParameteri)
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
Gurax_DeclareFunctionAlias(gurax_glTexParameteriv, "glTexParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTexParameteriv)
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
Gurax_DeclareFunctionAlias(gurax_glTranslated, "glTranslated")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTranslated)
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
Gurax_DeclareFunctionAlias(gurax_glTranslatef, "glTranslatef")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glTranslatef)
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
Gurax_DeclareFunctionAlias(gurax_glVertex2d, "glVertex2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2d)
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
Gurax_DeclareFunctionAlias(gurax_glVertex2dv, "glVertex2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex2dv(v);
	return Value::nil();
}

// opengl.glVertex2f(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex2f, "glVertex2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2f)
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
Gurax_DeclareFunctionAlias(gurax_glVertex2fv, "glVertex2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex2fv(v);
	return Value::nil();
}

// opengl.glVertex2i(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex2i, "glVertex2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2i)
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
Gurax_DeclareFunctionAlias(gurax_glVertex2iv, "glVertex2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex2iv(v);
	return Value::nil();
}

// opengl.glVertex2s(x:Number, y:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex2s, "glVertex2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2s)
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
Gurax_DeclareFunctionAlias(gurax_glVertex2sv, "glVertex2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex2sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex2sv(v);
	return Value::nil();
}

// opengl.glVertex3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex3d, "glVertex3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3d)
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
Gurax_DeclareFunctionAlias(gurax_glVertex3dv, "glVertex3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex3dv(v);
	return Value::nil();
}

// opengl.glVertex3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex3f, "glVertex3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3f)
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
Gurax_DeclareFunctionAlias(gurax_glVertex3fv, "glVertex3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex3fv(v);
	return Value::nil();
}

// opengl.glVertex3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex3i, "glVertex3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3i)
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
Gurax_DeclareFunctionAlias(gurax_glVertex3iv, "glVertex3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex3iv(v);
	return Value::nil();
}

// opengl.glVertex3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex3s, "glVertex3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3s)
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
Gurax_DeclareFunctionAlias(gurax_glVertex3sv, "glVertex3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex3sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex3sv(v);
	return Value::nil();
}

// opengl.glVertex4d(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex4d, "glVertex4d")
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

Gurax_ImplementFunction(gurax_glVertex4d)
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
Gurax_DeclareFunctionAlias(gurax_glVertex4dv, "glVertex4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex4dv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex4dv(v);
	return Value::nil();
}

// opengl.glVertex4f(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex4f, "glVertex4f")
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

Gurax_ImplementFunction(gurax_glVertex4f)
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
Gurax_DeclareFunctionAlias(gurax_glVertex4fv, "glVertex4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex4fv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex4fv(v);
	return Value::nil();
}

// opengl.glVertex4i(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex4i, "glVertex4i")
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

Gurax_ImplementFunction(gurax_glVertex4i)
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
Gurax_DeclareFunctionAlias(gurax_glVertex4iv, "glVertex4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex4iv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex4iv(v);
	return Value::nil();
}

// opengl.glVertex4s(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(gurax_glVertex4s, "glVertex4s")
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

Gurax_ImplementFunction(gurax_glVertex4s)
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
Gurax_DeclareFunctionAlias(gurax_glVertex4sv, "glVertex4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glVertex4sv)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex4sv(v);
	return Value::nil();
}

// opengl.glViewport(x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(gurax_glViewport, "glViewport")
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

Gurax_ImplementFunction(gurax_glViewport)
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

// opengl.glCopyTexSubImage3D(target:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(gurax_glCopyTexSubImage3D, "glCopyTexSubImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glCopyTexSubImage3D)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLint yoffset = args.PickNumber<GLint>();
	GLint zoffset = args.PickNumber<GLint>();
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	// Function body
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	return Value::nil();
}

// opengl.glActiveTexture(texture:Number)
Gurax_DeclareFunctionAlias(gurax_glActiveTexture, "glActiveTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glActiveTexture)
{
	// Arguments
	ArgPicker args(argument);
	GLenum texture = args.PickNumber<GLenum>();
	// Function body
	glActiveTexture(texture);
	return Value::nil();
}

// opengl.glClientActiveTexture(texture:Number)
Gurax_DeclareFunctionAlias(gurax_glClientActiveTexture, "glClientActiveTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glClientActiveTexture)
{
	// Arguments
	ArgPicker args(argument);
	GLenum texture = args.PickNumber<GLenum>();
	// Function body
	glClientActiveTexture(texture);
	return Value::nil();
}

// opengl.glLoadTransposeMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glLoadTransposeMatrixd, "glLoadTransposeMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLoadTransposeMatrixd)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glLoadTransposeMatrixd(m);
	return Value::nil();
}

// opengl.glLoadTransposeMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glLoadTransposeMatrixf, "glLoadTransposeMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glLoadTransposeMatrixf)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glLoadTransposeMatrixf(m);
	return Value::nil();
}

// opengl.glMultTransposeMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultTransposeMatrixd, "glMultTransposeMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultTransposeMatrixd)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glMultTransposeMatrixd(m);
	return Value::nil();
}

// opengl.glMultTransposeMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultTransposeMatrixf, "glMultTransposeMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultTransposeMatrixf)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glMultTransposeMatrixf(m);
	return Value::nil();
}

// opengl.glMultiTexCoord1d(target:Number, s:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1d, "glMultiTexCoord1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1d)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLdouble s = args.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord1d(target, s);
	return Value::nil();
}

// opengl.glMultiTexCoord1dv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1dv, "glMultiTexCoord1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1dv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord1dv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord1f(target:Number, s:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1f, "glMultiTexCoord1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1f)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLfloat s = args.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord1f(target, s);
	return Value::nil();
}

// opengl.glMultiTexCoord1fv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1fv, "glMultiTexCoord1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1fv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord1fv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord1i(target:Number, s:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1i, "glMultiTexCoord1i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1i)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint s = args.PickNumber<GLint>();
	// Function body
	glMultiTexCoord1i(target, s);
	return Value::nil();
}

// opengl.glMultiTexCoord1iv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1iv, "glMultiTexCoord1iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1iv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLint>();
	// Function body
	glMultiTexCoord1iv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord1s(target:Number, s:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1s, "glMultiTexCoord1s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1s)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLshort s = args.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord1s(target, s);
	return Value::nil();
}

// opengl.glMultiTexCoord1sv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord1sv, "glMultiTexCoord1sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord1sv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord1sv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord2d(target:Number, s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2d, "glMultiTexCoord2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2d)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLdouble s = args.PickNumber<GLdouble>();
	GLdouble t = args.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord2d(target, s, t);
	return Value::nil();
}

// opengl.glMultiTexCoord2dv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2dv, "glMultiTexCoord2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2dv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord2dv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord2f(target:Number, s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2f, "glMultiTexCoord2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2f)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLfloat s = args.PickNumber<GLfloat>();
	GLfloat t = args.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord2f(target, s, t);
	return Value::nil();
}

// opengl.glMultiTexCoord2fv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2fv, "glMultiTexCoord2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2fv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord2fv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord2i(target:Number, s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2i, "glMultiTexCoord2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2i)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint s = args.PickNumber<GLint>();
	GLint t = args.PickNumber<GLint>();
	// Function body
	glMultiTexCoord2i(target, s, t);
	return Value::nil();
}

// opengl.glMultiTexCoord2iv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2iv, "glMultiTexCoord2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2iv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLint>();
	// Function body
	glMultiTexCoord2iv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord2s(target:Number, s:Number, t:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2s, "glMultiTexCoord2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2s)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLshort s = args.PickNumber<GLshort>();
	GLshort t = args.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord2s(target, s, t);
	return Value::nil();
}

// opengl.glMultiTexCoord2sv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord2sv, "glMultiTexCoord2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord2sv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord2sv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord3d(target:Number, s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3d, "glMultiTexCoord3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3d)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLdouble s = args.PickNumber<GLdouble>();
	GLdouble t = args.PickNumber<GLdouble>();
	GLdouble r = args.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord3d(target, s, t, r);
	return Value::nil();
}

// opengl.glMultiTexCoord3dv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3dv, "glMultiTexCoord3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3dv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord3dv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord3f(target:Number, s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3f, "glMultiTexCoord3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3f)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLfloat s = args.PickNumber<GLfloat>();
	GLfloat t = args.PickNumber<GLfloat>();
	GLfloat r = args.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord3f(target, s, t, r);
	return Value::nil();
}

// opengl.glMultiTexCoord3fv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3fv, "glMultiTexCoord3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3fv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord3fv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord3i(target:Number, s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3i, "glMultiTexCoord3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3i)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint s = args.PickNumber<GLint>();
	GLint t = args.PickNumber<GLint>();
	GLint r = args.PickNumber<GLint>();
	// Function body
	glMultiTexCoord3i(target, s, t, r);
	return Value::nil();
}

// opengl.glMultiTexCoord3iv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3iv, "glMultiTexCoord3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3iv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLint>();
	// Function body
	glMultiTexCoord3iv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord3s(target:Number, s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3s, "glMultiTexCoord3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3s)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLshort s = args.PickNumber<GLshort>();
	GLshort t = args.PickNumber<GLshort>();
	GLshort r = args.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord3s(target, s, t, r);
	return Value::nil();
}

// opengl.glMultiTexCoord3sv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord3sv, "glMultiTexCoord3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord3sv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord3sv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord4d(target:Number, s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4d, "glMultiTexCoord4d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4d)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLdouble s = args.PickNumber<GLdouble>();
	GLdouble t = args.PickNumber<GLdouble>();
	GLdouble r = args.PickNumber<GLdouble>();
	GLdouble q = args.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord4d(target, s, t, r, q);
	return Value::nil();
}

// opengl.glMultiTexCoord4dv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4dv, "glMultiTexCoord4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4dv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord4dv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord4f(target:Number, s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4f, "glMultiTexCoord4f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4f)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLfloat s = args.PickNumber<GLfloat>();
	GLfloat t = args.PickNumber<GLfloat>();
	GLfloat r = args.PickNumber<GLfloat>();
	GLfloat q = args.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord4f(target, s, t, r, q);
	return Value::nil();
}

// opengl.glMultiTexCoord4fv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4fv, "glMultiTexCoord4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4fv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord4fv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord4i(target:Number, s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4i, "glMultiTexCoord4i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4i)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint s = args.PickNumber<GLint>();
	GLint t = args.PickNumber<GLint>();
	GLint r = args.PickNumber<GLint>();
	GLint q = args.PickNumber<GLint>();
	// Function body
	glMultiTexCoord4i(target, s, t, r, q);
	return Value::nil();
}

// opengl.glMultiTexCoord4iv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4iv, "glMultiTexCoord4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4iv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLint>();
	// Function body
	glMultiTexCoord4iv(target, v);
	return Value::nil();
}

// opengl.glMultiTexCoord4s(target:Number, s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4s, "glMultiTexCoord4s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("q", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4s)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLshort s = args.PickNumber<GLshort>();
	GLshort t = args.PickNumber<GLshort>();
	GLshort r = args.PickNumber<GLshort>();
	GLshort q = args.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord4s(target, s, t, r, q);
	return Value::nil();
}

// opengl.glMultiTexCoord4sv(target:Number, v[]:Number)
Gurax_DeclareFunctionAlias(gurax_glMultiTexCoord4sv, "glMultiTexCoord4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glMultiTexCoord4sv)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord4sv(target, v);
	return Value::nil();
}

// opengl.glSampleCoverage(value:Number, invert:Bool)
Gurax_DeclareFunctionAlias(gurax_glSampleCoverage, "glSampleCoverage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("invert", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(gurax_glSampleCoverage)
{
	// Arguments
	ArgPicker args(argument);
	GLclampf value = args.PickNumber<GLclampf>();
	GLboolean invert = static_cast<GLboolean>(args.PickBool());
	// Function body
	glSampleCoverage(value, invert);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(gurax_glewInit));
	frame.Assign(Gurax_CreateFunction(gurax_glewIsSupported));
	frame.Assign(Gurax_CreateFunction(gurax_glewGetExtension));
	frame.Assign(Gurax_CreateFunction(gurax_glewGetErrorString));
	frame.Assign(Gurax_CreateFunction(gurax_glewGetString));
	frame.Assign(Gurax_CreateFunction(gurax_glAccum));
	frame.Assign(Gurax_CreateFunction(gurax_glAlphaFunc));
	frame.Assign(Gurax_CreateFunction(gurax_glArrayElement));
	frame.Assign(Gurax_CreateFunction(gurax_glBegin));
	frame.Assign(Gurax_CreateFunction(gurax_glBindTexture));
	frame.Assign(Gurax_CreateFunction(gurax_glBlendFunc));
	frame.Assign(Gurax_CreateFunction(gurax_glCallList));
	frame.Assign(Gurax_CreateFunction(gurax_glClear));
	frame.Assign(Gurax_CreateFunction(gurax_glClearAccum));
	frame.Assign(Gurax_CreateFunction(gurax_glClearColor));
	frame.Assign(Gurax_CreateFunction(gurax_glClearDepth));
	frame.Assign(Gurax_CreateFunction(gurax_glClearIndex));
	frame.Assign(Gurax_CreateFunction(gurax_glClearStencil));
	frame.Assign(Gurax_CreateFunction(gurax_glClipPlane));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3b));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3bv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3d));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3dv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3f));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3fv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3i));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3iv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3s));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3sv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3ub));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3ubv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3ui));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3uiv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3us));
	frame.Assign(Gurax_CreateFunction(gurax_glColor3usv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4b));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4bv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4d));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4dv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4f));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4fv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4i));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4iv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4s));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4sv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4ub));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4ubv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4ui));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4uiv));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4us));
	frame.Assign(Gurax_CreateFunction(gurax_glColor4usv));
	frame.Assign(Gurax_CreateFunction(gurax_glColorMask));
	frame.Assign(Gurax_CreateFunction(gurax_glColorMaterial));
	frame.Assign(Gurax_CreateFunction(gurax_glCopyPixels));
	frame.Assign(Gurax_CreateFunction(gurax_glCopyTexImage1D));
	frame.Assign(Gurax_CreateFunction(gurax_glCopyTexImage2D));
	frame.Assign(Gurax_CreateFunction(gurax_glCopyTexSubImage1D));
	frame.Assign(Gurax_CreateFunction(gurax_glCopyTexSubImage2D));
	frame.Assign(Gurax_CreateFunction(gurax_glCullFace));
	frame.Assign(Gurax_CreateFunction(gurax_glDeleteLists));
	frame.Assign(Gurax_CreateFunction(gurax_glDeleteTextures));
	frame.Assign(Gurax_CreateFunction(gurax_glDepthFunc));
	frame.Assign(Gurax_CreateFunction(gurax_glDepthMask));
	frame.Assign(Gurax_CreateFunction(gurax_glDepthRange));
	frame.Assign(Gurax_CreateFunction(gurax_glDisable));
	frame.Assign(Gurax_CreateFunction(gurax_glDisableClientState));
	frame.Assign(Gurax_CreateFunction(gurax_glDrawArrays));
	frame.Assign(Gurax_CreateFunction(gurax_glDrawBuffer));
	frame.Assign(Gurax_CreateFunction(gurax_glEdgeFlag));
	frame.Assign(Gurax_CreateFunction(gurax_glEdgeFlagv));
	frame.Assign(Gurax_CreateFunction(gurax_glEnable));
	frame.Assign(Gurax_CreateFunction(gurax_glEnableClientState));
	frame.Assign(Gurax_CreateFunction(gurax_glEnd));
	frame.Assign(Gurax_CreateFunction(gurax_glEndList));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord1d));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord1dv));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord1f));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord1fv));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord2d));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord2dv));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord2f));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalCoord2fv));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalMesh1));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalMesh2));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalPoint1));
	frame.Assign(Gurax_CreateFunction(gurax_glEvalPoint2));
	frame.Assign(Gurax_CreateFunction(gurax_glFeedbackBuffer));
	frame.Assign(Gurax_CreateFunction(gurax_glFinish));
	frame.Assign(Gurax_CreateFunction(gurax_glFlush));
	frame.Assign(Gurax_CreateFunction(gurax_glFogf));
	frame.Assign(Gurax_CreateFunction(gurax_glFogfv));
	frame.Assign(Gurax_CreateFunction(gurax_glFogi));
	frame.Assign(Gurax_CreateFunction(gurax_glFogiv));
	frame.Assign(Gurax_CreateFunction(gurax_glFrontFace));
	frame.Assign(Gurax_CreateFunction(gurax_glFrustum));
	frame.Assign(Gurax_CreateFunction(gurax_glGenLists));
	frame.Assign(Gurax_CreateFunction(gurax_glGenTextures));
	frame.Assign(Gurax_CreateFunction(gurax_glGetError));
	frame.Assign(Gurax_CreateFunction(gurax_glGetString));
	frame.Assign(Gurax_CreateFunction(gurax_glHint));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexMask));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexd));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexdv));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexf));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexfv));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexi));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexiv));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexs));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexsv));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexub));
	frame.Assign(Gurax_CreateFunction(gurax_glIndexubv));
	frame.Assign(Gurax_CreateFunction(gurax_glInitNames));
	frame.Assign(Gurax_CreateFunction(gurax_glIsEnabled));
	frame.Assign(Gurax_CreateFunction(gurax_glIsList));
	frame.Assign(Gurax_CreateFunction(gurax_glIsTexture));
	frame.Assign(Gurax_CreateFunction(gurax_glLightModelf));
	frame.Assign(Gurax_CreateFunction(gurax_glLightModelfv));
	frame.Assign(Gurax_CreateFunction(gurax_glLightModeli));
	frame.Assign(Gurax_CreateFunction(gurax_glLightModeliv));
	frame.Assign(Gurax_CreateFunction(gurax_glLightf));
	frame.Assign(Gurax_CreateFunction(gurax_glLightfv));
	frame.Assign(Gurax_CreateFunction(gurax_glLighti));
	frame.Assign(Gurax_CreateFunction(gurax_glLightiv));
	frame.Assign(Gurax_CreateFunction(gurax_glLineStipple));
	frame.Assign(Gurax_CreateFunction(gurax_glLineWidth));
	frame.Assign(Gurax_CreateFunction(gurax_glListBase));
	frame.Assign(Gurax_CreateFunction(gurax_glLoadIdentity));
	frame.Assign(Gurax_CreateFunction(gurax_glLoadMatrixd));
	frame.Assign(Gurax_CreateFunction(gurax_glLoadMatrixf));
	frame.Assign(Gurax_CreateFunction(gurax_glLoadName));
	frame.Assign(Gurax_CreateFunction(gurax_glLogicOp));
	frame.Assign(Gurax_CreateFunction(gurax_glMap1d));
	frame.Assign(Gurax_CreateFunction(gurax_glMap1f));
	frame.Assign(Gurax_CreateFunction(gurax_glMap2d));
	frame.Assign(Gurax_CreateFunction(gurax_glMap2f));
	frame.Assign(Gurax_CreateFunction(gurax_glMapGrid1d));
	frame.Assign(Gurax_CreateFunction(gurax_glMapGrid1f));
	frame.Assign(Gurax_CreateFunction(gurax_glMapGrid2d));
	frame.Assign(Gurax_CreateFunction(gurax_glMapGrid2f));
	frame.Assign(Gurax_CreateFunction(gurax_glMaterialf));
	frame.Assign(Gurax_CreateFunction(gurax_glMaterialfv));
	frame.Assign(Gurax_CreateFunction(gurax_glMateriali));
	frame.Assign(Gurax_CreateFunction(gurax_glMaterialiv));
	frame.Assign(Gurax_CreateFunction(gurax_glMatrixMode));
	frame.Assign(Gurax_CreateFunction(gurax_glMultMatrixd));
	frame.Assign(Gurax_CreateFunction(gurax_glMultMatrixf));
	frame.Assign(Gurax_CreateFunction(gurax_glNewList));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3b));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3bv));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3d));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3dv));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3f));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3fv));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3i));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3iv));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3s));
	frame.Assign(Gurax_CreateFunction(gurax_glNormal3sv));
	frame.Assign(Gurax_CreateFunction(gurax_glOrtho));
	frame.Assign(Gurax_CreateFunction(gurax_glPassThrough));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelMapfv));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelMapuiv));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelMapusv));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelStoref));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelStorei));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelTransferf));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelTransferi));
	frame.Assign(Gurax_CreateFunction(gurax_glPixelZoom));
	frame.Assign(Gurax_CreateFunction(gurax_glPointSize));
	frame.Assign(Gurax_CreateFunction(gurax_glPolygonMode));
	frame.Assign(Gurax_CreateFunction(gurax_glPolygonOffset));
	frame.Assign(Gurax_CreateFunction(gurax_glPolygonStipple));
	frame.Assign(Gurax_CreateFunction(gurax_glPopAttrib));
	frame.Assign(Gurax_CreateFunction(gurax_glPopClientAttrib));
	frame.Assign(Gurax_CreateFunction(gurax_glPopMatrix));
	frame.Assign(Gurax_CreateFunction(gurax_glPopName));
	frame.Assign(Gurax_CreateFunction(gurax_glPrioritizeTextures));
	frame.Assign(Gurax_CreateFunction(gurax_glPushAttrib));
	frame.Assign(Gurax_CreateFunction(gurax_glPushClientAttrib));
	frame.Assign(Gurax_CreateFunction(gurax_glPushMatrix));
	frame.Assign(Gurax_CreateFunction(gurax_glPushName));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2d));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2dv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2f));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2fv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2i));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2iv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2s));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos2sv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3d));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3dv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3f));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3fv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3i));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3iv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3s));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos3sv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4d));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4dv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4f));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4fv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4i));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4iv));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4s));
	frame.Assign(Gurax_CreateFunction(gurax_glRasterPos4sv));
	frame.Assign(Gurax_CreateFunction(gurax_glReadBuffer));
	frame.Assign(Gurax_CreateFunction(gurax_glRectd));
	frame.Assign(Gurax_CreateFunction(gurax_glRectdv));
	frame.Assign(Gurax_CreateFunction(gurax_glRectf));
	frame.Assign(Gurax_CreateFunction(gurax_glRectfv));
	frame.Assign(Gurax_CreateFunction(gurax_glRecti));
	frame.Assign(Gurax_CreateFunction(gurax_glRectiv));
	frame.Assign(Gurax_CreateFunction(gurax_glRects));
	frame.Assign(Gurax_CreateFunction(gurax_glRectsv));
	frame.Assign(Gurax_CreateFunction(gurax_glRenderMode));
	frame.Assign(Gurax_CreateFunction(gurax_glRotated));
	frame.Assign(Gurax_CreateFunction(gurax_glRotatef));
	frame.Assign(Gurax_CreateFunction(gurax_glScaled));
	frame.Assign(Gurax_CreateFunction(gurax_glScalef));
	frame.Assign(Gurax_CreateFunction(gurax_glScissor));
	frame.Assign(Gurax_CreateFunction(gurax_glShadeModel));
	frame.Assign(Gurax_CreateFunction(gurax_glStencilFunc));
	frame.Assign(Gurax_CreateFunction(gurax_glStencilMask));
	frame.Assign(Gurax_CreateFunction(gurax_glStencilOp));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1d));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1dv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1f));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1fv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1i));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1iv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1s));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord1sv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2d));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2dv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2f));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2fv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2i));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2iv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2s));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord2sv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3d));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3dv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3f));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3fv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3i));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3iv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3s));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord3sv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4d));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4dv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4f));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4fv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4i));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4iv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4s));
	frame.Assign(Gurax_CreateFunction(gurax_glTexCoord4sv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexEnvf));
	frame.Assign(Gurax_CreateFunction(gurax_glTexEnvfv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexEnvi));
	frame.Assign(Gurax_CreateFunction(gurax_glTexEnviv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexGend));
	frame.Assign(Gurax_CreateFunction(gurax_glTexGendv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexGenf));
	frame.Assign(Gurax_CreateFunction(gurax_glTexGenfv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexGeni));
	frame.Assign(Gurax_CreateFunction(gurax_glTexGeniv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexParameterf));
	frame.Assign(Gurax_CreateFunction(gurax_glTexParameterfv));
	frame.Assign(Gurax_CreateFunction(gurax_glTexParameteri));
	frame.Assign(Gurax_CreateFunction(gurax_glTexParameteriv));
	frame.Assign(Gurax_CreateFunction(gurax_glTranslated));
	frame.Assign(Gurax_CreateFunction(gurax_glTranslatef));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2d));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2dv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2f));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2fv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2i));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2iv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2s));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex2sv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3d));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3dv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3f));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3fv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3i));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3iv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3s));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex3sv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4d));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4dv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4f));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4fv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4i));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4iv));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4s));
	frame.Assign(Gurax_CreateFunction(gurax_glVertex4sv));
	frame.Assign(Gurax_CreateFunction(gurax_glViewport));
	frame.Assign(Gurax_CreateFunction(gurax_glCopyTexSubImage3D));
	frame.Assign(Gurax_CreateFunction(gurax_glActiveTexture));
	frame.Assign(Gurax_CreateFunction(gurax_glClientActiveTexture));
	frame.Assign(Gurax_CreateFunction(gurax_glLoadTransposeMatrixd));
	frame.Assign(Gurax_CreateFunction(gurax_glLoadTransposeMatrixf));
	frame.Assign(Gurax_CreateFunction(gurax_glMultTransposeMatrixd));
	frame.Assign(Gurax_CreateFunction(gurax_glMultTransposeMatrixf));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1d));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1dv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1f));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1fv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1i));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1iv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1s));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord1sv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2d));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2dv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2f));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2fv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2i));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2iv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2s));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord2sv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3d));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3dv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3f));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3fv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3i));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3iv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3s));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord3sv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4d));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4dv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4f));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4fv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4i));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4iv));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4s));
	frame.Assign(Gurax_CreateFunction(gurax_glMultiTexCoord4sv));
	frame.Assign(Gurax_CreateFunction(gurax_glSampleCoverage));
}

Gurax_EndModuleScope(opengl)
