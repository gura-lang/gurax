//==============================================================================
// VType_Event.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_EVENT_H
#define GURAX_MODULE_WX_VTYPE_EVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Event
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Event : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Event VTYPE_Event;

//------------------------------------------------------------------------------
// Value_Event
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Event : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Event);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Event");
public:
	using EntityT = wxEvent;
protected:
	std::unique_ptr<EntityT> _pEntity;
	RefPtr<Value> _pValueUserData;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Event() = delete;
	explicit Value_Event(EntityT* pEntity, Value* pValueUserData, VType& vtype = VTYPE_Event) :
		Value_Object(vtype), _pEntity(pEntity), _pValueUserData(pValueUserData) {}
	// Copy constructor/operator
	Value_Event(const Value_Event& src) = delete;
	Value_Event& operator=(const Value_Event& src) = delete;
	// Move constructor/operator
	Value_Event(Value_Event&& src) noexcept = delete;
	Value_Event& operator=(Value_Event&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Event() = default;
public:
	EntityT& GetEntity() { return *_pEntity; }
	const EntityT& GetEntity() const { return *_pEntity; }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_Event&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Event&>(value).GetEntity();
	}
public:
	Value& GetValueUserData() { return *_pValueUserData; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(&GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && &GetEntity(*this) == &GetEntity(value);
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
