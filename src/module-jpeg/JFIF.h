//==============================================================================
// JFIF.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_JFIF_H
#define GURAX_MODULE_JPEG_JFIF_H
#include <gurax.h>
#include "Segment.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// JFIF
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE JFIF : public Segment {
public:
	// Referable declaration
	Gurax_DeclareReferable(JFIF);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("jpeg.JFIF");
public:
	struct Header {
		UInt8 identifier[5];
		Gurax_PackedUInt16_BE(version);
		UInt8 units;
		Gurax_PackedUInt16_BE(xDensity);
		Gurax_PackedUInt16_BE(yDensity);
		UInt8 xThumbnail;
		UInt8 yThumbnail;
	};
protected:
	Header _header;
	Binary _buffRGB;
public:
	// Constructor
	JFIF(BinaryReferable* pBuff) : Segment(Marker::APP0, pBuff) {
		::memset(&_header, 0x00, sizeof(_header));
	}
	// Copy constructor/operator
	JFIF(const JFIF& src) = delete;
	JFIF& operator=(const JFIF& src) = delete;
	// Move constructor/operator
	JFIF(JFIF&& src) noexcept = delete;
	JFIF& operator=(JFIF&& src) noexcept = delete;
protected:
	~JFIF() = default;
public:
	virtual bool IsJFIF() const override { return true; }
	virtual Value* CreateValue() const override;
	virtual bool AnalyzeBinary() override;
	virtual bool WriteToStream(Stream& stream) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const JFIF& other) const { return this == &other; }
	bool IsEqualTo(const JFIF& other) const { return IsIdentical(other); }
	bool IsLessThan(const JFIF& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
