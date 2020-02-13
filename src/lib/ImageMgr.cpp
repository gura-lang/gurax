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

const ImageMgr* ImageMgr::Find(Stream& stream, const char* imgTypeName)
{
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	const ImageMgr* pImageMgr = imgTypeName?
		imageMgrList.FindByImgTypeName(imgTypeName) : imageMgrList.FindResponsible(stream);
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

const ImageMgr* ImageMgrList::FindByImgTypeName(const char* imgTypeName) const
{
	for (const ImageMgr* pImageMgr : *this) {
		if (::strcasecmp(pImageMgr->GetImgTypeName(), imgTypeName) == 0) return pImageMgr;
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
