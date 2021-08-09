//==============================================================================
// VType_wxTreeCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTREECTRL_H
#define GURAX_MODULE_WX_VTYPE_WXTREECTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/treectrl.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxTreeCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxTreeCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxTreeCtrl VTYPE_wxTreeCtrl;

//------------------------------------------------------------------------------
// Value_wxTreeCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxTreeCtrl : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxTreeCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxTreeCtrl");
protected:
	wxWeakRef<wxTreeCtrl> _pEntity;
public:
	class EntityT : public wxTreeCtrl {
	public:
		using wxTreeCtrl::wxTreeCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxTreeCtrl() = delete;
	explicit Value_wxTreeCtrl(wxTreeCtrl* pEntity, VType& vtype = VTYPE_wxTreeCtrl) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxTreeCtrl(const Value_wxTreeCtrl& src) = delete;
	Value_wxTreeCtrl& operator=(const Value_wxTreeCtrl& src) = delete;
	// Move constructor/operator
	Value_wxTreeCtrl(Value_wxTreeCtrl&& src) noexcept = delete;
	Value_wxTreeCtrl& operator=(Value_wxTreeCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxTreeCtrl() = default;
public:
	wxTreeCtrl& GetEntity() { return *_pEntity; }
	const wxTreeCtrl& GetEntity() const { return *_pEntity; }
	wxTreeCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxTreeCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxTreeCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxTreeCtrl&>(value).GetEntity();
	}
	static const wxTreeCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxTreeCtrl&>(value).GetEntity();
	}
	static wxTreeCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxTreeCtrl&>(value).GetEntityPtr();
	}
	static const wxTreeCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxTreeCtrl&>(value).GetEntityPtr();
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