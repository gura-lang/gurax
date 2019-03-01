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
			::printf("error: %s\n", Error::GetLastError()->GetText());
			break;
		}
		if (!_pPUnitCur) {
			_pPUnitCur = _punitStack.empty()? nullptr : _punitStack.Pop();
		}
		pPUnit = _pPUnitCur;
	}
}

}
