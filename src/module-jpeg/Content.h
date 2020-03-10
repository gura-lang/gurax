//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_CONTENT_H
#define GURAX_MODULE_JPEG_CONTENT_H
#include <gurax.h>
#include "Segment.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
protected:
	RefPtr<SegmentOwner> _pSegmentOwner;
	RefPtr<BinaryReferable> _pBuffImage;
public:
	// Constructor
	Content() : _pSegmentOwner(new SegmentOwner()) {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content() = default;
public:
	SegmentOwner& GetSegmentOwner() { return *_pSegmentOwner; }
	const SegmentOwner& GetSegmentOwner() const { return *_pSegmentOwner; }
	const Binary* GetBuffImage() const { return _pBuffImage? &_pBuffImage->GetBinary() : nullptr; }
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
