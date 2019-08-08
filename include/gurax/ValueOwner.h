//==============================================================================
// ValueOwner.h
//==============================================================================
#ifndef GURAX_VALUEOWNER_H
#define GURAX_VALUEOWNER_H
#include "ValueList.h"

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
	using ValueList::ValueList;
protected:
	~ValueOwner() { Clear(); }
public:
	void Clear();
	ValueOwner* Clone() const;
	ValueOwner* CloneDeep() const;
	static ValueOwner* CreateFromIterator(Iterator& iterator, bool skipNilFlag);
	void Set(Int pos, Value* pValue);
	Value* Get(Int pos) const { return at(pos); }
	void Add(Value* pValue) { push_back(pValue); }
	void Add(const ValueList& values);
	void Insert(Int pos, Value* pValue) { insert(begin() + pos, pValue); }
	void Insert(Int pos, const ValueList& values);
public:
	template<typename T_Map> static ValueOwner* CollectKeys(const T_Map& map);
};

template<typename T_Map>
ValueOwner* ValueOwner::CollectKeys(const T_Map& map)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(map.size());
	for (auto& pair : map) pValueOwner->push_back(pair.first->Reference());
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
