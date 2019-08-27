//==============================================================================
// ValueTypedOwner.h
//==============================================================================
#ifndef GURAX_VALUETYPEDOWNER_H
#define GURAX_VALUETYPEDOWNER_H
#include "ValueOwner.h"
#include "VType_Number.h"
#include "VType_String.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueTypedOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueTypedOwner : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueTypedOwner);
public:
	//--------------------------------------------------------------------------
	// ValueTypedOwner::IteratorBase
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE IteratorBase : public Iterator {
	private:
		RefPtr<ValueTypedOwner> _pValueTypedOwner;
	public:
		IteratorBase(ValueTypedOwner* pValueTypedOwner) : _pValueTypedOwner(pValueTypedOwner) {}
	public:
		const ValueTypedOwner& GetValueTypedOwner() const { return *_pValueTypedOwner; }
		const ValueOwner& GetValueOwner() const { return GetValueTypedOwner().GetValueOwner(); }
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Each
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Each : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Each");
	private:
		size_t _idx;
		size_t _idxBegin;
	public:
		Iterator_Each(ValueTypedOwner* pValueTypedOwner, size_t idxBegin = 0) :
			IteratorBase(pValueTypedOwner), _idx(idxBegin), _idxBegin(idxBegin) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Reverse
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Reverse : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Reverse");
	private:
		size_t _idx;
	public:
		Iterator_Reverse(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Cycle
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Cycle : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Cycle");
	private:
		size_t _idx;
	public:
		Iterator_Cycle(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Pingpong
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Pingpong : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Pingpong");
	private:
		size_t _idx;
	public:
		Iterator_Pingpong(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Fold
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Fold : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Fold");
	private:
		size_t _idx;
	public:
		Iterator_Fold(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Permutation
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Permutation : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Permutation");
	public:
		Iterator_Permutation(ValueTypedOwner* pValueTypedOwner) :
			IteratorBase(pValueTypedOwner->Clone()) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_PartialPermutation
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_PartialPermutation : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_PartialPermutation");
	private:
		size_t _nExtract;
	public:
		Iterator_PartialPermutation(ValueTypedOwner* pValueTypedOwner, size_t nExtract) :
			IteratorBase(pValueTypedOwner->Clone()), _nExtract(nExtract) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Combination
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Combination : public IteratorBase {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("ValueTypedOwner::Iterator_Combination");
	private:
		size_t _nExtract;
	public:
		Iterator_Combination(ValueTypedOwner* pValueTypedOwner, size_t nExtract) :
			IteratorBase(pValueTypedOwner->Clone()), _nExtract(nExtract) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
private:
	VType* _pVTypeOfElems;	// set to "undefined", "any" or the other specific class
	RefPtr<ValueOwner> _pValueOwner;
public:
	// Constructor
	ValueTypedOwner() = delete;
	ValueTypedOwner(VType& vtypeOfElems, ValueOwner* pValueOwner);
	ValueTypedOwner(ValueOwner* pValueOwner) :
		_pVTypeOfElems(&pValueOwner->GetVTypeOfElems()), _pValueOwner(pValueOwner) {}
	// Copy constructor/operator
	ValueTypedOwner(const ValueTypedOwner& src) = delete;
	ValueTypedOwner& operator=(const ValueTypedOwner& src) = delete;
	// Move constructor/operator
	ValueTypedOwner(ValueTypedOwner&& src) = delete;
	ValueTypedOwner& operator=(ValueTypedOwner&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ValueTypedOwner() = default;
public:
	void Clear();
	ValueTypedOwner* Clone() const {
		return new ValueTypedOwner(*_pVTypeOfElems, _pValueOwner->Clone());
	}
	ValueTypedOwner* CloneDeep() const {
		return new ValueTypedOwner(*_pVTypeOfElems, _pValueOwner->CloneDeep());
	}
public:
	static ValueTypedOwner* CreateFromIterator(Iterator& iterator, bool skipNilFlag) {
		return new ValueTypedOwner(ValueOwner::CreateFromIterator(iterator, skipNilFlag));
	}
	template<typename T_Num>
	static ValueTypedOwner* CreateFromNumList(const NumList<T_Num>& nums) {
		return new ValueTypedOwner(VTYPE_Number, ValueOwner::CreateFromNumList<T_Num>(nums));
	}
	static ValueTypedOwner* CreateFromStringList(const StringList& strs) {
		return new ValueTypedOwner(VTYPE_String, ValueOwner::CreateFromStringList(strs));
	}
public:
	bool IsEmpty() const { return _pValueOwner->empty(); }
	size_t GetSize() const { return _pValueOwner->size(); }
	void Reserve(size_t size) { _pValueOwner->reserve(size); }
	bool Set(Int pos, Value* pValue);
	Value* Get(Int pos) const;
	bool IndexSet(const Value* pValueIndex, Value* pValue);
	bool IndexGet(const Value* pValueIndex, Value** ppValue) const;
	void Add(Value* pValue);
	void Add(const ValueList& values);
	void Add(const ValueTypedOwner& values);
	bool Add(Iterator& iterator);
	bool Append(const ValueList& values);
	bool Insert(Int pos, const ValueList& values);
	bool Insert(Int pos, const ValueTypedOwner& values);
	bool Insert(Int pos, Iterator& iterator);
	bool Erase(Int pos);
	bool Erase(const NumList<Int>& posList);
	void UpdateVTypeOfElems(const Value& value);
	void UpdateVTypeOfElems(VType& vtypeAdded);
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
	VType& GetVTypeOfElems() const { return *_pVTypeOfElems; }
	bool CheckPosition(Int pos) const { return GetValueOwner().CheckPosition(pos); }
	bool FixPosition(Int* pPos) const { return GetValueOwner().FixPosition(pPos); }
	bool HasDeterminedVTypeOfElems() const;
	Iterator* GenerateIterator() const { return new Iterator_Each(Reference()); }
private:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
};

}

#endif
