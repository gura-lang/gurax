//==============================================================================
// SampleSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// SampleSet
//------------------------------------------------------------------------------
SampleSet::SampleSet(ImageSet* pImageSet, LabelSet* pLabelSet) : _pImageSet(pImageSet), _pLabelSet(pLabelSet)
{
	_indices.reserve(pImageSet->GetNSamples());
	for (size_t i = 0; i < pImageSet->GetNSamples(); i++) _indices.push_back(i);
}

String SampleSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.SampleSet:%zusamples:%zurows:%zucols:%zuclasses",
		GetImageSet().GetNSamples(), GetImageSet().GetNRows(), GetImageSet().GetNCols(), GetLabelSet().GetNClasses());
}

//------------------------------------------------------------------------------
// SampleSetList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SampleSetOwner
//------------------------------------------------------------------------------
void SampleSetOwner::Clear()
{
	for (SampleSet* pSampleSet : *this) SampleSet::Delete(pSampleSet);
	clear();
}

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
Iterator_Each::Iterator_Each(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format& format) :
	_pSampleSet(pSampleSet), _elemType(elemType), _numCeil(numCeil), _format(format), _idx(0)
{
}

size_t Iterator_Each::GetLength() const
{
	return _pSampleSet->GetImageSet().GetNSamples();
}

Value* Iterator_Each::DoNextValue()
{
	if (_idx >= _pSampleSet->GetImageSet().GetNSamples()) return nullptr;
	size_t iSample = _pSampleSet->GetIndex(_idx);
	_idx++;
	return new Value_Sample(new Sample(_pSampleSet->Reference(), _elemType, _numCeil, _format, iSample));
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.Each:%zu/%zu", _idx, _pSampleSet->GetImageSet().GetNSamples());
}

//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
Iterator_EachBatch::Iterator_EachBatch(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil, const Image::Format& format) :
	_pSampleSet(pSampleSet), _batchSize(batchSize), _numCeil(numCeil), _format(format), _idx(0)
{
}

size_t Iterator_EachBatch::GetLength() const
{
	return _pSampleSet->GetImageSet().GetNSamples() / _batchSize;
}

Value* Iterator_EachBatch::DoNextValue()
{
	if (_idx + _batchSize > _pSampleSet->GetImageSet().GetNSamples()) return nullptr;
	size_t iSample = _pSampleSet->GetIndex(_idx);
	_idx += _batchSize;
	return new Value_Sample(new Sample(_pSampleSet->Reference(), _elemType, _numCeil, _format, iSample));
}

String Iterator_EachBatch::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.EachBatch:batchSize=%zu:%zu/%zu",
		_batchSize, _idx / _batchSize, _pSampleSet->GetImageSet().GetNSamples() / _batchSize);
}

Gurax_EndModuleScope(ml_mnist)
