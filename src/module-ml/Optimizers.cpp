//==============================================================================
// Optimizers.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Optimizer_None
//-------------------------------------------------------------------------
void Optimizer_None::InstanceEx::Reset()
{
}

bool Optimizer_None::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// Optimizer_AdaGrad
//------------------------------------------------------------------------------
void Optimizer_AdaGrad::InstanceEx::Reset()
{
}

bool Optimizer_AdaGrad::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// Optimizer_Adam
//------------------------------------------------------------------------------
void Optimizer_Adam::InstanceEx::Reset()
{
}

bool Optimizer_Adam::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// Optimizer_GradientDescent
//------------------------------------------------------------------------------
void Optimizer_GradientDescent::GatherMemberSymbol(SymbolList& symbolList) const
{
	symbolList.push_back(Gurax_Symbol(learningRate));
}

Value* Optimizer_GradientDescent::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(learningRate))) {
		return new Value_Number(_learningRate);
	}
	return nullptr;
}

bool Optimizer_GradientDescent::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(learningRate))) {
		if (pValue->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "property learningRate is a Number value");
			return false;
		}
		_learningRate = Value_Number::GetNumberPos<Double>(*pValue);
		return true;
	}
	return false;
}

void Optimizer_GradientDescent::InstanceEx::Reset()
{
}

bool Optimizer_GradientDescent::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	// _pArrayWork <- arrayGrad * _learningRate
	if (!Array::Mul(_pArrayWork, arrayGrad, _learningRate)) return false;
	// pArray <- pArray - _pArrayWork
	if (!Array::ReduceSub(pArray, *pArray, *_pArrayWork)) return false;
	return true;
}

//------------------------------------------------------------------------------
// Optimizer_Momentum
//------------------------------------------------------------------------------
void Optimizer_Momentum::InstanceEx::Reset()
{
}

bool Optimizer_Momentum::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	// _pArrayWork <- pArrayGrad * _learningRate
	if (!Array::Mul(_pArrayWork, arrayGrad, _learningRate)) return false;
	// _pArrayVel <- _pArrayVel * _momentum
	if (_pArrayVel.IsNull()) _pArrayVel.reset(_pArrayWork->CreateLike());
	if (!Array::Mul(_pArrayVel, *_pArrayVel, _momentum)) return false;
	// _pArrayVel <- _pArrayVel - _pArrayWork
	if (!Array::Sub(_pArrayVel, *_pArrayVel, *_pArrayWork)) return false;
	// pArray <- pArray + _pArrayVel
	if (!Array::ReduceAdd(pArray, *pArray, *_pArrayVel)) return false;
	return true;
}

//------------------------------------------------------------------------------
// Optimizer_Nesterov
//------------------------------------------------------------------------------
void Optimizer_Nesterov::InstanceEx::Reset()
{
}

bool Optimizer_Nesterov::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

//------------------------------------------------------------------------------
// Optimizer_RMSprop
//------------------------------------------------------------------------------
void Optimizer_RMSprop::InstanceEx::Reset()
{
}

bool Optimizer_RMSprop::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

Gurax_EndModuleScope(ml)
