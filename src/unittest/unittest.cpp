//==============================================================================
// unittest.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

TesterList Tester::_testerList;

int Main(int argc, char* argv[])
{
	if (argc < 2) {
		for (auto pTester : Tester::GetTesterList()) {
			::fprintf(stderr, "%s\n", pTester->GetName());
		}
		return 1;
	}
	const char* testerName = argv[1];
	Bootup();
	bool foundFlag = false;
	for (auto pTester : Tester::GetTesterList()) {
		if (::strcmp(pTester->GetName(), testerName) == 0) {
			pTester->Entry(argc - 2, argv + 2);
			foundFlag = true;
			break;
		}
	}
	if (!foundFlag) {
		::fprintf(stderr, "unknown tester name %s\n", testerName);
	}
	return 0;
}

}

int main(int argc, char* argv[])
{
	return Gurax::Main(argc, argv);
}
