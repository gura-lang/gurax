//==============================================================================
// VType_TimeDelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

The class `TimeDelta` represents a difference between two instances of `DateTime`.

${help.ComposePropertyHelp(TimeDelta, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(TimeDelta, `en)}

${help.ComposeMethodHelp(TimeDelta, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// TimeDelta(days?:Number, hours?:Number, mins?:Number, secs?:Number, msecs?:Number, usecs?:Number):map {block?}
Gurax_DeclareConstructor(TimeDelta)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("days", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("hours", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("mins", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("secs", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("msecs", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("usecs", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `TimeDelta` instance from specified time factors like numbers of days and hours.
)**");
}

Gurax_ImplementConstructor(TimeDelta)
{
	// Arguments
	ArgPicker args(argument);
	Int32 days	= args.IsValid()? args.PickNumber<Int32>() : 0;	// no range limit applied
	Int32 hours	= args.IsValid()? args.PickNumber<Int32>() : 0;	// no range limit applied
	Int32 mins	= args.IsValid()? args.PickNumber<Int32>() : 0;	// no range limit applied
	Int32 secs	= args.IsValid()? args.PickNumber<Int32>() : 0;	// no range limit applied
	Int32 msecs	= args.IsValid()? args.PickNumber<Int32>() : 0;	// no range limit applied
	Int32 usecs	= args.IsValid()? args.PickNumber<Int32>() : 0;	// no range limit applied
	// Function body
	RefPtr<TimeDelta> pTimeDelta(
		new TimeDelta(days, TimeDelta::CalcSecsPacked(hours, mins, secs), TimeDelta::CalcUSecsPacked(msecs, usecs)));
	return argument.ReturnValue(processor, new Value_TimeDelta(pTimeDelta.release()));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// TimeDelta#days
Gurax_DeclareProperty_RW(TimeDelta, days)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The days value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, days)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetDays());
}

Gurax_ImplementPropertySetter(TimeDelta, days)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetDays(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#hours
Gurax_DeclareProperty_RW(TimeDelta, hours)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The hours value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, hours)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetHours());
}

Gurax_ImplementPropertySetter(TimeDelta, hours)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetHours(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#mins
Gurax_DeclareProperty_RW(TimeDelta, mins)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The minutes value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, mins)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetMins());
}

Gurax_ImplementPropertySetter(TimeDelta, mins)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetMins(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#secs
Gurax_DeclareProperty_RW(TimeDelta, secs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The seconds value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, secs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetSecs());
}

Gurax_ImplementPropertySetter(TimeDelta, secs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetSecs(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#secsPacked
Gurax_DeclareProperty_RW(TimeDelta, secsPacked)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The packed seconds value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, secsPacked)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetSecsPacked());
}

Gurax_ImplementPropertySetter(TimeDelta, secsPacked)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetSecsPacked(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#msecs
Gurax_DeclareProperty_RW(TimeDelta, msecs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The micro-seconds value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, msecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetMSecs());
}

Gurax_ImplementPropertySetter(TimeDelta, msecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetMSecs(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#usecs
Gurax_DeclareProperty_RW(TimeDelta, usecs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The micro-seconds value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, usecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetUSecs());
}

Gurax_ImplementPropertySetter(TimeDelta, usecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetUSecs(Value_Number::GetNumber<Int32>(value));
}

// TimeDelta#usecsPacked
Gurax_DeclareProperty_RW(TimeDelta, usecsPacked)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The packed micro-seconds value of the time delta.
)**");
}

Gurax_ImplementPropertyGetter(TimeDelta, usecsPacked)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetSecsPacked());
}

Gurax_ImplementPropertySetter(TimeDelta, usecsPacked)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetSecsPacked(Value_Number::GetNumber<Int32>(value));
}

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
// -TimeDelta
Gurax_ImplementOpUnary(Neg, TimeDelta)
{
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(value);
	RefPtr<TimeDelta> pTd(-td);
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta + TimeDelta
Gurax_ImplementOpBinary(Add, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	RefPtr<TimeDelta> pTd(new TimeDelta(td1));
	*pTd += td2;
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta - TimeDelta
Gurax_ImplementOpBinary(Sub, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	RefPtr<TimeDelta> pTd(new TimeDelta(td1));
	*pTd -= td2;
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta * Number
Gurax_ImplementOpBinary(Mul, TimeDelta, Number)
{
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueL);
	Double num = Value_Number::GetNumber<Double>(valueR);
	RefPtr<TimeDelta> pTd(new TimeDelta(td));
	*pTd *= num;
	return new Value_TimeDelta(pTd.release());
}

// Number * TimeDelta
Gurax_ImplementOpBinary(Mul, Number, TimeDelta)
{
	Double num = Value_Number::GetNumber<Double>(valueL);
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueR);
	RefPtr<TimeDelta> pTd(new TimeDelta(td));
	*pTd *= num;
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta / Number
Gurax_ImplementOpBinary(Div, TimeDelta, Number)
{
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueL);
	Double num = Value_Number::GetNumber<Double>(valueR);
	if (num == 0) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	RefPtr<TimeDelta> pTd(new TimeDelta(td));
	*pTd /= num;
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta / TimeDelta
Gurax_ImplementOpBinary(Div, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	if (td2.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	return new Value_Number(td1 / td2);
}

// TimeDelta % TimeDelta
Gurax_ImplementOpBinary(Mod, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	if (td2.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	RefPtr<TimeDelta> pTd(new TimeDelta(td1));
	*pTd %= td2;
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta == TimeDelta
Gurax_ImplementOpBinary(Eq, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	return new Value_Bool(td1 == td2);
}

// TimeDelta != TimeDelta
Gurax_ImplementOpBinary(Ne, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	return new Value_Bool(td1 != td2);
}

// TimeDelta < TimeDelta
Gurax_ImplementOpBinary(Lt, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	return new Value_Bool(td1 < td2);
}

// TimeDelta <= TimeDelta
Gurax_ImplementOpBinary(Le, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	return new Value_Bool(td1 <= td2);
}

// TimeDelta > TimeDelta
Gurax_ImplementOpBinary(Gt, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	return new Value_Bool(td1 > td2);
}

// TimeDelta >= TimeDelta
Gurax_ImplementOpBinary(Ge, TimeDelta, TimeDelta)
{
	const TimeDelta& td1 = Value_TimeDelta::GetTimeDelta(valueL);
	const TimeDelta& td2 = Value_TimeDelta::GetTimeDelta(valueR);
	return new Value_Bool(td1 >= td2);
}

//------------------------------------------------------------------------------
// VType_TimeDelta
//------------------------------------------------------------------------------
VType_TimeDelta VTYPE_TimeDelta("TimeDelta");

void VType_TimeDelta::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(TimeDelta));
	// Assignment of property
	Assign(Gurax_CreateProperty(TimeDelta, days));
	Assign(Gurax_CreateProperty(TimeDelta, hours));
	Assign(Gurax_CreateProperty(TimeDelta, mins));
	Assign(Gurax_CreateProperty(TimeDelta, secs));
	Assign(Gurax_CreateProperty(TimeDelta, secsPacked));
	Assign(Gurax_CreateProperty(TimeDelta, msecs));
	Assign(Gurax_CreateProperty(TimeDelta, usecs));
	Assign(Gurax_CreateProperty(TimeDelta, usecsPacked));
	// Assignment of operator
	Gurax_AssignOpUnary(Neg, TimeDelta);
	Gurax_AssignOpBinary(Add, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Sub, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Mul, TimeDelta, Number);
	Gurax_AssignOpBinary(Mul, Number, TimeDelta);
	Gurax_AssignOpBinary(Div, TimeDelta, Number);
	Gurax_AssignOpBinary(Div, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Mod, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Eq, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Ne, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Lt, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Le, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Gt, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Ge, TimeDelta, TimeDelta);
}

//------------------------------------------------------------------------------
// Value_TimeDelta
//------------------------------------------------------------------------------
VType& Value_TimeDelta::vtype = VTYPE_TimeDelta;

String Value_TimeDelta::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTimeDelta().ToString(ss));
}

}
