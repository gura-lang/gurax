//==============================================================================
// VType_String.cpp
//==============================================================================
#include "stdafx.h"

// Declaration/implementation/creation of PropHandler
#define Gurax_DeclarePropertyAlias_R(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoGetValue(const Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoPutValue(Value& valueTarget, const Value* pValue, const Attribute& attr) const override {} \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable)

#define Gurax_DeclareProperty_R(nameVType, name) Gurax_DeclarePropertyAlias_R(nameVType, name, #name)

#define Gurax_ImplementPropertyGetter(nameVType, name) \
Value* PropHandler_##nameVType##_##name::DoGetValue(const Value& valueTarget, const Attribute& attr) const

#define Gurax_CreateProperty(nameVType, name) (new PropHandler_##nameVType##_##name())

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
	auto& valueThis = argument.GetValueThis<Value_String>();
	return new Value_Number(valueThis.GetStringSTL().size());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclarePropertyAlias_R(String, len, "len")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(String, len)
{
	return new Value_Number(0);
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
