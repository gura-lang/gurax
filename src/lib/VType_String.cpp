//==============================================================================
// VType_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// String#Len()
Gurax_DeclareMethod(String, Len)
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethod(String, Len)
{
	auto& valueThis = GetValueThis(argument);
	return new Value_Number(valueThis.GetStringSTL().size());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(String, len)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(String, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetStringSTL().size());
}

Gurax_DeclareProperty_RW(String, hoge)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertySetter(String, hoge)
{
}

Gurax_ImplementPropertyGetter(String, hoge)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetStringSTL().size());
}

//------------------------------------------------------------------------------
// VType_String
//------------------------------------------------------------------------------
VType_String VTYPE_String("String");

void VType_String::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
	Assign(Gurax_CreateMethod(String, Len));
	Assign(Gurax_CreateProperty(String, len));
}

Value* VType_String::DoCastFrom(const Value& value) const
{
	return new Value_String(value.ToString());
}

//------------------------------------------------------------------------------
// Value_String
//------------------------------------------------------------------------------
String Value_String::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetStringSTL().MakeQuoted(true);
	str += ">";
	return str;
}

String Value_String::ToStringDetail(const StringStyle& ss) const
{
	return GetStringSTL().MakeQuoted(true);
}

bool Value_String::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
