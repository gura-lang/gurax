//==============================================================================
// VType_Control.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_CONTROL_H
#define GURAX_MODULE_WX_VTYPE_CONTROL_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Control
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Control : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Control VTYPE_Control;

//------------------------------------------------------------------------------
// Value_Control
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Control : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Control);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Control");
public:
	class EntityT : public wxControl {
	public:
		using EntitySuper = wxControl;
		using wxControl::wxControl;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_Control() = delete;
	explicit Value_Control(wxControl* pEntity, VType& vtype = VTYPE_Control) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Control(const Value_Control& src) = delete;
	Value_Control& operator=(const Value_Control& src) = delete;
	// Move constructor/operator
	Value_Control(Value_Control&& src) noexcept = delete;
	Value_Control& operator=(Value_Control&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Control() = default;
public:
	wxControl* GetEntity() { return wxDynamicCast(Value_wxWindow::GetEntity(), wxControl); }
	const wxControl* GetEntity() const { return wxDynamicCast(Value_wxWindow::GetEntity(), wxControl); }
public:
	static wxControl* GetEntity(Value& value) {
		return dynamic_cast<Value_Control&>(value).GetEntity();
	}
	static const wxControl* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Control&>(value).GetEntity();
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
