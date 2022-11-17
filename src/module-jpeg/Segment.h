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
protected:
	UInt16 _marker;
	RefPtr<BinaryReferable> _pBuff;
public:
	// Constructor
	Segment(UInt16 marker, BinaryReferable* pBuff);
	// Copy constructor/operator
	Segment(const Segment& src) = delete;
	Segment& operator=(const Segment& src) = delete;
	// Move constructor/operator
	Segment(Segment&& src) = delete;
	Segment& operator=(Segment&& src) noexcept = delete;
protected:
	virtual ~Segment() = default;
public:
	UInt16 GetMarker() const { return _marker; }
	const Symbol* GetMarkerSymbol() const { return MarkerToSymbol(_marker); }
	Binary* GetBinary() { return _pBuff? &_pBuff->GetBinary() : nullptr; }
	const Binary* GetBinary() const { return _pBuff? &_pBuff->GetBinary() : nullptr; }
	const BinaryReferable* GetBinaryReferable() const { return _pBuff.get(); }
public:
	virtual bool IsJFIF() const { return false; }
	virtual bool IsExif() const { return false; }
	virtual Value* CreateValue() const;
	virtual bool AnalyzeBinary() { return true; }
	virtual bool WriteToStream(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Segment& other) const { return this == &other; }
	bool IsEqualTo(const Segment& other) const { return IsIdentical(other); }
	bool IsLessThan(const Segment& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SegmentList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SegmentList : public ListBase<Segment*> {
public:
	Segment* FindByMarker(UInt16 marker) const;
};

//------------------------------------------------------------------------------
// SegmentOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SegmentOwner : public SegmentList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SegmentOwner);
protected:
	~SegmentOwner() { Clear(); }
public:
	void Clear();
};

//------------------------------------------------------------------------------
// SegmentMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SegmentMap :
	 public std::unordered_map<const Symbol*, Segment*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId> {
public:
	~SegmentMap() { Clear(); }
	void Clear();
	Segment* Lookup(const Symbol* pSymbol) const;
};

Gurax_EndModuleScope(jpeg)

#endif
