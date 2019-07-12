//==============================================================================
// ValueTypedOwner.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueTypedOwner
//------------------------------------------------------------------------------
ValueTypedOwner::ValueTypedOwner() :
	_pVTypeOfElems(&VTYPE_Undefined), _pValueOwner(new ValueOwner())
{}

void ValueTypedOwner::Clear()
{
	_pVTypeOfElems = &VTYPE_Undefined;
	_pValueOwner->Clear();
}

void ValueTypedOwner::Append(const ValueTypedOwner& values)
{
	for (const Value* pValue : values.GetValueOwner()) {
		Add(pValue->Reference());
	}
}

void ValueTypedOwner::Append(Iterator& iterator)
{
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		Add(pValue->Reference());
	}
}

void ValueTypedOwner::UpdateVTypeOfElems(VType& vtypeAdded)
{
	if (_pVTypeOfElems->IsIdentical(VTYPE_Undefined)) {
		_pVTypeOfElems = &vtypeAdded;
	} else if (!_pVTypeOfElems->IsIdentical(vtypeAdded)) {
		_pVTypeOfElems = &VTYPE_Any;
	}
}

bool ValueTypedOwner::HasDeterminedVTypeOfElems() const
{
	return !_pVTypeOfElems->IsIdentical(VTYPE_Undefined) && !_pVTypeOfElems->IsIdentical(VTYPE_Any);
}

}
