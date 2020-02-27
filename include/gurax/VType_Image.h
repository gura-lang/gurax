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
	class GURAX_DLLDECLARE Iterator_Scan : public Iterator {
	private:
		RefPtr<Image> _pImage;
		Image::Scanner _scanner;
		bool _doneFlag;
	public:
		Iterator_Scan(Image* pImage, const Image::Scanner& scanner) :
			_pImage(pImage), _scanner(scanner), _doneFlag(scanner.IsEmpty()) {}
	public:
		const Image::Scanner& GetScanner() const { return _scanner; }
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return Flag::Finite | Flag::LenDetermined;
		}
		virtual size_t GetLength() const override { return _scanner.GetLength(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
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
