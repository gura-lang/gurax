//==============================================================================
// VType_Exif.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_VTYPE_EXIF_H
#define GURAX_MODULE_JPEG_VTYPE_EXIF_H
#include <gurax.h>
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

extern VType_Exif VTYPE_Exif;

//------------------------------------------------------------------------------
// Value_Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Exif : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Exif);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Exif");
protected:
	RefPtr<Exif> _pExif;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Exif() = delete;
	explicit Value_Exif(Exif* pExif, VType& vtype = VTYPE_Exif) :
		Value_Object(vtype), _pExif(pExif) {}
	// Copy constructor/operator
	Value_Exif(const Value_Exif& src) :
		Value_Object(src), _pExif(src._pExif->Reference()) {}
	Value_Exif& operator=(const Value_Exif& src) = delete;
	// Move constructor/operator
	Value_Exif(Value_Exif&& src) = delete;
	Value_Exif& operator=(Value_Exif&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Exif() = default;
public:
	Exif& GetExif() { return *_pExif; }
	const Exif& GetExif() const { return *_pExif; }
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
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetExif().IsEqualTo(Value_Exif::GetExif(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetExif().IsLessThan(Value_Exif::GetExif(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetExif().ToString(ss);
	}
};

Gurax_EndModuleScope(jpeg)

#endif