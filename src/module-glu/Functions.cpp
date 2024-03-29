﻿//==============================================================================
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

// glu.gluPickMatrix(x as Number, y as Number, width as Number, height as Number, viewport[] as Number)
Gurax_DeclareFunctionAlias(gluPickMatrix_gurax, "gluPickMatrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("viewport", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(gluPickMatrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble width = args_gurax.PickNumber<GLdouble>();
	GLdouble height = args_gurax.PickNumber<GLdouble>();
	auto viewport = args_gurax.PickNumList<GLint>();
	// Function body
	if (viewport.size() != 4) {
		Error::Issue(ErrorType::RangeError, "the argument viewport must be a list of four elements");
		return Value::nil();
	}
	gluPickMatrix(x, y, width, height, const_cast<GLint*>(viewport.data()));
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

// glu.gluScaleImage(format as Number, widthin as Number, heightin as Number, typein as Number, datain as Pointer, widthout as Number, heightout as Number, typeout as Number, dataout as Pointer)
Gurax_DeclareFunctionAlias(gluScaleImage_gurax, "gluScaleImage")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("widthin", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("heightin", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("typein", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("datain", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("widthout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("heightout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("typeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dataout", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluScaleImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLint widthin = args_gurax.PickNumber<GLint>();
	GLint heightin = args_gurax.PickNumber<GLint>();
	GLenum typein = args_gurax.PickNumber<GLenum>();
	const void* datain = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	GLint widthout = args_gurax.PickNumber<GLint>();
	GLint heightout = args_gurax.PickNumber<GLint>();
	GLenum typeout = args_gurax.PickNumber<GLenum>();
	void* dataout = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!dataout) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	int rtn = gluScaleImage(format, widthin, heightin, typein, datain, widthout, heightout, typeout, dataout);
	return new Gurax::Value_Number(rtn);
}

// glu.gluBuild1DMipmaps(target as Number, components as Number, width as Number, format as Number, type as Number, data as Pointer)
Gurax_DeclareFunctionAlias(gluBuild1DMipmaps_gurax, "gluBuild1DMipmaps")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("components", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluBuild1DMipmaps_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint components = args_gurax.PickNumber<GLint>();
	GLint width = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	// Function body
	int rtn = gluBuild1DMipmaps(target, components, width, format, type, data);
	return new Gurax::Value_Number(rtn);
}

// glu.gluBuild2DMipmaps(target as Number, components as Number, width as Number, height as Number, format as Number, type as Number, data as Pointer)
Gurax_DeclareFunctionAlias(gluBuild2DMipmaps_gurax, "gluBuild2DMipmaps")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("target", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("components", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluBuild2DMipmaps_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum target = args_gurax.PickNumber<GLenum>();
	GLint components = args_gurax.PickNumber<GLint>();
	GLint width = args_gurax.PickNumber<GLint>();
	GLint height = args_gurax.PickNumber<GLint>();
	GLenum format = args_gurax.PickNumber<GLenum>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	// Function body
	int rtn = gluBuild2DMipmaps(target, components, width, height, format, type, data);
	return new Gurax::Value_Number(rtn);
}

// glu.gluNewQuadric()
Gurax_DeclareFunctionAlias(gluNewQuadric_gurax, "gluNewQuadric")
{
	Declare(VTYPE_GLUquadric, Flag::None);
}

Gurax_ImplementFunctionEx(gluNewQuadric_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLUquadric* rtn = gluNewQuadric();
	if (!rtn) return Value::nil();
	return new Value_GLUquadric(rtn);
}

// glu.gluDeleteQuadric(quadObject as GLUquadric)
Gurax_DeclareFunctionAlias(gluDeleteQuadric_gurax, "gluDeleteQuadric")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluDeleteQuadric_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	// Function body
	gluDeleteQuadric(quadObject);
	return Gurax::Value::nil();
}

// glu.gluQuadricNormals(quadObject as GLUquadric, normals as Number)
Gurax_DeclareFunctionAlias(gluQuadricNormals_gurax, "gluQuadricNormals")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("normals", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluQuadricNormals_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLenum normals = args_gurax.PickNumber<GLenum>();
	// Function body
	gluQuadricNormals(quadObject, normals);
	return Gurax::Value::nil();
}

// glu.gluQuadricTexture(quadObject as GLUquadric, textureCoords as Bool)
Gurax_DeclareFunctionAlias(gluQuadricTexture_gurax, "gluQuadricTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("textureCoords", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluQuadricTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLboolean textureCoords = static_cast<GLboolean>(args_gurax.PickBool());
	// Function body
	gluQuadricTexture(quadObject, textureCoords);
	return Gurax::Value::nil();
}

// glu.gluQuadricOrientation(quadObject as GLUquadric, orientation as Number)
Gurax_DeclareFunctionAlias(gluQuadricOrientation_gurax, "gluQuadricOrientation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("orientation", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluQuadricOrientation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLenum orientation = args_gurax.PickNumber<GLenum>();
	// Function body
	gluQuadricOrientation(quadObject, orientation);
	return Gurax::Value::nil();
}

// glu.gluQuadricDrawStyle(quadObject as GLUquadric, drawStyle as Number)
Gurax_DeclareFunctionAlias(gluQuadricDrawStyle_gurax, "gluQuadricDrawStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("drawStyle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluQuadricDrawStyle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLenum drawStyle = args_gurax.PickNumber<GLenum>();
	// Function body
	gluQuadricDrawStyle(quadObject, drawStyle);
	return Gurax::Value::nil();
}

// glu.gluCylinder(quadObject as GLUquadric, baseRadius as Number, topRadius as Number, height as Number, slices as Number, stacks as Number)
Gurax_DeclareFunctionAlias(gluCylinder_gurax, "gluCylinder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("baseRadius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("topRadius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slices", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stacks", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluCylinder_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLdouble baseRadius = args_gurax.PickNumber<GLdouble>();
	GLdouble topRadius = args_gurax.PickNumber<GLdouble>();
	GLdouble height = args_gurax.PickNumber<GLdouble>();
	GLint slices = args_gurax.PickNumber<GLint>();
	GLint stacks = args_gurax.PickNumber<GLint>();
	// Function body
	gluCylinder(quadObject, baseRadius, topRadius, height, slices, stacks);
	return Gurax::Value::nil();
}

// glu.gluDisk(quadObject as GLUquadric, innerRadius as Number, outerRadius as Number, slices as Number, loops as Number)
Gurax_DeclareFunctionAlias(gluDisk_gurax, "gluDisk")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("innerRadius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("outerRadius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slices", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluDisk_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLdouble innerRadius = args_gurax.PickNumber<GLdouble>();
	GLdouble outerRadius = args_gurax.PickNumber<GLdouble>();
	GLint slices = args_gurax.PickNumber<GLint>();
	GLint loops = args_gurax.PickNumber<GLint>();
	// Function body
	gluDisk(quadObject, innerRadius, outerRadius, slices, loops);
	return Gurax::Value::nil();
}

// glu.gluPartialDisk(quadObject as GLUquadric, innerRadius as Number, outerRadius as Number, slices as Number, loops as Number, startAngle as Number, sweepAngle as Number)
Gurax_DeclareFunctionAlias(gluPartialDisk_gurax, "gluPartialDisk")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("innerRadius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("outerRadius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slices", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("startAngle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sweepAngle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluPartialDisk_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLdouble innerRadius = args_gurax.PickNumber<GLdouble>();
	GLdouble outerRadius = args_gurax.PickNumber<GLdouble>();
	GLint slices = args_gurax.PickNumber<GLint>();
	GLint loops = args_gurax.PickNumber<GLint>();
	GLdouble startAngle = args_gurax.PickNumber<GLdouble>();
	GLdouble sweepAngle = args_gurax.PickNumber<GLdouble>();
	// Function body
	gluPartialDisk(quadObject, innerRadius, outerRadius, slices, loops, startAngle, sweepAngle);
	return Gurax::Value::nil();
}

// glu.gluSphere(quadObject as GLUquadric, radius as Number, slices as Number, stacks as Number)
Gurax_DeclareFunctionAlias(gluSphere_gurax, "gluSphere")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("quadObject", VTYPE_GLUquadric, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slices", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stacks", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluSphere_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_quadObject = args_gurax.Pick<Value_GLUquadric>();
	GLUquadric* quadObject = value_quadObject.GetEntityPtr();
	GLdouble radius = args_gurax.PickNumber<GLdouble>();
	GLint slices = args_gurax.PickNumber<GLint>();
	GLint stacks = args_gurax.PickNumber<GLint>();
	// Function body
	gluSphere(quadObject, radius, slices, stacks);
	return Gurax::Value::nil();
}

// glu.gluNewTess()
Gurax_DeclareFunctionAlias(gluNewTess_gurax, "gluNewTess")
{
	Declare(VTYPE_GLUtesselator, Flag::None);
}

Gurax_ImplementFunctionEx(gluNewTess_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLUtesselator* rtn = gluNewTess();
	if (!rtn) return Value::nil();
	return new Value_GLUtesselator(rtn);
}

// glu.gluDeleteTess(tess as GLUtesselator)
Gurax_DeclareFunctionAlias(gluDeleteTess_gurax, "gluDeleteTess")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluDeleteTess_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	// Function body
	gluDeleteTess(tess);
	return Gurax::Value::nil();
}

// glu.gluTessBeginPolygon(tess as GLUtesselator, polygon_data as Pointer)
Gurax_DeclareFunctionAlias(gluTessBeginPolygon_gurax, "gluTessBeginPolygon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
	DeclareArg("polygon_data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluTessBeginPolygon_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	void* polygon_data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!polygon_data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	gluTessBeginPolygon(tess, polygon_data);
	return Gurax::Value::nil();
}

// glu.gluTessBeginContour(tess as GLUtesselator)
Gurax_DeclareFunctionAlias(gluTessBeginContour_gurax, "gluTessBeginContour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluTessBeginContour_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	// Function body
	gluTessBeginContour(tess);
	return Gurax::Value::nil();
}

// glu.gluTessEndContour(tess as GLUtesselator)
Gurax_DeclareFunctionAlias(gluTessEndContour_gurax, "gluTessEndContour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluTessEndContour_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	// Function body
	gluTessEndContour(tess);
	return Gurax::Value::nil();
}

// glu.gluTessEndPolygon(tess as GLUtesselator)
Gurax_DeclareFunctionAlias(gluTessEndPolygon_gurax, "gluTessEndPolygon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluTessEndPolygon_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	// Function body
	gluTessEndPolygon(tess);
	return Gurax::Value::nil();
}

// glu.gluTessProperty(tess as GLUtesselator, which as Number, value as Number)
Gurax_DeclareFunctionAlias(gluTessProperty_gurax, "gluTessProperty")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
	DeclareArg("which", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluTessProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	GLenum which = args_gurax.PickNumber<GLenum>();
	GLdouble value = args_gurax.PickNumber<GLdouble>();
	// Function body
	gluTessProperty(tess, which, value);
	return Gurax::Value::nil();
}

// glu.gluTessNormal(tess as GLUtesselator, x as Number, y as Number, z as Number)
Gurax_DeclareFunctionAlias(gluTessNormal_gurax, "gluTessNormal")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluTessNormal_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	GLdouble x = args_gurax.PickNumber<GLdouble>();
	GLdouble y = args_gurax.PickNumber<GLdouble>();
	GLdouble z = args_gurax.PickNumber<GLdouble>();
	// Function body
	gluTessNormal(tess, x, y, z);
	return Gurax::Value::nil();
}

// glu.gluGetTessProperty(tess as GLUtesselator, which as Number, value as Pointer)
Gurax_DeclareFunctionAlias(gluGetTessProperty_gurax, "gluGetTessProperty")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tess", VTYPE_GLUtesselator, ArgOccur::Once, ArgFlag::None);
	DeclareArg("which", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluGetTessProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_tess = args_gurax.Pick<Value_GLUtesselator>();
	GLUtesselator* tess = value_tess.GetEntityPtr();
	GLenum which = args_gurax.PickNumber<GLenum>();
	GLdouble* value = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<GLdouble>();
	if (!value) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	gluGetTessProperty(tess, which, value);
	return Gurax::Value::nil();
}

// glu.gluNewNurbsRenderer()
Gurax_DeclareFunctionAlias(gluNewNurbsRenderer_gurax, "gluNewNurbsRenderer")
{
	Declare(VTYPE_GLUnurbs, Flag::None);
}

Gurax_ImplementFunctionEx(gluNewNurbsRenderer_gurax, processor_gurax, argument_gurax)
{
	// Function body
	GLUnurbs* rtn = gluNewNurbsRenderer();
	if (!rtn) return Value::nil();
	return new Value_GLUnurbs(rtn);
}

// glu.gluDeleteNurbsRenderer(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluDeleteNurbsRenderer_gurax, "gluDeleteNurbsRenderer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluDeleteNurbsRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluDeleteNurbsRenderer(nobj);
	return Gurax::Value::nil();
}

// glu.gluBeginSurface(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluBeginSurface_gurax, "gluBeginSurface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluBeginSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluBeginSurface(nobj);
	return Gurax::Value::nil();
}

// glu.gluBeginCurve(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluBeginCurve_gurax, "gluBeginCurve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluBeginCurve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluBeginCurve(nobj);
	return Gurax::Value::nil();
}

// glu.gluEndCurve(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluEndCurve_gurax, "gluEndCurve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluEndCurve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluEndCurve(nobj);
	return Gurax::Value::nil();
}

// glu.gluEndSurface(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluEndSurface_gurax, "gluEndSurface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluEndSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluEndSurface(nobj);
	return Gurax::Value::nil();
}

// glu.gluBeginTrim(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluBeginTrim_gurax, "gluBeginTrim")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluBeginTrim_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluBeginTrim(nobj);
	return Gurax::Value::nil();
}

// glu.gluEndTrim(nobj as GLUnurbs)
Gurax_DeclareFunctionAlias(gluEndTrim_gurax, "gluEndTrim")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluEndTrim_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	// Function body
	gluEndTrim(nobj);
	return Gurax::Value::nil();
}

// glu.gluPwlCurve(nobj as GLUnurbs, array[] as Number, stride as Number, type as Number)
Gurax_DeclareFunctionAlias(gluPwlCurve_gurax, "gluPwlCurve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
	DeclareArg("array", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluPwlCurve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	auto array = args_gurax.PickNumList<GLfloat>();
	GLint stride = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	// Function body
	gluPwlCurve(nobj, array.sizeT<GLint>(), const_cast<GLfloat*>(array.data()), stride, type);
	return Value::nil();
}

// glu.gluNurbsCurve(nobj as GLUnurbs, knot[] as Number, stride as Number, ctlarray[] as Number, order as Number, type as Number)
Gurax_DeclareFunctionAlias(gluNurbsCurve_gurax, "gluNurbsCurve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
	DeclareArg("knot", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ctlarray", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluNurbsCurve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	auto knot = args_gurax.PickNumList<GLfloat>();
	GLint stride = args_gurax.PickNumber<GLint>();
	auto ctlarray = args_gurax.PickNumList<GLfloat>();
	GLint order = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	// Function body
	gluNurbsCurve(nobj, knot.sizeT<GLint>(), const_cast<GLfloat*>(knot.data()), stride,
		const_cast<GLfloat*>(ctlarray.data()), order, type);
	return Value::nil();
}

// glu.gluNurbsSurface(nobj as GLUnurbs, sknot[] as Number, tknot[] as Number, s_stride as Number, t_stride as Number, ctlarray[] as Number, sorder as Number, torder as Number, type as Number)
Gurax_DeclareFunctionAlias(gluNurbsSurface_gurax, "gluNurbsSurface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sknot", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("tknot", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("s_stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("t_stride", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ctlarray", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("sorder", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("torder", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluNurbsSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	auto sknot = args_gurax.PickNumList<float>();
	auto tknot = args_gurax.PickNumList<GLfloat>();
	GLint s_stride = args_gurax.PickNumber<GLint>();
	GLint t_stride = args_gurax.PickNumber<GLint>();
	auto ctlarray = args_gurax.PickNumList<GLfloat>();
	GLint sorder = args_gurax.PickNumber<GLint>();
	GLint torder = args_gurax.PickNumber<GLint>();
	GLenum type = args_gurax.PickNumber<GLenum>();
	// Function body
	gluNurbsSurface(nobj, sknot.sizeT<GLint>(), const_cast<GLfloat*>(sknot.data()),
		tknot.sizeT<GLint>(), const_cast<GLfloat*>(tknot.data()),
		s_stride, t_stride, const_cast<GLfloat*>(ctlarray.data()), sorder, torder, type);
	return Value::nil();
}

// glu.gluNurbsProperty(nobj as GLUnurbs, property as Number, value as Number)
Gurax_DeclareFunctionAlias(gluNurbsProperty_gurax, "gluNurbsProperty")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
	DeclareArg("property", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluNurbsProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	GLenum property = args_gurax.PickNumber<GLenum>();
	GLfloat value = args_gurax.PickNumber<GLfloat>();
	// Function body
	gluNurbsProperty(nobj, property, value);
	return Gurax::Value::nil();
}

// glu.gluGetNurbsProperty(nobj as GLUnurbs, property as Number, value as Pointer)
Gurax_DeclareFunctionAlias(gluGetNurbsProperty_gurax, "gluGetNurbsProperty")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("nobj", VTYPE_GLUnurbs, ArgOccur::Once, ArgFlag::None);
	DeclareArg("property", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluGetNurbsProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_nobj = args_gurax.Pick<Value_GLUnurbs>();
	GLUnurbs* nobj = value_nobj.GetEntityPtr();
	GLenum property = args_gurax.PickNumber<GLenum>();
	GLfloat* value = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<GLfloat>();
	if (!value) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	gluGetNurbsProperty(nobj, property, value);
	return Gurax::Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(gluErrorString_gurax));
	frame.Assign(Gurax_CreateFunction(gluGetString_gurax));
	frame.Assign(Gurax_CreateFunction(gluOrtho2D_gurax));
	frame.Assign(Gurax_CreateFunction(gluPerspective_gurax));
	frame.Assign(Gurax_CreateFunction(gluPickMatrix_gurax));
	frame.Assign(Gurax_CreateFunction(gluLookAt_gurax));
	frame.Assign(Gurax_CreateFunction(gluScaleImage_gurax));
	frame.Assign(Gurax_CreateFunction(gluBuild1DMipmaps_gurax));
	frame.Assign(Gurax_CreateFunction(gluBuild2DMipmaps_gurax));
	frame.Assign(Gurax_CreateFunction(gluNewQuadric_gurax));
	frame.Assign(Gurax_CreateFunction(gluDeleteQuadric_gurax));
	frame.Assign(Gurax_CreateFunction(gluQuadricNormals_gurax));
	frame.Assign(Gurax_CreateFunction(gluQuadricTexture_gurax));
	frame.Assign(Gurax_CreateFunction(gluQuadricOrientation_gurax));
	frame.Assign(Gurax_CreateFunction(gluQuadricDrawStyle_gurax));
	frame.Assign(Gurax_CreateFunction(gluCylinder_gurax));
	frame.Assign(Gurax_CreateFunction(gluDisk_gurax));
	frame.Assign(Gurax_CreateFunction(gluPartialDisk_gurax));
	frame.Assign(Gurax_CreateFunction(gluSphere_gurax));
	frame.Assign(Gurax_CreateFunction(gluNewTess_gurax));
	frame.Assign(Gurax_CreateFunction(gluDeleteTess_gurax));
	frame.Assign(Gurax_CreateFunction(gluTessBeginPolygon_gurax));
	frame.Assign(Gurax_CreateFunction(gluTessBeginContour_gurax));
	frame.Assign(Gurax_CreateFunction(gluTessEndContour_gurax));
	frame.Assign(Gurax_CreateFunction(gluTessEndPolygon_gurax));
	frame.Assign(Gurax_CreateFunction(gluTessProperty_gurax));
	frame.Assign(Gurax_CreateFunction(gluTessNormal_gurax));
	frame.Assign(Gurax_CreateFunction(gluGetTessProperty_gurax));
	frame.Assign(Gurax_CreateFunction(gluNewNurbsRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(gluDeleteNurbsRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(gluBeginSurface_gurax));
	frame.Assign(Gurax_CreateFunction(gluBeginCurve_gurax));
	frame.Assign(Gurax_CreateFunction(gluEndCurve_gurax));
	frame.Assign(Gurax_CreateFunction(gluEndSurface_gurax));
	frame.Assign(Gurax_CreateFunction(gluBeginTrim_gurax));
	frame.Assign(Gurax_CreateFunction(gluEndTrim_gurax));
	frame.Assign(Gurax_CreateFunction(gluPwlCurve_gurax));
	frame.Assign(Gurax_CreateFunction(gluNurbsCurve_gurax));
	frame.Assign(Gurax_CreateFunction(gluNurbsSurface_gurax));
	frame.Assign(Gurax_CreateFunction(gluNurbsProperty_gurax));
	frame.Assign(Gurax_CreateFunction(gluGetNurbsProperty_gurax));
}

Gurax_EndModuleScope(glu)
