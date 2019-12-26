//==============================================================================
// VType_Accumulator.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(hash)

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
// hash.Accumulator() {block?}
Gurax_DeclareConstructor(Accumulator)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Accumulator` instance.");
}

Gurax_ImplementConstructor(Accumulator)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator());
	return argument.ReturnValue(processor, new Value_Accumulator(pAccumulator.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// hash.Accumulator#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Accumulator, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Accumulator, MethodSkeleton)
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
// hash.Accumulator#propSkeleton
Gurax_DeclareProperty_R(Accumulator, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Accumulator, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Accumulator
//------------------------------------------------------------------------------
VType_Accumulator VTYPE_Accumulator("Accumulator");

void VType_Accumulator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Accumulator));
	// Assignment of method
	Assign(Gurax_CreateMethod(Accumulator, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Accumulator, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Accumulator
//------------------------------------------------------------------------------
VType& Value_Accumulator::vtype = VTYPE_Accumulator;

Gurax_EndModuleScope(hash)
