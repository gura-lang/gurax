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
	if (!pPUnit) return;
	if (pPUnit->GetPUnitExit()) {
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
	auto PrintPUnit = [](Stream& stream, const PUnit* pPUnit) {
		stream.Printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
	};
	auto PrintStack = [this](Stream& stream) {
		stream.Printf("%s\n", GetValueStack().ToString(StringStyle().Digest()).c_str());
	};
	if (!pPUnit) return;
	Stream& stream = *Stream::COut;
	const PUnit* pPUnitExit = nullptr;
	if (pPUnit->GetPUnitExit()) {
		pPUnitExit = pPUnit->GetPUnitExit();
		pPUnit = pPUnit->GetPUnitCont();	// skip PUnit_ExitPoint
	} else {
		PrintPUnit(stream, pPUnit);
		pPUnit = pPUnit->Exec(*this);
	}
	while (pPUnit && pPUnit != pPUnitExit) {
		PrintStack(stream);
		PrintPUnit(stream, pPUnit);
		pPUnit = pPUnit->Exec(*this);
	}
}

}
