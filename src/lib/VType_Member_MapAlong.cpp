//==============================================================================
// VType_Member_MapAlong.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapAlong
//------------------------------------------------------------------------------
VType_Member_MapAlong VTYPE_Member_MapAlong("Member_MapAlong");

void VType_Member_MapAlong::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_MapAlong
//------------------------------------------------------------------------------
String Value_Member_MapAlong::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

const DeclCallable* Value_Member_MapAlong::GetDeclCallable() const
{
	return GetValueProp().GetDeclCallable();
}

void Value_Member_MapAlong::DoCall(Processor& processor, Argument& argument)
{
	argument.SetValueThis(GetValueThis().Reference());
	GetValueProp().DoCall(processor, argument);
}

Value* Value_Member_MapAlong::DoIndexGet(const Index& index) const
{
	return GetValueProp().DoIndexGet(index);
}

void Value_Member_MapAlong::DoIndexSet(const Index& index, Value* pValue)
{
	GetValueProp().DoIndexSet(index, pValue);
}		

Value* Value_Member_MapAlong::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetValueProp().DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_Member_MapAlong::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetValueProp().DoPropSet(pSymbol, pValue.release(), attr);
}

}
