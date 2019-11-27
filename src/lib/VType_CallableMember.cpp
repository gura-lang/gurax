//==============================================================================
// VType_CallableMember.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_CallableMember
//------------------------------------------------------------------------------
VType_CallableMember VTYPE_CallableMember("CallableMember");

void VType_CallableMember::DoPrepare(Frame& frameOuter)
{
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_CallableMember
//------------------------------------------------------------------------------
VType& Value_CallableMember::vtype = VTYPE_CallableMember;

String Value_CallableMember::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

const DeclCallable* Value_CallableMember::GetDeclCallable()
{
	return GetValueProp().GetDeclCallable();
}

void Value_CallableMember::DoCall(Processor& processor, Argument& argument)
{
	argument.SetValueThis(GetValueThis().Reference());
	GetValueProp().DoCall(processor, argument);
}

Value* Value_CallableMember::DoEval(Processor& processor, Argument& argument) const
{
	argument.SetValueThis(GetValueThis().Reference());
	return GetValueProp().DoEval(processor, argument);
}

Value* Value_CallableMember::DoIndexGet(const Index& index) const
{
	return GetValueProp().DoIndexGet(index);
}

void Value_CallableMember::DoIndexSet(const Index& index, Value* pValue)
{
	GetValueProp().DoIndexSet(index, pValue);
}		

void Value_CallableMember::DoIndexOpApply(const Index& index, const Value& value, const Operator& op)
{
	GetValueProp().DoIndexOpApply(index, value, op);
}

Value* Value_CallableMember::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetValueProp().DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_CallableMember::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetValueProp().DoPropSet(pSymbol, pValue.release(), attr);
}

}
