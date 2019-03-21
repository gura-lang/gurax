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
	return debugFlag?
		dynamic_cast<Processor*>(new Processor_Debug()) :
		dynamic_cast<Processor*>(new Processor_Normal());
}

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
void Processor_Normal::RunLoop(const PUnit* pPUnit)
{
	if (pPUnit && pPUnit->GetPUnitExit()) {
		const PUnit* pPUnitExit = pPUnit->GetPUnitExit();
		pPUnit = pPUnit->GetPUnitCont();	// skip PUnit_ExitPoint
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
	if (pPUnit && pPUnit->GetPUnitExit()) {
		pPUnitExit = pPUnit->GetPUnitExit();
		pPUnit = pPUnit->GetPUnitCont();	// skip PUnit_ExitPoint
	}
	while (pPUnit && pPUnit != pPUnitExit) {
		stream.Printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
		pPUnit = pPUnit->Exec(*this);
		stream.Printf("%s\n", GetValueStack().ToString(ss).c_str());
	}
}

}
