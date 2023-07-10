//==============================================================================
// VType_Linear.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Linear, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Linear, `en)}

${help.ComposeMethodHelp(ml.Linear, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Linear(nRowsIn as Number, nColsIn as Number, nColsOut as Number) {block?}
Gurax_DeclareConstructor(Linear)
{
	Declare(VTYPE_Linear, Flag::None);
	DeclareArg("nRowsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsOut", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementConstructor(Linear)
{
	// Arguments
	ArgPicker args(argument);
	size_t nRowsIn = args.PickNumberPos<size_t>();
	size_t nColsIn = args.PickNumberPos<size_t>();
	size_t nColsOut = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Linear> pLinear(new Linear(nRowsIn, nColsIn, nColsOut));
	return argument.ReturnValue(processor, new Value_Linear(pLinear.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.Linear#nRowsIn
Gurax_DeclareProperty_R(Linear, nRowsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Linear, nRowsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLinear().GetNRowsIn());
}

// ml.Linear#nColsIn
Gurax_DeclareProperty_R(Linear, nColsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Linear, nColsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLinear().GetNColsIn());
}

//------------------------------------------------------------------------------
// VType_Linear
//------------------------------------------------------------------------------
VType_Linear VTYPE_Linear("Linear");

void VType_Linear::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Linear));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Linear, CalcSizeOut));
	// Assignment of property
	Assign(Gurax_CreateProperty(Linear, nRowsIn));
	Assign(Gurax_CreateProperty(Linear, nColsIn));
}

//------------------------------------------------------------------------------c
// Value_Linear
//------------------------------------------------------------------------------
VType& Value_Linear::vtype = VTYPE_Linear;

String Value_Linear::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLinear().ToString(ss));
}

bool Value_Linear::DoSerialize(Stream& stream) const
{
	return GetLinear().Serialize(stream);
}

Value* VType_Linear::DoDeserialize(Stream& stream) const
{
	RefPtr<Linear> pLinear(Linear::Deserialize(stream));
	return pLinear? new Value_Linear(pLinear.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
