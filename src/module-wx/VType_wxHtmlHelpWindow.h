//==============================================================================
// VType_wxHtmlHelpWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLHELPWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLHELPWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/html/helpwnd.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlHelpWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlHelpWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlHelpWindow VTYPE_wxHtmlHelpWindow;

//------------------------------------------------------------------------------
// Value_wxHtmlHelpWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlHelpWindow : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlHelpWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlHelpWindow");
protected:
	wxWeakRef<wxHtmlHelpWindow> _pEntity;
public:
	class EntityT : public wxHtmlHelpWindow {
	public:
		using wxHtmlHelpWindow::wxHtmlHelpWindow;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlHelpWindow() = delete;
	explicit Value_wxHtmlHelpWindow(wxHtmlHelpWindow* pEntity, VType& vtype = VTYPE_wxHtmlHelpWindow) :
		Value_wxWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxHtmlHelpWindow(const Value_wxHtmlHelpWindow& src) = delete;
	Value_wxHtmlHelpWindow& operator=(const Value_wxHtmlHelpWindow& src) = delete;
	// Move constructor/operator
	Value_wxHtmlHelpWindow(Value_wxHtmlHelpWindow&& src) noexcept = delete;
	Value_wxHtmlHelpWindow& operator=(Value_wxHtmlHelpWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlHelpWindow() = default;
public:
	wxHtmlHelpWindow& GetEntity() { return *_pEntity; }
	const wxHtmlHelpWindow& GetEntity() const { return *_pEntity; }
	wxHtmlHelpWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxHtmlHelpWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxHtmlHelpWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlHelpWindow&>(value).GetEntity();
	}
	static const wxHtmlHelpWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlHelpWindow&>(value).GetEntity();
	}
	static wxHtmlHelpWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlHelpWindow&>(value).GetEntityPtr();
	}
	static const wxHtmlHelpWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlHelpWindow&>(value).GetEntityPtr();
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