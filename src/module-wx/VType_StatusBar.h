//==============================================================================
// VType_StatusBar.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_STATUSBAR_H
#define GURAX_MODULE_WX_VTYPE_STATUSBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_Control.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_StatusBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_StatusBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_StatusBar VTYPE_StatusBar;

//------------------------------------------------------------------------------
// Value_StatusBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_StatusBar : public Value_Control {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_StatusBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_StatusBar");
public:
	class EntityT : public wxStatusBar {
	public:
		using EntitySuper = wxStatusBar;
		using wxStatusBar::wxStatusBar;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_StatusBar() = delete;
	explicit Value_StatusBar(wxStatusBar* pEntity, VType& vtype = VTYPE_StatusBar) :
		Value_Control(pEntity, vtype) {}
	// Copy constructor/operator
	Value_StatusBar(const Value_StatusBar& src) = delete;
	Value_StatusBar& operator=(const Value_StatusBar& src) = delete;
	// Move constructor/operator
	Value_StatusBar(Value_StatusBar&& src) noexcept = delete;
	Value_StatusBar& operator=(Value_StatusBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_StatusBar() = default;
public:
	wxStatusBar* GetEntity() { return wxDynamicCast(Value_Control::GetEntity(), wxStatusBar); }
	const wxStatusBar* GetEntity() const { return wxDynamicCast(Value_Control::GetEntity(), wxStatusBar); }
public:
	static wxStatusBar* GetEntity(Value& value) {
		return dynamic_cast<Value_StatusBar&>(value).GetEntity();
	}
	static const wxStatusBar* GetEntity(const Value& value) {
		return dynamic_cast<const Value_StatusBar&>(value).GetEntity();
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
