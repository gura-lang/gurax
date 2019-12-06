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

Value* Value::AsMember(const Value& valueTarget) const
{
	if (valueTarget.IsType(VTYPE_Module)) {
		return Reference();
	} else if (CanBeCallableMember()) {
		return new Value_CallableMember(valueTarget.Reference(), Reference());
	} else {
		return Reference();
	}
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

void Value::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	Stream::COut->Println("no help");
}

bool Value::CanEvalAsMethod(const Function& function) const
{
	if (function.IsTypeMethod() || function.IsTypeClassMethod()) return true;
	Error::Issue(ErrorType::ValueError, "the function can not be evaluated as a method");
	return false;
}

const DeclCallable* Value::GetDeclCallableWithError()
{
	const DeclCallable* pDeclCallable = GetDeclCallable();
	if (pDeclCallable) return pDeclCallable;
	Error::Issue(ErrorType::ValueError,
				 "value type '%s' can not be called", GetVType().MakeFullName().c_str());
	return nullptr;
}

const DeclCallable* Value::GetDeclCallable()
{
	return nullptr;
}

Value* Value::DoIndexGet(const Index& index) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be accessed by indexing", GetVType().MakeFullName().c_str());
	return Value::undefined();
}

void Value::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be accessed by indexing", GetVType().MakeFullName().c_str());
}

Value* Value::DoIndexOpApply(const Index& index, const Value& value, Processor& processor, const Operator& op)
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be accessed by indexing", GetVType().MakeFullName().c_str());
	return Value::undefined();
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

bool Value::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s doesn't accept method assignment", GetVType().MakeFullName().c_str());
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

//------------------------------------------------------------------------------
// Value::CustomCompare
//------------------------------------------------------------------------------
bool Value::CustomCompare::operator()(const Value* pValue1, const Value* pValue2) const
{
	if (Error::IsIssued()) return false;
	ArgFeeder args(_argument);
	RefPtr<Frame> pFrame(_function.LockFrameOuter());
	if (!args.FeedValue(*pFrame, pValue1->Reference()) ||
		!args.FeedValue(*pFrame, pValue2->Reference())) return false;
	RefPtr<Value> pValueRtn(_function.Eval(_processor, _argument));
	return pValueRtn->GetBool();
}

//------------------------------------------------------------------------------
// Value::KeyCustomCompare
//------------------------------------------------------------------------------
bool Value::KeyCustomCompare::operator()(const Value* pValue1, const Value* pValue2) const
{
	if (Error::IsIssued()) return false;
	ArgFeeder args(_argument);
	RefPtr<Frame> pFrame(_function.LockFrameOuter());
	if (!args.FeedValue(*pFrame, pValue1->GetValueKey().Reference()) ||
		!args.FeedValue(*pFrame, pValue2->GetValueKey().Reference())) return false;
	RefPtr<Value> pValueRtn(_function.Eval(_processor, _argument));
	return pValueRtn->GetBool();
}

}
