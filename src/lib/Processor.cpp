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
	PushPUnit(nullptr);
}

Processor* Processor::Create(bool debugFlag)
{
	if (debugFlag) {
		return new Processor_Debug();
	} else {
		return new Processor_Normal();
	}
}

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
void Processor_Normal::RunLoop(const PUnit* pPUnit)
{
	const PUnit* pPUnitExit = nullptr;
	
	if (pPUnitExit) {
		while (pPUnit && pPUnit != pPUnitExit) pPUnit = pPUnit->Exec(*this);
	} else {
		while (pPUnit) pPUnit = pPUnit->Exec(*this);
	}
}

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
void Processor_Debug::RunLoop(const PUnit* pPUnit)
{
	Stream& stream = *Stream::COut;
	StringStyle ss;
	ss.Digest();
	const PUnit* pPUnitExit = nullptr;
	
	while (pPUnit && pPUnit != pPUnitExit) {
		stream.Printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
		pPUnit = pPUnit->Exec(*this);
		stream.Printf("%s\n", GetValueStack().ToString(ss).c_str());
	}
}

}
