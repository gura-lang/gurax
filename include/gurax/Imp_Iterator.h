//==============================================================================
// Imp_Iterator.h
//==============================================================================
#ifndef GURAX_IMP_ITERATOR_H
#define GURAX_IMP_ITERATOR_H
#include "Iterator.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
template<typename T_Compare> Value* Iterator::FindMinMax()
{
	RefPtr<Value> pValueFound(NextValue());
	if (!pValueFound) return nullptr;
	for (;;) {
		RefPtr<Value> pValue(NextValue());
		if (!pValue) break;
		if (T_Compare()(pValueFound.get(), pValue.get())) pValueFound.reset(pValue.release());
	}
	return pValueFound.release();
}

template<typename T_Compare> Value* Iterator::FindMinMax(Int* pIdxFound)
{
	*pIdxFound = 0;
	RefPtr<Value> pValueFound(NextValue());
	if (!pValueFound) return nullptr;
	for (Int idx = 1; ; idx++) {
		RefPtr<Value> pValue(NextValue());
		if (!pValue) break;
		if (T_Compare()(pValueFound.get(), pValue.get())) {
			*pIdxFound = idx;
			pValueFound.reset(pValue.release());
		}
	}
	return pValueFound.release();
}

template<typename T_Compare> Value* Iterator::FindMinMax(NumList<Int>& idxFoundList)
{
	RefPtr<Value> pValueFound(NextValue());
	if (!pValueFound) return nullptr;
	idxFoundList.push_back(0);
	for (Int idx = 1; ; idx++) {
		RefPtr<Value> pValue(NextValue());
		if (!pValue) break;
		if (pValueFound->IsEqualTo(*pValue)) {
			idxFoundList.push_back(idx);
		} else if (T_Compare()(pValueFound.get(), pValue.get())) {
			idxFoundList.clear();
			idxFoundList.push_back(idx);
			pValueFound.reset(pValue.release());
		}
	}
	return pValueFound.release();
}

}

#endif

