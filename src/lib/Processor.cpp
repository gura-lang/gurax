//==============================================================================
// Processor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
Processor::Processor() :
	_pPUnitCur(nullptr), _pValueStack(new ValueStack()), _pFrame(Context::GetFrame().Reference())
{
}

void Processor::Run(const PUnit* pPUnit)
{
	while (pPUnit) {
		_pPUnitCur = nullptr;
		//::printf("%s\n", pPUnit->ToString().c_str());
		pPUnit->Exec(*this);
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			break;
		}
		pPUnit = _pPUnitCur;
	}
}

}
