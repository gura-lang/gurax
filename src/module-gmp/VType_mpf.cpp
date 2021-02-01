//==============================================================================
// VType_mpf.cpp
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
// gmp.mpf(num:gmp.mpf) {block?}
Gurax_DeclareConstructor(mpf)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("num", VTYPE_mpf, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `gmp.mpf` instance.");
}

Gurax_ImplementConstructor(mpf)
{
	// Arguments
	ArgPicker args(argument);
	mpf_class num;
	if (args.IsValid()) num = args.Pick<Value_mpf>().GetEntity();
	// Function body
	return argument.ReturnValue(processor, new Value_mpf(std::move(num)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.mpf#set_str(str:String, base?:Number):reduce
Gurax_DeclareMethod(mpf, set_str)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts to a string.\n");
}

Gurax_ImplementMethod(mpf, set_str)
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
		Error::Issue(ErrorType::FormatError, "invalid format for mpf value");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// gmp.mpf.default_prec
Gurax_DeclareClassProperty_RW(mpf, default_prec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The default precision of the mpf value.");
}

Gurax_ImplementClassPropertyGetter(mpf, default_prec)
{
	return new Value_Number(::mpf_get_default_prec());
}

Gurax_ImplementClassPropertySetter(mpf, default_prec)
{
	mp_bitcnt_t prec = Value_Number::GetNumber<mp_bitcnt_t>(value);
	::mpf_set_default_prec(prec);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gmp.mpf#prec
Gurax_DeclareProperty_RW(mpf, prec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The precision of the mpf value.");
}

Gurax_ImplementPropertyGetter(mpf, prec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(::mpf_get_prec(valueThis.GetEntity().get_mpf_t()));
}

Gurax_ImplementPropertySetter(mpf, prec)
{
	auto& valueThis = GetValueThis(valueTarget);
	mp_bitcnt_t prec = Value_Number::GetNumber<mp_bitcnt_t>(value);
	::mpf_set_prec(valueThis.GetEntity().get_mpf_t(), prec);
}

// gmp.mpf#sign
Gurax_DeclareProperty_R(mpf, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpf, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpf_sgn(valueThis.GetEntity().get_mpf_t()));
}

//------------------------------------------------------------------------------
// VType_mpf
//------------------------------------------------------------------------------
VType_mpf VTYPE_mpf("mpf");

void VType_mpf::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(mpf));
	// Assignment of method
	Assign(Gurax_CreateMethod(mpf, set_str));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(mpf, default_prec));
	// Assignment of property
	Assign(Gurax_CreateProperty(mpf, prec));
	Assign(Gurax_CreateProperty(mpf, sign));
	// Assignment of VType with alias name
	frameOuter.Assign("Float", new Value_VType(VTYPE_mpf));
}

Value* VType_mpf::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	mpf_t num;
	mpf_init(num);
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpf_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_mpf(mpf_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpz)) {
		::mpf_set_z(num, Value_mpz::GetEntity(value).get_mpz_t());
		return new Value_mpf(mpf_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpq)) {
		::mpf_set_q(num, Value_mpq::GetEntity(value).get_mpq_t());
		return new Value_mpf(mpf_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_mpf
//------------------------------------------------------------------------------
VType& Value_mpf::vtype = VTYPE_mpf;

String Value_mpf::ToString(const StringStyle& ss) const
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

bool Value_mpf::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char* strEntity;
	::gmp_asprintf(&strEntity, formatterFlags.ToString("Fe").c_str(), GetEntity().get_mpf_t());
	bool rtn = formatter.PutAlignedString(formatterFlags, strEntity);
	::free(strEntity);
	return rtn;
}

bool Value_mpf::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char* strEntity;
	::gmp_asprintf(&strEntity, formatterFlags.ToString("Ff").c_str(), GetEntity().get_mpf_t());
	bool rtn = formatter.PutAlignedString(formatterFlags, strEntity);
	::free(strEntity);
	return rtn;
}

bool Value_mpf::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char* strEntity;
	::gmp_asprintf(&strEntity, formatterFlags.ToString("Fg").c_str(), GetEntity().get_mpf_t());
	bool rtn = formatter.PutAlignedString(formatterFlags, strEntity);
	::free(strEntity);
	return rtn;
}

Gurax_EndModuleScope(gmp)
