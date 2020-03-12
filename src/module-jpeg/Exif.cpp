//==============================================================================
// Exif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
Value* Exif::CreateValue() const
{
	return new Value_Exif(Reference());
}

bool Exif::AnalyzeBinary()
{
	GetBinary()->Dump(Basement::Inst.GetStreamCOut());
	const UInt8* p = GetBinary()->data();
	size_t bytesAvail = GetBinary()->size();
	do {
		size_t bytes = sizeof(ExifHeader);
		const ExifHeader& hdr = *reinterpret_cast<const ExifHeader*>(p);
		p += bytes, bytesAvail -= bytes;
	} while (0);
	using TIFFHeaderT = TIFFHeader_LE;
	do {
		size_t bytes = sizeof(TIFFHeaderT);
		const TIFFHeaderT& hdr = *reinterpret_cast<const TIFFHeaderT>(p);
		p += bytes, bytesAvail -= bytes;
	} while (0);
	return true;
}

bool Exif::Write(Stream& stream) const
{
	return Segment::Write(stream);
}

String Exif::ToString(const StringStyle& ss) const
{
	return "jpeg.Exif";
}

Gurax_EndModuleScope(jpeg)
