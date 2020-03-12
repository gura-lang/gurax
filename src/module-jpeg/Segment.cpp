//==============================================================================
// Segment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Segment
//------------------------------------------------------------------------------
Segment::Segment(UInt16 marker, BinaryReferable* pBuff) : _marker(marker), _pBuff(pBuff)
{
}

Value* Segment::CreateValue() const
{
	return new Value_Segment(Reference());
}

bool Segment::Write(Stream& stream) const
{
	SHORT_BE buffShort;
	Gurax_PackUInt16(buffShort.num, _marker);
	//if (stream.Write(&buffShort, sizeof(buffShort)) < sizeof(buff
	return false;
}

String Segment::ToString(const StringStyle& ss) const
{
	return "jpeg.Segment";
}

//------------------------------------------------------------------------------
// SegmentList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SegmentOwner
//------------------------------------------------------------------------------
void SegmentOwner::Clear()
{
	for (Segment* pSegment : *this) Segment::Delete(pSegment);
	clear();
}

Gurax_EndModuleScope(jpeg)
