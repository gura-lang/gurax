//==============================================================================
// VType_wxSpinCtrlDouble.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSPINCTRLDOUBLE_H
#define GURAX_MODULE_WX_VTYPE_WXSPINCTRLDOUBLE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSpinCtrlDouble
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSpinCtrlDouble : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSpinCtrlDouble VTYPE_wxSpinCtrlDouble;

//------------------------------------------------------------------------------
// Value_wxSpinCtrlDouble
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSpinCtrlDouble : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSpinCtrlDouble);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSpinCtrlDouble");
protected:
	wxWeakRef<wxSpinCtrlDouble> _pEntity;
public:
	class EntityT : public wxSpinCtrlDouble {
	public:
		using wxSpinCtrlDouble::wxSpinCtrlDouble;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSpinCtrlDouble() = delete;
	explicit Value_wxSpinCtrlDouble(wxSpinCtrlDouble* pEntity, VType& vtype = VTYPE_wxSpinCtrlDouble) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxSpinCtrlDouble(const Value_wxSpinCtrlDouble& src) = delete;
	Value_wxSpinCtrlDouble& operator=(const Value_wxSpinCtrlDouble& src) = delete;
	// Move constructor/operator
	Value_wxSpinCtrlDouble(Value_wxSpinCtrlDouble&& src) noexcept = delete;
	Value_wxSpinCtrlDouble& operator=(Value_wxSpinCtrlDouble&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSpinCtrlDouble() = default;
public:
	wxSpinCtrlDouble& GetEntity() { return *_pEntity; }
	const wxSpinCtrlDouble& GetEntity() const { return *_pEntity; }
	wxSpinCtrlDouble* GetEntityPtr() { return _pEntity.get(); }
	const wxSpinCtrlDouble* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxSpinCtrlDouble& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSpinCtrlDouble&>(value).GetEntity();
	}
	static const wxSpinCtrlDouble& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSpinCtrlDouble&>(value).GetEntity();
	}
	static wxSpinCtrlDouble* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSpinCtrlDouble&>(value).GetEntityPtr();
	}
	static const wxSpinCtrlDouble* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSpinCtrlDouble&>(value).GetEntityPtr();
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
