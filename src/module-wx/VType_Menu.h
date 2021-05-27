//==============================================================================
// VType_Menu.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_MENU_H
#define GURAX_MODULE_WX_VTYPE_MENU_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Menu
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Menu : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Menu VTYPE_Menu;

//------------------------------------------------------------------------------
// Value_Menu
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Menu : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Menu);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Menu");
public:
	class EntityT : public wxMenu {
	public:
		using EntitySuper = wxMenu;
		using wxMenu::wxMenu;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_Menu() = delete;
	explicit Value_Menu(wxMenu* pEntity, VType& vtype = VTYPE_Menu) :
		Value_wxEvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Menu(const Value_Menu& src) = delete;
	Value_Menu& operator=(const Value_Menu& src) = delete;
	// Move constructor/operator
	Value_Menu(Value_Menu&& src) noexcept = delete;
	Value_Menu& operator=(Value_Menu&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Menu() = default;
public:
	wxMenu* GetEntity() { return wxDynamicCast(Value_wxEvtHandler::GetEntity(), wxMenu); }
	const wxMenu* GetEntity() const { return wxDynamicCast(Value_wxEvtHandler::GetEntity(), wxMenu); }
public:
	static wxMenu* GetEntity(Value& value) {
		return dynamic_cast<Value_Menu&>(value).GetEntity();
	}
	static const wxMenu* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Menu&>(value).GetEntity();
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
