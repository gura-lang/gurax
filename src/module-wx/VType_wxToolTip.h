//==============================================================================
// VType_wxToolTip.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTOOLTIP_H
#define GURAX_MODULE_WX_VTYPE_WXTOOLTIP_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxToolTip
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxToolTip : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxToolTip VTYPE_wxToolTip;

//------------------------------------------------------------------------------
// Value_wxToolTip
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxToolTip : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxToolTip);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxToolTip");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxToolTip() = delete;
	explicit Value_wxToolTip(const wxToolTip& entity, VType& vtype = VTYPE_wxToolTip) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxToolTip(const Value_wxToolTip& src) = delete;
	Value_wxToolTip& operator=(const Value_wxToolTip& src) = delete;
	// Move constructor/operator
	Value_wxToolTip(Value_wxToolTip&& src) noexcept = delete;
	Value_wxToolTip& operator=(Value_wxToolTip&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxToolTip() = default;
public:
	wxToolTip& GetEntity() { return reinterpret_cast<wxToolTip&>(Value_wxObject::GetEntity()); }
	const wxToolTip& GetEntity() const { return reinterpret_cast<const wxToolTip&>(Value_wxObject::GetEntity()); }
	wxToolTip* GetEntityPtr() { return reinterpret_cast<wxToolTip*>(Value_wxObject::GetEntityPtr()); }\
	const wxToolTip* GetEntityPtr() const { return reinterpret_cast<const wxToolTip*>(Value_wxObject::GetEntityPtr()); }
public:
	static wxToolTip& GetEntity(Value& value) {
		return dynamic_cast<Value_wxToolTip&>(value).GetEntity();
	}
	static const wxToolTip& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxToolTip&>(value).GetEntity();
	}
	static wxToolTip* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxToolTip&>(value).GetEntityPtr();
	}
	static const wxToolTip* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxToolTip&>(value).GetEntityPtr();
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
