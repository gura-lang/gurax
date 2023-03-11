//==============================================================================
// VType_Accumulator.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(hash.Accumulator, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(hash.Accumulator, `en)}

${help.ComposeMethodHelp(hash.Accumulator, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// hash.Accumulator#Initialize():Accumulator:reduce
Gurax_DeclareMethod(Accumulator, Initialize)
{
	Declare(VTYPE_Accumulator, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Initialize the state of the hash accumulator.
)""");
}

Gurax_ImplementMethod(Accumulator, Initialize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetAccumulator().Initialize();
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// hash.Accumulator#digest
Gurax_DeclareProperty_R(Accumulator, digest)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Accumulator, digest)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Binary& digest = valueThis.GetAccumulator().GetDigest();
	return new Value_Binary(digest);
}

// hash.Accumulator#digestHex
Gurax_DeclareProperty_R(Accumulator, digestHex)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Accumulator, digestHex)
{
	auto& valueThis = GetValueThis(valueTarget);
	bool upperFlag = attr.IsSet(Gurax_Symbol(upper));
	return new Value_String(valueThis.GetAccumulator().GetDigestHex(upperFlag));
}

// hash.Accumulator#number
Gurax_DeclareProperty_R(Accumulator, number)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Stream, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Accumulator, Initialize));
	// Assignment of property
	Assign(Gurax_CreateProperty(Accumulator, digest));
	Assign(Gurax_CreateProperty(Accumulator, digestHex));
	Assign(Gurax_CreateProperty(Accumulator, number));
}

//------------------------------------------------------------------------------
// Value_Accumulator
//------------------------------------------------------------------------------
VType& Value_Accumulator::vtype = VTYPE_Accumulator;

String Value_Accumulator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetAccumulator().ToString(ss));
}

Gurax_EndModuleScope(hash)
