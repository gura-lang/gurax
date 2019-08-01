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
	bool CheckPosition(Int pos, Int posRaw) const;
	bool CheckPosition(Int pos) const { return CheckPosition(pos, pos); }
	bool FixPosition(Int* pPos) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueList& valueList) const { return this == &valueList; }
	bool IsEqualTo(const ValueList& valueList) const { return IsIdentical(valueList); }
	bool IsLessThan(const ValueList& valueList) const { return this < &valueList; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	void IssueError_IndexOutOfRange(Int pos) const;
	void IssueError_IndexOutOfRange(const char* pos) const;
};

}

#endif
