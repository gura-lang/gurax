//==============================================================================
// VType_Member_MapToList.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapToList
//------------------------------------------------------------------------------
VType_Member_MapToList VTYPE_Member_MapToList("Member_MapToList");

void VType_Member_MapToList::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_MapToList
//------------------------------------------------------------------------------
String Value_Member_MapToList::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	//str += GetValueProp().ToStringDetail(ss);
	return str;
}

const DeclCallable* Value_Member_MapToList::GetDeclCallable() const
{
	//return GetValueProp().GetDeclCallable();
	return nullptr;
}

void Value_Member_MapToList::DoCall(Processor& processor, Argument& argument)
{
	//argument.SetValueThis(GetValueThis().Reference());
	//GetValueProp().DoCall(processor, argument);
}

Value* Value_Member_MapToList::DoIndexGet(const Index& index) const
{
	//return GetValueProp().DoIndexGet(index);
	return nullptr;
}

void Value_Member_MapToList::DoIndexSet(const Index& index, Value* pValue)
{
	//GetValueProp().DoIndexSet(index, pValue);
}		

Value* Value_Member_MapToList::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	//return GetValueProp().DoPropGet(pSymbol, attr, notFoundErrorFlag);
	return nullptr;
}

bool Value_Member_MapToList::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	//return GetValueProp().DoPropSet(pSymbol, pValue.release(), attr);
	return false;
}

}
