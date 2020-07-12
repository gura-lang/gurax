//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(opengl)

// opengl.glewInit()
Gurax_DeclareFunctionAlias(glewInit_gurax, "glewInit")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewInit_gurax)
{
	// Function body
	GLenum rtn = glewInit();
	return new Value_Number(rtn);
}

// opengl.glewIsSupported(name:String)
Gurax_DeclareFunctionAlias(glewIsSupported_gurax, "glewIsSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewIsSupported_gurax)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	GLboolean rtn = glewIsSupported(name);
	return new Value_Bool(!!rtn);
}

// opengl.glewGetExtension(name:String)
Gurax_DeclareFunctionAlias(glewGetExtension_gurax, "glewGetExtension")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewGetExtension_gurax)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	GLboolean rtn = glewGetExtension(name);
	return new Value_Bool(!!rtn);
}

// opengl.glewGetErrorString(error:Number)
Gurax_DeclareFunctionAlias(glewGetErrorString_gurax, "glewGetErrorString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("error", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewGetErrorString_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum error = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetErrorString(error);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glewGetString(name:Number)
Gurax_DeclareFunctionAlias(glewGetString_gurax, "glewGetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glewGetString_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum name = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetString(name);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glAccum(op:Number, value:Number)
Gurax_DeclareFunctionAlias(glAccum_gurax, "glAccum")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("op", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glAccum_gurax)
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
Gurax_DeclareFunctionAlias(glAlphaFunc_gurax, "glAlphaFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glAlphaFunc_gurax)
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
Gurax_DeclareFunctionAlias(glArrayElement_gurax, "glArrayElement")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glArrayElement_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	// Function body
	glArrayElement(i);
	return Value::nil();
}

// opengl.glBegin(mode:Number)
Gurax_DeclareFunctionAlias(glBegin_gurax, "glBegin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBegin_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glBegin(mode);
	return Value::nil();
}

// opengl.glBindTexture(target:Number, texture:Number)
Gurax_DeclareFunctionAlias(glBindTexture_gurax, "glBindTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBindTexture_gurax)
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
Gurax_DeclareFunctionAlias(glBlendFunc_gurax, "glBlendFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendFunc_gurax)
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
Gurax_DeclareFunctionAlias(glCallList_gurax, "glCallList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCallList_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	// Function body
	glCallList(list);
	return Value::nil();
}

// opengl.glCallLists(n:Number, type:Number, lists:Pointer)
Gurax_DeclareFunctionAlias(glCallLists_gurax, "glCallLists")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lists", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCallLists_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	GLenum type = args.PickNumber<GLenum>();
	const void* lists = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCallLists(n, type, lists);
	return Value::nil();
}

// opengl.glClear(mask:Number)
Gurax_DeclareFunctionAlias(glClear_gurax, "glClear")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClear_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glClear(mask);
	return Value::nil();
}

// opengl.glClearAccum(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glClearAccum_gurax, "glClearAccum")
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

Gurax_ImplementFunction(glClearAccum_gurax)
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
Gurax_DeclareFunctionAlias(glClearColor_gurax, "glClearColor")
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

Gurax_ImplementFunction(glClearColor_gurax)
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
Gurax_DeclareFunctionAlias(glClearDepth_gurax, "glClearDepth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearDepth_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLclampd depth = args.PickNumber<GLclampd>();
	// Function body
	glClearDepth(depth);
	return Value::nil();
}

// opengl.glClearIndex(c:Number)
Gurax_DeclareFunctionAlias(glClearIndex_gurax, "glClearIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearIndex_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat c = args.PickNumber<GLfloat>();
	// Function body
	glClearIndex(c);
	return Value::nil();
}

// opengl.glClearStencil(s:Number)
Gurax_DeclareFunctionAlias(glClearStencil_gurax, "glClearStencil")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearStencil_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	// Function body
	glClearStencil(s);
	return Value::nil();
}

// opengl.glClipPlane(plane:Number, equation[]:Number)
Gurax_DeclareFunctionAlias(glClipPlane_gurax, "glClipPlane")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("plane", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("equation", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClipPlane_gurax)
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
Gurax_DeclareFunctionAlias(glColor3b_gurax, "glColor3b")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3b_gurax)
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
Gurax_DeclareFunctionAlias(glColor3bv_gurax, "glColor3bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3bv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glColor3bv(v);
	return Value::nil();
}

// opengl.glColor3d(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3d_gurax, "glColor3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3d_gurax)
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
Gurax_DeclareFunctionAlias(glColor3dv_gurax, "glColor3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glColor3dv(v);
	return Value::nil();
}

// opengl.glColor3f(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3f_gurax, "glColor3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3f_gurax)
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
Gurax_DeclareFunctionAlias(glColor3fv_gurax, "glColor3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glColor3fv(v);
	return Value::nil();
}

// opengl.glColor3i(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3i_gurax, "glColor3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3i_gurax)
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
Gurax_DeclareFunctionAlias(glColor3iv_gurax, "glColor3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glColor3iv(v);
	return Value::nil();
}

// opengl.glColor3s(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3s_gurax, "glColor3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3s_gurax)
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
Gurax_DeclareFunctionAlias(glColor3sv_gurax, "glColor3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glColor3sv(v);
	return Value::nil();
}

// opengl.glColor3ub(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3ub_gurax, "glColor3ub")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3ub_gurax)
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
Gurax_DeclareFunctionAlias(glColor3ubv_gurax, "glColor3ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3ubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glColor3ubv(v);
	return Value::nil();
}

// opengl.glColor3ui(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3ui_gurax, "glColor3ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3ui_gurax)
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
Gurax_DeclareFunctionAlias(glColor3uiv_gurax, "glColor3uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glColor3uiv(v);
	return Value::nil();
}

// opengl.glColor3us(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glColor3us_gurax, "glColor3us")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3us_gurax)
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
Gurax_DeclareFunctionAlias(glColor3usv_gurax, "glColor3usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor3usv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glColor3usv(v);
	return Value::nil();
}

// opengl.glColor4b(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4b_gurax, "glColor4b")
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

Gurax_ImplementFunction(glColor4b_gurax)
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
Gurax_DeclareFunctionAlias(glColor4bv_gurax, "glColor4bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4bv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glColor4bv(v);
	return Value::nil();
}

// opengl.glColor4d(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4d_gurax, "glColor4d")
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

Gurax_ImplementFunction(glColor4d_gurax)
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
Gurax_DeclareFunctionAlias(glColor4dv_gurax, "glColor4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glColor4dv(v);
	return Value::nil();
}

// opengl.glColor4f(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4f_gurax, "glColor4f")
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

Gurax_ImplementFunction(glColor4f_gurax)
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
Gurax_DeclareFunctionAlias(glColor4fv_gurax, "glColor4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glColor4fv(v);
	return Value::nil();
}

// opengl.glColor4i(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4i_gurax, "glColor4i")
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

Gurax_ImplementFunction(glColor4i_gurax)
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
Gurax_DeclareFunctionAlias(glColor4iv_gurax, "glColor4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glColor4iv(v);
	return Value::nil();
}

// opengl.glColor4s(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4s_gurax, "glColor4s")
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

Gurax_ImplementFunction(glColor4s_gurax)
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
Gurax_DeclareFunctionAlias(glColor4sv_gurax, "glColor4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glColor4sv(v);
	return Value::nil();
}

// opengl.glColor4ub(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4ub_gurax, "glColor4ub")
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

Gurax_ImplementFunction(glColor4ub_gurax)
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
Gurax_DeclareFunctionAlias(glColor4ubv_gurax, "glColor4ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4ubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glColor4ubv(v);
	return Value::nil();
}

// opengl.glColor4ui(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4ui_gurax, "glColor4ui")
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

Gurax_ImplementFunction(glColor4ui_gurax)
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
Gurax_DeclareFunctionAlias(glColor4uiv_gurax, "glColor4uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glColor4uiv(v);
	return Value::nil();
}

// opengl.glColor4us(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glColor4us_gurax, "glColor4us")
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

Gurax_ImplementFunction(glColor4us_gurax)
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
Gurax_DeclareFunctionAlias(glColor4usv_gurax, "glColor4usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColor4usv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glColor4usv(v);
	return Value::nil();
}

// opengl.glColorMask(red:Bool, green:Bool, blue:Bool, alpha:Bool)
Gurax_DeclareFunctionAlias(glColorMask_gurax, "glColorMask")
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

Gurax_ImplementFunction(glColorMask_gurax)
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
Gurax_DeclareFunctionAlias(glColorMaterial_gurax, "glColorMaterial")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColorMaterial_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glColorMaterial(face, mode);
	return Value::nil();
}

// opengl.glColorPointer(size:Number, type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glColorPointer_gurax, "glColorPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColorPointer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint size = args.PickNumber<GLint>();
	GLenum type = args.PickNumber<GLenum>();
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glColorPointer(size, type, stride, pointer);
	return Value::nil();
}

// opengl.glCopyPixels(x:Number, y:Number, width:Number, height:Number, type:Number)
Gurax_DeclareFunctionAlias(glCopyPixels_gurax, "glCopyPixels")
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

Gurax_ImplementFunction(glCopyPixels_gurax)
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
Gurax_DeclareFunctionAlias(glCopyTexImage1D_gurax, "glCopyTexImage1D")
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

Gurax_ImplementFunction(glCopyTexImage1D_gurax)
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
Gurax_DeclareFunctionAlias(glCopyTexImage2D_gurax, "glCopyTexImage2D")
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

Gurax_ImplementFunction(glCopyTexImage2D_gurax)
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
Gurax_DeclareFunctionAlias(glCopyTexSubImage1D_gurax, "glCopyTexSubImage1D")
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

Gurax_ImplementFunction(glCopyTexSubImage1D_gurax)
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
Gurax_DeclareFunctionAlias(glCopyTexSubImage2D_gurax, "glCopyTexSubImage2D")
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

Gurax_ImplementFunction(glCopyTexSubImage2D_gurax)
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
Gurax_DeclareFunctionAlias(glCullFace_gurax, "glCullFace")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCullFace_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glCullFace(mode);
	return Value::nil();
}

// opengl.glDeleteLists(list:Number, range:Number)
Gurax_DeclareFunctionAlias(glDeleteLists_gurax, "glDeleteLists")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteLists_gurax)
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
Gurax_DeclareFunctionAlias(glDeleteTextures_gurax, "glDeleteTextures")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("textures", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteTextures_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto textures = args.PickNumList<GLuint>();
	// Function body
	glDeleteTextures(textures.sizeT<GLsizei>(), textures);
	return Value::nil();
}

// opengl.glDepthFunc(func:Number)
Gurax_DeclareFunctionAlias(glDepthFunc_gurax, "glDepthFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDepthFunc_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum func = args.PickNumber<GLenum>();
	// Function body
	glDepthFunc(func);
	return Value::nil();
}

// opengl.glDepthMask(flag:Bool)
Gurax_DeclareFunctionAlias(glDepthMask_gurax, "glDepthMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDepthMask_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean flag = static_cast<GLboolean>(args.PickBool());
	// Function body
	glDepthMask(flag);
	return Value::nil();
}

// opengl.glDepthRange(zNear:Number, zFar:Number)
Gurax_DeclareFunctionAlias(glDepthRange_gurax, "glDepthRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("zNear", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zFar", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDepthRange_gurax)
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
Gurax_DeclareFunctionAlias(glDisable_gurax, "glDisable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDisable_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	glDisable(cap);
	return Value::nil();
}

// opengl.glDisableClientState(array:Number)
Gurax_DeclareFunctionAlias(glDisableClientState_gurax, "glDisableClientState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDisableClientState_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum array = args.PickNumber<GLenum>();
	// Function body
	glDisableClientState(array);
	return Value::nil();
}

// opengl.glDrawArrays(mode:Number, first:Number, count:Number)
Gurax_DeclareFunctionAlias(glDrawArrays_gurax, "glDrawArrays")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawArrays_gurax)
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
Gurax_DeclareFunctionAlias(glDrawBuffer_gurax, "glDrawBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawBuffer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glDrawBuffer(mode);
	return Value::nil();
}

// opengl.glDrawElements(mode:Number, count:Number, type:Number, indices:Pointer)
Gurax_DeclareFunctionAlias(glDrawElements_gurax, "glDrawElements")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawElements_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLenum type = args.PickNumber<GLenum>();
	const void* indices = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawElements(mode, count, type, indices);
	return Value::nil();
}

// opengl.glDrawPixels(width:Number, height:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glDrawPixels_gurax, "glDrawPixels")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawPixels_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLenum format = args.PickNumber<GLenum>();
	GLenum type = args.PickNumber<GLenum>();
	const void* pixels = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawPixels(width, height, format, type, pixels);
	return Value::nil();
}

// opengl.glEdgeFlag(flag:Bool)
Gurax_DeclareFunctionAlias(glEdgeFlag_gurax, "glEdgeFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEdgeFlag_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLboolean flag = static_cast<GLboolean>(args.PickBool());
	// Function body
	glEdgeFlag(flag);
	return Value::nil();
}

// opengl.glEdgeFlagPointer(stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glEdgeFlagPointer_gurax, "glEdgeFlagPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEdgeFlagPointer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glEdgeFlagPointer(stride, pointer);
	return Value::nil();
}

// opengl.glEdgeFlagv(flag[]:Bool)
Gurax_DeclareFunctionAlias(glEdgeFlagv_gurax, "glEdgeFlagv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEdgeFlagv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto flag = args.PickListT<GLboolean>([](Value& value) { return value.GetBool()? GL_TRUE : GL_FALSE; });
	// Function body
	glEdgeFlagv(flag);
	return Value::nil();
}

// opengl.glEnable(cap:Number)
Gurax_DeclareFunctionAlias(glEnable_gurax, "glEnable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnable_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	glEnable(cap);
	return Value::nil();
}

// opengl.glEnableClientState(array:Number)
Gurax_DeclareFunctionAlias(glEnableClientState_gurax, "glEnableClientState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnableClientState_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum array = args.PickNumber<GLenum>();
	// Function body
	glEnableClientState(array);
	return Value::nil();
}

// opengl.glEnd()
Gurax_DeclareFunctionAlias(glEnd_gurax, "glEnd")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnd_gurax)
{
	// Function body
	glEnd();
	return Value::nil();
}

// opengl.glEndList()
Gurax_DeclareFunctionAlias(glEndList_gurax, "glEndList")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEndList_gurax)
{
	// Function body
	glEndList();
	return Value::nil();
}

// opengl.glEvalCoord1d(u:Number)
Gurax_DeclareFunctionAlias(glEvalCoord1d_gurax, "glEvalCoord1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble u = args.PickNumber<GLdouble>();
	// Function body
	glEvalCoord1d(u);
	return Value::nil();
}

// opengl.glEvalCoord1dv(u[]:Number)
Gurax_DeclareFunctionAlias(glEvalCoord1dv_gurax, "glEvalCoord1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLdouble>();
	// Function body
	glEvalCoord1dv(u);
	return Value::nil();
}

// opengl.glEvalCoord1f(u:Number)
Gurax_DeclareFunctionAlias(glEvalCoord1f_gurax, "glEvalCoord1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat u = args.PickNumber<GLfloat>();
	// Function body
	glEvalCoord1f(u);
	return Value::nil();
}

// opengl.glEvalCoord1fv(u[]:Number)
Gurax_DeclareFunctionAlias(glEvalCoord1fv_gurax, "glEvalCoord1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord1fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLfloat>();
	// Function body
	glEvalCoord1fv(u);
	return Value::nil();
}

// opengl.glEvalCoord2d(u:Number, v:Number)
Gurax_DeclareFunctionAlias(glEvalCoord2d_gurax, "glEvalCoord2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2d_gurax)
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
Gurax_DeclareFunctionAlias(glEvalCoord2dv_gurax, "glEvalCoord2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLdouble>();
	// Function body
	glEvalCoord2dv(u);
	return Value::nil();
}

// opengl.glEvalCoord2f(u:Number, v:Number)
Gurax_DeclareFunctionAlias(glEvalCoord2f_gurax, "glEvalCoord2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2f_gurax)
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
Gurax_DeclareFunctionAlias(glEvalCoord2fv_gurax, "glEvalCoord2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("u", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalCoord2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto u = args.PickNumList<GLfloat>();
	// Function body
	glEvalCoord2fv(u);
	return Value::nil();
}

// opengl.glEvalMesh1(mode:Number, i1:Number, i2:Number)
Gurax_DeclareFunctionAlias(glEvalMesh1_gurax, "glEvalMesh1")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalMesh1_gurax)
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
Gurax_DeclareFunctionAlias(glEvalMesh2_gurax, "glEvalMesh2")
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

Gurax_ImplementFunction(glEvalMesh2_gurax)
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
Gurax_DeclareFunctionAlias(glEvalPoint1_gurax, "glEvalPoint1")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalPoint1_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint i = args.PickNumber<GLint>();
	// Function body
	glEvalPoint1(i);
	return Value::nil();
}

// opengl.glEvalPoint2(i:Number, j:Number)
Gurax_DeclareFunctionAlias(glEvalPoint2_gurax, "glEvalPoint2")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("j", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEvalPoint2_gurax)
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
Gurax_DeclareFunctionAlias(glFeedbackBuffer_gurax, "glFeedbackBuffer")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFeedbackBuffer_gurax)
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
Gurax_DeclareFunctionAlias(glFinish_gurax, "glFinish")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFinish_gurax)
{
	// Function body
	glFinish();
	return Value::nil();
}

// opengl.glFlush()
Gurax_DeclareFunctionAlias(glFlush_gurax, "glFlush")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFlush_gurax)
{
	// Function body
	glFlush();
	return Value::nil();
}

// opengl.glFogf(pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glFogf_gurax, "glFogf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogf_gurax)
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
Gurax_DeclareFunctionAlias(glFogfv_gurax, "glFogfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogfv_gurax)
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
Gurax_DeclareFunctionAlias(glFogi_gurax, "glFogi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogi_gurax)
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
Gurax_DeclareFunctionAlias(glFogiv_gurax, "glFogiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogiv_gurax)
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
Gurax_DeclareFunctionAlias(glFrontFace_gurax, "glFrontFace")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFrontFace_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glFrontFace(mode);
	return Value::nil();
}

// opengl.glFrustum(left:Number, right:Number, bottom:Number, top:Number, zNear:Number, zFar:Number)
Gurax_DeclareFunctionAlias(glFrustum_gurax, "glFrustum")
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

Gurax_ImplementFunction(glFrustum_gurax)
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
Gurax_DeclareFunctionAlias(glGenLists_gurax, "glGenLists")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGenLists_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei range = args.PickNumber<GLsizei>();
	// Function body
	GLuint rtn = glGenLists(range);
	return new Value_Number(rtn);
}

// opengl.glGenTextures(n:Number)
Gurax_DeclareFunctionAlias(glGenTextures_gurax, "glGenTextures")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGenTextures_gurax)
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
Gurax_DeclareFunctionAlias(glGetError_gurax, "glGetError")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGetError_gurax)
{
	// Function body
	GLenum rtn = glGetError();
	return new Value_Number(rtn);
}

// opengl.glGetString(name:Number)
Gurax_DeclareFunctionAlias(glGetString_gurax, "glGetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGetString_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum name = args.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glGetString(name);
	return new Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glHint(target:Number, mode:Number)
Gurax_DeclareFunctionAlias(glHint_gurax, "glHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glHint_gurax)
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
Gurax_DeclareFunctionAlias(glIndexMask_gurax, "glIndexMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexMask_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glIndexMask(mask);
	return Value::nil();
}

// opengl.glIndexPointer(type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glIndexPointer_gurax, "glIndexPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexPointer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum type = args.PickNumber<GLenum>();
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glIndexPointer(type, stride, pointer);
	return Value::nil();
}

// opengl.glIndexd(c:Number)
Gurax_DeclareFunctionAlias(glIndexd_gurax, "glIndexd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexd_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble c = args.PickNumber<GLdouble>();
	// Function body
	glIndexd(c);
	return Value::nil();
}

// opengl.glIndexdv(c[]:Number)
Gurax_DeclareFunctionAlias(glIndexdv_gurax, "glIndexdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexdv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLdouble>();
	// Function body
	glIndexdv(c);
	return Value::nil();
}

// opengl.glIndexf(c:Number)
Gurax_DeclareFunctionAlias(glIndexf_gurax, "glIndexf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat c = args.PickNumber<GLfloat>();
	// Function body
	glIndexf(c);
	return Value::nil();
}

// opengl.glIndexfv(c[]:Number)
Gurax_DeclareFunctionAlias(glIndexfv_gurax, "glIndexfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexfv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLfloat>();
	// Function body
	glIndexfv(c);
	return Value::nil();
}

// opengl.glIndexi(c:Number)
Gurax_DeclareFunctionAlias(glIndexi_gurax, "glIndexi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexi_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint c = args.PickNumber<GLint>();
	// Function body
	glIndexi(c);
	return Value::nil();
}

// opengl.glIndexiv(c[]:Number)
Gurax_DeclareFunctionAlias(glIndexiv_gurax, "glIndexiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLint>();
	// Function body
	glIndexiv(c);
	return Value::nil();
}

// opengl.glIndexs(c:Number)
Gurax_DeclareFunctionAlias(glIndexs_gurax, "glIndexs")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexs_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLshort c = args.PickNumber<GLshort>();
	// Function body
	glIndexs(c);
	return Value::nil();
}

// opengl.glIndexsv(c[]:Number)
Gurax_DeclareFunctionAlias(glIndexsv_gurax, "glIndexsv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexsv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLshort>();
	// Function body
	glIndexsv(c);
	return Value::nil();
}

// opengl.glIndexub(c:Number)
Gurax_DeclareFunctionAlias(glIndexub_gurax, "glIndexub")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexub_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLubyte c = args.PickNumber<GLubyte>();
	// Function body
	glIndexub(c);
	return Value::nil();
}

// opengl.glIndexubv(c[]:Number)
Gurax_DeclareFunctionAlias(glIndexubv_gurax, "glIndexubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("c", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIndexubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto c = args.PickNumList<GLubyte>();
	// Function body
	glIndexubv(c);
	return Value::nil();
}

// opengl.glInitNames()
Gurax_DeclareFunctionAlias(glInitNames_gurax, "glInitNames")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glInitNames_gurax)
{
	// Function body
	glInitNames();
	return Value::nil();
}

// opengl.glInterleavedArrays(format:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glInterleavedArrays_gurax, "glInterleavedArrays")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glInterleavedArrays_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum format = args.PickNumber<GLenum>();
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glInterleavedArrays(format, stride, pointer);
	return Value::nil();
}

// opengl.glIsEnabled(cap:Number)
Gurax_DeclareFunctionAlias(glIsEnabled_gurax, "glIsEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsEnabled_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	// Function body
	GLboolean rtn = glIsEnabled(cap);
	return new Value_Bool(!!rtn);
}

// opengl.glIsList(list:Number)
Gurax_DeclareFunctionAlias(glIsList_gurax, "glIsList")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsList_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint list = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsList(list);
	return new Value_Bool(!!rtn);
}

// opengl.glIsTexture(texture:Number)
Gurax_DeclareFunctionAlias(glIsTexture_gurax, "glIsTexture")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsTexture_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint texture = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsTexture(texture);
	return new Value_Bool(!!rtn);
}

// opengl.glLightModelf(pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glLightModelf_gurax, "glLightModelf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModelf_gurax)
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
Gurax_DeclareFunctionAlias(glLightModelfv_gurax, "glLightModelfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModelfv_gurax)
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
Gurax_DeclareFunctionAlias(glLightModeli_gurax, "glLightModeli")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModeli_gurax)
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
Gurax_DeclareFunctionAlias(glLightModeliv_gurax, "glLightModeliv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightModeliv_gurax)
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
Gurax_DeclareFunctionAlias(glLightf_gurax, "glLightf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightf_gurax)
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
Gurax_DeclareFunctionAlias(glLightfv_gurax, "glLightfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightfv_gurax)
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
Gurax_DeclareFunctionAlias(glLighti_gurax, "glLighti")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLighti_gurax)
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
Gurax_DeclareFunctionAlias(glLightiv_gurax, "glLightiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLightiv_gurax)
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
Gurax_DeclareFunctionAlias(glLineStipple_gurax, "glLineStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pattern", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLineStipple_gurax)
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
Gurax_DeclareFunctionAlias(glLineWidth_gurax, "glLineWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLineWidth_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat width = args.PickNumber<GLfloat>();
	// Function body
	glLineWidth(width);
	return Value::nil();
}

// opengl.glListBase(base:Number)
Gurax_DeclareFunctionAlias(glListBase_gurax, "glListBase")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glListBase_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint base = args.PickNumber<GLuint>();
	// Function body
	glListBase(base);
	return Value::nil();
}

// opengl.glLoadIdentity()
Gurax_DeclareFunctionAlias(glLoadIdentity_gurax, "glLoadIdentity")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadIdentity_gurax)
{
	// Function body
	glLoadIdentity();
	return Value::nil();
}

// opengl.glLoadMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(glLoadMatrixd_gurax, "glLoadMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadMatrixd_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glLoadMatrixd(m);
	return Value::nil();
}

// opengl.glLoadMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(glLoadMatrixf_gurax, "glLoadMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadMatrixf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glLoadMatrixf(m);
	return Value::nil();
}

// opengl.glLoadName(name:Number)
Gurax_DeclareFunctionAlias(glLoadName_gurax, "glLoadName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadName_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint name = args.PickNumber<GLuint>();
	// Function body
	glLoadName(name);
	return Value::nil();
}

// opengl.glLogicOp(opcode:Number)
Gurax_DeclareFunctionAlias(glLogicOp_gurax, "glLogicOp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("opcode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLogicOp_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum opcode = args.PickNumber<GLenum>();
	// Function body
	glLogicOp(opcode);
	return Value::nil();
}

// opengl.glMap1d(target:Number, u1:Number, u2:Number, stride:Number, order:Number, points[]:Number)
Gurax_DeclareFunctionAlias(glMap1d_gurax, "glMap1d")
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

Gurax_ImplementFunction(glMap1d_gurax)
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
Gurax_DeclareFunctionAlias(glMap1f_gurax, "glMap1f")
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

Gurax_ImplementFunction(glMap1f_gurax)
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
Gurax_DeclareFunctionAlias(glMap2d_gurax, "glMap2d")
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

Gurax_ImplementFunction(glMap2d_gurax)
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
Gurax_DeclareFunctionAlias(glMap2f_gurax, "glMap2f")
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

Gurax_ImplementFunction(glMap2f_gurax)
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
Gurax_DeclareFunctionAlias(glMapGrid1d_gurax, "glMapGrid1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMapGrid1d_gurax)
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
Gurax_DeclareFunctionAlias(glMapGrid1f_gurax, "glMapGrid1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("un", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("u2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMapGrid1f_gurax)
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
Gurax_DeclareFunctionAlias(glMapGrid2d_gurax, "glMapGrid2d")
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

Gurax_ImplementFunction(glMapGrid2d_gurax)
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
Gurax_DeclareFunctionAlias(glMapGrid2f_gurax, "glMapGrid2f")
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

Gurax_ImplementFunction(glMapGrid2f_gurax)
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
Gurax_DeclareFunctionAlias(glMaterialf_gurax, "glMaterialf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMaterialf_gurax)
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
Gurax_DeclareFunctionAlias(glMaterialfv_gurax, "glMaterialfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMaterialfv_gurax)
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
Gurax_DeclareFunctionAlias(glMateriali_gurax, "glMateriali")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMateriali_gurax)
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
Gurax_DeclareFunctionAlias(glMaterialiv_gurax, "glMaterialiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMaterialiv_gurax)
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
Gurax_DeclareFunctionAlias(glMatrixMode_gurax, "glMatrixMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMatrixMode_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glMatrixMode(mode);
	return Value::nil();
}

// opengl.glMultMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(glMultMatrixd_gurax, "glMultMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultMatrixd_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glMultMatrixd(m);
	return Value::nil();
}

// opengl.glMultMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(glMultMatrixf_gurax, "glMultMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultMatrixf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glMultMatrixf(m);
	return Value::nil();
}

// opengl.glNewList(list:Number, mode:Number)
Gurax_DeclareFunctionAlias(glNewList_gurax, "glNewList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("list", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNewList_gurax)
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
Gurax_DeclareFunctionAlias(glNormal3b_gurax, "glNormal3b")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3b_gurax)
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
Gurax_DeclareFunctionAlias(glNormal3bv_gurax, "glNormal3bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3bv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glNormal3bv(v);
	return Value::nil();
}

// opengl.glNormal3d(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(glNormal3d_gurax, "glNormal3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3d_gurax)
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
Gurax_DeclareFunctionAlias(glNormal3dv_gurax, "glNormal3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glNormal3dv(v);
	return Value::nil();
}

// opengl.glNormal3f(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(glNormal3f_gurax, "glNormal3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3f_gurax)
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
Gurax_DeclareFunctionAlias(glNormal3fv_gurax, "glNormal3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glNormal3fv(v);
	return Value::nil();
}

// opengl.glNormal3i(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(glNormal3i_gurax, "glNormal3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3i_gurax)
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
Gurax_DeclareFunctionAlias(glNormal3iv_gurax, "glNormal3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glNormal3iv(v);
	return Value::nil();
}

// opengl.glNormal3s(nx:Number, ny:Number, nz:Number)
Gurax_DeclareFunctionAlias(glNormal3s_gurax, "glNormal3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ny", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3s_gurax)
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
Gurax_DeclareFunctionAlias(glNormal3sv_gurax, "glNormal3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glNormal3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glNormal3sv(v);
	return Value::nil();
}

// opengl.glOrtho(left:Number, right:Number, bottom:Number, top:Number, zNear:Number, zFar:Number)
Gurax_DeclareFunctionAlias(glOrtho_gurax, "glOrtho")
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

Gurax_ImplementFunction(glOrtho_gurax)
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
Gurax_DeclareFunctionAlias(glPassThrough_gurax, "glPassThrough")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("token", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPassThrough_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat token = args.PickNumber<GLfloat>();
	// Function body
	glPassThrough(token);
	return Value::nil();
}

// opengl.glPixelMapfv(map:Number, mapsize:Number, values[]:Number)
Gurax_DeclareFunctionAlias(glPixelMapfv_gurax, "glPixelMapfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelMapfv_gurax)
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
Gurax_DeclareFunctionAlias(glPixelMapuiv_gurax, "glPixelMapuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelMapuiv_gurax)
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
Gurax_DeclareFunctionAlias(glPixelMapusv_gurax, "glPixelMapusv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelMapusv_gurax)
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
Gurax_DeclareFunctionAlias(glPixelStoref_gurax, "glPixelStoref")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelStoref_gurax)
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
Gurax_DeclareFunctionAlias(glPixelStorei_gurax, "glPixelStorei")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelStorei_gurax)
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
Gurax_DeclareFunctionAlias(glPixelTransferf_gurax, "glPixelTransferf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelTransferf_gurax)
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
Gurax_DeclareFunctionAlias(glPixelTransferi_gurax, "glPixelTransferi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelTransferi_gurax)
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
Gurax_DeclareFunctionAlias(glPixelZoom_gurax, "glPixelZoom")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yfactor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPixelZoom_gurax)
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
Gurax_DeclareFunctionAlias(glPointSize_gurax, "glPointSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPointSize_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat size = args.PickNumber<GLfloat>();
	// Function body
	glPointSize(size);
	return Value::nil();
}

// opengl.glPolygonMode(face:Number, mode:Number)
Gurax_DeclareFunctionAlias(glPolygonMode_gurax, "glPolygonMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPolygonMode_gurax)
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
Gurax_DeclareFunctionAlias(glPolygonOffset_gurax, "glPolygonOffset")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("units", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPolygonOffset_gurax)
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
Gurax_DeclareFunctionAlias(glPolygonStipple_gurax, "glPolygonStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPolygonStipple_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto mask = args.PickNumList<GLubyte>();
	// Function body
	glPolygonStipple(mask);
	return Value::nil();
}

// opengl.glPopAttrib()
Gurax_DeclareFunctionAlias(glPopAttrib_gurax, "glPopAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopAttrib_gurax)
{
	// Function body
	glPopAttrib();
	return Value::nil();
}

// opengl.glPopClientAttrib()
Gurax_DeclareFunctionAlias(glPopClientAttrib_gurax, "glPopClientAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopClientAttrib_gurax)
{
	// Function body
	glPopClientAttrib();
	return Value::nil();
}

// opengl.glPopMatrix()
Gurax_DeclareFunctionAlias(glPopMatrix_gurax, "glPopMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopMatrix_gurax)
{
	// Function body
	glPopMatrix();
	return Value::nil();
}

// opengl.glPopName()
Gurax_DeclareFunctionAlias(glPopName_gurax, "glPopName")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPopName_gurax)
{
	// Function body
	glPopName();
	return Value::nil();
}

// opengl.glPrioritizeTextures(n:Number, textures[]:Number, priorities[]:Number)
Gurax_DeclareFunctionAlias(glPrioritizeTextures_gurax, "glPrioritizeTextures")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textures", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("priorities", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPrioritizeTextures_gurax)
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
Gurax_DeclareFunctionAlias(glPushAttrib_gurax, "glPushAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushAttrib_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glPushAttrib(mask);
	return Value::nil();
}

// opengl.glPushClientAttrib(mask:Number)
Gurax_DeclareFunctionAlias(glPushClientAttrib_gurax, "glPushClientAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushClientAttrib_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLbitfield mask = args.PickNumber<GLbitfield>();
	// Function body
	glPushClientAttrib(mask);
	return Value::nil();
}

// opengl.glPushMatrix()
Gurax_DeclareFunctionAlias(glPushMatrix_gurax, "glPushMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushMatrix_gurax)
{
	// Function body
	glPushMatrix();
	return Value::nil();
}

// opengl.glPushName(name:Number)
Gurax_DeclareFunctionAlias(glPushName_gurax, "glPushName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPushName_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint name = args.PickNumber<GLuint>();
	// Function body
	glPushName(name);
	return Value::nil();
}

// opengl.glRasterPos2d(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glRasterPos2d_gurax, "glRasterPos2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2d_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos2dv_gurax, "glRasterPos2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos2dv(v);
	return Value::nil();
}

// opengl.glRasterPos2f(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glRasterPos2f_gurax, "glRasterPos2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2f_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos2fv_gurax, "glRasterPos2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos2fv(v);
	return Value::nil();
}

// opengl.glRasterPos2i(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glRasterPos2i_gurax, "glRasterPos2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2i_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos2iv_gurax, "glRasterPos2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos2iv(v);
	return Value::nil();
}

// opengl.glRasterPos2s(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glRasterPos2s_gurax, "glRasterPos2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2s_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos2sv_gurax, "glRasterPos2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos2sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos2sv(v);
	return Value::nil();
}

// opengl.glRasterPos3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glRasterPos3d_gurax, "glRasterPos3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3d_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos3dv_gurax, "glRasterPos3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos3dv(v);
	return Value::nil();
}

// opengl.glRasterPos3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glRasterPos3f_gurax, "glRasterPos3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3f_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos3fv_gurax, "glRasterPos3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos3fv(v);
	return Value::nil();
}

// opengl.glRasterPos3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glRasterPos3i_gurax, "glRasterPos3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3i_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos3iv_gurax, "glRasterPos3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos3iv(v);
	return Value::nil();
}

// opengl.glRasterPos3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glRasterPos3s_gurax, "glRasterPos3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3s_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos3sv_gurax, "glRasterPos3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos3sv(v);
	return Value::nil();
}

// opengl.glRasterPos4d(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glRasterPos4d_gurax, "glRasterPos4d")
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

Gurax_ImplementFunction(glRasterPos4d_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos4dv_gurax, "glRasterPos4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glRasterPos4dv(v);
	return Value::nil();
}

// opengl.glRasterPos4f(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glRasterPos4f_gurax, "glRasterPos4f")
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

Gurax_ImplementFunction(glRasterPos4f_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos4fv_gurax, "glRasterPos4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glRasterPos4fv(v);
	return Value::nil();
}

// opengl.glRasterPos4i(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glRasterPos4i_gurax, "glRasterPos4i")
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

Gurax_ImplementFunction(glRasterPos4i_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos4iv_gurax, "glRasterPos4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glRasterPos4iv(v);
	return Value::nil();
}

// opengl.glRasterPos4s(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glRasterPos4s_gurax, "glRasterPos4s")
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

Gurax_ImplementFunction(glRasterPos4s_gurax)
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
Gurax_DeclareFunctionAlias(glRasterPos4sv_gurax, "glRasterPos4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRasterPos4sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glRasterPos4sv(v);
	return Value::nil();
}

// opengl.glReadBuffer(mode:Number)
Gurax_DeclareFunctionAlias(glReadBuffer_gurax, "glReadBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glReadBuffer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glReadBuffer(mode);
	return Value::nil();
}

// opengl.glRectd(x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunctionAlias(glRectd_gurax, "glRectd")
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

Gurax_ImplementFunction(glRectd_gurax)
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
Gurax_DeclareFunctionAlias(glRectdv_gurax, "glRectdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectdv_gurax)
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
Gurax_DeclareFunctionAlias(glRectf_gurax, "glRectf")
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

Gurax_ImplementFunction(glRectf_gurax)
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
Gurax_DeclareFunctionAlias(glRectfv_gurax, "glRectfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectfv_gurax)
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
Gurax_DeclareFunctionAlias(glRecti_gurax, "glRecti")
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

Gurax_ImplementFunction(glRecti_gurax)
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
Gurax_DeclareFunctionAlias(glRectiv_gurax, "glRectiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectiv_gurax)
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
Gurax_DeclareFunctionAlias(glRects_gurax, "glRects")
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

Gurax_ImplementFunction(glRects_gurax)
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
Gurax_DeclareFunctionAlias(glRectsv_gurax, "glRectsv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRectsv_gurax)
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
Gurax_DeclareFunctionAlias(glRenderMode_gurax, "glRenderMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glRenderMode_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	GLint rtn = glRenderMode(mode);
	return new Value_Number(rtn);
}

// opengl.glRotated(angle:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glRotated_gurax, "glRotated")
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

Gurax_ImplementFunction(glRotated_gurax)
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
Gurax_DeclareFunctionAlias(glRotatef_gurax, "glRotatef")
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

Gurax_ImplementFunction(glRotatef_gurax)
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
Gurax_DeclareFunctionAlias(glScaled_gurax, "glScaled")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glScaled_gurax)
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
Gurax_DeclareFunctionAlias(glScalef_gurax, "glScalef")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glScalef_gurax)
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
Gurax_DeclareFunctionAlias(glScissor_gurax, "glScissor")
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

Gurax_ImplementFunction(glScissor_gurax)
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
Gurax_DeclareFunctionAlias(glShadeModel_gurax, "glShadeModel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glShadeModel_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glShadeModel(mode);
	return Value::nil();
}

// opengl.glStencilFunc(func:Number, ref:Number, mask:Number)
Gurax_DeclareFunctionAlias(glStencilFunc_gurax, "glStencilFunc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("func", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilFunc_gurax)
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
Gurax_DeclareFunctionAlias(glStencilMask_gurax, "glStencilMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilMask_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glStencilMask(mask);
	return Value::nil();
}

// opengl.glStencilOp(fail:Number, zfail:Number, zpass:Number)
Gurax_DeclareFunctionAlias(glStencilOp_gurax, "glStencilOp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zfail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zpass", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilOp_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord1d_gurax, "glTexCoord1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble s = args.PickNumber<GLdouble>();
	// Function body
	glTexCoord1d(s);
	return Value::nil();
}

// opengl.glTexCoord1dv(v[]:Number)
Gurax_DeclareFunctionAlias(glTexCoord1dv_gurax, "glTexCoord1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord1dv(v);
	return Value::nil();
}

// opengl.glTexCoord1f(s:Number)
Gurax_DeclareFunctionAlias(glTexCoord1f_gurax, "glTexCoord1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat s = args.PickNumber<GLfloat>();
	// Function body
	glTexCoord1f(s);
	return Value::nil();
}

// opengl.glTexCoord1fv(v[]:Number)
Gurax_DeclareFunctionAlias(glTexCoord1fv_gurax, "glTexCoord1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord1fv(v);
	return Value::nil();
}

// opengl.glTexCoord1i(s:Number)
Gurax_DeclareFunctionAlias(glTexCoord1i_gurax, "glTexCoord1i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint s = args.PickNumber<GLint>();
	// Function body
	glTexCoord1i(s);
	return Value::nil();
}

// opengl.glTexCoord1iv(v[]:Number)
Gurax_DeclareFunctionAlias(glTexCoord1iv_gurax, "glTexCoord1iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord1iv(v);
	return Value::nil();
}

// opengl.glTexCoord1s(s:Number)
Gurax_DeclareFunctionAlias(glTexCoord1s_gurax, "glTexCoord1s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLshort s = args.PickNumber<GLshort>();
	// Function body
	glTexCoord1s(s);
	return Value::nil();
}

// opengl.glTexCoord1sv(v[]:Number)
Gurax_DeclareFunctionAlias(glTexCoord1sv_gurax, "glTexCoord1sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord1sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord1sv(v);
	return Value::nil();
}

// opengl.glTexCoord2d(s:Number, t:Number)
Gurax_DeclareFunctionAlias(glTexCoord2d_gurax, "glTexCoord2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2d_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord2dv_gurax, "glTexCoord2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord2dv(v);
	return Value::nil();
}

// opengl.glTexCoord2f(s:Number, t:Number)
Gurax_DeclareFunctionAlias(glTexCoord2f_gurax, "glTexCoord2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2f_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord2fv_gurax, "glTexCoord2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord2fv(v);
	return Value::nil();
}

// opengl.glTexCoord2i(s:Number, t:Number)
Gurax_DeclareFunctionAlias(glTexCoord2i_gurax, "glTexCoord2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2i_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord2iv_gurax, "glTexCoord2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord2iv(v);
	return Value::nil();
}

// opengl.glTexCoord2s(s:Number, t:Number)
Gurax_DeclareFunctionAlias(glTexCoord2s_gurax, "glTexCoord2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2s_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord2sv_gurax, "glTexCoord2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord2sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord2sv(v);
	return Value::nil();
}

// opengl.glTexCoord3d(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(glTexCoord3d_gurax, "glTexCoord3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3d_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord3dv_gurax, "glTexCoord3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord3dv(v);
	return Value::nil();
}

// opengl.glTexCoord3f(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(glTexCoord3f_gurax, "glTexCoord3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3f_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord3fv_gurax, "glTexCoord3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord3fv(v);
	return Value::nil();
}

// opengl.glTexCoord3i(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(glTexCoord3i_gurax, "glTexCoord3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3i_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord3iv_gurax, "glTexCoord3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord3iv(v);
	return Value::nil();
}

// opengl.glTexCoord3s(s:Number, t:Number, r:Number)
Gurax_DeclareFunctionAlias(glTexCoord3s_gurax, "glTexCoord3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3s_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord3sv_gurax, "glTexCoord3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord3sv(v);
	return Value::nil();
}

// opengl.glTexCoord4d(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(glTexCoord4d_gurax, "glTexCoord4d")
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

Gurax_ImplementFunction(glTexCoord4d_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord4dv_gurax, "glTexCoord4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glTexCoord4dv(v);
	return Value::nil();
}

// opengl.glTexCoord4f(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(glTexCoord4f_gurax, "glTexCoord4f")
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

Gurax_ImplementFunction(glTexCoord4f_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord4fv_gurax, "glTexCoord4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glTexCoord4fv(v);
	return Value::nil();
}

// opengl.glTexCoord4i(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(glTexCoord4i_gurax, "glTexCoord4i")
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

Gurax_ImplementFunction(glTexCoord4i_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord4iv_gurax, "glTexCoord4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glTexCoord4iv(v);
	return Value::nil();
}

// opengl.glTexCoord4s(s:Number, t:Number, r:Number, q:Number)
Gurax_DeclareFunctionAlias(glTexCoord4s_gurax, "glTexCoord4s")
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

Gurax_ImplementFunction(glTexCoord4s_gurax)
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
Gurax_DeclareFunctionAlias(glTexCoord4sv_gurax, "glTexCoord4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexCoord4sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glTexCoord4sv(v);
	return Value::nil();
}

// opengl.glTexEnvf(target:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glTexEnvf_gurax, "glTexEnvf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnvf_gurax)
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
Gurax_DeclareFunctionAlias(glTexEnvfv_gurax, "glTexEnvfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnvfv_gurax)
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
Gurax_DeclareFunctionAlias(glTexEnvi_gurax, "glTexEnvi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnvi_gurax)
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
Gurax_DeclareFunctionAlias(glTexEnviv_gurax, "glTexEnviv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexEnviv_gurax)
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
Gurax_DeclareFunctionAlias(glTexGend_gurax, "glTexGend")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGend_gurax)
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
Gurax_DeclareFunctionAlias(glTexGendv_gurax, "glTexGendv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGendv_gurax)
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
Gurax_DeclareFunctionAlias(glTexGenf_gurax, "glTexGenf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGenf_gurax)
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
Gurax_DeclareFunctionAlias(glTexGenfv_gurax, "glTexGenfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGenfv_gurax)
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
Gurax_DeclareFunctionAlias(glTexGeni_gurax, "glTexGeni")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGeni_gurax)
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
Gurax_DeclareFunctionAlias(glTexGeniv_gurax, "glTexGeniv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexGeniv_gurax)
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
Gurax_DeclareFunctionAlias(glTexParameterf_gurax, "glTexParameterf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameterf_gurax)
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
Gurax_DeclareFunctionAlias(glTexParameterfv_gurax, "glTexParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameterfv_gurax)
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
Gurax_DeclareFunctionAlias(glTexParameteri_gurax, "glTexParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameteri_gurax)
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
Gurax_DeclareFunctionAlias(glTexParameteriv_gurax, "glTexParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameteriv_gurax)
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
Gurax_DeclareFunctionAlias(glTranslated_gurax, "glTranslated")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTranslated_gurax)
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
Gurax_DeclareFunctionAlias(glTranslatef_gurax, "glTranslatef")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTranslatef_gurax)
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
Gurax_DeclareFunctionAlias(glVertex2d_gurax, "glVertex2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2d_gurax)
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
Gurax_DeclareFunctionAlias(glVertex2dv_gurax, "glVertex2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex2dv(v);
	return Value::nil();
}

// opengl.glVertex2f(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glVertex2f_gurax, "glVertex2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2f_gurax)
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
Gurax_DeclareFunctionAlias(glVertex2fv_gurax, "glVertex2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex2fv(v);
	return Value::nil();
}

// opengl.glVertex2i(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glVertex2i_gurax, "glVertex2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2i_gurax)
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
Gurax_DeclareFunctionAlias(glVertex2iv_gurax, "glVertex2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex2iv(v);
	return Value::nil();
}

// opengl.glVertex2s(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glVertex2s_gurax, "glVertex2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2s_gurax)
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
Gurax_DeclareFunctionAlias(glVertex2sv_gurax, "glVertex2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex2sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex2sv(v);
	return Value::nil();
}

// opengl.glVertex3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertex3d_gurax, "glVertex3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3d_gurax)
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
Gurax_DeclareFunctionAlias(glVertex3dv_gurax, "glVertex3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex3dv(v);
	return Value::nil();
}

// opengl.glVertex3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertex3f_gurax, "glVertex3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3f_gurax)
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
Gurax_DeclareFunctionAlias(glVertex3fv_gurax, "glVertex3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex3fv(v);
	return Value::nil();
}

// opengl.glVertex3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertex3i_gurax, "glVertex3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3i_gurax)
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
Gurax_DeclareFunctionAlias(glVertex3iv_gurax, "glVertex3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex3iv(v);
	return Value::nil();
}

// opengl.glVertex3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertex3s_gurax, "glVertex3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3s_gurax)
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
Gurax_DeclareFunctionAlias(glVertex3sv_gurax, "glVertex3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex3sv(v);
	return Value::nil();
}

// opengl.glVertex4d(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertex4d_gurax, "glVertex4d")
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

Gurax_ImplementFunction(glVertex4d_gurax)
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
Gurax_DeclareFunctionAlias(glVertex4dv_gurax, "glVertex4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertex4dv(v);
	return Value::nil();
}

// opengl.glVertex4f(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertex4f_gurax, "glVertex4f")
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

Gurax_ImplementFunction(glVertex4f_gurax)
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
Gurax_DeclareFunctionAlias(glVertex4fv_gurax, "glVertex4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertex4fv(v);
	return Value::nil();
}

// opengl.glVertex4i(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertex4i_gurax, "glVertex4i")
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

Gurax_ImplementFunction(glVertex4i_gurax)
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
Gurax_DeclareFunctionAlias(glVertex4iv_gurax, "glVertex4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertex4iv(v);
	return Value::nil();
}

// opengl.glVertex4s(x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertex4s_gurax, "glVertex4s")
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

Gurax_ImplementFunction(glVertex4s_gurax)
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
Gurax_DeclareFunctionAlias(glVertex4sv_gurax, "glVertex4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertex4sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertex4sv(v);
	return Value::nil();
}

// opengl.glViewport(x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glViewport_gurax, "glViewport")
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

Gurax_ImplementFunction(glViewport_gurax)
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
Gurax_DeclareFunctionAlias(glCopyTexSubImage3D_gurax, "glCopyTexSubImage3D")
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

Gurax_ImplementFunction(glCopyTexSubImage3D_gurax)
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

// opengl.glDrawRangeElements(mode:Number, start:Number, end:Number, count:Number, type:Number, indices:Pointer)
Gurax_DeclareFunctionAlias(glDrawRangeElements_gurax, "glDrawRangeElements")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("start", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("end", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawRangeElements_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLuint start = args.PickNumber<GLuint>();
	GLuint end = args.PickNumber<GLuint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLenum type = args.PickNumber<GLenum>();
	const void* indices = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawRangeElements(mode, start, end, count, type, indices);
	return Value::nil();
}

// opengl.glTexImage3D(target:Number, level:Number, internalFormat:Number, width:Number, height:Number, depth:Number, border:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTexImage3D_gurax, "glTexImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalFormat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexImage3D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint internalFormat = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLsizei depth = args.PickNumber<GLsizei>();
	GLint border = args.PickNumber<GLint>();
	GLenum format = args.PickNumber<GLenum>();
	GLenum type = args.PickNumber<GLenum>();
	const void* pixels = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels);
	return Value::nil();
}

// opengl.glTexSubImage3D(target:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTexSubImage3D_gurax, "glTexSubImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexSubImage3D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLint yoffset = args.PickNumber<GLint>();
	GLint zoffset = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLsizei depth = args.PickNumber<GLsizei>();
	GLenum format = args.PickNumber<GLenum>();
	GLenum type = args.PickNumber<GLenum>();
	const void* pixels = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	return Value::nil();
}

// opengl.glActiveTexture(texture:Number)
Gurax_DeclareFunctionAlias(glActiveTexture_gurax, "glActiveTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glActiveTexture_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum texture = args.PickNumber<GLenum>();
	// Function body
	glActiveTexture(texture);
	return Value::nil();
}

// opengl.glClientActiveTexture(texture:Number)
Gurax_DeclareFunctionAlias(glClientActiveTexture_gurax, "glClientActiveTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClientActiveTexture_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum texture = args.PickNumber<GLenum>();
	// Function body
	glClientActiveTexture(texture);
	return Value::nil();
}

// opengl.glCompressedTexImage1D(target:Number, level:Number, internalformat:Number, width:Number, border:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTexImage1D_gurax, "glCompressedTexImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompressedTexImage1D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLenum internalformat = args.PickNumber<GLenum>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLint border = args.PickNumber<GLint>();
	GLsizei imageSize = args.PickNumber<GLsizei>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	return Value::nil();
}

// opengl.glCompressedTexImage2D(target:Number, level:Number, internalformat:Number, width:Number, height:Number, border:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTexImage2D_gurax, "glCompressedTexImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompressedTexImage2D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLenum internalformat = args.PickNumber<GLenum>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLint border = args.PickNumber<GLint>();
	GLsizei imageSize = args.PickNumber<GLsizei>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	return Value::nil();
}

// opengl.glCompressedTexImage3D(target:Number, level:Number, internalformat:Number, width:Number, height:Number, depth:Number, border:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTexImage3D_gurax, "glCompressedTexImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompressedTexImage3D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLenum internalformat = args.PickNumber<GLenum>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLsizei depth = args.PickNumber<GLsizei>();
	GLint border = args.PickNumber<GLint>();
	GLsizei imageSize = args.PickNumber<GLsizei>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	return Value::nil();
}

// opengl.glCompressedTexSubImage1D(target:Number, level:Number, xoffset:Number, width:Number, format:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTexSubImage1D_gurax, "glCompressedTexSubImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompressedTexSubImage1D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLenum format = args.PickNumber<GLenum>();
	GLsizei imageSize = args.PickNumber<GLsizei>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	return Value::nil();
}

// opengl.glCompressedTexSubImage2D(target:Number, level:Number, xoffset:Number, yoffset:Number, width:Number, height:Number, format:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTexSubImage2D_gurax, "glCompressedTexSubImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompressedTexSubImage2D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLint yoffset = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLenum format = args.PickNumber<GLenum>();
	GLsizei imageSize = args.PickNumber<GLsizei>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	return Value::nil();
}

// opengl.glCompressedTexSubImage3D(target:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, format:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTexSubImage3D_gurax, "glCompressedTexSubImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompressedTexSubImage3D_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLint level = args.PickNumber<GLint>();
	GLint xoffset = args.PickNumber<GLint>();
	GLint yoffset = args.PickNumber<GLint>();
	GLint zoffset = args.PickNumber<GLint>();
	GLsizei width = args.PickNumber<GLsizei>();
	GLsizei height = args.PickNumber<GLsizei>();
	GLsizei depth = args.PickNumber<GLsizei>();
	GLenum format = args.PickNumber<GLenum>();
	GLsizei imageSize = args.PickNumber<GLsizei>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	return Value::nil();
}

// opengl.glLoadTransposeMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(glLoadTransposeMatrixd_gurax, "glLoadTransposeMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadTransposeMatrixd_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glLoadTransposeMatrixd(m);
	return Value::nil();
}

// opengl.glLoadTransposeMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(glLoadTransposeMatrixf_gurax, "glLoadTransposeMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLoadTransposeMatrixf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glLoadTransposeMatrixf(m);
	return Value::nil();
}

// opengl.glMultTransposeMatrixd(m[]:Number)
Gurax_DeclareFunctionAlias(glMultTransposeMatrixd_gurax, "glMultTransposeMatrixd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultTransposeMatrixd_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLdouble>();
	// Function body
	glMultTransposeMatrixd(m);
	return Value::nil();
}

// opengl.glMultTransposeMatrixf(m[]:Number)
Gurax_DeclareFunctionAlias(glMultTransposeMatrixf_gurax, "glMultTransposeMatrixf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultTransposeMatrixf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto m = args.PickNumList<GLfloat>();
	// Function body
	glMultTransposeMatrixf(m);
	return Value::nil();
}

// opengl.glMultiTexCoord1d(target:Number, s:Number)
Gurax_DeclareFunctionAlias(glMultiTexCoord1d_gurax, "glMultiTexCoord1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1d_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1dv_gurax, "glMultiTexCoord1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1dv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1f_gurax, "glMultiTexCoord1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1f_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1fv_gurax, "glMultiTexCoord1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1fv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1i_gurax, "glMultiTexCoord1i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1i_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1iv_gurax, "glMultiTexCoord1iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1iv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1s_gurax, "glMultiTexCoord1s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1s_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord1sv_gurax, "glMultiTexCoord1sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord1sv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2d_gurax, "glMultiTexCoord2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2d_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2dv_gurax, "glMultiTexCoord2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2dv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2f_gurax, "glMultiTexCoord2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2f_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2fv_gurax, "glMultiTexCoord2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2fv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2i_gurax, "glMultiTexCoord2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2i_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2iv_gurax, "glMultiTexCoord2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2iv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2s_gurax, "glMultiTexCoord2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2s_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord2sv_gurax, "glMultiTexCoord2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord2sv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3d_gurax, "glMultiTexCoord3d")
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

Gurax_ImplementFunction(glMultiTexCoord3d_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3dv_gurax, "glMultiTexCoord3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord3dv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3f_gurax, "glMultiTexCoord3f")
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

Gurax_ImplementFunction(glMultiTexCoord3f_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3fv_gurax, "glMultiTexCoord3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord3fv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3i_gurax, "glMultiTexCoord3i")
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

Gurax_ImplementFunction(glMultiTexCoord3i_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3iv_gurax, "glMultiTexCoord3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord3iv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3s_gurax, "glMultiTexCoord3s")
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

Gurax_ImplementFunction(glMultiTexCoord3s_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord3sv_gurax, "glMultiTexCoord3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord3sv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4d_gurax, "glMultiTexCoord4d")
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

Gurax_ImplementFunction(glMultiTexCoord4d_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4dv_gurax, "glMultiTexCoord4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord4dv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4f_gurax, "glMultiTexCoord4f")
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

Gurax_ImplementFunction(glMultiTexCoord4f_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4fv_gurax, "glMultiTexCoord4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord4fv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4i_gurax, "glMultiTexCoord4i")
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

Gurax_ImplementFunction(glMultiTexCoord4i_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4iv_gurax, "glMultiTexCoord4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord4iv_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4s_gurax, "glMultiTexCoord4s")
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

Gurax_ImplementFunction(glMultiTexCoord4s_gurax)
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
Gurax_DeclareFunctionAlias(glMultiTexCoord4sv_gurax, "glMultiTexCoord4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiTexCoord4sv_gurax)
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
Gurax_DeclareFunctionAlias(glSampleCoverage_gurax, "glSampleCoverage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("invert", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSampleCoverage_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLclampf value = args.PickNumber<GLclampf>();
	GLboolean invert = static_cast<GLboolean>(args.PickBool());
	// Function body
	glSampleCoverage(value, invert);
	return Value::nil();
}

// opengl.glBlendColor(red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(glBlendColor_gurax, "glBlendColor")
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

Gurax_ImplementFunction(glBlendColor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLclampf red = args.PickNumber<GLclampf>();
	GLclampf green = args.PickNumber<GLclampf>();
	GLclampf blue = args.PickNumber<GLclampf>();
	GLclampf alpha = args.PickNumber<GLclampf>();
	// Function body
	glBlendColor(red, green, blue, alpha);
	return Value::nil();
}

// opengl.glBlendEquation(mode:Number)
Gurax_DeclareFunctionAlias(glBlendEquation_gurax, "glBlendEquation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendEquation_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glBlendEquation(mode);
	return Value::nil();
}

// opengl.glBlendFuncSeparate(sfactorRGB:Number, dfactorRGB:Number, sfactorAlpha:Number, dfactorAlpha:Number)
Gurax_DeclareFunctionAlias(glBlendFuncSeparate_gurax, "glBlendFuncSeparate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sfactorRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dfactorRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sfactorAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dfactorAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendFuncSeparate_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum sfactorRGB = args.PickNumber<GLenum>();
	GLenum dfactorRGB = args.PickNumber<GLenum>();
	GLenum sfactorAlpha = args.PickNumber<GLenum>();
	GLenum dfactorAlpha = args.PickNumber<GLenum>();
	// Function body
	glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	return Value::nil();
}

// opengl.glFogCoordPointer(type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glFogCoordPointer_gurax, "glFogCoordPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogCoordPointer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum type = args.PickNumber<GLenum>();
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glFogCoordPointer(type, stride, pointer);
	return Value::nil();
}

// opengl.glFogCoordd(coord:Number)
Gurax_DeclareFunctionAlias(glFogCoordd_gurax, "glFogCoordd")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogCoordd_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble coord = args.PickNumber<GLdouble>();
	// Function body
	glFogCoordd(coord);
	return Value::nil();
}

// opengl.glFogCoorddv(coord[]:Number)
Gurax_DeclareFunctionAlias(glFogCoorddv_gurax, "glFogCoorddv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogCoorddv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto coord = args.PickNumList<GLdouble>();
	// Function body
	glFogCoorddv(coord);
	return Value::nil();
}

// opengl.glFogCoordf(coord:Number)
Gurax_DeclareFunctionAlias(glFogCoordf_gurax, "glFogCoordf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogCoordf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat coord = args.PickNumber<GLfloat>();
	// Function body
	glFogCoordf(coord);
	return Value::nil();
}

// opengl.glFogCoordfv(coord[]:Number)
Gurax_DeclareFunctionAlias(glFogCoordfv_gurax, "glFogCoordfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFogCoordfv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto coord = args.PickNumList<GLfloat>();
	// Function body
	glFogCoordfv(coord);
	return Value::nil();
}

// opengl.glMultiDrawArrays(mode:Number, first[]:Number, count[]:Number, drawcount:Number)
Gurax_DeclareFunctionAlias(glMultiDrawArrays_gurax, "glMultiDrawArrays")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("drawcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMultiDrawArrays_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	auto first = args.PickNumList<GLint>();
	auto count = args.PickNumList<GLsizei>();
	GLsizei drawcount = args.PickNumber<GLsizei>();
	// Function body
	glMultiDrawArrays(mode, first, count, drawcount);
	return Value::nil();
}

// opengl.glPointParameterf(pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glPointParameterf_gurax, "glPointParameterf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPointParameterf_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLfloat param = args.PickNumber<GLfloat>();
	// Function body
	glPointParameterf(pname, param);
	return Value::nil();
}

// opengl.glPointParameterfv(pname:Number, params[]:Number)
Gurax_DeclareFunctionAlias(glPointParameterfv_gurax, "glPointParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPointParameterfv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLfloat>();
	// Function body
	glPointParameterfv(pname, params);
	return Value::nil();
}

// opengl.glPointParameteri(pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glPointParameteri_gurax, "glPointParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPointParameteri_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	GLint param = args.PickNumber<GLint>();
	// Function body
	glPointParameteri(pname, param);
	return Value::nil();
}

// opengl.glPointParameteriv(pname:Number, params[]:Number)
Gurax_DeclareFunctionAlias(glPointParameteriv_gurax, "glPointParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPointParameteriv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glPointParameteriv(pname, params);
	return Value::nil();
}

// opengl.glSecondaryColor3b(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3b_gurax, "glSecondaryColor3b")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3b_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLbyte red = args.PickNumber<GLbyte>();
	GLbyte green = args.PickNumber<GLbyte>();
	GLbyte blue = args.PickNumber<GLbyte>();
	// Function body
	glSecondaryColor3b(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3bv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3bv_gurax, "glSecondaryColor3bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3bv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glSecondaryColor3bv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3d(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3d_gurax, "glSecondaryColor3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble red = args.PickNumber<GLdouble>();
	GLdouble green = args.PickNumber<GLdouble>();
	GLdouble blue = args.PickNumber<GLdouble>();
	// Function body
	glSecondaryColor3d(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3dv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3dv_gurax, "glSecondaryColor3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glSecondaryColor3dv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3f(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3f_gurax, "glSecondaryColor3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat red = args.PickNumber<GLfloat>();
	GLfloat green = args.PickNumber<GLfloat>();
	GLfloat blue = args.PickNumber<GLfloat>();
	// Function body
	glSecondaryColor3f(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3fv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3fv_gurax, "glSecondaryColor3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glSecondaryColor3fv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3i(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3i_gurax, "glSecondaryColor3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint red = args.PickNumber<GLint>();
	GLint green = args.PickNumber<GLint>();
	GLint blue = args.PickNumber<GLint>();
	// Function body
	glSecondaryColor3i(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3iv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3iv_gurax, "glSecondaryColor3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLint>();
	// Function body
	glSecondaryColor3iv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3s(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3s_gurax, "glSecondaryColor3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLshort red = args.PickNumber<GLshort>();
	GLshort green = args.PickNumber<GLshort>();
	GLshort blue = args.PickNumber<GLshort>();
	// Function body
	glSecondaryColor3s(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3sv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3sv_gurax, "glSecondaryColor3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLshort>();
	// Function body
	glSecondaryColor3sv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3ub(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3ub_gurax, "glSecondaryColor3ub")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3ub_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLubyte red = args.PickNumber<GLubyte>();
	GLubyte green = args.PickNumber<GLubyte>();
	GLubyte blue = args.PickNumber<GLubyte>();
	// Function body
	glSecondaryColor3ub(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3ubv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3ubv_gurax, "glSecondaryColor3ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3ubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glSecondaryColor3ubv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3ui(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3ui_gurax, "glSecondaryColor3ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint red = args.PickNumber<GLuint>();
	GLuint green = args.PickNumber<GLuint>();
	GLuint blue = args.PickNumber<GLuint>();
	// Function body
	glSecondaryColor3ui(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3uiv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3uiv_gurax, "glSecondaryColor3uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLuint>();
	// Function body
	glSecondaryColor3uiv(v);
	return Value::nil();
}

// opengl.glSecondaryColor3us(red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3us_gurax, "glSecondaryColor3us")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3us_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLushort red = args.PickNumber<GLushort>();
	GLushort green = args.PickNumber<GLushort>();
	GLushort blue = args.PickNumber<GLushort>();
	// Function body
	glSecondaryColor3us(red, green, blue);
	return Value::nil();
}

// opengl.glSecondaryColor3usv(v[]:Number)
Gurax_DeclareFunctionAlias(glSecondaryColor3usv_gurax, "glSecondaryColor3usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColor3usv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto v = args.PickNumList<GLushort>();
	// Function body
	glSecondaryColor3usv(v);
	return Value::nil();
}

// opengl.glSecondaryColorPointer(size:Number, type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glSecondaryColorPointer_gurax, "glSecondaryColorPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSecondaryColorPointer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint size = args.PickNumber<GLint>();
	GLenum type = args.PickNumber<GLenum>();
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glSecondaryColorPointer(size, type, stride, pointer);
	return Value::nil();
}

// opengl.glWindowPos2d(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glWindowPos2d_gurax, "glWindowPos2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	// Function body
	glWindowPos2d(x, y);
	return Value::nil();
}

// opengl.glWindowPos2dv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos2dv_gurax, "glWindowPos2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLdouble>();
	// Function body
	glWindowPos2dv(p);
	return Value::nil();
}

// opengl.glWindowPos2f(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glWindowPos2f_gurax, "glWindowPos2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	// Function body
	glWindowPos2f(x, y);
	return Value::nil();
}

// opengl.glWindowPos2fv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos2fv_gurax, "glWindowPos2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLfloat>();
	// Function body
	glWindowPos2fv(p);
	return Value::nil();
}

// opengl.glWindowPos2i(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glWindowPos2i_gurax, "glWindowPos2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	// Function body
	glWindowPos2i(x, y);
	return Value::nil();
}

// opengl.glWindowPos2iv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos2iv_gurax, "glWindowPos2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLint>();
	// Function body
	glWindowPos2iv(p);
	return Value::nil();
}

// opengl.glWindowPos2s(x:Number, y:Number)
Gurax_DeclareFunctionAlias(glWindowPos2s_gurax, "glWindowPos2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	// Function body
	glWindowPos2s(x, y);
	return Value::nil();
}

// opengl.glWindowPos2sv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos2sv_gurax, "glWindowPos2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos2sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLshort>();
	// Function body
	glWindowPos2sv(p);
	return Value::nil();
}

// opengl.glWindowPos3d(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glWindowPos3d_gurax, "glWindowPos3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glWindowPos3d(x, y, z);
	return Value::nil();
}

// opengl.glWindowPos3dv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos3dv_gurax, "glWindowPos3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLdouble>();
	// Function body
	glWindowPos3dv(p);
	return Value::nil();
}

// opengl.glWindowPos3f(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glWindowPos3f_gurax, "glWindowPos3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glWindowPos3f(x, y, z);
	return Value::nil();
}

// opengl.glWindowPos3fv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos3fv_gurax, "glWindowPos3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLfloat>();
	// Function body
	glWindowPos3fv(p);
	return Value::nil();
}

// opengl.glWindowPos3i(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glWindowPos3i_gurax, "glWindowPos3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint x = args.PickNumber<GLint>();
	GLint y = args.PickNumber<GLint>();
	GLint z = args.PickNumber<GLint>();
	// Function body
	glWindowPos3i(x, y, z);
	return Value::nil();
}

// opengl.glWindowPos3iv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos3iv_gurax, "glWindowPos3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLint>();
	// Function body
	glWindowPos3iv(p);
	return Value::nil();
}

// opengl.glWindowPos3s(x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glWindowPos3s_gurax, "glWindowPos3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	// Function body
	glWindowPos3s(x, y, z);
	return Value::nil();
}

// opengl.glWindowPos3sv(p[]:Number)
Gurax_DeclareFunctionAlias(glWindowPos3sv_gurax, "glWindowPos3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glWindowPos3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	auto p = args.PickNumList<GLshort>();
	// Function body
	glWindowPos3sv(p);
	return Value::nil();
}

// opengl.glBeginQuery(target:Number, id:Number)
Gurax_DeclareFunctionAlias(glBeginQuery_gurax, "glBeginQuery")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBeginQuery_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLuint id = args.PickNumber<GLuint>();
	// Function body
	glBeginQuery(target, id);
	return Value::nil();
}

// opengl.glBindBuffer(target:Number, buffer:Number)
Gurax_DeclareFunctionAlias(glBindBuffer_gurax, "glBindBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBindBuffer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLuint buffer = args.PickNumber<GLuint>();
	// Function body
	glBindBuffer(target, buffer);
	return Value::nil();
}

// opengl.glBufferData(target:Number, size:Number, data:Pointer, usage:Number)
Gurax_DeclareFunctionAlias(glBufferData_gurax, "glBufferData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("usage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBufferData_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLsizeiptr size = args.PickNumber<GLsizeiptr>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLenum usage = args.PickNumber<GLenum>();
	// Function body
	glBufferData(target, size, data, usage);
	return Value::nil();
}

// opengl.glBufferSubData(target:Number, offset:Number, size:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glBufferSubData_gurax, "glBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBufferSubData_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLintptr offset = args.PickNumber<GLintptr>();
	GLsizeiptr size = args.PickNumber<GLsizeiptr>();
	const void* data = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glBufferSubData(target, offset, size, data);
	return Value::nil();
}

// opengl.glDeleteBuffers(n:Number, buffers[]:Number)
Gurax_DeclareFunctionAlias(glDeleteBuffers_gurax, "glDeleteBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffers", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteBuffers_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	auto buffers = args.PickNumList<GLuint>();
	// Function body
	glDeleteBuffers(n, buffers);
	return Value::nil();
}

// opengl.glDeleteQueries(n:Number, ids[]:Number)
Gurax_DeclareFunctionAlias(glDeleteQueries_gurax, "glDeleteQueries")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ids", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteQueries_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	auto ids = args.PickNumList<GLuint>();
	// Function body
	glDeleteQueries(n, ids);
	return Value::nil();
}

// opengl.glEndQuery(target:Number)
Gurax_DeclareFunctionAlias(glEndQuery_gurax, "glEndQuery")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEndQuery_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	// Function body
	glEndQuery(target);
	return Value::nil();
}

// opengl.glGenBuffers(n:Number)
Gurax_DeclareFunctionAlias(glGenBuffers_gurax, "glGenBuffers")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGenBuffers_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	// Function body
	std::unique_ptr<GLuint []> buffers(new GLuint [n]);
	glGenBuffers(n, buffers.get());
	return Value_List::Create(buffers.get(), n);
}

// opengl.glGenQueries(n:Number)
Gurax_DeclareFunctionAlias(glGenQueries_gurax, "glGenQueries")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGenQueries_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	// Function body
	std::unique_ptr<GLuint []> ids(new GLuint [n]);
	glGenQueries(n, ids.get());
	return Value_List::Create(ids.get(), n);
}

// opengl.glIsBuffer(buffer:Number)
Gurax_DeclareFunctionAlias(glIsBuffer_gurax, "glIsBuffer")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsBuffer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buffer = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsBuffer(buffer);
	return new Value_Bool(!!rtn);
}

// opengl.glIsQuery(id:Number)
Gurax_DeclareFunctionAlias(glIsQuery_gurax, "glIsQuery")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsQuery_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint id = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsQuery(id);
	return new Value_Bool(!!rtn);
}

// opengl.glUnmapBuffer(target:Number)
Gurax_DeclareFunctionAlias(glUnmapBuffer_gurax, "glUnmapBuffer")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUnmapBuffer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	// Function body
	GLboolean rtn = glUnmapBuffer(target);
	return new Value_Bool(!!rtn);
}

// opengl.glAttachShader(program:Number, shader:Number)
Gurax_DeclareFunctionAlias(glAttachShader_gurax, "glAttachShader")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glAttachShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	GLuint shader = args.PickNumber<GLuint>();
	// Function body
	glAttachShader(program, shader);
	return Value::nil();
}

// opengl.glBlendEquationSeparate(modeRGB:Number, modeAlpha:Number)
Gurax_DeclareFunctionAlias(glBlendEquationSeparate_gurax, "glBlendEquationSeparate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("modeRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendEquationSeparate_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum modeRGB = args.PickNumber<GLenum>();
	GLenum modeAlpha = args.PickNumber<GLenum>();
	// Function body
	glBlendEquationSeparate(modeRGB, modeAlpha);
	return Value::nil();
}

// opengl.glCompileShader(shader:Number)
Gurax_DeclareFunctionAlias(glCompileShader_gurax, "glCompileShader")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCompileShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint shader = args.PickNumber<GLuint>();
	// Function body
	glCompileShader(shader);
	return Value::nil();
}

// opengl.glCreateProgram()
Gurax_DeclareFunctionAlias(glCreateProgram_gurax, "glCreateProgram")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCreateProgram_gurax)
{
	// Function body
	GLuint rtn = glCreateProgram();
	return new Value_Number(rtn);
}

// opengl.glCreateShader(type:Number)
Gurax_DeclareFunctionAlias(glCreateShader_gurax, "glCreateShader")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glCreateShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum type = args.PickNumber<GLenum>();
	// Function body
	GLuint rtn = glCreateShader(type);
	return new Value_Number(rtn);
}

// opengl.glDeleteProgram(program:Number)
Gurax_DeclareFunctionAlias(glDeleteProgram_gurax, "glDeleteProgram")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteProgram_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	// Function body
	glDeleteProgram(program);
	return Value::nil();
}

// opengl.glDeleteShader(shader:Number)
Gurax_DeclareFunctionAlias(glDeleteShader_gurax, "glDeleteShader")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDeleteShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint shader = args.PickNumber<GLuint>();
	// Function body
	glDeleteShader(shader);
	return Value::nil();
}

// opengl.glDetachShader(program:Number, shader:Number)
Gurax_DeclareFunctionAlias(glDetachShader_gurax, "glDetachShader")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDetachShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	GLuint shader = args.PickNumber<GLuint>();
	// Function body
	glDetachShader(program, shader);
	return Value::nil();
}

// opengl.glDisableVertexAttribArray(index:Number)
Gurax_DeclareFunctionAlias(glDisableVertexAttribArray_gurax, "glDisableVertexAttribArray")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDisableVertexAttribArray_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	// Function body
	glDisableVertexAttribArray(index);
	return Value::nil();
}

// opengl.glDrawBuffers(n:Number, bufs[]:Number)
Gurax_DeclareFunctionAlias(glDrawBuffers_gurax, "glDrawBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufs", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawBuffers_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLsizei n = args.PickNumber<GLsizei>();
	auto bufs = args.PickNumList<GLenum>();
	// Function body
	glDrawBuffers(n, bufs);
	return Value::nil();
}

// opengl.glEnableVertexAttribArray(index:Number)
Gurax_DeclareFunctionAlias(glEnableVertexAttribArray_gurax, "glEnableVertexAttribArray")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnableVertexAttribArray_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	// Function body
	glEnableVertexAttribArray(index);
	return Value::nil();
}

// opengl.glIsProgram(program:Number)
Gurax_DeclareFunctionAlias(glIsProgram_gurax, "glIsProgram")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsProgram_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsProgram(program);
	return new Value_Bool(!!rtn);
}

// opengl.glIsShader(shader:Number)
Gurax_DeclareFunctionAlias(glIsShader_gurax, "glIsShader")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint shader = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsShader(shader);
	return new Value_Bool(!!rtn);
}

// opengl.glLinkProgram(program:Number)
Gurax_DeclareFunctionAlias(glLinkProgram_gurax, "glLinkProgram")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glLinkProgram_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	// Function body
	glLinkProgram(program);
	return Value::nil();
}

// opengl.glStencilFuncSeparate(frontfunc:Number, backfunc:Number, ref:Number, mask:Number)
Gurax_DeclareFunctionAlias(glStencilFuncSeparate_gurax, "glStencilFuncSeparate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("frontfunc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("backfunc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ref", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilFuncSeparate_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum frontfunc = args.PickNumber<GLenum>();
	GLenum backfunc = args.PickNumber<GLenum>();
	GLint ref = args.PickNumber<GLint>();
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glStencilFuncSeparate(frontfunc, backfunc, ref, mask);
	return Value::nil();
}

// opengl.glStencilMaskSeparate(face:Number, mask:Number)
Gurax_DeclareFunctionAlias(glStencilMaskSeparate_gurax, "glStencilMaskSeparate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilMaskSeparate_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLuint mask = args.PickNumber<GLuint>();
	// Function body
	glStencilMaskSeparate(face, mask);
	return Value::nil();
}

// opengl.glStencilOpSeparate(face:Number, sfail:Number, dpfail:Number, dppass:Number)
Gurax_DeclareFunctionAlias(glStencilOpSeparate_gurax, "glStencilOpSeparate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sfail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dpfail", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dppass", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glStencilOpSeparate_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum face = args.PickNumber<GLenum>();
	GLenum sfail = args.PickNumber<GLenum>();
	GLenum dpfail = args.PickNumber<GLenum>();
	GLenum dppass = args.PickNumber<GLenum>();
	// Function body
	glStencilOpSeparate(face, sfail, dpfail, dppass);
	return Value::nil();
}

// opengl.glUniform1f(location:Number, v0:Number)
Gurax_DeclareFunctionAlias(glUniform1f_gurax, "glUniform1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform1f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLfloat v0 = args.PickNumber<GLfloat>();
	// Function body
	glUniform1f(location, v0);
	return Value::nil();
}

// opengl.glUniform1fv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform1fv_gurax, "glUniform1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform1fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniform1fv(location, count, value);
	return Value::nil();
}

// opengl.glUniform1i(location:Number, v0:Number)
Gurax_DeclareFunctionAlias(glUniform1i_gurax, "glUniform1i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform1i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLint v0 = args.PickNumber<GLint>();
	// Function body
	glUniform1i(location, v0);
	return Value::nil();
}

// opengl.glUniform1iv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform1iv_gurax, "glUniform1iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform1iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLint>();
	// Function body
	glUniform1iv(location, count, value);
	return Value::nil();
}

// opengl.glUniform2f(location:Number, v0:Number, v1:Number)
Gurax_DeclareFunctionAlias(glUniform2f_gurax, "glUniform2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform2f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLfloat v0 = args.PickNumber<GLfloat>();
	GLfloat v1 = args.PickNumber<GLfloat>();
	// Function body
	glUniform2f(location, v0, v1);
	return Value::nil();
}

// opengl.glUniform2fv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform2fv_gurax, "glUniform2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniform2fv(location, count, value);
	return Value::nil();
}

// opengl.glUniform2i(location:Number, v0:Number, v1:Number)
Gurax_DeclareFunctionAlias(glUniform2i_gurax, "glUniform2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform2i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLint v0 = args.PickNumber<GLint>();
	GLint v1 = args.PickNumber<GLint>();
	// Function body
	glUniform2i(location, v0, v1);
	return Value::nil();
}

// opengl.glUniform2iv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform2iv_gurax, "glUniform2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform2iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLint>();
	// Function body
	glUniform2iv(location, count, value);
	return Value::nil();
}

// opengl.glUniform3f(location:Number, v0:Number, v1:Number, v2:Number)
Gurax_DeclareFunctionAlias(glUniform3f_gurax, "glUniform3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform3f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLfloat v0 = args.PickNumber<GLfloat>();
	GLfloat v1 = args.PickNumber<GLfloat>();
	GLfloat v2 = args.PickNumber<GLfloat>();
	// Function body
	glUniform3f(location, v0, v1, v2);
	return Value::nil();
}

// opengl.glUniform3fv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform3fv_gurax, "glUniform3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniform3fv(location, count, value);
	return Value::nil();
}

// opengl.glUniform3i(location:Number, v0:Number, v1:Number, v2:Number)
Gurax_DeclareFunctionAlias(glUniform3i_gurax, "glUniform3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform3i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLint v0 = args.PickNumber<GLint>();
	GLint v1 = args.PickNumber<GLint>();
	GLint v2 = args.PickNumber<GLint>();
	// Function body
	glUniform3i(location, v0, v1, v2);
	return Value::nil();
}

// opengl.glUniform3iv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform3iv_gurax, "glUniform3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLint>();
	// Function body
	glUniform3iv(location, count, value);
	return Value::nil();
}

// opengl.glUniform4f(location:Number, v0:Number, v1:Number, v2:Number, v3:Number)
Gurax_DeclareFunctionAlias(glUniform4f_gurax, "glUniform4f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform4f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLfloat v0 = args.PickNumber<GLfloat>();
	GLfloat v1 = args.PickNumber<GLfloat>();
	GLfloat v2 = args.PickNumber<GLfloat>();
	GLfloat v3 = args.PickNumber<GLfloat>();
	// Function body
	glUniform4f(location, v0, v1, v2, v3);
	return Value::nil();
}

// opengl.glUniform4fv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform4fv_gurax, "glUniform4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniform4fv(location, count, value);
	return Value::nil();
}

// opengl.glUniform4i(location:Number, v0:Number, v1:Number, v2:Number, v3:Number)
Gurax_DeclareFunctionAlias(glUniform4i_gurax, "glUniform4i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform4i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLint v0 = args.PickNumber<GLint>();
	GLint v1 = args.PickNumber<GLint>();
	GLint v2 = args.PickNumber<GLint>();
	GLint v3 = args.PickNumber<GLint>();
	// Function body
	glUniform4i(location, v0, v1, v2, v3);
	return Value::nil();
}

// opengl.glUniform4iv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform4iv_gurax, "glUniform4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLint>();
	// Function body
	glUniform4iv(location, count, value);
	return Value::nil();
}

// opengl.glUniformMatrix2fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix2fv_gurax, "glUniformMatrix2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix2fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix3fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix3fv_gurax, "glUniformMatrix3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix3fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix4fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix4fv_gurax, "glUniformMatrix4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix4fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUseProgram(program:Number)
Gurax_DeclareFunctionAlias(glUseProgram_gurax, "glUseProgram")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUseProgram_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	// Function body
	glUseProgram(program);
	return Value::nil();
}

// opengl.glValidateProgram(program:Number)
Gurax_DeclareFunctionAlias(glValidateProgram_gurax, "glValidateProgram")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glValidateProgram_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint program = args.PickNumber<GLuint>();
	// Function body
	glValidateProgram(program);
	return Value::nil();
}

// opengl.glVertexAttrib1d(index:Number, x:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib1d_gurax, "glVertexAttrib1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib1d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLdouble x = args.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib1d(index, x);
	return Value::nil();
}

// opengl.glVertexAttrib1dv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib1dv_gurax, "glVertexAttrib1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib1dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib1dv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib1f(index:Number, x:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib1f_gurax, "glVertexAttrib1f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib1f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLfloat x = args.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib1f(index, x);
	return Value::nil();
}

// opengl.glVertexAttrib1fv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib1fv_gurax, "glVertexAttrib1fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib1fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib1fv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib1s(index:Number, x:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib1s_gurax, "glVertexAttrib1s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib1s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLshort x = args.PickNumber<GLshort>();
	// Function body
	glVertexAttrib1s(index, x);
	return Value::nil();
}

// opengl.glVertexAttrib1sv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib1sv_gurax, "glVertexAttrib1sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib1sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertexAttrib1sv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib2d(index:Number, x:Number, y:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib2d_gurax, "glVertexAttrib2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib2d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib2d(index, x, y);
	return Value::nil();
}

// opengl.glVertexAttrib2dv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib2dv_gurax, "glVertexAttrib2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib2dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib2dv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib2f(index:Number, x:Number, y:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib2f_gurax, "glVertexAttrib2f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib2f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib2f(index, x, y);
	return Value::nil();
}

// opengl.glVertexAttrib2fv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib2fv_gurax, "glVertexAttrib2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib2fv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib2s(index:Number, x:Number, y:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib2s_gurax, "glVertexAttrib2s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib2s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	// Function body
	glVertexAttrib2s(index, x, y);
	return Value::nil();
}

// opengl.glVertexAttrib2sv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib2sv_gurax, "glVertexAttrib2sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib2sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertexAttrib2sv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib3d(index:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib3d_gurax, "glVertexAttrib3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib3d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib3d(index, x, y, z);
	return Value::nil();
}

// opengl.glVertexAttrib3dv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib3dv_gurax, "glVertexAttrib3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib3dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib3dv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib3f(index:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib3f_gurax, "glVertexAttrib3f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib3f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib3f(index, x, y, z);
	return Value::nil();
}

// opengl.glVertexAttrib3fv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib3fv_gurax, "glVertexAttrib3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib3fv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib3s(index:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib3s_gurax, "glVertexAttrib3s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib3s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	// Function body
	glVertexAttrib3s(index, x, y, z);
	return Value::nil();
}

// opengl.glVertexAttrib3sv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib3sv_gurax, "glVertexAttrib3sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib3sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertexAttrib3sv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4Nbv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Nbv_gurax, "glVertexAttrib4Nbv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Nbv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glVertexAttrib4Nbv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4Niv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Niv_gurax, "glVertexAttrib4Niv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Niv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertexAttrib4Niv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4Nsv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Nsv_gurax, "glVertexAttrib4Nsv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Nsv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertexAttrib4Nsv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4Nub(index:Number, x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Nub_gurax, "glVertexAttrib4Nub")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Nub_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLubyte x = args.PickNumber<GLubyte>();
	GLubyte y = args.PickNumber<GLubyte>();
	GLubyte z = args.PickNumber<GLubyte>();
	GLubyte w = args.PickNumber<GLubyte>();
	// Function body
	glVertexAttrib4Nub(index, x, y, z, w);
	return Value::nil();
}

// opengl.glVertexAttrib4Nubv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Nubv_gurax, "glVertexAttrib4Nubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Nubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glVertexAttrib4Nubv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4Nuiv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Nuiv_gurax, "glVertexAttrib4Nuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Nuiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLuint>();
	// Function body
	glVertexAttrib4Nuiv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4Nusv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4Nusv_gurax, "glVertexAttrib4Nusv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4Nusv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLushort>();
	// Function body
	glVertexAttrib4Nusv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4bv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4bv_gurax, "glVertexAttrib4bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4bv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLbyte>();
	// Function body
	glVertexAttrib4bv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4d(index:Number, x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4d_gurax, "glVertexAttrib4d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4d_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLdouble x = args.PickNumber<GLdouble>();
	GLdouble y = args.PickNumber<GLdouble>();
	GLdouble z = args.PickNumber<GLdouble>();
	GLdouble w = args.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib4d(index, x, y, z, w);
	return Value::nil();
}

// opengl.glVertexAttrib4dv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4dv_gurax, "glVertexAttrib4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4dv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib4dv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4f(index:Number, x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4f_gurax, "glVertexAttrib4f")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4f_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLfloat x = args.PickNumber<GLfloat>();
	GLfloat y = args.PickNumber<GLfloat>();
	GLfloat z = args.PickNumber<GLfloat>();
	GLfloat w = args.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib4f(index, x, y, z, w);
	return Value::nil();
}

// opengl.glVertexAttrib4fv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4fv_gurax, "glVertexAttrib4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib4fv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4iv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4iv_gurax, "glVertexAttrib4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLint>();
	// Function body
	glVertexAttrib4iv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4s(index:Number, x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4s_gurax, "glVertexAttrib4s")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4s_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLshort x = args.PickNumber<GLshort>();
	GLshort y = args.PickNumber<GLshort>();
	GLshort z = args.PickNumber<GLshort>();
	GLshort w = args.PickNumber<GLshort>();
	// Function body
	glVertexAttrib4s(index, x, y, z, w);
	return Value::nil();
}

// opengl.glVertexAttrib4sv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4sv_gurax, "glVertexAttrib4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLshort>();
	// Function body
	glVertexAttrib4sv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4ubv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4ubv_gurax, "glVertexAttrib4ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4ubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLubyte>();
	// Function body
	glVertexAttrib4ubv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4uiv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4uiv_gurax, "glVertexAttrib4uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLuint>();
	// Function body
	glVertexAttrib4uiv(index, v);
	return Value::nil();
}

// opengl.glVertexAttrib4usv(index:Number, v[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttrib4usv_gurax, "glVertexAttrib4usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttrib4usv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v = args.PickNumList<GLushort>();
	// Function body
	glVertexAttrib4usv(index, v);
	return Value::nil();
}

// opengl.glVertexAttribPointer(index:Number, size:Number, type:Number, normalized:Bool, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glVertexAttribPointer_gurax, "glVertexAttribPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("normalized", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribPointer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLint size = args.PickNumber<GLint>();
	GLenum type = args.PickNumber<GLenum>();
	GLboolean normalized = static_cast<GLboolean>(args.PickBool());
	GLsizei stride = args.PickNumber<GLsizei>();
	const void* pointer = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	return Value::nil();
}

// opengl.glUniformMatrix2x3fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix2x3fv_gurax, "glUniformMatrix2x3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix2x3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix2x3fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix2x4fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix2x4fv_gurax, "glUniformMatrix2x4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix2x4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix2x4fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix3x2fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix3x2fv_gurax, "glUniformMatrix3x2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix3x2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix3x2fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix3x4fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix3x4fv_gurax, "glUniformMatrix3x4fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix3x4fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix3x4fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix4x2fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix4x2fv_gurax, "glUniformMatrix4x2fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix4x2fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix4x2fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glUniformMatrix4x3fv(location:Number, count:Number, transpose:Bool, value[]:Number)
Gurax_DeclareFunctionAlias(glUniformMatrix4x3fv_gurax, "glUniformMatrix4x3fv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniformMatrix4x3fv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args.PickBool());
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix4x3fv(location, count, transpose, value);
	return Value::nil();
}

// opengl.glBeginConditionalRender(id:Number, mode:Number)
Gurax_DeclareFunctionAlias(glBeginConditionalRender_gurax, "glBeginConditionalRender")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBeginConditionalRender_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint id = args.PickNumber<GLuint>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glBeginConditionalRender(id, mode);
	return Value::nil();
}

// opengl.glBeginTransformFeedback(primitiveMode:Number)
Gurax_DeclareFunctionAlias(glBeginTransformFeedback_gurax, "glBeginTransformFeedback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("primitiveMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBeginTransformFeedback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum primitiveMode = args.PickNumber<GLenum>();
	// Function body
	glBeginTransformFeedback(primitiveMode);
	return Value::nil();
}

// opengl.glClampColor(target:Number, clamp:Number)
Gurax_DeclareFunctionAlias(glClampColor_gurax, "glClampColor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clamp", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClampColor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum clamp = args.PickNumber<GLenum>();
	// Function body
	glClampColor(target, clamp);
	return Value::nil();
}

// opengl.glClearBufferfi(buffer:Number, drawBuffer:Number, depth:Number, stencil:Number)
Gurax_DeclareFunctionAlias(glClearBufferfi_gurax, "glClearBufferfi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawBuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stencil", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearBufferfi_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum buffer = args.PickNumber<GLenum>();
	GLint drawBuffer = args.PickNumber<GLint>();
	GLfloat depth = args.PickNumber<GLfloat>();
	GLint stencil = args.PickNumber<GLint>();
	// Function body
	glClearBufferfi(buffer, drawBuffer, depth, stencil);
	return Value::nil();
}

// opengl.glClearBufferfv(buffer:Number, drawBuffer:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glClearBufferfv_gurax, "glClearBufferfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawBuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearBufferfv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum buffer = args.PickNumber<GLenum>();
	GLint drawBuffer = args.PickNumber<GLint>();
	auto value = args.PickNumList<GLfloat>();
	// Function body
	glClearBufferfv(buffer, drawBuffer, value);
	return Value::nil();
}

// opengl.glClearBufferiv(buffer:Number, drawBuffer:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glClearBufferiv_gurax, "glClearBufferiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawBuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearBufferiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum buffer = args.PickNumber<GLenum>();
	GLint drawBuffer = args.PickNumber<GLint>();
	auto value = args.PickNumList<GLint>();
	// Function body
	glClearBufferiv(buffer, drawBuffer, value);
	return Value::nil();
}

// opengl.glClearBufferuiv(buffer:Number, drawBuffer:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glClearBufferuiv_gurax, "glClearBufferuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawBuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glClearBufferuiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum buffer = args.PickNumber<GLenum>();
	GLint drawBuffer = args.PickNumber<GLint>();
	auto value = args.PickNumList<GLuint>();
	// Function body
	glClearBufferuiv(buffer, drawBuffer, value);
	return Value::nil();
}

// opengl.glColorMaski(buf:Number, red:Bool, green:Bool, blue:Bool, alpha:Bool)
Gurax_DeclareFunctionAlias(glColorMaski_gurax, "glColorMaski")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glColorMaski_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buf = args.PickNumber<GLuint>();
	GLboolean red = static_cast<GLboolean>(args.PickBool());
	GLboolean green = static_cast<GLboolean>(args.PickBool());
	GLboolean blue = static_cast<GLboolean>(args.PickBool());
	GLboolean alpha = static_cast<GLboolean>(args.PickBool());
	// Function body
	glColorMaski(buf, red, green, blue, alpha);
	return Value::nil();
}

// opengl.glDisablei(cap:Number, index:Number)
Gurax_DeclareFunctionAlias(glDisablei_gurax, "glDisablei")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDisablei_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	GLuint index = args.PickNumber<GLuint>();
	// Function body
	glDisablei(cap, index);
	return Value::nil();
}

// opengl.glEnablei(cap:Number, index:Number)
Gurax_DeclareFunctionAlias(glEnablei_gurax, "glEnablei")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEnablei_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	GLuint index = args.PickNumber<GLuint>();
	// Function body
	glEnablei(cap, index);
	return Value::nil();
}

// opengl.glEndConditionalRender()
Gurax_DeclareFunctionAlias(glEndConditionalRender_gurax, "glEndConditionalRender")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEndConditionalRender_gurax)
{
	// Function body
	glEndConditionalRender();
	return Value::nil();
}

// opengl.glEndTransformFeedback()
Gurax_DeclareFunctionAlias(glEndTransformFeedback_gurax, "glEndTransformFeedback")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glEndTransformFeedback_gurax)
{
	// Function body
	glEndTransformFeedback();
	return Value::nil();
}

// opengl.glIsEnabledi(cap:Number, index:Number)
Gurax_DeclareFunctionAlias(glIsEnabledi_gurax, "glIsEnabledi")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glIsEnabledi_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum cap = args.PickNumber<GLenum>();
	GLuint index = args.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsEnabledi(cap, index);
	return new Value_Bool(!!rtn);
}

// opengl.glTexParameterIiv(target:Number, pname:Number, params[]:Number)
Gurax_DeclareFunctionAlias(glTexParameterIiv_gurax, "glTexParameterIiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameterIiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLint>();
	// Function body
	glTexParameterIiv(target, pname, params);
	return Value::nil();
}

// opengl.glTexParameterIuiv(target:Number, pname:Number, params[]:Number)
Gurax_DeclareFunctionAlias(glTexParameterIuiv_gurax, "glTexParameterIuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexParameterIuiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum pname = args.PickNumber<GLenum>();
	auto params = args.PickNumList<GLuint>();
	// Function body
	glTexParameterIuiv(target, pname, params);
	return Value::nil();
}

// opengl.glUniform1ui(location:Number, v0:Number)
Gurax_DeclareFunctionAlias(glUniform1ui_gurax, "glUniform1ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform1ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLuint v0 = args.PickNumber<GLuint>();
	// Function body
	glUniform1ui(location, v0);
	return Value::nil();
}

// opengl.glUniform1uiv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform1uiv_gurax, "glUniform1uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform1uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLuint>();
	// Function body
	glUniform1uiv(location, count, value);
	return Value::nil();
}

// opengl.glUniform2ui(location:Number, v0:Number, v1:Number)
Gurax_DeclareFunctionAlias(glUniform2ui_gurax, "glUniform2ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform2ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLuint v0 = args.PickNumber<GLuint>();
	GLuint v1 = args.PickNumber<GLuint>();
	// Function body
	glUniform2ui(location, v0, v1);
	return Value::nil();
}

// opengl.glUniform2uiv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform2uiv_gurax, "glUniform2uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform2uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLuint>();
	// Function body
	glUniform2uiv(location, count, value);
	return Value::nil();
}

// opengl.glUniform3ui(location:Number, v0:Number, v1:Number, v2:Number)
Gurax_DeclareFunctionAlias(glUniform3ui_gurax, "glUniform3ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform3ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLuint v0 = args.PickNumber<GLuint>();
	GLuint v1 = args.PickNumber<GLuint>();
	GLuint v2 = args.PickNumber<GLuint>();
	// Function body
	glUniform3ui(location, v0, v1, v2);
	return Value::nil();
}

// opengl.glUniform3uiv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform3uiv_gurax, "glUniform3uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform3uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLuint>();
	// Function body
	glUniform3uiv(location, count, value);
	return Value::nil();
}

// opengl.glUniform4ui(location:Number, v0:Number, v1:Number, v2:Number, v3:Number)
Gurax_DeclareFunctionAlias(glUniform4ui_gurax, "glUniform4ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform4ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLuint v0 = args.PickNumber<GLuint>();
	GLuint v1 = args.PickNumber<GLuint>();
	GLuint v2 = args.PickNumber<GLuint>();
	GLuint v3 = args.PickNumber<GLuint>();
	// Function body
	glUniform4ui(location, v0, v1, v2, v3);
	return Value::nil();
}

// opengl.glUniform4uiv(location:Number, count:Number, value[]:Number)
Gurax_DeclareFunctionAlias(glUniform4uiv_gurax, "glUniform4uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glUniform4uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLint location = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	auto value = args.PickNumList<GLuint>();
	// Function body
	glUniform4uiv(location, count, value);
	return Value::nil();
}

// opengl.glVertexAttribI1i(index:Number, v0:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI1i_gurax, "glVertexAttribI1i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI1i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLint v0 = args.PickNumber<GLint>();
	// Function body
	glVertexAttribI1i(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI1iv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI1iv_gurax, "glVertexAttribI1iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI1iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLint>();
	// Function body
	glVertexAttribI1iv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI1ui(index:Number, v0:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI1ui_gurax, "glVertexAttribI1ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI1ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLuint v0 = args.PickNumber<GLuint>();
	// Function body
	glVertexAttribI1ui(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI1uiv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI1uiv_gurax, "glVertexAttribI1uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI1uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLuint>();
	// Function body
	glVertexAttribI1uiv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI2i(index:Number, v0:Number, v1:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI2i_gurax, "glVertexAttribI2i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI2i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLint v0 = args.PickNumber<GLint>();
	GLint v1 = args.PickNumber<GLint>();
	// Function body
	glVertexAttribI2i(index, v0, v1);
	return Value::nil();
}

// opengl.glVertexAttribI2iv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI2iv_gurax, "glVertexAttribI2iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI2iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLint>();
	// Function body
	glVertexAttribI2iv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI2ui(index:Number, v0:Number, v1:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI2ui_gurax, "glVertexAttribI2ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI2ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLuint v0 = args.PickNumber<GLuint>();
	GLuint v1 = args.PickNumber<GLuint>();
	// Function body
	glVertexAttribI2ui(index, v0, v1);
	return Value::nil();
}

// opengl.glVertexAttribI2uiv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI2uiv_gurax, "glVertexAttribI2uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI2uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLuint>();
	// Function body
	glVertexAttribI2uiv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI3i(index:Number, v0:Number, v1:Number, v2:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI3i_gurax, "glVertexAttribI3i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI3i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLint v0 = args.PickNumber<GLint>();
	GLint v1 = args.PickNumber<GLint>();
	GLint v2 = args.PickNumber<GLint>();
	// Function body
	glVertexAttribI3i(index, v0, v1, v2);
	return Value::nil();
}

// opengl.glVertexAttribI3iv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI3iv_gurax, "glVertexAttribI3iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI3iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLint>();
	// Function body
	glVertexAttribI3iv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI3ui(index:Number, v0:Number, v1:Number, v2:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI3ui_gurax, "glVertexAttribI3ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI3ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLuint v0 = args.PickNumber<GLuint>();
	GLuint v1 = args.PickNumber<GLuint>();
	GLuint v2 = args.PickNumber<GLuint>();
	// Function body
	glVertexAttribI3ui(index, v0, v1, v2);
	return Value::nil();
}

// opengl.glVertexAttribI3uiv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI3uiv_gurax, "glVertexAttribI3uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI3uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLuint>();
	// Function body
	glVertexAttribI3uiv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI4bv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4bv_gurax, "glVertexAttribI4bv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4bv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLbyte>();
	// Function body
	glVertexAttribI4bv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI4i(index:Number, v0:Number, v1:Number, v2:Number, v3:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4i_gurax, "glVertexAttribI4i")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4i_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLint v0 = args.PickNumber<GLint>();
	GLint v1 = args.PickNumber<GLint>();
	GLint v2 = args.PickNumber<GLint>();
	GLint v3 = args.PickNumber<GLint>();
	// Function body
	glVertexAttribI4i(index, v0, v1, v2, v3);
	return Value::nil();
}

// opengl.glVertexAttribI4iv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4iv_gurax, "glVertexAttribI4iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4iv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLint>();
	// Function body
	glVertexAttribI4iv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI4sv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4sv_gurax, "glVertexAttribI4sv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4sv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLshort>();
	// Function body
	glVertexAttribI4sv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI4ubv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4ubv_gurax, "glVertexAttribI4ubv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4ubv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLubyte>();
	// Function body
	glVertexAttribI4ubv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI4ui(index:Number, v0:Number, v1:Number, v2:Number, v3:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4ui_gurax, "glVertexAttribI4ui")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4ui_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLuint v0 = args.PickNumber<GLuint>();
	GLuint v1 = args.PickNumber<GLuint>();
	GLuint v2 = args.PickNumber<GLuint>();
	GLuint v3 = args.PickNumber<GLuint>();
	// Function body
	glVertexAttribI4ui(index, v0, v1, v2, v3);
	return Value::nil();
}

// opengl.glVertexAttribI4uiv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4uiv_gurax, "glVertexAttribI4uiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4uiv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLuint>();
	// Function body
	glVertexAttribI4uiv(index, v0);
	return Value::nil();
}

// opengl.glVertexAttribI4usv(index:Number, v0[]:Number)
Gurax_DeclareFunctionAlias(glVertexAttribI4usv_gurax, "glVertexAttribI4usv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v0", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribI4usv_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	auto v0 = args.PickNumList<GLushort>();
	// Function body
	glVertexAttribI4usv(index, v0);
	return Value::nil();
}

// opengl.glDrawArraysInstanced(mode:Number, first:Number, count:Number, primcount:Number)
Gurax_DeclareFunctionAlias(glDrawArraysInstanced_gurax, "glDrawArraysInstanced")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawArraysInstanced_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLint first = args.PickNumber<GLint>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLsizei primcount = args.PickNumber<GLsizei>();
	// Function body
	glDrawArraysInstanced(mode, first, count, primcount);
	return Value::nil();
}

// opengl.glDrawElementsInstanced(mode:Number, count:Number, type:Number, indices:Pointer, primcount:Number)
Gurax_DeclareFunctionAlias(glDrawElementsInstanced_gurax, "glDrawElementsInstanced")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glDrawElementsInstanced_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum mode = args.PickNumber<GLenum>();
	GLsizei count = args.PickNumber<GLsizei>();
	GLenum type = args.PickNumber<GLenum>();
	const void* indices = args.Pick<Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei primcount = args.PickNumber<GLsizei>();
	// Function body
	glDrawElementsInstanced(mode, count, type, indices, primcount);
	return Value::nil();
}

// opengl.glPrimitiveRestartIndex(buffer:Number)
Gurax_DeclareFunctionAlias(glPrimitiveRestartIndex_gurax, "glPrimitiveRestartIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glPrimitiveRestartIndex_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buffer = args.PickNumber<GLuint>();
	// Function body
	glPrimitiveRestartIndex(buffer);
	return Value::nil();
}

// opengl.glTexBuffer(target:Number, internalFormat:Number, buffer:Number)
Gurax_DeclareFunctionAlias(glTexBuffer_gurax, "glTexBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalFormat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glTexBuffer_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum internalFormat = args.PickNumber<GLenum>();
	GLuint buffer = args.PickNumber<GLuint>();
	// Function body
	glTexBuffer(target, internalFormat, buffer);
	return Value::nil();
}

// opengl.glFramebufferTexture(target:Number, attachment:Number, texture:Number, level:Number)
Gurax_DeclareFunctionAlias(glFramebufferTexture_gurax, "glFramebufferTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glFramebufferTexture_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLenum target = args.PickNumber<GLenum>();
	GLenum attachment = args.PickNumber<GLenum>();
	GLuint texture = args.PickNumber<GLuint>();
	GLint level = args.PickNumber<GLint>();
	// Function body
	glFramebufferTexture(target, attachment, texture, level);
	return Value::nil();
}

// opengl.glVertexAttribDivisor(index:Number, divisor:Number)
Gurax_DeclareFunctionAlias(glVertexAttribDivisor_gurax, "glVertexAttribDivisor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("divisor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glVertexAttribDivisor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint index = args.PickNumber<GLuint>();
	GLuint divisor = args.PickNumber<GLuint>();
	// Function body
	glVertexAttribDivisor(index, divisor);
	return Value::nil();
}

// opengl.glBlendEquationSeparatei(buf:Number, modeRGB:Number, modeAlpha:Number)
Gurax_DeclareFunctionAlias(glBlendEquationSeparatei_gurax, "glBlendEquationSeparatei")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendEquationSeparatei_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buf = args.PickNumber<GLuint>();
	GLenum modeRGB = args.PickNumber<GLenum>();
	GLenum modeAlpha = args.PickNumber<GLenum>();
	// Function body
	glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
	return Value::nil();
}

// opengl.glBlendEquationi(buf:Number, mode:Number)
Gurax_DeclareFunctionAlias(glBlendEquationi_gurax, "glBlendEquationi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendEquationi_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buf = args.PickNumber<GLuint>();
	GLenum mode = args.PickNumber<GLenum>();
	// Function body
	glBlendEquationi(buf, mode);
	return Value::nil();
}

// opengl.glBlendFuncSeparatei(buf:Number, srcRGB:Number, dstRGB:Number, srcAlpha:Number, dstAlpha:Number)
Gurax_DeclareFunctionAlias(glBlendFuncSeparatei_gurax, "glBlendFuncSeparatei")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendFuncSeparatei_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buf = args.PickNumber<GLuint>();
	GLenum srcRGB = args.PickNumber<GLenum>();
	GLenum dstRGB = args.PickNumber<GLenum>();
	GLenum srcAlpha = args.PickNumber<GLenum>();
	GLenum dstAlpha = args.PickNumber<GLenum>();
	// Function body
	glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	return Value::nil();
}

// opengl.glBlendFunci(buf:Number, src:Number, dst:Number)
Gurax_DeclareFunctionAlias(glBlendFunci_gurax, "glBlendFunci")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glBlendFunci_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint buf = args.PickNumber<GLuint>();
	GLenum src = args.PickNumber<GLenum>();
	GLenum dst = args.PickNumber<GLenum>();
	// Function body
	glBlendFunci(buf, src, dst);
	return Value::nil();
}

// opengl.glMinSampleShading(value:Number)
Gurax_DeclareFunctionAlias(glMinSampleShading_gurax, "glMinSampleShading")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glMinSampleShading_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLclampf value = args.PickNumber<GLclampf>();
	// Function body
	glMinSampleShading(value);
	return Value::nil();
}

// opengl.glGetGraphicsResetStatus()
Gurax_DeclareFunctionAlias(glGetGraphicsResetStatus_gurax, "glGetGraphicsResetStatus")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glGetGraphicsResetStatus_gurax)
{
	// Function body
	GLenum rtn = glGetGraphicsResetStatus();
	return new Value_Number(rtn);
}

// opengl.glSpecializeShader(shader:Number, pEntryPoint[]:Number, numSpecializationConstants:Number, pConstantIndex[]:Number, pConstantValue[]:Number)
Gurax_DeclareFunctionAlias(glSpecializeShader_gurax, "glSpecializeShader")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pEntryPoint", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("numSpecializationConstants", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pConstantIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("pConstantValue", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glSpecializeShader_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLuint shader = args.PickNumber<GLuint>();
	auto pEntryPoint = args.PickNumList<GLchar>();
	GLuint numSpecializationConstants = args.PickNumber<GLuint>();
	auto pConstantIndex = args.PickNumList<GLuint>();
	auto pConstantValue = args.PickNumList<GLuint>();
	// Function body
	glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(glewInit_gurax));
	frame.Assign(Gurax_CreateFunction(glewIsSupported_gurax));
	frame.Assign(Gurax_CreateFunction(glewGetExtension_gurax));
	frame.Assign(Gurax_CreateFunction(glewGetErrorString_gurax));
	frame.Assign(Gurax_CreateFunction(glewGetString_gurax));
	frame.Assign(Gurax_CreateFunction(glAccum_gurax));
	frame.Assign(Gurax_CreateFunction(glAlphaFunc_gurax));
	frame.Assign(Gurax_CreateFunction(glArrayElement_gurax));
	frame.Assign(Gurax_CreateFunction(glBegin_gurax));
	frame.Assign(Gurax_CreateFunction(glBindTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFunc_gurax));
	frame.Assign(Gurax_CreateFunction(glCallList_gurax));
	frame.Assign(Gurax_CreateFunction(glCallLists_gurax));
	frame.Assign(Gurax_CreateFunction(glClear_gurax));
	frame.Assign(Gurax_CreateFunction(glClearAccum_gurax));
	frame.Assign(Gurax_CreateFunction(glClearColor_gurax));
	frame.Assign(Gurax_CreateFunction(glClearDepth_gurax));
	frame.Assign(Gurax_CreateFunction(glClearIndex_gurax));
	frame.Assign(Gurax_CreateFunction(glClearStencil_gurax));
	frame.Assign(Gurax_CreateFunction(glClipPlane_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3b_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3bv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3d_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3f_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3i_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3s_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3ub_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3ubv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3ui_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3us_gurax));
	frame.Assign(Gurax_CreateFunction(glColor3usv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4b_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4bv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4d_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4f_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4i_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4s_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4ub_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4ubv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4ui_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4us_gurax));
	frame.Assign(Gurax_CreateFunction(glColor4usv_gurax));
	frame.Assign(Gurax_CreateFunction(glColorMask_gurax));
	frame.Assign(Gurax_CreateFunction(glColorMaterial_gurax));
	frame.Assign(Gurax_CreateFunction(glColorPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyPixels_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTexImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTexImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTexSubImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTexSubImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glCullFace_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteLists_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteTextures_gurax));
	frame.Assign(Gurax_CreateFunction(glDepthFunc_gurax));
	frame.Assign(Gurax_CreateFunction(glDepthMask_gurax));
	frame.Assign(Gurax_CreateFunction(glDepthRange_gurax));
	frame.Assign(Gurax_CreateFunction(glDisable_gurax));
	frame.Assign(Gurax_CreateFunction(glDisableClientState_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawArrays_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElements_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawPixels_gurax));
	frame.Assign(Gurax_CreateFunction(glEdgeFlag_gurax));
	frame.Assign(Gurax_CreateFunction(glEdgeFlagPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glEdgeFlagv_gurax));
	frame.Assign(Gurax_CreateFunction(glEnable_gurax));
	frame.Assign(Gurax_CreateFunction(glEnableClientState_gurax));
	frame.Assign(Gurax_CreateFunction(glEnd_gurax));
	frame.Assign(Gurax_CreateFunction(glEndList_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1d_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1dv_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1f_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord1fv_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2d_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2f_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalCoord2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalMesh1_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalMesh2_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalPoint1_gurax));
	frame.Assign(Gurax_CreateFunction(glEvalPoint2_gurax));
	frame.Assign(Gurax_CreateFunction(glFeedbackBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glFinish_gurax));
	frame.Assign(Gurax_CreateFunction(glFlush_gurax));
	frame.Assign(Gurax_CreateFunction(glFogf_gurax));
	frame.Assign(Gurax_CreateFunction(glFogfv_gurax));
	frame.Assign(Gurax_CreateFunction(glFogi_gurax));
	frame.Assign(Gurax_CreateFunction(glFogiv_gurax));
	frame.Assign(Gurax_CreateFunction(glFrontFace_gurax));
	frame.Assign(Gurax_CreateFunction(glFrustum_gurax));
	frame.Assign(Gurax_CreateFunction(glGenLists_gurax));
	frame.Assign(Gurax_CreateFunction(glGenTextures_gurax));
	frame.Assign(Gurax_CreateFunction(glGetError_gurax));
	frame.Assign(Gurax_CreateFunction(glGetString_gurax));
	frame.Assign(Gurax_CreateFunction(glHint_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexMask_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexd_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexdv_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexf_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexfv_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexi_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexiv_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexs_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexsv_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexub_gurax));
	frame.Assign(Gurax_CreateFunction(glIndexubv_gurax));
	frame.Assign(Gurax_CreateFunction(glInitNames_gurax));
	frame.Assign(Gurax_CreateFunction(glInterleavedArrays_gurax));
	frame.Assign(Gurax_CreateFunction(glIsEnabled_gurax));
	frame.Assign(Gurax_CreateFunction(glIsList_gurax));
	frame.Assign(Gurax_CreateFunction(glIsTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glLightModelf_gurax));
	frame.Assign(Gurax_CreateFunction(glLightModelfv_gurax));
	frame.Assign(Gurax_CreateFunction(glLightModeli_gurax));
	frame.Assign(Gurax_CreateFunction(glLightModeliv_gurax));
	frame.Assign(Gurax_CreateFunction(glLightf_gurax));
	frame.Assign(Gurax_CreateFunction(glLightfv_gurax));
	frame.Assign(Gurax_CreateFunction(glLighti_gurax));
	frame.Assign(Gurax_CreateFunction(glLightiv_gurax));
	frame.Assign(Gurax_CreateFunction(glLineStipple_gurax));
	frame.Assign(Gurax_CreateFunction(glLineWidth_gurax));
	frame.Assign(Gurax_CreateFunction(glListBase_gurax));
	frame.Assign(Gurax_CreateFunction(glLoadIdentity_gurax));
	frame.Assign(Gurax_CreateFunction(glLoadMatrixd_gurax));
	frame.Assign(Gurax_CreateFunction(glLoadMatrixf_gurax));
	frame.Assign(Gurax_CreateFunction(glLoadName_gurax));
	frame.Assign(Gurax_CreateFunction(glLogicOp_gurax));
	frame.Assign(Gurax_CreateFunction(glMap1d_gurax));
	frame.Assign(Gurax_CreateFunction(glMap1f_gurax));
	frame.Assign(Gurax_CreateFunction(glMap2d_gurax));
	frame.Assign(Gurax_CreateFunction(glMap2f_gurax));
	frame.Assign(Gurax_CreateFunction(glMapGrid1d_gurax));
	frame.Assign(Gurax_CreateFunction(glMapGrid1f_gurax));
	frame.Assign(Gurax_CreateFunction(glMapGrid2d_gurax));
	frame.Assign(Gurax_CreateFunction(glMapGrid2f_gurax));
	frame.Assign(Gurax_CreateFunction(glMaterialf_gurax));
	frame.Assign(Gurax_CreateFunction(glMaterialfv_gurax));
	frame.Assign(Gurax_CreateFunction(glMateriali_gurax));
	frame.Assign(Gurax_CreateFunction(glMaterialiv_gurax));
	frame.Assign(Gurax_CreateFunction(glMatrixMode_gurax));
	frame.Assign(Gurax_CreateFunction(glMultMatrixd_gurax));
	frame.Assign(Gurax_CreateFunction(glMultMatrixf_gurax));
	frame.Assign(Gurax_CreateFunction(glNewList_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3b_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3bv_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3d_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3f_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3i_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3s_gurax));
	frame.Assign(Gurax_CreateFunction(glNormal3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glOrtho_gurax));
	frame.Assign(Gurax_CreateFunction(glPassThrough_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelMapfv_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelMapuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelMapusv_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelStoref_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelStorei_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelTransferf_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelTransferi_gurax));
	frame.Assign(Gurax_CreateFunction(glPixelZoom_gurax));
	frame.Assign(Gurax_CreateFunction(glPointSize_gurax));
	frame.Assign(Gurax_CreateFunction(glPolygonMode_gurax));
	frame.Assign(Gurax_CreateFunction(glPolygonOffset_gurax));
	frame.Assign(Gurax_CreateFunction(glPolygonStipple_gurax));
	frame.Assign(Gurax_CreateFunction(glPopAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glPopClientAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glPopMatrix_gurax));
	frame.Assign(Gurax_CreateFunction(glPopName_gurax));
	frame.Assign(Gurax_CreateFunction(glPrioritizeTextures_gurax));
	frame.Assign(Gurax_CreateFunction(glPushAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glPushClientAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glPushMatrix_gurax));
	frame.Assign(Gurax_CreateFunction(glPushName_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2d_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2f_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2i_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2s_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos2sv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3d_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3f_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3i_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3s_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4d_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4f_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4i_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4s_gurax));
	frame.Assign(Gurax_CreateFunction(glRasterPos4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glReadBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glRectd_gurax));
	frame.Assign(Gurax_CreateFunction(glRectdv_gurax));
	frame.Assign(Gurax_CreateFunction(glRectf_gurax));
	frame.Assign(Gurax_CreateFunction(glRectfv_gurax));
	frame.Assign(Gurax_CreateFunction(glRecti_gurax));
	frame.Assign(Gurax_CreateFunction(glRectiv_gurax));
	frame.Assign(Gurax_CreateFunction(glRects_gurax));
	frame.Assign(Gurax_CreateFunction(glRectsv_gurax));
	frame.Assign(Gurax_CreateFunction(glRenderMode_gurax));
	frame.Assign(Gurax_CreateFunction(glRotated_gurax));
	frame.Assign(Gurax_CreateFunction(glRotatef_gurax));
	frame.Assign(Gurax_CreateFunction(glScaled_gurax));
	frame.Assign(Gurax_CreateFunction(glScalef_gurax));
	frame.Assign(Gurax_CreateFunction(glScissor_gurax));
	frame.Assign(Gurax_CreateFunction(glShadeModel_gurax));
	frame.Assign(Gurax_CreateFunction(glStencilFunc_gurax));
	frame.Assign(Gurax_CreateFunction(glStencilMask_gurax));
	frame.Assign(Gurax_CreateFunction(glStencilOp_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1d_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1dv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1f_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1fv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1i_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1iv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1s_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord1sv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2d_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2f_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2i_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2s_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord2sv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3d_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3f_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3i_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3s_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4d_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4f_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4i_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4s_gurax));
	frame.Assign(Gurax_CreateFunction(glTexCoord4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexEnvf_gurax));
	frame.Assign(Gurax_CreateFunction(glTexEnvfv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexEnvi_gurax));
	frame.Assign(Gurax_CreateFunction(glTexEnviv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexGend_gurax));
	frame.Assign(Gurax_CreateFunction(glTexGendv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexGenf_gurax));
	frame.Assign(Gurax_CreateFunction(glTexGenfv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexGeni_gurax));
	frame.Assign(Gurax_CreateFunction(glTexGeniv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameterf_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glTranslated_gurax));
	frame.Assign(Gurax_CreateFunction(glTranslatef_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex2sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertex4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glViewport_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTexSubImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawRangeElements_gurax));
	frame.Assign(Gurax_CreateFunction(glTexImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glTexSubImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glActiveTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glClientActiveTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTexImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTexImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTexImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTexSubImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTexSubImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTexSubImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glLoadTransposeMatrixd_gurax));
	frame.Assign(Gurax_CreateFunction(glLoadTransposeMatrixf_gurax));
	frame.Assign(Gurax_CreateFunction(glMultTransposeMatrixd_gurax));
	frame.Assign(Gurax_CreateFunction(glMultTransposeMatrixf_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1d_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1dv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1f_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1fv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1i_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1iv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1s_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord1sv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2d_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2f_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2i_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2s_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord2sv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3d_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3f_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3i_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3s_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4d_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4f_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4i_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4s_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiTexCoord4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glSampleCoverage_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendColor_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquation_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFuncSeparate_gurax));
	frame.Assign(Gurax_CreateFunction(glFogCoordPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glFogCoordd_gurax));
	frame.Assign(Gurax_CreateFunction(glFogCoorddv_gurax));
	frame.Assign(Gurax_CreateFunction(glFogCoordf_gurax));
	frame.Assign(Gurax_CreateFunction(glFogCoordfv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiDrawArrays_gurax));
	frame.Assign(Gurax_CreateFunction(glPointParameterf_gurax));
	frame.Assign(Gurax_CreateFunction(glPointParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glPointParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glPointParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3b_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3bv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3d_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3f_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3i_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3s_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3ub_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3ubv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3ui_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3us_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColor3usv_gurax));
	frame.Assign(Gurax_CreateFunction(glSecondaryColorPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2d_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2f_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2i_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2s_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos2sv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3d_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3f_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3i_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3s_gurax));
	frame.Assign(Gurax_CreateFunction(glWindowPos3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glBeginQuery_gurax));
	frame.Assign(Gurax_CreateFunction(glBindBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glBufferData_gurax));
	frame.Assign(Gurax_CreateFunction(glBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteBuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteQueries_gurax));
	frame.Assign(Gurax_CreateFunction(glEndQuery_gurax));
	frame.Assign(Gurax_CreateFunction(glGenBuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glGenQueries_gurax));
	frame.Assign(Gurax_CreateFunction(glIsBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glIsQuery_gurax));
	frame.Assign(Gurax_CreateFunction(glUnmapBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glAttachShader_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationSeparate_gurax));
	frame.Assign(Gurax_CreateFunction(glCompileShader_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateShader_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteShader_gurax));
	frame.Assign(Gurax_CreateFunction(glDetachShader_gurax));
	frame.Assign(Gurax_CreateFunction(glDisableVertexAttribArray_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawBuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glEnableVertexAttribArray_gurax));
	frame.Assign(Gurax_CreateFunction(glIsProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glIsShader_gurax));
	frame.Assign(Gurax_CreateFunction(glLinkProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glStencilFuncSeparate_gurax));
	frame.Assign(Gurax_CreateFunction(glStencilMaskSeparate_gurax));
	frame.Assign(Gurax_CreateFunction(glStencilOpSeparate_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1f_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1i_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1iv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2f_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2i_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3f_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3i_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4f_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4i_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUseProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glValidateProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib1d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib1dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib1f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib1fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib1s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib1sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib2d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib2f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib2s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib2sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib3d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib3f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib3s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib3sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Nbv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Niv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Nsv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Nub_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Nubv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Nuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4Nusv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4bv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4d_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4f_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4s_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4ubv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttrib4usv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix2x3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix2x4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix3x2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix3x4fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix4x2fv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix4x3fv_gurax));
	frame.Assign(Gurax_CreateFunction(glBeginConditionalRender_gurax));
	frame.Assign(Gurax_CreateFunction(glBeginTransformFeedback_gurax));
	frame.Assign(Gurax_CreateFunction(glClampColor_gurax));
	frame.Assign(Gurax_CreateFunction(glClearBufferfi_gurax));
	frame.Assign(Gurax_CreateFunction(glClearBufferfv_gurax));
	frame.Assign(Gurax_CreateFunction(glClearBufferiv_gurax));
	frame.Assign(Gurax_CreateFunction(glClearBufferuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glColorMaski_gurax));
	frame.Assign(Gurax_CreateFunction(glDisablei_gurax));
	frame.Assign(Gurax_CreateFunction(glEnablei_gurax));
	frame.Assign(Gurax_CreateFunction(glEndConditionalRender_gurax));
	frame.Assign(Gurax_CreateFunction(glEndTransformFeedback_gurax));
	frame.Assign(Gurax_CreateFunction(glIsEnabledi_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameterIiv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameterIuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1ui_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2ui_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3ui_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4ui_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI1i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI1iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI1ui_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI1uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI2i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI2iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI2ui_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI2uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI3i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI3iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI3ui_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI3uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4bv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4i_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4iv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4sv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4ubv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4ui_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4uiv_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribI4usv_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawArraysInstanced_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsInstanced_gurax));
	frame.Assign(Gurax_CreateFunction(glPrimitiveRestartIndex_gurax));
	frame.Assign(Gurax_CreateFunction(glTexBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribDivisor_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationSeparatei_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationi_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFuncSeparatei_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFunci_gurax));
	frame.Assign(Gurax_CreateFunction(glMinSampleShading_gurax));
	frame.Assign(Gurax_CreateFunction(glGetGraphicsResetStatus_gurax));
	frame.Assign(Gurax_CreateFunction(glSpecializeShader_gurax));
}

Gurax_EndModuleScope(opengl)
