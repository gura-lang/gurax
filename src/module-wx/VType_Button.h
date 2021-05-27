//==============================================================================
// VType_Button.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_BUTTON_H
#define GURAX_MODULE_WX_VTYPE_BUTTON_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxAnyButton.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Button
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Button : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Button VTYPE_Button;

//------------------------------------------------------------------------------
// Value_Button
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Button : public Value_wxAnyButton {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Button);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Button");
public:
	class EntityT : public wxButton {
	public:
		using EntitySuper = wxButton;
		using wxButton::wxButton;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_Button() = delete;
	explicit Value_Button(wxButton* pEntity, VType& vtype = VTYPE_Button) :
		Value_wxAnyButton(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Button(const Value_Button& src) = delete;
	Value_Button& operator=(const Value_Button& src) = delete;
	// Move constructor/operator
	Value_Button(Value_Button&& src) noexcept = delete;
	Value_Button& operator=(Value_Button&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Button() = default;
public:
	wxButton* GetEntity() { return wxDynamicCast(Value_wxAnyButton::GetEntity(), wxButton); }
	const wxButton* GetEntity() const { return wxDynamicCast(Value_wxAnyButton::GetEntity(), wxButton); }
public:
	static wxButton* GetEntity(Value& value) {
		return dynamic_cast<Value_Button&>(value).GetEntity();
	}
	static const wxButton* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Button&>(value).GetEntity();
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
