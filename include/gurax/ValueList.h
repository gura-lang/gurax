//==============================================================================
// ValueList.h
//==============================================================================
#ifndef GURAX_VALUELIST_H
#define GURAX_VALUELIST_H
#include "Value.h"

namespace Gurax {

class Random;

//------------------------------------------------------------------------------
// ValueList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueList : public ListBase<Value*> {
public:
	ValueList() {}
	ValueList(const_iterator first, const_iterator last) : ListBase(first, last) {}
public:
	static const ValueList Empty;
public:
	ValueList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	ValueList& Sort(Processor& processor, const Function& function);
	ValueList& StableSort(SortOrder sortOrder = SortOrder::Ascend);
	ValueList& StableSort(Processor& processor, const Function& function);
	ValueList& Shuffle(Random& random);
	VType& GetVTypeOfElems() const;
	void IncCntRefOfEach() const;
	bool CheckPosition(Int pos, Int posRaw) const;
	bool CheckPosition(Int pos) const { return CheckPosition(pos, pos); }
	bool FixPosition(Int* pPos) const;
	bool Contains(const Value& value) const;
	size_t Count(const Value& value) const;
	size_t CountFalse() const;
	size_t CountTrue() const;
	size_t CountIf(Processor& processor, const Function& function) const;
	template<typename T_Num>
	NumList<T_Num> ToNumList() const { return Value_Number::GetNumList<T_Num>(*this); }
	template<typename T>
	ListBase<T> ToListT(std::function<T(Value& value)> fn) const {
		ListBase<T> lst;
		lst.reserve(size());
		for (Value* pValue : *this) lst.push_back(fn(*pValue));
		return lst;
	}
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
