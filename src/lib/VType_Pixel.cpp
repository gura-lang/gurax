//==============================================================================
// VType_Pixel.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Pixel, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Pixel, `en)}

${help.ComposeMethodHelp(Pixel, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Pixel() {block?}
Gurax_DeclareConstructor(Pixel)
{
	Declare(VTYPE_Pixel, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Pixel` instance.
)**");
}

Gurax_ImplementConstructor(Pixel)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Pixel> pPixel(new Pixel(Color::black, 0, 0));
	return argument.ReturnValue(processor, new Value_Pixel(pPixel.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Pixel#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Pixel, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Pixel, MethodSkeleton)
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
// Pixel#color
Gurax_DeclareProperty_R(Pixel, color)
{
	Declare(VTYPE_Color, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
X-position.
)**");
}

Gurax_ImplementPropertyGetter(Pixel, color)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Color(valueThis.GetPixel().GetColor());
}

// Pixel#x
Gurax_DeclareProperty_R(Pixel, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
X-position.
)**");
}

Gurax_ImplementPropertyGetter(Pixel, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPixel().GetX());
}

// Pixel#y
Gurax_DeclareProperty_R(Pixel, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Y-position.
)**");
}

Gurax_ImplementPropertyGetter(Pixel, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPixel().GetY());
}

//------------------------------------------------------------------------------
// VType_Pixel
//------------------------------------------------------------------------------
VType_Pixel VTYPE_Pixel("Pixel");

void VType_Pixel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Pixel));
	// Assignment of method
	Assign(Gurax_CreateMethod(Pixel, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Pixel, color));
	Assign(Gurax_CreateProperty(Pixel, x));
	Assign(Gurax_CreateProperty(Pixel, y));
}

//------------------------------------------------------------------------------
// Value_Pixel
//------------------------------------------------------------------------------
VType& Value_Pixel::vtype = VTYPE_Pixel;

String Value_Pixel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPixel().ToString(ss));
}

}
