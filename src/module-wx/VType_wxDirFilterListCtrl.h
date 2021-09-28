//==============================================================================
// VType_wxDirFilterListCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDIRFILTERLISTCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXDIRFILTERLISTCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dirctrl.h>
#include "Util.h"
#include "VType_wxChoice.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDirFilterListCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDirFilterListCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDirFilterListCtrl VTYPE_wxDirFilterListCtrl;

//------------------------------------------------------------------------------
// Value_wxDirFilterListCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDirFilterListCtrl : public Value_wxChoice {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDirFilterListCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDirFilterListCtrl");
protected:
	wxWeakRef<wxDirFilterListCtrl> _pEntity;
public:
	class EntityT : public wxDirFilterListCtrl {
	public:
		using wxDirFilterListCtrl::wxDirFilterListCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDirFilterListCtrl() = delete;
	explicit Value_wxDirFilterListCtrl(wxDirFilterListCtrl* pEntity, VType& vtype = VTYPE_wxDirFilterListCtrl) :
		Value_wxChoice(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxDirFilterListCtrl(const Value_wxDirFilterListCtrl& src) = delete;
	Value_wxDirFilterListCtrl& operator=(const Value_wxDirFilterListCtrl& src) = delete;
	// Move constructor/operator
	Value_wxDirFilterListCtrl(Value_wxDirFilterListCtrl&& src) noexcept = delete;
	Value_wxDirFilterListCtrl& operator=(Value_wxDirFilterListCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDirFilterListCtrl() = default;
public:
	wxDirFilterListCtrl& GetEntity() { return *_pEntity; }
	const wxDirFilterListCtrl& GetEntity() const { return *_pEntity; }
	wxDirFilterListCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxDirFilterListCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxDirFilterListCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDirFilterListCtrl&>(value).GetEntity();
	}
	static const wxDirFilterListCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDirFilterListCtrl&>(value).GetEntity();
	}
	static wxDirFilterListCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDirFilterListCtrl&>(value).GetEntityPtr();
	}
	static const wxDirFilterListCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDirFilterListCtrl&>(value).GetEntityPtr();
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