//==============================================================================
// VType_wxAnimationCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXANIMATIONCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXANIMATIONCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/animate.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAnimationCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAnimationCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAnimationCtrl VTYPE_wxAnimationCtrl;

//------------------------------------------------------------------------------
// Value_wxAnimationCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAnimationCtrl : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAnimationCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAnimationCtrl");
protected:
	wxWeakRef<wxAnimationCtrl> _pEntity;
public:
	class EntityT : public wxAnimationCtrl {
	public:
		using wxAnimationCtrl::wxAnimationCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAnimationCtrl() = delete;
	explicit Value_wxAnimationCtrl(wxAnimationCtrl* pEntity, VType& vtype = VTYPE_wxAnimationCtrl) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxAnimationCtrl(const Value_wxAnimationCtrl& src) = delete;
	Value_wxAnimationCtrl& operator=(const Value_wxAnimationCtrl& src) = delete;
	// Move constructor/operator
	Value_wxAnimationCtrl(Value_wxAnimationCtrl&& src) noexcept = delete;
	Value_wxAnimationCtrl& operator=(Value_wxAnimationCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAnimationCtrl() = default;
public:
	wxAnimationCtrl& GetEntity() { return *_pEntity; }
	const wxAnimationCtrl& GetEntity() const { return *_pEntity; }
	wxAnimationCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxAnimationCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxAnimationCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAnimationCtrl&>(value).GetEntity();
	}
	static const wxAnimationCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAnimationCtrl&>(value).GetEntity();
	}
	static wxAnimationCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAnimationCtrl&>(value).GetEntityPtr();
	}
	static const wxAnimationCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAnimationCtrl&>(value).GetEntityPtr();
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
