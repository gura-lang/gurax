//==============================================================================
// ValueTypedOwner.h
//==============================================================================
#ifndef GURAX_VALUETYPEDOWNER_H
#define GURAX_VALUETYPEDOWNER_H
#include "ValueOwner.h"

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
	private:
		size_t _idx;
	public:
		Iterator_Each(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Reverse
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Reverse : public IteratorBase {
	private:
		size_t _idx;
	public:
		Iterator_Reverse(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Cycle
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Cycle : public IteratorBase {
	private:
		size_t _idx;
	public:
		Iterator_Cycle(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Pingpong
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Pingpong : public IteratorBase {
	private:
		size_t _idx;
	public:
		Iterator_Pingpong(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Fold
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Fold : public IteratorBase {
	private:
		size_t _idx;
	public:
		Iterator_Fold(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Permutation
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Permutation : public IteratorBase {
	private:
		size_t _idx;
	public:
		Iterator_Permutation(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
	//--------------------------------------------------------------------------
	// ValueTypedOwner::Iterator_Combination
	//--------------------------------------------------------------------------
	class GURAX_DLLDECLARE Iterator_Combination : public IteratorBase {
	private:
		size_t _idx;
	public:
		Iterator_Combination(ValueTypedOwner* pValueTypedOwner) : IteratorBase(pValueTypedOwner), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual Value* DoNextValue() override;
		virtual size_t GetLength() const override { return GetValueOwner().size(); }
		virtual String ToString(const StringStyle& ss) const override;
	};
private:
	VType* _pVTypeOfElems;	// set to "undefined", "any" or the other specific class
	RefPtr<ValueOwner> _pValueOwner;
public:
	// Constructor
	ValueTypedOwner();
	ValueTypedOwner(VType* pVTypeOfElems, ValueOwner* pValueOwner) :
		_pVTypeOfElems(pVTypeOfElems), _pValueOwner(pValueOwner) {}
	ValueTypedOwner(ValueOwner* pValueOwner) :
		ValueTypedOwner(pValueOwner->GetVTypeOfElems(), pValueOwner) {}
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
	ValueTypedOwner* Clone() const;
	ValueTypedOwner* CloneDeep() const {
		return new ValueTypedOwner(_pVTypeOfElems, _pValueOwner->CloneDeep());
	}
	bool IsEmpty() const { return _pValueOwner->empty(); }
	size_t GetSize() const { return _pValueOwner->size(); }
	void Reserve(size_t size) { _pValueOwner->reserve(size); }
	void Set(size_t pos, Value* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		_pValueOwner->Set(pos, pValue);
	}
	Value* Get(size_t pos) const { return _pValueOwner->Get(pos); }
	bool IndexSet(const Value* pValueIndex, Value* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		return _pValueOwner->IndexSet(pValueIndex, pValue);
	}
	bool IndexGet(const Value* pValueIndex, Value** ppValue) const {
		return _pValueOwner->IndexGet(pValueIndex, ppValue);
	}
	void Add(Value* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		_pValueOwner->push_back(pValue);
	}
	void Append(const ValueTypedOwner& values);
	void Append(Iterator& iterator);
	void UpdateVTypeOfElems(VType& vtypeAdded);
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
	VType* GetVTypeOfElems() const { return _pVTypeOfElems; }
	bool HasDeterminedVTypeOfElems() const;
};

}

#endif
