//==============================================================================
// PathMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PathMgr
//------------------------------------------------------------------------------
PathMgr* PathMgr::FindResponsible(const char* pathName)
{
	const PathMgrList& pathMgrList = Basement::Inst.GetPathMgrList();
	PathMgr* pPathMgr = pathMgrList.FindResponsible(nullptr, pathName);
	if (!pPathMgr) {
		Error::Issue(ErrorType::PathError, "unsupported path name");
		return nullptr;
	}
	return pPathMgr;
}

Directory* PathMgr::OpenDirectory(const char* pathName)
{
	PathMgr* pPathMgr = PathMgr::FindResponsible(pathName);
	if (!pPathMgr) return nullptr;
	return pPathMgr->OpenDirectory(nullptr, &pathName);
}

PathMgr::Existence PathMgr::CheckExistence(const char* pathName)
{
	PathMgr* pPathMgr = PathMgr::FindResponsible(pathName);
	if (!pPathMgr) return Existence::None;
	return pPathMgr->CheckExistence(nullptr, pathName);
}

String PathMgr::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// PathMgrList
//------------------------------------------------------------------------------
PathMgr* PathMgrList::FindResponsible(Directory* pDirectoryParent, const char* pathName) const
{
	for (PathMgr* pPathMgr : *this) {
		if (pPathMgr->IsResponsible(pDirectoryParent, pathName)) return pPathMgr;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// PathMgrOwner
//------------------------------------------------------------------------------
void PathMgrOwner::Clear()
{
	for (PathMgr* pPathMgr : *this) PathMgr::Delete(pPathMgr);
	clear();
}

}
