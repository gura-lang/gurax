//==============================================================================
// VType_wxTreebook.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTREEBOOK_H
#define GURAX_MODULE_WX_VTYPE_WXTREEBOOK_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/treebook.h>
#include "Util.h"
#include "VType_wxBookCtrlBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxTreebook
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxTreebook : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxTreebook VTYPE_wxTreebook;

//------------------------------------------------------------------------------
// Value_wxTreebook
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxTreebook : public Value_wxBookCtrlBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxTreebook);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxTreebook");
protected:
	wxWeakRef<wxTreebook> _pEntity;
public:
	class EntityT : public wxTreebook {
	public:
		using wxTreebook::wxTreebook;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxTreebook() = delete;
	explicit Value_wxTreebook(wxTreebook* pEntity, VType& vtype = VTYPE_wxTreebook) :
		Value_wxBookCtrlBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxTreebook(const Value_wxTreebook& src) = delete;
	Value_wxTreebook& operator=(const Value_wxTreebook& src) = delete;
	// Move constructor/operator
	Value_wxTreebook(Value_wxTreebook&& src) noexcept = delete;
	Value_wxTreebook& operator=(Value_wxTreebook&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxTreebook() = default;
public:
	wxTreebook& GetEntity() { return *_pEntity; }
	const wxTreebook& GetEntity() const { return *_pEntity; }
	wxTreebook* GetEntityPtr() { return _pEntity.get(); }
	const wxTreebook* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxTreebook& GetEntity(Value& value) {
		return dynamic_cast<Value_wxTreebook&>(value).GetEntity();
	}
	static const wxTreebook& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxTreebook&>(value).GetEntity();
	}
	static wxTreebook* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxTreebook&>(value).GetEntityPtr();
	}
	static const wxTreebook* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxTreebook&>(value).GetEntityPtr();
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
