//==============================================================================
// VType_Point.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Point, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Point, `en)}

${help.ComposeMethodHelp(model.obj.Point, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Point() {block?}
Gurax_DeclareConstructor(Point)
{
	Declare(VTYPE_Point, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.obj.Point` instance.
)**");
}

Gurax_ImplementConstructor(Point)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Point> pPoint(new Point());
	return argument.ReturnValue(processor, new Value_Point(pPoint.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Point#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Point, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Point, MethodSkeleton)
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
// model.obj.Point#propSkeleton
Gurax_DeclareProperty_R(Point, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Point, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Point
//------------------------------------------------------------------------------
VType_Point VTYPE_Point("Point");

void VType_Point::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Point));
	// Assignment of method
	Assign(Gurax_CreateMethod(Point, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Point, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Point
//------------------------------------------------------------------------------
VType& Value_Point::vtype = VTYPE_Point;

String Value_Point::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPoint().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
