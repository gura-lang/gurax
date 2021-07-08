//==============================================================================
// VType_wxCommandLinkButton.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOMMANDLINKBUTTON_H
#define GURAX_MODULE_WX_VTYPE_WXCOMMANDLINKBUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/commandlinkbutton.h>
#include "Util.h"
#include "VType_wxButton.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCommandLinkButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCommandLinkButton : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCommandLinkButton VTYPE_wxCommandLinkButton;

//------------------------------------------------------------------------------
// Value_wxCommandLinkButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCommandLinkButton : public Value_wxButton {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCommandLinkButton);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCommandLinkButton");
public:
	class EntityT : public wxCommandLinkButton {
	public:
		using wxCommandLinkButton::wxCommandLinkButton;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxCommandLinkButton() = delete;
	explicit Value_wxCommandLinkButton(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxCommandLinkButton) :
		Value_wxButton(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxCommandLinkButton(const Value_wxCommandLinkButton& src) = delete;
	Value_wxCommandLinkButton& operator=(const Value_wxCommandLinkButton& src) = delete;
	// Move constructor/operator
	Value_wxCommandLinkButton(Value_wxCommandLinkButton&& src) noexcept = delete;
	Value_wxCommandLinkButton& operator=(Value_wxCommandLinkButton&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCommandLinkButton() = default;
public:
	wxCommandLinkButton& GetEntity() {
		return reinterpret_cast<wxCommandLinkButton&>(Value_wxEvtHandler::GetEntity());
	}
	const wxCommandLinkButton& GetEntity() const {
		return reinterpret_cast<const wxCommandLinkButton&>(Value_wxEvtHandler::GetEntity());
	}
	wxCommandLinkButton* GetEntityPtr() {
		return reinterpret_cast<wxCommandLinkButton*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxCommandLinkButton* GetEntityPtr() const {
		return reinterpret_cast<const wxCommandLinkButton*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxCommandLinkButton& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCommandLinkButton&>(value).GetEntity();
	}
	static const wxCommandLinkButton& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCommandLinkButton&>(value).GetEntity();
	}
	static wxCommandLinkButton* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCommandLinkButton&>(value).GetEntityPtr();
	}
	static const wxCommandLinkButton* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCommandLinkButton&>(value).GetEntityPtr();
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
