﻿//==============================================================================
// VType_wxWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxWindow VTYPE_wxWindow;

//------------------------------------------------------------------------------
// Value_wxWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxWindow : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxWindow");
protected:
	wxWeakRef<wxWindow> _pEntity;
public:
	class EntityT : public wxWindow {
	public:
		using wxWindow::wxWindow;
	public:
		EntityCore core_gurax;
		virtual bool AcceptsFocus() const override;
		virtual bool AcceptsFocusFromKeyboard() const override;
		virtual bool AcceptsFocusRecursively() const override;
		virtual bool HasFocus() const override;
		virtual void SetCanFocus(bool canFocus) override;
		bool public_AcceptsFocus() const { return wxWindow::AcceptsFocus(); }
		bool public_AcceptsFocusFromKeyboard() const { return wxWindow::AcceptsFocusFromKeyboard(); }
		bool public_AcceptsFocusRecursively() const { return wxWindow::AcceptsFocusRecursively(); }
		bool public_HasFocus() const { return wxWindow::HasFocus(); }
		void public_SetCanFocus(bool canFocus) { wxWindow::SetCanFocus(canFocus); }
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxWindow() = delete;
	explicit Value_wxWindow(wxWindow* pEntity, VType& vtype = VTYPE_wxWindow) :
		Value_wxEvtHandler(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxWindow(const Value_wxWindow& src) = delete;
	Value_wxWindow& operator=(const Value_wxWindow& src) = delete;
	// Move constructor/operator
	Value_wxWindow(Value_wxWindow&& src) noexcept = delete;
	Value_wxWindow& operator=(Value_wxWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxWindow() = default;
public:
	wxWindow& GetEntity() { return *_pEntity; }
	const wxWindow& GetEntity() const { return *_pEntity; }
	wxWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxWindow&>(value).GetEntity();
	}
	static const wxWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxWindow&>(value).GetEntity();
	}
	static wxWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxWindow&>(value).GetEntityPtr();
	}
	static const wxWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxWindow&>(value).GetEntityPtr();
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
