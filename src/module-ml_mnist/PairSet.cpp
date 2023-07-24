//==============================================================================
// PairSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// PairSet
//------------------------------------------------------------------------------
PairSet::PairSet(ImageSet* pImageSet, LabelSet* pLabelSet) : _pImageSet(pImageSet), _pLabelSet(pLabelSet)
{
	_indices.reserve(pImageSet->GetNSamples());
	for (size_t i = 0; i < pImageSet->GetNSamples(); i++) _indices.push_back(i);
}

String PairSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.PairSet:%zusamples:%zurows:%zucols:%zuclasses",
		GetImageSet().GetNSamples(), GetImageSet().GetNRows(), GetImageSet().GetNCols(), GetLabelSet().GetNClasses());
}

//------------------------------------------------------------------------------
// PairSetList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PairSetOwner
//------------------------------------------------------------------------------
void PairSetOwner::Clear()
{
	for (PairSet* pPairSet : *this) PairSet::Delete(pPairSet);
	clear();
}

Gurax_EndModuleScope(ml_mnist)
