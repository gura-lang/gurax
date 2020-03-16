//==============================================================================
// Exif.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_EXIF_H
#define GURAX_MODULE_JPEG_EXIF_H
#include <gurax.h>
#include "Segment.h"
#include "IFD.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Exif : public Segment {
public:
	// Referable declaration
	Gurax_DeclareReferable(Exif);
protected:
	bool _bigEndianFlag;
	IFDOwner _ifdOwner;
public:
	// Constructor
	Exif(BinaryReferable* pBuff) : Segment(Marker::APP1, pBuff), _bigEndianFlag(false) {}
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
	template<typename TypeDef> IFD* AnalyzeIFD(
		const Symbol* pSymbolOfIFD, const UInt8* buff, size_t bytesBuff, size_t offset);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Exif& other) const { return this == &other; }
	bool IsEqualTo(const Exif& other) const { return IsIdentical(other); }
	bool IsLessThan(const Exif& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
