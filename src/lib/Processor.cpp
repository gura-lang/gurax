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
		//::printf("%s\n", pPUnit->ToString().c_str());
		pPUnit = pPUnit->Exec(*this);
	}
	if (Error::IsIssued()) Error::Print(*Stream::CErr);
}

}
