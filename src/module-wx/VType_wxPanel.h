//==============================================================================
// VType_wxPanel.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPANEL_H
#define GURAX_MODULE_WX_VTYPE_WXPANEL_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPanel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPanel : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPanel VTYPE_wxPanel;

//------------------------------------------------------------------------------
// Value_wxPanel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPanel : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPanel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPanel");
public:
	class EntityT : public wxPanel {
	public:
		using wxPanel::wxPanel;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPanel() = delete;
	explicit Value_wxPanel(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxPanel) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxPanel(const Value_wxPanel& src) = delete;
	Value_wxPanel& operator=(const Value_wxPanel& src) = delete;
	// Move constructor/operator
	Value_wxPanel(Value_wxPanel&& src) noexcept = delete;
	Value_wxPanel& operator=(Value_wxPanel&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPanel() = default;
public:
	wxPanel* GetEntity() {
		return reinterpret_cast<wxPanel*>(Value_wxEvtHandler::GetEntity());
	}
	const wxPanel* GetEntity() const {
		return reinterpret_cast<const wxPanel*>(Value_wxEvtHandler::GetEntity());
	}
public:
	static wxPanel* GetEntity(Value& value) {
		return dynamic_cast<Value_wxPanel&>(value).GetEntity();
	}
	static const wxPanel* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPanel&>(value).GetEntity();
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
