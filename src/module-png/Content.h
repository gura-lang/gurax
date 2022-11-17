//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_PNG_CONTENT_H
#define GURAX_MODULE_PNG_CONTENT_H
#include <gurax.h>
#include "ImageExtension.h"

Gurax_BeginModuleScope(png)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("png.Content");
public:
	png_structp png_ptr;
	png_infop info_ptr;
public:
	// Constructor
	Content() : png_ptr(nullptr), info_ptr(nullptr) {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) noexcept = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content();
public:
	bool Read(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(png)

#endif
