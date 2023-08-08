//==============================================================================
// VType_ImageSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.ImageSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.ImageSet, `en)}

${help.ComposeMethodHelp(ml.cifar.ImageSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.cifar.ImageSet() {block?}
Gurax_DeclareConstructor(ImageSet)
{
	Declare(VTYPE_ImageSet, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.cifar.ImageSet` instance.
)""");
}

Gurax_ImplementConstructor(ImageSet)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<ImageSet> pImageSet(new ImageSet());
	return argument.ReturnValue(processor, new Value_ImageSet(pImageSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.cifar.ImageSet#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(ImageSet, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(ImageSet, MethodSkeleton)
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

//------------------------------------------------------------------------------
// VType_ImageSet
//------------------------------------------------------------------------------
VType_ImageSet VTYPE_ImageSet("ImageSet");

void VType_ImageSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(ImageSet));
	// Assignment of method
	Assign(Gurax_CreateMethod(ImageSet, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(ImageSet, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_ImageSet
//------------------------------------------------------------------------------
VType& Value_ImageSet::vtype = VTYPE_ImageSet;

String Value_ImageSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetImageSet().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
