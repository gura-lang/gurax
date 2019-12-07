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
	Int32 seed = (validFlag_seed = args.IsValid())?
		args.PickNumber<Int32>() : static_cast<Int32>(std::random_device()());
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
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
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
		"Randomly generates an integer number within the range of `[0, range)`");
}

Gurax_ImplementClassMethod(Random, Int)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
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
		"In default, the value of `mean` is `0` and `stddev` is `1`.");
}

Gurax_ImplementClassMethod(Random, Normal)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
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
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Function body
	random.Reset();
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// Random#seed
Gurax_DeclareClassProperty_RW(Random, seed)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Seed value of the random instance.");
}

Gurax_ImplementClassPropertyGetter(Random, seed)
{
	Random& random = valueTarget.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueTarget).GetRandom() : Random::Global();
	return new Value_Number(random.GetSeed());
}

Gurax_ImplementClassPropertySetter(Random, seed)
{
	Random& random = valueTarget.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueTarget).GetRandom() : Random::Global();
	random.SetSeed(Value_Number::GetNumber<UInt32>(value));
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
