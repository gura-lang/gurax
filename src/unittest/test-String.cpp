//==============================================================================
// test-String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(String)
{
	StringList names;
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		::printf("%-20s %08zx\n", pSampleRecord->name, String::CalcHash(pSampleRecord->name));
		names.push_back(pSampleRecord->name);
	}
	for (auto name : names) ::printf("%s\n", name.c_str());
	::printf("[Sort in ascending order]\n");
	names.Sort();
	for (auto name : names) ::printf("%s\n", name.c_str());
	::printf("[Sort in descending order]\n");
	names.Sort(SortOrder::Descend);
	for (auto name : names) ::printf("%s\n", name.c_str());
}

}
