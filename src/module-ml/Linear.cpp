//==============================================================================
// Linear.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Linear
//------------------------------------------------------------------------------
Linear::Linear(size_t nRowsIn, size_t nColsIn, size_t nColsOut) : Gear(true), _nRowsIn(nRowsIn), _nColsIn(nColsIn), _nColsOut(nColsOut)
{
}

Linear::Linear(size_t nRowsIn, size_t nColsIn, size_t nColsOut, Array* pArrayDot, Array* pArrayBias) : Gear(true),
	_nRowsIn(nRowsIn), _nColsIn(nColsIn), _nColsOut(nColsOut), _pArrayDot(pArrayDot), _pArrayBias(pArrayBias)
{
}

void Linear::Initialize()
{
}

bool Linear::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag)
{
	_pArrayFwdIn.reset(arrayFwdIn.Reference());
	if (!Array::Dot(_pArrayFwd1, arrayFwdIn, *_pArrayDot)) return false;
	return Array::Add(pArrayFwdOut, *_pArrayFwd1, *_pArrayBias);
}

bool Linear::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	_pArrayBiasGrad.reset(arrayBwdIn.Reference());
	if (bwdPropagationFlag) {
		// pArrayBwdOut = arrayBwdIn |.| transpose(_pArrayDot)
		_pArrayDot->Transpose2d(_pArrayDotTrans);
		if (!Array::Dot(pArrayBwdOut, arrayBwdIn, *_pArrayDotTrans)) return false;
	}
	do {
		// _pArrayDotGrad = transpose(_pArrayFwdIn) |.| arrayBwdIn
		_pArrayFwdIn->Transpose2d(_pArrayFwdInTrans);
		if (!Array::Dot(_pArrayDotGrad, *_pArrayFwdInTrans, arrayBwdIn)) return false;
	} while (0);
	return _pOptimizerInstDot->Update(processor, _pArrayDot, *_pArrayDotGrad) &&
			 _pOptimizerInstBias->Update(processor, _pArrayBias, *_pArrayBiasGrad);
}

String Linear::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Linear");
}

bool Linear::Serialize(Stream& stream) const
{
	if (!stream.SerializePackedNumber<size_t>(_nRowsIn)) return false;
	if (!stream.SerializePackedNumber<size_t>(_nColsIn)) return false;
	if (!stream.SerializePackedNumber<size_t>(_nColsOut)) return false;
	if (!_pArrayDot->Serialize(stream)) return false;
	if (!_pArrayBias->Serialize(stream)) return false;
	return true;
}

Linear* Linear::Deserialize(Stream& stream)
{
	size_t nRowsIn, nColsIn, nColsOut;
	if (!stream.DeserializePackedNumber<size_t>(nRowsIn)) return nullptr;
	if (!stream.DeserializePackedNumber<size_t>(nColsIn)) return nullptr;
	if (!stream.DeserializePackedNumber<size_t>(nColsOut)) return nullptr;
	RefPtr<Array> pArrayDot(Array::Deserialize(stream));
	if (!pArrayDot) return nullptr;
	RefPtr<Array> pArrayBias(Array::Deserialize(stream));
	if (!pArrayBias) return nullptr;
	return new Linear(nRowsIn, nColsIn, nColsOut, pArrayDot.release(), pArrayBias.release());
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
