//==============================================================================
// ImageMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ImageMgr
//------------------------------------------------------------------------------
void ImageMgr::Assign(ImageMgr* pImageMgr)
{
	ImageMgrOwner& imageMgrOwner = Basement::Inst.GetImageMgrOwner();
	imageMgrOwner.push_back(pImageMgr);
}

const ImageMgr* ImageMgr::FindResponsible(Stream& stream)
{
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	const ImageMgr* pImageMgr = imageMgrList.FindResponsible(stream);
	if (!pImageMgr) {
		Error::Issue(ErrorType::FormatError, "unsupported image format");
		return nullptr;
	}
	return pImageMgr;
}

const ImageMgr* ImageMgr::FindByTypeName(const char* typeName)
{
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	const ImageMgr* pImageMgr = imageMgrList.FindByTypeName(typeName);
	if (!pImageMgr) {
		Error::Issue(ErrorType::FormatError, "unsupported image format");
		return nullptr;
	}
	return pImageMgr;
}

//------------------------------------------------------------------------------
// ImageMgrList
//------------------------------------------------------------------------------
const ImageMgr* ImageMgrList::FindResponsible(Stream& stream) const
{
	for (const ImageMgr* pImageMgr : *this) {
		if (pImageMgr->IsResponsible(stream)) return pImageMgr;
	}
	return nullptr;
}

const ImageMgr* ImageMgrList::FindByTypeName(const char* typeName) const
{
	for (const ImageMgr* pImageMgr : *this) {
		if (::strcmp(pImageMgr->GetTypeName(), typeName) == 0) return pImageMgr;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// ImageMgrOwner
//------------------------------------------------------------------------------
void ImageMgrOwner::Clear()
{
	for (ImageMgr* pImageMgr : *this) ImageMgr::Delete(pImageMgr);
	clear();
}

}
