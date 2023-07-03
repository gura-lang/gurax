//==============================================================================
// VType_Rational.h
//==============================================================================
#ifndef GURAX_VTYPE_RATIONAL_H
#define GURAX_VTYPE_RATIONAL_H
#include "VType_Object.h"
#include "Rational.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Rational
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Rational : public VType {
public:
	static const SerialId serialId = 0x0000001a;
public:
	VType_Rational() : VType(serialId) {}
	explicit VType_Rational(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Rational(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Rational VTYPE_Rational;

//------------------------------------------------------------------------------
// Value_Rational
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Rational : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Rational);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Rational");
protected:
	Rational _rational;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Rational() = delete;
	explicit Value_Rational(Rational rational, VType& vtype = VTYPE_Rational) :
		Value_Object(vtype), _rational(rational) {}
	// Copy constructor/operator
	Value_Rational(const Value_Rational& src) : Value_Object(src), _rational(src._rational) {}
	Value_Rational& operator=(const Value_Rational& src) = delete;
	// Move constructor/operator
	Value_Rational(Value_Rational&& src) = delete;
	Value_Rational& operator=(Value_Rational&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Rational() = default;
public:
	Rational& GetRational() { return _rational; }
	const Rational& GetRational() const { return _rational; }
public:
	static Rational& GetRational(Value& value) {
		return dynamic_cast<Value_Rational&>(value).GetRational();
	}
	static const Rational& GetRational(const Value& value) {
		return dynamic_cast<const Value_Rational&>(value).GetRational();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetRational().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetRational().IsEqualTo(Value_Rational::GetRational(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetRational().IsLessThan(Value_Rational::GetRational(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

}

#endif
