//==============================================================================
// VType_Random.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Random(seed?:Number):map {block?}
Gurax_DeclareConstructor(Random)
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

Gurax_ImplementConstructor(Random)
{
	// Arguments
	ArgPicker args(argument);
	bool validFlag_seed = false;
	Int32 seed = (validFlag_seed = args.IsValid())? args.PickNumber<Int32>() : 0;
	// Function body
	RefPtr<Random> pRandom(validFlag_seed? new Random(seed) : Random::Global().Reference());
	return argument.ReturnValue(processor, new Value_Random(pRandom.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Random.Float()
Gurax_DeclareClassMethod(Random, Float)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Randomly generates a real number in the range of `[0, 1)`");
}

Gurax_ImplementClassMethod(Random, Float)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsType(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Function body
	return new Value_Number(random.GenFloat<Double>());
}

// Random.Int(range:Number)
Gurax_DeclareClassMethod(Random, Int)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Randomly generates an integer number in the range of `[0, range)`");
}

Gurax_ImplementClassMethod(Random, Int)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsType(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	Int range = args.PickNumberNonNeg<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return new Value_Number(random.GenInt<Int>(range));
}

// Random.Normal(mean?:Number, stddev?:Number)
Gurax_DeclareClassMethod(Random, Normal)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mean", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("stddev", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Randomly generates a real number based on uniform distribution with specified mean and standard deviation values.\n"
		"The default value of `mean` is `0` and `stddev` is `1`.");
}

Gurax_ImplementClassMethod(Random, Normal)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsType(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	Double mean = args.IsValid()? args.PickNumber<Double>() : 0.;
	Double stddev = args.IsValid()? args.PickNumber<Double>() : 1.;
	// Function body
	return new Value_Number(random.GenNormal<Double>(mean, stddev));
}

// Random.Reset():void
Gurax_DeclareClassMethod(Random, Reset)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reset the seed of the random generator.");
}

Gurax_ImplementClassMethod(Random, Reset)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsType(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Function body
	random.Reset();
	return Value::nil();
}

// Random.SetSeed(seed:Number):void
Gurax_DeclareClassMethod(Random, SetSeed)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("seed", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Set the seed of the random generator.");
}

Gurax_ImplementClassMethod(Random, SetSeed)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsType(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	UInt32 seed = args.PickNumber<UInt32>();
	// Function body
	random.SetSeed(seed);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// Random#seed
Gurax_DeclareProperty_R(Random, seed)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Value of the red element.");
}

Gurax_ImplementPropertyGetter(Random, seed)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetRandom().GetSeed());
}

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
VType_Random VTYPE_Random("Random");

void VType_Random::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Random));
	// Assignment of method
	Assign(Gurax_CreateMethod(Random, Float));
	Assign(Gurax_CreateMethod(Random, Int));
	Assign(Gurax_CreateMethod(Random, Normal));
	Assign(Gurax_CreateMethod(Random, Reset));
	Assign(Gurax_CreateMethod(Random, SetSeed));
	// Assignment of property
	Assign(Gurax_CreateProperty(Random, seed));
}

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
VType& Value_Random::vtype = VTYPE_Random;

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
