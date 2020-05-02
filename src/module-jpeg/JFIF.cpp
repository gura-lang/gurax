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
	return Segment::AnalyzeBinary();
}

bool JFIF::WriteToStream(Stream& stream)
{
	return Segment::WriteToStream(stream);
}

String JFIF::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("<jpeg.Segment:%s(JFIF)>", GetMarkerSymbol()->GetName());
	return str;
}

Gurax_EndModuleScope(jpeg)
