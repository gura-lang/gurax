//==============================================================================
// VType_ArgSlot.h
//==============================================================================
#ifndef GURAX_VTYPE_ARGSLOT_H
#define GURAX_VTYPE_ARGSLOT_H
#include "VType_Object.h"
#include "ArgSlot.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ArgSlot : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ArgSlot VTYPE_ArgSlot;

//------------------------------------------------------------------------------
// Value_ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ArgSlot : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ArgSlot);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ArgSlot");
protected:
	RefPtr<ArgSlot> _pArgSlot;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ArgSlot() = delete;
	Value_ArgSlot(ArgSlot* pArgSlot, VType& vtype = VTYPE_ArgSlot) :
		Value_Object(vtype), _pArgSlot(pArgSlot) {}
	// Copy constructor/operator
	Value_ArgSlot(const Value_ArgSlot& src) :
		Value_Object(src), _pArgSlot(src._pArgSlot->Reference()) {}
	Value_ArgSlot& operator=(const Value_ArgSlot& src) = delete;
	// Move constructor/operator
	Value_ArgSlot(Value_ArgSlot&& src) = delete;
	Value_ArgSlot& operator=(Value_ArgSlot&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ArgSlot() = default;
public:
	ArgSlot& GetArgSlot() { return *_pArgSlot; }
	const ArgSlot& GetArgSlot() const { return *_pArgSlot; }
public:
	static ArgSlot& GetArgSlot(Value& value) {
		return dynamic_cast<Value_ArgSlot&>(value).GetArgSlot();
	}
	static const ArgSlot& GetArgSlot(const Value& value) {
		return dynamic_cast<const Value_ArgSlot&>(value).GetArgSlot();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArgSlot().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetArgSlot().IsEqualTo(Value_ArgSlot::GetArgSlot(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetArgSlot().IsLessThan(Value_ArgSlot::GetArgSlot(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
