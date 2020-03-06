//==============================================================================
// Exif.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_EXIF_H
#define GURAX_MODULE_JPEG_EXIF_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Exif : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Exif);
public:
	// Constructor
	Exif() {}
	// Copy constructor/operator
	Exif(const Exif& src) = delete;
	Exif& operator=(const Exif& src) = delete;
	// Move constructor/operator
	Exif(Exif&& src) = delete;
	Exif& operator=(Exif&& src) noexcept = delete;
protected:
	~Exif() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Exif& other) const { return this == &other; }
	bool IsEqualTo(const Exif& other) const { return IsIdentical(other); }
	bool IsLessThan(const Exif& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
