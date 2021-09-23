//==============================================================================
// VType_wxGridCellAttr.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLATTR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLATTR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxClientDataContainer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellAttr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellAttr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellAttr VTYPE_wxGridCellAttr;

//------------------------------------------------------------------------------
// Value_wxGridCellAttr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellAttr : public Value_wxClientDataContainer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellAttr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellAttr");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellAttr() = delete;
	explicit Value_wxGridCellAttr(const wxGridCellAttr& entity, VType& vtype = VTYPE_wxGridCellAttr) :
		Value_wxClientDataContainer(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridCellAttr(const Value_wxGridCellAttr& src) = delete;
	Value_wxGridCellAttr& operator=(const Value_wxGridCellAttr& src) = delete;
	// Move constructor/operator
	Value_wxGridCellAttr(Value_wxGridCellAttr&& src) noexcept = delete;
	Value_wxGridCellAttr& operator=(Value_wxGridCellAttr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellAttr() = default;
public:
	wxGridCellAttr& GetEntity() { return reinterpret_cast<wxGridCellAttr&>(Value_wxClientDataContainer::GetEntity()); }
	const wxGridCellAttr& GetEntity() const { return reinterpret_cast<const wxGridCellAttr&>(Value_wxClientDataContainer::GetEntity()); }
	wxGridCellAttr* GetEntityPtr() { return reinterpret_cast<wxGridCellAttr*>(Value_wxClientDataContainer::GetEntityPtr()); }\
	const wxGridCellAttr* GetEntityPtr() const { return reinterpret_cast<const wxGridCellAttr*>(Value_wxClientDataContainer::GetEntityPtr()); }
public:
	static wxGridCellAttr& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellAttr&>(value).GetEntity();
	}
	static const wxGridCellAttr& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellAttr&>(value).GetEntity();
	}
	static wxGridCellAttr* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellAttr&>(value).GetEntityPtr();
	}
	static const wxGridCellAttr* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellAttr&>(value).GetEntityPtr();
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
