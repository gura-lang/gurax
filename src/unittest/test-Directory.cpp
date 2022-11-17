//==============================================================================
// test-Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void PrintDirectory(Directory& directory, int indentLevel)
{
	::printf("%*s%s\n", indentLevel * 2, "", directory.GetName());
	directory.RewindChild();
	Directory* pDirectoryChild;
	while ((pDirectoryChild = directory.NextChild())) {
		PrintDirectory(*pDirectoryChild, indentLevel + 1);
	}
}

Gurax_TesterEntry(Directory)
{
#if 0
	char sep = '/';
	bool caseFlag = false;
	RefPtr<Directory_CustomContainer> pDirectory(new Directory_CustomContainer("foo", Directory::Type::Root, sep, caseFlag));
	pDirectory->AddChildInTree("dir1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-2", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-3", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir2", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir3", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir4/dir4-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir5/dir5-1/dir5-1-1/dir5-1-1-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir6/", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir4", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	PrintDirectory(*pDirectory, 0);
	do {
		const char* pathNames[] = {
			"dir1",
			"dir1/",
			"dirx",
			"dir1/dir1-1",
			"dir1/dir1-1/",
			"dir1/dir1-x",
			"dir5/dir5-1/dir5-1-1/dir5-1-1-1",
			"dir5/dir5-1/dir5-1-1/dir5-1-1-1/",
		};
		for (int i = 0; i < Gurax_ArraySizeOf(pathNames); i++) {
			const char* pathName = pathNames[i];
			const char* p = pathName;
			Directory* pDirectoryFound = pDirectory->SearchInTree(&p);
			::printf("\"%s\": %s, \"%s\"\n", pathName, pDirectoryFound? "found" : "not found", p);
		}
	} while (0);
#endif
}

}
