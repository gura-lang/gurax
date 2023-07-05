//==============================================================================
// VType_Conv1d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Conv1d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Conv1d, `en)}

${help.ComposeMethodHelp(ml.Conv1d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Conv1d() {block?}
Gurax_DeclareConstructor(Conv1d)
{
	Declare(VTYPE_Conv1d, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Conv1d` instance.
)""");
}

Gurax_ImplementConstructor(Conv1d)
{
	// Function body
	RefPtr<Conv1d> pConv1d(new Conv1d());
	return argument.ReturnValue(processor, new Value_Conv1d(pConv1d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Conv1d#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Conv1d, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Conv1d, MethodSkeleton)
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
// ml.Conv1d#propSkeleton
Gurax_DeclareProperty_R(Conv1d, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Conv1d, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Conv1d
//------------------------------------------------------------------------------
VType_Conv1d VTYPE_Conv1d("Conv1d");

void VType_Conv1d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Conv1d));
	// Assignment of method
	Assign(Gurax_CreateMethod(Conv1d, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Conv1d, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Conv1d
//------------------------------------------------------------------------------
VType& Value_Conv1d::vtype = VTYPE_Conv1d;

String Value_Conv1d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetConv1d().ToString(ss));
}

bool Value_Conv1d::DoSerialize(Stream& stream) const
{
	return GetConv1d().Serialize(stream);
}

Value* VType_Conv1d::DoDeserialize(Stream& stream) const
{
	RefPtr<Conv1d> pConv1d(Conv1d::Deserialize(stream));
	return pConv1d? new Value_Conv1d(pConv1d.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
