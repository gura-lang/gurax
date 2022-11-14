//==============================================================================
// VType_CallableMember.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(CallableMember, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(CallableMember, `en)}

${help.ComposeMethodHelp(CallableMember, `en)}
)**";

//------------------------------------------------------------------------------
// VType_CallableMember
//------------------------------------------------------------------------------
VType_CallableMember VTYPE_CallableMember("CallableMember");

void VType_CallableMember::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_CallableMember
//------------------------------------------------------------------------------
VType& Value_CallableMember::vtype = VTYPE_CallableMember;

String Value_CallableMember::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetValueProp().ToString(StringStyle::Unbracket));
}

void Value_CallableMember::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	GetValueProp().PresentHelp(processor, pLangCode);
}

const DeclCallable* Value_CallableMember::GetDeclCallable()
{
	return GetValueProp().GetDeclCallable();
}

void Value_CallableMember::DoCall(Processor& processor, Argument& argument)
{
	argument.SetValueThis(GetValueThis().Reference());
	GetValueProp().Call(processor, argument);
}

Value* Value_CallableMember::DoEval(Processor& processor, Argument& argument) const
{
	argument.SetValueThis(GetValueThis().Reference());
	return GetValueProp().Eval(processor, argument);
}

Value* Value_CallableMember::DoIndexGet(const Index& index) const
{
	return GetValueProp().IndexGet(index);
}

void Value_CallableMember::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	GetValueProp().IndexSet(index, pValue.release());
}		

bool Value_CallableMember::DoEmptyIndexGet(Value** ppValue) const
{
	return GetValueProp().DoEmptyIndexGet(ppValue);
}

bool Value_CallableMember::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	return GetValueProp().DoEmptyIndexSet(pValue.release());
}

bool Value_CallableMember::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	return GetValueProp().DoSingleIndexGet(valueIndex, ppValue);
}

bool Value_CallableMember::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	return GetValueProp().DoSingleIndexSet(valueIndex, pValue.release());
}

Value* Value_CallableMember::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetValueProp().GetProperty(pSymbol, attr, notFoundErrorFlag);
}

bool Value_CallableMember::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetValueProp().SetProperty(pSymbol, pValue.release(), attr);
}

}
