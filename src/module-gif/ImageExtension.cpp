//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	char buff[3];
	return stream.Read(buff, 3) == 3 && ::memcmp(buff, "GIF", 3) == 0;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return ::strcasecmp(extName, ".gif") == 0;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	return ReadStream(stream, image);
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	return WriteStream(stream, image);
}

bool ImageMgrEx::ReadStream(Stream& stream, Image& image)
{
	return false;
}

bool ImageMgrEx::WriteStream(Stream& stream, const Image& image)
{
	return true;
}

Gurax_EndModuleScope(gif)
