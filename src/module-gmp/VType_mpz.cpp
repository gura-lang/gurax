//==============================================================================
// VType_mpz.cpp
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
// gmp.mpz(num:gmp.mpz) {block?}
Gurax_DeclareConstructor(mpz)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("num", VTYPE_mpz, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `gmp.mpz` instance.");
}

Gurax_ImplementConstructor(mpz)
{
	// Arguments
	ArgPicker args(argument);
	mpz_class num;
	if (args.IsValid()) num = args.Pick<Value_mpz>().GetEntity();
	// Function body
	return argument.ReturnValue(processor, new Value_mpz(std::move(num)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.mpz#get_str(base?:Number)
Gurax_DeclareMethod(mpz, get_str)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts to a string.\n");
}

Gurax_ImplementMethod(mpz, get_str)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int base = args.IsValid()? args.PickNumber<int>() : 10;
	// Function body
	return new Value_String(valueThis.GetEntity().get_str(base));
}

// gmp.mpz#set_str(str:String, base?:Number):reduce
Gurax_DeclareMethod(mpz, set_str)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts to a string.\n");
}

Gurax_ImplementMethod(mpz, set_str)
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
		Error::Issue(ErrorType::FormatError, "invalid format for mpz value");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.mpz#sign
Gurax_DeclareProperty_R(mpz, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpz, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpz_sgn(valueThis.GetEntity().get_mpz_t()));
}

//------------------------------------------------------------------------------
// VType_mpz
//------------------------------------------------------------------------------
VType_mpz VTYPE_mpz("mpz");

void VType_mpz::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(mpz));
	// Assignment of method
	Assign(Gurax_CreateMethod(mpz, get_str));
	Assign(Gurax_CreateMethod(mpz, set_str));
	// Assignment of property
	Assign(Gurax_CreateProperty(mpz, sign));
}

Value* VType_mpz::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	mpz_t num;
	mpz_init(num);
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpz_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_mpz(mpz_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpq)) {
		::mpz_set_q(num, Value_mpq::GetEntity(value).get_mpq_t());
		return new Value_mpz(mpz_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpf)) {
		::mpz_set_f(num, Value_mpf::GetEntity(value).get_mpf_t());
		return new Value_mpz(mpz_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_mpz
//------------------------------------------------------------------------------
VType& Value_mpz::vtype = VTYPE_mpz;

String Value_mpz::ToString(const StringStyle& ss) const
{
	String strEntity = GetEntity().get_str();
	strEntity += "L";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

bool Value_mpz::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(10).c_str());
}

bool Value_mpz::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(2).c_str());
}

bool Value_mpz::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(8).c_str());
}

bool Value_mpz::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(16).c_str());
}


Gurax_EndModuleScope(gmp)
