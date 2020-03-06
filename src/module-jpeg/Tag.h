//==============================================================================
// Tag.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_TAG_H
#define GURAX_MODULE_JPEG_TAG_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Tag);
public:
	// Constructor
	Tag() {}
	// Copy constructor/operator
	Tag(const Tag& src) = delete;
	Tag& operator=(const Tag& src) = delete;
	// Move constructor/operator
	Tag(Tag&& src) = delete;
	Tag& operator=(Tag&& src) noexcept = delete;
protected:
	~Tag() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Tag& other) const { return this == &other; }
	bool IsEqualTo(const Tag& other) const { return IsIdentical(other); }
	bool IsLessThan(const Tag& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
