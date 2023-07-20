//==============================================================================
// Linear.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Linear
//------------------------------------------------------------------------------
Linear::Linear(size_t nColsOut, const Array::ElemTypeT& elemType, bool enableBiasFlag) :
	Gear(true), _elemType(elemType), _nColsOut(nColsOut), _enableBiasFlag(enableBiasFlag),
	_pArrayWeight(Array::none()), _pArrayBias(Array::none())
{
}

Linear::Linear(Array* pArrayWeight, Array* pArrayBias, bool enableBiasFlag) :
	Gear(true), _elemType(pArrayWeight->GetElemType()),
	_nColsOut(pArrayWeight->GetDimSizes().GetColSize()), _enableBiasFlag(enableBiasFlag),
	_pArrayWeight(pArrayWeight), _pArrayBias(pArrayBias)
{
}

void Linear::Bootup()
{
}

bool Linear::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller)
{
	size_t nColsIn = arrayFwdIn.GetDimSizes().GetColSize();
	_pArrayFwdIn.reset(arrayFwdIn.Reference());
	if (_pArrayWeight->IsNone()) {
		_pArrayWeight.reset(Array::Create(_elemType, DimSizes(nColsIn, _nColsOut)));
		if (controller.IsTraining()) _pArrayWeight->FillRandomNormal(0, ::sqrt(1. / nColsIn), controller.GetRandom());
	}
	if (!Array::Dot(_pArrayFwd1, arrayFwdIn, *_pArrayWeight)) return false;
	if (_pArrayBias->IsNone()) {
		_pArrayBias.reset(Array::Create(_elemType, DimSizes(_nColsOut)));
		if (controller.IsTraining()) _pArrayBias->FillRandomNormal(0, ::sqrt(1. / nColsIn), controller.GetRandom());
	}
	return Array::Add(pArrayFwdOut, *_pArrayFwd1, *_pArrayBias);
}

bool Linear::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (bwdPropagationFlag) {
		// pArrayBwdOut = arrayBwdIn |.| T(_pArrayWeight)
		_pArrayWeight->Transpose2d(_pArrayWeightTrans);
		if (!Array::Dot(pArrayBwdOut, arrayBwdIn, *_pArrayWeightTrans)) return false;
	}
	do {
		// _pArrayWeightGrad = T(_pArrayFwdIn) |.| arrayBwdIn
		_pArrayFwdIn->Transpose2d(_pArrayFwdInTrans);
		if (!Array::Dot(_pArrayWeightGrad, *_pArrayFwdInTrans, arrayBwdIn)) return false;
	} while (0);
	if (!_pOptimizerInstWeight->Update(processor, _pArrayWeight, *_pArrayWeightGrad)) return false;
	if (_pArrayBias->IsNone()) return true;
	_pArrayBiasGrad.reset(arrayBwdIn.Reference());
	return _pOptimizerInstBias->Update(processor, _pArrayBias, *_pArrayBiasGrad);
}

String Linear::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Linear:%s:%s", _pArrayWeight->ToString(StringStyle::Brief).c_str(),
					_pArrayBias->ToString(StringStyle::Brief).c_str());
}

bool Linear::Serialize(Stream& stream) const
{
	if (!_pArrayWeight->Serialize(stream)) return false;
	if (!_pArrayBias->Serialize(stream)) return false;
	if (!stream.SerializeNumber<bool>(_enableBiasFlag)) return false;
	return true;
}

Linear* Linear::Deserialize(Stream& stream)
{
	RefPtr<Array> pArrayWeight(Array::Deserialize(stream));
	if (!pArrayWeight) return nullptr;
	RefPtr<Array> pArrayBias(Array::Deserialize(stream));
	if (!pArrayBias) return nullptr;
	bool enableBiasFlag;
	if (!stream.DeserializeNumber<bool>(enableBiasFlag)) return nullptr;
	return new Linear(pArrayWeight.release(), pArrayBias.release(), enableBiasFlag);
}

//------------------------------------------------------------------------------
// LinearList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// LinearOwner
//------------------------------------------------------------------------------
void LinearOwner::Clear()
{
	for (Linear* pLinear : *this) Linear::Delete(pLinear);
	clear();
}

Gurax_EndModuleScope(ml)
