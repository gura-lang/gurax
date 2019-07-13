//==============================================================================
// VType_Member_MapToIter.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapToIter
//------------------------------------------------------------------------------
VType_Member_MapToIter VTYPE_Member_MapToIter("Member_MapToIter");

void VType_Member_MapToIter::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_MapToIter
//------------------------------------------------------------------------------
String Value_Member_MapToIter::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

const DeclCallable* Value_Member_MapToIter::GetDeclCallable() const
{
	return GetValueProp().GetDeclCallable();
}

void Value_Member_MapToIter::DoCall(Processor& processor, Argument& argument)
{
	argument.SetValueThis(GetValueThis().Reference());
	GetValueProp().DoCall(processor, argument);
}

Value* Value_Member_MapToIter::DoIndexGet(const Index& index) const
{
	return GetValueProp().DoIndexGet(index);
}

void Value_Member_MapToIter::DoIndexSet(const Index& index, Value* pValue)
{
	GetValueProp().DoIndexSet(index, pValue);
}		

Value* Value_Member_MapToIter::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetValueProp().DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_Member_MapToIter::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetValueProp().DoPropSet(pSymbol, pValue.release(), attr);
}

}
