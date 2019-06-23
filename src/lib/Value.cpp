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

Value* Value::DoPropGet(const Symbol* pSymbol, const Attribute& attr)
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
	Error::Issue(ErrorType::PropertyError,
				 "value type '%s' doesn't have a property '%s'",
				 GetVType().MakeFullName().c_str(), pSymbol->GetName());
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

//------------------------------------------------------------------------------
// ValueList
//------------------------------------------------------------------------------
ValueList& ValueList::Sort(SortOrder sortOrder)
{
	SortListByOrder<ValueList, Value::LessThan, Value::GreaterThan>(*this, sortOrder);
	return *this;
}

VType* ValueList::GetVTypeOfElems() const
{
	if (empty()) return &VTYPE_Undefined;
	auto ppValue = begin();
	VType* pVTypeOfElems = &(*ppValue)->GetVType();
	ppValue++;
	for ( ; ppValue != end(); ppValue++) {
		if (!pVTypeOfElems->IsIdentical((*ppValue)->GetVType())) return &VTYPE_Any;
	}
	return pVTypeOfElems;
}

String ValueList::ToString(const StringStyle& ss) const
{
	String str;
	str += "[";
	for (auto ppValue = begin(); ppValue != end(); ++ppValue) {
		if (ppValue != begin()) str += ss.GetComma();
		str += (*ppValue)->ToString(ss);
	}
	str += "]";
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner
//------------------------------------------------------------------------------
void ValueOwner::Clear()
{
	for (Value* pValue : *this) Value::Delete(pValue);
	clear();
}

ValueOwner* ValueOwner::Clone() const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(size());
	for (Value* pValue : *this) pValueOwner->push_back(pValue->Reference());
	return pValueOwner.release();
}

ValueOwner* ValueOwner::CloneDeep() const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(size());
	for (Value* pValue : *this) {
		Value* pValueCloned = pValue->Clone();
		if (!pValueCloned) return nullptr;
		pValueOwner->push_back(pValueCloned);
	}
	return pValueOwner.release();
}

void ValueOwner::Set(size_t pos, Value* pValue)
{
	auto ppValue = begin() + pos;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

bool ValueOwner::IndexGet(const Value* pValueIndex, Value** ppValue) const
{
	if (pValueIndex->IsInstanceOf(VTYPE_Number)) {
		const Value_Number* pValueIndexEx = dynamic_cast<const Value_Number*>(pValueIndex);
		int idxOrg = pValueIndexEx->GetInt();
		int idx = (idxOrg >= 0)? idxOrg : idxOrg + size();
		if (0 <= idx && static_cast<size_t>(idx) < size()) {
			*ppValue = Get(idx)->Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %d is out of range of the list size %zu",
					 idx, size());
	} else if (pValueIndex->IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool* pValueIndexEx = dynamic_cast<const Value_Bool*>(pValueIndex);
		int idx = static_cast<int>(pValueIndexEx->GetBool());
		if (static_cast<size_t>(idx) < size()) {
			*ppValue = Get(idx)->Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %s is out of range of the list size %zu",
					 pValueIndexEx->ToString().c_str(), size());
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

bool ValueOwner::IndexSet(const Value* pValueIndex, Value* pValue)
{
	if (pValueIndex->IsInstanceOf(VTYPE_Number)) {
		const Value_Number* pValueIndexEx = dynamic_cast<const Value_Number*>(pValueIndex);
		int idxOrg = pValueIndexEx->GetInt();
		int idx = (idxOrg >= 0)? idxOrg : idxOrg + size();
		if (0 <= idx && static_cast<size_t>(idx) < size()) {
			Set(idx, pValue);
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %d is out of range of the list size %zu",
					 idx, size());
	} else if (pValueIndex->IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool* pValueIndexEx = dynamic_cast<const Value_Bool*>(pValueIndex);
		int idx = static_cast<int>(pValueIndexEx->GetBool());
		if (static_cast<size_t>(idx) < size()) {
			Set(idx, pValue);
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %s is out of range of the list size %zu",
					 pValueIndexEx->ToString().c_str(), size());
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	Value::Delete(pValue);
	return false;
}

//------------------------------------------------------------------------------
// ValueTypedOwner
//------------------------------------------------------------------------------
ValueTypedOwner::ValueTypedOwner() :
	_pVTypeOfElems(&VTYPE_Undefined), _pValueOwner(new ValueOwner())
{}

void ValueTypedOwner::Clear()
{
	_pVTypeOfElems = &VTYPE_Undefined;
	_pValueOwner->Clear();
}

void ValueTypedOwner::UpdateVTypeOfElems(VType& vtypeAdded)
{
	if (_pVTypeOfElems->IsIdentical(VTYPE_Undefined)) {
		_pVTypeOfElems = &vtypeAdded;
	} else if (!_pVTypeOfElems->IsIdentical(vtypeAdded)) {
		_pVTypeOfElems = &VTYPE_Any;
	}
}

bool ValueTypedOwner::HasDeterminedVTypeOfElems() const
{
	return !_pVTypeOfElems->IsIdentical(VTYPE_Undefined) && !_pVTypeOfElems->IsIdentical(VTYPE_Any);
}

//------------------------------------------------------------------------------
// ValueStack
//------------------------------------------------------------------------------
void ValueStack::Remove(size_t offset)
{
	auto ppValue = begin() + size() - (offset + 1);
	Value* pValue = *ppValue;
	erase(ppValue);
	Value::Delete(pValue);
}

void ValueStack::Remove(size_t offset, size_t cnt)
{
	auto ppValueBegin = begin() + size() - (offset + cnt);
	auto ppValueEnd = ppValueBegin + cnt;
	for (auto ppValue = ppValueBegin; ppValue != ppValueEnd; ppValue++) {
		Value::Delete(*ppValue);
	}
	erase(ppValueBegin, ppValueEnd);
}

void ValueStack::Shrink(size_t cnt)
{
	if (cnt >= size()) return;
	auto ppValueEnd = rbegin() + size() - cnt;
	for (auto ppValue = rbegin(); ppValue != ppValueEnd; ppValue++) {
		Value::Delete(*ppValue);
	}
	erase(begin() + cnt, end());
}

//------------------------------------------------------------------------------
// ValueMap
//------------------------------------------------------------------------------
void ValueMap::Clear()
{
	for (auto& pair : *this) Value::Delete(pair.second);
	clear();
}

void ValueMap::Assign(const Symbol* pSymbol, Value* pValue)
{
	auto pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pValue);
	} else {
		Value::Delete(pPair->second);
		pPair->second = pValue;
	}
}

String ValueMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		Value* pValue = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pValue->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pValue->ToString();
		str += "\n";
	}
	return str;
}

//------------------------------------------------------------------------------
// ValueDict
//------------------------------------------------------------------------------
void ValueDict::Clear()
{
	for (auto& pair : *this) {
		Value::Delete(pair.first);
		Value::Delete(pair.second);
	}
	clear();
}

ValueDict* ValueDict::Clone() const
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	pValueDict->reserve(size());
	for (auto pair : *this) {
		pValueDict->emplace(pair.first->Reference(), pair.second->Reference());
	}
	return pValueDict.release();
}

ValueDict* ValueDict::CloneDeep() const
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	pValueDict->reserve(size());
	for (auto pair : *this) {
		Value* pValueKeyCloned = pair.first->Clone();
		if (!pValueKeyCloned) return nullptr;
		Value* pValueCloned = pair.second->Clone();
		if (!pValueCloned) return nullptr;
		pValueDict->emplace(pValueKeyCloned, pValueCloned);
	}
	return pValueDict.release();
}

void ValueDict::Assign(Value* pValueKey, Value* pValue)
{
	auto pPair = find(pValueKey);
	if (pPair == end()) {
		emplace(pValueKey, pValue);
	} else {
		Value::Delete(pPair->second);
		pPair->second = pValue;
	}
}

String ValueDict::ToString(const StringStyle& ss) const
{
	const char* strPair = ss.IsCram()? "=>" : " => ";
	RefPtr<ValueOwner> pKeys(GetKeys());
	pKeys->Sort();
	String str;
	str += "%{";
	for (auto ppValueKey = pKeys->begin(); ppValueKey != pKeys->end(); ppValueKey++) {
		const Value* pValueKey = *ppValueKey;
		Value* pValue = Lookup(pValueKey);
		if (ppValueKey != pKeys->begin()) str += ss.GetComma();
		str += pValueKey->ToString(ss);
		str += strPair;
		str += pValue->ToString(ss);
	}
	str += "}";
	return str;
}

}
