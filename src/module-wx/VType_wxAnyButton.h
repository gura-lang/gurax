//==============================================================================
// VType_wxAnyButton.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXANYBUTTON_H
#define GURAX_MODULE_WX_VTYPE_WXANYBUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAnyButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAnyButton : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAnyButton VTYPE_wxAnyButton;

//------------------------------------------------------------------------------
// Value_wxAnyButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAnyButton : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAnyButton);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAnyButton");
public:
	class EntityT : public wxAnyButton {
	public:
		using wxAnyButton::wxAnyButton;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAnyButton() = delete;
	explicit Value_wxAnyButton(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxAnyButton) :
		Value_wxControl(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxAnyButton(const Value_wxAnyButton& src) = delete;
	Value_wxAnyButton& operator=(const Value_wxAnyButton& src) = delete;
	// Move constructor/operator
	Value_wxAnyButton(Value_wxAnyButton&& src) noexcept = delete;
	Value_wxAnyButton& operator=(Value_wxAnyButton&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAnyButton() = default;
public:
	wxAnyButton& GetEntity() {
		return reinterpret_cast<wxAnyButton&>(Value_wxEvtHandler::GetEntity());
	}
	const wxAnyButton& GetEntity() const {
		return reinterpret_cast<const wxAnyButton&>(Value_wxEvtHandler::GetEntity());
	}
	wxAnyButton* GetEntityPtr() {
		return reinterpret_cast<wxAnyButton*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxAnyButton* GetEntityPtr() const {
		return reinterpret_cast<const wxAnyButton*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxAnyButton& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAnyButton&>(value).GetEntity();
	}
	static const wxAnyButton& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAnyButton&>(value).GetEntity();
	}
	static wxAnyButton* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAnyButton&>(value).GetEntityPtr();
	}
	static const wxAnyButton* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAnyButton&>(value).GetEntityPtr();
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
