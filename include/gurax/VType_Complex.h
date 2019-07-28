//==============================================================================
// VType_Complex.h
//==============================================================================
#ifndef GURAX_VTYPE_COMPLEX_H
#define GURAX_VTYPE_COMPLEX_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Complex
//------------------------------------------------------------------------------
class VType_Complex : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Complex VTYPE_Complex;

//------------------------------------------------------------------------------
// Value_Complex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Complex : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Complex);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Complex");
protected:
	Complex _num;
public:
	// Constructor
	explicit Value_Complex(VType& vtype = VTYPE_Complex) :
		Value_Complex(0., vtype) {}
	explicit Value_Complex(const Complex& num, VType& vtype = VTYPE_Complex) :
		Value_Object(vtype), _num(num) {}
	// Copy constructor/operator
	Value_Complex(const Value_Complex& src) :
		Value_Object(src), _num(src._num) {}
	Value_Complex& operator=(const Value_Complex& src) = delete;
	// Move constructor/operator
	Value_Complex(Value_Complex&& src) = delete;
	Value_Complex& operator=(Value_Complex&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Complex() = default;
public:
	Double GetComplexRaw() const { return _num; }
	template<typename T_Num> T_Num GetComplex() const { return static_cast<T_Num>(_num); }
	template<typename T_Num> T_Num GetComplexRanged(T_Num numMin, T_Num numMax) const;
	template<typename T_Num> T_Num GetComplexNonNeg() const;
public:
	static Double GetComplexRaw(const Value& value) {
		return dynamic_cast<const Value_Complex&>(value).GetComplexRaw();
	}
	template<typename T_Num> static T_Num GetComplex(const Value& value) {
		return dynamic_cast<const Value_Complex&>(value).GetComplex<T_Num>();
	}
	template<typename T_Num> static T_Num GetComplexRanged(const Value& value, T_Num numMin, T_Num numMax) {
		return dynamic_cast<const Value_Complex&>(value).GetComplexRanged<T_Num>(numMin, numMax);
	}
	template<typename T_Num> static T_Num GetComplexNonNeg(const Value& value) {
		return dynamic_cast<const Value_Complex&>(value).GetComplexNonNeg<T_Num>();
	}
public:
	template<typename T_Num>
	static NumList<T_Num> GetNumList(const ValueList& values);
	template<typename T_Num>
	static NumList<T_Num> GetNumListRanged(const ValueList& values, T_Num numMin, T_Num numMax);
	template<typename T_Num>
	static NumList<T_Num> GetNumListNonNeg(const ValueList& values);
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return GetComplex<size_t>(); }
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) && GetComplex<Double>() == Value_Complex::GetComplex<Double>(*pValue);
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetComplex<Double>() < Value_Complex::GetComplex<Double>(*pValue) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
	virtual bool IsAsDictKey() const override { return true; }
	virtual bool Format_d(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_u(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_b(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_o(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_x(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_e(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_f(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_g(Formatter& formatter, FormatterFlags& flags) const override;
	virtual bool Format_c(Formatter& formatter, FormatterFlags& flags) const override;
};

template<typename T_Num>
T_Num Value_Complex::GetComplexRanged(T_Num numMin, T_Num numMax) const
{
	if ((_num < static_cast<Double>(numMin) || static_cast<Double>(numMax) < _num) && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "the number must be between %g and %g",
					 static_cast<Double>(numMin), static_cast<Double>(numMax));
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
T_Num Value_Complex::GetComplexNonNeg() const
{
	if (_num < 0 && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "negative value is not acceptable");
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
NumList<T_Num> Value_Complex::GetNumList(const ValueList& values)
{
	NumList<T_Num> nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = GetComplexRaw(*pValue);
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Complex::GetNumListRanged(const ValueList& values, T_Num numMin, T_Num numMax)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	Double numMinDbl = static_cast<Double>(numMin);
	Double numMaxDbl = static_cast<Double>(numMax);
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Complex::GetComplexRaw(*pValue);
		if ((numRaw < numMinDbl || numMaxDbl < numRaw)) {
			Error::Issue(ErrorType::RangeError, "the number must be between %g and %g", numMinDbl, numMaxDbl);
			break;
		}
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Complex::GetNumListNonNeg(const ValueList& values)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Complex::GetComplexRaw(*pValue);
		if (numRaw < 0) {
			Error::Issue(ErrorType::RangeError, "negative value is not acceptable");
			break;
		}
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

}

#endif
