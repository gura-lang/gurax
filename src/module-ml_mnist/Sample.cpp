//==============================================================================
// Sample.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Sample
//------------------------------------------------------------------------------
Sample::Sample(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format& format, size_t idx, size_t batchSize) :
		_pSampleSet(pSampleSet), _elemType(elemType), _numCeil(numCeil), _format(format), _idx(idx), _batchSize(batchSize)
{
}

const Array& Sample::GetArrayInput()
{
	_pSampleSet->GetImageSet().ExtractAsArray(_pArrayInput, *_pSampleSet, _elemType, _numCeil, _idx, _batchSize);
	return *_pArrayInput;
}

const Array& Sample::GetArrayResult()
{
	size_t nClasses = _pSampleSet->GetLabelSet().GetNClasses();
	if (_pArrayResult) {
		// nothing to do
	} else if (_batchSize == 0) {
		_pArrayResult.reset(Array::Create(_elemType, DimSizes(nClasses)));
		_pArrayResult->IndexSetDouble(GetLabel(_idx), 1.);
	} else {
		_pArrayResult.reset(Array::Create(_elemType, DimSizes(_batchSize, nClasses)));
		for (size_t i = 0; i < _batchSize; i++) {
			_pArrayResult->IndexSetDouble(i * nClasses + GetLabel(_idx + i), 1.);
		}
	}
	return *_pArrayResult;
}

const Image& Sample::GetImage()
{
	_pSampleSet->GetImageSet().ExtractAsImage(_pImage, *_pSampleSet, _format, _idx, _batchSize);
	return *_pImage;
}

UInt32 Sample::GetLabel(size_t idx) const
{
	return _pSampleSet->GetLabelSet().GetLabel(_pSampleSet->GetIndex(idx));
}

String Sample::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.Sample");
}

//------------------------------------------------------------------------------
// SampleList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SampleOwner
//------------------------------------------------------------------------------
void SampleOwner::Clear()
{
	for (Sample* pSample : *this) Sample::Delete(pSample);
	clear();
}

Gurax_EndModuleScope(ml_mnist)
