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
	//--------------------------------------------------------------------------
	// ValueTypedOwner::IteratorBase
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE IteratorBase : public Iterator {
	private:
		RefPtr<ValueOwner> _pValueOwner;
	public:
		IteratorBase(ValueOwner* pValueOwner) : _pValueOwner(pValueOwner) {}
	public:
		ValueOwner& GetValueOwner() { return *_pValueOwner; }
		const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Each
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Each : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Each");
	private:
		size_t _idx;
		size_t _idxBegin;
	public:
		Iterator_Each(ValueOwner* pValueOwner, size_t idxBegin = 0) :
			IteratorBase(pValueOwner), _idx(idxBegin), _idxBegin(idxBegin) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Reverse
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Reverse : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Reverse");
	private:
		size_t _idx;
	public:
		Iterator_Reverse(ValueOwner* pValueOwner) : IteratorBase(pValueOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Cycle
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Cycle : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Cycle");
	private:
		size_t _idx;
	public:
		Iterator_Cycle(ValueOwner* pValueOwner) : IteratorBase(pValueOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Pingpong
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Pingpong : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Pingpong");
	private:
		size_t _idx;
	public:
		Iterator_Pingpong(ValueOwner* pValueOwner) : IteratorBase(pValueOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Fold
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Fold : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Fold");
	private:
		size_t _idx;
	public:
		Iterator_Fold(ValueOwner* pValueOwner) : IteratorBase(pValueOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Permutation
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Permutation : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Permutation");
	private:
		NumList<size_t> _indices;
		bool _doneFlag;
	public:
		Iterator_Permutation(ValueOwner* pValueOwner) :
			IteratorBase(pValueOwner), _doneFlag(false) {
			_indices.FillSeq(GetValueOwner().size());
		}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_PartialPermutation
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_PartialPermutation : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_PartialPermutation");
	private:
		size_t _nExtract;
		bool _doneFlag;
		NumList<size_t> _indices;
	public:
		Iterator_PartialPermutation(ValueOwner* pValueOwner, size_t nExtract) :
			IteratorBase(pValueOwner), _nExtract(nExtract), _doneFlag(false) {
			_indices.FillSeq(GetValueOwner().size());
		}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueOwner::Iterator_Combination
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Combination : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueOwner::Iterator_Combination");
	private:
		size_t _nExtract;
		bool _doneFlag;
		NumList<size_t> _indices;
	public:
		Iterator_Combination(ValueOwner* pValueOwner, size_t nExtract) :
			IteratorBase(pValueOwner), _nExtract(nExtract), _doneFlag(false) {
			_indices.FillSeq(GetValueOwner().size());
		}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	//using ValueList::ValueList;
	ValueOwner() {}
protected:
	ValueOwner(const ValueOwner& valueOwner) : ValueList(valueOwner) {}
	ValueOwner(const_iterator pBegin, const_iterator pEnd) : ValueList(pBegin, pEnd) {}
	~ValueOwner() { Clear(); }
public:
	void Clear();
	ValueOwner* Clone() const;
	ValueOwner* Extract(size_t n) const;
	template<typename T_Num>
	ValueOwner* Extract(NumList<T_Num>& indices) const;
	template<typename T_Num>
	ValueOwner* Extract(NumList<T_Num>& indices, size_t n) const;
	ValueOwner* CloneDeep() const;
public:
	static ValueOwner* CreateFromIterator(Iterator& iterator, bool skipNilFlag);
	template<typename T_Num>
	static ValueOwner* CreateFromNumList(const NumList<T_Num>& nums);
	static ValueOwner* CreateFromStringList(const StringList& strs);
public:
	void Set(Int pos, Value* pValue);
	Value* Get(Int pos) const { return at(pos); }
	void Add(Value* pValue) { push_back(pValue); }
	void Add(const ValueList& values);
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
