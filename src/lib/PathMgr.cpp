//==============================================================================
// PathMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PathMgr
//------------------------------------------------------------------------------
void PathMgr::Assign(PathMgr* pPathMgr)
{
	Basement::Inst.AssignPathMgr(pPathMgr);
}

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

Directory* PathMgr::OpenDirectory(const char* pathName, Directory::Type typeWouldBe)
{
	const PathMgrList& pathMgrList = Basement::Inst.GetPathMgrList();
	Directory* pDirectory = nullptr;
	while (*pathName) {
		PathMgr* pPathMgr = pathMgrList.FindResponsible(pDirectory, pathName);
		if (!pPathMgr) return nullptr;
		pDirectory = pPathMgr->OpenDirectory(pDirectory, &pathName, typeWouldBe);
		if (!pDirectory) return nullptr;
	}
	return pDirectory;
}

PathMgr::Existence PathMgr::CheckExistence(const char* pathName)
{
	PathMgr* pPathMgr = PathMgr::FindResponsible(pathName);
	if (!pPathMgr) return Existence::None;
	return pPathMgr->CheckExistence(nullptr, &pathName);
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
	for (auto ppPathMgr = rbegin(); ppPathMgr != rend(); ppPathMgr++) {
		PathMgr* pPathMgr = *ppPathMgr;
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
