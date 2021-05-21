//==============================================================================
// VType_EventType.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_EVENTTYPE_H
#define GURAX_MODULE_WX_VTYPE_EVENTTYPE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_EventType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_EventType : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_EventType VTYPE_EventType;

//------------------------------------------------------------------------------
// Value_EventType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_EventType : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_EventType);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_EventType");
public:
	using EntityT = wxEventType;
protected:
	EntityT _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_EventType() = delete;
	explicit Value_EventType(const EntityT& entity, VType& vtype = VTYPE_EventType) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_EventType(const Value_EventType& src) = delete;
	Value_EventType& operator=(const Value_EventType& src) = delete;
	// Move constructor/operator
	Value_EventType(Value_EventType&& src) noexcept = delete;
	Value_EventType& operator=(Value_EventType&& src) noexcept = delete;
protected:
	// Destructor
	~Value_EventType() = default;
public:
	EntityT& GetEntity() { return _entity; }
	const EntityT& GetEntity() const { return _entity; }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_EventType&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_EventType&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(&GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(&GetEntity(*this) < &GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
