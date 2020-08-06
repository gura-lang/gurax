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
	RefPtr<Argument> pArgument(new Argument(function));
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
	RefPtr<Argument> pArgument(new Argument(function));
	std::stable_sort(begin(), end(), Value::KeyCustomCompare(processor, function, *pArgument));
	return *this;
}

ValueList& ValueList::Shuffle(Random& random)
{
	std::shuffle(begin(), end(), random.GetEngine());
	return *this;
}

VType& ValueList::GetVTypeOfElems() const
{
	if (empty()) return VTYPE_Undefined;
	auto ppValue = begin();
	VType* pVTypeOfElems = &(*ppValue)->GetVType();
	ppValue++;
	for ( ; ppValue != end(); ppValue++) {
		if (!pVTypeOfElems->IsIdentical((*ppValue)->GetVType())) return VTYPE_Any;
	}
	return *pVTypeOfElems;
}

VType& ValueList::GetVTypeOfElemsQuick() const
{
	return empty()? VTYPE_Undefined : front()->GetVType();
}

void ValueList::IncCntRefOfEach() const
{
	for (Value* pValue : *this) pValue->IncCntRef();
}

bool ValueList::CheckPosition(Int pos, Int posRaw) const
{
	if (0 <= pos && static_cast<size_t>(pos) < size()) return true;
	IssueError_IndexOutOfRange(posRaw);
	return false;
}

bool ValueList::FixPosition(Int* pPos) const
{
	Int posRaw = *pPos;
	if (*pPos < 0) *pPos += size();
	return CheckPosition(*pPos, posRaw);
}

bool ValueList::Contains(const Value& value) const
{
	for (const Value* pValue : *this) {
		if (pValue->IsEqualTo(&value)) return true;
	}
	return false;
}

size_t ValueList::Count(const Value& value) const
{
	size_t cnt = 0;
	for (const Value* pValue : *this) {
		if (pValue->IsEqualTo(&value)) cnt++;
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
	RefPtr<Argument> pArgument(new Argument(function));
	for (const Value* pValue : *this) {
		ArgFeeder args(*pArgument);
		args.FeedValue(frame, pValue->Reference());
		RefPtr<Value> pValueRtn(function.Eval(processor, *pArgument));
		if (pValueRtn->GetBool()) cnt++;
	}
	return cnt;
}

DimSizes ValueList::GetShape() const
{
	DimSizes dimSizes;
	const ValueList* pValues = this;
	while (pValues) {
		dimSizes.push_back(pValues->size());
		if (pValues->empty() || !pValues->front()->IsType(VTYPE_List)) break;
		pValues = &Value_List::GetValueOwner(*pValues->front());
	}
	return dimSizes;
}

Array* ValueList::CreateArray(Array::ElemTypeT& elemType) const
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

bool ValueList::CreateArraySub(Array::ElemTypeT& elemType, void* p, size_t& idx,
		DimSizes::const_iterator pDimSize, DimSizes::const_iterator pDimSizeEnd) const
{
	if (*pDimSize != size()) {
		Error::Issue(ErrorType::ValueError, "failed to create an array");
		return false;
	} else if (pDimSize + 1 == pDimSizeEnd) {
		for (const Value* pValue : *this) {
			if (!elemType.IndexSetValue(p, idx, *pValue)) return false;
			idx++;
		}
	} else {
		for (const Value* pValue : *this) {
			if (pValue->IsType(VTYPE_List)) {
				const ValueList& values = Value_List::GetValueOwner(*pValue);
				values.CreateArraySub(elemType, p, idx, pDimSize + 1, pDimSizeEnd);
			} else {
				Error::Issue(ErrorType::ValueError, "failed to create an array");
				return false;
			}
		}
	}
	return true;
}

String ValueList::ToString(const StringStyle& ss) const
{
	String str;
	StringStyle ssMod(ss);
	ssMod.SetQuoteString();
	ssMod.SetQuoteSymbol();
	str += "[";
	for (auto ppValue = begin(); ppValue != end(); ++ppValue) {
		if (ppValue != begin()) str += ssMod.GetComma();
		str += (*ppValue)->ToString(ssMod);
	}
	str += "]";
	return str;
}

void ValueList::IssueError_IndexOutOfRange(Int pos) const
{
	Error::Issue(ErrorType::IndexError, "specified position %d exceeds the list's size of %zu",
				 pos, size());
}

void ValueList::IssueError_IndexOutOfRange(const char* pos) const
{
	Error::Issue(ErrorType::IndexError, "specified position %s is out of range of the list size %zu",
				 pos, size());
}

}
