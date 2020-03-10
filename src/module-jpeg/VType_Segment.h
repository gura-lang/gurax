//==============================================================================
// VType_Segment.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_VTYPE_SEGMENT_H
#define GURAX_MODULE_JPEG_VTYPE_SEGMENT_H
#include <gurax.h>
#include "Segment.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// VType_Segment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Segment : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Segment VTYPE_Segment;

//------------------------------------------------------------------------------
// Value_Segment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Segment : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Segment);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Segment");
protected:
	RefPtr<Segment> _pSegment;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Segment() = delete;
	explicit Value_Segment(Segment* pSegment, VType& vtype = VTYPE_Segment) :
		Value_Object(vtype), _pSegment(pSegment) {}
	// Copy constructor/operator
	Value_Segment(const Value_Segment& src) :
		Value_Object(src), _pSegment(src._pSegment->Reference()) {}
	Value_Segment& operator=(const Value_Segment& src) = delete;
	// Move constructor/operator
	Value_Segment(Value_Segment&& src) = delete;
	Value_Segment& operator=(Value_Segment&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Segment() = default;
public:
	Segment& GetSegment() { return *_pSegment; }
	const Segment& GetSegment() const { return *_pSegment; }
public:
	static Segment& GetSegment(Value& value) {
		return dynamic_cast<Value_Segment&>(value).GetSegment();
	}
	static const Segment& GetSegment(const Value& value) {
		return dynamic_cast<const Value_Segment&>(value).GetSegment();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSegment().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetSegment().IsEqualTo(Value_Segment::GetSegment(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetSegment().IsLessThan(Value_Segment::GetSegment(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetSegment().ToString(ss);
	}
};

Gurax_EndModuleScope(jpeg)

#endif
