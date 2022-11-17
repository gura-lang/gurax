//==============================================================================
// JFIF.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)


//------------------------------------------------------------------------------
// JFIF
//------------------------------------------------------------------------------
Value* JFIF::CreateValue() const
{
	return new Value_JFIF(Reference());
}

bool JFIF::AnalyzeBinary()
{
	const UInt8* pBuff = GetBinary()->data();
	size_t bytesAvail = GetBinary()->size();
	if (bytesAvail < sizeof(Header)) {
		IssueError_InvalidFormat();
		return false;
	}
	::memcpy(&_header, pBuff, sizeof(_header));
	if (::memcmp(_header.identifier, "JFIF\0", 5) != 0) {
		IssueError_InvalidFormat();
		return false;
	}
	pBuff += sizeof(_header);
	bytesAvail -= sizeof(_header);
	int width = _header.xThumbnail;
	int height = _header.yThumbnail;
	size_t bytesRGB = width * height * 3;
	if (bytesAvail < bytesRGB) {
		IssueError_InvalidFormat();
		return false;
	}
	_buffRGB = Binary(pBuff, bytesAvail);
	return true;
}

bool JFIF::WriteToStream(Stream& stream)
{
	return stream.Write(&_header, sizeof(_header)) && stream.Write(_buffRGB);
}

String JFIF::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("<jpeg.Segment:%s(JFIF)>", GetMarkerSymbol()->GetName());
	return str;
}

Gurax_EndModuleScope(jpeg)
