//==============================================================================
// ThreadCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ThreadCustom
//------------------------------------------------------------------------------
ThreadCustom::ThreadCustom(Processor& processor, Function* pFunction, Argument* pArgument) :
	_pProcessor(processor.CreateSubProcessor()), _pFunction(pFunction), _pArgument(pArgument)
{
}

void ThreadCustom::Run()
{
	Value::Delete(_pFunction->Eval(*_pProcessor, *_pArgument));
}

}
