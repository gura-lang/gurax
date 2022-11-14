//==============================================================================
// VType_cairo_rectangle_int_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_rectangle_int_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_rectangle_int_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_rectangle_int_t, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// cairo_rectangle_int_t(x?:Number, y?:Number, width?:Number, height?:Number) {block?}
Gurax_DeclareConstructor(cairo_rectangle_int_t)
{
	Declare(VTYPE_cairo_rectangle_int_t, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `cairo_rectangle_int_t` instance.
)**");
}

Gurax_ImplementConstructor(cairo_rectangle_int_t)
{
	// Arguments
	ArgPicker args(argument);
	cairo_rectangle_int_t rectangle;
	rectangle.x = args.IsValid()? args.PickNumber<int>() : 0;
	rectangle.y = args.IsValid()? args.PickNumber<int>() : 0;
	rectangle.width = args.IsValid()? args.PickNumber<int>() : 0;
	rectangle.height = args.IsValid()? args.PickNumber<int>() : 0;
	// Function body
	return argument.ReturnValue(processor, new Value_cairo_rectangle_int_t(rectangle));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_rectangle_int_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_rectangle_int_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(cairo_rectangle_int_t, MethodSkeleton)
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
// cairo.cairo_rectangle_int_t#propSkeleton
Gurax_DeclareProperty_R(cairo_rectangle_int_t, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_rectangle_int_t, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_cairo_rectangle_int_t
//------------------------------------------------------------------------------
VType_cairo_rectangle_int_t VTYPE_cairo_rectangle_int_t("cairo_rectangle_int_t");

void VType_cairo_rectangle_int_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(cairo_rectangle_int_t));
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_rectangle_int_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_rectangle_int_t, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_cairo_rectangle_int_t
//------------------------------------------------------------------------------
VType& Value_cairo_rectangle_int_t::vtype = VTYPE_cairo_rectangle_int_t;

String Value_cairo_rectangle_int_t::ToString(const StringStyle& ss) const
{
	const cairo_rectangle_int_t& rectangle = GetEntity();
	return ToStringGeneric(ss, String().Format("cairo.cairo_rectangle_int_t:x=%d,y=%d,width=%d,height=%d",
			rectangle.x, rectangle.y, rectangle.width, rectangle.height));
}

Gurax_EndModuleScope(cairo)
