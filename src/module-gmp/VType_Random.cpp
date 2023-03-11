//==============================================================================
// VType_Random.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gmp.Random, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gmp.Random, `en)}

${help.ComposeMethodHelp(gmp.Random, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// gmp.Random(seed?:gmp.Int) {block?}
Gurax_DeclareConstructor(Random)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("seed", VTYPE_Int, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `gmp.Random` instance.
)""");
}

Gurax_ImplementConstructor(Random)
{
	// Arguments
	ArgPicker args(argument);
	bool validFlag_seed = false;
	mpz_class seed;
	if (validFlag_seed = args.IsValid()) seed = args.Pick<Value_Int>().GetEntity();
	// Function body
	RefPtr<Random> pRandom(new Random());
	if (validFlag_seed) pRandom->SetSeed(seed);
	return argument.ReturnValue(processor, new Value_Random(pRandom.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.Random##Float(prec?:Number)
Gurax_DeclareHybridMethod(Random, Float)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("prec", VTYPE_Int, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Generates a random number as an instance of gmp.Float.
)""");
}

Gurax_ImplementHybridMethod(Random, Float)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetEntity() : VType_Random::GetRandomGlobal();
	// Arguments
	ArgPicker args(argument);
	mp_bitcnt_t prec = args.IsValid()? args.PickNumber<mp_bitcnt_t>() : ::mpf_get_default_prec();
	// Function body
	return new Value_Float(random.GenFloat(prec));
}

// Random##FloatSeq(cnt?:Number, prec?:Number) {block?}
Gurax_DeclareHybridMethod(Random, FloatSeq)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("prec", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that randomly generates real numbers in the range of `[0, 1)`
for the specified times by `cnt`.
If `cnt` is ommited, the iterator generates numbers indefinitely.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)""");
}

Gurax_ImplementHybridMethod(Random, FloatSeq)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetEntity() : VType_Random::GetRandomGlobal();
	// Arguments
	ArgPicker args(argument);
	size_t cnt = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	mp_bitcnt_t prec = args.IsValid()? args.PickNumber<mp_bitcnt_t>() : ::mpf_get_default_prec();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Random::Iterator_FloatSeq(random.Reference(), cnt, prec));
	return argument.ReturnIterator(processor, pIterator.release());
}

// gmp.Random##Int(range:gmp.Int)
Gurax_DeclareHybridMethod(Random, Int)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Int, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Generates a random number as an instance of gmp.Int.
)""");
}

Gurax_ImplementHybridMethod(Random, Int)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetEntity() : VType_Random::GetRandomGlobal();
	// Arguments
	ArgPicker args(argument);
	mpz_class& range = args.Pick<Value_Int>().GetEntity();
	// Function body
	return new Value_Int(random.GenInt(range));
}

// gmp.Random##IntBits(bits:Number)
Gurax_DeclareHybridMethod(Random, IntBits)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("bits", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Generates a random number as an instance of gmp.Int.
)""");
}

Gurax_ImplementHybridMethod(Random, IntBits)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetEntity() : VType_Random::GetRandomGlobal();
	// Arguments
	ArgPicker args(argument);
	mp_bitcnt_t bits = args.PickNumber<mp_bitcnt_t>();
	// Function body
	return new Value_Int(random.GenIntBits(bits));
}

// gmp.Random##IntSeq(range:gmp.Int, cnt?:Number) {block?}
Gurax_DeclareHybridMethod(Random, IntSeq)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_Int, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that randomly generates integer numbers in the range of `[0, range)`
for the specified times by `cnt`.
If `cnt` is ommited, the iterator generates numbers indefinitely.

This method may take either an instance or `Random` class as its target.
If `Random` class is specified, a global instance of `Random` is used.
)""");
}

Gurax_ImplementHybridMethod(Random, IntSeq)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetEntity() : VType_Random::GetRandomGlobal();
	// Arguments
	ArgPicker args(argument);
	mpz_class& range = args.Pick<Value_Int>().GetEntity();
	size_t cnt = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Random::Iterator_IntSeq(random.Reference(), cnt, range));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.Random##seed
Gurax_DeclareHybridProperty_W(Random, seed)
{
	Declare(VTYPE_Int, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementHybridPropertySetter(Random, seed)
{
	Random& random = valueTarget.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueTarget).GetEntity() : VType_Random::GetRandomGlobal();
	random.SetSeed(Value_Int::GetEntity(value));
}

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
VType_Random VTYPE_Random("Random");
RefPtr<Random> VType_Random::_pRandomGlobal;

void VType_Random::DoPrepare(Frame& frameOuter)
{
	// Initialize global state
	_pRandomGlobal.reset(new Random());
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Random));
	// Assignment of method
	Assign(Gurax_CreateHybridMethod(Random, Float));
	Assign(Gurax_CreateHybridMethod(Random, FloatSeq));
	Assign(Gurax_CreateHybridMethod(Random, Int));
	Assign(Gurax_CreateHybridMethod(Random, IntBits));
	Assign(Gurax_CreateHybridMethod(Random, IntSeq));
	// Assignment of property
	Assign(Gurax_CreateHybridProperty(Random, seed));
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
	return new Value_Float(_pRandom->GenFloat(_prec));
}

String VType_Random::Iterator_FloatSeq::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("gmp.Random.FloatSeq:prec=%zu", _prec);
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
	return new Value_Int(_pRandom->GenInt(_range));
}

String VType_Random::Iterator_IntSeq::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("gmp.Random.IntSeq:range=%s", _range.get_str().c_str());
	if (_cnt != -1) str.Format(":n=%zu", _cnt);
	return str;
}

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
VType& Value_Random::vtype = VTYPE_Random;

String Value_Random::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gmp.Random");
}

Gurax_EndModuleScope(gmp)
