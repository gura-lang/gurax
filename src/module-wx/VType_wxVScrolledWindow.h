//==============================================================================
// VType_wxVScrolledWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVSCROLLEDWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXVSCROLLEDWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/vscroll.h>
#include "Util.h"
#include "VType_wxPanel.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxVScrolledWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxVScrolledWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxVScrolledWindow VTYPE_wxVScrolledWindow;

//------------------------------------------------------------------------------
// Value_wxVScrolledWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxVScrolledWindow : public Value_wxPanel {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxVScrolledWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxVScrolledWindow");
protected:
	wxWeakRef<wxVScrolledWindow> _pEntity;
public:
	class EntityT : public wxVScrolledWindow {
	public:
		using wxVScrolledWindow::wxVScrolledWindow;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxVScrolledWindow() = delete;
	explicit Value_wxVScrolledWindow(wxVScrolledWindow* pEntity, VType& vtype = VTYPE_wxVScrolledWindow) :
		Value_wxPanel(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxVScrolledWindow(const Value_wxVScrolledWindow& src) = delete;
	Value_wxVScrolledWindow& operator=(const Value_wxVScrolledWindow& src) = delete;
	// Move constructor/operator
	Value_wxVScrolledWindow(Value_wxVScrolledWindow&& src) noexcept = delete;
	Value_wxVScrolledWindow& operator=(Value_wxVScrolledWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxVScrolledWindow() = default;
public:
	wxVScrolledWindow& GetEntity() { return *_pEntity; }
	const wxVScrolledWindow& GetEntity() const { return *_pEntity; }
	wxVScrolledWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxVScrolledWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxVScrolledWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxVScrolledWindow&>(value).GetEntity();
	}
	static const wxVScrolledWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxVScrolledWindow&>(value).GetEntity();
	}
	static wxVScrolledWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxVScrolledWindow&>(value).GetEntityPtr();
	}
	static const wxVScrolledWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxVScrolledWindow&>(value).GetEntityPtr();
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
