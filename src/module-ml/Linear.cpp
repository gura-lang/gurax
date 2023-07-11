//==============================================================================
// Linear.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Linear
//------------------------------------------------------------------------------
Linear::Linear(size_t nColsOut, const Array::ElemTypeT& elemType) :
	Gear(true), _elemType(elemType), _nColsOut(nColsOut)
{
}

Linear::Linear(Array* pArrayWeight, Array* pArrayBias) :
	Gear(true), _elemType(pArrayWeight->GetElemType()), _nColsOut(pArrayWeight->GetDimSizes().GetColSize()),
	_pArrayWeight(pArrayWeight), _pArrayBias(pArrayBias)
{
}

void Linear::Initialize()
{
}

bool Linear::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag)
{
	if (!_pArrayWeight) {
		size_t nColsIn = arrayFwdIn.GetDimSizes().GetColSize();
		_pArrayWeight.reset(Array::Create(_elemType, DimSizes(nColsIn, _nColsOut)));
		_pArrayBias.reset(Array::Create(_elemType, DimSizes(_nColsOut)));
		Double stddev = ::sqrt(1 / nColsIn);
		_pArrayWeight->FillRandomNormal(Random::Global(), 0, stddev);
		_pArrayBias->FillRandomNormal(Random::Global(), 0, stddev);
	}
	_pArrayFwdIn.reset(arrayFwdIn.Reference());
	if (!Array::Dot(_pArrayFwd1, arrayFwdIn, *_pArrayWeight)) return false;
	return Array::Add(pArrayFwdOut, *_pArrayFwd1, *_pArrayBias);
}

bool Linear::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	_pArrayBiasGrad.reset(arrayBwdIn.Reference());
	if (bwdPropagationFlag) {
		// pArrayBwdOut = arrayBwdIn |.| transpose(_pArrayWeight)
		_pArrayWeight->Transpose2d(_pArrayWeightTrans);
		if (!Array::Dot(pArrayBwdOut, arrayBwdIn, *_pArrayWeightTrans)) return false;
	}
	do {
		// _pArrayWeightGrad = transpose(_pArrayFwdIn) |.| arrayBwdIn
		_pArrayFwdIn->Transpose2d(_pArrayFwdInTrans);
		if (!Array::Dot(_pArrayWeightGrad, *_pArrayFwdInTrans, arrayBwdIn)) return false;
	} while (0);
	return _pOptimizerInstWeight->Update(processor, _pArrayWeight, *_pArrayWeightGrad) &&
			 _pOptimizerInstBias->Update(processor, _pArrayBias, *_pArrayBiasGrad);
}

String Linear::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Linear");
}

bool Linear::Serialize(Stream& stream) const
{
	if (!_pArrayWeight->Serialize(stream)) return false;
	if (!_pArrayBias->Serialize(stream)) return false;
	return true;
}

Linear* Linear::Deserialize(Stream& stream)
{
	RefPtr<Array> pArrayWeight(Array::Deserialize(stream));
	if (!pArrayWeight) return nullptr;
	RefPtr<Array> pArrayBias(Array::Deserialize(stream));
	if (!pArrayBias) return nullptr;
	return new Linear(pArrayWeight.release(), pArrayBias.release());
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
