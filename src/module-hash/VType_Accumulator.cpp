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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// hash.Accumulator#Initialize()
Gurax_DeclareMethod(Accumulator, Initialize)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Accumulator, Initialize)
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

// hash.Accumulator#Update()
Gurax_DeclareMethod(Accumulator, Update)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Accumulator, Update)
{
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// hash.Accumulator#digest
Gurax_DeclareProperty_R(Accumulator, digest)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Accumulator, digest)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// hash.Accumulator#digestHex
Gurax_DeclareProperty_R(Accumulator, digestHex)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Accumulator, digestHex)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// hash.Accumulator#number
Gurax_DeclareProperty_R(Accumulator, number)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Accumulator, number)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetAccumulator().GetValue();
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
	Declare(VTYPE_Stream, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Accumulator, Initialize));
	Assign(Gurax_CreateMethod(Accumulator, Update));
	// Assignment of property
	Assign(Gurax_CreateProperty(Accumulator, digest));
	Assign(Gurax_CreateProperty(Accumulator, digestHex));
	Assign(Gurax_CreateProperty(Accumulator, number));
}

//------------------------------------------------------------------------------
// Value_Accumulator
//------------------------------------------------------------------------------
VType& Value_Accumulator::vtype = VTYPE_Accumulator;

Gurax_EndModuleScope(hash)
