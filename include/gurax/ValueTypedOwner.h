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
