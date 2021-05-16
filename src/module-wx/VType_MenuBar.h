//==============================================================================
// VType_MenuBar.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_MENUBAR_H
#define GURAX_MODULE_WX_VTYPE_MENUBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_Window.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_MenuBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MenuBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_MenuBar VTYPE_MenuBar;

//------------------------------------------------------------------------------
// Value_MenuBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MenuBar : public Value_Window {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MenuBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MenuBar");
public:
	class EntityT : public wxMenuBar {
	public:
		using EntitySuper = wxMenuBar;
		using wxMenuBar::wxMenuBar;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_MenuBar() = delete;
	explicit Value_MenuBar(wxMenuBar* pEntity, VType& vtype = VTYPE_MenuBar) :
		Value_Window(pEntity, vtype) {}
	// Copy constructor/operator
	Value_MenuBar(const Value_MenuBar& src) = delete;
	Value_MenuBar& operator=(const Value_MenuBar& src) = delete;
	// Move constructor/operator
	Value_MenuBar(Value_MenuBar&& src) noexcept = delete;
	Value_MenuBar& operator=(Value_MenuBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MenuBar() = default;
public:
	wxMenuBar* GetEntity() { return wxDynamicCast(Value_Window::GetEntity(), wxMenuBar); }
	const wxMenuBar* GetEntity() const { return wxDynamicCast(Value_Window::GetEntity(), wxMenuBar); }
public:
	static wxMenuBar* GetEntity(Value& value) {
		return dynamic_cast<Value_MenuBar&>(value).GetEntity();
	}
	static const wxMenuBar* GetEntity(const Value& value) {
		return dynamic_cast<const Value_MenuBar&>(value).GetEntity();
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
