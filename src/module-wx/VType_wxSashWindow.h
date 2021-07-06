//==============================================================================
// VType_wxSashWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSASHWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXSASHWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSashWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSashWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSashWindow VTYPE_wxSashWindow;

//------------------------------------------------------------------------------
// Value_wxSashWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSashWindow : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSashWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSashWindow");
public:
	class EntityT : public wxSashWindow {
	public:
		using wxSashWindow::wxSashWindow;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSashWindow() = delete;
	explicit Value_wxSashWindow(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxSashWindow) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxSashWindow(const Value_wxSashWindow& src) = delete;
	Value_wxSashWindow& operator=(const Value_wxSashWindow& src) = delete;
	// Move constructor/operator
	Value_wxSashWindow(Value_wxSashWindow&& src) noexcept = delete;
	Value_wxSashWindow& operator=(Value_wxSashWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSashWindow() = default;
public:
	wxSashWindow& GetEntity() {
		return reinterpret_cast<wxSashWindow&>(Value_wxEvtHandler::GetEntity());
	}
	const wxSashWindow& GetEntity() const {
		return reinterpret_cast<const wxSashWindow&>(Value_wxEvtHandler::GetEntity());
	}
	wxSashWindow* GetEntityPtr() {
		return reinterpret_cast<wxSashWindow*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxSashWindow* GetEntityPtr() const {
		return reinterpret_cast<const wxSashWindow*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxSashWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSashWindow&>(value).GetEntity();
	}
	static const wxSashWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSashWindow&>(value).GetEntity();
	}
	static wxSashWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSashWindow&>(value).GetEntityPtr();
	}
	static const wxSashWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSashWindow&>(value).GetEntityPtr();
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
