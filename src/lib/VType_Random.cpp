//==============================================================================
// VType_Random.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Random(seed?:Number):map {block?}
Gurax_DeclareFunction(Random)
{
	Declare(VTYPE_Random, Flag::Map);
	DeclareArg("seed", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Random` instance that has been initialized with the specified seed.\n"
		"If the argument `seed` is omitted, it creates an instance that holds a reference\n"
		"to a random generator globally shared in the interpreter's environment.\n");
}

Gurax_ImplementFunction(Random)
{
	// Arguments
	ArgPicker args(argument);
	bool seedFlag = false;
	Int32 seed = (seedFlag = args.IsValid())? args.PickNumber<Int32>() : 0;
	// Function body
	RefPtr<Random> pRandom(seedFlag? new Random(seed) : Random::Global().Reference());
	return ReturnValue(processor, argument, new Value_Random(pRandom.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Random#Normal(mean?:Number, stddev?:Number)
Gurax_DeclareMethod(Random, Normal)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mean", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("stddev", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Randomly generates a real number based on uniform distribution with specified mean and standard deviation values.\n"
		"The default value of `mean` is `0` and `stddev` is `1`.");
}

Gurax_ImplementMethod(Random, Normal)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double mean = args.IsValid()? args.PickNumber<Double>() : 0.;
	Double stddev = args.IsValid()? args.PickNumber<Double>() : 1.;
	// Function body
	return new Value_Number(valueThis.GetRandom().Normal<Double>(mean, stddev));
}

// Random#Range(range:Number)
Gurax_DeclareMethod(Random, Range)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Randomly generates an integer number in the range of `[0, range)`");
}

Gurax_ImplementMethod(Random, Range)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int range = args.PickNumberNonNeg<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return new Value_Number(valueThis.GetRandom().Range<Int>(range));
}

// Random#Reset():void
Gurax_DeclareMethod(Random, Reset)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reset the seed of the random generator.");
}

Gurax_ImplementMethod(Random, Reset)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetRandom().Reset();
	return Value::nil();
}

// Random#Uniform()
Gurax_DeclareMethod(Random, Uniform)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Randomly generates a real number in the range of `[0, 1)`");
}

Gurax_ImplementMethod(Random, Uniform)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Number(valueThis.GetRandom().Uniform<Double>());
}

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
VType_Random VTYPE_Random("Random");

void VType_Random::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Random));
	// Assignment of method
	Assign(Gurax_CreateMethod(Random, Normal));
	Assign(Gurax_CreateMethod(Random, Range));
	Assign(Gurax_CreateMethod(Random, Reset));
	Assign(Gurax_CreateMethod(Random, Uniform));
}

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
String Value_Random::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":seed=0x%08x>", GetRandom().GetSeed());
	return str;
}

String Value_Random::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
