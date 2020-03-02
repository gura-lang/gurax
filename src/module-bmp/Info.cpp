//==============================================================================
// Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
bool Info::Read(Stream& stream)
{
	if (stream.Read(&_bfh, BitmapFileHeader::bytes) < BitmapFileHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	if (stream.Read(&_bih, BitmapInfoHeader::bytes) < BitmapInfoHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	return true;
}

String Info::ToString(const StringStyle& ss) const
{
	return "bmp.Info";
}

Gurax_EndModuleScope(bmp)
