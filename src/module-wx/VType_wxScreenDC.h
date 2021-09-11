//==============================================================================
// VType_wxScreenDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSCREENDC_H
#define GURAX_MODULE_WX_VTYPE_WXSCREENDC_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxScreenDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxScreenDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxScreenDC VTYPE_wxScreenDC;

//------------------------------------------------------------------------------
// Value_wxScreenDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxScreenDC : public Value_wxDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxScreenDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxScreenDC");
protected:
	wxScreenDC& _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxScreenDC() = delete;
	explicit Value_wxScreenDC(const wxScreenDC& entity, VType& vtype = VTYPE_wxScreenDC) :
		Value_wxDC(entity, vtype), _entity(const_cast<wxScreenDC&>(entity)) {}
	// Copy constructor/operator
	Value_wxScreenDC(const Value_wxScreenDC& src) = delete;
	Value_wxScreenDC& operator=(const Value_wxScreenDC& src) = delete;
	// Move constructor/operator
	Value_wxScreenDC(Value_wxScreenDC&& src) noexcept = delete;
	Value_wxScreenDC& operator=(Value_wxScreenDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxScreenDC() = default;
public:
	wxScreenDC& GetEntity() { return _entity; }
	const wxScreenDC& GetEntity() const { return _entity; }
	wxScreenDC* GetEntityPtr() { return &_entity; }
	const wxScreenDC* GetEntityPtr() const { return &_entity; }
public:
	static wxScreenDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxScreenDC&>(value).GetEntity();
	}
	static const wxScreenDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxScreenDC&>(value).GetEntity();
	}
	static wxScreenDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxScreenDC&>(value).GetEntityPtr();
	}
	static const wxScreenDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxScreenDC&>(value).GetEntityPtr();
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
