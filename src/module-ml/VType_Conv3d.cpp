//==============================================================================
// VType_Conv3d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Conv3d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Conv3d, `en)}

${help.ComposeMethodHelp(ml.Conv3d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Conv3d() {block?}
Gurax_DeclareConstructor(Conv3d)
{
	Declare(VTYPE_Conv3d, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Conv3d` instance.
)""");
}

Gurax_ImplementConstructor(Conv3d)
{
	// Function body
	RefPtr<Conv3d> pConv3d(new Conv3d());
	return argument.ReturnValue(processor, new Value_Conv3d(pConv3d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Conv3d#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Conv3d, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Conv3d, MethodSkeleton)
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
// ml.Conv3d#propSkeleton
Gurax_DeclareProperty_R(Conv3d, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Conv3d, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Conv3d
//------------------------------------------------------------------------------
VType_Conv3d VTYPE_Conv3d("Conv3d");

void VType_Conv3d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Conv3d));
	// Assignment of method
	Assign(Gurax_CreateMethod(Conv3d, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Conv3d, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Conv3d
//------------------------------------------------------------------------------
VType& Value_Conv3d::vtype = VTYPE_Conv3d;

String Value_Conv3d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetConv3d().ToString(ss));
}

bool Value_Conv3d::DoSerialize(Stream& stream) const
{
	return GetConv3d().Serialize(stream);
}

Value* VType_Conv3d::DoDeserialize(Stream& stream) const
{
	RefPtr<Conv3d> pConv3d(Conv3d::Deserialize(stream));
	return pConv3d? new Value_Conv3d(pConv3d.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
