//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	return false;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return false;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	return false;
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	return false;
}

Gurax_EndModuleScope(jpeg)
