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
	TypeDef_BE::SHORT buffShort;
	Gurax_PackUInt16(buffShort.num, _marker);
	if (!stream.Write(&buffShort, sizeof(buffShort))) return false;
	if (_pBuff) {
		const Binary& buff = _pBuff->GetBinary();
		size_t bytes = buff.size() + 2;
		if (bytes > 0xffff) {
			Error::Issue(ErrorType::FormatError, "too large segment");
			return false;
		}
		Gurax_PackUInt16(buffShort.num, static_cast<UInt16>(bytes));
		if (!stream.Write(&buffShort, sizeof(buffShort))) return false;
		if (!stream.Write(buff)) return false;
	}
	return true;
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
