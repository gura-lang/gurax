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

bool Segment::WriteToStream(Stream& stream)
{
	TypeDef_BE::SHORT packed;
	Gurax_PackUInt16(packed.num, _marker);
	if (!stream.Write(&packed, sizeof(packed))) return false;
	if (_pBuff) {
		const Binary& buff = _pBuff->GetBinary();
		size_t bytes = buff.size() + 2;
		if (bytes > 0xffff) {
			Error::Issue(ErrorType::FormatError, "too large segment");
			return false;
		}
		Gurax_PackUInt16(packed.num, static_cast<UInt16>(bytes));
		if (!stream.Write(&packed, sizeof(packed))) return false;
		if (!stream.Write(buff)) return false;
	}
	return true;
}

String Segment::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("<jpeg.Segment:%s>", GetMarkerSymbol()->GetName());
	return str;
}

//------------------------------------------------------------------------------
// SegmentList
//------------------------------------------------------------------------------
Segment* SegmentList::FindByMarker(UInt16 marker) const
{
	for (Segment* pSegment : *this) {
		if (pSegment->GetMarker() == marker) return pSegment;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// SegmentOwner
//------------------------------------------------------------------------------
void SegmentOwner::Clear()
{
	for (Segment* pSegment : *this) Segment::Delete(pSegment);
	clear();
}

//------------------------------------------------------------------------------
// SegmentMap
//------------------------------------------------------------------------------
void SegmentMap::Clear()
{
	for (auto iter = begin(); iter != end(); iter++) Segment::Delete(iter->second);
	clear();
}

Segment* SegmentMap::Lookup(const Symbol* pSymbol) const
{
	auto iter = find(pSymbol);
	return (iter == end())? nullptr : iter->second;
}

Gurax_EndModuleScope(jpeg)
