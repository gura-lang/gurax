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
	imageMgrOwner.v.push_back(pImageMgr);
}

String ImageMgr::ToString(const StringStyle& ss) const
{
	return String().Format("<ImageMgr:%s>", GetImgTypeName());
}

//------------------------------------------------------------------------------
// ImageMgrList
//------------------------------------------------------------------------------
const ImageMgr* ImageMgrList::FindResponsible(Stream& stream) const
{
	for (const ImageMgr* pImageMgr : v) {
		size_t offset = stream.GetOffset();
		bool flag = pImageMgr->IsResponsible(stream);
		stream.SetOffset(offset);
		if (flag) return pImageMgr;
	}
	return nullptr;
}

const ImageMgr* ImageMgrList::FindByImgTypeName(const char* imgTypeName) const
{
	for (const ImageMgr* pImageMgr : v) {
		if (::strcasecmp(pImageMgr->GetImgTypeName(), imgTypeName) == 0) return pImageMgr;
	}
	return nullptr;
}

const ImageMgr* ImageMgrList::FindByFileName(const char* fileName) const
{
	String extName = PathName(fileName).ExtractExtName();
	if (extName.empty()) return nullptr;
	for (const ImageMgr* pImageMgr : v) {
		if (pImageMgr->IsResponsibleExtName(extName.c_str())) return pImageMgr;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// ImageMgrOwner
//------------------------------------------------------------------------------
void ImageMgrOwner::Clear()
{
	for (ImageMgr* pImageMgr : v) ImageMgr::Delete(pImageMgr);
	v.clear();
}

}
