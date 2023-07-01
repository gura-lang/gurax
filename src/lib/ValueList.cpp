//==============================================================================
// ValueList.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueList
//------------------------------------------------------------------------------
const ValueList ValueList::Empty;

ValueList& ValueList::Sort(SortOrder sortOrder)
{
	SortByOrder<Value::KeyLessThan, Value::KeyGreaterThan>(sortOrder);
	return *this;
}

ValueList& ValueList::Sort(Processor& processor, const Function& function)
{
	RefPtr<Argument> pArgument(new Argument(processor, function));
	std::sort(begin(), end(), Value::KeyCustomCompare(processor, function, *pArgument));
	return *this;
}

ValueList& ValueList::StableSort(SortOrder sortOrder)
{
	StableSortByOrder<Value::KeyLessThan, Value::KeyGreaterThan>(sortOrder);
	return *this;
}

ValueList& ValueList::StableSort(Processor& processor, const Function& function)
{
	RefPtr<Argument> pArgument(new Argument(processor, function));
	std::stable_sort(begin(), end(), Value::KeyCustomCompare(processor, function, *pArgument));
	return *this;
}

ValueList& ValueList::Shuffle(Random& random)
{
	std::shuffle(begin(), end(), random.GetEngine());
	return *this;
}

bool ValueList::IsElemInstanceOf(const VType& vtype) const
{
	for (const Value* pValue : *this) {
		if (!pValue->IsInstanceOf(vtype)) return false;
	}
	return true;
}

VType& ValueList::GetVTypeOfElems() const
{
	if (empty()) return VTYPE_Undefined;
	auto ppValue = begin();
	VType* pVTypeOfElems = &(*ppValue)->GetVTypeCustom();
	ppValue++;
	for ( ; ppValue != end(); ppValue++) {
		if (!pVTypeOfElems->IsIdentical((*ppValue)->GetVTypeCustom())) return VTYPE_Any;
	}
	return *pVTypeOfElems;
}

VType& ValueList::GetVTypeOfElemsQuick() const
{
	return empty()? VTYPE_Undefined : front()->GetVTypeCustom();
}

void ValueList::IncCntRefOfEach() const
{
	for (Value* pValue : *this) pValue->IncCntRef();
}

bool ValueList::CheckPosition(Int pos, Int posRaw, bool raiseFlag) const
{
	if (0 <= pos && static_cast<size_t>(pos) < size()) return true;
	if (raiseFlag) IssueError_IndexOutOfRange(posRaw);
	return false;
}

bool ValueList::FixPosition(Int* pPos, bool raiseFlag) const
{
	Int posRaw = *pPos;
	if (*pPos < 0) *pPos += size();
	return CheckPosition(*pPos, posRaw, raiseFlag);
}

bool ValueList::Contains(const Value& value) const
{
	for (const Value* pValue : *this) {
		if (pValue->IsEqualTo(value)) return true;
	}
	return false;
}

size_t ValueList::Count(const Value& value) const
{
	size_t cnt = 0;
	for (const Value* pValue : *this) {
		if (pValue->IsEqualTo(value)) cnt++;
	}
	return cnt;
}

size_t ValueList::CountFalse() const
{
	size_t cnt = 0;
	for (const Value* pValue : *this) {
		if (!pValue->GetBool()) cnt++;
	}
	return cnt;
}

size_t ValueList::CountTrue() const
{
	size_t cnt = 0;
	for (const Value* pValue : *this) {
		if (pValue->GetBool()) cnt++;
	}
	return cnt;
}

size_t ValueList::CountIf(Processor& processor, const Function& function) const
{
	Frame& frame = processor.GetFrameCur();
	size_t cnt = 0;
	RefPtr<Argument> pArgument(new Argument(processor, function));
	for (const Value* pValue : *this) {
		ArgFeeder args(*pArgument, frame);
		args.FeedValue(pValue->Reference());
		RefPtr<Value> pValueRtn(function.Eval(processor, *pArgument));
		if (pValueRtn->GetBool()) cnt++;
	}
	return cnt;
}

const Value& ValueList::Max() const
{
	if (empty()) return Value::C_nil();
	ValueList::const_iterator ppValue = begin();
	const Value* pValueRtn = *ppValue++;
	for ( ; ppValue != end(); ppValue++) {
		const Value* pValue = *ppValue;
		if (pValueRtn->IsLessThan(*pValue)) pValueRtn = pValue;
	}
	return *pValueRtn;
}

const Value& ValueList::Min() const
{
	if (empty()) return Value::C_nil();
	ValueList::const_iterator ppValue = begin();
	const Value* pValueRtn = *ppValue++;
	for ( ; ppValue != end(); ppValue++) {
		const Value* pValue = *ppValue;
		if (pValue->IsLessThan(*pValueRtn)) pValueRtn = pValue;
	}
	return *pValueRtn;
}

const Value& ValueList::Max(size_t* pIdx) const
{
	*pIdx = 0;
	if (empty()) return Value::C_nil();
	ValueList::const_iterator ppValue = begin();
	const Value* pValueRtn = *ppValue++;
	for (size_t idx = 1; ppValue != end(); ppValue++, idx++) {
		const Value* pValue = *ppValue;
		if (pValueRtn->IsLessThan(*pValue)) {
			pValueRtn = pValue;
			*pIdx = idx;
		}
	}
	return *pValueRtn;
}

const Value& ValueList::Min(size_t* pIdx) const
{
	*pIdx = 0;
	if (empty()) return Value::C_nil();
	ValueList::const_iterator ppValue = begin();
	const Value* pValueRtn = *ppValue++;
	for (size_t idx = 1; ppValue != end(); ppValue++, idx++) {
		const Value* pValue = *ppValue;
		if (pValue->IsLessThan(*pValueRtn)) {
			pValueRtn = pValue;
			*pIdx = idx;
		}
	}
	return *pValueRtn;
}

DimSizes ValueList::GetShape() const
{
	DimSizes dimSizes;
	const ValueList* pValues = this;
	while (pValues) {
		dimSizes.push_back(pValues->size());
		if (pValues->empty()) {
			break;
		} else if (pValues->front()->IsType(VTYPE_List)) {
			pValues = &Value_List::GetValueOwner(*pValues->front());
		} else if (pValues->front()->IsType(VTYPE_Tuple)) {
			pValues = &Value_Tuple::GetValueOwner(*pValues->front());
		} else {
			break;
		}
	}
	return dimSizes;
}

Array* ValueList::CreateArray(const Array::ElemTypeT& elemType) const
{
	DimSizes dimSizes = GetShape();
	if (dimSizes.CalcLength() == 0) {
		Error::Issue(ErrorType::ValueError, "failed to create an array");
		return nullptr;
	}
	RefPtr<Array> pArray(Array::Create(elemType, dimSizes));
	size_t idx = 0;
	if (!CreateArraySub(elemType, pArray->GetPointerC<void>(), idx,
							dimSizes.begin(), dimSizes.end())) return nullptr;
	return pArray.release();
}

bool ValueList::CreateArraySub(const Array::ElemTypeT& elemType, void* p, size_t& idx,
		DimSizes::const_iterator pDimSize, DimSizes::const_iterator pDimSizeEnd) const
{
	if (*pDimSize != size()) {
		Error::Issue(ErrorType::ValueError, "failed to create an array");
		return false;
	} else if (pDimSize + 1 == pDimSizeEnd) {
		for (const Value* pValue : *this) {
			if (!Array::funcs.IndexSetValue[elemType.id](p, idx, *pValue)) return false;
			idx++;
		}
	} else {
		for (const Value* pValue : *this) {
			if (pValue->IsType(VTYPE_List)) {
				const ValueList& values = Value_List::GetValueOwner(*pValue);
				values.CreateArraySub(elemType, p, idx, pDimSize + 1, pDimSizeEnd);
			} else if (pValue->IsType(VTYPE_Tuple)) {
				const ValueList& values = Value_Tuple::GetValueOwner(*pValue);
				values.CreateArraySub(elemType, p, idx, pDimSize + 1, pDimSizeEnd);
			} else {
				Error::Issue(ErrorType::ValueError, "failed to create an array");
				return false;
			}
		}
	}
	return true;
}

bool ValueList::IsEqualTo(const ValueList& valueList) const
{
	auto ppValue1 = begin(), ppValue2 = valueList.begin();
	for ( ; ppValue1 != end() && ppValue2 != valueList.end(); ppValue1++, ppValue2++) {
		if (!(*ppValue1)->IsEqualTo(**ppValue2)) return false;
	}
	return ppValue1 == end() && ppValue2 == valueList.end();
}

bool ValueList::IsLessThan(const ValueList& valueList) const
{
	auto ppValue1 = begin(), ppValue2 = valueList.begin();
	for ( ; ppValue1 != end() && ppValue2 != valueList.end(); ppValue1++, ppValue2++) {
		if ((*ppValue2)->IsLessThan(**ppValue1)) return false;
		if ((*ppValue1)->IsLessThan(**ppValue2)) return true;
	}
	return ppValue1 == end() && ppValue2 != valueList.end();
}

String ValueList::ToString(const StringStyle& ss) const
{
	String str;
	StringStyle ssMod(ss);
	ssMod.SetQuoteString();
	ssMod.SetQuoteSymbol();
	str += ss.GetOpening();
	for (auto ppValue = begin(); ppValue != end(); ++ppValue) {
		if (ppValue != begin()) str += ssMod.GetComma();
		if (*ppValue) {
			str += (*ppValue)->ToString(ssMod);
		} else {
			str += "null";
		}
	}
	if (size() == 1 && ss.IsWithParenthesis()) str += ',';
	str += ss.GetClosing();
	return str;
}

bool ValueList::Serialize(Stream& stream, bool serializeSizeFlag) const
{
	if (serializeSizeFlag && !stream.SerializePackedNumber<size_t>(size())) return false;
	for (const Value* pValue : *this) {
		if (!pValue->Serialize(stream)) return false;
	}
	return true;
}

void ValueList::IssueError_IndexOutOfRange(Int pos) const
{
	Error::Issue(ErrorType::IndexError, "specified position %d exceeds the list's size of %zu", pos, size());
}

void ValueList::IssueError_IndexOutOfRange(const char* pos) const
{
	Error::Issue(ErrorType::IndexError, "specified position %s is out of range of the list size %zu", pos, size());
}

}
