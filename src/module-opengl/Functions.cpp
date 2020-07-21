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

Gurax_ImplementFunctionEx(glewInit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLenum rtn = glewInit();
	return new Gurax::Value_Number(rtn);
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

Gurax_ImplementFunctionEx(glewIsSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	GLboolean rtn = glewIsSupported(name);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glewGetExtension_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	GLboolean rtn = glewGetExtension(name);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glewGetErrorString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum error = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetErrorString(error);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
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

Gurax_ImplementFunctionEx(glewGetString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum name = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glewGetString(name);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
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

Gurax_ImplementFunctionEx(glAccum_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum op = args_gurax.PickNumber<GLenum>();
	GLfloat value = args_gurax.PickNumber<GLfloat>();
	// Function body
	glAccum(op, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glAlphaFunc_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum func = args_gurax.PickNumber<GLenum>();
	GLclampf ref = args_gurax.PickNumber<GLclampf>();
	// Function body
	glAlphaFunc(func, ref);
	return Gurax::Value::nil();
}

// opengl.glAreTexturesResident(n:Number, textures[]:Number, residences:Pointer)
Gurax_DeclareFunctionAlias(glAreTexturesResident_gurax, "glAreTexturesResident")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textures", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("residences", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glAreTexturesResident_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	auto textures = args_gurax.PickNumList<GLuint>();
	GLboolean* residences = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLboolean>();
	if (!residences) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	GLboolean rtn = glAreTexturesResident(n, textures, residences);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glArrayElement_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint i = args_gurax.PickNumber<GLint>();
	// Function body
	glArrayElement(i);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBegin_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glBegin(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBindTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	// Function body
	glBindTexture(target, texture);
	return Gurax::Value::nil();
}

// opengl.glBitmap(width:Number, height:Number, xorig:Number, yorig:Number, xmove:Number, ymove:Number, bitmap:Pointer)
Gurax_DeclareFunctionAlias(glBitmap_gurax, "glBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xorig", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yorig", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xmove", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ymove", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBitmap_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLfloat xorig = args_gurax.PickNumber<GLfloat>();
	GLfloat yorig = args_gurax.PickNumber<GLfloat>();
	GLfloat xmove = args_gurax.PickNumber<GLfloat>();
	GLfloat ymove = args_gurax.PickNumber<GLfloat>();
	const GLubyte* bitmap = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLubyte>();
	// Function body
	glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendFunc_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum sfactor = args_gurax.PickNumber<GLenum>();
	GLenum dfactor = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendFunc(sfactor, dfactor);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCallList_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint list = args_gurax.PickNumber<GLuint>();
	// Function body
	glCallList(list);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCallLists_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* lists = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCallLists(n, type, lists);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClear_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbitfield mask = args_gurax.PickNumber<GLbitfield>();
	// Function body
	glClear(mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearAccum_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat red = args_gurax.PickNumber<GLfloat>();
	GLfloat green = args_gurax.PickNumber<GLfloat>();
	GLfloat blue = args_gurax.PickNumber<GLfloat>();
	GLfloat alpha = args_gurax.PickNumber<GLfloat>();
	// Function body
	glClearAccum(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearColor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampf red = args_gurax.PickNumber<GLclampf>();
	GLclampf green = args_gurax.PickNumber<GLclampf>();
	GLclampf blue = args_gurax.PickNumber<GLclampf>();
	GLclampf alpha = args_gurax.PickNumber<GLclampf>();
	// Function body
	glClearColor(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearDepth_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampd depth = args_gurax.PickNumber<GLclampd>();
	// Function body
	glClearDepth(depth);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat c = args_gurax.PickNumber<GLfloat>();
	// Function body
	glClearIndex(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearStencil_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint s = args_gurax.PickNumber<GLint>();
	// Function body
	glClearStencil(s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClipPlane_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum plane = args_gurax.PickNumber<GLenum>();
	auto equation = args_gurax.PickNumList<GLdouble>();
	// Function body
	glClipPlane(plane, equation);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3b_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbyte red = args_gurax.PickNumber<GLbyte>();
	GLbyte green = args_gurax.PickNumber<GLbyte>();
	GLbyte blue = args_gurax.PickNumber<GLbyte>();
	// Function body
	glColor3b(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3bv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLbyte>();
	// Function body
	glColor3bv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble red = args_gurax.PickNumber<GLdouble>();
	GLdouble green = args_gurax.PickNumber<GLdouble>();
	GLdouble blue = args_gurax.PickNumber<GLdouble>();
	// Function body
	glColor3d(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glColor3dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat red = args_gurax.PickNumber<GLfloat>();
	GLfloat green = args_gurax.PickNumber<GLfloat>();
	GLfloat blue = args_gurax.PickNumber<GLfloat>();
	// Function body
	glColor3f(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glColor3fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint red = args_gurax.PickNumber<GLint>();
	GLint green = args_gurax.PickNumber<GLint>();
	GLint blue = args_gurax.PickNumber<GLint>();
	// Function body
	glColor3i(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glColor3iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort red = args_gurax.PickNumber<GLshort>();
	GLshort green = args_gurax.PickNumber<GLshort>();
	GLshort blue = args_gurax.PickNumber<GLshort>();
	// Function body
	glColor3s(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glColor3sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3ub_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLubyte red = args_gurax.PickNumber<GLubyte>();
	GLubyte green = args_gurax.PickNumber<GLubyte>();
	GLubyte blue = args_gurax.PickNumber<GLubyte>();
	// Function body
	glColor3ub(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3ubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLubyte>();
	// Function body
	glColor3ubv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint red = args_gurax.PickNumber<GLuint>();
	GLuint green = args_gurax.PickNumber<GLuint>();
	GLuint blue = args_gurax.PickNumber<GLuint>();
	// Function body
	glColor3ui(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLuint>();
	// Function body
	glColor3uiv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3us_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLushort red = args_gurax.PickNumber<GLushort>();
	GLushort green = args_gurax.PickNumber<GLushort>();
	GLushort blue = args_gurax.PickNumber<GLushort>();
	// Function body
	glColor3us(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor3usv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLushort>();
	// Function body
	glColor3usv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4b_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbyte red = args_gurax.PickNumber<GLbyte>();
	GLbyte green = args_gurax.PickNumber<GLbyte>();
	GLbyte blue = args_gurax.PickNumber<GLbyte>();
	GLbyte alpha = args_gurax.PickNumber<GLbyte>();
	// Function body
	glColor4b(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4bv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLbyte>();
	// Function body
	glColor4bv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble red = args_gurax.PickNumber<GLdouble>();
	GLdouble green = args_gurax.PickNumber<GLdouble>();
	GLdouble blue = args_gurax.PickNumber<GLdouble>();
	GLdouble alpha = args_gurax.PickNumber<GLdouble>();
	// Function body
	glColor4d(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glColor4dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat red = args_gurax.PickNumber<GLfloat>();
	GLfloat green = args_gurax.PickNumber<GLfloat>();
	GLfloat blue = args_gurax.PickNumber<GLfloat>();
	GLfloat alpha = args_gurax.PickNumber<GLfloat>();
	// Function body
	glColor4f(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glColor4fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint red = args_gurax.PickNumber<GLint>();
	GLint green = args_gurax.PickNumber<GLint>();
	GLint blue = args_gurax.PickNumber<GLint>();
	GLint alpha = args_gurax.PickNumber<GLint>();
	// Function body
	glColor4i(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glColor4iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort red = args_gurax.PickNumber<GLshort>();
	GLshort green = args_gurax.PickNumber<GLshort>();
	GLshort blue = args_gurax.PickNumber<GLshort>();
	GLshort alpha = args_gurax.PickNumber<GLshort>();
	// Function body
	glColor4s(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glColor4sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4ub_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLubyte red = args_gurax.PickNumber<GLubyte>();
	GLubyte green = args_gurax.PickNumber<GLubyte>();
	GLubyte blue = args_gurax.PickNumber<GLubyte>();
	GLubyte alpha = args_gurax.PickNumber<GLubyte>();
	// Function body
	glColor4ub(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4ubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLubyte>();
	// Function body
	glColor4ubv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint red = args_gurax.PickNumber<GLuint>();
	GLuint green = args_gurax.PickNumber<GLuint>();
	GLuint blue = args_gurax.PickNumber<GLuint>();
	GLuint alpha = args_gurax.PickNumber<GLuint>();
	// Function body
	glColor4ui(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLuint>();
	// Function body
	glColor4uiv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4us_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLushort red = args_gurax.PickNumber<GLushort>();
	GLushort green = args_gurax.PickNumber<GLushort>();
	GLushort blue = args_gurax.PickNumber<GLushort>();
	GLushort alpha = args_gurax.PickNumber<GLushort>();
	// Function body
	glColor4us(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColor4usv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLushort>();
	// Function body
	glColor4usv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColorMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLboolean red = static_cast<GLboolean>(args_gurax.PickBool());
	GLboolean green = static_cast<GLboolean>(args_gurax.PickBool());
	GLboolean blue = static_cast<GLboolean>(args_gurax.PickBool());
	GLboolean alpha = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glColorMask(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColorMaterial_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glColorMaterial(face, mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColorPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glColorPointer(size, type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCopyPixels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	// Function body
	glCopyPixels(x, y, width, height, type);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCopyTexImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum internalFormat = args_gurax.PickNumber<GLenum>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	// Function body
	glCopyTexImage1D(target, level, internalFormat, x, y, width, border);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCopyTexImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum internalFormat = args_gurax.PickNumber<GLenum>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	// Function body
	glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCopyTexSubImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyTexSubImage1D(target, level, xoffset, x, y, width);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCopyTexSubImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCullFace_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glCullFace(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDeleteLists_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint list = args_gurax.PickNumber<GLuint>();
	GLsizei range = args_gurax.PickNumber<GLsizei>();
	// Function body
	glDeleteLists(list, range);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDeleteTextures_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto textures = args_gurax.PickNumList<GLuint>();
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

Gurax_ImplementFunctionEx(glDepthFunc_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum func = args_gurax.PickNumber<GLenum>();
	// Function body
	glDepthFunc(func);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDepthMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLboolean flag = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glDepthMask(flag);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDepthRange_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampd zNear = args_gurax.PickNumber<GLclampd>();
	GLclampd zFar = args_gurax.PickNumber<GLclampd>();
	// Function body
	glDepthRange(zNear, zFar);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDisable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum cap = args_gurax.PickNumber<GLenum>();
	// Function body
	glDisable(cap);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDisableClientState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum array = args_gurax.PickNumber<GLenum>();
	// Function body
	glDisableClientState(array);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawArrays_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLint first = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	// Function body
	glDrawArrays(mode, first, count);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glDrawBuffer(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawElements_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indices = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawElements(mode, count, type, indices);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawPixels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawPixels(width, height, format, type, pixels);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEdgeFlag_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLboolean flag = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glEdgeFlag(flag);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEdgeFlagPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glEdgeFlagPointer(stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEdgeFlagv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto flag = args_gurax.PickListT<GLboolean>([](Gurax::Value& value) {
		return value.GetBool()? GL_TRUE : GL_FALSE;
	});
	// Function body
	glEdgeFlagv(flag);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEnable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum cap = args_gurax.PickNumber<GLenum>();
	// Function body
	glEnable(cap);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEnableClientState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum array = args_gurax.PickNumber<GLenum>();
	// Function body
	glEnableClientState(array);
	return Gurax::Value::nil();
}

// opengl.glEnd()
Gurax_DeclareFunctionAlias(glEnd_gurax, "glEnd")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glEnd_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glEnd();
	return Gurax::Value::nil();
}

// opengl.glEndList()
Gurax_DeclareFunctionAlias(glEndList_gurax, "glEndList")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glEndList_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glEndList();
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble u = args_gurax.PickNumber<GLdouble>();
	// Function body
	glEvalCoord1d(u);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord1dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto u = args_gurax.PickNumList<GLdouble>();
	// Function body
	glEvalCoord1dv(u);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat u = args_gurax.PickNumber<GLfloat>();
	// Function body
	glEvalCoord1f(u);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord1fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto u = args_gurax.PickNumList<GLfloat>();
	// Function body
	glEvalCoord1fv(u);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble u = args_gurax.PickNumber<GLdouble>();
	GLdouble v = args_gurax.PickNumber<GLdouble>();
	// Function body
	glEvalCoord2d(u, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto u = args_gurax.PickNumList<GLdouble>();
	// Function body
	glEvalCoord2dv(u);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat u = args_gurax.PickNumber<GLfloat>();
	GLfloat v = args_gurax.PickNumber<GLfloat>();
	// Function body
	glEvalCoord2f(u, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalCoord2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto u = args_gurax.PickNumList<GLfloat>();
	// Function body
	glEvalCoord2fv(u);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalMesh1_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLint i1 = args_gurax.PickNumber<GLint>();
	GLint i2 = args_gurax.PickNumber<GLint>();
	// Function body
	glEvalMesh1(mode, i1, i2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalMesh2_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLint i1 = args_gurax.PickNumber<GLint>();
	GLint i2 = args_gurax.PickNumber<GLint>();
	GLint j1 = args_gurax.PickNumber<GLint>();
	GLint j2 = args_gurax.PickNumber<GLint>();
	// Function body
	glEvalMesh2(mode, i1, i2, j1, j2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalPoint1_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint i = args_gurax.PickNumber<GLint>();
	// Function body
	glEvalPoint1(i);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEvalPoint2_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint i = args_gurax.PickNumber<GLint>();
	GLint j = args_gurax.PickNumber<GLint>();
	// Function body
	glEvalPoint2(i, j);
	return Gurax::Value::nil();
}

// opengl.glFeedbackBuffer(size:Number, type:Number, buffer:Pointer)
Gurax_DeclareFunctionAlias(glFeedbackBuffer_gurax, "glFeedbackBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFeedbackBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei size = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLfloat* buffer = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!buffer) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glFeedbackBuffer(size, type, buffer);
	return Gurax::Value::nil();
}

// opengl.glFinish()
Gurax_DeclareFunctionAlias(glFinish_gurax, "glFinish")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFinish_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glFinish();
	return Gurax::Value::nil();
}

// opengl.glFlush()
Gurax_DeclareFunctionAlias(glFlush_gurax, "glFlush")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFlush_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glFlush();
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glFogf(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glFogfv(pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glFogi(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glFogiv(pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFrontFace_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glFrontFace(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFrustum_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble left = args_gurax.PickNumber<GLdouble>();
	GLdouble right = args_gurax.PickNumber<GLdouble>();
	GLdouble bottom = args_gurax.PickNumber<GLdouble>();
	GLdouble top = args_gurax.PickNumber<GLdouble>();
	GLdouble zNear = args_gurax.PickNumber<GLdouble>();
	GLdouble zFar = args_gurax.PickNumber<GLdouble>();
	// Function body
	glFrustum(left, right, bottom, top, zNear, zFar);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glGenLists_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei range = args_gurax.PickNumber<GLsizei>();
	// Function body
	GLuint rtn = glGenLists(range);
	return new Gurax::Value_Number(rtn);
}

// opengl.glGenTextures(n:Number, textures:Pointer)
Gurax_DeclareFunctionAlias(glGenTextures_gurax, "glGenTextures")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textures", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenTextures_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* textures = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!textures) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGenTextures(n, textures);
	return Gurax::Value::nil();
}

// opengl.glGetBooleanv(pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetBooleanv_gurax, "glGetBooleanv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetBooleanv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLboolean* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLboolean>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetBooleanv(pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetClipPlane(plane:Number, equation:Pointer)
Gurax_DeclareFunctionAlias(glGetClipPlane_gurax, "glGetClipPlane")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("plane", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("equation", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetClipPlane_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum plane = args_gurax.PickNumber<GLenum>();
	GLdouble* equation = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!equation) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetClipPlane(plane, equation);
	return Gurax::Value::nil();
}

// opengl.glGetDoublev(pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetDoublev_gurax, "glGetDoublev")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetDoublev_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLdouble* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetDoublev(pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetError()
Gurax_DeclareFunctionAlias(glGetError_gurax, "glGetError")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLenum rtn = glGetError();
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetFloatv(pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetFloatv_gurax, "glGetFloatv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetFloatv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetFloatv(pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetIntegerv(pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetIntegerv_gurax, "glGetIntegerv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetIntegerv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetIntegerv(pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetLightfv(light:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetLightfv_gurax, "glGetLightfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetLightfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum light = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetLightfv(light, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetLightiv(light:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetLightiv_gurax, "glGetLightiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("light", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetLightiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum light = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetLightiv(light, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetMapdv(target:Number, query:Number, v:Pointer)
Gurax_DeclareFunctionAlias(glGetMapdv_gurax, "glGetMapdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("query", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetMapdv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum query = args_gurax.PickNumber<GLenum>();
	GLdouble* v = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!v) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetMapdv(target, query, v);
	return Gurax::Value::nil();
}

// opengl.glGetMapfv(target:Number, query:Number, v:Pointer)
Gurax_DeclareFunctionAlias(glGetMapfv_gurax, "glGetMapfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("query", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetMapfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum query = args_gurax.PickNumber<GLenum>();
	GLfloat* v = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!v) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetMapfv(target, query, v);
	return Gurax::Value::nil();
}

// opengl.glGetMapiv(target:Number, query:Number, v:Pointer)
Gurax_DeclareFunctionAlias(glGetMapiv_gurax, "glGetMapiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("query", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetMapiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum query = args_gurax.PickNumber<GLenum>();
	GLint* v = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!v) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetMapiv(target, query, v);
	return Gurax::Value::nil();
}

// opengl.glGetMaterialfv(face:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetMaterialfv_gurax, "glGetMaterialfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetMaterialfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetMaterialfv(face, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetMaterialiv(face:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetMaterialiv_gurax, "glGetMaterialiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetMaterialiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetMaterialiv(face, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetPixelMapfv(map:Number, values:Pointer)
Gurax_DeclareFunctionAlias(glGetPixelMapfv_gurax, "glGetPixelMapfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetPixelMapfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum map = args_gurax.PickNumber<GLenum>();
	GLfloat* values = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!values) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetPixelMapfv(map, values);
	return Gurax::Value::nil();
}

// opengl.glGetPixelMapuiv(map:Number, values:Pointer)
Gurax_DeclareFunctionAlias(glGetPixelMapuiv_gurax, "glGetPixelMapuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetPixelMapuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum map = args_gurax.PickNumber<GLenum>();
	GLuint* values = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!values) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetPixelMapuiv(map, values);
	return Gurax::Value::nil();
}

// opengl.glGetPixelMapusv(map:Number, values:Pointer)
Gurax_DeclareFunctionAlias(glGetPixelMapusv_gurax, "glGetPixelMapusv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("map", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetPixelMapusv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum map = args_gurax.PickNumber<GLenum>();
	GLushort* values = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLushort>();
	if (!values) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetPixelMapusv(map, values);
	return Gurax::Value::nil();
}

// opengl.glGetPolygonStipple(mask:Pointer)
Gurax_DeclareFunctionAlias(glGetPolygonStipple_gurax, "glGetPolygonStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetPolygonStipple_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLubyte* mask = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLubyte>();
	if (!mask) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetPolygonStipple(mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glGetString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum name = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = glGetString(name);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glGetTexEnvfv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexEnvfv_gurax, "glGetTexEnvfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexEnvfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexEnvfv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexEnviv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexEnviv_gurax, "glGetTexEnviv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexEnviv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexEnviv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexGendv(coord:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexGendv_gurax, "glGetTexGendv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexGendv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLdouble* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexGendv(coord, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexGenfv(coord:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexGenfv_gurax, "glGetTexGenfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexGenfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexGenfv(coord, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexGeniv(coord:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexGeniv_gurax, "glGetTexGeniv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("coord", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexGeniv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexGeniv(coord, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexImage(target:Number, level:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetTexImage_gurax, "glGetTexImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexImage(target, level, format, type, pixels);
	return Gurax::Value::nil();
}

// opengl.glGetTexLevelParameterfv(target:Number, level:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexLevelParameterfv_gurax, "glGetTexLevelParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexLevelParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexLevelParameterfv(target, level, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexLevelParameteriv(target:Number, level:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexLevelParameteriv_gurax, "glGetTexLevelParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexLevelParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexLevelParameteriv(target, level, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexParameterfv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexParameterfv_gurax, "glGetTexParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexParameterfv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexParameteriv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexParameteriv_gurax, "glGetTexParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexParameteriv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glHint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glHint(target, mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint mask = args_gurax.PickNumber<GLuint>();
	// Function body
	glIndexMask(mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glIndexPointer(type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble c = args_gurax.PickNumber<GLdouble>();
	// Function body
	glIndexd(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexdv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto c = args_gurax.PickNumList<GLdouble>();
	// Function body
	glIndexdv(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat c = args_gurax.PickNumber<GLfloat>();
	// Function body
	glIndexf(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto c = args_gurax.PickNumList<GLfloat>();
	// Function body
	glIndexfv(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint c = args_gurax.PickNumber<GLint>();
	// Function body
	glIndexi(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto c = args_gurax.PickNumList<GLint>();
	// Function body
	glIndexiv(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexs_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort c = args_gurax.PickNumber<GLshort>();
	// Function body
	glIndexs(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexsv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto c = args_gurax.PickNumList<GLshort>();
	// Function body
	glIndexsv(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexub_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLubyte c = args_gurax.PickNumber<GLubyte>();
	// Function body
	glIndexub(c);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIndexubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto c = args_gurax.PickNumList<GLubyte>();
	// Function body
	glIndexubv(c);
	return Gurax::Value::nil();
}

// opengl.glInitNames()
Gurax_DeclareFunctionAlias(glInitNames_gurax, "glInitNames")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glInitNames_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glInitNames();
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glInterleavedArrays_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glInterleavedArrays(format, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIsEnabled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum cap = args_gurax.PickNumber<GLenum>();
	// Function body
	GLboolean rtn = glIsEnabled(cap);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glIsList_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint list = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsList(list);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glIsTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsTexture(texture);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glLightModelf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glLightModelf(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLightModelfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glLightModelfv(pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLightModeli_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glLightModeli(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLightModeliv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glLightModeliv(pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLightf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum light = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glLightf(light, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLightfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum light = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glLightfv(light, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLighti_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum light = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glLighti(light, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLightiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum light = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glLightiv(light, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLineStipple_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint factor = args_gurax.PickNumber<GLint>();
	GLushort pattern = args_gurax.PickNumber<GLushort>();
	// Function body
	glLineStipple(factor, pattern);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLineWidth_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat width = args_gurax.PickNumber<GLfloat>();
	// Function body
	glLineWidth(width);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glListBase_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint base = args_gurax.PickNumber<GLuint>();
	// Function body
	glListBase(base);
	return Gurax::Value::nil();
}

// opengl.glLoadIdentity()
Gurax_DeclareFunctionAlias(glLoadIdentity_gurax, "glLoadIdentity")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glLoadIdentity_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glLoadIdentity();
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLoadMatrixd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLdouble>();
	// Function body
	glLoadMatrixd(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLoadMatrixf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLfloat>();
	// Function body
	glLoadMatrixf(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLoadName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint name = args_gurax.PickNumber<GLuint>();
	// Function body
	glLoadName(name);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLogicOp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum opcode = args_gurax.PickNumber<GLenum>();
	// Function body
	glLogicOp(opcode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMap1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLdouble u1 = args_gurax.PickNumber<GLdouble>();
	GLdouble u2 = args_gurax.PickNumber<GLdouble>();
	GLint stride = args_gurax.PickNumber<GLint>();
	GLint order = args_gurax.PickNumber<GLint>();
	auto points = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMap1d(target, u1, u2, stride, order, points);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMap1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLfloat u1 = args_gurax.PickNumber<GLfloat>();
	GLfloat u2 = args_gurax.PickNumber<GLfloat>();
	GLint stride = args_gurax.PickNumber<GLint>();
	GLint order = args_gurax.PickNumber<GLint>();
	auto points = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMap1f(target, u1, u2, stride, order, points);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMap2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLdouble u1 = args_gurax.PickNumber<GLdouble>();
	GLdouble u2 = args_gurax.PickNumber<GLdouble>();
	GLint ustride = args_gurax.PickNumber<GLint>();
	GLint uorder = args_gurax.PickNumber<GLint>();
	GLdouble v1 = args_gurax.PickNumber<GLdouble>();
	GLdouble v2 = args_gurax.PickNumber<GLdouble>();
	GLint vstride = args_gurax.PickNumber<GLint>();
	GLint vorder = args_gurax.PickNumber<GLint>();
	auto points = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMap2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLfloat u1 = args_gurax.PickNumber<GLfloat>();
	GLfloat u2 = args_gurax.PickNumber<GLfloat>();
	GLint ustride = args_gurax.PickNumber<GLint>();
	GLint uorder = args_gurax.PickNumber<GLint>();
	GLfloat v1 = args_gurax.PickNumber<GLfloat>();
	GLfloat v2 = args_gurax.PickNumber<GLfloat>();
	GLint vstride = args_gurax.PickNumber<GLint>();
	GLint vorder = args_gurax.PickNumber<GLint>();
	auto points = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMapGrid1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint un = args_gurax.PickNumber<GLint>();
	GLdouble u1 = args_gurax.PickNumber<GLdouble>();
	GLdouble u2 = args_gurax.PickNumber<GLdouble>();
	// Function body
	glMapGrid1d(un, u1, u2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMapGrid1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint un = args_gurax.PickNumber<GLint>();
	GLfloat u1 = args_gurax.PickNumber<GLfloat>();
	GLfloat u2 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMapGrid1f(un, u1, u2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMapGrid2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint un = args_gurax.PickNumber<GLint>();
	GLdouble u1 = args_gurax.PickNumber<GLdouble>();
	GLdouble u2 = args_gurax.PickNumber<GLdouble>();
	GLint vn = args_gurax.PickNumber<GLint>();
	GLdouble v1 = args_gurax.PickNumber<GLdouble>();
	GLdouble v2 = args_gurax.PickNumber<GLdouble>();
	// Function body
	glMapGrid2d(un, u1, u2, vn, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMapGrid2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint un = args_gurax.PickNumber<GLint>();
	GLfloat u1 = args_gurax.PickNumber<GLfloat>();
	GLfloat u2 = args_gurax.PickNumber<GLfloat>();
	GLint vn = args_gurax.PickNumber<GLint>();
	GLfloat v1 = args_gurax.PickNumber<GLfloat>();
	GLfloat v2 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMapGrid2f(un, u1, u2, vn, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMaterialf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMaterialf(face, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMaterialfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMaterialfv(face, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMateriali_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glMateriali(face, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMaterialiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glMaterialiv(face, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMatrixMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glMatrixMode(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultMatrixd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMultMatrixd(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultMatrixf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMultMatrixf(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNewList_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint list = args_gurax.PickNumber<GLuint>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glNewList(list, mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3b_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbyte nx = args_gurax.PickNumber<GLbyte>();
	GLbyte ny = args_gurax.PickNumber<GLbyte>();
	GLbyte nz = args_gurax.PickNumber<GLbyte>();
	// Function body
	glNormal3b(nx, ny, nz);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3bv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLbyte>();
	// Function body
	glNormal3bv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble nx = args_gurax.PickNumber<GLdouble>();
	GLdouble ny = args_gurax.PickNumber<GLdouble>();
	GLdouble nz = args_gurax.PickNumber<GLdouble>();
	// Function body
	glNormal3d(nx, ny, nz);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glNormal3dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat nx = args_gurax.PickNumber<GLfloat>();
	GLfloat ny = args_gurax.PickNumber<GLfloat>();
	GLfloat nz = args_gurax.PickNumber<GLfloat>();
	// Function body
	glNormal3f(nx, ny, nz);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glNormal3fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint nx = args_gurax.PickNumber<GLint>();
	GLint ny = args_gurax.PickNumber<GLint>();
	GLint nz = args_gurax.PickNumber<GLint>();
	// Function body
	glNormal3i(nx, ny, nz);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glNormal3iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort nx = args_gurax.PickNumber<GLshort>();
	GLshort ny = args_gurax.PickNumber<GLshort>();
	GLshort nz = args_gurax.PickNumber<GLshort>();
	// Function body
	glNormal3s(nx, ny, nz);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glNormal3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glNormal3sv(v);
	return Gurax::Value::nil();
}

// opengl.glNormalPointer(type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glNormalPointer_gurax, "glNormalPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNormalPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glNormalPointer(type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glOrtho_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble left = args_gurax.PickNumber<GLdouble>();
	GLdouble right = args_gurax.PickNumber<GLdouble>();
	GLdouble bottom = args_gurax.PickNumber<GLdouble>();
	GLdouble top = args_gurax.PickNumber<GLdouble>();
	GLdouble zNear = args_gurax.PickNumber<GLdouble>();
	GLdouble zFar = args_gurax.PickNumber<GLdouble>();
	// Function body
	glOrtho(left, right, bottom, top, zNear, zFar);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPassThrough_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat token = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPassThrough(token);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelMapfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum map = args_gurax.PickNumber<GLenum>();
	GLsizei mapsize = args_gurax.PickNumber<GLsizei>();
	auto values = args_gurax.PickNumList<GLfloat>();
	// Function body
	glPixelMapfv(map, mapsize, values);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelMapuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum map = args_gurax.PickNumber<GLenum>();
	GLsizei mapsize = args_gurax.PickNumber<GLsizei>();
	auto values = args_gurax.PickNumList<GLuint>();
	// Function body
	glPixelMapuiv(map, mapsize, values);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelMapusv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum map = args_gurax.PickNumber<GLenum>();
	GLsizei mapsize = args_gurax.PickNumber<GLsizei>();
	auto values = args_gurax.PickNumList<GLushort>();
	// Function body
	glPixelMapusv(map, mapsize, values);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelStoref_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPixelStoref(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelStorei_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glPixelStorei(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelTransferf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPixelTransferf(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelTransferi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glPixelTransferi(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPixelZoom_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat xfactor = args_gurax.PickNumber<GLfloat>();
	GLfloat yfactor = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPixelZoom(xfactor, yfactor);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPointSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat size = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPointSize(size);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPolygonMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glPolygonMode(face, mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPolygonOffset_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat factor = args_gurax.PickNumber<GLfloat>();
	GLfloat units = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPolygonOffset(factor, units);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPolygonStipple_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto mask = args_gurax.PickNumList<GLubyte>();
	// Function body
	glPolygonStipple(mask);
	return Gurax::Value::nil();
}

// opengl.glPopAttrib()
Gurax_DeclareFunctionAlias(glPopAttrib_gurax, "glPopAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glPopAttrib_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glPopAttrib();
	return Gurax::Value::nil();
}

// opengl.glPopClientAttrib()
Gurax_DeclareFunctionAlias(glPopClientAttrib_gurax, "glPopClientAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glPopClientAttrib_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glPopClientAttrib();
	return Gurax::Value::nil();
}

// opengl.glPopMatrix()
Gurax_DeclareFunctionAlias(glPopMatrix_gurax, "glPopMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glPopMatrix_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glPopMatrix();
	return Gurax::Value::nil();
}

// opengl.glPopName()
Gurax_DeclareFunctionAlias(glPopName_gurax, "glPopName")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glPopName_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glPopName();
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPrioritizeTextures_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	auto textures = args_gurax.PickNumList<GLuint>();
	auto priorities = args_gurax.PickNumList<GLclampf>();
	// Function body
	glPrioritizeTextures(n, textures, priorities);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPushAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbitfield mask = args_gurax.PickNumber<GLbitfield>();
	// Function body
	glPushAttrib(mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPushClientAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbitfield mask = args_gurax.PickNumber<GLbitfield>();
	// Function body
	glPushClientAttrib(mask);
	return Gurax::Value::nil();
}

// opengl.glPushMatrix()
Gurax_DeclareFunctionAlias(glPushMatrix_gurax, "glPushMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glPushMatrix_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glPushMatrix();
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPushName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint name = args_gurax.PickNumber<GLuint>();
	// Function body
	glPushName(name);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	// Function body
	glRasterPos2d(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glRasterPos2dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	// Function body
	glRasterPos2f(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glRasterPos2fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	// Function body
	glRasterPos2i(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glRasterPos2iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	// Function body
	glRasterPos2s(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos2sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glRasterPos2sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glRasterPos3d(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glRasterPos3dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glRasterPos3f(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glRasterPos3fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLint z = args_gurax.PickNumber<GLint>();
	// Function body
	glRasterPos3i(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glRasterPos3iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	// Function body
	glRasterPos3s(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glRasterPos3sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	GLdouble w = args_gurax.PickNumber<GLdouble>();
	// Function body
	glRasterPos4d(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glRasterPos4dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	GLfloat w = args_gurax.PickNumber<GLfloat>();
	// Function body
	glRasterPos4f(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glRasterPos4fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLint z = args_gurax.PickNumber<GLint>();
	GLint w = args_gurax.PickNumber<GLint>();
	// Function body
	glRasterPos4i(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glRasterPos4iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	GLshort w = args_gurax.PickNumber<GLshort>();
	// Function body
	glRasterPos4s(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRasterPos4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glRasterPos4sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glReadBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glReadBuffer(mode);
	return Gurax::Value::nil();
}

// opengl.glReadPixels(x:Number, y:Number, width:Number, height:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glReadPixels_gurax, "glReadPixels")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glReadPixels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glReadPixels(x, y, width, height, format, type, pixels);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRectd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x1 = args_gurax.PickNumber<GLdouble>();
	GLdouble y1 = args_gurax.PickNumber<GLdouble>();
	GLdouble x2 = args_gurax.PickNumber<GLdouble>();
	GLdouble y2 = args_gurax.PickNumber<GLdouble>();
	// Function body
	glRectd(x1, y1, x2, y2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRectdv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v1 = args_gurax.PickNumList<GLdouble>();
	auto v2 = args_gurax.PickNumList<GLdouble>();
	// Function body
	glRectdv(v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRectf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x1 = args_gurax.PickNumber<GLfloat>();
	GLfloat y1 = args_gurax.PickNumber<GLfloat>();
	GLfloat x2 = args_gurax.PickNumber<GLfloat>();
	GLfloat y2 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glRectf(x1, y1, x2, y2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRectfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v1 = args_gurax.PickNumList<GLfloat>();
	auto v2 = args_gurax.PickNumList<GLfloat>();
	// Function body
	glRectfv(v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRecti_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x1 = args_gurax.PickNumber<GLint>();
	GLint y1 = args_gurax.PickNumber<GLint>();
	GLint x2 = args_gurax.PickNumber<GLint>();
	GLint y2 = args_gurax.PickNumber<GLint>();
	// Function body
	glRecti(x1, y1, x2, y2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRectiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v1 = args_gurax.PickNumList<GLint>();
	auto v2 = args_gurax.PickNumList<GLint>();
	// Function body
	glRectiv(v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x1 = args_gurax.PickNumber<GLshort>();
	GLshort y1 = args_gurax.PickNumber<GLshort>();
	GLshort x2 = args_gurax.PickNumber<GLshort>();
	GLshort y2 = args_gurax.PickNumber<GLshort>();
	// Function body
	glRects(x1, y1, x2, y2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRectsv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v1 = args_gurax.PickNumList<GLshort>();
	auto v2 = args_gurax.PickNumList<GLshort>();
	// Function body
	glRectsv(v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRenderMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	GLint rtn = glRenderMode(mode);
	return new Gurax::Value_Number(rtn);
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

Gurax_ImplementFunctionEx(glRotated_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble angle = args_gurax.PickNumber<GLdouble>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glRotated(angle, x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glRotatef_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat angle = args_gurax.PickNumber<GLfloat>();
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glRotatef(angle, x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glScaled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glScaled(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glScalef_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glScalef(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glScissor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glScissor(x, y, width, height);
	return Gurax::Value::nil();
}

// opengl.glSelectBuffer(size:Number, buffer:Pointer)
Gurax_DeclareFunctionAlias(glSelectBuffer_gurax, "glSelectBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glSelectBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei size = args_gurax.PickNumber<GLsizei>();
	GLuint* buffer = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!buffer) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glSelectBuffer(size, buffer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glShadeModel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glShadeModel(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glStencilFunc_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum func = args_gurax.PickNumber<GLenum>();
	GLint ref = args_gurax.PickNumber<GLint>();
	GLuint mask = args_gurax.PickNumber<GLuint>();
	// Function body
	glStencilFunc(func, ref, mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glStencilMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint mask = args_gurax.PickNumber<GLuint>();
	// Function body
	glStencilMask(mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glStencilOp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum fail = args_gurax.PickNumber<GLenum>();
	GLenum zfail = args_gurax.PickNumber<GLenum>();
	GLenum zpass = args_gurax.PickNumber<GLenum>();
	// Function body
	glStencilOp(fail, zfail, zpass);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	// Function body
	glTexCoord1d(s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glTexCoord1dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexCoord1f(s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexCoord1fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint s = args_gurax.PickNumber<GLint>();
	// Function body
	glTexCoord1i(s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glTexCoord1iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort s = args_gurax.PickNumber<GLshort>();
	// Function body
	glTexCoord1s(s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord1sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glTexCoord1sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	GLdouble t = args_gurax.PickNumber<GLdouble>();
	// Function body
	glTexCoord2d(s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glTexCoord2dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	GLfloat t = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexCoord2f(s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexCoord2fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint s = args_gurax.PickNumber<GLint>();
	GLint t = args_gurax.PickNumber<GLint>();
	// Function body
	glTexCoord2i(s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glTexCoord2iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort s = args_gurax.PickNumber<GLshort>();
	GLshort t = args_gurax.PickNumber<GLshort>();
	// Function body
	glTexCoord2s(s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord2sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glTexCoord2sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	GLdouble t = args_gurax.PickNumber<GLdouble>();
	GLdouble r = args_gurax.PickNumber<GLdouble>();
	// Function body
	glTexCoord3d(s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glTexCoord3dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	GLfloat t = args_gurax.PickNumber<GLfloat>();
	GLfloat r = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexCoord3f(s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexCoord3fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint s = args_gurax.PickNumber<GLint>();
	GLint t = args_gurax.PickNumber<GLint>();
	GLint r = args_gurax.PickNumber<GLint>();
	// Function body
	glTexCoord3i(s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glTexCoord3iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort s = args_gurax.PickNumber<GLshort>();
	GLshort t = args_gurax.PickNumber<GLshort>();
	GLshort r = args_gurax.PickNumber<GLshort>();
	// Function body
	glTexCoord3s(s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glTexCoord3sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	GLdouble t = args_gurax.PickNumber<GLdouble>();
	GLdouble r = args_gurax.PickNumber<GLdouble>();
	GLdouble q = args_gurax.PickNumber<GLdouble>();
	// Function body
	glTexCoord4d(s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glTexCoord4dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	GLfloat t = args_gurax.PickNumber<GLfloat>();
	GLfloat r = args_gurax.PickNumber<GLfloat>();
	GLfloat q = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexCoord4f(s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexCoord4fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint s = args_gurax.PickNumber<GLint>();
	GLint t = args_gurax.PickNumber<GLint>();
	GLint r = args_gurax.PickNumber<GLint>();
	GLint q = args_gurax.PickNumber<GLint>();
	// Function body
	glTexCoord4i(s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glTexCoord4iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort s = args_gurax.PickNumber<GLshort>();
	GLshort t = args_gurax.PickNumber<GLshort>();
	GLshort r = args_gurax.PickNumber<GLshort>();
	GLshort q = args_gurax.PickNumber<GLshort>();
	// Function body
	glTexCoord4s(s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexCoord4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glTexCoord4sv(v);
	return Gurax::Value::nil();
}

// opengl.glTexCoordPointer(size:Number, type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glTexCoordPointer_gurax, "glTexCoordPointer")
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

Gurax_ImplementFunctionEx(glTexCoordPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTexCoordPointer(size, type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexEnvf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexEnvf(target, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexEnvfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexEnvfv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexEnvi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glTexEnvi(target, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexEnviv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glTexEnviv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexGend_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLdouble param = args_gurax.PickNumber<GLdouble>();
	// Function body
	glTexGend(coord, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexGendv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLdouble>();
	// Function body
	glTexGendv(coord, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexGenf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexGenf(coord, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexGenfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexGenfv(coord, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexGeni_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glTexGeni(coord, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexGeniv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum coord = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glTexGeniv(coord, pname, params);
	return Gurax::Value::nil();
}

// opengl.glTexImage1D(target:Number, level:Number, internalformat:Number, width:Number, border:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTexImage1D_gurax, "glTexImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTexImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint internalformat = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
	return Gurax::Value::nil();
}

// opengl.glTexImage2D(target:Number, level:Number, internalformat:Number, width:Number, height:Number, border:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTexImage2D_gurax, "glTexImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTexImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint internalformat = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexParameterf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTexParameterf(target, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glTexParameterfv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexParameteri_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glTexParameteri(target, pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glTexParameteriv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glTexSubImage1D(target:Number, level:Number, xoffset:Number, width:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTexSubImage1D_gurax, "glTexSubImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTexSubImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	return Gurax::Value::nil();
}

// opengl.glTexSubImage2D(target:Number, level:Number, xoffset:Number, yoffset:Number, width:Number, height:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTexSubImage2D_gurax, "glTexSubImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTexSubImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTranslated_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glTranslated(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTranslatef_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTranslatef(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertex2d(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertex2dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertex2f(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertex2fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	// Function body
	glVertex2i(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glVertex2iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertex2s(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex2sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertex2sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertex3d(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertex3dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertex3f(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertex3fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLint z = args_gurax.PickNumber<GLint>();
	// Function body
	glVertex3i(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glVertex3iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertex3s(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertex3sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	GLdouble w = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertex4d(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertex4dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	GLfloat w = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertex4f(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertex4fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLint z = args_gurax.PickNumber<GLint>();
	GLint w = args_gurax.PickNumber<GLint>();
	// Function body
	glVertex4i(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glVertex4iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	GLshort w = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertex4s(x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertex4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertex4sv(v);
	return Gurax::Value::nil();
}

// opengl.glVertexPointer(size:Number, type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glVertexPointer_gurax, "glVertexPointer")
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

Gurax_ImplementFunctionEx(glVertexPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glVertexPointer(size, type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glViewport_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glViewport(x, y, width, height);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCopyTexSubImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawRangeElements_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLuint start = args_gurax.PickNumber<GLuint>();
	GLuint end = args_gurax.PickNumber<GLuint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indices = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawRangeElements(mode, start, end, count, type, indices);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint internalFormat = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexSubImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glActiveTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum texture = args_gurax.PickNumber<GLenum>();
	// Function body
	glActiveTexture(texture);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClientActiveTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum texture = args_gurax.PickNumber<GLenum>();
	// Function body
	glClientActiveTexture(texture);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompressedTexImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompressedTexImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompressedTexImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLint border = args_gurax.PickNumber<GLint>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompressedTexSubImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompressedTexSubImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompressedTexSubImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	return Gurax::Value::nil();
}

// opengl.glGetCompressedTexImage(target:Number, lod:Number, img:Pointer)
Gurax_DeclareFunctionAlias(glGetCompressedTexImage_gurax, "glGetCompressedTexImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lod", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("img", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetCompressedTexImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint lod = args_gurax.PickNumber<GLint>();
	void* img = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!img) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetCompressedTexImage(target, lod, img);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLoadTransposeMatrixd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLdouble>();
	// Function body
	glLoadTransposeMatrixd(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glLoadTransposeMatrixf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLfloat>();
	// Function body
	glLoadTransposeMatrixf(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultTransposeMatrixd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMultTransposeMatrixd(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultTransposeMatrixf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto m = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMultTransposeMatrixf(m);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord1d(target, s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord1dv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord1f(target, s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord1fv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint s = args_gurax.PickNumber<GLint>();
	// Function body
	glMultiTexCoord1i(target, s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glMultiTexCoord1iv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLshort s = args_gurax.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord1s(target, s);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord1sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord1sv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	GLdouble t = args_gurax.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord2d(target, s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord2dv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	GLfloat t = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord2f(target, s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord2fv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint s = args_gurax.PickNumber<GLint>();
	GLint t = args_gurax.PickNumber<GLint>();
	// Function body
	glMultiTexCoord2i(target, s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glMultiTexCoord2iv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLshort s = args_gurax.PickNumber<GLshort>();
	GLshort t = args_gurax.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord2s(target, s, t);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord2sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord2sv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	GLdouble t = args_gurax.PickNumber<GLdouble>();
	GLdouble r = args_gurax.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord3d(target, s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord3dv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	GLfloat t = args_gurax.PickNumber<GLfloat>();
	GLfloat r = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord3f(target, s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord3fv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint s = args_gurax.PickNumber<GLint>();
	GLint t = args_gurax.PickNumber<GLint>();
	GLint r = args_gurax.PickNumber<GLint>();
	// Function body
	glMultiTexCoord3i(target, s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glMultiTexCoord3iv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLshort s = args_gurax.PickNumber<GLshort>();
	GLshort t = args_gurax.PickNumber<GLshort>();
	GLshort r = args_gurax.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord3s(target, s, t, r);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord3sv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLdouble s = args_gurax.PickNumber<GLdouble>();
	GLdouble t = args_gurax.PickNumber<GLdouble>();
	GLdouble r = args_gurax.PickNumber<GLdouble>();
	GLdouble q = args_gurax.PickNumber<GLdouble>();
	// Function body
	glMultiTexCoord4d(target, s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glMultiTexCoord4dv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLfloat s = args_gurax.PickNumber<GLfloat>();
	GLfloat t = args_gurax.PickNumber<GLfloat>();
	GLfloat r = args_gurax.PickNumber<GLfloat>();
	GLfloat q = args_gurax.PickNumber<GLfloat>();
	// Function body
	glMultiTexCoord4f(target, s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glMultiTexCoord4fv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint s = args_gurax.PickNumber<GLint>();
	GLint t = args_gurax.PickNumber<GLint>();
	GLint r = args_gurax.PickNumber<GLint>();
	GLint q = args_gurax.PickNumber<GLint>();
	// Function body
	glMultiTexCoord4i(target, s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glMultiTexCoord4iv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLshort s = args_gurax.PickNumber<GLshort>();
	GLshort t = args_gurax.PickNumber<GLshort>();
	GLshort r = args_gurax.PickNumber<GLshort>();
	GLshort q = args_gurax.PickNumber<GLshort>();
	// Function body
	glMultiTexCoord4s(target, s, t, r, q);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiTexCoord4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glMultiTexCoord4sv(target, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSampleCoverage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampf value = args_gurax.PickNumber<GLclampf>();
	GLboolean invert = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glSampleCoverage(value, invert);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendColor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampf red = args_gurax.PickNumber<GLclampf>();
	GLclampf green = args_gurax.PickNumber<GLclampf>();
	GLclampf blue = args_gurax.PickNumber<GLclampf>();
	GLclampf alpha = args_gurax.PickNumber<GLclampf>();
	// Function body
	glBlendColor(red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendEquation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendEquation(mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendFuncSeparate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum sfactorRGB = args_gurax.PickNumber<GLenum>();
	GLenum dfactorRGB = args_gurax.PickNumber<GLenum>();
	GLenum sfactorAlpha = args_gurax.PickNumber<GLenum>();
	GLenum dfactorAlpha = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogCoordPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glFogCoordPointer(type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogCoordd_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble coord = args_gurax.PickNumber<GLdouble>();
	// Function body
	glFogCoordd(coord);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogCoorddv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto coord = args_gurax.PickNumList<GLdouble>();
	// Function body
	glFogCoorddv(coord);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogCoordf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat coord = args_gurax.PickNumber<GLfloat>();
	// Function body
	glFogCoordf(coord);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFogCoordfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto coord = args_gurax.PickNumList<GLfloat>();
	// Function body
	glFogCoordfv(coord);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMultiDrawArrays_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	auto first = args_gurax.PickNumList<GLint>();
	auto count = args_gurax.PickNumList<GLsizei>();
	GLsizei drawcount = args_gurax.PickNumber<GLsizei>();
	// Function body
	glMultiDrawArrays(mode, first, count, drawcount);
	return Gurax::Value::nil();
}

// opengl.glMultiDrawElements(mode:Number, count[]:Number, type:Number, indices[]:Pointer)
Gurax_DeclareFunctionAlias(glMultiDrawElements_gurax, "glMultiDrawElements")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMultiDrawElements_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	auto count = args_gurax.PickNumList<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	auto indices = args_gurax.PickListT<const void*>([](Gurax::Value& value) {
		return Gurax::Value_Pointer::GetPointer(value).GetPointerC<const void*>();
	});
	// Function body
	GLsizei drawcount = count.sizeT<GLsizei>();
	if (drawcount != indices.sizeT<GLsizei>()) {
		Error::Issue(ErrorType::RangeError, "count and indices must have the same number of elements");
		return Value::nil();
	}
	glMultiDrawElements(mode, count, type, indices, drawcount);
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

Gurax_ImplementFunctionEx(glPointParameterf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPointParameterf(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPointParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLfloat>();
	// Function body
	glPointParameterfv(pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPointParameteri_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glPointParameteri(pname, param);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPointParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glPointParameteriv(pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3b_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbyte red = args_gurax.PickNumber<GLbyte>();
	GLbyte green = args_gurax.PickNumber<GLbyte>();
	GLbyte blue = args_gurax.PickNumber<GLbyte>();
	// Function body
	glSecondaryColor3b(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3bv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLbyte>();
	// Function body
	glSecondaryColor3bv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble red = args_gurax.PickNumber<GLdouble>();
	GLdouble green = args_gurax.PickNumber<GLdouble>();
	GLdouble blue = args_gurax.PickNumber<GLdouble>();
	// Function body
	glSecondaryColor3d(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glSecondaryColor3dv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat red = args_gurax.PickNumber<GLfloat>();
	GLfloat green = args_gurax.PickNumber<GLfloat>();
	GLfloat blue = args_gurax.PickNumber<GLfloat>();
	// Function body
	glSecondaryColor3f(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glSecondaryColor3fv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint red = args_gurax.PickNumber<GLint>();
	GLint green = args_gurax.PickNumber<GLint>();
	GLint blue = args_gurax.PickNumber<GLint>();
	// Function body
	glSecondaryColor3i(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glSecondaryColor3iv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort red = args_gurax.PickNumber<GLshort>();
	GLshort green = args_gurax.PickNumber<GLshort>();
	GLshort blue = args_gurax.PickNumber<GLshort>();
	// Function body
	glSecondaryColor3s(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glSecondaryColor3sv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3ub_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLubyte red = args_gurax.PickNumber<GLubyte>();
	GLubyte green = args_gurax.PickNumber<GLubyte>();
	GLubyte blue = args_gurax.PickNumber<GLubyte>();
	// Function body
	glSecondaryColor3ub(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3ubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLubyte>();
	// Function body
	glSecondaryColor3ubv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint red = args_gurax.PickNumber<GLuint>();
	GLuint green = args_gurax.PickNumber<GLuint>();
	GLuint blue = args_gurax.PickNumber<GLuint>();
	// Function body
	glSecondaryColor3ui(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLuint>();
	// Function body
	glSecondaryColor3uiv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3us_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLushort red = args_gurax.PickNumber<GLushort>();
	GLushort green = args_gurax.PickNumber<GLushort>();
	GLushort blue = args_gurax.PickNumber<GLushort>();
	// Function body
	glSecondaryColor3us(red, green, blue);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColor3usv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto v = args_gurax.PickNumList<GLushort>();
	// Function body
	glSecondaryColor3usv(v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSecondaryColorPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glSecondaryColorPointer(size, type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	// Function body
	glWindowPos2d(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLdouble>();
	// Function body
	glWindowPos2dv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	// Function body
	glWindowPos2f(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLfloat>();
	// Function body
	glWindowPos2fv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	// Function body
	glWindowPos2i(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLint>();
	// Function body
	glWindowPos2iv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	// Function body
	glWindowPos2s(x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos2sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLshort>();
	// Function body
	glWindowPos2sv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glWindowPos3d(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLdouble>();
	// Function body
	glWindowPos3dv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glWindowPos3f(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLfloat>();
	// Function body
	glWindowPos3fv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLint z = args_gurax.PickNumber<GLint>();
	// Function body
	glWindowPos3i(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLint>();
	// Function body
	glWindowPos3iv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	// Function body
	glWindowPos3s(x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glWindowPos3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto p = args_gurax.PickNumList<GLshort>();
	// Function body
	glWindowPos3sv(p);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBeginQuery_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLuint id = args_gurax.PickNumber<GLuint>();
	// Function body
	glBeginQuery(target, id);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBindBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glBindBuffer(target, buffer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBufferData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLenum usage = args_gurax.PickNumber<GLenum>();
	// Function body
	glBufferData(target, size, data, usage);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glBufferSubData(target, offset, size, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDeleteBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	auto buffers = args_gurax.PickNumList<GLuint>();
	// Function body
	glDeleteBuffers(n, buffers);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDeleteQueries_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	auto ids = args_gurax.PickNumList<GLuint>();
	// Function body
	glDeleteQueries(n, ids);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEndQuery_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	// Function body
	glEndQuery(target);
	return Gurax::Value::nil();
}

// opengl.glGenBuffers(n:Number, buffers:Pointer)
Gurax_DeclareFunctionAlias(glGenBuffers_gurax, "glGenBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* buffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!buffers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGenBuffers(n, buffers);
	return Gurax::Value::nil();
}

// opengl.glGenQueries(n:Number, ids:Pointer)
Gurax_DeclareFunctionAlias(glGenQueries_gurax, "glGenQueries")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ids", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenQueries_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* ids = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!ids) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGenQueries(n, ids);
	return Gurax::Value::nil();
}

// opengl.glGetBufferParameteriv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetBufferParameteriv_gurax, "glGetBufferParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetBufferParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetBufferParameteriv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetBufferSubData(target:Number, offset:Number, size:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glGetBufferSubData_gurax, "glGetBufferSubData")
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

Gurax_ImplementFunctionEx(glGetBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	void* data = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetBufferSubData(target, offset, size, data);
	return Gurax::Value::nil();
}

// opengl.glGetQueryObjectiv(id:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetQueryObjectiv_gurax, "glGetQueryObjectiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryObjectiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetQueryObjectiv(id, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetQueryObjectuiv(id:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetQueryObjectuiv_gurax, "glGetQueryObjectuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryObjectuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetQueryObjectuiv(id, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetQueryiv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetQueryiv_gurax, "glGetQueryiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetQueryiv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIsBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsBuffer(buffer);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glIsQuery_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsQuery(id);
	return new Gurax::Value_Bool(!!rtn);
}

// opengl.glMapBuffer(target:Number, access:Number)
Gurax_DeclareFunctionAlias(glMapBuffer_gurax, "glMapBuffer")
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("access", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMapBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum access = args_gurax.PickNumber<GLenum>();
	// Function body
	void* rtn = glMapBuffer(target, access);
	return new Gurax::Value_Pointer(new Pointer_Memory(new MemorySloth(rtn)));
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

Gurax_ImplementFunctionEx(glUnmapBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	// Function body
	GLboolean rtn = glUnmapBuffer(target);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glAttachShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint shader = args_gurax.PickNumber<GLuint>();
	// Function body
	glAttachShader(program, shader);
	return Gurax::Value::nil();
}

// opengl.glBindAttribLocation(program:Number, index:Number, name:String)
Gurax_DeclareFunctionAlias(glBindAttribLocation_gurax, "glBindAttribLocation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBindAttribLocation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	glBindAttribLocation(program, index, name);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendEquationSeparate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum modeRGB = args_gurax.PickNumber<GLenum>();
	GLenum modeAlpha = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendEquationSeparate(modeRGB, modeAlpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glCompileShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	// Function body
	glCompileShader(shader);
	return Gurax::Value::nil();
}

// opengl.glCreateProgram()
Gurax_DeclareFunctionAlias(glCreateProgram_gurax, "glCreateProgram")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateProgram_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLuint rtn = glCreateProgram();
	return new Gurax::Value_Number(rtn);
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

Gurax_ImplementFunctionEx(glCreateShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum type = args_gurax.PickNumber<GLenum>();
	// Function body
	GLuint rtn = glCreateShader(type);
	return new Gurax::Value_Number(rtn);
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

Gurax_ImplementFunctionEx(glDeleteProgram_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	// Function body
	glDeleteProgram(program);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDeleteShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	// Function body
	glDeleteShader(shader);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDetachShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint shader = args_gurax.PickNumber<GLuint>();
	// Function body
	glDetachShader(program, shader);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDisableVertexAttribArray_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	glDisableVertexAttribArray(index);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	auto bufs = args_gurax.PickNumList<GLenum>();
	// Function body
	glDrawBuffers(n, bufs);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEnableVertexAttribArray_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	glEnableVertexAttribArray(index);
	return Gurax::Value::nil();
}

// opengl.glGetActiveAttrib(program:Number, index:Number, maxLength:Number, length:Pointer, size:Pointer, type:Pointer, name:Pointer)
Gurax_DeclareFunctionAlias(glGetActiveAttrib_gurax, "glGetActiveAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxLength", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetActiveAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLsizei maxLength = args_gurax.PickNumber<GLsizei>();
	GLsizei* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLint* size = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!size) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLenum* type = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLenum>();
	if (!type) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* name = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!name) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetActiveAttrib(program, index, maxLength, length, size, type, name);
	return Gurax::Value::nil();
}

// opengl.glGetActiveUniform(program:Number, index:Number, maxLength:Number, length:Pointer, size:Pointer, type:Pointer, name:Pointer)
Gurax_DeclareFunctionAlias(glGetActiveUniform_gurax, "glGetActiveUniform")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxLength", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetActiveUniform_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLsizei maxLength = args_gurax.PickNumber<GLsizei>();
	GLsizei* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLint* size = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!size) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLenum* type = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLenum>();
	if (!type) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* name = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!name) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetActiveUniform(program, index, maxLength, length, size, type, name);
	return Gurax::Value::nil();
}

// opengl.glGetAttachedShaders(program:Number, maxCount:Number, count:Pointer, shaders:Pointer)
Gurax_DeclareFunctionAlias(glGetAttachedShaders_gurax, "glGetAttachedShaders")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("shaders", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetAttachedShaders_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLsizei maxCount = args_gurax.PickNumber<GLsizei>();
	GLsizei* count = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!count) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLuint* shaders = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!shaders) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetAttachedShaders(program, maxCount, count, shaders);
	return Gurax::Value::nil();
}

// opengl.glGetAttribLocation(program:Number, name:String)
Gurax_DeclareFunctionAlias(glGetAttribLocation_gurax, "glGetAttribLocation")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetAttribLocation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	GLint rtn = glGetAttribLocation(program, name);
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetProgramInfoLog(program:Number, bufSize:Number, length:Pointer, infoLog:Pointer)
Gurax_DeclareFunctionAlias(glGetProgramInfoLog_gurax, "glGetProgramInfoLog")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("infoLog", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetProgramInfoLog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLsizei* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* infoLog = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!infoLog) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetProgramInfoLog(program, bufSize, length, infoLog);
	return Gurax::Value::nil();
}

// opengl.glGetProgramiv(program:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetProgramiv_gurax, "glGetProgramiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetProgramiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetProgramiv(program, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetShaderInfoLog(shader:Number, bufSize:Number, length:Pointer, infoLog:Pointer)
Gurax_DeclareFunctionAlias(glGetShaderInfoLog_gurax, "glGetShaderInfoLog")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("infoLog", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetShaderInfoLog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLsizei* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* infoLog = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!infoLog) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetShaderInfoLog(shader, bufSize, length, infoLog);
	return Gurax::Value::nil();
}

// opengl.glGetShaderSource(obj:Number, maxLength:Number, length:Pointer, source:Pointer)
Gurax_DeclareFunctionAlias(glGetShaderSource_gurax, "glGetShaderSource")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("obj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxLength", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("source", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetShaderSource_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint obj = args_gurax.PickNumber<GLuint>();
	GLsizei maxLength = args_gurax.PickNumber<GLsizei>();
	GLsizei* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* source = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!source) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetShaderSource(obj, maxLength, length, source);
	return Gurax::Value::nil();
}

// opengl.glGetShaderiv(shader:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetShaderiv_gurax, "glGetShaderiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetShaderiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetShaderiv(shader, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetUniformLocation(program:Number, name:String)
Gurax_DeclareFunctionAlias(glGetUniformLocation_gurax, "glGetUniformLocation")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetUniformLocation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	GLint rtn = glGetUniformLocation(program, name);
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetUniformfv(program:Number, location:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetUniformfv_gurax, "glGetUniformfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetUniformfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetUniformfv(program, location, params);
	return Gurax::Value::nil();
}

// opengl.glGetUniformiv(program:Number, location:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetUniformiv_gurax, "glGetUniformiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetUniformiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetUniformiv(program, location, params);
	return Gurax::Value::nil();
}

// opengl.glGetVertexAttribdv(index:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexAttribdv_gurax, "glGetVertexAttribdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexAttribdv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLdouble* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexAttribdv(index, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetVertexAttribfv(index:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexAttribfv_gurax, "glGetVertexAttribfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexAttribfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexAttribfv(index, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetVertexAttribiv(index:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexAttribiv_gurax, "glGetVertexAttribiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexAttribiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexAttribiv(index, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIsProgram_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsProgram(program);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glIsShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsShader(shader);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glLinkProgram_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	// Function body
	glLinkProgram(program);
	return Gurax::Value::nil();
}

// opengl.glShaderSource(shader:Number, count:Number, string[]:String, length:Pointer)
Gurax_DeclareFunctionAlias(glShaderSource_gurax, "glShaderSource")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glShaderSource_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto string = args_gurax.PickListT<const GLchar*>([](Gurax::Value& value) {
		return reinterpret_cast<const GLchar*>(Gurax::Value_String::GetString(value));
	});
	GLint* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glShaderSource(shader, count, string, length);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glStencilFuncSeparate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum frontfunc = args_gurax.PickNumber<GLenum>();
	GLenum backfunc = args_gurax.PickNumber<GLenum>();
	GLint ref = args_gurax.PickNumber<GLint>();
	GLuint mask = args_gurax.PickNumber<GLuint>();
	// Function body
	glStencilFuncSeparate(frontfunc, backfunc, ref, mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glStencilMaskSeparate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLuint mask = args_gurax.PickNumber<GLuint>();
	// Function body
	glStencilMaskSeparate(face, mask);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glStencilOpSeparate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum face = args_gurax.PickNumber<GLenum>();
	GLenum sfail = args_gurax.PickNumber<GLenum>();
	GLenum dpfail = args_gurax.PickNumber<GLenum>();
	GLenum dppass = args_gurax.PickNumber<GLenum>();
	// Function body
	glStencilOpSeparate(face, sfail, dpfail, dppass);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLfloat v0 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glUniform1f(location, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform1fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniform1fv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform1i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	// Function body
	glUniform1i(location, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform1iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLint>();
	// Function body
	glUniform1iv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLfloat v0 = args_gurax.PickNumber<GLfloat>();
	GLfloat v1 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glUniform2f(location, v0, v1);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniform2fv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	GLint v1 = args_gurax.PickNumber<GLint>();
	// Function body
	glUniform2i(location, v0, v1);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLint>();
	// Function body
	glUniform2iv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLfloat v0 = args_gurax.PickNumber<GLfloat>();
	GLfloat v1 = args_gurax.PickNumber<GLfloat>();
	GLfloat v2 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glUniform3f(location, v0, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniform3fv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	GLint v1 = args_gurax.PickNumber<GLint>();
	GLint v2 = args_gurax.PickNumber<GLint>();
	// Function body
	glUniform3i(location, v0, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLint>();
	// Function body
	glUniform3iv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLfloat v0 = args_gurax.PickNumber<GLfloat>();
	GLfloat v1 = args_gurax.PickNumber<GLfloat>();
	GLfloat v2 = args_gurax.PickNumber<GLfloat>();
	GLfloat v3 = args_gurax.PickNumber<GLfloat>();
	// Function body
	glUniform4f(location, v0, v1, v2, v3);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniform4fv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	GLint v1 = args_gurax.PickNumber<GLint>();
	GLint v2 = args_gurax.PickNumber<GLint>();
	GLint v3 = args_gurax.PickNumber<GLint>();
	// Function body
	glUniform4i(location, v0, v1, v2, v3);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLint>();
	// Function body
	glUniform4iv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix2fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix3fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix4fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUseProgram_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	// Function body
	glUseProgram(program);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glValidateProgram_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	// Function body
	glValidateProgram(program);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib1d(index, x);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib1dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib1dv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib1f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib1f(index, x);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib1fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib1fv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib1s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLshort x = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertexAttrib1s(index, x);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib1sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertexAttrib1sv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib2d(index, x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib2dv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib2f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib2f(index, x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib2fv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib2s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertexAttrib2s(index, x, y);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib2sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertexAttrib2sv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib3d(index, x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib3dv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib3f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib3f(index, x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib3fv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib3s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertexAttrib3s(index, x, y, z);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib3sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertexAttrib3sv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Nbv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLbyte>();
	// Function body
	glVertexAttrib4Nbv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Niv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glVertexAttrib4Niv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Nsv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertexAttrib4Nsv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Nub_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLubyte x = args_gurax.PickNumber<GLubyte>();
	GLubyte y = args_gurax.PickNumber<GLubyte>();
	GLubyte z = args_gurax.PickNumber<GLubyte>();
	GLubyte w = args_gurax.PickNumber<GLubyte>();
	// Function body
	glVertexAttrib4Nub(index, x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Nubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLubyte>();
	// Function body
	glVertexAttrib4Nubv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Nuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLuint>();
	// Function body
	glVertexAttrib4Nuiv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4Nusv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLushort>();
	// Function body
	glVertexAttrib4Nusv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4bv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLbyte>();
	// Function body
	glVertexAttrib4bv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	GLdouble w = args_gurax.PickNumber<GLdouble>();
	// Function body
	glVertexAttrib4d(index, x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLdouble>();
	// Function body
	glVertexAttrib4dv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4f_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLfloat x = args_gurax.PickNumber<GLfloat>();
	GLfloat y = args_gurax.PickNumber<GLfloat>();
	GLfloat z = args_gurax.PickNumber<GLfloat>();
	GLfloat w = args_gurax.PickNumber<GLfloat>();
	// Function body
	glVertexAttrib4f(index, x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLfloat>();
	// Function body
	glVertexAttrib4fv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLint>();
	// Function body
	glVertexAttrib4iv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4s_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLshort x = args_gurax.PickNumber<GLshort>();
	GLshort y = args_gurax.PickNumber<GLshort>();
	GLshort z = args_gurax.PickNumber<GLshort>();
	GLshort w = args_gurax.PickNumber<GLshort>();
	// Function body
	glVertexAttrib4s(index, x, y, z, w);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertexAttrib4sv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4ubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLubyte>();
	// Function body
	glVertexAttrib4ubv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLuint>();
	// Function body
	glVertexAttrib4uiv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttrib4usv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v = args_gurax.PickNumList<GLushort>();
	// Function body
	glVertexAttrib4usv(index, v);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLboolean normalized = static_cast<GLboolean>(args_gurax.PickBool());
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix2x3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix2x3fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix2x4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix2x4fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix3x2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix3x2fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix3x4fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix3x4fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix4x2fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix4x2fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniformMatrix4x3fv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glUniformMatrix4x3fv(location, count, transpose, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBeginConditionalRender_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glBeginConditionalRender(id, mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBeginTransformFeedback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum primitiveMode = args_gurax.PickNumber<GLenum>();
	// Function body
	glBeginTransformFeedback(primitiveMode);
	return Gurax::Value::nil();
}

// opengl.glBindFragDataLocation(program:Number, colorNumber:Number, name:String)
Gurax_DeclareFunctionAlias(glBindFragDataLocation_gurax, "glBindFragDataLocation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colorNumber", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBindFragDataLocation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint colorNumber = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	glBindFragDataLocation(program, colorNumber, name);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClampColor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum clamp = args_gurax.PickNumber<GLenum>();
	// Function body
	glClampColor(target, clamp);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearBufferfi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawBuffer = args_gurax.PickNumber<GLint>();
	GLfloat depth = args_gurax.PickNumber<GLfloat>();
	GLint stencil = args_gurax.PickNumber<GLint>();
	// Function body
	glClearBufferfi(buffer, drawBuffer, depth, stencil);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearBufferfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawBuffer = args_gurax.PickNumber<GLint>();
	auto value = args_gurax.PickNumList<GLfloat>();
	// Function body
	glClearBufferfv(buffer, drawBuffer, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearBufferiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawBuffer = args_gurax.PickNumber<GLint>();
	auto value = args_gurax.PickNumList<GLint>();
	// Function body
	glClearBufferiv(buffer, drawBuffer, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glClearBufferuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawBuffer = args_gurax.PickNumber<GLint>();
	auto value = args_gurax.PickNumList<GLuint>();
	// Function body
	glClearBufferuiv(buffer, drawBuffer, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glColorMaski_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLboolean red = static_cast<GLboolean>(args_gurax.PickBool());
	GLboolean green = static_cast<GLboolean>(args_gurax.PickBool());
	GLboolean blue = static_cast<GLboolean>(args_gurax.PickBool());
	GLboolean alpha = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glColorMaski(buf, red, green, blue, alpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDisablei_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum cap = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	glDisablei(cap, index);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glEnablei_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum cap = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	glEnablei(cap, index);
	return Gurax::Value::nil();
}

// opengl.glEndConditionalRender()
Gurax_DeclareFunctionAlias(glEndConditionalRender_gurax, "glEndConditionalRender")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glEndConditionalRender_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glEndConditionalRender();
	return Gurax::Value::nil();
}

// opengl.glEndTransformFeedback()
Gurax_DeclareFunctionAlias(glEndTransformFeedback_gurax, "glEndTransformFeedback")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glEndTransformFeedback_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glEndTransformFeedback();
	return Gurax::Value::nil();
}

// opengl.glGetBooleani_v(pname:Number, index:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glGetBooleani_v_gurax, "glGetBooleani_v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetBooleani_v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLboolean* data = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLboolean>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetBooleani_v(pname, index, data);
	return Gurax::Value::nil();
}

// opengl.glGetFragDataLocation(program:Number, name:String)
Gurax_DeclareFunctionAlias(glGetFragDataLocation_gurax, "glGetFragDataLocation")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetFragDataLocation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	GLint rtn = glGetFragDataLocation(program, name);
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetStringi(name:Number, index:Number)
Gurax_DeclareFunctionAlias(glGetStringi_gurax, "glGetStringi")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetStringi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum name = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	const GLubyte* rtn = glGetStringi(name, index);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
}

// opengl.glGetTexParameterIiv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexParameterIiv_gurax, "glGetTexParameterIiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexParameterIiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexParameterIiv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTexParameterIuiv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTexParameterIuiv_gurax, "glGetTexParameterIuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTexParameterIuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTexParameterIuiv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTransformFeedbackVarying(program:Number, index:Number, bufSize:Number, length:Pointer, size:Pointer, type:Pointer, name:Pointer)
Gurax_DeclareFunctionAlias(glGetTransformFeedbackVarying_gurax, "glGetTransformFeedbackVarying")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTransformFeedbackVarying_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLsizei* length = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!length) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLsizei* size = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!size) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLenum* type = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLenum>();
	if (!type) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* name = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!name) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	return Gurax::Value::nil();
}

// opengl.glGetUniformuiv(program:Number, location:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetUniformuiv_gurax, "glGetUniformuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetUniformuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetUniformuiv(program, location, params);
	return Gurax::Value::nil();
}

// opengl.glGetVertexAttribIiv(index:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexAttribIiv_gurax, "glGetVertexAttribIiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexAttribIiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexAttribIiv(index, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetVertexAttribIuiv(index:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexAttribIuiv_gurax, "glGetVertexAttribIuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexAttribIuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexAttribIuiv(index, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glIsEnabledi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum cap = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsEnabledi(cap, index);
	return new Gurax::Value_Bool(!!rtn);
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

Gurax_ImplementFunctionEx(glTexParameterIiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLint>();
	// Function body
	glTexParameterIiv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexParameterIuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	auto params = args_gurax.PickNumList<GLuint>();
	// Function body
	glTexParameterIuiv(target, pname, params);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform1ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	// Function body
	glUniform1ui(location, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform1uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLuint>();
	// Function body
	glUniform1uiv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform2ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	GLuint v1 = args_gurax.PickNumber<GLuint>();
	// Function body
	glUniform2ui(location, v0, v1);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform2uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLuint>();
	// Function body
	glUniform2uiv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform3ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	GLuint v1 = args_gurax.PickNumber<GLuint>();
	GLuint v2 = args_gurax.PickNumber<GLuint>();
	// Function body
	glUniform3ui(location, v0, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform3uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLuint>();
	// Function body
	glUniform3uiv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform4ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	GLuint v1 = args_gurax.PickNumber<GLuint>();
	GLuint v2 = args_gurax.PickNumber<GLuint>();
	GLuint v3 = args_gurax.PickNumber<GLuint>();
	// Function body
	glUniform4ui(location, v0, v1, v2, v3);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glUniform4uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	auto value = args_gurax.PickNumList<GLuint>();
	// Function body
	glUniform4uiv(location, count, value);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI1i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	// Function body
	glVertexAttribI1i(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI1iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLint>();
	// Function body
	glVertexAttribI1iv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI1ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexAttribI1ui(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI1uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLuint>();
	// Function body
	glVertexAttribI1uiv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI2i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	GLint v1 = args_gurax.PickNumber<GLint>();
	// Function body
	glVertexAttribI2i(index, v0, v1);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI2iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLint>();
	// Function body
	glVertexAttribI2iv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI2ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	GLuint v1 = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexAttribI2ui(index, v0, v1);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI2uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLuint>();
	// Function body
	glVertexAttribI2uiv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI3i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	GLint v1 = args_gurax.PickNumber<GLint>();
	GLint v2 = args_gurax.PickNumber<GLint>();
	// Function body
	glVertexAttribI3i(index, v0, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI3iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLint>();
	// Function body
	glVertexAttribI3iv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI3ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	GLuint v1 = args_gurax.PickNumber<GLuint>();
	GLuint v2 = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexAttribI3ui(index, v0, v1, v2);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI3uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLuint>();
	// Function body
	glVertexAttribI3uiv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4bv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLbyte>();
	// Function body
	glVertexAttribI4bv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4i_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint v0 = args_gurax.PickNumber<GLint>();
	GLint v1 = args_gurax.PickNumber<GLint>();
	GLint v2 = args_gurax.PickNumber<GLint>();
	GLint v3 = args_gurax.PickNumber<GLint>();
	// Function body
	glVertexAttribI4i(index, v0, v1, v2, v3);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLint>();
	// Function body
	glVertexAttribI4iv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4sv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLshort>();
	// Function body
	glVertexAttribI4sv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4ubv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLubyte>();
	// Function body
	glVertexAttribI4ubv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4ui_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint v0 = args_gurax.PickNumber<GLuint>();
	GLuint v1 = args_gurax.PickNumber<GLuint>();
	GLuint v2 = args_gurax.PickNumber<GLuint>();
	GLuint v3 = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexAttribI4ui(index, v0, v1, v2, v3);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4uiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLuint>();
	// Function body
	glVertexAttribI4uiv(index, v0);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribI4usv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	auto v0 = args_gurax.PickNumList<GLushort>();
	// Function body
	glVertexAttribI4usv(index, v0);
	return Gurax::Value::nil();
}

// opengl.glVertexAttribIPointer(index:Number, size:Number, type:Number, stride:Number, pointer:Pointer)
Gurax_DeclareFunctionAlias(glVertexAttribIPointer_gurax, "glVertexAttribIPointer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexAttribIPointer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	const void* pointer = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glVertexAttribIPointer(index, size, type, stride, pointer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawArraysInstanced_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLint first = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLsizei primcount = args_gurax.PickNumber<GLsizei>();
	// Function body
	glDrawArraysInstanced(mode, first, count, primcount);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glDrawElementsInstanced_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indices = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei primcount = args_gurax.PickNumber<GLsizei>();
	// Function body
	glDrawElementsInstanced(mode, count, type, indices, primcount);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glPrimitiveRestartIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glPrimitiveRestartIndex(buffer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glTexBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum internalFormat = args_gurax.PickNumber<GLenum>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glTexBuffer(target, internalFormat, buffer);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glFramebufferTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTexture(target, attachment, texture, level);
	return Gurax::Value::nil();
}

// opengl.glGetBufferParameteri64v(target:Number, value:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glGetBufferParameteri64v_gurax, "glGetBufferParameteri64v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetBufferParameteri64v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum value = args_gurax.PickNumber<GLenum>();
	GLint64* data = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint64>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetBufferParameteri64v(target, value, data);
	return Gurax::Value::nil();
}

// opengl.glGetInteger64i_v(pname:Number, index:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glGetInteger64i_v_gurax, "glGetInteger64i_v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetInteger64i_v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint64* data = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint64>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetInteger64i_v(pname, index, data);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glVertexAttribDivisor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint divisor = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexAttribDivisor(index, divisor);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendEquationSeparatei_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum modeRGB = args_gurax.PickNumber<GLenum>();
	GLenum modeAlpha = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendEquationi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendEquationi(buf, mode);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendFuncSeparatei_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum srcRGB = args_gurax.PickNumber<GLenum>();
	GLenum dstRGB = args_gurax.PickNumber<GLenum>();
	GLenum srcAlpha = args_gurax.PickNumber<GLenum>();
	GLenum dstAlpha = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glBlendFunci_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum src = args_gurax.PickNumber<GLenum>();
	GLenum dst = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendFunci(buf, src, dst);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glMinSampleShading_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampf value = args_gurax.PickNumber<GLclampf>();
	// Function body
	glMinSampleShading(value);
	return Gurax::Value::nil();
}

// opengl.glGetGraphicsResetStatus()
Gurax_DeclareFunctionAlias(glGetGraphicsResetStatus_gurax, "glGetGraphicsResetStatus")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetGraphicsResetStatus_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLenum rtn = glGetGraphicsResetStatus();
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetnCompressedTexImage(target:Number, lod:Number, bufSize:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetnCompressedTexImage_gurax, "glGetnCompressedTexImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lod", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetnCompressedTexImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint lod = args_gurax.PickNumber<GLint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLvoid* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLvoid>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetnCompressedTexImage(target, lod, bufSize, pixels);
	return Gurax::Value::nil();
}

// opengl.glGetnTexImage(tex:Number, level:Number, format:Number, type:Number, bufSize:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetnTexImage_gurax, "glGetnTexImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetnTexImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum tex = args_gurax.PickNumber<GLenum>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLvoid* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLvoid>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetnTexImage(tex, level, format, type, bufSize, pixels);
	return Gurax::Value::nil();
}

// opengl.glGetnUniformdv(program:Number, location:Number, bufSize:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetnUniformdv_gurax, "glGetnUniformdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetnUniformdv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLdouble* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetnUniformdv(program, location, bufSize, params);
	return Gurax::Value::nil();
}

// opengl.glMultiDrawArraysIndirectCount(mode:Number, indirect:Pointer, drawcount:Number, maxdrawcount:Number, stride:Number)
Gurax_DeclareFunctionAlias(glMultiDrawArraysIndirectCount_gurax, "glMultiDrawArraysIndirectCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indirect", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxdrawcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMultiDrawArraysIndirectCount_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	const GLvoid* indirect = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLvoid>();
	GLintptr drawcount = args_gurax.PickNumber<GLintptr>();
	GLsizei maxdrawcount = args_gurax.PickNumber<GLsizei>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	// Function body
	glMultiDrawArraysIndirectCount(mode, indirect, drawcount, maxdrawcount, stride);
	return Gurax::Value::nil();
}

// opengl.glMultiDrawElementsIndirectCount(mode:Number, type:Number, indirect:Pointer, drawcount:Number, maxdrawcount:Number, stride:Number)
Gurax_DeclareFunctionAlias(glMultiDrawElementsIndirectCount_gurax, "glMultiDrawElementsIndirectCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indirect", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxdrawcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMultiDrawElementsIndirectCount_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const GLvoid* indirect = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLvoid>();
	GLintptr drawcount = args_gurax.PickNumber<GLintptr>();
	GLsizei maxdrawcount = args_gurax.PickNumber<GLsizei>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	// Function body
	glMultiDrawElementsIndirectCount(mode, type, indirect, drawcount, maxdrawcount, stride);
	return Gurax::Value::nil();
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

Gurax_ImplementFunctionEx(glSpecializeShader_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	auto pEntryPoint = args_gurax.PickNumList<GLchar>();
	GLuint numSpecializationConstants = args_gurax.PickNumber<GLuint>();
	auto pConstantIndex = args_gurax.PickNumList<GLuint>();
	auto pConstantValue = args_gurax.PickNumList<GLuint>();
	// Function body
	glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
	return Gurax::Value::nil();
}

// opengl.glClearDepthf(d:Number)
Gurax_DeclareFunctionAlias(glClearDepthf_gurax, "glClearDepthf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("d", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearDepthf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampf d = args_gurax.PickNumber<GLclampf>();
	// Function body
	glClearDepthf(d);
	return Gurax::Value::nil();
}

// opengl.glDepthRangef(n:Number, f:Number)
Gurax_DeclareFunctionAlias(glDepthRangef_gurax, "glDepthRangef")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("f", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDepthRangef_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLclampf n = args_gurax.PickNumber<GLclampf>();
	GLclampf f = args_gurax.PickNumber<GLclampf>();
	// Function body
	glDepthRangef(n, f);
	return Gurax::Value::nil();
}

// opengl.glGetShaderPrecisionFormat(shadertype:Number, precisiontype:Number, range:Pointer, precision:Pointer)
Gurax_DeclareFunctionAlias(glGetShaderPrecisionFormat_gurax, "glGetShaderPrecisionFormat")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shadertype", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("precisiontype", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("precision", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetShaderPrecisionFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum shadertype = args_gurax.PickNumber<GLenum>();
	GLenum precisiontype = args_gurax.PickNumber<GLenum>();
	GLint* range = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!range) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLint* precision = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!precision) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	return Gurax::Value::nil();
}

// opengl.glReleaseShaderCompiler()
Gurax_DeclareFunctionAlias(glReleaseShaderCompiler_gurax, "glReleaseShaderCompiler")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glReleaseShaderCompiler_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glReleaseShaderCompiler();
	return Gurax::Value::nil();
}

// opengl.glShaderBinary(count:Number, shaders:Pointer, binaryformat:Number, binary:Pointer, length:Number)
Gurax_DeclareFunctionAlias(glShaderBinary_gurax, "glShaderBinary")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("shaders", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("binaryformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("binary", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glShaderBinary_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLuint* shaders = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	GLenum binaryformat = args_gurax.PickNumber<GLenum>();
	const void* binary = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei length = args_gurax.PickNumber<GLsizei>();
	// Function body
	glShaderBinary(count, shaders, binaryformat, binary, length);
	return Gurax::Value::nil();
}

// opengl.glMemoryBarrierByRegion(barriers:Number)
Gurax_DeclareFunctionAlias(glMemoryBarrierByRegion_gurax, "glMemoryBarrierByRegion")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("barriers", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMemoryBarrierByRegion_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLbitfield barriers = args_gurax.PickNumber<GLbitfield>();
	// Function body
	glMemoryBarrierByRegion(barriers);
	return Gurax::Value::nil();
}

// opengl.glPrimitiveBoundingBoxARB(minX:Number, minY:Number, minZ:Number, minW:Number, maxX:Number, maxY:Number, maxZ:Number, maxW:Number)
Gurax_DeclareFunctionAlias(glPrimitiveBoundingBoxARB_gurax, "glPrimitiveBoundingBoxARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minZ", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minW", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxZ", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxW", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glPrimitiveBoundingBoxARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLfloat minX = args_gurax.PickNumber<GLfloat>();
	GLfloat minY = args_gurax.PickNumber<GLfloat>();
	GLfloat minZ = args_gurax.PickNumber<GLfloat>();
	GLfloat minW = args_gurax.PickNumber<GLfloat>();
	GLfloat maxX = args_gurax.PickNumber<GLfloat>();
	GLfloat maxY = args_gurax.PickNumber<GLfloat>();
	GLfloat maxZ = args_gurax.PickNumber<GLfloat>();
	GLfloat maxW = args_gurax.PickNumber<GLfloat>();
	// Function body
	glPrimitiveBoundingBoxARB(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
	return Gurax::Value::nil();
}

// opengl.glDrawArraysInstancedBaseInstance(mode:Number, first:Number, count:Number, primcount:Number, baseinstance:Number)
Gurax_DeclareFunctionAlias(glDrawArraysInstancedBaseInstance_gurax, "glDrawArraysInstancedBaseInstance")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("baseinstance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawArraysInstancedBaseInstance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLint first = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLsizei primcount = args_gurax.PickNumber<GLsizei>();
	GLuint baseinstance = args_gurax.PickNumber<GLuint>();
	// Function body
	glDrawArraysInstancedBaseInstance(mode, first, count, primcount, baseinstance);
	return Gurax::Value::nil();
}

// opengl.glDrawElementsInstancedBaseInstance(mode:Number, count:Number, type:Number, indices:Pointer, primcount:Number, baseinstance:Number)
Gurax_DeclareFunctionAlias(glDrawElementsInstancedBaseInstance_gurax, "glDrawElementsInstancedBaseInstance")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("baseinstance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawElementsInstancedBaseInstance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indices = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei primcount = args_gurax.PickNumber<GLsizei>();
	GLuint baseinstance = args_gurax.PickNumber<GLuint>();
	// Function body
	glDrawElementsInstancedBaseInstance(mode, count, type, indices, primcount, baseinstance);
	return Gurax::Value::nil();
}

// opengl.glDrawElementsInstancedBaseVertexBaseInstance(mode:Number, count:Number, type:Number, indices:Pointer, primcount:Number, basevertex:Number, baseinstance:Number)
Gurax_DeclareFunctionAlias(glDrawElementsInstancedBaseVertexBaseInstance_gurax, "glDrawElementsInstancedBaseVertexBaseInstance")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("basevertex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("baseinstance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawElementsInstancedBaseVertexBaseInstance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indices = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei primcount = args_gurax.PickNumber<GLsizei>();
	GLint basevertex = args_gurax.PickNumber<GLint>();
	GLuint baseinstance = args_gurax.PickNumber<GLuint>();
	// Function body
	glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, primcount, basevertex, baseinstance);
	return Gurax::Value::nil();
}

// opengl.glGetImageHandleARB(texture:Number, level:Number, layered:Bool, layer:Number, format:Number)
Gurax_DeclareFunctionAlias(glGetImageHandleARB_gurax, "glGetImageHandleARB")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("layered", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("layer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetImageHandleARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLboolean layered = static_cast<GLboolean>(args_gurax.PickBool());
	GLint layer = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	// Function body
	GLuint64 rtn = glGetImageHandleARB(texture, level, layered, layer, format);
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetTextureHandleARB(texture:Number)
Gurax_DeclareFunctionAlias(glGetTextureHandleARB_gurax, "glGetTextureHandleARB")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureHandleARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	// Function body
	GLuint64 rtn = glGetTextureHandleARB(texture);
	return new Gurax::Value_Number(rtn);
}

// opengl.glGetTextureSamplerHandleARB(texture:Number, sampler:Number)
Gurax_DeclareFunctionAlias(glGetTextureSamplerHandleARB_gurax, "glGetTextureSamplerHandleARB")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sampler", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureSamplerHandleARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLuint sampler = args_gurax.PickNumber<GLuint>();
	// Function body
	GLuint64 rtn = glGetTextureSamplerHandleARB(texture, sampler);
	return new Gurax::Value_Number(rtn);
}

// opengl.glIsImageHandleResidentARB(handle:Number)
Gurax_DeclareFunctionAlias(glIsImageHandleResidentARB_gurax, "glIsImageHandleResidentARB")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("handle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glIsImageHandleResidentARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint64 handle = args_gurax.PickNumber<GLuint64>();
	// Function body
	GLboolean rtn = glIsImageHandleResidentARB(handle);
	return new Gurax::Value_Bool(!!rtn);
}

// opengl.glIsTextureHandleResidentARB(handle:Number)
Gurax_DeclareFunctionAlias(glIsTextureHandleResidentARB_gurax, "glIsTextureHandleResidentARB")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("handle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glIsTextureHandleResidentARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint64 handle = args_gurax.PickNumber<GLuint64>();
	// Function body
	GLboolean rtn = glIsTextureHandleResidentARB(handle);
	return new Gurax::Value_Bool(!!rtn);
}

// opengl.glMakeImageHandleNonResidentARB(handle:Number)
Gurax_DeclareFunctionAlias(glMakeImageHandleNonResidentARB_gurax, "glMakeImageHandleNonResidentARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMakeImageHandleNonResidentARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint64 handle = args_gurax.PickNumber<GLuint64>();
	// Function body
	glMakeImageHandleNonResidentARB(handle);
	return Gurax::Value::nil();
}

// opengl.glMakeImageHandleResidentARB(handle:Number, access:Number)
Gurax_DeclareFunctionAlias(glMakeImageHandleResidentARB_gurax, "glMakeImageHandleResidentARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("access", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMakeImageHandleResidentARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint64 handle = args_gurax.PickNumber<GLuint64>();
	GLenum access = args_gurax.PickNumber<GLenum>();
	// Function body
	glMakeImageHandleResidentARB(handle, access);
	return Gurax::Value::nil();
}

// opengl.glMakeTextureHandleNonResidentARB(handle:Number)
Gurax_DeclareFunctionAlias(glMakeTextureHandleNonResidentARB_gurax, "glMakeTextureHandleNonResidentARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMakeTextureHandleNonResidentARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint64 handle = args_gurax.PickNumber<GLuint64>();
	// Function body
	glMakeTextureHandleNonResidentARB(handle);
	return Gurax::Value::nil();
}

// opengl.glMakeTextureHandleResidentARB(handle:Number)
Gurax_DeclareFunctionAlias(glMakeTextureHandleResidentARB_gurax, "glMakeTextureHandleResidentARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glMakeTextureHandleResidentARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint64 handle = args_gurax.PickNumber<GLuint64>();
	// Function body
	glMakeTextureHandleResidentARB(handle);
	return Gurax::Value::nil();
}

// opengl.glProgramUniformHandleui64ARB(program:Number, location:Number, value:Number)
Gurax_DeclareFunctionAlias(glProgramUniformHandleui64ARB_gurax, "glProgramUniformHandleui64ARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glProgramUniformHandleui64ARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint64 value = args_gurax.PickNumber<GLuint64>();
	// Function body
	glProgramUniformHandleui64ARB(program, location, value);
	return Gurax::Value::nil();
}

// opengl.glProgramUniformHandleui64vARB(program:Number, location:Number, count:Number, values:Pointer)
Gurax_DeclareFunctionAlias(glProgramUniformHandleui64vARB_gurax, "glProgramUniformHandleui64vARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glProgramUniformHandleui64vARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLuint64* values = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint64>();
	// Function body
	glProgramUniformHandleui64vARB(program, location, count, values);
	return Gurax::Value::nil();
}

// opengl.glUniformHandleui64ARB(location:Number, value:Number)
Gurax_DeclareFunctionAlias(glUniformHandleui64ARB_gurax, "glUniformHandleui64ARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformHandleui64ARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLuint64 value = args_gurax.PickNumber<GLuint64>();
	// Function body
	glUniformHandleui64ARB(location, value);
	return Gurax::Value::nil();
}

// opengl.glUniformHandleui64vARB(location:Number, count:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformHandleui64vARB_gurax, "glUniformHandleui64vARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformHandleui64vARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLuint64* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint64>();
	// Function body
	glUniformHandleui64vARB(location, count, value);
	return Gurax::Value::nil();
}

// opengl.glVertexAttribL1ui64ARB(index:Number, x:Number)
Gurax_DeclareFunctionAlias(glVertexAttribL1ui64ARB_gurax, "glVertexAttribL1ui64ARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexAttribL1ui64ARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint64EXT x = args_gurax.PickNumber<GLuint64EXT>();
	// Function body
	glVertexAttribL1ui64ARB(index, x);
	return Gurax::Value::nil();
}

// opengl.glVertexAttribL1ui64vARB(index:Number, v:Pointer)
Gurax_DeclareFunctionAlias(glVertexAttribL1ui64vARB_gurax, "glVertexAttribL1ui64vARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexAttribL1ui64vARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint index = args_gurax.PickNumber<GLuint>();
	const GLuint64EXT* v = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint64EXT>();
	// Function body
	glVertexAttribL1ui64vARB(index, v);
	return Gurax::Value::nil();
}

// opengl.glBindFragDataLocationIndexed(program:Number, colorNumber:Number, index:Number, name:String)
Gurax_DeclareFunctionAlias(glBindFragDataLocationIndexed_gurax, "glBindFragDataLocationIndexed")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colorNumber", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBindFragDataLocationIndexed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLuint colorNumber = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	glBindFragDataLocationIndexed(program, colorNumber, index, name);
	return Gurax::Value::nil();
}

// opengl.glGetFragDataIndex(program:Number, name:String)
Gurax_DeclareFunctionAlias(glGetFragDataIndex_gurax, "glGetFragDataIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetFragDataIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	const GLchar* name = reinterpret_cast<const GLchar*>(args_gurax.PickString());
	// Function body
	GLint rtn = glGetFragDataIndex(program, name);
	return new Gurax::Value_Number(rtn);
}

// opengl.glBufferStorage(target:Number, size:Number, data:Pointer, flags:Number)
Gurax_DeclareFunctionAlias(glBufferStorage_gurax, "glBufferStorage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBufferStorage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLbitfield flags = args_gurax.PickNumber<GLbitfield>();
	// Function body
	glBufferStorage(target, size, data, flags);
	return Gurax::Value::nil();
}

// opengl.glClearBufferData(target:Number, internalformat:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearBufferData_gurax, "glClearBufferData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearBufferData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearBufferData(target, internalformat, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearBufferSubData(target:Number, internalformat:Number, offset:Number, size:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearBufferSubData_gurax, "glClearBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearBufferSubData(target, internalformat, offset, size, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearNamedBufferDataEXT(buffer:Number, internalformat:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedBufferDataEXT_gurax, "glClearNamedBufferDataEXT")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedBufferDataEXT_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearNamedBufferDataEXT(buffer, internalformat, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearNamedBufferSubDataEXT(buffer:Number, internalformat:Number, offset:Number, size:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedBufferSubDataEXT_gurax, "glClearNamedBufferSubDataEXT")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedBufferSubDataEXT_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearTexImage(texture:Number, level:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearTexImage_gurax, "glClearTexImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearTexImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearTexImage(texture, level, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearTexSubImage(texture:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearTexSubImage_gurax, "glClearTexSubImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearTexSubImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClipControl(origin:Number, depth:Number)
Gurax_DeclareFunctionAlias(glClipControl_gurax, "glClipControl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("origin", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClipControl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum origin = args_gurax.PickNumber<GLenum>();
	GLenum depth = args_gurax.PickNumber<GLenum>();
	// Function body
	glClipControl(origin, depth);
	return Gurax::Value::nil();
}

// opengl.glClampColorARB(target:Number, clamp:Number)
Gurax_DeclareFunctionAlias(glClampColorARB_gurax, "glClampColorARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clamp", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClampColorARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum clamp = args_gurax.PickNumber<GLenum>();
	// Function body
	glClampColorARB(target, clamp);
	return Gurax::Value::nil();
}

// opengl.glDispatchCompute(num_groups_x:Number, num_groups_y:Number, num_groups_z:Number)
Gurax_DeclareFunctionAlias(glDispatchCompute_gurax, "glDispatchCompute")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("num_groups_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_groups_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_groups_z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDispatchCompute_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint num_groups_x = args_gurax.PickNumber<GLuint>();
	GLuint num_groups_y = args_gurax.PickNumber<GLuint>();
	GLuint num_groups_z = args_gurax.PickNumber<GLuint>();
	// Function body
	glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
	return Gurax::Value::nil();
}

// opengl.glDispatchComputeIndirect(indirect:Number)
Gurax_DeclareFunctionAlias(glDispatchComputeIndirect_gurax, "glDispatchComputeIndirect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("indirect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDispatchComputeIndirect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLintptr indirect = args_gurax.PickNumber<GLintptr>();
	// Function body
	glDispatchComputeIndirect(indirect);
	return Gurax::Value::nil();
}

// opengl.glDispatchComputeGroupSizeARB(num_groups_x:Number, num_groups_y:Number, num_groups_z:Number, group_size_x:Number, group_size_y:Number, group_size_z:Number)
Gurax_DeclareFunctionAlias(glDispatchComputeGroupSizeARB_gurax, "glDispatchComputeGroupSizeARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("num_groups_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_groups_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_groups_z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("group_size_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("group_size_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("group_size_z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDispatchComputeGroupSizeARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint num_groups_x = args_gurax.PickNumber<GLuint>();
	GLuint num_groups_y = args_gurax.PickNumber<GLuint>();
	GLuint num_groups_z = args_gurax.PickNumber<GLuint>();
	GLuint group_size_x = args_gurax.PickNumber<GLuint>();
	GLuint group_size_y = args_gurax.PickNumber<GLuint>();
	GLuint group_size_z = args_gurax.PickNumber<GLuint>();
	// Function body
	glDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z);
	return Gurax::Value::nil();
}

// opengl.glCopyBufferSubData(readtarget:Number, writetarget:Number, readoffset:Number, writeoffset:Number, size:Number)
Gurax_DeclareFunctionAlias(glCopyBufferSubData_gurax, "glCopyBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("readtarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("writetarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("readoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("writeoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCopyBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum readtarget = args_gurax.PickNumber<GLenum>();
	GLenum writetarget = args_gurax.PickNumber<GLenum>();
	GLintptr readoffset = args_gurax.PickNumber<GLintptr>();
	GLintptr writeoffset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	// Function body
	glCopyBufferSubData(readtarget, writetarget, readoffset, writeoffset, size);
	return Gurax::Value::nil();
}

// opengl.glCopyImageSubData(srcName:Number, srcTarget:Number, srcLevel:Number, srcX:Number, srcY:Number, srcZ:Number, dstName:Number, dstTarget:Number, dstLevel:Number, dstX:Number, dstY:Number, dstZ:Number, srcWidth:Number, srcHeight:Number, srcDepth:Number)
Gurax_DeclareFunctionAlias(glCopyImageSubData_gurax, "glCopyImageSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("srcName", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcTarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcLevel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcZ", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstName", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstTarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstLevel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstZ", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcWidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcHeight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcDepth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCopyImageSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint srcName = args_gurax.PickNumber<GLuint>();
	GLenum srcTarget = args_gurax.PickNumber<GLenum>();
	GLint srcLevel = args_gurax.PickNumber<GLint>();
	GLint srcX = args_gurax.PickNumber<GLint>();
	GLint srcY = args_gurax.PickNumber<GLint>();
	GLint srcZ = args_gurax.PickNumber<GLint>();
	GLuint dstName = args_gurax.PickNumber<GLuint>();
	GLenum dstTarget = args_gurax.PickNumber<GLenum>();
	GLint dstLevel = args_gurax.PickNumber<GLint>();
	GLint dstX = args_gurax.PickNumber<GLint>();
	GLint dstY = args_gurax.PickNumber<GLint>();
	GLint dstZ = args_gurax.PickNumber<GLint>();
	GLsizei srcWidth = args_gurax.PickNumber<GLsizei>();
	GLsizei srcHeight = args_gurax.PickNumber<GLsizei>();
	GLsizei srcDepth = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
	return Gurax::Value::nil();
}

// opengl.glDebugMessageControlARB(source:Number, type:Number, severity:Number, count:Number, ids:Pointer, enabled:Bool)
Gurax_DeclareFunctionAlias(glDebugMessageControlARB_gurax, "glDebugMessageControlARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("source", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("severity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ids", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enabled", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDebugMessageControlARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum source = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLenum severity = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLuint* ids = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	GLboolean enabled = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glDebugMessageControlARB(source, type, severity, count, ids, enabled);
	return Gurax::Value::nil();
}

// opengl.glDebugMessageInsertARB(source:Number, type:Number, id:Number, severity:Number, length:Number, buf:Pointer)
Gurax_DeclareFunctionAlias(glDebugMessageInsertARB_gurax, "glDebugMessageInsertARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("source", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("severity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buf", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDebugMessageInsertARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum source = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLenum severity = args_gurax.PickNumber<GLenum>();
	GLsizei length = args_gurax.PickNumber<GLsizei>();
	const GLchar* buf = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLchar>();
	// Function body
	glDebugMessageInsertARB(source, type, id, severity, length, buf);
	return Gurax::Value::nil();
}

// opengl.glGetDebugMessageLogARB(count:Number, bufSize:Number, sources:Pointer, types:Pointer, ids:Pointer, severities:Pointer, lengths:Pointer, messageLog:Pointer)
Gurax_DeclareFunctionAlias(glGetDebugMessageLogARB_gurax, "glGetDebugMessageLogARB")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sources", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("types", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ids", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("severities", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lengths", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("messageLog", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetDebugMessageLogARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint count = args_gurax.PickNumber<GLuint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	GLenum* sources = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLenum>();
	if (!sources) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLenum* types = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLenum>();
	if (!types) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLuint* ids = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!ids) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLenum* severities = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLenum>();
	if (!severities) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLsizei* lengths = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLsizei>();
	if (!lengths) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLchar* messageLog = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLchar>();
	if (!messageLog) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	GLuint rtn = glGetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog);
	return new Gurax::Value_Number(rtn);
}

// opengl.glBindTextureUnit(unit:Number, texture:Number)
Gurax_DeclareFunctionAlias(glBindTextureUnit_gurax, "glBindTextureUnit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("unit", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBindTextureUnit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint unit = args_gurax.PickNumber<GLuint>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	// Function body
	glBindTextureUnit(unit, texture);
	return Gurax::Value::nil();
}

// opengl.glBlitNamedFramebuffer(readFramebuffer:Number, drawFramebuffer:Number, srcX0:Number, srcY0:Number, srcX1:Number, srcY1:Number, dstX0:Number, dstY0:Number, dstX1:Number, dstY1:Number, mask:Number, filter:Number)
Gurax_DeclareFunctionAlias(glBlitNamedFramebuffer_gurax, "glBlitNamedFramebuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("readFramebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawFramebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcX0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcY0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcX1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcY1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstX0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstY0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstX1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstY1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBlitNamedFramebuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint readFramebuffer = args_gurax.PickNumber<GLuint>();
	GLuint drawFramebuffer = args_gurax.PickNumber<GLuint>();
	GLint srcX0 = args_gurax.PickNumber<GLint>();
	GLint srcY0 = args_gurax.PickNumber<GLint>();
	GLint srcX1 = args_gurax.PickNumber<GLint>();
	GLint srcY1 = args_gurax.PickNumber<GLint>();
	GLint dstX0 = args_gurax.PickNumber<GLint>();
	GLint dstY0 = args_gurax.PickNumber<GLint>();
	GLint dstX1 = args_gurax.PickNumber<GLint>();
	GLint dstY1 = args_gurax.PickNumber<GLint>();
	GLbitfield mask = args_gurax.PickNumber<GLbitfield>();
	GLenum filter = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	return Gurax::Value::nil();
}

// opengl.glCheckNamedFramebufferStatus(framebuffer:Number, target:Number)
Gurax_DeclareFunctionAlias(glCheckNamedFramebufferStatus_gurax, "glCheckNamedFramebufferStatus")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCheckNamedFramebufferStatus_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum target = args_gurax.PickNumber<GLenum>();
	// Function body
	GLenum rtn = glCheckNamedFramebufferStatus(framebuffer, target);
	return new Gurax::Value_Number(rtn);
}

// opengl.glClearNamedBufferData(buffer:Number, internalformat:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedBufferData_gurax, "glClearNamedBufferData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedBufferData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearNamedBufferData(buffer, internalformat, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearNamedBufferSubData(buffer:Number, internalformat:Number, offset:Number, size:Number, format:Number, type:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedBufferSubData_gurax, "glClearNamedBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
	return Gurax::Value::nil();
}

// opengl.glClearNamedFramebufferfi(framebuffer:Number, buffer:Number, drawbuffer:Number, depth:Number, stencil:Number)
Gurax_DeclareFunctionAlias(glClearNamedFramebufferfi_gurax, "glClearNamedFramebufferfi")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stencil", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedFramebufferfi_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawbuffer = args_gurax.PickNumber<GLint>();
	GLfloat depth = args_gurax.PickNumber<GLfloat>();
	GLint stencil = args_gurax.PickNumber<GLint>();
	// Function body
	glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
	return Gurax::Value::nil();
}

// opengl.glClearNamedFramebufferfv(framebuffer:Number, buffer:Number, drawbuffer:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedFramebufferfv_gurax, "glClearNamedFramebufferfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedFramebufferfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawbuffer = args_gurax.PickNumber<GLint>();
	GLfloat* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!value) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
	return Gurax::Value::nil();
}

// opengl.glClearNamedFramebufferiv(framebuffer:Number, buffer:Number, drawbuffer:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedFramebufferiv_gurax, "glClearNamedFramebufferiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedFramebufferiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawbuffer = args_gurax.PickNumber<GLint>();
	const GLint* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLint>();
	// Function body
	glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
	return Gurax::Value::nil();
}

// opengl.glClearNamedFramebufferuiv(framebuffer:Number, buffer:Number, drawbuffer:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glClearNamedFramebufferuiv_gurax, "glClearNamedFramebufferuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glClearNamedFramebufferuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum buffer = args_gurax.PickNumber<GLenum>();
	GLint drawbuffer = args_gurax.PickNumber<GLint>();
	const GLuint* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	// Function body
	glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
	return Gurax::Value::nil();
}

// opengl.glCompressedTextureSubImage1D(texture:Number, level:Number, xoffset:Number, width:Number, format:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTextureSubImage1D_gurax, "glCompressedTextureSubImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

Gurax_ImplementFunctionEx(glCompressedTextureSubImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
	return Gurax::Value::nil();
}

// opengl.glCompressedTextureSubImage2D(texture:Number, level:Number, xoffset:Number, yoffset:Number, width:Number, height:Number, format:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTextureSubImage2D_gurax, "glCompressedTextureSubImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

Gurax_ImplementFunctionEx(glCompressedTextureSubImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
	return Gurax::Value::nil();
}

// opengl.glCompressedTextureSubImage3D(texture:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, format:Number, imageSize:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glCompressedTextureSubImage3D_gurax, "glCompressedTextureSubImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

Gurax_ImplementFunctionEx(glCompressedTextureSubImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLsizei imageSize = args_gurax.PickNumber<GLsizei>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	return Gurax::Value::nil();
}

// opengl.glCopyNamedBufferSubData(readBuffer:Number, writeBuffer:Number, readOffset:Number, writeOffset:Number, size:Number)
Gurax_DeclareFunctionAlias(glCopyNamedBufferSubData_gurax, "glCopyNamedBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("readBuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("writeBuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("readOffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("writeOffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCopyNamedBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint readBuffer = args_gurax.PickNumber<GLuint>();
	GLuint writeBuffer = args_gurax.PickNumber<GLuint>();
	GLintptr readOffset = args_gurax.PickNumber<GLintptr>();
	GLintptr writeOffset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	// Function body
	glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
	return Gurax::Value::nil();
}

// opengl.glCopyTextureSubImage1D(texture:Number, level:Number, xoffset:Number, x:Number, y:Number, width:Number)
Gurax_DeclareFunctionAlias(glCopyTextureSubImage1D_gurax, "glCopyTextureSubImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCopyTextureSubImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
	return Gurax::Value::nil();
}

// opengl.glCopyTextureSubImage2D(texture:Number, level:Number, xoffset:Number, yoffset:Number, x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glCopyTextureSubImage2D_gurax, "glCopyTextureSubImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

Gurax_ImplementFunctionEx(glCopyTextureSubImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
	return Gurax::Value::nil();
}

// opengl.glCopyTextureSubImage3D(texture:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glCopyTextureSubImage3D_gurax, "glCopyTextureSubImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

Gurax_ImplementFunctionEx(glCopyTextureSubImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
	return Gurax::Value::nil();
}

// opengl.glCreateBuffers(n:Number, buffers:Pointer)
Gurax_DeclareFunctionAlias(glCreateBuffers_gurax, "glCreateBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* buffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!buffers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateBuffers(n, buffers);
	return Gurax::Value::nil();
}

// opengl.glCreateFramebuffers(n:Number, framebuffers:Pointer)
Gurax_DeclareFunctionAlias(glCreateFramebuffers_gurax, "glCreateFramebuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("framebuffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateFramebuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* framebuffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!framebuffers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateFramebuffers(n, framebuffers);
	return Gurax::Value::nil();
}

// opengl.glCreateProgramPipelines(n:Number, pipelines:Pointer)
Gurax_DeclareFunctionAlias(glCreateProgramPipelines_gurax, "glCreateProgramPipelines")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pipelines", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateProgramPipelines_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* pipelines = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!pipelines) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateProgramPipelines(n, pipelines);
	return Gurax::Value::nil();
}

// opengl.glCreateQueries(target:Number, n:Number, ids:Pointer)
Gurax_DeclareFunctionAlias(glCreateQueries_gurax, "glCreateQueries")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ids", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateQueries_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* ids = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!ids) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateQueries(target, n, ids);
	return Gurax::Value::nil();
}

// opengl.glCreateRenderbuffers(n:Number, renderbuffers:Pointer)
Gurax_DeclareFunctionAlias(glCreateRenderbuffers_gurax, "glCreateRenderbuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateRenderbuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* renderbuffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!renderbuffers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateRenderbuffers(n, renderbuffers);
	return Gurax::Value::nil();
}

// opengl.glCreateSamplers(n:Number, samplers:Pointer)
Gurax_DeclareFunctionAlias(glCreateSamplers_gurax, "glCreateSamplers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samplers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateSamplers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* samplers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!samplers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateSamplers(n, samplers);
	return Gurax::Value::nil();
}

// opengl.glCreateTextures(target:Number, n:Number, textures:Pointer)
Gurax_DeclareFunctionAlias(glCreateTextures_gurax, "glCreateTextures")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textures", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateTextures_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* textures = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!textures) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateTextures(target, n, textures);
	return Gurax::Value::nil();
}

// opengl.glCreateTransformFeedbacks(n:Number, ids:Pointer)
Gurax_DeclareFunctionAlias(glCreateTransformFeedbacks_gurax, "glCreateTransformFeedbacks")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ids", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateTransformFeedbacks_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* ids = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!ids) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateTransformFeedbacks(n, ids);
	return Gurax::Value::nil();
}

// opengl.glCreateVertexArrays(n:Number, arrays:Pointer)
Gurax_DeclareFunctionAlias(glCreateVertexArrays_gurax, "glCreateVertexArrays")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("arrays", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCreateVertexArrays_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* arrays = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!arrays) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glCreateVertexArrays(n, arrays);
	return Gurax::Value::nil();
}

// opengl.glDisableVertexArrayAttrib(vaobj:Number, index:Number)
Gurax_DeclareFunctionAlias(glDisableVertexArrayAttrib_gurax, "glDisableVertexArrayAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDisableVertexArrayAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	glDisableVertexArrayAttrib(vaobj, index);
	return Gurax::Value::nil();
}

// opengl.glEnableVertexArrayAttrib(vaobj:Number, index:Number)
Gurax_DeclareFunctionAlias(glEnableVertexArrayAttrib_gurax, "glEnableVertexArrayAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glEnableVertexArrayAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	// Function body
	glEnableVertexArrayAttrib(vaobj, index);
	return Gurax::Value::nil();
}

// opengl.glFlushMappedNamedBufferRange(buffer:Number, offset:Number, length:Number)
Gurax_DeclareFunctionAlias(glFlushMappedNamedBufferRange_gurax, "glFlushMappedNamedBufferRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFlushMappedNamedBufferRange_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr length = args_gurax.PickNumber<GLsizeiptr>();
	// Function body
	glFlushMappedNamedBufferRange(buffer, offset, length);
	return Gurax::Value::nil();
}

// opengl.glGenerateTextureMipmap(texture:Number)
Gurax_DeclareFunctionAlias(glGenerateTextureMipmap_gurax, "glGenerateTextureMipmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenerateTextureMipmap_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	// Function body
	glGenerateTextureMipmap(texture);
	return Gurax::Value::nil();
}

// opengl.glGetCompressedTextureImage(texture:Number, level:Number, bufSize:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetCompressedTextureImage_gurax, "glGetCompressedTextureImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetCompressedTextureImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetCompressedTextureImage(texture, level, bufSize, pixels);
	return Gurax::Value::nil();
}

// opengl.glGetNamedBufferParameteri64v(buffer:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedBufferParameteri64v_gurax, "glGetNamedBufferParameteri64v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedBufferParameteri64v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint64* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint64>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedBufferParameteri64v(buffer, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetNamedBufferParameteriv(buffer:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedBufferParameteriv_gurax, "glGetNamedBufferParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedBufferParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedBufferParameteriv(buffer, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetNamedBufferSubData(buffer:Number, offset:Number, size:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedBufferSubData_gurax, "glGetNamedBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	void* data = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedBufferSubData(buffer, offset, size, data);
	return Gurax::Value::nil();
}

// opengl.glGetNamedFramebufferAttachmentParameteriv(framebuffer:Number, attachment:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedFramebufferAttachmentParameteriv_gurax, "glGetNamedFramebufferAttachmentParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedFramebufferAttachmentParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetNamedFramebufferParameteriv(framebuffer:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedFramebufferParameteriv_gurax, "glGetNamedFramebufferParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedFramebufferParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedFramebufferParameteriv(framebuffer, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetNamedRenderbufferParameteriv(renderbuffer:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedRenderbufferParameteriv_gurax, "glGetNamedRenderbufferParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedRenderbufferParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetQueryBufferObjecti64v(id:Number, buffer:Number, pname:Number, offset:Number)
Gurax_DeclareFunctionAlias(glGetQueryBufferObjecti64v_gurax, "glGetQueryBufferObjecti64v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryBufferObjecti64v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	// Function body
	glGetQueryBufferObjecti64v(id, buffer, pname, offset);
	return Gurax::Value::nil();
}

// opengl.glGetQueryBufferObjectiv(id:Number, buffer:Number, pname:Number, offset:Number)
Gurax_DeclareFunctionAlias(glGetQueryBufferObjectiv_gurax, "glGetQueryBufferObjectiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryBufferObjectiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	// Function body
	glGetQueryBufferObjectiv(id, buffer, pname, offset);
	return Gurax::Value::nil();
}

// opengl.glGetQueryBufferObjectui64v(id:Number, buffer:Number, pname:Number, offset:Number)
Gurax_DeclareFunctionAlias(glGetQueryBufferObjectui64v_gurax, "glGetQueryBufferObjectui64v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryBufferObjectui64v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	// Function body
	glGetQueryBufferObjectui64v(id, buffer, pname, offset);
	return Gurax::Value::nil();
}

// opengl.glGetQueryBufferObjectuiv(id:Number, buffer:Number, pname:Number, offset:Number)
Gurax_DeclareFunctionAlias(glGetQueryBufferObjectuiv_gurax, "glGetQueryBufferObjectuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetQueryBufferObjectuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint id = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	// Function body
	glGetQueryBufferObjectuiv(id, buffer, pname, offset);
	return Gurax::Value::nil();
}

// opengl.glGetTextureImage(texture:Number, level:Number, format:Number, type:Number, bufSize:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureImage_gurax, "glGetTextureImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureImage(texture, level, format, type, bufSize, pixels);
	return Gurax::Value::nil();
}

// opengl.glGetTextureLevelParameterfv(texture:Number, level:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureLevelParameterfv_gurax, "glGetTextureLevelParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureLevelParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureLevelParameterfv(texture, level, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTextureLevelParameteriv(texture:Number, level:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureLevelParameteriv_gurax, "glGetTextureLevelParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureLevelParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureLevelParameteriv(texture, level, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTextureParameterIiv(texture:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureParameterIiv_gurax, "glGetTextureParameterIiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureParameterIiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureParameterIiv(texture, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTextureParameterIuiv(texture:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureParameterIuiv_gurax, "glGetTextureParameterIuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureParameterIuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureParameterIuiv(texture, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTextureParameterfv(texture:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureParameterfv_gurax, "glGetTextureParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureParameterfv(texture, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTextureParameteriv(texture:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureParameteriv_gurax, "glGetTextureParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureParameteriv(texture, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetTransformFeedbacki64_v(xfb:Number, pname:Number, index:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetTransformFeedbacki64_v_gurax, "glGetTransformFeedbacki64_v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfb", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTransformFeedbacki64_v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint xfb = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint64* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint64>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTransformFeedbacki64_v(xfb, pname, index, param);
	return Gurax::Value::nil();
}

// opengl.glGetTransformFeedbacki_v(xfb:Number, pname:Number, index:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetTransformFeedbacki_v_gurax, "glGetTransformFeedbacki_v")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfb", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTransformFeedbacki_v_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint xfb = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTransformFeedbacki_v(xfb, pname, index, param);
	return Gurax::Value::nil();
}

// opengl.glGetTransformFeedbackiv(xfb:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetTransformFeedbackiv_gurax, "glGetTransformFeedbackiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfb", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTransformFeedbackiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint xfb = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTransformFeedbackiv(xfb, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetVertexArrayIndexed64iv(vaobj:Number, index:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexArrayIndexed64iv_gurax, "glGetVertexArrayIndexed64iv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexArrayIndexed64iv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint64* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint64>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetVertexArrayIndexediv(vaobj:Number, index:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexArrayIndexediv_gurax, "glGetVertexArrayIndexediv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexArrayIndexediv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexArrayIndexediv(vaobj, index, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetVertexArrayiv(vaobj:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glGetVertexArrayiv_gurax, "glGetVertexArrayiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetVertexArrayiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!param) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetVertexArrayiv(vaobj, pname, param);
	return Gurax::Value::nil();
}

// opengl.glInvalidateNamedFramebufferData(framebuffer:Number, numAttachments:Number, attachments:Pointer)
Gurax_DeclareFunctionAlias(glInvalidateNamedFramebufferData_gurax, "glInvalidateNamedFramebufferData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numAttachments", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachments", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glInvalidateNamedFramebufferData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLsizei numAttachments = args_gurax.PickNumber<GLsizei>();
	const GLenum* attachments = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLenum>();
	// Function body
	glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
	return Gurax::Value::nil();
}

// opengl.glInvalidateNamedFramebufferSubData(framebuffer:Number, numAttachments:Number, attachments:Pointer, x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glInvalidateNamedFramebufferSubData_gurax, "glInvalidateNamedFramebufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numAttachments", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachments", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glInvalidateNamedFramebufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLsizei numAttachments = args_gurax.PickNumber<GLsizei>();
	const GLenum* attachments = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLenum>();
	GLint x = args_gurax.PickNumber<GLint>();
	GLint y = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
	return Gurax::Value::nil();
}

// opengl.glNamedBufferData(buffer:Number, size:Number, data:Pointer, usage:Number)
Gurax_DeclareFunctionAlias(glNamedBufferData_gurax, "glNamedBufferData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("usage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedBufferData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLenum usage = args_gurax.PickNumber<GLenum>();
	// Function body
	glNamedBufferData(buffer, size, data, usage);
	return Gurax::Value::nil();
}

// opengl.glNamedBufferStorage(buffer:Number, size:Number, data:Pointer, flags:Number)
Gurax_DeclareFunctionAlias(glNamedBufferStorage_gurax, "glNamedBufferStorage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedBufferStorage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLbitfield flags = args_gurax.PickNumber<GLbitfield>();
	// Function body
	glNamedBufferStorage(buffer, size, data, flags);
	return Gurax::Value::nil();
}

// opengl.glNamedBufferSubData(buffer:Number, offset:Number, size:Number, data:Pointer)
Gurax_DeclareFunctionAlias(glNamedBufferSubData_gurax, "glNamedBufferSubData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedBufferSubData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glNamedBufferSubData(buffer, offset, size, data);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferDrawBuffer(framebuffer:Number, mode:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferDrawBuffer_gurax, "glNamedFramebufferDrawBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferDrawBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glNamedFramebufferDrawBuffer(framebuffer, mode);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferDrawBuffers(framebuffer:Number, n:Number, bufs:Pointer)
Gurax_DeclareFunctionAlias(glNamedFramebufferDrawBuffers_gurax, "glNamedFramebufferDrawBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufs", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferDrawBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	const GLenum* bufs = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLenum>();
	// Function body
	glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferParameteri(framebuffer:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferParameteri_gurax, "glNamedFramebufferParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferParameteri_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glNamedFramebufferParameteri(framebuffer, pname, param);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferReadBuffer(framebuffer:Number, mode:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferReadBuffer_gurax, "glNamedFramebufferReadBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferReadBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glNamedFramebufferReadBuffer(framebuffer, mode);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferRenderbuffer(framebuffer:Number, attachment:Number, renderbuffertarget:Number, renderbuffer:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferRenderbuffer_gurax, "glNamedFramebufferRenderbuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffertarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferRenderbuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum renderbuffertarget = args_gurax.PickNumber<GLenum>();
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferTexture(framebuffer:Number, attachment:Number, texture:Number, level:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferTexture_gurax, "glNamedFramebufferTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	// Function body
	glNamedFramebufferTexture(framebuffer, attachment, texture, level);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferTextureLayer(framebuffer:Number, attachment:Number, texture:Number, level:Number, layer:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferTextureLayer_gurax, "glNamedFramebufferTextureLayer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("layer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferTextureLayer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint layer = args_gurax.PickNumber<GLint>();
	// Function body
	glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
	return Gurax::Value::nil();
}

// opengl.glNamedRenderbufferStorage(renderbuffer:Number, internalformat:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glNamedRenderbufferStorage_gurax, "glNamedRenderbufferStorage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedRenderbufferStorage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
	return Gurax::Value::nil();
}

// opengl.glNamedRenderbufferStorageMultisample(renderbuffer:Number, samples:Number, internalformat:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glNamedRenderbufferStorageMultisample_gurax, "glNamedRenderbufferStorageMultisample")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samples", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedRenderbufferStorageMultisample_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	GLsizei samples = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
	return Gurax::Value::nil();
}

// opengl.glTextureBuffer(texture:Number, internalformat:Number, buffer:Number)
Gurax_DeclareFunctionAlias(glTextureBuffer_gurax, "glTextureBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glTextureBuffer(texture, internalformat, buffer);
	return Gurax::Value::nil();
}

// opengl.glTextureBufferRange(texture:Number, internalformat:Number, buffer:Number, offset:Number, size:Number)
Gurax_DeclareFunctionAlias(glTextureBufferRange_gurax, "glTextureBufferRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureBufferRange_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	// Function body
	glTextureBufferRange(texture, internalformat, buffer, offset, size);
	return Gurax::Value::nil();
}

// opengl.glTextureParameterIiv(texture:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glTextureParameterIiv_gurax, "glTextureParameterIiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureParameterIiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	const GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLint>();
	// Function body
	glTextureParameterIiv(texture, pname, params);
	return Gurax::Value::nil();
}

// opengl.glTextureParameterIuiv(texture:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glTextureParameterIuiv_gurax, "glTextureParameterIuiv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureParameterIuiv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	const GLuint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	// Function body
	glTextureParameterIuiv(texture, pname, params);
	return Gurax::Value::nil();
}

// opengl.glTextureParameterf(texture:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glTextureParameterf_gurax, "glTextureParameterf")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureParameterf_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLfloat param = args_gurax.PickNumber<GLfloat>();
	// Function body
	glTextureParameterf(texture, pname, param);
	return Gurax::Value::nil();
}

// opengl.glTextureParameterfv(texture:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glTextureParameterfv_gurax, "glTextureParameterfv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureParameterfv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	const GLfloat* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLfloat>();
	// Function body
	glTextureParameterfv(texture, pname, param);
	return Gurax::Value::nil();
}

// opengl.glTextureParameteri(texture:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glTextureParameteri_gurax, "glTextureParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureParameteri_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glTextureParameteri(texture, pname, param);
	return Gurax::Value::nil();
}

// opengl.glTextureParameteriv(texture:Number, pname:Number, param:Pointer)
Gurax_DeclareFunctionAlias(glTextureParameteriv_gurax, "glTextureParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	const GLint* param = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLint>();
	// Function body
	glTextureParameteriv(texture, pname, param);
	return Gurax::Value::nil();
}

// opengl.glTextureStorage1D(texture:Number, levels:Number, internalformat:Number, width:Number)
Gurax_DeclareFunctionAlias(glTextureStorage1D_gurax, "glTextureStorage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("levels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureStorage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLsizei levels = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	// Function body
	glTextureStorage1D(texture, levels, internalformat, width);
	return Gurax::Value::nil();
}

// opengl.glTextureStorage2D(texture:Number, levels:Number, internalformat:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glTextureStorage2D_gurax, "glTextureStorage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("levels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureStorage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLsizei levels = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glTextureStorage2D(texture, levels, internalformat, width, height);
	return Gurax::Value::nil();
}

// opengl.glTextureStorage2DMultisample(texture:Number, samples:Number, internalformat:Number, width:Number, height:Number, fixedsamplelocations:Bool)
Gurax_DeclareFunctionAlias(glTextureStorage2DMultisample_gurax, "glTextureStorage2DMultisample")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samples", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fixedsamplelocations", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureStorage2DMultisample_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLsizei samples = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLboolean fixedsamplelocations = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
	return Gurax::Value::nil();
}

// opengl.glTextureStorage3D(texture:Number, levels:Number, internalformat:Number, width:Number, height:Number, depth:Number)
Gurax_DeclareFunctionAlias(glTextureStorage3D_gurax, "glTextureStorage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("levels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureStorage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLsizei levels = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	// Function body
	glTextureStorage3D(texture, levels, internalformat, width, height, depth);
	return Gurax::Value::nil();
}

// opengl.glTextureStorage3DMultisample(texture:Number, samples:Number, internalformat:Number, width:Number, height:Number, depth:Number, fixedsamplelocations:Bool)
Gurax_DeclareFunctionAlias(glTextureStorage3DMultisample_gurax, "glTextureStorage3DMultisample")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samples", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fixedsamplelocations", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureStorage3DMultisample_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLsizei samples = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLboolean fixedsamplelocations = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
	return Gurax::Value::nil();
}

// opengl.glTextureSubImage1D(texture:Number, level:Number, xoffset:Number, width:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTextureSubImage1D_gurax, "glTextureSubImage1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureSubImage1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
	return Gurax::Value::nil();
}

// opengl.glTextureSubImage2D(texture:Number, level:Number, xoffset:Number, yoffset:Number, width:Number, height:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTextureSubImage2D_gurax, "glTextureSubImage2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTextureSubImage2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
	return Gurax::Value::nil();
}

// opengl.glTextureSubImage3D(texture:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, format:Number, type:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glTextureSubImage3D_gurax, "glTextureSubImage3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

Gurax_ImplementFunctionEx(glTextureSubImage3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	return Gurax::Value::nil();
}

// opengl.glTransformFeedbackBufferBase(xfb:Number, index:Number, buffer:Number)
Gurax_DeclareFunctionAlias(glTransformFeedbackBufferBase_gurax, "glTransformFeedbackBufferBase")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfb", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTransformFeedbackBufferBase_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint xfb = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glTransformFeedbackBufferBase(xfb, index, buffer);
	return Gurax::Value::nil();
}

// opengl.glTransformFeedbackBufferRange(xfb:Number, index:Number, buffer:Number, offset:Number, size:Number)
Gurax_DeclareFunctionAlias(glTransformFeedbackBufferRange_gurax, "glTransformFeedbackBufferRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xfb", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glTransformFeedbackBufferRange_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint xfb = args_gurax.PickNumber<GLuint>();
	GLuint index = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizeiptr size = args_gurax.PickNumber<GLsizeiptr>();
	// Function body
	glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
	return Gurax::Value::nil();
}

// opengl.glUnmapNamedBuffer(buffer:Number)
Gurax_DeclareFunctionAlias(glUnmapNamedBuffer_gurax, "glUnmapNamedBuffer")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUnmapNamedBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glUnmapNamedBuffer(buffer);
	return new Gurax::Value_Bool(!!rtn);
}

// opengl.glVertexArrayAttribBinding(vaobj:Number, attribindex:Number, bindingindex:Number)
Gurax_DeclareFunctionAlias(glVertexArrayAttribBinding_gurax, "glVertexArrayAttribBinding")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attribindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bindingindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayAttribBinding_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint attribindex = args_gurax.PickNumber<GLuint>();
	GLuint bindingindex = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayAttribFormat(vaobj:Number, attribindex:Number, size:Number, type:Number, normalized:Bool, relativeoffset:Number)
Gurax_DeclareFunctionAlias(glVertexArrayAttribFormat_gurax, "glVertexArrayAttribFormat")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attribindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("normalized", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("relativeoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayAttribFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint attribindex = args_gurax.PickNumber<GLuint>();
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLboolean normalized = static_cast<GLboolean>(args_gurax.PickBool());
	GLuint relativeoffset = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayAttribIFormat(vaobj:Number, attribindex:Number, size:Number, type:Number, relativeoffset:Number)
Gurax_DeclareFunctionAlias(glVertexArrayAttribIFormat_gurax, "glVertexArrayAttribIFormat")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attribindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("relativeoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayAttribIFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint attribindex = args_gurax.PickNumber<GLuint>();
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLuint relativeoffset = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayAttribLFormat(vaobj:Number, attribindex:Number, size:Number, type:Number, relativeoffset:Number)
Gurax_DeclareFunctionAlias(glVertexArrayAttribLFormat_gurax, "glVertexArrayAttribLFormat")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attribindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("relativeoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayAttribLFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint attribindex = args_gurax.PickNumber<GLuint>();
	GLint size = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLuint relativeoffset = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayBindingDivisor(vaobj:Number, bindingindex:Number, divisor:Number)
Gurax_DeclareFunctionAlias(glVertexArrayBindingDivisor_gurax, "glVertexArrayBindingDivisor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bindingindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("divisor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayBindingDivisor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint bindingindex = args_gurax.PickNumber<GLuint>();
	GLuint divisor = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayElementBuffer(vaobj:Number, buffer:Number)
Gurax_DeclareFunctionAlias(glVertexArrayElementBuffer_gurax, "glVertexArrayElementBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayElementBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glVertexArrayElementBuffer(vaobj, buffer);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayVertexBuffer(vaobj:Number, bindingindex:Number, buffer:Number, offset:Number, stride:Number)
Gurax_DeclareFunctionAlias(glVertexArrayVertexBuffer_gurax, "glVertexArrayVertexBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bindingindex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayVertexBuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint bindingindex = args_gurax.PickNumber<GLuint>();
	GLuint buffer = args_gurax.PickNumber<GLuint>();
	GLintptr offset = args_gurax.PickNumber<GLintptr>();
	GLsizei stride = args_gurax.PickNumber<GLsizei>();
	// Function body
	glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
	return Gurax::Value::nil();
}

// opengl.glVertexArrayVertexBuffers(vaobj:Number, first:Number, count:Number, buffers:Pointer, offsets:Pointer, strides:Pointer)
Gurax_DeclareFunctionAlias(glVertexArrayVertexBuffers_gurax, "glVertexArrayVertexBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vaobj", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("first", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offsets", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("strides", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glVertexArrayVertexBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint vaobj = args_gurax.PickNumber<GLuint>();
	GLuint first = args_gurax.PickNumber<GLuint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLuint* buffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	const GLintptr* offsets = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLintptr>();
	const GLsizei* strides = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLsizei>();
	// Function body
	glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
	return Gurax::Value::nil();
}

// opengl.glDrawBuffersARB(n:Number, bufs:Pointer)
Gurax_DeclareFunctionAlias(glDrawBuffersARB_gurax, "glDrawBuffersARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufs", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawBuffersARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	const GLenum* bufs = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLenum>();
	// Function body
	glDrawBuffersARB(n, bufs);
	return Gurax::Value::nil();
}

// opengl.glBlendEquationSeparateiARB(buf:Number, modeRGB:Number, modeAlpha:Number)
Gurax_DeclareFunctionAlias(glBlendEquationSeparateiARB_gurax, "glBlendEquationSeparateiARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeAlpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBlendEquationSeparateiARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum modeRGB = args_gurax.PickNumber<GLenum>();
	GLenum modeAlpha = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
	return Gurax::Value::nil();
}

// opengl.glBlendEquationiARB(buf:Number, mode:Number)
Gurax_DeclareFunctionAlias(glBlendEquationiARB_gurax, "glBlendEquationiARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBlendEquationiARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum mode = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendEquationiARB(buf, mode);
	return Gurax::Value::nil();
}

// opengl.glBlendFuncSeparateiARB(buf:Number, srcRGB:Number, dstRGB:Number, srcAlpha:Number, dstAlpha:Number)
Gurax_DeclareFunctionAlias(glBlendFuncSeparateiARB_gurax, "glBlendFuncSeparateiARB")
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

Gurax_ImplementFunctionEx(glBlendFuncSeparateiARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum srcRGB = args_gurax.PickNumber<GLenum>();
	GLenum dstRGB = args_gurax.PickNumber<GLenum>();
	GLenum srcAlpha = args_gurax.PickNumber<GLenum>();
	GLenum dstAlpha = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	return Gurax::Value::nil();
}

// opengl.glBlendFunciARB(buf:Number, src:Number, dst:Number)
Gurax_DeclareFunctionAlias(glBlendFunciARB_gurax, "glBlendFunciARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBlendFunciARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint buf = args_gurax.PickNumber<GLuint>();
	GLenum src = args_gurax.PickNumber<GLenum>();
	GLenum dst = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlendFunciARB(buf, src, dst);
	return Gurax::Value::nil();
}

// opengl.glDrawElementsBaseVertex(mode:Number, count:Number, type:Number, indices:Pointer, basevertex:Number)
Gurax_DeclareFunctionAlias(glDrawElementsBaseVertex_gurax, "glDrawElementsBaseVertex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("basevertex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawElementsBaseVertex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* indices = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!indices) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLint basevertex = args_gurax.PickNumber<GLint>();
	// Function body
	glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	return Gurax::Value::nil();
}

// opengl.glDrawElementsInstancedBaseVertex(mode:Number, count:Number, type:Number, indices:Pointer, primcount:Number, basevertex:Number)
Gurax_DeclareFunctionAlias(glDrawElementsInstancedBaseVertex_gurax, "glDrawElementsInstancedBaseVertex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primcount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("basevertex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawElementsInstancedBaseVertex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indices = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei primcount = args_gurax.PickNumber<GLsizei>();
	GLint basevertex = args_gurax.PickNumber<GLint>();
	// Function body
	glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
	return Gurax::Value::nil();
}

// opengl.glDrawRangeElementsBaseVertex(mode:Number, start:Number, end:Number, count:Number, type:Number, indices:Pointer, basevertex:Number)
Gurax_DeclareFunctionAlias(glDrawRangeElementsBaseVertex_gurax, "glDrawRangeElementsBaseVertex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("start", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("end", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indices", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("basevertex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawRangeElementsBaseVertex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLuint start = args_gurax.PickNumber<GLuint>();
	GLuint end = args_gurax.PickNumber<GLuint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	void* indices = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!indices) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	GLint basevertex = args_gurax.PickNumber<GLint>();
	// Function body
	glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	return Gurax::Value::nil();
}

// opengl.glDrawArraysIndirect(mode:Number, indirect:Pointer)
Gurax_DeclareFunctionAlias(glDrawArraysIndirect_gurax, "glDrawArraysIndirect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indirect", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawArraysIndirect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	const void* indirect = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawArraysIndirect(mode, indirect);
	return Gurax::Value::nil();
}

// opengl.glDrawElementsIndirect(mode:Number, type:Number, indirect:Pointer)
Gurax_DeclareFunctionAlias(glDrawElementsIndirect_gurax, "glDrawElementsIndirect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("indirect", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDrawElementsIndirect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum mode = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* indirect = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	// Function body
	glDrawElementsIndirect(mode, type, indirect);
	return Gurax::Value::nil();
}

// opengl.glFramebufferParameteri(target:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glFramebufferParameteri_gurax, "glFramebufferParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferParameteri_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferParameteri(target, pname, param);
	return Gurax::Value::nil();
}

// opengl.glGetFramebufferParameteriv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetFramebufferParameteriv_gurax, "glGetFramebufferParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetFramebufferParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetFramebufferParameteriv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetNamedFramebufferParameterivEXT(framebuffer:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetNamedFramebufferParameterivEXT_gurax, "glGetNamedFramebufferParameterivEXT")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetNamedFramebufferParameterivEXT_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetNamedFramebufferParameterivEXT(framebuffer, pname, params);
	return Gurax::Value::nil();
}

// opengl.glNamedFramebufferParameteriEXT(framebuffer:Number, pname:Number, param:Number)
Gurax_DeclareFunctionAlias(glNamedFramebufferParameteriEXT_gurax, "glNamedFramebufferParameteriEXT")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("param", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glNamedFramebufferParameteriEXT_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint param = args_gurax.PickNumber<GLint>();
	// Function body
	glNamedFramebufferParameteriEXT(framebuffer, pname, param);
	return Gurax::Value::nil();
}

// opengl.glBindFramebuffer(target:Number, framebuffer:Number)
Gurax_DeclareFunctionAlias(glBindFramebuffer_gurax, "glBindFramebuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBindFramebuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glBindFramebuffer(target, framebuffer);
	return Gurax::Value::nil();
}

// opengl.glBindRenderbuffer(target:Number, renderbuffer:Number)
Gurax_DeclareFunctionAlias(glBindRenderbuffer_gurax, "glBindRenderbuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBindRenderbuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glBindRenderbuffer(target, renderbuffer);
	return Gurax::Value::nil();
}

// opengl.glBlitFramebuffer(srcX0:Number, srcY0:Number, srcX1:Number, srcY1:Number, dstX0:Number, dstY0:Number, dstX1:Number, dstY1:Number, mask:Number, filter:Number)
Gurax_DeclareFunctionAlias(glBlitFramebuffer_gurax, "glBlitFramebuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("srcX0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcY0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcX1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcY1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstX0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstY0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstX1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstY1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glBlitFramebuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint srcX0 = args_gurax.PickNumber<GLint>();
	GLint srcY0 = args_gurax.PickNumber<GLint>();
	GLint srcX1 = args_gurax.PickNumber<GLint>();
	GLint srcY1 = args_gurax.PickNumber<GLint>();
	GLint dstX0 = args_gurax.PickNumber<GLint>();
	GLint dstY0 = args_gurax.PickNumber<GLint>();
	GLint dstX1 = args_gurax.PickNumber<GLint>();
	GLint dstY1 = args_gurax.PickNumber<GLint>();
	GLbitfield mask = args_gurax.PickNumber<GLbitfield>();
	GLenum filter = args_gurax.PickNumber<GLenum>();
	// Function body
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	return Gurax::Value::nil();
}

// opengl.glCheckFramebufferStatus(target:Number)
Gurax_DeclareFunctionAlias(glCheckFramebufferStatus_gurax, "glCheckFramebufferStatus")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glCheckFramebufferStatus_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	// Function body
	GLenum rtn = glCheckFramebufferStatus(target);
	return new Gurax::Value_Number(rtn);
}

// opengl.glDeleteFramebuffers(n:Number, framebuffers:Pointer)
Gurax_DeclareFunctionAlias(glDeleteFramebuffers_gurax, "glDeleteFramebuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("framebuffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDeleteFramebuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	const GLuint* framebuffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	// Function body
	glDeleteFramebuffers(n, framebuffers);
	return Gurax::Value::nil();
}

// opengl.glDeleteRenderbuffers(n:Number, renderbuffers:Pointer)
Gurax_DeclareFunctionAlias(glDeleteRenderbuffers_gurax, "glDeleteRenderbuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glDeleteRenderbuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	const GLuint* renderbuffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	// Function body
	glDeleteRenderbuffers(n, renderbuffers);
	return Gurax::Value::nil();
}

// opengl.glFramebufferRenderbuffer(target:Number, attachment:Number, renderbuffertarget:Number, renderbuffer:Number)
Gurax_DeclareFunctionAlias(glFramebufferRenderbuffer_gurax, "glFramebufferRenderbuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffertarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferRenderbuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum renderbuffertarget = args_gurax.PickNumber<GLenum>();
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	// Function body
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTexture1D(target:Number, attachment:Number, textarget:Number, texture:Number, level:Number)
Gurax_DeclareFunctionAlias(glFramebufferTexture1D_gurax, "glFramebufferTexture1D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferTexture1D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum textarget = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTexture1D(target, attachment, textarget, texture, level);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTexture2D(target:Number, attachment:Number, textarget:Number, texture:Number, level:Number)
Gurax_DeclareFunctionAlias(glFramebufferTexture2D_gurax, "glFramebufferTexture2D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferTexture2D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum textarget = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTexture3D(target:Number, attachment:Number, textarget:Number, texture:Number, level:Number, layer:Number)
Gurax_DeclareFunctionAlias(glFramebufferTexture3D_gurax, "glFramebufferTexture3D")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textarget", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("layer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferTexture3D_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum textarget = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint layer = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTexture3D(target, attachment, textarget, texture, level, layer);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTextureLayer(target:Number, attachment:Number, texture:Number, level:Number, layer:Number)
Gurax_DeclareFunctionAlias(glFramebufferTextureLayer_gurax, "glFramebufferTextureLayer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("layer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferTextureLayer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint layer = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTextureLayer(target, attachment, texture, level, layer);
	return Gurax::Value::nil();
}

// opengl.glGenFramebuffers(n:Number, framebuffers:Pointer)
Gurax_DeclareFunctionAlias(glGenFramebuffers_gurax, "glGenFramebuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("framebuffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenFramebuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* framebuffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!framebuffers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGenFramebuffers(n, framebuffers);
	return Gurax::Value::nil();
}

// opengl.glGenRenderbuffers(n:Number, renderbuffers:Pointer)
Gurax_DeclareFunctionAlias(glGenRenderbuffers_gurax, "glGenRenderbuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderbuffers", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenRenderbuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLsizei n = args_gurax.PickNumber<GLsizei>();
	GLuint* renderbuffers = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLuint>();
	if (!renderbuffers) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGenRenderbuffers(n, renderbuffers);
	return Gurax::Value::nil();
}

// opengl.glGenerateMipmap(target:Number)
Gurax_DeclareFunctionAlias(glGenerateMipmap_gurax, "glGenerateMipmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGenerateMipmap_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	// Function body
	glGenerateMipmap(target);
	return Gurax::Value::nil();
}

// opengl.glGetFramebufferAttachmentParameteriv(target:Number, attachment:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetFramebufferAttachmentParameteriv_gurax, "glGetFramebufferAttachmentParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetFramebufferAttachmentParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	return Gurax::Value::nil();
}

// opengl.glGetRenderbufferParameteriv(target:Number, pname:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetRenderbufferParameteriv_gurax, "glGetRenderbufferParameteriv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetRenderbufferParameteriv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLint>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetRenderbufferParameteriv(target, pname, params);
	return Gurax::Value::nil();
}

// opengl.glIsFramebuffer(framebuffer:Number)
Gurax_DeclareFunctionAlias(glIsFramebuffer_gurax, "glIsFramebuffer")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("framebuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glIsFramebuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint framebuffer = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsFramebuffer(framebuffer);
	return new Gurax::Value_Bool(!!rtn);
}

// opengl.glIsRenderbuffer(renderbuffer:Number)
Gurax_DeclareFunctionAlias(glIsRenderbuffer_gurax, "glIsRenderbuffer")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderbuffer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glIsRenderbuffer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint renderbuffer = args_gurax.PickNumber<GLuint>();
	// Function body
	GLboolean rtn = glIsRenderbuffer(renderbuffer);
	return new Gurax::Value_Bool(!!rtn);
}

// opengl.glRenderbufferStorage(target:Number, internalformat:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glRenderbufferStorage_gurax, "glRenderbufferStorage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glRenderbufferStorage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glRenderbufferStorage(target, internalformat, width, height);
	return Gurax::Value::nil();
}

// opengl.glRenderbufferStorageMultisample(target:Number, samples:Number, internalformat:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glRenderbufferStorageMultisample_gurax, "glRenderbufferStorageMultisample")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samples", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("internalformat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glRenderbufferStorageMultisample_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLsizei samples = args_gurax.PickNumber<GLsizei>();
	GLenum internalformat = args_gurax.PickNumber<GLenum>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	// Function body
	glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTextureARB(target:Number, attachment:Number, texture:Number, level:Number)
Gurax_DeclareFunctionAlias(glFramebufferTextureARB_gurax, "glFramebufferTextureARB")
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

Gurax_ImplementFunctionEx(glFramebufferTextureARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTextureARB(target, attachment, texture, level);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTextureFaceARB(target:Number, attachment:Number, texture:Number, level:Number, face:Number)
Gurax_DeclareFunctionAlias(glFramebufferTextureFaceARB_gurax, "glFramebufferTextureFaceARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("face", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferTextureFaceARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLenum face = args_gurax.PickNumber<GLenum>();
	// Function body
	glFramebufferTextureFaceARB(target, attachment, texture, level, face);
	return Gurax::Value::nil();
}

// opengl.glFramebufferTextureLayerARB(target:Number, attachment:Number, texture:Number, level:Number, layer:Number)
Gurax_DeclareFunctionAlias(glFramebufferTextureLayerARB_gurax, "glFramebufferTextureLayerARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attachment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("layer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glFramebufferTextureLayerARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLenum attachment = args_gurax.PickNumber<GLenum>();
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint layer = args_gurax.PickNumber<GLint>();
	// Function body
	glFramebufferTextureLayerARB(target, attachment, texture, level, layer);
	return Gurax::Value::nil();
}

// opengl.glProgramParameteriARB(program:Number, pname:Number, value:Number)
Gurax_DeclareFunctionAlias(glProgramParameteriARB_gurax, "glProgramParameteriARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glProgramParameteriARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint value = args_gurax.PickNumber<GLint>();
	// Function body
	glProgramParameteriARB(program, pname, value);
	return Gurax::Value::nil();
}

// opengl.glProgramBinary(program:Number, binaryFormat:Number, binary:Pointer, length:Number)
Gurax_DeclareFunctionAlias(glProgramBinary_gurax, "glProgramBinary")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("binaryFormat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("binary", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glProgramBinary_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLenum binaryFormat = args_gurax.PickNumber<GLenum>();
	const void* binary = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<const void*>();
	GLsizei length = args_gurax.PickNumber<GLsizei>();
	// Function body
	glProgramBinary(program, binaryFormat, binary, length);
	return Gurax::Value::nil();
}

// opengl.glProgramParameteri(program:Number, pname:Number, value:Number)
Gurax_DeclareFunctionAlias(glProgramParameteri_gurax, "glProgramParameteri")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pname", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glProgramParameteri_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLenum pname = args_gurax.PickNumber<GLenum>();
	GLint value = args_gurax.PickNumber<GLint>();
	// Function body
	glProgramParameteri(program, pname, value);
	return Gurax::Value::nil();
}

// opengl.glGetCompressedTextureSubImage(texture:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, bufSize:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetCompressedTextureSubImage_gurax, "glGetCompressedTextureSubImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetCompressedTextureSubImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
	return Gurax::Value::nil();
}

// opengl.glGetTextureSubImage(texture:Number, level:Number, xoffset:Number, yoffset:Number, zoffset:Number, width:Number, height:Number, depth:Number, format:Number, type:Number, bufSize:Number, pixels:Pointer)
Gurax_DeclareFunctionAlias(glGetTextureSubImage_gurax, "glGetTextureSubImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("zoffset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bufSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetTextureSubImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint texture = args_gurax.PickNumber<GLuint>();
	GLint level = args_gurax.PickNumber<GLint>();
	GLint xoffset = args_gurax.PickNumber<GLint>();
	GLint yoffset = args_gurax.PickNumber<GLint>();
	GLint zoffset = args_gurax.PickNumber<GLint>();
	GLsizei width = args_gurax.PickNumber<GLsizei>();
	GLsizei height = args_gurax.PickNumber<GLsizei>();
	GLsizei depth = args_gurax.PickNumber<GLsizei>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	GLsizei bufSize = args_gurax.PickNumber<GLsizei>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
	return Gurax::Value::nil();
}

// opengl.glSpecializeShaderARB(shader:Number, pEntryPoint:Pointer, numSpecializationConstants:Number, pConstantIndex:Pointer, pConstantValue:Pointer)
Gurax_DeclareFunctionAlias(glSpecializeShaderARB_gurax, "glSpecializeShaderARB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("shader", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pEntryPoint", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numSpecializationConstants", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pConstantIndex", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pConstantValue", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glSpecializeShaderARB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint shader = args_gurax.PickNumber<GLuint>();
	const GLchar* pEntryPoint = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLchar>();
	GLuint numSpecializationConstants = args_gurax.PickNumber<GLuint>();
	const GLuint* pConstantIndex = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	const GLuint* pConstantValue = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLuint>();
	// Function body
	glSpecializeShaderARB(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
	return Gurax::Value::nil();
}

// opengl.glGetUniformdv(program:Number, location:Number, params:Pointer)
Gurax_DeclareFunctionAlias(glGetUniformdv_gurax, "glGetUniformdv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("program", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("params", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glGetUniformdv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLuint program = args_gurax.PickNumber<GLuint>();
	GLint location = args_gurax.PickNumber<GLint>();
	GLdouble* params = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!params) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	glGetUniformdv(program, location, params);
	return Gurax::Value::nil();
}

// opengl.glUniform1d(location:Number, x:Number)
Gurax_DeclareFunctionAlias(glUniform1d_gurax, "glUniform1d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform1d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	// Function body
	glUniform1d(location, x);
	return Gurax::Value::nil();
}

// opengl.glUniform1dv(location:Number, count:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glUniform1dv_gurax, "glUniform1dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform1dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniform1dv(location, count, value);
	return Gurax::Value::nil();
}

// opengl.glUniform2d(location:Number, x:Number, y:Number)
Gurax_DeclareFunctionAlias(glUniform2d_gurax, "glUniform2d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform2d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	// Function body
	glUniform2d(location, x, y);
	return Gurax::Value::nil();
}

// opengl.glUniform2dv(location:Number, count:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glUniform2dv_gurax, "glUniform2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniform2dv(location, count, value);
	return Gurax::Value::nil();
}

// opengl.glUniform3d(location:Number, x:Number, y:Number, z:Number)
Gurax_DeclareFunctionAlias(glUniform3d_gurax, "glUniform3d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform3d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	glUniform3d(location, x, y, z);
	return Gurax::Value::nil();
}

// opengl.glUniform3dv(location:Number, count:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glUniform3dv_gurax, "glUniform3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniform3dv(location, count, value);
	return Gurax::Value::nil();
}

// opengl.glUniform4d(location:Number, x:Number, y:Number, z:Number, w:Number)
Gurax_DeclareFunctionAlias(glUniform4d_gurax, "glUniform4d")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform4d_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	GLdouble w = args_gurax.PickNumber<GLdouble>();
	// Function body
	glUniform4d(location, x, y, z, w);
	return Gurax::Value::nil();
}

// opengl.glUniform4dv(location:Number, count:Number, value:Pointer)
Gurax_DeclareFunctionAlias(glUniform4dv_gurax, "glUniform4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniform4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniform4dv(location, count, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix2dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix2dv_gurax, "glUniformMatrix2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix2dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix2x3dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix2x3dv_gurax, "glUniformMatrix2x3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix2x3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix2x3dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix2x4dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix2x4dv_gurax, "glUniformMatrix2x4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix2x4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix2x4dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix3dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix3dv_gurax, "glUniformMatrix3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix3dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix3x2dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix3x2dv_gurax, "glUniformMatrix3x2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix3x2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix3x2dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix3x4dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix3x4dv_gurax, "glUniformMatrix3x4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix3x4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix3x4dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix4dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix4dv_gurax, "glUniformMatrix4dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix4dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix4dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix4x2dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix4x2dv_gurax, "glUniformMatrix4x2dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix4x2dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix4x2dv(location, count, transpose, value);
	return Gurax::Value::nil();
}

// opengl.glUniformMatrix4x3dv(location:Number, count:Number, transpose:Bool, value:Pointer)
Gurax_DeclareFunctionAlias(glUniformMatrix4x3dv_gurax, "glUniformMatrix4x3dv")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("location", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("transpose", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(glUniformMatrix4x3dv_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLint location = args_gurax.PickNumber<GLint>();
	GLsizei count = args_gurax.PickNumber<GLsizei>();
	GLboolean transpose = static_cast<GLboolean>(args_gurax.PickBool());
	const GLdouble* value = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<GLdouble>();
	// Function body
	glUniformMatrix4x3dv(location, count, transpose, value);
	return Gurax::Value::nil();
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
	frame.Assign(Gurax_CreateFunction(glAreTexturesResident_gurax));
	frame.Assign(Gurax_CreateFunction(glArrayElement_gurax));
	frame.Assign(Gurax_CreateFunction(glBegin_gurax));
	frame.Assign(Gurax_CreateFunction(glBindTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glBitmap_gurax));
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
	frame.Assign(Gurax_CreateFunction(glGetBooleanv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetClipPlane_gurax));
	frame.Assign(Gurax_CreateFunction(glGetDoublev_gurax));
	frame.Assign(Gurax_CreateFunction(glGetError_gurax));
	frame.Assign(Gurax_CreateFunction(glGetFloatv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetIntegerv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetLightfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetLightiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetMapdv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetMapfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetMapiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetMaterialfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetMaterialiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetPixelMapfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetPixelMapuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetPixelMapusv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetPolygonStipple_gurax));
	frame.Assign(Gurax_CreateFunction(glGetString_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexEnvfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexEnviv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexGendv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexGenfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexGeniv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexImage_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexLevelParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexLevelParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexParameteriv_gurax));
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
	frame.Assign(Gurax_CreateFunction(glNormalPointer_gurax));
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
	frame.Assign(Gurax_CreateFunction(glReadPixels_gurax));
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
	frame.Assign(Gurax_CreateFunction(glSelectBuffer_gurax));
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
	frame.Assign(Gurax_CreateFunction(glTexCoordPointer_gurax));
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
	frame.Assign(Gurax_CreateFunction(glTexImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glTexImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameterf_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glTexParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glTexSubImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glTexSubImage2D_gurax));
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
	frame.Assign(Gurax_CreateFunction(glVertexPointer_gurax));
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
	frame.Assign(Gurax_CreateFunction(glGetCompressedTexImage_gurax));
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
	frame.Assign(Gurax_CreateFunction(glMultiDrawElements_gurax));
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
	frame.Assign(Gurax_CreateFunction(glGetBufferParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryObjectiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryObjectuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryiv_gurax));
	frame.Assign(Gurax_CreateFunction(glIsBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glIsQuery_gurax));
	frame.Assign(Gurax_CreateFunction(glMapBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glUnmapBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glAttachShader_gurax));
	frame.Assign(Gurax_CreateFunction(glBindAttribLocation_gurax));
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
	frame.Assign(Gurax_CreateFunction(glGetActiveAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glGetActiveUniform_gurax));
	frame.Assign(Gurax_CreateFunction(glGetAttachedShaders_gurax));
	frame.Assign(Gurax_CreateFunction(glGetAttribLocation_gurax));
	frame.Assign(Gurax_CreateFunction(glGetProgramInfoLog_gurax));
	frame.Assign(Gurax_CreateFunction(glGetProgramiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetShaderInfoLog_gurax));
	frame.Assign(Gurax_CreateFunction(glGetShaderSource_gurax));
	frame.Assign(Gurax_CreateFunction(glGetShaderiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetUniformLocation_gurax));
	frame.Assign(Gurax_CreateFunction(glGetUniformfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetUniformiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexAttribdv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexAttribfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexAttribiv_gurax));
	frame.Assign(Gurax_CreateFunction(glIsProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glIsShader_gurax));
	frame.Assign(Gurax_CreateFunction(glLinkProgram_gurax));
	frame.Assign(Gurax_CreateFunction(glShaderSource_gurax));
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
	frame.Assign(Gurax_CreateFunction(glBindFragDataLocation_gurax));
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
	frame.Assign(Gurax_CreateFunction(glGetBooleani_v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetFragDataLocation_gurax));
	frame.Assign(Gurax_CreateFunction(glGetStringi_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexParameterIiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTexParameterIuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTransformFeedbackVarying_gurax));
	frame.Assign(Gurax_CreateFunction(glGetUniformuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexAttribIiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexAttribIuiv_gurax));
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
	frame.Assign(Gurax_CreateFunction(glVertexAttribIPointer_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawArraysInstanced_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsInstanced_gurax));
	frame.Assign(Gurax_CreateFunction(glPrimitiveRestartIndex_gurax));
	frame.Assign(Gurax_CreateFunction(glTexBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glGetBufferParameteri64v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetInteger64i_v_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribDivisor_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationSeparatei_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationi_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFuncSeparatei_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFunci_gurax));
	frame.Assign(Gurax_CreateFunction(glMinSampleShading_gurax));
	frame.Assign(Gurax_CreateFunction(glGetGraphicsResetStatus_gurax));
	frame.Assign(Gurax_CreateFunction(glGetnCompressedTexImage_gurax));
	frame.Assign(Gurax_CreateFunction(glGetnTexImage_gurax));
	frame.Assign(Gurax_CreateFunction(glGetnUniformdv_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiDrawArraysIndirectCount_gurax));
	frame.Assign(Gurax_CreateFunction(glMultiDrawElementsIndirectCount_gurax));
	frame.Assign(Gurax_CreateFunction(glSpecializeShader_gurax));
	frame.Assign(Gurax_CreateFunction(glClearDepthf_gurax));
	frame.Assign(Gurax_CreateFunction(glDepthRangef_gurax));
	frame.Assign(Gurax_CreateFunction(glGetShaderPrecisionFormat_gurax));
	frame.Assign(Gurax_CreateFunction(glReleaseShaderCompiler_gurax));
	frame.Assign(Gurax_CreateFunction(glShaderBinary_gurax));
	frame.Assign(Gurax_CreateFunction(glMemoryBarrierByRegion_gurax));
	frame.Assign(Gurax_CreateFunction(glPrimitiveBoundingBoxARB_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawArraysInstancedBaseInstance_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsInstancedBaseInstance_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsInstancedBaseVertexBaseInstance_gurax));
	frame.Assign(Gurax_CreateFunction(glGetImageHandleARB_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureHandleARB_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureSamplerHandleARB_gurax));
	frame.Assign(Gurax_CreateFunction(glIsImageHandleResidentARB_gurax));
	frame.Assign(Gurax_CreateFunction(glIsTextureHandleResidentARB_gurax));
	frame.Assign(Gurax_CreateFunction(glMakeImageHandleNonResidentARB_gurax));
	frame.Assign(Gurax_CreateFunction(glMakeImageHandleResidentARB_gurax));
	frame.Assign(Gurax_CreateFunction(glMakeTextureHandleNonResidentARB_gurax));
	frame.Assign(Gurax_CreateFunction(glMakeTextureHandleResidentARB_gurax));
	frame.Assign(Gurax_CreateFunction(glProgramUniformHandleui64ARB_gurax));
	frame.Assign(Gurax_CreateFunction(glProgramUniformHandleui64vARB_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformHandleui64ARB_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformHandleui64vARB_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribL1ui64ARB_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexAttribL1ui64vARB_gurax));
	frame.Assign(Gurax_CreateFunction(glBindFragDataLocationIndexed_gurax));
	frame.Assign(Gurax_CreateFunction(glGetFragDataIndex_gurax));
	frame.Assign(Gurax_CreateFunction(glBufferStorage_gurax));
	frame.Assign(Gurax_CreateFunction(glClearBufferData_gurax));
	frame.Assign(Gurax_CreateFunction(glClearBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedBufferDataEXT_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedBufferSubDataEXT_gurax));
	frame.Assign(Gurax_CreateFunction(glClearTexImage_gurax));
	frame.Assign(Gurax_CreateFunction(glClearTexSubImage_gurax));
	frame.Assign(Gurax_CreateFunction(glClipControl_gurax));
	frame.Assign(Gurax_CreateFunction(glClampColorARB_gurax));
	frame.Assign(Gurax_CreateFunction(glDispatchCompute_gurax));
	frame.Assign(Gurax_CreateFunction(glDispatchComputeIndirect_gurax));
	frame.Assign(Gurax_CreateFunction(glDispatchComputeGroupSizeARB_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyImageSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glDebugMessageControlARB_gurax));
	frame.Assign(Gurax_CreateFunction(glDebugMessageInsertARB_gurax));
	frame.Assign(Gurax_CreateFunction(glGetDebugMessageLogARB_gurax));
	frame.Assign(Gurax_CreateFunction(glBindTextureUnit_gurax));
	frame.Assign(Gurax_CreateFunction(glBlitNamedFramebuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glCheckNamedFramebufferStatus_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedBufferData_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedFramebufferfi_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedFramebufferfv_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedFramebufferiv_gurax));
	frame.Assign(Gurax_CreateFunction(glClearNamedFramebufferuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTextureSubImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTextureSubImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glCompressedTextureSubImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyNamedBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTextureSubImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTextureSubImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glCopyTextureSubImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateBuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateFramebuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateProgramPipelines_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateQueries_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateRenderbuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateSamplers_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateTextures_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateTransformFeedbacks_gurax));
	frame.Assign(Gurax_CreateFunction(glCreateVertexArrays_gurax));
	frame.Assign(Gurax_CreateFunction(glDisableVertexArrayAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glEnableVertexArrayAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glFlushMappedNamedBufferRange_gurax));
	frame.Assign(Gurax_CreateFunction(glGenerateTextureMipmap_gurax));
	frame.Assign(Gurax_CreateFunction(glGetCompressedTextureImage_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedBufferParameteri64v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedBufferParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedFramebufferAttachmentParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedFramebufferParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedRenderbufferParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryBufferObjecti64v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryBufferObjectiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryBufferObjectui64v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetQueryBufferObjectuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureImage_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureLevelParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureLevelParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureParameterIiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureParameterIuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTransformFeedbacki64_v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTransformFeedbacki_v_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTransformFeedbackiv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexArrayIndexed64iv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexArrayIndexediv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetVertexArrayiv_gurax));
	frame.Assign(Gurax_CreateFunction(glInvalidateNamedFramebufferData_gurax));
	frame.Assign(Gurax_CreateFunction(glInvalidateNamedFramebufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedBufferData_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedBufferStorage_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedBufferSubData_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferDrawBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferDrawBuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferReadBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferRenderbuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferTexture_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferTextureLayer_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedRenderbufferStorage_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedRenderbufferStorageMultisample_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureBufferRange_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureParameterIiv_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureParameterIuiv_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureParameterf_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureParameterfv_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureStorage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureStorage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureStorage2DMultisample_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureStorage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureStorage3DMultisample_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureSubImage1D_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureSubImage2D_gurax));
	frame.Assign(Gurax_CreateFunction(glTextureSubImage3D_gurax));
	frame.Assign(Gurax_CreateFunction(glTransformFeedbackBufferBase_gurax));
	frame.Assign(Gurax_CreateFunction(glTransformFeedbackBufferRange_gurax));
	frame.Assign(Gurax_CreateFunction(glUnmapNamedBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayAttribBinding_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayAttribFormat_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayAttribIFormat_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayAttribLFormat_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayBindingDivisor_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayElementBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayVertexBuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glVertexArrayVertexBuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawBuffersARB_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationSeparateiARB_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendEquationiARB_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFuncSeparateiARB_gurax));
	frame.Assign(Gurax_CreateFunction(glBlendFunciARB_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsBaseVertex_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsInstancedBaseVertex_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawRangeElementsBaseVertex_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawArraysIndirect_gurax));
	frame.Assign(Gurax_CreateFunction(glDrawElementsIndirect_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glGetFramebufferParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetNamedFramebufferParameterivEXT_gurax));
	frame.Assign(Gurax_CreateFunction(glNamedFramebufferParameteriEXT_gurax));
	frame.Assign(Gurax_CreateFunction(glBindFramebuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glBindRenderbuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glBlitFramebuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glCheckFramebufferStatus_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteFramebuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glDeleteRenderbuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferRenderbuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTexture1D_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTexture2D_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTexture3D_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTextureLayer_gurax));
	frame.Assign(Gurax_CreateFunction(glGenFramebuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glGenRenderbuffers_gurax));
	frame.Assign(Gurax_CreateFunction(glGenerateMipmap_gurax));
	frame.Assign(Gurax_CreateFunction(glGetFramebufferAttachmentParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glGetRenderbufferParameteriv_gurax));
	frame.Assign(Gurax_CreateFunction(glIsFramebuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glIsRenderbuffer_gurax));
	frame.Assign(Gurax_CreateFunction(glRenderbufferStorage_gurax));
	frame.Assign(Gurax_CreateFunction(glRenderbufferStorageMultisample_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTextureARB_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTextureFaceARB_gurax));
	frame.Assign(Gurax_CreateFunction(glFramebufferTextureLayerARB_gurax));
	frame.Assign(Gurax_CreateFunction(glProgramParameteriARB_gurax));
	frame.Assign(Gurax_CreateFunction(glProgramBinary_gurax));
	frame.Assign(Gurax_CreateFunction(glProgramParameteri_gurax));
	frame.Assign(Gurax_CreateFunction(glGetCompressedTextureSubImage_gurax));
	frame.Assign(Gurax_CreateFunction(glGetTextureSubImage_gurax));
	frame.Assign(Gurax_CreateFunction(glSpecializeShaderARB_gurax));
	frame.Assign(Gurax_CreateFunction(glGetUniformdv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1d_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform1dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2d_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3d_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4d_gurax));
	frame.Assign(Gurax_CreateFunction(glUniform4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix2x3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix2x4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix3dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix3x2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix3x4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix4dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix4x2dv_gurax));
	frame.Assign(Gurax_CreateFunction(glUniformMatrix4x3dv_gurax));
}

Gurax_EndModuleScope(opengl)
