//==============================================================================
// test-PathName.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* pathNames[] = {
	"",
	"/",
	"/aaa",
	"/aaa/",
	"/aaa/bbb",
	"/aaa/bbb/ccc",
	"/aaa/..",
	"/aaa/../",
	"/aaa/bbb/..",
	"/aaa/bbb/../",
	"/aaa/bbb/../..",
	"/aaa/bbb/../../",
	"/aaa/../ccc",
	"/aaa/bbb/../ccc",
	"/aaa/bbb/../../ccc",
	"/aaa/bbb/ccc/ddd/../../eee/fff/../ggg",
	"/aaa/.",
	"/aaa/./",
	"/aaa/./bbb/./ccc",
	"/aaa/./bbb/./ccc/",
	"..",
	"/..",
	"/../aaa",
	"/.",
	"/./aaa",
	"aaa",
	"aaa/",
	"aaa/bbb",
	"aaa/bbb/ccc",
	"aaa/..",
	"aaa/../",
	"aaa/bbb/..",
	"aaa/bbb/../",
	"aaa/bbb/../..",
	"aaa/bbb/../../",
	"aaa/../ccc",
	"aaa/bbb/../ccc",
	"aaa/bbb/../../ccc",
	"aaa/bbb/ccc/ddd/../../eee/fff/../ggg",
	"aaa/.",
	"aaa/./",
	"aaa/./bbb/./ccc",
	"aaa/./bbb/./ccc/",
	"C:/",
	"C:/aaa",
	"C:/aaa/",
	"C:/aaa/bbb",
	"C:/aaa/bbb/ccc",
	"C:/aaa/..",
	"C:/aaa/../",
	"C:/aaa/bbb/..",
	"C:/aaa/bbb/../",
	"C:/aaa/bbb/../..",
	"C:/aaa/bbb/../../",
	"C:/aaa/../ccc",
	"C:/aaa/bbb/../ccc",
	"C:/aaa/bbb/../../ccc",
	"C:/aaa/bbb/ccc/ddd/../../eee/fff/../ggg",
	"C:/aaa/.",
	"C:/aaa/./",
	"C:/aaa/./bbb/./ccc",
	"C:/aaa/./bbb/./ccc/",
	"C:",
	"C:aaa",
	"C:aaa/",
	"C:aaa/bbb",
	"C:aaa/bbb/ccc",
	"C:aaa/..",
	"C:aaa/../",
	"C:aaa/bbb/..",
	"C:aaa/bbb/../",
	"C:aaa/bbb/../..",
	"C:aaa/bbb/../../",
	"C:aaa/../ccc",
	"C:aaa/bbb/../ccc",
	"C:aaa/bbb/../../ccc",
	"C:aaa/bbb/ccc/ddd/../../eee/fff/../ggg",
	"C:aaa/.",
	"C:aaa/./",
	"C:aaa/./bbb/./ccc",
	"C:aaa/./bbb/./ccc/",
	".aaa",
	"/.aaa",
	"/aaa/.bbb",
	"aaa.ext",
	"/aaa/bbb.ext",
	"/aaa/bbb.ccc/",
};

static void Test_Regulate()
{
	PrintTitle("Regulate");
	for (size_t i = 0; i < Gurax_ArraySizeOf(pathNames); ++i) {
		const char* pathName = pathNames[i];
		::printf("'%s' .. '%s'\n", pathName, PathName(pathName).Regulate().c_str());
		String pathNameMod = String::Replace<CharCase>(pathName, "/", "\\");
		::printf("'%s' .. '%s'\n", pathNameMod.c_str(), PathName(pathNameMod).Regulate().c_str());
	}
}

static void Test_SplitFileName()
{
	PrintTitle("SplitFileName");
	String dirName, fileName;
	for (size_t i = 0; i < Gurax_ArraySizeOf(pathNames); ++i) {
		const char* pathName = pathNames[i];
		PathName(pathName).SplitFileName(&dirName, &fileName);
		::printf("'%s' .. '%s', '%s'\n", pathName, dirName.c_str(), fileName.c_str());
	}
}

static void Test_SplitBottomName()
{
	PrintTitle("SplitBottomName");
	String headName, bottomName;
	for (size_t i = 0; i < Gurax_ArraySizeOf(pathNames); ++i) {
		const char* pathName = pathNames[i];
		PathName(pathName).SplitBottomName(&headName, &bottomName);
		::printf("'%s' .. '%s', '%s'\n", pathName, headName.c_str(), bottomName.c_str());
	}
}

static void Test_SplitExtName()
{
	PrintTitle("SplitExtName");
	String baseName, extName;
	for (size_t i = 0; i < Gurax_ArraySizeOf(pathNames); ++i) {
		const char* pathName = pathNames[i];
		PathName(pathName).SplitExtName(&baseName, &extName);
		::printf("'%s' .. '%s', '%s'\n", pathName, baseName.c_str(), extName.c_str());
	}
}

void Test_DoesMatch()
{
	PrintTitle("DoesMatch");
	struct Info {
		const char* pathName;
		const char* pattern;
		bool caseFlag;
	};
	static const Info infoTbl[] = {
		{ "abcdefg",	"a*",			true },
		{ "abcdefg",	"a*efg",		true },
		{ "abcdefg",	"a*ef",			true },
		{ "abcdefg",	"a?cdefg",		true },
		{ "abcdefg",	"a????fg",		true },
		{ "abcdefg",	"a????f?",		true },
		{ "abcdefg",	"a???f?",		true },
		{ "abcdefg",	"A*",			true },
		{ "abcdefg",	"A*",			false },
		{ "bcdefg",		"a*",			true },
	};
	for (size_t i = 0; i < Gurax_ArraySizeOf(infoTbl); ++i) {
		const Info& info = infoTbl[i];
		bool rtn = PathName(info.pathName).SetCaseFlag(info.caseFlag).DoesMatchPattern(info.pattern);
		::printf("%-16s %-16s %s .. %s\n", info.pathName, info.pattern,
				 info.caseFlag? "(case)" : "(icase)", rtn? "OK" : "NG");
	}
}

void Test_Join()
{
	PrintTitle("JoinAfter/JoinBefore");
	struct Info {
		const char* pathName1;
		const char* pathName2;
	};
	static const Info infoTbl[] = {
		{ "aaa",		"bbb"		},
		{ "aaa/",		"bbb"		},
		{ "aaa/",		"/bbb"		},
		{ "aaa\\",		"bbb"		},
		{ "aaa\\",		"\\bbb"		},
		{ "",			""			},
		{ "aaa",		""			},
		{ "aaa/",		""			},
		{ "",			"bbb"		},
		{ "",			"/bbb"		},
	};
	for (size_t i = 0; i < Gurax_ArraySizeOf(infoTbl); ++i) {
		const Info& info = infoTbl[i];
		String rtn1 = PathName(info.pathName1).JoinAfter(info.pathName2);
		::printf("%-16s + %-16s -> %s\n", info.pathName1, info.pathName2, rtn1.c_str());
		String rtn2 = PathName(info.pathName2).JoinBefore(info.pathName1);
		::printf("%-16s + %-16s -> %s\n", info.pathName1, info.pathName2, rtn2.c_str());
	}
}

void Test_IsAbsName()
{
	PrintTitle("IsAbsName");
	for (size_t i = 0; i < Gurax_ArraySizeOf(pathNames); ++i) {
		const char* pathName = pathNames[i];
		::printf("%-40s .. %s\n", pathName,
				 PathName(pathName).IsAbsName()? "absolute" : "relative");
	}
}

void Test_MakeAbsName()
{
	PrintTitle("MakeAbsName");
	::printf("%s\n", PathName("aaa").MakeAbsName().c_str());
	::printf("%s\n", PathName("../aaa/bbb").MakeAbsName().c_str());
}
		
Gurax_TesterEntry(PathName)
{
	Test_Regulate();
	Test_SplitFileName();
	Test_SplitBottomName();
	Test_SplitExtName();
	Test_DoesMatch();
	Test_Join();
	Test_IsAbsName();
	//Test_MakeAbsName();
}

}
