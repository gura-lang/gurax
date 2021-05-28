//==============================================================================
// VType_wxWindow.h
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
public:
	class EntityT : public wxWindow {
	public:
		using wxWindow::wxWindow;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxWindow() = delete;
	explicit Value_wxWindow(wxTrackable* pEntity, VType& vtype = VTYPE_wxWindow) :
		Value_wxEvtHandler(pEntity, vtype) {}
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
	wxWindow* GetEntity() {
		return reinterpret_cast<wxWindow*>(Value_wxTrackable::GetEntity());
	}
	const wxWindow* GetEntity() const {
		return reinterpret_cast<const wxWindow*>(Value_wxTrackable::GetEntity());
	}
public:
	static wxWindow* GetEntity(Value& value) {
		return dynamic_cast<Value_wxWindow&>(value).GetEntity();
	}
	static const wxWindow* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxWindow&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntity(*this) < GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
