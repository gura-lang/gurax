//==============================================================================
// test-String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(String)
{
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		::printf("%-20s %08zx\n", pSampleRecord->name, String::CalcHash(pSampleRecord->name));
	}
}

}
