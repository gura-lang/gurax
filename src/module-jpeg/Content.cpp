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
	SHORT_BE buffShort;
	if (stream.Read(&buffShort, sizeof(buffShort)) < sizeof(buffShort)) {
		IssueError_InvalidFormat();
		return false;
	}
	UInt16 marker = Gurax_UnpackUInt16(buffShort.num);
	if (marker != Marker::SOI) {
		IssueError_InvalidFormat();
		return false;
	}
	for (;;) {
		if (stream.Read(&buffShort, sizeof(buffShort)) < sizeof(buffShort)) {
			IssueError_InvalidFormat();
			return false;
		}
		UInt16 marker = Gurax_UnpackUInt16(buffShort.num);
		::printf("%04x\n", marker);
		if (marker == Marker::SOS) break;
		if (stream.Read(&buffShort, sizeof(buffShort)) < sizeof(buffShort)) {
			IssueError_InvalidFormat();
			return false;
		}
		UInt16 len = Gurax_UnpackUInt16(buffShort.num);
		stream.Seek(len - 2, Stream::SeekMode::Cur);
	}
	
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
