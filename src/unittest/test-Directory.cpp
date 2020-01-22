//==============================================================================
// test-Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void PrintDirectory(const Directory& directory, int indentLevel)
{
	::printf("%*s%s\n", indentLevel * 2, "", directory.GetName());
	if (directory.IsCustomContainer()) {
		for (const Directory* pDirectoryChild :
				 dynamic_cast<const Directory_CustomContainer&>(directory).GetDirectoryOwner()) {
			PrintDirectory(*pDirectoryChild, indentLevel + 1);
		}
	}
}

Gurax_TesterEntry(Directory)
{
	char sep = '/';
	bool caseFlag = false;
	RefPtr<Directory_CustomContainer> pDirectory(new Directory_CustomContainer("foo", Directory::Type::RootContainer, sep, caseFlag));
	pDirectory->AddChildInTree("dir1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-2", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-3", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir2", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir3", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir4/dir4-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir5/dir5-1/dir5-1-1/dir5-1-1-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir6/", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	PrintDirectory(*pDirectory, 0);
}

}
