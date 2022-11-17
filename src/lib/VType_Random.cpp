//==============================================================================
// VType_Random.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Random, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Random, `en)}

${help.ComposeMethodHelp(Random, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Random(seed?:Number):map {block?}
Gurax_DeclareConstructor(Random)
{
	Declare(VTYPE_Random, Flag::Map);
	DeclareArg("seed", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Random` instance that has been initialized with the specified seed.
If the argument `seed` is omitted, it creates an instance that holds a reference
to a random generator globally shared in the interpreter's environment.
)**");
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
// Random##Bool()
Gurax_DeclareHybridMethod(Random, Bool)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Randomly generates a boolean value, `true` or `false`.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, Bool)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Function body
	return new Value_Bool(random.GenBool());
}

// Random##BoolSeq(cnt?:Number) {block?}
Gurax_DeclareHybridMethod(Random, BoolSeq)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that randomly generates boolean numbers, `true` or `false`
for the specified times by `cnt`.
If `cnt` is ommited, the iterator generates numbers indefinitely.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, BoolSeq)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	size_t cnt = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Random::Iterator_BoolSeq(random.Reference(), cnt));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Random##Float()
Gurax_DeclareHybridMethod(Random, Float)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Randomly generates a real number in the range of `[0, 1)`.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, Float)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Function body
	return new Value_Number(random.GenFloat<Double>());
}

// Random##FloatSeq(cnt?:Number) {block?}
Gurax_DeclareHybridMethod(Random, FloatSeq)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that randomly generates real numbers in the range of `[0, 1)`
for the specified times by `cnt`.
If `cnt` is ommited, the iterator generates numbers indefinitely.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, FloatSeq)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	size_t cnt = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Random::Iterator_FloatSeq(random.Reference(), cnt));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Random##Int(range:Number)
Gurax_DeclareHybridMethod(Random, Int)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Randomly generates an integer number within the range of `[0, range)`

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, Int)
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

// Random##IntSeq(range:Number, cnt?:Number) {block?}
Gurax_DeclareHybridMethod(Random, IntSeq)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that randomly generates integer numbers in the range of `[0, range)`
for the specified times by `cnt`.
If `cnt` is ommited, the iterator generates numbers indefinitely.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, IntSeq)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	Int range = args.PickNumberNonNeg<Int>();
	size_t cnt = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Random::Iterator_IntSeq(random.Reference(), cnt, range));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Random##Normal(mean?:Number, stddev?:Number)
Gurax_DeclareHybridMethod(Random, Normal)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mean", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("stddev", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Randomly generates a real number based on uniform distribution
with specified mean and standard deviation values.
In default, the value of `mean` is `0` and `stddev` is `1`.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, Normal)
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

// Random##NormalSeq(mean?:Number, stddev?:Number, cnt?:Number) {block?}
Gurax_DeclareHybridMethod(Random, NormalSeq)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mean", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("stddev", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that randomly generates real numbers based
on uniform distribution with specified mean and standard deviation values
for the specified times by `cnt`.
If `cnt` is ommited, the iterator generates numbers indefinitely.
In default, the value of `mean` is `0` and `stddev` is `1`.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, NormalSeq)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetRandom() : Random::Global();
	// Arguments
	ArgPicker args(argument);
	Double mean = args.IsValid()? args.PickNumber<Double>() : 0.;
	Double stddev = args.IsValid()? args.PickNumber<Double>() : 1.;
	size_t cnt = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Random::Iterator_NormalSeq(random.Reference(), cnt, mean, stddev));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Random##Reset():void
Gurax_DeclareHybridMethod(Random, Reset)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Reset the seed of the random generator.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)**");
}

Gurax_ImplementHybridMethod(Random, Reset)
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
// Random##seed
Gurax_DeclareHybridProperty_RW(Random, seed)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Seed value of the random instance.
)**");
}

Gurax_ImplementHybridPropertyGetter(Random, seed)
{
	Random& random = valueTarget.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueTarget).GetRandom() : Random::Global();
	return new Value_Number(random.GetSeed());
}

Gurax_ImplementHybridPropertySetter(Random, seed)
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
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Random));
	// Assignment of method
	Assign(Gurax_CreateMethod(Random, Bool));
	Assign(Gurax_CreateMethod(Random, BoolSeq));
	Assign(Gurax_CreateMethod(Random, Float));
	Assign(Gurax_CreateMethod(Random, FloatSeq));
	Assign(Gurax_CreateMethod(Random, Int));
	Assign(Gurax_CreateMethod(Random, IntSeq));
	Assign(Gurax_CreateMethod(Random, Normal));
	Assign(Gurax_CreateMethod(Random, NormalSeq));
	Assign(Gurax_CreateMethod(Random, Reset));
	// Assignment of property
	Assign(Gurax_CreateProperty(Random, seed));
}

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
VType& Value_Random::vtype = VTYPE_Random;

String Value_Random::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetRandom().ToString(ss));
}

//------------------------------------------------------------------------------
// VType_Random::Iterator_BoolSeq
//------------------------------------------------------------------------------
Value* VType_Random::Iterator_BoolSeq::DoNextValue()
{
	if (_cnt != -1) {
		if (_idx >= _cnt) return nullptr;
		_idx++;
	}
	return new Value_Bool(_pRandom->GenBool());
}

String VType_Random::Iterator_BoolSeq::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("Random.BoolSeq");
	if (_cnt != -1) str.Format(":n=%zu", _cnt);
	return str;
}

//------------------------------------------------------------------------------
// VType_Random::Iterator_FloatSeq
//------------------------------------------------------------------------------
Value* VType_Random::Iterator_FloatSeq::DoNextValue()
{
	if (_cnt != -1) {
		if (_idx >= _cnt) return nullptr;
		_idx++;
	}
	return new Value_Number(_pRandom->GenFloat());
}

String VType_Random::Iterator_FloatSeq::ToString(const StringStyle& ss) const
{
	String str = "Random.FloatSeq";
	if (_cnt != -1) str.Format(":n=%zu", _cnt);
	return str;
}

//------------------------------------------------------------------------------
// VType_Random::Iterator_IntSeq
//------------------------------------------------------------------------------
Value* VType_Random::Iterator_IntSeq::DoNextValue()
{
	if (_cnt != -1) {
		if (_idx >= _cnt) return nullptr;
		_idx++;
	}
	return new Value_Number(_pRandom->GenInt<Int>(_range));
}

String VType_Random::Iterator_IntSeq::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("Random.IntSeq:range=%zu", _range);
	if (_cnt != -1) str.Format(":n=%zu", _cnt);
	return str;
}

//------------------------------------------------------------------------------
// VType_Random::Iterator_NormalSeq
//------------------------------------------------------------------------------
Value* VType_Random::Iterator_NormalSeq::DoNextValue()
{
	if (_cnt != -1) {
		if (_idx >= _cnt) return nullptr;
		_idx++;
	}
	return new Value_Number(_pRandom->GenNormal<Double>(_mean, _stddev));
}

String VType_Random::Iterator_NormalSeq::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("Random.NormalSeq:mean=%g,stddev=%g", _mean, _stddev);
	if (_cnt != -1) str.Format(":n=%zu", _cnt);
	return str;
}

}
