//==============================================================================
// VType_Image.h
//==============================================================================
#ifndef GURAX_VTYPE_IMAGE_H
#define GURAX_VTYPE_IMAGE_H
#include "VType_Object.h"
#include "Image.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Image
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Image : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Image VTYPE_Image;

//------------------------------------------------------------------------------
// Value_Image
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Image : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Image);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Image");
protected:
	RefPtr<Image> _pImage;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Image() = delete;
	Value_Image(Image* pImage, VType& vtype = VTYPE_Image) : Value_Object(vtype), _pImage(pImage) {}
	// Copy constructor/operator
	Value_Image(const Value_Image& src) : Value_Object(src), _pImage(src._pImage.Reference()) {}
	Value_Image& operator=(const Value_Image& src) = delete;
	// Move constructor/operator
	Value_Image(Value_Image&& src) = delete;
	Value_Image& operator=(Value_Image&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Image() = default;
public:
	Image& GetImage() { return *_pImage; }
	const Image& GetImage() const { return *_pImage; }
public:
	static Image& GetImage(Value& value) {
		return dynamic_cast<Value_Image&>(value).GetImage();
	}
	static const Image& GetImage(const Value& value) {
		return dynamic_cast<const Value_Image&>(value).GetImage();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetImage().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetImage().IsEqualTo(Value_Image::GetImage(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetImage().IsLessThan(Value_Image::GetImage(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetImage().ToString(ss);
	}
};

}

#endif
