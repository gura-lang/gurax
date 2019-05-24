//==============================================================================
// VType_TimeDelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// TimeDelta(days?:Number, hours?:Number, mins?:Number, secs?:Number, usecs?:Number)
Gurax_DeclareFunction(TimeDelta)
{
	Declare(VTYPE_DateTime, Flag::None);
	DeclareArg("days", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("hours", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("mins", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("secs", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("usecs", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `TimeDelta` instance.");
}

Gurax_ImplementFunction(TimeDelta)
{
	// Arguments
	ArgPicker args(argument);
	Int32 days	= args.IsValid()? args.PickInt32() : 0;
	Int32 hours	= args.IsValid()? args.PickInt32() : 0;
	Int32 mins	= args.IsValid()? args.PickInt32() : 0;
	Int32 secs	= args.IsValid()? args.PickInt32() : 0;
	Int32 usecs	= args.IsValid()? args.PickInt32() : 0;
	// Function body
	RefPtr<TimeDelta> pTimeDelta(new TimeDelta(days, TimeDelta::CalcSecsRaw(hours, mins, secs), usecs));
	return new Value_TimeDelta(pTimeDelta.release());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// TimeDelta#days
Gurax_DeclareProperty_RW(TimeDelta, days)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The days value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, days)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetDays());
}

Gurax_ImplementPropertySetter(TimeDelta, days)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetDays(Value_Number::GetInt32(value));
}

// TimeDelta#hours
Gurax_DeclareProperty_RW(TimeDelta, hours)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The hours value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, hours)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetHours());
}

Gurax_ImplementPropertySetter(TimeDelta, hours)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetHours(Value_Number::GetInt32(value));
}

// TimeDelta#mins
Gurax_DeclareProperty_RW(TimeDelta, mins)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The minutes value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, mins)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetMins());
}

Gurax_ImplementPropertySetter(TimeDelta, mins)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetMins(Value_Number::GetInt32(value));
}

// TimeDelta#secs
Gurax_DeclareProperty_RW(TimeDelta, secs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The seconds value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, secs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetSecs());
}

Gurax_ImplementPropertySetter(TimeDelta, secs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetSecs(Value_Number::GetInt32(value));
}

// TimeDelta#secsRaw
Gurax_DeclareProperty_RW(TimeDelta, secsRaw)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The raw-seconds value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, secsRaw)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetSecsRaw());
}

Gurax_ImplementPropertySetter(TimeDelta, secsRaw)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetSecsRaw(Value_Number::GetInt32(value));
}

// TimeDelta#msecs
Gurax_DeclareProperty_RW(TimeDelta, msecs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The micro-seconds value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, msecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetMSecs());
}

Gurax_ImplementPropertySetter(TimeDelta, msecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetMSecs(Value_Number::GetInt32(value));
}

// TimeDelta#usecs
Gurax_DeclareProperty_RW(TimeDelta, usecs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The micro-seconds value of the time delta.");
}

Gurax_ImplementPropertyGetter(TimeDelta, usecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTimeDelta().GetUSecs());
}

Gurax_ImplementPropertySetter(TimeDelta, usecs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTimeDelta().SetUSecs(Value_Number::GetInt32(value));
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
	int num = Value_Number::GetInt(valueR);
	RefPtr<TimeDelta> pTd(new TimeDelta(td));
	//*pTd *= num;
	return new Value_TimeDelta(pTd.release());
}

// Number * TimeDelta
Gurax_ImplementOpBinary(Mul, Number, TimeDelta)
{
	int num = Value_Number::GetInt(valueL);
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueR);
	RefPtr<TimeDelta> pTd(new TimeDelta(td));
	//*pTd *= num;
	return new Value_TimeDelta(pTd.release());
}

// TimeDelta / Number
Gurax_ImplementOpBinary(Div, TimeDelta, Number)
{
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueL);
	int num = Value_Number::GetInt(valueR);
	if (num == 0) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	RefPtr<TimeDelta> pTd(new TimeDelta(td));
	//*pTd /= num;
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
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(TimeDelta));
	// Assignment of property
	Assign(Gurax_CreateProperty(TimeDelta, days));
	Assign(Gurax_CreateProperty(TimeDelta, hours));
	Assign(Gurax_CreateProperty(TimeDelta, mins));
	Assign(Gurax_CreateProperty(TimeDelta, secs));
	Assign(Gurax_CreateProperty(TimeDelta, secsRaw));
	Assign(Gurax_CreateProperty(TimeDelta, msecs));
	Assign(Gurax_CreateProperty(TimeDelta, usecs));
	// Assignment of operator
	Gurax_AssignOpUnary(Neg, TimeDelta);
	Gurax_AssignOpBinary(Add, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Sub, TimeDelta, TimeDelta);
	Gurax_AssignOpBinary(Mul, TimeDelta, Number);
	Gurax_AssignOpBinary(Mul, Number, TimeDelta);
	Gurax_AssignOpBinary(Div, TimeDelta, Number);
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

}
