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
	RefPtr<Value_Random> pValue(new Value_Random());
	gmp_randstate_t& state = pValue->GetEntity();
	::gmp_randinit_default(state);
	if (validFlag_seed) ::gmp_randseed(state, seed.get_mpz_t());
	return argument.ReturnValue(processor, pValue.release());
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
	gmp_randstate_t* pState = valueThis.IsInstanceOf(VTYPE_Random)?
		&dynamic_cast<Value_Random&>(valueThis).GetEntity() : &VType_Random::GetStateGlobal();
	// Arguments
	ArgPicker args(argument);
	mp_bitcnt_t prec = args.IsValid()? args.PickNumber<mp_bitcnt_t>() : ::mpf_get_default_prec();
	// Function body
	mpf_t num;
	mpf_init(num);
	mpf_urandomb(num, *pState, prec);
	return new Value_mpf(mpf_class(num));
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
	gmp_randstate_t* pState = valueThis.IsInstanceOf(VTYPE_Random)?
		&dynamic_cast<Value_Random&>(valueThis).GetEntity() : &VType_Random::GetStateGlobal();
	// Arguments
	ArgPicker args(argument);
	mpz_class& range = args.Pick<Value_mpz>().GetEntity();
	// Function body
	mpz_t num;
	mpz_init(num);
	mpz_urandomm(num, *pState, range.get_mpz_t());
	return new Value_mpz(mpz_class(num));
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
	gmp_randstate_t* pState = valueThis.IsInstanceOf(VTYPE_Random)?
		&dynamic_cast<Value_Random&>(valueThis).GetEntity() : &VType_Random::GetStateGlobal();
	// Arguments
	ArgPicker args(argument);
	mp_bitcnt_t bits = args.PickNumber<mp_bitcnt_t>();
	// Function body
	mpz_t num;
	mpz_init(num);
	mpz_urandomb(num, *pState, bits);
	return new Value_mpz(mpz_class(num));
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
	gmp_randstate_t* pState = valueTarget.IsInstanceOf(VTYPE_Random)?
		&dynamic_cast<Value_Random&>(valueTarget).GetEntity() : &VType_Random::GetStateGlobal();
	::gmp_randseed(*pState, Value_mpz::GetEntity(value).get_mpz_t());
}

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
VType_Random VTYPE_Random("Random");
gmp_randstate_t VType_Random::_stateGlobal;

void VType_Random::DoPrepare(Frame& frameOuter)
{
	// Initialize global state
	::gmp_randinit_default(_stateGlobal);
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
// Value_Random
//------------------------------------------------------------------------------
VType& Value_Random::vtype = VTYPE_Random;

String Value_Random::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gmp.Random");
}

Gurax_EndModuleScope(gmp)
