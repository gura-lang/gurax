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
	if (pPUnit->GetPUnitSentinel()) {
		const PUnit* pPUnitSentinel = pPUnit->GetPUnitSentinel();
		pPUnit = pPUnit->GetPUnitCont();	// skip PUnit_BeginQuote
		while (pPUnit && pPUnit != pPUnitSentinel) pPUnit = pPUnit->Exec(*this);
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
	const PUnit* pPUnitSentinel = nullptr;
	if (pPUnit->GetPUnitSentinel()) {
		pPUnitSentinel = pPUnit->GetPUnitSentinel();
		pPUnit = pPUnit->GetPUnitCont();	// skip PUnit_BeginQuote
	} else {
		PrintPUnit(stream, pPUnit);
		pPUnit = pPUnit->Exec(*this);
	}
	while (pPUnit && pPUnit != pPUnitSentinel) {
		PrintStack(stream);
		PrintPUnit(stream, pPUnit);
		pPUnit = pPUnit->Exec(*this);
	}
}

}
