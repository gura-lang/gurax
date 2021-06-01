//==============================================================================
// VType_wxControl.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCONTROL_H
#define GURAX_MODULE_WX_VTYPE_WXCONTROL_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxControl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxControl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxControl VTYPE_wxControl;

//------------------------------------------------------------------------------
// Value_wxControl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxControl : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxControl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxControl");
public:
	class EntityT : public wxControl {
	public:
		using wxControl::wxControl;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxControl() = delete;
	explicit Value_wxControl(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxControl) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxControl(const Value_wxControl& src) = delete;
	Value_wxControl& operator=(const Value_wxControl& src) = delete;
	// Move constructor/operator
	Value_wxControl(Value_wxControl&& src) noexcept = delete;
	Value_wxControl& operator=(Value_wxControl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxControl() = default;
public:
	wxControl* GetEntityPtr() {
		return reinterpret_cast<wxControl*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxControl* GetEntityPtr() const {
		return reinterpret_cast<const wxControl*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxControl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxControl&>(value).GetEntityPtr();
	}
	static const wxControl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxControl&>(value).GetEntityPtr();
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
