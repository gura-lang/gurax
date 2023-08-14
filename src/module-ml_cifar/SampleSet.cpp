//==============================================================================
// SampleSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// SampleSet
//------------------------------------------------------------------------------
SampleSet::SampleSet(bool superClassFlag) : _superClassFlag(superClassFlag), _nSamples(0),
							_pLabelSet(new LabelSet()), _pImageSet(new ImageSet())
{
}

bool SampleSet::Read(Stream& stream)
{
	struct Pack {
		UInt8 labelSuper;
		UInt8 label;
	};
	UInt8 buffImage[ImageSet::nChannels * ImageSet::nRowsImage * ImageSet::nColsImage];
	for (;;) {
		if (_superClassFlag) {
			Pack pack;
			size_t bytesRead = stream.Read(&pack, sizeof(pack));
			if (bytesRead == 0) break;
			if (bytesRead != sizeof(pack)) return false;
			_pLabelSet->Add(pack.labelSuper, pack.label);
		} else {
			UInt8 label;
			size_t bytesRead = stream.Read(&label, sizeof(label));
			if (bytesRead == 0) break;
			_pLabelSet->Add(label);
		}
		if (stream.Read(buffImage, sizeof(buffImage)) < sizeof(buffImage)) return false;
		_pImageSet->Add(buffImage, sizeof(buffImage));
		_nSamples++;
	}
	_indices.reserve(_nSamples);
	for (size_t i = 0; i < _nSamples; i++) _indices.push_back(i);
	return true;
}

String SampleSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.SampleSet:%zusamples:%zuchannels:%zurows:%zucols:%zuclasses:%zusuper-classes",
		_nSamples, ImageSet::nChannels, ImageSet::nRowsImage, ImageSet::nColsImage, GetLabelSet().GetNClasses(), GetLabelSet().GetNClassesSuper());
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

#if 0
//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachBatch : public Iterator {
private:
	RefPtr<SampleSet> _pSampleSet;
	RefPtr<Array> _pArrayImage;
	RefPtr<Array> _pArrayLabel;
	size_t _batchSize;
	Double _numCeil;
	size_t _idx;
public:
	Iterator_EachBatch(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};
#endif

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
	return _pSampleSet->GetNSamples() / nChars;
}

Value* Iterator_Each::DoNextValue()
{
	size_t nChars = (_batchSize == 0)? 1 : _batchSize;
	if (_idx + nChars > _pSampleSet->GetNSamples()) return nullptr;
	RefPtr<Sample> pSample(new Sample(_pSampleSet->Reference(), _elemType, _numCeil, _format, _idx, _batchSize));
	_idx += nChars;
	return new Value_Sample(pSample.release());
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.Each:%zu/%zu", _idx, _pSampleSet->GetNSamples());
}

#if 0
//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
Iterator_EachBatch::Iterator_EachBatch(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil) :
	_pSampleSet(pSampleSet),
	_pArrayImage(Array::Create(elemType, DimSizes(batchSize, pSampleSet->GetImageSet().GetNRows(), pSampleSet->GetImageSet().GetNCols()))),
	_pArrayLabel(Array::Create(elemType, DimSizes(batchSize, pSampleSet->GetLabelSet().GetNClasses()))),
	_batchSize(batchSize), _numCeil(numCeil), _idx(0)
{
}

size_t Iterator_EachBatch::GetLength() const
{
	return _pSampleSet->GetImageSet().GetNSamples() / _batchSize;
}

Value* Iterator_EachBatch::DoNextValue()
{
	if (_idx + _batchSize > _pSampleSet->GetImageSet().GetNSamples()) return nullptr;
	void* pImageDst = _pArrayImage->GetPointerC<void>();
	_pArrayLabel->FillZero();
	size_t offset = 0;
	size_t nElems = _pSampleSet->GetImageSet().GetNRows() * _pSampleSet->GetImageSet().GetNCols();
	size_t nClasses = _pSampleSet->GetLabelSet().GetNClasses();
	for (size_t i = 0; i < _batchSize; i++, _idx++) {
		size_t iSample = _pSampleSet->GetIndex(_idx);
		_pSampleSet->GetImageSet().Extract(_pArrayImage->GetElemType(), pImageDst, iSample, _numCeil);
		UInt32 label = _pSampleSet->GetLabelSet().GetLabel(iSample);
		_pArrayLabel->IndexSetDouble(offset + label, 1.);
		pImageDst = _pArrayImage->FwdPointer(pImageDst, nElems);
		offset += nClasses;
	}
	return Value_Tuple::Create(new Value_Array(_pArrayImage->Reference()), new Value_Array(_pArrayLabel->Reference()));
}

String Iterator_EachBatch::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.EachBatch:batchSize=%zu:%zu/%zu",
		_batchSize, _idx / _batchSize, _pSampleSet->GetImageSet().GetNSamples() / _batchSize);
}
#endif

Gurax_EndModuleScope(ml_cifar)
