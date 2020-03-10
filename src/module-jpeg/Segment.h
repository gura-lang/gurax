//==============================================================================
// Segment.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_SEGMENT_H
#define GURAX_MODULE_JPEG_SEGMENT_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Segment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Segment : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Segment);
public:
	// Constructor
	Segment() {}
	// Copy constructor/operator
	Segment(const Segment& src) = delete;
	Segment& operator=(const Segment& src) = delete;
	// Move constructor/operator
	Segment(Segment&& src) = delete;
	Segment& operator=(Segment&& src) noexcept = delete;
protected:
	~Segment() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Segment& other) const { return this == &other; }
	bool IsEqualTo(const Segment& other) const { return IsIdentical(other); }
	bool IsLessThan(const Segment& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
