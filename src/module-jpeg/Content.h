//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_CONTENT_H
#define GURAX_MODULE_JPEG_CONTENT_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
public:
	// Constructor
	Content() {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content() = default;
public:
	bool Read(Stream& stream);
	bool Write(Stream& stream) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
