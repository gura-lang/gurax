//==============================================================================
// VType_Segment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// jpeg.Segment() {block?}
Gurax_DeclareConstructor(Segment)
{
	Declare(VTYPE_Segment, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.Segment` instance.");
}

Gurax_ImplementConstructor(Segment)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Segment> pSegment(new Segment());
	return argument.ReturnValue(processor, new Value_Segment(pSegment.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.Segment#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Segment, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Segment, MethodSkeleton)
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
// jpeg.Segment#propSkeleton
Gurax_DeclareProperty_R(Segment, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Segment, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Segment
//------------------------------------------------------------------------------
VType_Segment VTYPE_Segment("Segment");

void VType_Segment::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Segment));
	// Assignment of method
	Assign(Gurax_CreateMethod(Segment, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Segment, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Segment
//------------------------------------------------------------------------------
VType& Value_Segment::vtype = VTYPE_Segment;

Gurax_EndModuleScope(jpeg)
