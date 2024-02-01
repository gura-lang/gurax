//==============================================================================
// VType_Rational.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gmp.Rational, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gmp.Rational, `en)}

${help.ComposeMethodHelp(gmp.Rational, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// gmp.Rational(num:gmp.Rational) {block?}
Gurax_DeclareConstructor(Rational)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("num", VTYPE_Rational, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `gmp.Rational` instance.
)""");
}

Gurax_ImplementConstructor(Rational)
{
	// Arguments
	ArgPicker args(argument);
	mpq_class num;
	if (args.IsValid()) num = args.Pick<Value_Rational>().GetEntity();
	// Function body
	return argument.ReturnValue(processor, new Value_Rational(std::move(num)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.Rational#set_str(str:String, base?:Number):reduce
Gurax_DeclareMethod(Rational, set_str)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts to a string.
)""");
}

Gurax_ImplementMethod(Rational, set_str)
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
		Error::Issue(ErrorType::FormatError, "invalid format for Rational value");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.Rational#denom
Gurax_DeclareProperty_R(Rational, denom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Rational, denom)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Int(valueThis.GetEntity().get_den());
}

// gmp.Rational#numer
Gurax_DeclareProperty_R(Rational, numer)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Rational, numer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Int(valueThis.GetEntity().get_num());
}

// gmp.Rational#sign
Gurax_DeclareProperty_R(Rational, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Rational, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpq_sgn(valueThis.GetEntity().get_mpq_t()));
}

//------------------------------------------------------------------------------
// VType_Rational
//------------------------------------------------------------------------------
VType_Rational VTYPE_Rational("Rational");

void VType_Rational::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Rational));
	// Assignment of method
	Assign(Gurax_CreateMethod(Rational, set_str));
	// Assignment of property
	Assign(Gurax_CreateProperty(Rational, denom));
	Assign(Gurax_CreateProperty(Rational, numer));
	Assign(Gurax_CreateProperty(Rational, sign));
}

Value* VType_Rational::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	mpq_t num;
	mpq_init(num);
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpq_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_Rational(mpq_class(num));
	} else if (value.IsInstanceOf(VTYPE_Int)) {
		::mpq_set_z(num, Value_Int::GetEntity(value).get_mpz_t());
		return new Value_Rational(mpq_class(num));
	} else if (value.IsInstanceOf(VTYPE_Float)) {
		::mpq_set_f(num, Value_Float::GetEntity(value).get_mpf_t());
		return new Value_Rational(mpq_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Rational
//------------------------------------------------------------------------------
VType& Value_Rational::vtype = VTYPE_Rational;

String Value_Rational::ToString(const StringStyle& ss) const
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
