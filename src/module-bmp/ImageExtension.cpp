//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	::printf("IsResponsible()\n");
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

Gurax_EndModuleScope(bmp)
