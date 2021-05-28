//==============================================================================
// VType_wxButton.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXBUTTON_H
#define GURAX_MODULE_WX_VTYPE_WXBUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxAnyButton.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxButton : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxButton VTYPE_wxButton;

//------------------------------------------------------------------------------
// Value_wxButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxButton : public Value_wxAnyButton {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxButton);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxButton");
public:
	class EntityT : public wxButton {
	public:
		using wxButton::wxButton;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxButton() = delete;
	explicit Value_wxButton(wxTrackable* pEntity, VType& vtype = VTYPE_wxButton) :
		Value_wxAnyButton(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxButton(const Value_wxButton& src) = delete;
	Value_wxButton& operator=(const Value_wxButton& src) = delete;
	// Move constructor/operator
	Value_wxButton(Value_wxButton&& src) noexcept = delete;
	Value_wxButton& operator=(Value_wxButton&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxButton() = default;
public:
	wxButton* GetEntity() {
		return reinterpret_cast<wxButton*>(Value_wxTrackable::GetEntity());
	}
	const wxButton* GetEntity() const {
		return reinterpret_cast<const wxButton*>(Value_wxTrackable::GetEntity());
	}
public:
	static wxButton* GetEntity(Value& value) {
		return dynamic_cast<Value_wxButton&>(value).GetEntity();
	}
	static const wxButton* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxButton&>(value).GetEntity();
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
