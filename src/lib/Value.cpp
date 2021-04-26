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

VType& Value::GetVTypeCustom() const
{
	return _pCustomPack? _pCustomPack->GetVType() : GetVTypeOfEntity();
}

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
	for (const VType* pVType = &GetVTypeCustom(); pVType; pVType = pVType->GetVTypeInh()) {
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

bool Value::InitCustomProp(VTypeCustom& vtypeCustom, Processor* pProcessor)
{
	if (_pCustomPack) {
		_pCustomPack->SetVType(vtypeCustom);
	} else {
		_pCustomPack.reset(new CustomPack(vtypeCustom, pProcessor, this));
	}
	return _pCustomPack->InitCustomProp();
}

String Value::ToStringGeneric(const StringStyle& ss, const char* strEntity) const
{
	if (ss.IsUnbracket()) return strEntity;
	String strHeader = GetVTypeCustom().MakeFullName();
	if (*strEntity == '\0' || strHeader == strEntity) {
		return String().Format("<%s>", strHeader.c_str());
	}
	strHeader += ":";
	return String::StartsWith<CharCase>(strEntity, strHeader.c_str())?
		String().Format("<%s>", strEntity) :
		String().Format("<%s%s>", strHeader.c_str(), strEntity);
}

void Value::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	Stream::COut->Println("no help");
}

bool Value::FeedExpandToArgument(Frame& frame, Argument& argument)
{
	argument.FeedValue(frame, Reference());
	return !Error::IsIssued();
}

bool Value::CanEvalAsMethod(const Function& function) const
{
	if (function.IsTypeMethod() || function.IsTypeConstructor()) return true;
	Error::Issue(ErrorType::ValueError, "the function can not be evaluated as a method");
	return false;
}

const DeclCallable* Value::GetDeclCallableWithError()
{
	const DeclCallable* pDeclCallable = GetDeclCallable();
	if (pDeclCallable) return pDeclCallable;
	Error::Issue(ErrorType::ValueError,
				 "value type '%s' can not be called", GetVTypeCustom().MakeFullName().c_str());
	return nullptr;
}

const DeclCallable* Value::GetDeclCallable()
{
	return nullptr;
}

Value* Value::DoIndexGet(const Index& index) const
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.empty()) {
		Value* pValue = nullptr;
		if (!DoEmptyIndexGet(&pValue)) return Value::nil();
		return pValue;
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		Value* pValue = nullptr;
		if (!index.EachIndexGet(valueIndex, &pValue)) return Value::nil();
		return pValue;
	} else {
		RefPtr<ValueOwner> pValuesRtn(new ValueOwner());
		pValuesRtn->reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			Value* pValue = nullptr;
			if (!index.EachIndexGet(*pValueIndex, &pValue)) return Value::nil();
			pValuesRtn->push_back(pValue);
		}
		return new Value_List(pValuesRtn.release());
	}
}

void Value::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.empty()) {
		DoEmptyIndexSet(pValue.release());
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		index.EachIndexSet(valueIndex, pValue.release());
	} else if (pValue->IsIterable()) {
		RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
		for (const Value* pValueIndexEach : valuesIndex) {
			RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
			if (!pValueIndexEach) break;
			if (!index.EachIndexSet(*pValueIndexEach, pValueEach.release())) return;
		}
	} else {
		for (const Value* pValueIndex : valuesIndex) {
			if (!index.EachIndexSet(*pValueIndex, pValue->Reference())) return;
		}
	}
}

bool Value::DoEmptyIndexGet(Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError,
				 "value type %s can not be accessed by indexing", GetVTypeCustom().MakeFullName().c_str());
	return Value::undefined();
}

bool Value::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError,
				 "value type %s can not be accessed by indexing", GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError,
				 "value type %s can not be accessed by indexing", GetVTypeCustom().MakeFullName().c_str());
	return Value::undefined();
}

bool Value::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError,
				 "value type %s can not be accessed by indexing", GetVTypeCustom().MakeFullName().c_str());
	return false;
}

Value* Value::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	VType& vtype = GetVTypeCustom();
	const PropSlot* pPropSlot = vtype.LookupPropSlot(pSymbol);
	if (pPropSlot) {
		if (!pPropSlot->CheckValidAttribute(attr)) return nullptr;
		if (!pPropSlot->IsSet(PropSlot::Flag::Readable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not readable", pSymbol->GetName());
			return nullptr;
		}
		return pPropSlot->GetValue(*this, attr);
	}
	RefPtr<Value> pValue(vtype.GetFrameOfMember().Retrieve(pSymbol));
	if (pValue) return pValue.release();
	if (notFoundErrorFlag) {
		Error::Issue(ErrorType::PropertyError,
					 "value type '%s' doesn't have a property '%s'",
					 vtype.MakeFullName().c_str(), pSymbol->GetName());
	}
	return nullptr;
}

bool Value::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	VType& vtype = GetVTypeCustom();
	const PropSlot* pPropSlot = vtype.LookupPropSlot(pSymbol);
	if (pPropSlot) {
		if (!pPropSlot->CheckValidAttribute(attr)) return false;
		if (!pPropSlot->IsSet(PropSlot::Flag::Writable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
			return false;
		}
		return pPropSlot->SetValue(*this, *pValue, attr);
	}
	Error::Issue(ErrorType::PropertyError,
				 "value type '%s' doesn't have a property '%s'",
				 vtype.MakeFullName().c_str(), pSymbol->GetName());
	return false;
}

bool Value::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s doesn't accept method assignment", GetVTypeCustom().MakeFullName().c_str());
	return false;
}

Iterator* Value::DoGenIterator() const
{
	Error::Issue(ErrorType::IteratorError,
				 "value type %s can not generate iterator", GetVTypeCustom().MakeFullName().c_str());
	return nullptr;
}

bool Value::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%d qualifier",
				 GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%u qualifier",
				 GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%b qualifier",
				 GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%o qualifier",
				 GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%x qualifier",
				 GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%e qualifier",
				 GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				"value type %s can not be formatted with %%f qualifier",
				GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				"value type %s can not be formatted with %%g qualifier",
				GetVTypeCustom().MakeFullName().c_str());
	return false;
}

bool Value::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags,
						ToString().c_str(), formatterFlags.precision);
}

bool Value::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				"value type %s can not be formatted with %%c qualifier",
				GetVTypeCustom().MakeFullName().c_str());
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

//------------------------------------------------------------------------------
// Value::CustomPack
//------------------------------------------------------------------------------
Value::CustomPack::CustomPack(VTypeCustom& vtypeCustom, Processor* pProcessor, Value* pValueThis) :
	_pVTypeCustom(&vtypeCustom), _pProcessor(pProcessor), _pValueThis(pValueThis), _pValuesProp(new ValueOwner())
{
}

Value::CustomPack::~CustomPack()
{
	const VTypeCustom* pVTypeCustom = _pVTypeCustom;
	for (;;) {
		const Function& funcDestructor = pVTypeCustom->GetDestructor();
		if (!funcDestructor.IsEmpty()) {
			RefPtr<Argument> pArgument(new Argument(funcDestructor));
			pArgument->SetValueThis(_pValueThis->Reference());
			Value::Delete(funcDestructor.Eval(*_pProcessor, *pArgument));
			if (Error::IsIssued()) return;
		}
		const VType* pVType = pVTypeCustom->GetVTypeInh();
		if (!pVType || !pVType->IsCustom()) break;
		pVTypeCustom = dynamic_cast<const VTypeCustom*>(pVType);
	}
}

bool Value::CustomPack::InitCustomProp()
{
	const ValueOwner& valuesPropInit = _pVTypeCustom->GetValuesPropOfInstInit();
	size_t iProp = _pValuesProp->size();
	_pValuesProp->reserve(valuesPropInit.size());
	for (auto ppValue = valuesPropInit.begin() + iProp; ppValue != valuesPropInit.end(); ppValue++) {
		Value* pValue = *ppValue;
		RefPtr<Value> pValueCloned = pValue->Clone();
		if (!pValueCloned) {
			Error::Issue(ErrorType::PropertyError, "failed to initialize property");
			return false;
		}
		_pValuesProp->push_back(pValueCloned.release());
	}
	return true;
}

void Value::CustomPack::SetCustomProp(size_t iProp, Value* pValue)
{
	ValueOwner::iterator ppValue = _pValuesProp->begin() + iProp;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

Value* Value::CustomPack::GetCustomProp(size_t iProp)
{
	return (*_pValuesProp)[iProp]->Reference();
}

}
