//==============================================================================
// VType_Random.h
//==============================================================================
#ifndef GURAX_VTYPE_RANDOM_H
#define GURAX_VTYPE_RANDOM_H
#include "VType_Object.h"
#include "Random.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
class VType_Random : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Random VTYPE_Random;

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Random : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Random);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Random");
protected:
	RefPtr<Random> _pRandom;
public:
	// Constructor
	Value_Random() = delete;
	explicit Value_Random(Random* pRandom, VType& vtype = VTYPE_Random) :
		Value_Object(vtype), _pRandom(pRandom) {}
	// Copy constructor/operator
	Value_Random(const Value_Random& src) :
		Value_Object(src), _pRandom(src._pRandom->Reference()) {}
	Value_Random& operator=(const Value_Random& src) = delete;
	// Move constructor/operator
	Value_Random(Value_Random&& src) = delete;
	Value_Random& operator=(Value_Random&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Random() = default;
public:
	Random& GetRandom() { return *_pRandom; }
	const Random& GetRandom() const { return *_pRandom; }
public:
	static Random& GetRandom(Value& value) {
		return dynamic_cast<Value_Random&>(value).GetRandom();
	}
	static const Random& GetRandom(const Value& value) {
		return dynamic_cast<const Value_Random&>(value).GetRandom();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetRandom().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetRandom().IsEqualTo(dynamic_cast<const Value_Random*>(pValue)->GetRandom());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetRandom().IsLessThan(dynamic_cast<const Value_Random*>(pValue)->GetRandom()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
