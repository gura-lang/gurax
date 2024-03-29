﻿//==============================================================================
// VType_wxSettableHeaderColumn.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSETTABLEHEADERCOLUMN_H
#define GURAX_MODULE_WX_VTYPE_WXSETTABLEHEADERCOLUMN_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/headercol.h>
#include "Util.h"
#include "VType_wxHeaderColumn.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSettableHeaderColumn
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSettableHeaderColumn : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSettableHeaderColumn VTYPE_wxSettableHeaderColumn;

//------------------------------------------------------------------------------
// Value_wxSettableHeaderColumn
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSettableHeaderColumn : public Value_wxHeaderColumn {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSettableHeaderColumn);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSettableHeaderColumn");
protected:
	wxSettableHeaderColumn* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSettableHeaderColumn() = delete;
	explicit Value_wxSettableHeaderColumn(wxSettableHeaderColumn* pEntity, VType& vtype = VTYPE_wxSettableHeaderColumn) :
		Value_wxHeaderColumn(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxSettableHeaderColumn(const Value_wxSettableHeaderColumn& src) = delete;
	Value_wxSettableHeaderColumn& operator=(const Value_wxSettableHeaderColumn& src) = delete;
	// Move constructor/operator
	Value_wxSettableHeaderColumn(Value_wxSettableHeaderColumn&& src) noexcept = delete;
	Value_wxSettableHeaderColumn& operator=(Value_wxSettableHeaderColumn&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSettableHeaderColumn() = default;
public:
	wxSettableHeaderColumn& GetEntity() { return *_pEntity; }
	const wxSettableHeaderColumn& GetEntity() const { return *_pEntity; }
	wxSettableHeaderColumn* GetEntityPtr() { return _pEntity; }
	const wxSettableHeaderColumn* GetEntityPtr() const { return _pEntity; }
public:
	static wxSettableHeaderColumn& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSettableHeaderColumn&>(value).GetEntity();
	}
	static const wxSettableHeaderColumn& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSettableHeaderColumn&>(value).GetEntity();
	}
	static wxSettableHeaderColumn* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSettableHeaderColumn&>(value).GetEntityPtr();
	}
	static const wxSettableHeaderColumn* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSettableHeaderColumn&>(value).GetEntityPtr();
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
