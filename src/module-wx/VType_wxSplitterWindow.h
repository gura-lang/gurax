﻿//==============================================================================
// VType_wxSplitterWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSPLITTERWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXSPLITTERWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/splitter.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSplitterWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSplitterWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSplitterWindow VTYPE_wxSplitterWindow;

//------------------------------------------------------------------------------
// Value_wxSplitterWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSplitterWindow : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSplitterWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSplitterWindow");
protected:
	wxWeakRef<wxSplitterWindow> _pEntity;
public:
	class EntityT : public wxSplitterWindow {
	public:
		using wxSplitterWindow::wxSplitterWindow;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSplitterWindow() = delete;
	explicit Value_wxSplitterWindow(wxSplitterWindow* pEntity, VType& vtype = VTYPE_wxSplitterWindow) :
		Value_wxWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxSplitterWindow(const Value_wxSplitterWindow& src) = delete;
	Value_wxSplitterWindow& operator=(const Value_wxSplitterWindow& src) = delete;
	// Move constructor/operator
	Value_wxSplitterWindow(Value_wxSplitterWindow&& src) noexcept = delete;
	Value_wxSplitterWindow& operator=(Value_wxSplitterWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSplitterWindow() = default;
public:
	wxSplitterWindow& GetEntity() { return *_pEntity; }
	const wxSplitterWindow& GetEntity() const { return *_pEntity; }
	wxSplitterWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxSplitterWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxSplitterWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSplitterWindow&>(value).GetEntity();
	}
	static const wxSplitterWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSplitterWindow&>(value).GetEntity();
	}
	static wxSplitterWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSplitterWindow&>(value).GetEntityPtr();
	}
	static const wxSplitterWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSplitterWindow&>(value).GetEntityPtr();
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
