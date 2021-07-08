//==============================================================================
// VType_wxSpinButton.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSPINBUTTON_H
#define GURAX_MODULE_WX_VTYPE_WXSPINBUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSpinButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSpinButton : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSpinButton VTYPE_wxSpinButton;

//------------------------------------------------------------------------------
// Value_wxSpinButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSpinButton : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSpinButton);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSpinButton");
public:
	class EntityT : public wxSpinButton {
	public:
		using wxSpinButton::wxSpinButton;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSpinButton() = delete;
	explicit Value_wxSpinButton(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxSpinButton) :
		Value_wxControl(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxSpinButton(const Value_wxSpinButton& src) = delete;
	Value_wxSpinButton& operator=(const Value_wxSpinButton& src) = delete;
	// Move constructor/operator
	Value_wxSpinButton(Value_wxSpinButton&& src) noexcept = delete;
	Value_wxSpinButton& operator=(Value_wxSpinButton&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSpinButton() = default;
public:
	wxSpinButton& GetEntity() {
		return reinterpret_cast<wxSpinButton&>(Value_wxEvtHandler::GetEntity());
	}
	const wxSpinButton& GetEntity() const {
		return reinterpret_cast<const wxSpinButton&>(Value_wxEvtHandler::GetEntity());
	}
	wxSpinButton* GetEntityPtr() {
		return reinterpret_cast<wxSpinButton*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxSpinButton* GetEntityPtr() const {
		return reinterpret_cast<const wxSpinButton*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxSpinButton& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSpinButton&>(value).GetEntity();
	}
	static const wxSpinButton& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSpinButton&>(value).GetEntity();
	}
	static wxSpinButton* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSpinButton&>(value).GetEntityPtr();
	}
	static const wxSpinButton* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSpinButton&>(value).GetEntityPtr();
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
