//==============================================================================
// VType_wxMenuItem.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMENUITEM_H
#define GURAX_MODULE_WX_VTYPE_WXMENUITEM_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMenuItem
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMenuItem : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMenuItem VTYPE_wxMenuItem;

//------------------------------------------------------------------------------
// Value_wxMenuItem
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMenuItem : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMenuItem);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMenuItem");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMenuItem() = delete;
	explicit Value_wxMenuItem(const wxObject& entity, VType& vtype = VTYPE_wxMenuItem) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxMenuItem(const Value_wxMenuItem& src) = delete;
	Value_wxMenuItem& operator=(const Value_wxMenuItem& src) = delete;
	// Move constructor/operator
	Value_wxMenuItem(Value_wxMenuItem&& src) noexcept = delete;
	Value_wxMenuItem& operator=(Value_wxMenuItem&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMenuItem() = default;
public:
	wxMenuItem& GetEntity() {
		return reinterpret_cast<wxMenuItem&>(Value_wxObject::GetEntity());
	}
	const wxMenuItem& GetEntity() const {
		return reinterpret_cast<const wxMenuItem&>(Value_wxObject::GetEntity());
	}
	wxMenuItem* GetEntityPtr() {
		return reinterpret_cast<wxMenuItem*>(Value_wxObject::GetEntityPtr());
	}
	const wxMenuItem* GetEntityPtr() const {
		return reinterpret_cast<const wxMenuItem*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxMenuItem& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMenuItem&>(value).GetEntity();
	}
	static const wxMenuItem& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMenuItem&>(value).GetEntity();
	}
	static wxMenuItem* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMenuItem&>(value).GetEntityPtr();
	}
	static const wxMenuItem* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMenuItem&>(value).GetEntityPtr();
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
