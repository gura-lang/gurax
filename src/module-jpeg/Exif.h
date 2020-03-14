//==============================================================================
// Exif.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_EXIF_H
#define GURAX_MODULE_JPEG_EXIF_H
#include <gurax.h>
#include "Segment.h"

Gurax_BeginModuleScope(jpeg)

class IFD;

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Exif : public Segment {
public:
	// Referable declaration
	Gurax_DeclareReferable(Exif);
public:
	// Constructor
	Exif(BinaryReferable* pBuff) : Segment(Marker::APP1, pBuff) {}
	// Copy constructor/operator
	Exif(const Exif& src) = delete;
	Exif& operator=(const Exif& src) = delete;
	// Move constructor/operator
	Exif(Exif&& src) = delete;
	Exif& operator=(Exif&& src) noexcept = delete;
protected:
	~Exif() = default;
public:
	virtual Value* CreateValue() const override;
	virtual bool AnalyzeBinary() override;
	virtual bool Write(Stream& stream) const override;
protected:
	template<typename T> IFD* CreateIFD_T(const UInt8*& pBuff, size_t& bytesAvail);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Exif& other) const { return this == &other; }
	bool IsEqualTo(const Exif& other) const { return IsIdentical(other); }
	bool IsLessThan(const Exif& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
