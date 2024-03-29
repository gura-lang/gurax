﻿//==============================================================================
// VType_wxPopupWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPOPUPWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXPOPUPWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/popupwin.h>
#include "Util.h"
#include "VType_wxNonOwnedWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPopupWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPopupWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPopupWindow VTYPE_wxPopupWindow;

//------------------------------------------------------------------------------
// Value_wxPopupWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPopupWindow : public Value_wxNonOwnedWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPopupWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPopupWindow");
protected:
	wxWeakRef<wxPopupWindow> _pEntity;
public:
	class EntityT : public wxPopupWindow {
	public:
		using wxPopupWindow::wxPopupWindow;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPopupWindow() = delete;
	explicit Value_wxPopupWindow(wxPopupWindow* pEntity, VType& vtype = VTYPE_wxPopupWindow) :
		Value_wxNonOwnedWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxPopupWindow(const Value_wxPopupWindow& src) = delete;
	Value_wxPopupWindow& operator=(const Value_wxPopupWindow& src) = delete;
	// Move constructor/operator
	Value_wxPopupWindow(Value_wxPopupWindow&& src) noexcept = delete;
	Value_wxPopupWindow& operator=(Value_wxPopupWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPopupWindow() = default;
public:
	wxPopupWindow& GetEntity() { return *_pEntity; }
	const wxPopupWindow& GetEntity() const { return *_pEntity; }
	wxPopupWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxPopupWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxPopupWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPopupWindow&>(value).GetEntity();
	}
	static const wxPopupWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPopupWindow&>(value).GetEntity();
	}
	static wxPopupWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPopupWindow&>(value).GetEntityPtr();
	}
	static const wxPopupWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPopupWindow&>(value).GetEntityPtr();
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
