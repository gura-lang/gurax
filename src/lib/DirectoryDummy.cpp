//==============================================================================
// DirectoryDummy.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// DirectoryDummy
//-----------------------------------------------------------------------------
void DirectoryDummy::DoRewindChild()
{
	_idxChild = 0;
}

Directory* DirectoryDummy::DoNextChild()
{
	CoreOwner& coreOwner = GetCoreEx().GetCoreOwner();
	if (_idxChild >= coreOwner.size()) return nullptr;
	RefPtr<Directory> pDirectory(coreOwner[_idxChild]->GenerateDirectory());
	_idxChild++;
	pDirectory->SetDirectoryParent(Reference());
	return pDirectory.release();
}

Value_Stat* DirectoryDummy::DoCreateStatValue()
{
	StatDummy* pStatEx = GetCoreEx().GetStatDummy();
	return pStatEx? new Value_Stat(pStatEx->Reference()) : nullptr;
}

}
