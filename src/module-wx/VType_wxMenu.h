//==============================================================================
// VType_wxMenu.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMENU_H
#define GURAX_MODULE_WX_VTYPE_WXMENU_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMenu
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMenu : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMenu VTYPE_wxMenu;

//------------------------------------------------------------------------------
// Value_wxMenu
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMenu : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMenu);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMenu");
protected:
	wxWeakRef<wxMenu> _pEntity;
public:
	class EntityT : public wxMenu {
	public:
		using wxMenu::wxMenu;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMenu() = delete;
	explicit Value_wxMenu(wxMenu* pEntity, VType& vtype = VTYPE_wxMenu) :
		Value_wxEvtHandler(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxMenu(const Value_wxMenu& src) = delete;
	Value_wxMenu& operator=(const Value_wxMenu& src) = delete;
	// Move constructor/operator
	Value_wxMenu(Value_wxMenu&& src) noexcept = delete;
	Value_wxMenu& operator=(Value_wxMenu&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMenu() = default;
public:
	wxMenu& GetEntity() { return *_pEntity; }
	const wxMenu& GetEntity() const { return *_pEntity; }
	wxMenu* GetEntityPtr() { return _pEntity.get(); }
	const wxMenu* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxMenu& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMenu&>(value).GetEntity();
	}
	static const wxMenu& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMenu&>(value).GetEntity();
	}
	static wxMenu* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMenu&>(value).GetEntityPtr();
	}
	static const wxMenu* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMenu&>(value).GetEntityPtr();
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
