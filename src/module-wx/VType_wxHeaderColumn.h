//==============================================================================
// VType_wxHeaderColumn.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHEADERCOLUMN_H
#define GURAX_MODULE_WX_VTYPE_WXHEADERCOLUMN_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/headercol.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHeaderColumn
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHeaderColumn : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHeaderColumn VTYPE_wxHeaderColumn;

//------------------------------------------------------------------------------
// Value_wxHeaderColumn
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHeaderColumn : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHeaderColumn);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHeaderColumn");
protected:
	wxHeaderColumn* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHeaderColumn() = delete;
	explicit Value_wxHeaderColumn(wxHeaderColumn* pEntity, VType& vtype = VTYPE_wxHeaderColumn) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxHeaderColumn(const wxHeaderColumn& entity, VType& vtype = VTYPE_wxHeaderColumn) :
		Value_Object(vtype), _pEntity(const_cast<wxHeaderColumn*>(&entity)) {}
	// Copy constructor/operator
	Value_wxHeaderColumn(const Value_wxHeaderColumn& src) = delete;
	Value_wxHeaderColumn& operator=(const Value_wxHeaderColumn& src) = delete;
	// Move constructor/operator
	Value_wxHeaderColumn(Value_wxHeaderColumn&& src) noexcept = delete;
	Value_wxHeaderColumn& operator=(Value_wxHeaderColumn&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHeaderColumn() = default;
public:
	wxHeaderColumn& GetEntity() { return *_pEntity; }
	const wxHeaderColumn& GetEntity() const { return *_pEntity; }
	wxHeaderColumn* GetEntityPtr() { return _pEntity; }
	const wxHeaderColumn* GetEntityPtr() const { return _pEntity; }
public:
	static wxHeaderColumn& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHeaderColumn&>(value).GetEntity();
	}
	static const wxHeaderColumn& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHeaderColumn&>(value).GetEntity();
	}
	static wxHeaderColumn* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHeaderColumn&>(value).GetEntityPtr();
	}
	static const wxHeaderColumn* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHeaderColumn&>(value).GetEntityPtr();
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
