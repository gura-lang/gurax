//==============================================================================
// VType_ImageDescriptor.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_IMAGEDESCRIPTOR_H
#define GURAX_MODULE_GIF_VTYPE_IMAGEDESCRIPTOR_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_ImageDescriptor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ImageDescriptor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ImageDescriptor VTYPE_ImageDescriptor;

//------------------------------------------------------------------------------
// Value_ImageDescriptor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ImageDescriptor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ImageDescriptor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ImageDescriptor");
protected:
	RefPtr<Content::ImageProp> _pImageProp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ImageDescriptor() = delete;
	explicit Value_ImageDescriptor(Content::ImageProp* pImageProp, VType& vtype = VTYPE_ImageDescriptor) :
		Value_Object(vtype), _pImageProp(pImageProp) {}
	// Copy constructor/operator
	Value_ImageDescriptor(const Value_ImageDescriptor& src) :
		Value_Object(src), _pImageProp(src._pImageProp->Reference()) {}
	Value_ImageDescriptor& operator=(const Value_ImageDescriptor& src) = delete;
	// Move constructor/operator
	Value_ImageDescriptor(Value_ImageDescriptor&& src) noexcept = delete;
	Value_ImageDescriptor& operator=(Value_ImageDescriptor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ImageDescriptor() = default;
public:
	Content::ImageProp& GetImageProp() { return *_pImageProp; }
	const Content::ImageProp& GetImageProp() const { return *_pImageProp; }
public:
	static Content::ImageProp& GetImageProp(Value& value) {
		return dynamic_cast<Value_ImageDescriptor&>(value).GetImageProp();
	}
	static const Content::ImageProp& GetImageProp(const Value& value) {
		return dynamic_cast<const Value_ImageDescriptor&>(value).GetImageProp();
	}
	static Content::ImageProp* GetEntityPtr(Value& value) { return &GetImageProp(value); }
	static const Content::ImageProp* GetEntityPtr(const Value& value) { return &GetImageProp(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetImageProp().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetImageProp().IsEqualTo(Value_ImageDescriptor::GetImageProp(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetImageProp().IsLessThan(Value_ImageDescriptor::GetImageProp(value)) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
