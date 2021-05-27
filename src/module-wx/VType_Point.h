//==============================================================================
// VType_Point.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_POINT_H
#define GURAX_MODULE_WX_VTYPE_POINT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Point : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Point VTYPE_Point;

//------------------------------------------------------------------------------
// Value_Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Point : public Gurax::Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Point);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Point");
public:
	using EntityT = wxPoint;
protected:
	EntityT _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Point() = delete;
	explicit Value_Point(const EntityT& entity, VType& vtype = VTYPE_Point) :
		Gurax::Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Point(const Value_Point& src) = delete;
	Value_Point& operator=(const Value_Point& src) = delete;
	// Move constructor/operator
	Value_Point(Value_Point&& src) noexcept = delete;
	Value_Point& operator=(Value_Point&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Point() = default;
public:
	EntityT& GetEntity() { return _entity; }
	const EntityT& GetEntity() const { return _entity; }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_Point&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Point&>(value).GetEntity();
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
