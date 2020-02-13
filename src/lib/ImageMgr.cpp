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
}

const ImageMgr* ImageMgr::FindResponsible(Stream& stream)
{
	return nullptr;
}

const ImageMgr* ImageMgr::FindByTypeName(const char* typeName)
{
	return nullptr;
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
