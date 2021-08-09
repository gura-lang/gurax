//==============================================================================
// VType_wxAcceleratorTable.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXACCELERATORTABLE_H
#define GURAX_MODULE_WX_VTYPE_WXACCELERATORTABLE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAcceleratorTable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAcceleratorTable : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAcceleratorTable VTYPE_wxAcceleratorTable;

//------------------------------------------------------------------------------
// Value_wxAcceleratorTable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAcceleratorTable : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAcceleratorTable);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAcceleratorTable");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAcceleratorTable() = delete;
	explicit Value_wxAcceleratorTable(const wxObject& entity, VType& vtype = VTYPE_wxAcceleratorTable) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxAcceleratorTable(const Value_wxAcceleratorTable& src) = delete;
	Value_wxAcceleratorTable& operator=(const Value_wxAcceleratorTable& src) = delete;
	// Move constructor/operator
	Value_wxAcceleratorTable(Value_wxAcceleratorTable&& src) noexcept = delete;
	Value_wxAcceleratorTable& operator=(Value_wxAcceleratorTable&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAcceleratorTable() = default;
public:
	wxAcceleratorTable& GetEntity() {
		return reinterpret_cast<wxAcceleratorTable&>(Value_wxObject::GetEntity());
	}
	const wxAcceleratorTable& GetEntity() const {
		return reinterpret_cast<const wxAcceleratorTable&>(Value_wxObject::GetEntity());
	}
	wxAcceleratorTable* GetEntityPtr() {
		return reinterpret_cast<wxAcceleratorTable*>(Value_wxObject::GetEntityPtr());
	}
	const wxAcceleratorTable* GetEntityPtr() const {
		return reinterpret_cast<const wxAcceleratorTable*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxAcceleratorTable& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAcceleratorTable&>(value).GetEntity();
	}
	static const wxAcceleratorTable& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAcceleratorTable&>(value).GetEntity();
	}
	static wxAcceleratorTable* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAcceleratorTable&>(value).GetEntityPtr();
	}
	static const wxAcceleratorTable* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAcceleratorTable&>(value).GetEntityPtr();
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