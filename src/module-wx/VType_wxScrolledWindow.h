﻿//==============================================================================
// VType_wxScrolledWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSCROLLEDWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXSCROLLEDWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxPanel.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxScrolledWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxScrolledWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxScrolledWindow VTYPE_wxScrolledWindow;

//------------------------------------------------------------------------------
// Value_wxScrolledWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxScrolledWindow : public Value_wxPanel {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxScrolledWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxScrolledWindow");
protected:
	wxWeakRef<wxScrolledWindow> _pEntity;
public:
	class EntityT : public wxScrolledWindow {
	public:
		using wxScrolledWindow::wxScrolledWindow;
	public:
		EntityCore core_gurax;
		virtual void OnDraw(wxDC& dc) override;
		virtual void AdjustScrollbars() override;
		void public_OnDraw(wxDC& dc) { wxScrolledWindow::OnDraw(dc); }
		void public_AdjustScrollbars() { wxScrolledWindow::AdjustScrollbars(); }
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxScrolledWindow() = delete;
	explicit Value_wxScrolledWindow(wxScrolledWindow* pEntity, VType& vtype = VTYPE_wxScrolledWindow) :
		Value_wxPanel(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxScrolledWindow(const Value_wxScrolledWindow& src) = delete;
	Value_wxScrolledWindow& operator=(const Value_wxScrolledWindow& src) = delete;
	// Move constructor/operator
	Value_wxScrolledWindow(Value_wxScrolledWindow&& src) noexcept = delete;
	Value_wxScrolledWindow& operator=(Value_wxScrolledWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxScrolledWindow() = default;
public:
	wxScrolledWindow& GetEntity() { return *_pEntity; }
	const wxScrolledWindow& GetEntity() const { return *_pEntity; }
	wxScrolledWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxScrolledWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxScrolledWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxScrolledWindow&>(value).GetEntity();
	}
	static const wxScrolledWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxScrolledWindow&>(value).GetEntity();
	}
	static wxScrolledWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxScrolledWindow&>(value).GetEntityPtr();
	}
	static const wxScrolledWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxScrolledWindow&>(value).GetEntityPtr();
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
