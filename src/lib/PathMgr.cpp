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
	PathMgrOwner& pathMgrOwner = Basement::Inst.GetPathMgrOwner();
	pathMgrOwner.push_back(pPathMgr);
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
	if (!*pathName) {
		PathMgr* pPathMgr = pathMgrList.FindResponsible(nullptr, pathName);
		if (!pPathMgr) {
			Error::Issue(ErrorType::PathError, "invalid path name");
			return nullptr;
		}
		return pPathMgr->OpenDirectory(nullptr, &pathName, typeWouldBe);
	}
	RefPtr<Directory> pDirectory;
	while (*pathName) {
		if (pDirectory && PathName::IsSep(*pathName)) pathName++;
		PathMgr* pPathMgr = pathMgrList.FindResponsible(pDirectory.get(), pathName);
		if (!pPathMgr) {
			Error::Issue(ErrorType::PathError, "invalid path name");
			return nullptr;
		}
		pDirectory.reset(pPathMgr->OpenDirectory(pDirectory.release(), &pathName, typeWouldBe));
		if (!pDirectory) return nullptr;
	}
	return pDirectory.release();
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
