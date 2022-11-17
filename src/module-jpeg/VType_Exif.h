//==============================================================================
// VType_Exif.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_VTYPE_EXIF_H
#define GURAX_MODULE_JPEG_VTYPE_EXIF_H
#include <gurax.h>
#include "VType_Segment.h"
#include "Exif.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// VType_Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Exif : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Exif VTYPE_Exif;

//------------------------------------------------------------------------------
// Value_Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Exif : public Value_Segment {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Exif);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Exif");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Exif() = delete;
	explicit Value_Exif(Exif* pExif, VType& vtype = VTYPE_Exif) : Value_Segment(pExif, vtype) {}
	// Copy constructor/operator
	Value_Exif(const Value_Exif& src) = delete;
	Value_Exif& operator=(const Value_Exif& src) = delete;
	// Move constructor/operator
	Value_Exif(Value_Exif&& src) = delete;
	Value_Exif& operator=(Value_Exif&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Exif() = default;
public:
	Exif& GetExif() { return dynamic_cast<Exif&>(GetSegment()); }
	const Exif& GetExif() const { return dynamic_cast<const Exif&>(GetSegment()); }
public:
	static Exif& GetExif(Value& value) {
		return dynamic_cast<Value_Exif&>(value).GetExif();
	}
	static const Exif& GetExif(const Value& value) {
		return dynamic_cast<const Value_Exif&>(value).GetExif();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetExif().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetExif().IsEqualTo(Value_Exif::GetExif(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetExif().IsLessThan(Value_Exif::GetExif(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(jpeg)

#endif
