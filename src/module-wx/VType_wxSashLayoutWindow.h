//==============================================================================
// VType_wxSashLayoutWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSASHLAYOUTWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXSASHLAYOUTWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxSashWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSashLayoutWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSashLayoutWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSashLayoutWindow VTYPE_wxSashLayoutWindow;

//------------------------------------------------------------------------------
// Value_wxSashLayoutWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSashLayoutWindow : public Value_wxSashWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSashLayoutWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSashLayoutWindow");
protected:
	wxWeakRef<wxSashLayoutWindow> _pEntity;
public:
	class EntityT : public wxSashLayoutWindow {
	public:
		using wxSashLayoutWindow::wxSashLayoutWindow;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSashLayoutWindow() = delete;
	explicit Value_wxSashLayoutWindow(wxSashLayoutWindow* pEntity, VType& vtype = VTYPE_wxSashLayoutWindow) :
		Value_wxSashWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxSashLayoutWindow(const Value_wxSashLayoutWindow& src) = delete;
	Value_wxSashLayoutWindow& operator=(const Value_wxSashLayoutWindow& src) = delete;
	// Move constructor/operator
	Value_wxSashLayoutWindow(Value_wxSashLayoutWindow&& src) noexcept = delete;
	Value_wxSashLayoutWindow& operator=(Value_wxSashLayoutWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSashLayoutWindow() = default;
public:
	wxSashLayoutWindow& GetEntity() { return *_pEntity; }
	const wxSashLayoutWindow& GetEntity() const { return *_pEntity; }
	wxSashLayoutWindow* GetEntityPtr() { return _pEntity.get(); }
	const wxSashLayoutWindow* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxSashLayoutWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSashLayoutWindow&>(value).GetEntity();
	}
	static const wxSashLayoutWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSashLayoutWindow&>(value).GetEntity();
	}
	static wxSashLayoutWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSashLayoutWindow&>(value).GetEntityPtr();
	}
	static const wxSashLayoutWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSashLayoutWindow&>(value).GetEntityPtr();
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