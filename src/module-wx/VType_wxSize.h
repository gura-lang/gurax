//==============================================================================
// VType_wxSize.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSIZE_H
#define GURAX_MODULE_WX_VTYPE_WXSIZE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSize
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSize : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSize VTYPE_wxSize;

//------------------------------------------------------------------------------
// Value_wxSize
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSize : public Gurax::Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSize);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSize");
public:
	using EntityT = wxSize;
protected:
	EntityT _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSize() = delete;
	explicit Value_wxSize(const EntityT& entity, VType& vtype = VTYPE_wxSize) :
		Gurax::Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxSize(const Value_wxSize& src) = delete;
	Value_wxSize& operator=(const Value_wxSize& src) = delete;
	// Move constructor/operator
	Value_wxSize(Value_wxSize&& src) noexcept = delete;
	Value_wxSize& operator=(Value_wxSize&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSize() = default;
public:
	EntityT& GetEntity() { return _entity; }
	const EntityT& GetEntity() const { return _entity; }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSize&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSize&>(value).GetEntity();
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
