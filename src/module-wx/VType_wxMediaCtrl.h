//==============================================================================
// VType_wxMediaCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMEDIACTRL_H
#define GURAX_MODULE_WX_VTYPE_WXMEDIACTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMediaCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMediaCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMediaCtrl VTYPE_wxMediaCtrl;

//------------------------------------------------------------------------------
// Value_wxMediaCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMediaCtrl : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMediaCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMediaCtrl");
protected:
	wxWeakRef<wxMediaCtrl> _pEntity;
public:
	class EntityT : public wxMediaCtrl {
	public:
		using wxMediaCtrl::wxMediaCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMediaCtrl() = delete;
	explicit Value_wxMediaCtrl(wxMediaCtrl* pEntity, VType& vtype = VTYPE_wxMediaCtrl) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxMediaCtrl(const Value_wxMediaCtrl& src) = delete;
	Value_wxMediaCtrl& operator=(const Value_wxMediaCtrl& src) = delete;
	// Move constructor/operator
	Value_wxMediaCtrl(Value_wxMediaCtrl&& src) noexcept = delete;
	Value_wxMediaCtrl& operator=(Value_wxMediaCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMediaCtrl() = default;
public:
	wxMediaCtrl& GetEntity() { return *_pEntity; }
	const wxMediaCtrl& GetEntity() const { return *_pEntity; }
	wxMediaCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxMediaCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxMediaCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMediaCtrl&>(value).GetEntity();
	}
	static const wxMediaCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMediaCtrl&>(value).GetEntity();
	}
	static wxMediaCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMediaCtrl&>(value).GetEntityPtr();
	}
	static const wxMediaCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMediaCtrl&>(value).GetEntityPtr();
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
