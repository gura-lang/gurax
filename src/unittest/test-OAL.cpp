//==============================================================================
// test-OAL.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static void Test_ParseStatMode()
{
	auto func = [](const char* mode, mode_t st_mode) {
		mode_t st_modeOld = st_mode;
		OAL::ParseStatMode(mode, st_mode);
		::printf("%-12s %03o->%03o\n", mode, st_modeOld, st_mode);
	};
	func("o+x", 0);
	func("o+w", 0);
	func("o+r", 0);
	func("g+x", 0);
	func("g+w", 0);
	func("g+r", 0);
	func("u+x", 0);
	func("u+w", 0);
	func("u+r", 0);
	func("og+x", 0);
	func("ou+x", 0);
	func("gu+x", 0);
	func("og+w", 0);
	func("ou+w", 0);
	func("gu+w", 0);
	func("og+r", 0);
	func("ou+r", 0);
	func("gu+r", 0);
	func("ogu+x", 0);
	func("ogu+w", 0);
	func("ogu+r", 0);
	func("a+x", 0);
	func("a+x", 0);
	func("a+x", 0);
	func("a+w", 0);
	func("a+w", 0);
	func("a+w", 0);
	func("a+r", 0);
	func("a+r", 0);
	func("a+r", 0);
	func("a+xw", 0);
	func("a+xr", 0);
	func("a+wr", 0);
	func("o-x", 0777);
	func("o-w", 0777);
	func("o-r", 0777);
	func("g-x", 0777);
	func("g-w", 0777);
	func("g-r", 0777);
	func("u-x", 0777);
	func("u-w", 0777);
	func("u-r", 0777);
}

Gurax_TesterEntry(OAL)
{
	Test_ParseStatMode();
}

}
