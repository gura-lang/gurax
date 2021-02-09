//==============================================================================
// VType_GraphicControlExtension.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_GRAPHICCONTROLEXTENSION_H
#define GURAX_MODULE_GIF_VTYPE_GRAPHICCONTROLEXTENSION_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_GraphicControlExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GraphicControlExtension : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GraphicControlExtension VTYPE_GraphicControlExtension;

//------------------------------------------------------------------------------
// Value_GraphicControlExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GraphicControlExtension : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GraphicControlExtension);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GraphicControlExtension");
protected:
	RefPtr<Content::ImageProp> _pImageProp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GraphicControlExtension() = delete;
	explicit Value_GraphicControlExtension(Content::ImageProp* pImageProp, VType& vtype = VTYPE_GraphicControlExtension) :
		Value_Object(vtype), _pImageProp(pImageProp) {}
	// Copy constructor/operator
	Value_GraphicControlExtension(const Value_GraphicControlExtension& src) :
		Value_Object(src), _pImageProp(src._pImageProp->Reference()) {}
	Value_GraphicControlExtension& operator=(const Value_GraphicControlExtension& src) = delete;
	// Move constructor/operator
	Value_GraphicControlExtension(Value_GraphicControlExtension&& src) noexcept = delete;
	Value_GraphicControlExtension& operator=(Value_GraphicControlExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GraphicControlExtension() = default;
public:
	Content::ImageProp& GetImageProp() { return *_pImageProp; }
	const Content::ImageProp& GetImageProp() const { return *_pImageProp; }
public:
	static Content::ImageProp& GetImageProp(Value& value) {
		return dynamic_cast<Value_GraphicControlExtension&>(value).GetImageProp();
	}
	static const Content::ImageProp& GetImageProp(const Value& value) {
		return dynamic_cast<const Value_GraphicControlExtension&>(value).GetImageProp();
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
			GetImageProp().IsEqualTo(Value_GraphicControlExtension::GetImageProp(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetImageProp().IsLessThan(Value_GraphicControlExtension::GetImageProp(value)) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
