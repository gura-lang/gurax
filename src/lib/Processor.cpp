//==============================================================================
// Processor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
Processor::Processor() :
	_pValueStack(new ValueStack()), _pFrame(Context::GetFrame().Reference())
{
}

void Processor::Run(const PUnit* pPUnit)
{
	while (pPUnit) {
		pPUnit = pPUnit->Exec(*this);
	}
}

void Processor::DebugRun(const PUnit* pPUnit)
{
	while (pPUnit) {
		::printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
		pPUnit = pPUnit->Exec(*this);
		::printf("%s\n", GetValueStack().ToString().c_str());
	}
}

}
