//==============================================================================
// Value.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Value
//------------------------------------------------------------------------------
const Value *Value::_pValue_undefined	= nullptr;
const Value *Value::_pValue_nil			= nullptr;
const Value *Value::_pValue_false_		= nullptr;
const Value *Value::_pValue_true_		= nullptr;
const Value *Value::_pValue_Zero		= nullptr;
const Value *Value::_pValue_EmptyStr	= nullptr;

void Value::CreateConstant()
{
	_pValue_undefined	= new Value_Undefined();
	_pValue_nil			= new Value_Nil();
	_pValue_false_		= new Value_Bool(false);
	_pValue_true_		= new Value_Bool(true);
	_pValue_Zero		= new Value_Number(0);
	_pValue_EmptyStr	= new Value_String("");
}

bool Value::IsInstanceOf(const VType& vtype) const
{
	for (const VType *pVType = &GetVType(); pVType != nullptr; pVType = pVType->GetVTypeInh()) {
		if (pVType->IsIdentical(vtype)) return true;
	}
	return false;
}

String Value::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ">";
	return str;
}

void Value::_ToStringDigest(String& str, const StringStyle& ss) const
{
	str += "<";
	str += GetVType().MakeFullName();
	if (ss.IsAddressInfo() && !IsUndefined() && !IsNil()) str.Printf(":%p", this);
}

const DeclCallable* Value::GetDeclCallable() const
{
	Error::Issue(ErrorType::ValueError,
				 "value type '%s' can not be called", GetVType().MakeFullName().c_str());
	return nullptr;
}

Value* Value::DoIndexGet(const Index& index) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be accessed by indexing", GetVType().MakeFullName().c_str());
	return Value::undefined();
}

void Value::DoIndexSet(const Index& index, Value* pValue)
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be accessed by indexing", GetVType().MakeFullName().c_str());
}

Value* Value::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const PropHandler* pPropHandler = GetVType().LookupPropHandler(pSymbol);
	if (pPropHandler) {
		if (!pPropHandler->IsSet(PropHandler::Flag::Readable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not readable", pSymbol->GetName());
			return nullptr;
		}
		return pPropHandler->GetValue(*this, attr);
	}
	Value* pValue = GetVType().GetFrame().Lookup(pSymbol);
	if (pValue) return pValue;
	if (notFoundErrorFlag) {
		Error::Issue(ErrorType::PropertyError,
					 "value type '%s' doesn't have a property '%s'",
					 GetVType().MakeFullName().c_str(), pSymbol->GetName());
	}
	return nullptr;
}

bool Value::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetVType().LookupPropHandler(pSymbol);
	if (pPropHandler) {
		if (!pPropHandler->IsSet(PropHandler::Flag::Writable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
			return false;
		}
		return pPropHandler->SetValue(*this, *pValue, attr);
	}
	Error::Issue(ErrorType::PropertyError,
				 "value type '%s' doesn't have a property '%s'",
				 GetVType().MakeFullName().c_str(), pSymbol->GetName());
	return false;
}

Iterator* Value::DoGenIterator() const
{
	Error::Issue(ErrorType::IteratorError,
				 "value type %s can not generate iterator", GetVType().MakeFullName().c_str());
	return nullptr;
}

bool Value::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%d qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%u qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%b qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%o qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%x qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%e qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%f qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%g qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Value::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, ToString().c_str(), formatterFlags.precision);
}

bool Value::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%c qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

}
