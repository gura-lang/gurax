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
	DeclareCaller(VTYPE_Any, DeclCallable::Flag::None);
}

Gurax_ImplementMethod(String, Len)
{
	auto& valueThis = argument.GetValueThis<Value_String>();
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
	//Assign(Gurax_CreatePropHandler(String, Len));
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
