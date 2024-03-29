//==============================================================================
// Linear.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Linear
//------------------------------------------------------------------------------
Linear::Linear(size_t nColsOut, bool enableBiasFlag) :
	Gear(true), _nColsOut(nColsOut), _enableBiasFlag(enableBiasFlag),
	_pArrayWeight(Array::none()), _pArrayBias(Array::none())
{
}

Linear::Linear(size_t nColsOut, bool enableBiasFlag, Array* pArrayWeight, Array* pArrayBias) :
	Gear(true), _nColsOut(nColsOut), _enableBiasFlag(enableBiasFlag),
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
	const Array::ElemTypeT& elemType = arrayFwdIn.GetElemType();
	if (_pArrayWeight->IsNone()) {
		_pArrayWeight.reset(Array::Create(elemType, DimSizes(nColsIn, _nColsOut)));
		if (controller.IsTraining()) _pArrayWeight->FillRandomNormal(0, ::sqrt(1. / nColsIn), controller.GetRandom());
	}
	if (!Array::Dot(_pArrayFwd1, arrayFwdIn, *_pArrayWeight)) return false;
	if (_pArrayBias->IsNone()) {
		_pArrayBias.reset(Array::Create(elemType, DimSizes(_nColsOut)));
		if (controller.IsTraining()) _pArrayBias->FillRandomNormal(0, ::sqrt(1. / nColsIn), controller.GetRandom());
	}
	return Array::Add(pArrayFwdOut, *_pArrayFwd1, *_pArrayBias);
}

bool Linear::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (bwdPropagationFlag) {
		// pArrayBwdOut = arrayBwdIn |.| T(_pArrayWeight)
		if (!Array::Dot(pArrayBwdOut, arrayBwdIn, *_pArrayWeight, false, true)) return false;
	}
	// _pArrayWeightGrad = T(_pArrayFwdIn) |.| arrayBwdIn
	if (!Array::Dot(_pArrayWeightGrad, *_pArrayFwdIn, arrayBwdIn, true, false)) return false;
	if (!_pOptimizerInstWeight->Update(processor, _pArrayWeight, *_pArrayWeightGrad)) return false;
	if (_pArrayBias->IsNone()) return true;
	_pArrayBiasGrad.reset(arrayBwdIn.Reference());
	return _pOptimizerInstBias->Update(processor, _pArrayBias, *_pArrayBiasGrad);
}

String Linear::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Linear:%s:%s:%s", _enableBiasFlag? "bias" : "noBias",
					_pArrayWeight->ToString(StringStyle::Brief).c_str(),
					_pArrayBias->ToString(StringStyle::Brief).c_str());
}

bool Linear::Serialize(Stream& stream) const
{
	if (!stream.SerializePackedNumber<size_t>(_nColsOut)) return false;
	if (!stream.SerializeNumber<bool>(_enableBiasFlag)) return false;
	if (!_pArrayWeight->Serialize(stream)) return false;
	if (!_pArrayBias->Serialize(stream)) return false;
	return true;
}

Linear* Linear::Deserialize(Stream& stream)
{
	size_t nColsOut;
	bool enableBiasFlag;
	if (!stream.DeserializePackedNumber<size_t>(nColsOut)) return nullptr;
	if (!stream.DeserializeNumber<bool>(enableBiasFlag)) return nullptr;
	RefPtr<Array> pArrayWeight(Array::Deserialize(stream));
	if (!pArrayWeight) return nullptr;
	RefPtr<Array> pArrayBias(Array::Deserialize(stream));
	if (!pArrayBias) return nullptr;
	return new Linear(nColsOut, enableBiasFlag, pArrayWeight.release(), pArrayBias.release());
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
