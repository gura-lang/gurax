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
	SortListByOrder<ValueList, Value::KeyLessThan, Value::KeyGreaterThan>(*this, sortOrder);
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
	StableSortListByOrder<ValueList, Value::KeyLessThan, Value::KeyGreaterThan>(*this, sortOrder);
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
