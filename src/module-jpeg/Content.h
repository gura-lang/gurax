//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_CONTENT_H
#define GURAX_MODULE_JPEG_CONTENT_H
#include <gurax.h>
#include "Segment.h"

Gurax_BeginModuleScope(jpeg)

class Exif;
class JFIF;

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
	SegmentMap _segmentMap;
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
	Exif* FindExif();
	JFIF* FindJFIF();
	SegmentOwner& GetSegmentOwner() { return *_pSegmentOwner; }
	const SegmentOwner& GetSegmentOwner() const { return *_pSegmentOwner; }
	const SegmentMap& GetSegmentMap() const { return _segmentMap; }
	const BinaryReferable* GetBuffImage() const { return _pBuffImage.get(); }
	void SetBuffImage(BinaryReferable* pBuffImage) { _pBuffImage.reset(pBuffImage); }
public:
	void PrepareSegmentMap();
	bool Read(Stream& stream);
	bool Write(Stream& stream) const;
	void AddSegment(Segment* pSegment);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
