//==============================================================================
// VType_ImageProp.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_IMAGEPROP_H
#define GURAX_MODULE_GIF_VTYPE_IMAGEPROP_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_ImageProp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ImageProp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ImageProp VTYPE_ImageProp;

//------------------------------------------------------------------------------
// Value_ImageProp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ImageProp : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ImageProp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ImageProp");
protected:
	RefPtr<Content::ImageProp> _pImageProp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ImageProp() = delete;
	explicit Value_ImageProp(Content::ImageProp* pImageProp, VType& vtype = VTYPE_ImageProp) :
		Value_Object(vtype), _pImageProp(pImageProp) {}
	// Copy constructor/operator
	Value_ImageProp(const Value_ImageProp& src) :
		Value_Object(src), _pImageProp(src._pImageProp->Reference()) {}
	Value_ImageProp& operator=(const Value_ImageProp& src) = delete;
	// Move constructor/operator
	Value_ImageProp(Value_ImageProp&& src) noexcept = delete;
	Value_ImageProp& operator=(Value_ImageProp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ImageProp() = default;
public:
	Content::ImageProp& GetImageProp() { return *_pImageProp; }
	const Content::ImageProp& GetImageProp() const { return *_pImageProp; }
	Content::ImageProp* GetImagePropPtr() { return _pImageProp.get(); }
	const Content::ImageProp* GetImagePropPtr() const { return _pImageProp.get(); }
public:
	static Content::ImageProp& GetImageProp(Value& value) {
		return dynamic_cast<Value_ImageProp&>(value).GetImageProp();
	}
	static const Content::ImageProp& GetImageProp(const Value& value) {
		return dynamic_cast<const Value_ImageProp&>(value).GetImageProp();
	}
	static Content::ImageProp* GetImagePropPtr(Value& value) { return &GetImageProp(value); }
	static const Content::ImageProp* GetImagePropPtr(const Value& value) { return &GetImageProp(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetImagePropPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetImagePropPtr() == Value_ImageProp::GetImagePropPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetImagePropPtr() < Value_ImageProp::GetImagePropPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
