//==============================================================================
// ValueOwner.h
//==============================================================================
#ifndef GURAX_VALUEOWNER_H
#define GURAX_VALUEOWNER_H
#include "ValueList.h"
#include "VType_Number.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueOwner : public ValueList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueOwner);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ValueOwner");
public:
	ValueOwner() {}
protected:
	ValueOwner(const ValueOwner& valueOwner) : ValueList(valueOwner) {}
	ValueOwner(const_iterator pBegin, const_iterator pEnd) : ValueList(pBegin, pEnd) {}
	~ValueOwner() { Clear(); }
public:
	void Clear();
	ValueOwner* Clone() const;
	ValueOwner* CloneDeep() const;
	ValueOwner* Head(size_t n) const;
	ValueOwner* Tail(size_t n) const;
	template<typename T_Num>
	ValueOwner* Extract(NumList<T_Num>& indices) const;
	template<typename T_Num>
	ValueOwner* Extract(NumList<T_Num>& indices, size_t n) const;
public:
	static ValueOwner* Create(Value* pValue);
	static ValueOwner* Create(Value* pValue1, Value* pValue2);
	static ValueOwner* Create(Value* pValue1, Value* pValue2, Value* pValue3);
	static ValueOwner* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4);
	static ValueOwner* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5);
	static ValueOwner* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5, Value* pValue6);
	template<typename T>
	static ValueOwner* Create(const T* tbl, size_t n) {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(n);
		for (size_t i = 0; i < n; i++) pValueOwner->push_back(new Value_Number(tbl[i]));
		return pValueOwner.release();
	}
	static ValueOwner* CreateFromIterator(Iterator& iterator, bool skipNilFlag);
	template<typename T_Num>
	static ValueOwner* CreateFromNumList(const NumList<T_Num>& nums);
	static ValueOwner* CreateFromStringList(const StringList& strs);
public:
	void Set(Int pos, Value* pValue);
	void Add(Value* pValue) { push_back(pValue); }
	void Add(const ValueList& values);
	void Add(Iterator& iterator);
	void AddX(const ValueList& values);
	void Insert(Int pos, Value* pValue) { insert(begin() + pos, pValue); }
	void Insert(Int pos, const ValueList& values);
	Value* Shift();
public:
	template<typename T_Map> static ValueOwner* CollectKeys(const T_Map& map);
};

template<typename T_Num>
ValueOwner* ValueOwner::Extract(NumList<T_Num>& indices) const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(indices.size());
	for (T_Num idx : indices) pValueOwner->push_back((*this)[idx]->Reference());
	return pValueOwner.release();
}

template<typename T_Num>
ValueOwner* ValueOwner::Extract(NumList<T_Num>& indices, size_t n) const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(indices.size());
	for (auto pIdx = indices.begin(); pIdx != indices.begin() + n; pIdx++) {
		pValueOwner->push_back((*this)[*pIdx]->Reference());
	}
	return pValueOwner.release();
}

template<typename T_Num>
ValueOwner* ValueOwner::CreateFromNumList(const NumList<T_Num>& nums)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(nums.size());
	for (T_Num num : nums) pValueOwner->push_back(new Value_Number(num));
	return pValueOwner.release();
}

template<typename T_Map>
ValueOwner* ValueOwner::CollectKeys(const T_Map& map)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(map.GetMap().size());
	for (auto& pair : map.GetMap()) pValueOwner->push_back(pair.first->Reference());
	return pValueOwner.release();
}

//------------------------------------------------------------------------------
// ValueStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueStack : public ValueOwner {
public:
	Value* Peek(int offset) { return *(rbegin() + offset); }
	void Push(Value* pValue) { push_back(pValue); }
	Value* Pop() { Value* pValue = back(); pop_back(); return pValue; }
	void Remove(size_t offset);
	void Remove(size_t offset, size_t cnt);
	void Shrink(size_t cnt);
};

}

#endif
