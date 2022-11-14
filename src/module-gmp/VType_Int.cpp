//==============================================================================
// VType_Int.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gmp.Int, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gmp.Int, `en)}

${help.ComposeMethodHelp(gmp.Int, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// gmp.Int(num:gmp.Int) {block?}
Gurax_DeclareConstructor(Int)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("num", VTYPE_Int, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `gmp.Int` instance.
)**");
}

Gurax_ImplementConstructor(Int)
{
	// Arguments
	ArgPicker args(argument);
	mpz_class num;
	if (args.IsValid()) num = args.Pick<Value_Int>().GetEntity();
	// Function body
	return argument.ReturnValue(processor, new Value_Int(std::move(num)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.Int#get_str(base?:Number)
Gurax_DeclareMethod(Int, get_str)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(
Converts to a string.
)**");
}

Gurax_ImplementMethod(Int, get_str)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int base = args.IsValid()? args.PickNumber<int>() : 10;
	// Function body
	return new Value_String(valueThis.GetEntity().get_str(base));
}

// gmp.Int#set_str(str:String, base?:Number):reduce
Gurax_DeclareMethod(Int, set_str)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(
Converts to a string.
)**");
}

Gurax_ImplementMethod(Int, set_str)
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
		Error::Issue(ErrorType::FormatError, "invalid format for Int value");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.Int#sign
Gurax_DeclareProperty_R(Int, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Int, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpz_sgn(valueThis.GetEntity().get_mpz_t()));
}

//------------------------------------------------------------------------------
// VType_Int
//------------------------------------------------------------------------------
VType_Int VTYPE_Int("Int");

void VType_Int::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Int));
	// Assignment of method
	Assign(Gurax_CreateMethod(Int, get_str));
	Assign(Gurax_CreateMethod(Int, set_str));
	// Assignment of property
	Assign(Gurax_CreateProperty(Int, sign));
}

Value* VType_Int::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	mpz_t num;
	mpz_init(num);
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpz_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_Int(mpz_class(num));
	} else if (value.IsInstanceOf(VTYPE_Rational)) {
		::mpz_set_q(num, Value_Rational::GetEntity(value).get_mpq_t());
		return new Value_Int(mpz_class(num));
	} else if (value.IsInstanceOf(VTYPE_Float)) {
		::mpz_set_f(num, Value_Float::GetEntity(value).get_mpf_t());
		return new Value_Int(mpz_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Int
//------------------------------------------------------------------------------
VType& Value_Int::vtype = VTYPE_Int;

String Value_Int::ToString(const StringStyle& ss) const
{
	String strEntity = GetEntity().get_str();
	strEntity += "L";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

bool Value_Int::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(10).c_str());
}

bool Value_Int::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(2).c_str());
}

bool Value_Int::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(8).c_str());
}

bool Value_Int::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetEntity().get_str(16).c_str());
}


Gurax_EndModuleScope(gmp)
