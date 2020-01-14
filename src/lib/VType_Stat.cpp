//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
// Stat() {block?}
Gurax_DeclareConstructor(Stat)
{
	Declare(VTYPE_Stat, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Stat` instance.");
}

Gurax_ImplementConstructor(Stat)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Stat> pStat(new Stat());
	return argument.ReturnValue(processor, new Value_Stat(pStat.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Stat#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Stat, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Stat, MethodSkeleton)
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
// Stat#propSkeleton
Gurax_DeclareProperty_R(Stat, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Stat, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Stat
//------------------------------------------------------------------------------
VType_Stat VTYPE_Stat("Stat");

void VType_Stat::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Stat));
	// Assignment of method
	Assign(Gurax_CreateMethod(Stat, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Stat, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Stat
//------------------------------------------------------------------------------
VType& Value_Stat::vtype = VTYPE_Stat;

}