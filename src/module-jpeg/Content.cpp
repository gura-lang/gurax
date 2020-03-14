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
	TypeDef_BE::SHORT buffShort;
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
		if (marker == Marker::SOS) {
			GetSegmentOwner().push_back(new Segment(marker, nullptr));
			break;
		}
		if (stream.Read(&buffShort, sizeof(buffShort)) < sizeof(buffShort)) {
			IssueError_InvalidFormat();
			return false;
		}
		UInt16 bytesToRead = Gurax_UnpackUInt16(buffShort.num) - 2;
		RefPtr<BinaryReferable> pBuff(stream.ReadAsReferable(bytesToRead));
		if (Error::IsIssued()) {
			IssueError_InvalidFormat();
			return false;
		}
		RefPtr<Segment> pSegment;
		if (marker == Marker::APP1) {
			pSegment.reset(new Exif(pBuff.release()));
		} else {
			pSegment.reset(new Segment(marker, pBuff.release()));
		}
		if (!pSegment->AnalyzeBinary()) return false;
		GetSegmentOwner().push_back(pSegment.release());
	}
	_pBuffImage.reset(new BinaryReferable());
	stream.ReadToEnd(_pBuffImage->GetBinary());
	return true;
}

bool Content::Write(Stream& stream) const
{
	TypeDef_BE::SHORT buffShort;
	Gurax_PackUInt16(buffShort.num, Marker::SOI);
	if (!stream.Write(&buffShort, sizeof(buffShort))) return false;
	for (auto pSegment : GetSegmentOwner()) {
		if (!pSegment->Write(stream)) return false;
	}
	return _pBuffImage? stream.Write(_pBuffImage->GetBinary()) : true;
}
	
String Content::ToString(const StringStyle& ss) const
{
	return "jpeg.Content";
}

Gurax_EndModuleScope(jpeg)
