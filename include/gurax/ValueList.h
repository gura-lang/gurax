//==============================================================================
// ValueList.h
//==============================================================================
#ifndef GURAX_VALUELIST_H
#define GURAX_VALUELIST_H
#include "Value.h"
#include "Array.h"
#include "ListBase.h"
#include "VType_Number.h"

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
	bool IsElemInstanceOf(const VType& vtype) const;
	VType& GetVTypeOfElems() const;
	VType& GetVTypeOfElemsQuick() const;
	void IncCntRefOfEach() const;
	bool CheckPosition(Int pos, Int posRaw, bool raiseFlag) const;
	bool CheckPosition(Int pos, bool raiseFlag) const { return CheckPosition(pos, pos, raiseFlag); }
	bool FixPosition(Int* pPos, bool raiseFlag) const;
	bool Contains(const Value& value) const;
	size_t Count(const Value& value) const;
	size_t CountFalse() const;
	size_t CountTrue() const;
	size_t CountIf(Processor& processor, const Function& function) const;
	Value& Get(Int pos) const { return *at(pos); }
	const Value& Max() const;
	const Value& Min() const;
	const Value& Max(size_t* pIdx) const;
	const Value& Min(size_t* pIdx) const;
	//bool IndexGet(const Value& valueIndex, Value** ppValue, bool tupleResultFlag) const;
	template<typename T_Num>
	NumList<T_Num> ToNumList() const { return Value_Number::GetNumList<T_Num>(*this); }
	template<typename T_Num>
	NumList<T_Num> ToNumListRanged(T_Num numMin, T_Num numMax) const {
		return Value_Number::GetNumListRanged<T_Num>(*this);
	}
	template<typename T_Num>
	NumList<T_Num> ToNumListNonNeg() const { return Value_Number::GetNumListNonNeg<T_Num>(*this); }
	template<typename T_Num>
	NumList<T_Num> ToNumListPos() const { return Value_Number::GetNumListPos<T_Num>(*this); }
	template<typename T>
	ListBase<T> ToListT(std::function<T(Value& value)> fn) const {
		ListBase<T> lst;
		lst.reserve(size());
		for (Value* pValue : *this) lst.push_back(fn(*pValue));
		return lst;
	}
	DimSizes GetShape() const;
	Array* CreateArray(const Array::ElemTypeT& elemType) const;
	bool CreateArraySub(const Array::ElemTypeT& elemType, void* p, size_t& idx,
		DimSizes::const_iterator pDimSize, DimSizes::const_iterator pDimSizeEnd) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueList& valueList) const { return this == &valueList; }
	bool IsEqualTo(const ValueList& valueList) const;
	bool IsLessThan(const ValueList& valueList) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	bool Serialize(Stream& stream, bool serializeSizeFlag = true) const;
public:
	void IssueError_IndexOutOfRange(Int pos) const;
	void IssueError_IndexOutOfRange(const char* pos) const;
};

}

#endif
