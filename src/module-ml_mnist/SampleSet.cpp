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
Iterator_Each::Iterator_Each(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format& format, size_t batchSize) :
	_pSampleSet(pSampleSet), _elemType(elemType), _numCeil(numCeil), _format(format), _batchSize(batchSize), _idx(0)
{
}

size_t Iterator_Each::GetLength() const
{
	size_t nChars = (_batchSize == 0)? 1 : _batchSize;
	return _pSampleSet->GetImageSet().GetNSamples() / nChars;
}

Value* Iterator_Each::DoNextValue()
{
	size_t nChars = (_batchSize == 0)? 1 : _batchSize;
	if (_idx + nChars > _pSampleSet->GetImageSet().GetNSamples()) return nullptr;
	RefPtr<Sample> pSample(new Sample(_pSampleSet->Reference(), _elemType, _numCeil, _format, _idx, _batchSize));
	_idx += nChars;
	return new Value_Sample(pSample.release());
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.Each:%zu/%zu", _idx, _pSampleSet->GetImageSet().GetNSamples());
}

Gurax_EndModuleScope(ml_mnist)
