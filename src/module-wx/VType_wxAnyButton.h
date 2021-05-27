//==============================================================================
// VType_wxAnyButton.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_ANYBUTTON_H
#define GURAX_MODULE_WX_VTYPE_ANYBUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_Control.h"

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
class GURAX_DLLDECLARE Value_wxAnyButton : public Value_Control {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAnyButton);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAnyButton");
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
	Value_wxAnyButton() = delete;
	explicit Value_wxAnyButton(wxAnyButton* pEntity, VType& vtype = VTYPE_wxAnyButton) :
		Value_Control(pEntity, vtype) {}
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
	wxAnyButton* GetEntity() { return wxDynamicCast(Value_Control::GetEntity(), wxAnyButton); }
	const wxAnyButton* GetEntity() const { return wxDynamicCast(Value_Control::GetEntity(), wxAnyButton); }
public:
	static wxAnyButton* GetEntity(Value& value) {
		return dynamic_cast<Value_wxAnyButton&>(value).GetEntity();
	}
	static const wxAnyButton* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAnyButton&>(value).GetEntity();
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
