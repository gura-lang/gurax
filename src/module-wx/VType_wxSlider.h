﻿//==============================================================================
// VType_wxSlider.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSLIDER_H
#define GURAX_MODULE_WX_VTYPE_WXSLIDER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSlider
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSlider : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSlider VTYPE_wxSlider;

//------------------------------------------------------------------------------
// Value_wxSlider
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSlider : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSlider);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSlider");
protected:
	wxWeakRef<wxSlider> _pEntity;
public:
	class EntityT : public wxSlider {
	public:
		using wxSlider::wxSlider;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSlider() = delete;
	explicit Value_wxSlider(wxSlider* pEntity, VType& vtype = VTYPE_wxSlider) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxSlider(const Value_wxSlider& src) = delete;
	Value_wxSlider& operator=(const Value_wxSlider& src) = delete;
	// Move constructor/operator
	Value_wxSlider(Value_wxSlider&& src) noexcept = delete;
	Value_wxSlider& operator=(Value_wxSlider&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSlider() = default;
public:
	wxSlider& GetEntity() { return *_pEntity; }
	const wxSlider& GetEntity() const { return *_pEntity; }
	wxSlider* GetEntityPtr() { return _pEntity.get(); }
	const wxSlider* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxSlider& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSlider&>(value).GetEntity();
	}
	static const wxSlider& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSlider&>(value).GetEntity();
	}
	static wxSlider* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSlider&>(value).GetEntityPtr();
	}
	static const wxSlider* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSlider&>(value).GetEntityPtr();
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
