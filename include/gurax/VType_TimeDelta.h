//==============================================================================
// VType_TimeDelta.h
//==============================================================================
#ifndef GURAX_VTYPE_TIMEDELTA_H
#define GURAX_VTYPE_TIMEDELTA_H
#include "VType_Object.h"
#include "TimeDelta.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_TimeDelta
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_TimeDelta : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_TimeDelta VTYPE_TimeDelta;

//------------------------------------------------------------------------------
// Value_TimeDelta
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_TimeDelta : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_TimeDelta);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_TimeDelta");
protected:
	RefPtr<TimeDelta> _pTimeDelta;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_TimeDelta(VType& vtype = VTYPE_TimeDelta) :
		Value_TimeDelta(new TimeDelta(), vtype) {}
	explicit Value_TimeDelta(TimeDelta *pTimeDelta, VType& vtype = VTYPE_TimeDelta) :
		Value_Object(vtype), _pTimeDelta(pTimeDelta) {}
	// Copy constructor/operator
	Value_TimeDelta(const Value_TimeDelta& src) :
		Value_Object(src), _pTimeDelta(src._pTimeDelta->Reference()) {}
	Value_TimeDelta& operator=(const Value_TimeDelta& src) = delete;
	// Move constructor/operator
	Value_TimeDelta(Value_TimeDelta&& src) = delete;
	Value_TimeDelta& operator=(Value_TimeDelta&& src) noexcept = delete;
protected:
	// Destructor
	~Value_TimeDelta() = default;
public:
	TimeDelta& GetTimeDelta() { return *_pTimeDelta; }
	const TimeDelta& GetTimeDelta() const { return *_pTimeDelta; }
public:
	static TimeDelta& GetTimeDelta(Value& value) {
		return dynamic_cast<Value_TimeDelta&>(value).GetTimeDelta();
	}
	static const TimeDelta& GetTimeDelta(const Value &value) {
		return dynamic_cast<const Value_TimeDelta&>(value).GetTimeDelta();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTimeDelta().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return GetTimeDelta().IsEqualTo(dynamic_cast<const Value_TimeDelta&>(value).GetTimeDelta());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTimeDelta().IsLessThan(dynamic_cast<const Value_TimeDelta&>(value).GetTimeDelta()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
