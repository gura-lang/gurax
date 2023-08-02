//==============================================================================
// VType_PairSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.PairSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.PairSet, `en)}

${help.ComposeMethodHelp(ml.cifar.PairSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.cifar.PairSet(superClassFlag as Bool) {block?}
Gurax_DeclareConstructor(PairSet)
{
	Declare(VTYPE_PairSet, Flag::None);
	DeclareArg("superClassFlag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.cifar.PairSet` instance.
)""");
}

Gurax_ImplementConstructor(PairSet)
{
	// Arguments
	ArgPicker args(argument);
	Bool superClassFlag = args.PickBool();
	// Function body
	RefPtr<PairSet> pPairSet(new PairSet(superClassFlag));
	return argument.ReturnValue(processor, new Value_PairSet(pPairSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.cifar.PairSet#Read(stream as Stream):reduce
Gurax_DeclareMethod(PairSet, Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(PairSet, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	if (!valueThis.GetPairSet().Read(stream)) {
		Error::Issue(ErrorType::FormatError, "invalid format of CIFAR-10/100 file");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.cifar.PairSet#nSamples
Gurax_DeclareProperty_R(PairSet, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPairSet().GetNSamples());
}

//------------------------------------------------------------------------------
// VType_PairSet
//------------------------------------------------------------------------------
VType_PairSet VTYPE_PairSet("PairSet");

void VType_PairSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(PairSet));
	// Assignment of method
	Assign(Gurax_CreateMethod(PairSet, Read));
	// Assignment of property
	Assign(Gurax_CreateProperty(PairSet, nSamples));
}

//------------------------------------------------------------------------------
// Value_PairSet
//------------------------------------------------------------------------------
VType& Value_PairSet::vtype = VTYPE_PairSet;

String Value_PairSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPairSet().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
