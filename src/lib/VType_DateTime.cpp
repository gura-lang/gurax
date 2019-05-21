//==============================================================================
// VType_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// DateTime(year?:Number, month?:Number, day?:Number,
//	hour?:Number, min?:Number, sec?:Number, usec?:Number, minsOff?:Number)
Gurax_DeclareFunction(DateTime)
{
	Declare(VTYPE_DateTime, Flag::None);
	DeclareArg("year", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("month", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("day", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("hour", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("min", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("sec", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("usec", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("minsOff", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `DateTime` instance.");
}

Gurax_ImplementFunction(DateTime)
{
	// Arguments
#if 0
	ArgPicker args(argument);
	UInt16 year = args.IsDefined()? args.PickUInt16() : 0;
	UInt8 month = args.IsDefined()? args.PickUInt8() : 0;
	UInt8 day = args.IsDefined()? args.PickUInt8() : 0;
	UInt8 hour = args.IsDefined()? args.PickUInt8() : 0;
	UInt8 min = args.IsDefined()? args.PickUInt8() : 0;
	UInt8 sec = args.IsDefined()? args.PickUInt8() : 0;
	UInt32 usec = args.IsDefined()? args.PickUInt32() : 0;
	UInt32 secsOff = args.IsDefined()? args.PickUInt32() : 0;
#endif
	// Function body
	return new Value_DateTime(new DateTime());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// DateTime#year
Gurax_DeclareProperty_RW(DateTime, year)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The year value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetYear());
}

Gurax_ImplementPropertySetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetYear(Value_Number::GetInt16(value));
}

//------------------------------------------------------------------------------
// VType_DateTime
//------------------------------------------------------------------------------
VType_DateTime VTYPE_DateTime("DateTime");

void VType_DateTime::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(DateTime));
	// Assignment of property
	Assign(Gurax_CreateProperty(DateTime, year));
}

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------
String Value_DateTime::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetDateTime().ToString(ss);
	str += ">";
	return str;
}

String Value_DateTime::ToStringDetail(const StringStyle& ss) const
{
	return GetDateTime().ToString(ss);
}

}
