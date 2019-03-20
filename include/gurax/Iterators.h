//==============================================================================
// Iterators.h
//==============================================================================
#ifndef GURAX_ITERATORS_H
#define GURAX_ITERATORS_H
#include "Iterator.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator_Const
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Const : public Iterator {
private:
	RefPtr<Value> _pValue;
public:
	Iterator_Const(Value* pValue) : _pValue(pValue) {}
	virtual Value* NextValue() override { return _pValue.get(); }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_ConstN
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ConstN : public Iterator {
private:
	RefPtr<Value> _pValue;
	size_t _num;
	size_t _idx;
public:
	Iterator_ConstN(Value* pValue, size_t num) : _pValue(pValue) , _num(num), _idx(0) {}
	virtual Value* NextValue() override {
		if (_idx >= _num) return nullptr;
		_idx++;
		return _pValue.get();
	}
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Each : public Iterator {
private:
	RefPtr<ValueTypedOwner> _pValueTypedOwner;
	size_t _idx;
public:
	Iterator_Each(ValueTypedOwner* pValueTypedOwner) : _pValueTypedOwner(pValueTypedOwner), _idx(0) {}
	ValueTypedOwner& GetValueTypedOwner() { return *_pValueTypedOwner; }
	const ValueTypedOwner& GetValueTypedOwner() const { return *_pValueTypedOwner; }
	const ValueOwner& GetValueOwner() const { return GetValueTypedOwner().GetValueOwner(); }
	virtual Value* NextValue() override {
		const ValueOwner& valueOwner = GetValueOwner();
		if (_idx >= valueOwner.size()) return nullptr;
		return valueOwner[_idx++];
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
