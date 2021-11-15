//==============================================================================
// VType_wxCollapsibleHeaderCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLLAPSIBLEHEADERCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXCOLLAPSIBLEHEADERCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/collheaderctrl.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCollapsibleHeaderCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCollapsibleHeaderCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCollapsibleHeaderCtrl VTYPE_wxCollapsibleHeaderCtrl;

//------------------------------------------------------------------------------
// Value_wxCollapsibleHeaderCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCollapsibleHeaderCtrl : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCollapsibleHeaderCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCollapsibleHeaderCtrl");
protected:
	wxWeakRef<wxCollapsibleHeaderCtrl> _pEntity;
public:
	class EntityT : public wxCollapsibleHeaderCtrl {
	public:
		using wxCollapsibleHeaderCtrl::wxCollapsibleHeaderCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxCollapsibleHeaderCtrl() = delete;
	explicit Value_wxCollapsibleHeaderCtrl(wxCollapsibleHeaderCtrl* pEntity, VType& vtype = VTYPE_wxCollapsibleHeaderCtrl) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxCollapsibleHeaderCtrl(const Value_wxCollapsibleHeaderCtrl& src) = delete;
	Value_wxCollapsibleHeaderCtrl& operator=(const Value_wxCollapsibleHeaderCtrl& src) = delete;
	// Move constructor/operator
	Value_wxCollapsibleHeaderCtrl(Value_wxCollapsibleHeaderCtrl&& src) noexcept = delete;
	Value_wxCollapsibleHeaderCtrl& operator=(Value_wxCollapsibleHeaderCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCollapsibleHeaderCtrl() = default;
public:
	wxCollapsibleHeaderCtrl& GetEntity() { return *_pEntity; }
	const wxCollapsibleHeaderCtrl& GetEntity() const { return *_pEntity; }
	wxCollapsibleHeaderCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxCollapsibleHeaderCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxCollapsibleHeaderCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCollapsibleHeaderCtrl&>(value).GetEntity();
	}
	static const wxCollapsibleHeaderCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCollapsibleHeaderCtrl&>(value).GetEntity();
	}
	static wxCollapsibleHeaderCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCollapsibleHeaderCtrl&>(value).GetEntityPtr();
	}
	static const wxCollapsibleHeaderCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCollapsibleHeaderCtrl&>(value).GetEntityPtr();
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
