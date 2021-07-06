//==============================================================================
// VType_wxGDIObject.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGDIOBJECT_H
#define GURAX_MODULE_WX_VTYPE_WXGDIOBJECT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGDIObject
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGDIObject : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGDIObject VTYPE_wxGDIObject;

//------------------------------------------------------------------------------
// Value_wxGDIObject
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGDIObject : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGDIObject);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGDIObject");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGDIObject() = delete;
	explicit Value_wxGDIObject(const wxObject& entity, VType& vtype = VTYPE_wxGDIObject) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGDIObject(const Value_wxGDIObject& src) = delete;
	Value_wxGDIObject& operator=(const Value_wxGDIObject& src) = delete;
	// Move constructor/operator
	Value_wxGDIObject(Value_wxGDIObject&& src) noexcept = delete;
	Value_wxGDIObject& operator=(Value_wxGDIObject&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGDIObject() = default;
public:
	wxGDIObject& GetEntity() {
		return reinterpret_cast<wxGDIObject&>(Value_wxObject::GetEntity());
	}
	const wxGDIObject& GetEntity() const {
		return reinterpret_cast<const wxGDIObject&>(Value_wxObject::GetEntity());
	}
	wxGDIObject* GetEntityPtr() {
		return reinterpret_cast<wxGDIObject*>(Value_wxObject::GetEntityPtr());
	}
	const wxGDIObject* GetEntityPtr() const {
		return reinterpret_cast<const wxGDIObject*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxGDIObject& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGDIObject&>(value).GetEntity();
	}
	static const wxGDIObject& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGDIObject&>(value).GetEntity();
	}
	static wxGDIObject* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGDIObject&>(value).GetEntityPtr();
	}
	static const wxGDIObject* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGDIObject&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntityPtr(*this) == GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntityPtr(*this) < GetEntityPtr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif