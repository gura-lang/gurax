//==============================================================================
// VType_Cifar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.Cifar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.Cifar, `en)}

${help.ComposeMethodHelp(ml.cifar.Cifar, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.cifar.Cifar(superClassFlag as Bool) {block?}
Gurax_DeclareConstructor(Cifar)
{
	Declare(VTYPE_Cifar, Flag::None);
	DeclareArg("superClassFlag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.cifar.Cifar` instance.
)""");
}

Gurax_ImplementConstructor(Cifar)
{
	// Arguments
	ArgPicker args(argument);
	Bool superClassFlag = args.PickBool();
	// Function body
	RefPtr<Cifar> pCifar(new Cifar(superClassFlag));
	return argument.ReturnValue(processor, new Value_Cifar(pCifar.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.cifar.Cifar#Read(stream as Stream):reduce
Gurax_DeclareMethod(Cifar, Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Cifar, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	if (!valueThis.GetCifar().Read(stream)) {
		Error::Issue(ErrorType::FormatError, "invalid format of CIFAR-10/100 file");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.cifar.Cifar#nSamples
Gurax_DeclareProperty_R(Cifar, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Cifar, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetCifar().GetNSamples());
}

//------------------------------------------------------------------------------
// VType_Cifar
//------------------------------------------------------------------------------
VType_Cifar VTYPE_Cifar("Cifar");

void VType_Cifar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Cifar));
	// Assignment of method
	Assign(Gurax_CreateMethod(Cifar, Read));
	// Assignment of property
	Assign(Gurax_CreateProperty(Cifar, nSamples));
}

//------------------------------------------------------------------------------
// Value_Cifar
//------------------------------------------------------------------------------
VType& Value_Cifar::vtype = VTYPE_Cifar;

String Value_Cifar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCifar().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
