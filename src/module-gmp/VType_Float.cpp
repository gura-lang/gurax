//==============================================================================
// VType_Float.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gmp.Float, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gmp.Float, `en)}

${help.ComposeMethodHelp(gmp.Float, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// gmp.Float(num:gmp.Float) {block?}
Gurax_DeclareConstructor(Float)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("num", VTYPE_Float, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `gmp.Float` instance.
)""");
}

Gurax_ImplementConstructor(Float)
{
	// Arguments
	ArgPicker args(argument);
	mpf_class num;
	if (args.IsValid()) num = args.Pick<Value_Float>().GetEntity();
	// Function body
	return argument.ReturnValue(processor, new Value_Float(std::move(num)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.Float#set_str(str:String, base?:Number):reduce
Gurax_DeclareMethod(Float, set_str)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts to a string.
)""");
}

Gurax_ImplementMethod(Float, set_str)
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
		Error::Issue(ErrorType::FormatError, "invalid format for Float value");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// gmp.Float.default_prec
Gurax_DeclareClassProperty_RW(Float, default_prec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The default precision of the Float value.
)""");
}

Gurax_ImplementClassPropertyGetter(Float, default_prec)
{
	return new Value_Number(::mpf_get_default_prec());
}

Gurax_ImplementClassPropertySetter(Float, default_prec)
{
	mp_bitcnt_t prec = Value_Number::GetNumber<mp_bitcnt_t>(value);
	::mpf_set_default_prec(prec);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.Float#prec
Gurax_DeclareProperty_RW(Float, prec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The precision of the Float value.
)""");
}

Gurax_ImplementPropertyGetter(Float, prec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(::mpf_get_prec(valueThis.GetEntity().get_mpf_t()));
}

Gurax_ImplementPropertySetter(Float, prec)
{
	auto& valueThis = GetValueThis(valueTarget);
	mp_bitcnt_t prec = Value_Number::GetNumber<mp_bitcnt_t>(value);
	::mpf_set_prec(valueThis.GetEntity().get_mpf_t(), prec);
}

// gmp.Float#sign
Gurax_DeclareProperty_R(Float, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Float, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpf_sgn(valueThis.GetEntity().get_mpf_t()));
}

//------------------------------------------------------------------------------
// VType_Float
//------------------------------------------------------------------------------
VType_Float VTYPE_Float("Float");

void VType_Float::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Float));
	// Assignment of method
	Assign(Gurax_CreateMethod(Float, set_str));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(Float, default_prec));
	// Assignment of property
	Assign(Gurax_CreateProperty(Float, prec));
	Assign(Gurax_CreateProperty(Float, sign));
}

Value* VType_Float::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	mpf_t num;
	mpf_init(num);
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpf_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_Float(mpf_class(num));
	} else if (value.IsInstanceOf(VTYPE_Int)) {
		::mpf_set_z(num, Value_Int::GetEntity(value).get_mpz_t());
		return new Value_Float(mpf_class(num));
	} else if (value.IsInstanceOf(VTYPE_Rational)) {
		::mpf_set_q(num, Value_Rational::GetEntity(value).get_mpq_t());
		return new Value_Float(mpf_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Float
//------------------------------------------------------------------------------
VType& Value_Float::vtype = VTYPE_Float;

String Value_Float::ToString(const StringStyle& ss) const
{
	String strEntity;
	char* buff;
	::gmp_asprintf(&buff, "%Fg", GetEntity().get_mpf_t());
	strEntity += buff;
	::free(buff);
	bool digitOnlyFlag = true;
	for (char ch : strEntity) {
		if (ch == '.' || ch == 'e') {
			digitOnlyFlag = false;
			break;
		}
	}
	strEntity += digitOnlyFlag? ".L" : "L";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

bool Value_Float::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char* strEntity;
	::gmp_asprintf(&strEntity, formatterFlags.ToString("Fe").c_str(), GetEntity().get_mpf_t());
	bool rtn = formatter.PutAlignedString(formatterFlags, strEntity);
	::free(strEntity);
	return rtn;
}

bool Value_Float::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char* strEntity;
	::gmp_asprintf(&strEntity, formatterFlags.ToString("Ff").c_str(), GetEntity().get_mpf_t());
	bool rtn = formatter.PutAlignedString(formatterFlags, strEntity);
	::free(strEntity);
	return rtn;
}

bool Value_Float::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char* strEntity;
	::gmp_asprintf(&strEntity, formatterFlags.ToString("Fg").c_str(), GetEntity().get_mpf_t());
	bool rtn = formatter.PutAlignedString(formatterFlags, strEntity);
	::free(strEntity);
	return rtn;
}

Gurax_EndModuleScope(gmp)
