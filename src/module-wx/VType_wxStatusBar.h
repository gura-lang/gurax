//==============================================================================
// VType_wxStatusBar.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSTATUSBAR_H
#define GURAX_MODULE_WX_VTYPE_WXSTATUSBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxStatusBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxStatusBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxStatusBar VTYPE_wxStatusBar;

//------------------------------------------------------------------------------
// Value_wxStatusBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxStatusBar : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxStatusBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxStatusBar");
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
	Value_wxStatusBar() = delete;
	explicit Value_wxStatusBar(wxTrackable* pEntity, VType& vtype = VTYPE_wxStatusBar) :
		Value_wxControl(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxStatusBar(const Value_wxStatusBar& src) = delete;
	Value_wxStatusBar& operator=(const Value_wxStatusBar& src) = delete;
	// Move constructor/operator
	Value_wxStatusBar(Value_wxStatusBar&& src) noexcept = delete;
	Value_wxStatusBar& operator=(Value_wxStatusBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxStatusBar() = default;
public:
	wxStatusBar* GetEntity() {
		return reinterpret_cast<wxStatusBar*>(Value_wxTrackable::GetEntity());
	}
	const wxStatusBar* GetEntity() const {
		return reinterpret_cast<const wxStatusBar*>(Value_wxTrackable::GetEntity());
	}
public:
	static wxStatusBar* GetEntity(Value& value) {
		return dynamic_cast<Value_wxStatusBar&>(value).GetEntity();
	}
	static const wxStatusBar* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxStatusBar&>(value).GetEntity();
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
