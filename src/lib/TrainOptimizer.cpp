//==============================================================================
// TrainOptimizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainOptimizer
//------------------------------------------------------------------------------
String TrainOptimizer::ToString(const StringStyle& ss) const
{
	return String().Format("TrainOptimizer");
}

//------------------------------------------------------------------------------
// TrainOptimizerList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TrainOptimizerOwner
//------------------------------------------------------------------------------
void TrainOptimizerOwner::Clear()
{
	for (TrainOptimizer* pTrainOptimizer : *this) TrainOptimizer::Delete(pTrainOptimizer);
	clear();
}

//------------------------------------------------------------------------------
// TrainOptimizer_None
//-------------------------------------------------------------------------
void TrainOptimizer_None::Reset()
{
}

bool TrainOptimizer_None::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// TrainOptimizer_AdaGrad
//------------------------------------------------------------------------------
void TrainOptimizer_AdaGrad::Reset()
{
}

bool TrainOptimizer_AdaGrad::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// TrainOptimizer_Adam
//------------------------------------------------------------------------------
void TrainOptimizer_Adam::Reset()
{
}

bool TrainOptimizer_Adam::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// TrainOptimizer_GradientDescent
//------------------------------------------------------------------------------
void TrainOptimizer_GradientDescent::Reset()
{
}

bool TrainOptimizer_GradientDescent::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	// _pArrayWork <- arrayGrad * _learningRate
	if (!Array::Mul(_pArrayWork, arrayGrad, _learningRate)) return false;
	// pArray <- pArray - _pArrayWork
	if (!Array::Sub(pArray, *pArray, *_pArrayWork)) return false;
	return true;
}

//------------------------------------------------------------------------------
// TrainOptimizer_Momentum
//------------------------------------------------------------------------------
void TrainOptimizer_Momentum::Reset()
{
}

bool TrainOptimizer_Momentum::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	// _pArrayWork <- pArrayGrad * _learningRate
	if (!Array::Mul(_pArrayWork, arrayGrad, _learningRate)) return false;
	// _pArrayVel <- _pArrayVel * _momentum
	if (_pArrayVel.IsNull()) _pArrayVel.reset(_pArrayWork->CreateLike());
	if (!Array::Mul(_pArrayVel, *_pArrayVel, _momentum)) return false;
	// _pArrayVel <- _pArrayVel - _pArrayWork
	if (!Array::Sub(_pArrayVel, *_pArrayVel, *_pArrayWork)) return false;
	// pArray <- pArray + _pArrayVel
	if (!Array::Add(pArray, *pArray, *_pArrayVel)) return false;
	return true;
}

//------------------------------------------------------------------------------
// TrainOptimizer_Nesterov
//------------------------------------------------------------------------------
void TrainOptimizer_Nesterov::Reset()
{
}

bool TrainOptimizer_Nesterov::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// TrainOptimizer_RMSprop
//------------------------------------------------------------------------------
void TrainOptimizer_RMSprop::Reset()
{
}

bool TrainOptimizer_RMSprop::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

}
