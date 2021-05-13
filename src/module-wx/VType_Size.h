//==============================================================================
// VType_Size.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_SIZE_H
#define GURAX_MODULE_WX_VTYPE_SIZE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Size
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Size : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Size VTYPE_Size;

//------------------------------------------------------------------------------
// Value_Size
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Size : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Size);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Size");
public:
	using EntityT = wxSize;
protected:
	EntityT _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Size() = delete;
	explicit Value_Size(const EntityT& entity, VType& vtype = VTYPE_Size) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Size(const Value_Size& src) = delete;
	Value_Size& operator=(const Value_Size& src) = delete;
	// Move constructor/operator
	Value_Size(Value_Size&& src) noexcept = delete;
	Value_Size& operator=(Value_Size&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Size() = default;
public:
	EntityT& GetEntity() { return _entity; }
	const EntityT& GetEntity() const { return _entity; }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_Size&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Size&>(value).GetEntity();
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
