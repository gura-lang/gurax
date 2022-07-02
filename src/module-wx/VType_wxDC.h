//==============================================================================
// VType_wxDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDC_H
#define GURAX_MODULE_WX_VTYPE_WXDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dc.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDC VTYPE_wxDC;

//------------------------------------------------------------------------------
// Value_wxDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDC : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDC");
protected:
	std::unique_ptr<wxDC> _pEntityHolder;	// this may be nullptr
	wxDC& _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDC() = delete;
	explicit Value_wxDC(wxDC* pEntity, VType& vtype = VTYPE_wxDC) :
		Value_Object(vtype), _pEntityHolder(pEntity), _entity(*pEntity) {}
	explicit Value_wxDC(wxDC& entity, VType& vtype = VTYPE_wxDC) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxDC(const Value_wxDC& src) = delete;
	Value_wxDC& operator=(const Value_wxDC& src) = delete;
	// Move constructor/operator
	Value_wxDC(Value_wxDC&& src) noexcept = delete;
	Value_wxDC& operator=(Value_wxDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDC() = default;
public:
	wxDC& GetEntity() { return _entity; }
	const wxDC& GetEntity() const { return _entity; }
	wxDC* GetEntityPtr() { return &_entity; }
	const wxDC* GetEntityPtr() const { return &_entity; }
public:
	static wxDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDC&>(value).GetEntity();
	}
	static const wxDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDC&>(value).GetEntity();
	}
	static wxDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDC&>(value).GetEntityPtr();
	}
	static const wxDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDC&>(value).GetEntityPtr();
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
