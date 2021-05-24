//==============================================================================
// VType_AnyButton.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_ANYBUTTON_H
#define GURAX_MODULE_WX_VTYPE_ANYBUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_Control.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_AnyButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_AnyButton : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_AnyButton VTYPE_AnyButton;

//------------------------------------------------------------------------------
// Value_AnyButton
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_AnyButton : public Value_Control {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_AnyButton);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_AnyButton");
public:
	class EntityT : public wxAnyButton {
	public:
		using EntitySuper = wxAnyButton;
		using wxAnyButton::wxAnyButton;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_AnyButton() = delete;
	explicit Value_AnyButton(wxAnyButton* pEntity, VType& vtype = VTYPE_AnyButton) :
		Value_Control(pEntity, vtype) {}
	// Copy constructor/operator
	Value_AnyButton(const Value_AnyButton& src) = delete;
	Value_AnyButton& operator=(const Value_AnyButton& src) = delete;
	// Move constructor/operator
	Value_AnyButton(Value_AnyButton&& src) noexcept = delete;
	Value_AnyButton& operator=(Value_AnyButton&& src) noexcept = delete;
protected:
	// Destructor
	~Value_AnyButton() = default;
public:
	wxAnyButton* GetEntity() { return wxDynamicCast(Value_Control::GetEntity(), wxAnyButton); }
	const wxAnyButton* GetEntity() const { return wxDynamicCast(Value_Control::GetEntity(), wxAnyButton); }
public:
	static wxAnyButton* GetEntity(Value& value) {
		return dynamic_cast<Value_AnyButton&>(value).GetEntity();
	}
	static const wxAnyButton* GetEntity(const Value& value) {
		return dynamic_cast<const Value_AnyButton&>(value).GetEntity();
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
