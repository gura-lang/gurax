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
	ValueTypedOwner* Extract(size_t n) const {
		return new ValueTypedOwner(_pValueOwner->Extract(n));
	}
	template<typename T_Num>
	ValueTypedOwner* Extract(NumList<T_Num>& indices) const {
		return new ValueTypedOwner(_pValueOwner->Extract<T_Num>(indices));
	}
	template<typename T_Num>
		ValueTypedOwner* Extract(NumList<T_Num>& indices, size_t n) const {
		return new ValueTypedOwner(_pValueOwner->Extract<T_Num>(indices, n));
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
	Value* Shift() { return GetValueOwner().Shift(); }
	void UpdateVTypeOfElems(const Value& value);
	void UpdateVTypeOfElems(VType& vtypeAdded);
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
	ValueOwner& GetValueOwnerToSort() { return *_pValueOwner; }
	ValueOwner* GetValueOwnerReference() const { return _pValueOwner->Reference(); }
	VType& GetVTypeOfElems() const { return *_pVTypeOfElems; }
	bool CheckPosition(Int pos) const { return GetValueOwner().CheckPosition(pos); }
	bool FixPosition(Int* pPos) const { return GetValueOwner().FixPosition(pPos); }
	bool HasDeterminedVTypeOfElems() const;
	Iterator* GenerateIterator() const;
private:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
};

}

#endif
