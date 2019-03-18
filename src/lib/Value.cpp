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

void Value::PrepareBasic(Frame& frame)
{
	_pValue_undefined	= new Value_Undefined();
	_pValue_nil			= new Value_Nil();
	_pValue_false_		= new Value_Bool(false);
	_pValue_true_		= new Value_Bool(true);
	_pValue_Zero		= new Value_Number(0);
	_pValue_EmptyStr	= new Value_String("");
	frame.Assign("nil",		_pValue_nil->Reference());
	frame.Assign("false",	_pValue_false_->Reference());
	frame.Assign("true",	_pValue_true_->Reference());
}

bool Value::GetBool() const
{
	return !(IsUndefined() || IsNil() ||
			 (IsType(VTYPE_Bool) && !dynamic_cast<const Value_Bool*>(this)->GetBool()));
}

bool Value::IsInstanceOf(const VType& vtype) const
{
	for (const VType *pVType = &GetVType(); pVType != nullptr; pVType = pVType->GetVTypeInherited()) {
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
	if (!IsUndefined() && !IsNil()) {
		char buff[64];
		::sprintf(buff, ":%p", this);
		str += buff;
	}
}

Value* Value::DoCall(Processor& processor, Argument& argument)
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be called", GetVType().MakeFullName().c_str());
	return Value::undefined();
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
	return pPropHandler? pPropHandler->DoGetValue(*this, attr) : GetVType().GetFrame().Lookup(pSymbol);
}

bool Value::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetVType().LookupPropHandler(pSymbol);
	if (pPropHandler) {
		pPropHandler->DoSetValue(*this, pValue.release(), attr);
		return true;
	}
	return false;
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
	iterator ppValue = begin() + pos;
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
	iterator pPair = find(pSymbol);
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
	iterator pPair = find(pValueKey);
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
	str += "{";
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
