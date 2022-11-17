//==============================================================================
// VType_Pixel.h
//==============================================================================
#ifndef GURAX_VTYPE_PIXEL_H
#define GURAX_VTYPE_PIXEL_H
#include "VType_Object.h"
#include "Pixel.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Pixel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Pixel : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Pixel VTYPE_Pixel;

//------------------------------------------------------------------------------
// Value_Pixel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Pixel : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Pixel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Pixel");
protected:
	RefPtr<Pixel> _pPixel;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Pixel() = delete;
	explicit Value_Pixel(Pixel* pPixel, VType& vtype = VTYPE_Pixel) :
		Value_Object(vtype), _pPixel(pPixel) {}
	// Copy constructor/operator
	Value_Pixel(const Value_Pixel& src) :
		Value_Object(src), _pPixel(src._pPixel->Reference()) {}
	Value_Pixel& operator=(const Value_Pixel& src) = delete;
	// Move constructor/operator
	Value_Pixel(Value_Pixel&& src) = delete;
	Value_Pixel& operator=(Value_Pixel&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Pixel() = default;
public:
	Pixel& GetPixel() { return *_pPixel; }
	const Pixel& GetPixel() const { return *_pPixel; }
public:
	static Pixel& GetPixel(Value& value) {
		return dynamic_cast<Value_Pixel&>(value).GetPixel();
	}
	static const Pixel& GetPixel(const Value& value) {
		return dynamic_cast<const Value_Pixel&>(value).GetPixel();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPixel().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPixel().IsEqualTo(Value_Pixel::GetPixel(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPixel().IsLessThan(Value_Pixel::GetPixel(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
