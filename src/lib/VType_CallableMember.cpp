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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// VType_CallableMember
//------------------------------------------------------------------------------
VType_CallableMember VTYPE_CallableMember("CallableMember");

void VType_CallableMember::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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

Value* Value_CallableMember::DoIndexOpApply(const Index& index, Value& value, Processor& processor, const Operator& op)
{
	return GetValueProp().IndexOpApply(index, value, processor, op);
}

Value* Value_CallableMember::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetValueProp().PropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_CallableMember::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetValueProp().PropSet(pSymbol, pValue.release(), attr);
}

}
