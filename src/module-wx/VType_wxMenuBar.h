//==============================================================================
// VType_wxMenuBar.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMENUBAR_H
#define GURAX_MODULE_WX_VTYPE_WXMENUBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMenuBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMenuBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMenuBar VTYPE_wxMenuBar;

//------------------------------------------------------------------------------
// Value_wxMenuBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMenuBar : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMenuBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMenuBar");
public:
	class EntityT : public wxMenuBar {
	public:
		using wxMenuBar::wxMenuBar;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMenuBar() = delete;
	explicit Value_wxMenuBar(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxMenuBar) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxMenuBar(const Value_wxMenuBar& src) = delete;
	Value_wxMenuBar& operator=(const Value_wxMenuBar& src) = delete;
	// Move constructor/operator
	Value_wxMenuBar(Value_wxMenuBar&& src) noexcept = delete;
	Value_wxMenuBar& operator=(Value_wxMenuBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMenuBar() = default;
public:
	wxMenuBar& GetEntity() {
		return reinterpret_cast<wxMenuBar&>(Value_wxEvtHandler::GetEntity());
	}
	const wxMenuBar& GetEntity() const {
		return reinterpret_cast<const wxMenuBar&>(Value_wxEvtHandler::GetEntity());
	}
	wxMenuBar* GetEntityPtr() {
		return reinterpret_cast<wxMenuBar*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxMenuBar* GetEntityPtr() const {
		return reinterpret_cast<const wxMenuBar*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxMenuBar& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMenuBar&>(value).GetEntity();
	}
	static const wxMenuBar& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMenuBar&>(value).GetEntity();
	}
	static wxMenuBar* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMenuBar&>(value).GetEntityPtr();
	}
	static const wxMenuBar* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMenuBar&>(value).GetEntityPtr();
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
