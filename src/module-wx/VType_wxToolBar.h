//==============================================================================
// VType_wxToolBar.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTOOLBAR_H
#define GURAX_MODULE_WX_VTYPE_WXTOOLBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxToolBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxToolBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxToolBar VTYPE_wxToolBar;

//------------------------------------------------------------------------------
// Value_wxToolBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxToolBar : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxToolBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxToolBar");
protected:
	wxWeakRef<wxToolBar> _pEntity;
public:
	class EntityT : public wxToolBar {
	public:
		using wxToolBar::wxToolBar;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxToolBar() = delete;
	explicit Value_wxToolBar(wxToolBar* pEntity, VType& vtype = VTYPE_wxToolBar) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxToolBar(const Value_wxToolBar& src) = delete;
	Value_wxToolBar& operator=(const Value_wxToolBar& src) = delete;
	// Move constructor/operator
	Value_wxToolBar(Value_wxToolBar&& src) noexcept = delete;
	Value_wxToolBar& operator=(Value_wxToolBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxToolBar() = default;
public:
	wxToolBar& GetEntity() { return *_pEntity; }
	const wxToolBar& GetEntity() const { return *_pEntity; }
	wxToolBar* GetEntityPtr() { return _pEntity.get(); }
	const wxToolBar* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxToolBar& GetEntity(Value& value) {
		return dynamic_cast<Value_wxToolBar&>(value).GetEntity();
	}
	static const wxToolBar& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxToolBar&>(value).GetEntity();
	}
	static wxToolBar* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxToolBar&>(value).GetEntityPtr();
	}
	static const wxToolBar* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxToolBar&>(value).GetEntityPtr();
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
