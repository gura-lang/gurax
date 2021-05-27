//==============================================================================
// VType_Panel.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_PANEL_H
#define GURAX_MODULE_WX_VTYPE_PANEL_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Panel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Panel : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Panel VTYPE_Panel;

//------------------------------------------------------------------------------
// Value_Panel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Panel : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Panel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Panel");
public:
	class EntityT : public wxPanel {
	public:
		using EntitySuper = wxPanel;
		using wxPanel::wxPanel;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_Panel() = delete;
	explicit Value_Panel(wxPanel* pEntity, VType& vtype = VTYPE_Panel) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Panel(const Value_Panel& src) = delete;
	Value_Panel& operator=(const Value_Panel& src) = delete;
	// Move constructor/operator
	Value_Panel(Value_Panel&& src) noexcept = delete;
	Value_Panel& operator=(Value_Panel&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Panel() = default;
public:
	wxPanel* GetEntity() { return wxDynamicCast(Value_wxWindow::GetEntity(), wxPanel); }
	const wxPanel* GetEntity() const { return wxDynamicCast(Value_wxWindow::GetEntity(), wxPanel); }
public:
	static wxPanel* GetEntity(Value& value) {
		return dynamic_cast<Value_Panel&>(value).GetEntity();
	}
	static const wxPanel* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Panel&>(value).GetEntity();
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
