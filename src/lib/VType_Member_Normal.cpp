//==============================================================================
// VType_Member_Normal.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_Normal
//------------------------------------------------------------------------------
VType_Member_Normal VTYPE_Member_Normal("Member_Normal");

void VType_Member_Normal::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_Normal
//------------------------------------------------------------------------------
String Value_Member_Normal::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

const DeclCallable* Value_Member_Normal::GetDeclCallable() const
{
	return GetValueProp().GetDeclCallable();
}

void Value_Member_Normal::DoCall(Processor& processor, Argument& argument)
{
	argument.SetValueThis(GetValueThis().Reference());
	GetValueProp().DoCall(processor, argument);
}

Value* Value_Member_Normal::DoIndexGet(const Index& index) const
{
	return GetValueProp().DoIndexGet(index);
}

void Value_Member_Normal::DoIndexSet(const Index& index, Value* pValue)
{
	GetValueProp().DoIndexSet(index, pValue);
}		

Value* Value_Member_Normal::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetValueProp().DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_Member_Normal::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetValueProp().DoPropSet(pSymbol, pValue.release(), attr);
}

}
