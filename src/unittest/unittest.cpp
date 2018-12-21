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
	size_t nLen = ::strlen(testerName);
	for (auto pTester : Tester::GetTesterList()) {
		if (::strncasecmp(pTester->GetName(), testerName, nLen) == 0) {
			::printf("[%s]\n", pTester->GetName());
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
