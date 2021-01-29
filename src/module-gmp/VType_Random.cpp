//==============================================================================
// VType_Random.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// gmp.Random(seed?:gmp.mpz) {block?}
Gurax_DeclareConstructor(Random)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("seed", VTYPE_mpz, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `gmp.Random` instance.");
}

Gurax_ImplementConstructor(Random)
{
	// Arguments
	ArgPicker args(argument);
	bool validFlag_seed = false;
	mpz_class seed;
	if (validFlag_seed = args.IsValid()) seed = args.Pick<Value_mpz>().GetEntity();
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
	DeclareArg("prec", VTYPE_mpz, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Generates a random number as an instance of gmp.mpf.\n");
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
	return new Value_mpf(random.GenFloat(prec));
}

// gmp.Random##Int(range:gmp.mpz)
Gurax_DeclareHybridMethod(Random, Int)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("range", VTYPE_mpz, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Generates a random number as an instance of gmp.mpz.\n");
}

Gurax_ImplementHybridMethod(Random, Int)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	Random& random = valueThis.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueThis).GetEntity() : VType_Random::GetRandomGlobal();
	// Arguments
	ArgPicker args(argument);
	mpz_class& range = args.Pick<Value_mpz>().GetEntity();
	// Function body
	return new Value_mpz(random.GenInt(range));
}

// gmp.Random##IntBits(bits:Number)
Gurax_DeclareHybridMethod(Random, IntBits)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("bits", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Generates a random number as an instance of gmp.mpz.\n");
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
	return new Value_mpz(random.GenIntBits(bits));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.Random##seed
Gurax_DeclareHybridProperty_W(Random, seed)
{
	Declare(VTYPE_mpz, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementHybridPropertySetter(Random, seed)
{
	Random& random = valueTarget.IsInstanceOf(VTYPE_Random)?
		dynamic_cast<Value_Random&>(valueTarget).GetEntity() : VType_Random::GetRandomGlobal();
	random.SetSeed(Value_mpz::GetEntity(value));
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Random));
	// Assignment of method
	Assign(Gurax_CreateHybridMethod(Random, Float));
	Assign(Gurax_CreateHybridMethod(Random, Int));
	Assign(Gurax_CreateHybridMethod(Random, IntBits));
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
	return new Value_mpf(_pRandom->GenFloat(_prec));
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
	return new Value_mpz(_pRandom->GenInt(_range));
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
