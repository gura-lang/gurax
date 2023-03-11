//==============================================================================
// VType_cairo_matrix_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_matrix_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_matrix_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_matrix_t, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// cairo_matrix_t(xx?:Number, yx?:Number, xy?:Number, yy?:Number, x0?:Number, y0?:Number) {block?}
Gurax_DeclareConstructor(cairo_matrix_t)
{
	Declare(VTYPE_cairo_matrix_t, Flag::None);
	DeclareArg("xx", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("yx", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("xy", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("yy", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x0", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y0", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `cairo_matrix_t` instance.
)""");
}

Gurax_ImplementConstructor(cairo_matrix_t)
{
	// Arguments
	ArgPicker args(argument);
	cairo_matrix_t matrix;
	matrix.xx = args.IsValid()? args.PickNumber<double>() : 0;
	matrix.yx = args.IsValid()? args.PickNumber<double>() : 0;
	matrix.xy = args.IsValid()? args.PickNumber<double>() : 0;
	matrix.yy = args.IsValid()? args.PickNumber<double>() : 0;
	matrix.x0 = args.IsValid()? args.PickNumber<double>() : 0;
	matrix.y0 = args.IsValid()? args.PickNumber<double>() : 0;
	// Function body
	return argument.ReturnValue(processor, new Value_cairo_matrix_t(matrix));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_matrix_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_matrix_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(cairo_matrix_t, MethodSkeleton)
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
// cairo.cairo_matrix_t#xx
Gurax_DeclareProperty_RW(cairo_matrix_t, xx)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_matrix_t, xx)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().xx);
}

Gurax_ImplementPropertySetter(cairo_matrix_t, xx)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().xx = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_matrix_t#yx
Gurax_DeclareProperty_RW(cairo_matrix_t, yx)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_matrix_t, yx)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().yx);
}

Gurax_ImplementPropertySetter(cairo_matrix_t, yx)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().yx = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_matrix_t#xy
Gurax_DeclareProperty_RW(cairo_matrix_t, xy)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_matrix_t, xy)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().xy);
}

Gurax_ImplementPropertySetter(cairo_matrix_t, xy)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().xy = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_matrix_t#yy
Gurax_DeclareProperty_RW(cairo_matrix_t, yy)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_matrix_t, yy)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().yy);
}

Gurax_ImplementPropertySetter(cairo_matrix_t, yy)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().yy = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_matrix_t#x0
Gurax_DeclareProperty_RW(cairo_matrix_t, x0)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_matrix_t, x0)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x0);
}

Gurax_ImplementPropertySetter(cairo_matrix_t, x0)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x0 = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_matrix_t#y0
Gurax_DeclareProperty_RW(cairo_matrix_t, y0)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_matrix_t, y0)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y0);
}

Gurax_ImplementPropertySetter(cairo_matrix_t, y0)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y0 = Value_Number::GetNumber<double>(value);
}

//------------------------------------------------------------------------------
// VType_cairo_matrix_t
//------------------------------------------------------------------------------
VType_cairo_matrix_t VTYPE_cairo_matrix_t("cairo_matrix_t");

void VType_cairo_matrix_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(cairo_matrix_t));
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_matrix_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_matrix_t, xx));
	Assign(Gurax_CreateProperty(cairo_matrix_t, yx));
	Assign(Gurax_CreateProperty(cairo_matrix_t, xy));
	Assign(Gurax_CreateProperty(cairo_matrix_t, yy));
	Assign(Gurax_CreateProperty(cairo_matrix_t, x0));
	Assign(Gurax_CreateProperty(cairo_matrix_t, y0));
}

//------------------------------------------------------------------------------
// Value_cairo_matrix_t
//------------------------------------------------------------------------------
VType& Value_cairo_matrix_t::vtype = VTYPE_cairo_matrix_t;

String Value_cairo_matrix_t::ToString(const StringStyle& ss) const
{
	const cairo_matrix_t& matrix = GetEntity();
	return ToStringGeneric(ss, String().Format("cairo.cairo_matrix_t:xx=%g,yx=%g,xy=%g,yy=%g,x0=%g,y0=%g",
			matrix.xx, matrix.yx, matrix.xy, matrix.yy, matrix.x0, matrix.y0));
}

Gurax_EndModuleScope(cairo)
