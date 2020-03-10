//==============================================================================
// Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
bool Content::Read(Stream& stream)
{
	SHORT_BE data;
	if (stream.Read(&data, sizeof(data)) < sizeof(data)) {
		IssueError_InvalidFormat();
		return false;
	}
	UInt16 marker = Gurax_UnpackUInt16(data.num);
	::printf("%04x\n", marker);
	if (stream.Read(&data, sizeof(data)) < sizeof(data)) {
		IssueError_InvalidFormat();
		return false;
	}
	UInt16 len = Gurax_UnpackUInt16(data.num);
	::printf("%04x\n", len);
	return true;
}

bool Content::Write(Stream& stream) const
{
	return false;
}
	
String Content::ToString(const StringStyle& ss) const
{
	return "jpeg.Content";
}

Gurax_EndModuleScope(jpeg)
