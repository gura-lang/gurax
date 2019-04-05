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
	for (size_t i = 0; i < ArraySizeOf(pathNames); i++) {
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
	for (size_t i = 0; i < ArraySizeOf(pathNames); i++) {
		const char* pathName = pathNames[i];
		PathName(pathName).SplitFileName(&dirName, &fileName);
		::printf("'%s' .. '%s', '%s'\n", pathName, dirName.c_str(), fileName.c_str());
	}
}

static void Test_SplitBottomName()
{
	PrintTitle("SplitBottomName");
	String headName, bottomName;
	for (size_t i = 0; i < ArraySizeOf(pathNames); i++) {
		const char* pathName = pathNames[i];
		PathName(pathName).SplitBottomName(&headName, &bottomName);
		::printf("'%s' .. '%s', '%s'\n", pathName, headName.c_str(), bottomName.c_str());
	}
}

static void Test_SplitExtName()
{
	PrintTitle("SplitExtName");
	String baseName, extName;
	for (size_t i = 0; i < ArraySizeOf(pathNames); i++) {
		const char* pathName = pathNames[i];
		PathName(pathName).SplitExtName(&baseName, &extName);
		::printf("'%s' .. '%s', '%s'\n", pathName, baseName.c_str(), extName.c_str());
	}
}

Gurax_TesterEntry(PathName)
{
	Test_Regulate();
	Test_SplitFileName();
	Test_SplitBottomName();
	Test_SplitExtName();
}

}
