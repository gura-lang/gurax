//==============================================================================
// Iterators.h
//==============================================================================
#ifndef GURAX_ITERATORS_H
#define GURAX_ITERATORS_H
#include "Iterator.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Each : public Iterator {
private:
	RefPtr<ValueTypedOwner> _pValueTypedOwner;
	size_t _idx;
public:
	Iterator_Each(ValueTypedOwner* pValueTypedOwner) : _pValueTypedOwner(pValueTypedOwner), _idx(0) {}
	const ValueOwner& GetValueOwner() const { return _pValueTypedOwner->GetValueOwner(); }
	virtual Value* Next() override {
		const ValueOwner& valueOwner = GetValueOwner();
		return (_idx < valueOwner.size())? valueOwner[_idx++] : nullptr;
	}
};

}

#endif
