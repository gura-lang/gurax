//==============================================================================
// Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
String Directory::MakePathName(bool addSepFlag, const char* pathNameTrail) const
{
	return "";
}

int Directory::CountDepth() const
{
	return 0;
}

Value* Directory::DoGetStatValue()
{
	Error::Issue(ErrorType::PropertyError, "no status value available");
	return Value::nil();
}

String Directory::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// DirectoryList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DirectoryOwner
//------------------------------------------------------------------------------
void DirectoryOwner::Clear()
{
	for (Directory* pDirectory : *this) Directory::Delete(pDirectory);
	clear();
}

}
