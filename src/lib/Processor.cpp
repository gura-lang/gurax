//==============================================================================
// Processor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
Processor::Processor() :
	_pValueStack(new ValueStack()), _pFrameStack(new FrameStack())
{
	GetPUnitStack().reserve(1024);
	GetValueStack().reserve(1024);
	GetFrameStack().reserve(1024);
	GetFrameStack().Push(Context::GetFrame().Reference());
}

Processor* Processor::Normal()
{
	return new Processor_Normal();
}

Processor* Processor::Debug()
{
	return new Processor_Debug();
}

void Processor::Call(const PUnit* pPUnit, Argument& argument)
{
	argument.AssignToFrame(PushFrame_Function());
	Run(pPUnit);
}

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
void Processor_Normal::Run(const PUnit* pPUnit)
{
	while (pPUnit) {
		pPUnit = pPUnit->Exec(*this);
	}
}

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
void Processor_Debug::Run(const PUnit* pPUnit)
{
	while (pPUnit) {
		::printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
		pPUnit = pPUnit->Exec(*this);
		::printf("%s\n", GetValueStack().ToString().c_str());
	}
}

}
