//==============================================================================
// ValueList.h
//==============================================================================
#ifndef GURAX_VALUELIST_H
#define GURAX_VALUELIST_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueList : public std::vector<Value*> {
public:
	using std::vector<Value*>::vector;
public:
	ValueList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	VType& GetVTypeOfElems() const;
	void IncCntRefOfEach() const;
	bool CheckPosition(Int pos) const;
	bool FixPosition(Int* pPos) const {
		if (*pPos < 0) *pPos += size();
		return CheckPosition(*pPos);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueList& valueList) const { return this == &valueList; }
	bool IsEqualTo(const ValueList& valueList) const { return IsIdentical(valueList); }
	bool IsLessThan(const ValueList& valueList) const { return this < &valueList; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	void IssueError_IndexOutOfRange(Int pos) const {
		Error::Issue(ErrorType::IndexError, "position %d exceeds the list's size of %zu",
					 pos, size());
	}
	void IssueError_IndexOutOfRange(const char* pos) const {
		Error::Issue(ErrorType::IndexError, "position %s is out of range of the list size %zu",
					 pos, size());
	}
};

}

#endif
