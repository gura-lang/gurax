//==============================================================================
// VType_ImageMgr.h
//==============================================================================
#ifndef GURAX_VTYPE_IMAGEMGR_H
#define GURAX_VTYPE_IMAGEMGR_H
#include "VType_Object.h"
#include "ImageMgr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ImageMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ImageMgr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ImageMgr VTYPE_ImageMgr;

//------------------------------------------------------------------------------
// Value_ImageMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ImageMgr : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ImageMgr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ImageMgr");
protected:
	RefPtr<ImageMgr> _pImageMgr;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ImageMgr() = delete;
	explicit Value_ImageMgr(ImageMgr* pImageMgr, VType& vtype = VTYPE_ImageMgr) :
		Value_Object(vtype), _pImageMgr(pImageMgr) {}
	// Copy constructor/operator
	Value_ImageMgr(const Value_ImageMgr& src) :
		Value_Object(src), _pImageMgr(src._pImageMgr->Reference()) {}
	Value_ImageMgr& operator=(const Value_ImageMgr& src) = delete;
	// Move constructor/operator
	Value_ImageMgr(Value_ImageMgr&& src) noexcept = delete;
	Value_ImageMgr& operator=(Value_ImageMgr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ImageMgr() = default;
public:
	ImageMgr& GetImageMgr() { return *_pImageMgr; }
	const ImageMgr& GetImageMgr() const { return *_pImageMgr; }
public:
	static ImageMgr& GetImageMgr(Value& value) {
		return dynamic_cast<Value_ImageMgr&>(value).GetImageMgr();
	}
	static const ImageMgr& GetImageMgr(const Value& value) {
		return dynamic_cast<const Value_ImageMgr&>(value).GetImageMgr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetImageMgr().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetImageMgr().IsEqualTo(Value_ImageMgr::GetImageMgr(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetImageMgr().IsLessThan(Value_ImageMgr::GetImageMgr(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetImageMgr().ToString(ss);
	}
};

}

#endif
