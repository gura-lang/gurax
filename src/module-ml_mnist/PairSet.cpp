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

//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
Iterator_EachBatch::Iterator_EachBatch(PairSet* pPairSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil) :
	_pPairSet(pPairSet),
	_pArrayImage(Array::Create(elemType, DimSizes(batchSize, pPairSet->GetImageSet().GetNRows(), pPairSet->GetImageSet().GetNCols()))),
	_pArrayLabel(Array::Create(elemType, DimSizes(batchSize, pPairSet->GetLabelSet().GetNClasses()))),
	_batchSize(batchSize), _numCeil(numCeil), _idx(0)
{
}

size_t Iterator_EachBatch::GetLength() const
{
	return _pPairSet->GetImageSet().GetNSamples() / _batchSize;
}

Value* Iterator_EachBatch::DoNextValue()
{
	void* pImageDst = _pArrayImage->GetPointerC<void>();
	_pArrayLabel->FillZero();
	size_t offset = 0;
	size_t nElems = _pPairSet->GetImageSet().GetNRows() * _pPairSet->GetImageSet().GetNCols();
	size_t nClasses = _pPairSet->GetLabelSet().GetNClasses();
	for (size_t i = 0; i < _batchSize; i++, _idx++) {
		size_t iSample = _pPairSet->GetIndex(_idx);
		_pPairSet->GetImageSet().Extract(_pArrayImage->GetElemType(), pImageDst, iSample, _numCeil);
		UInt32 label = _pPairSet->GetLabelSet().GetLabel(iSample);
		_pArrayLabel->IndexSetDouble(offset + label, 1.);
		pImageDst = _pArrayImage->FwdPointer(pImageDst, nElems);
		offset += nClasses;
	}
	return Value_Tuple::Create(new Value_Array(_pArrayImage->Reference()), new Value_Array(_pArrayLabel->Reference()));
}

String Iterator_EachBatch::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.EachBatch:batchSize=%zu", _batchSize);
}

Gurax_EndModuleScope(ml_mnist)
