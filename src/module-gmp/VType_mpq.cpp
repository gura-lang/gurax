//==============================================================================
// VType_mpq.cpp
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
// gmp.mpq(num:gmp.mpq) {block?}
Gurax_DeclareConstructor(mpq)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("num", VTYPE_mpq, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `gmp.mpq` instance.");
}

Gurax_ImplementConstructor(mpq)
{
	// Arguments
	ArgPicker args(argument);
	mpq_class num;
	if (args.IsValid()) num = args.Pick<Value_mpq>().GetEntity();
	// Function body
	return argument.ReturnValue(processor, new Value_mpq(std::move(num)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.mpq#set_str(str:String, base?:Number):reduce
Gurax_DeclareMethod(mpq, set_str)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts to a string.\n");
}

Gurax_ImplementMethod(mpq, set_str)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	int base = args.IsValid()? args.PickNumber<int>() : 10;
	// Function body
	int rtn = valueThis.GetEntity().set_str(str, base);
	if (rtn < 0) {
		Error::Issue(ErrorType::FormatError, "invalid format for mpq value");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.mpq#denom
Gurax_DeclareProperty_R(mpq, denom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, denom)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_mpz(valueThis.GetEntity().get_den());
}

// gmp.mpq#numer
Gurax_DeclareProperty_R(mpq, numer)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, numer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_mpz(valueThis.GetEntity().get_num());
}

// gmp.mpq#sign
Gurax_DeclareProperty_R(mpq, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpq_sgn(valueThis.GetEntity().get_mpq_t()));
}

//------------------------------------------------------------------------------
// VType_mpq
//------------------------------------------------------------------------------
VType_mpq VTYPE_mpq("mpq");

void VType_mpq::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(mpq));
	// Assignment of method
	Assign(Gurax_CreateMethod(mpq, set_str));
	// Assignment of property
	Assign(Gurax_CreateProperty(mpq, denom));
	Assign(Gurax_CreateProperty(mpq, numer));
	Assign(Gurax_CreateProperty(mpq, sign));
}

Value* VType_mpq::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	mpq_t num;
	mpq_init(num);
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpq_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_mpq(mpq_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpz)) {
		::mpq_set_z(num, Value_mpz::GetEntity(value).get_mpz_t());
		return new Value_mpq(mpq_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpf)) {
		::mpq_set_f(num, Value_mpf::GetEntity(value).get_mpf_t());
		return new Value_mpq(mpq_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_mpq
//------------------------------------------------------------------------------
VType& Value_mpq::vtype = VTYPE_mpq;

String Value_mpq::ToString(const StringStyle& ss) const
{
	String strEntity;
	strEntity = _entity.get_num().get_str();
	if (_entity.get_den() != 1) {
		strEntity += "L/";
		strEntity += _entity.get_den().get_str();
	}
	strEntity += "Lr";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

Gurax_EndModuleScope(gmp)
