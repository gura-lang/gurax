//==============================================================================
// VType_Number.h
//==============================================================================
#ifndef GURAX_VTYPE_NUMBER_H
#define GURAX_VTYPE_NUMBER_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Number
//------------------------------------------------------------------------------
class VType_Number : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Number VTYPE_Number;

//------------------------------------------------------------------------------
// Value_Number
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Number : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Number);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Number");
protected:
	Double _num;
public:
	// Constructor
	explicit Value_Number(VType& vtype = VTYPE_Number) :
		Value_Number(0., vtype) {}
	explicit Value_Number(Double num, VType& vtype = VTYPE_Number) :
		Value_Object(vtype), _num(num) {}
	// Copy constructor/operator
	Value_Number(const Value_Number& src) :
		Value_Object(src), _num(src._num) {}
	Value_Number& operator=(const Value_Number& src) = delete;
	// Move constructor/operator
	Value_Number(Value_Number&& src) = delete;
	Value_Number& operator=(Value_Number&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Number() = default;
public:
	Double GetNumberRaw() const { return _num; }
	template<typename T_Num> T_Num GetNumber() const { return static_cast<T_Num>(_num); }
	template<typename T_Num> T_Num GetNumberRanged(T_Num numMin, T_Num numMax) const;
	template<typename T_Num> T_Num GetNumberNonNeg() const;
public:
	static Double GetNumberRaw(const Value& value) {
		return dynamic_cast<const Value_Number&>(value).GetNumberRaw();
	}
	template<typename T_Num> static T_Num GetNumber(const Value& value) {
		return dynamic_cast<const Value_Number&>(value).GetNumber<T_Num>();
	}
	template<typename T_Num> static T_Num GetNumberRanged(const Value& value, T_Num numMin, T_Num numMax) {
		return dynamic_cast<const Value_Number&>(value).GetNumberRanged<T_Num>(numMin, numMax);
	}
	template<typename T_Num> static T_Num GetNumberNonNeg(const Value& value) {
		return dynamic_cast<const Value_Number&>(value).GetNumberNonNeg<T_Num>();
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
	virtual size_t DoCalcHash() const override { return GetNumber<size_t>(); }
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) && GetNumber<Double>() == Value_Number::GetNumber<Double>(*pValue);
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetNumber<Double>() < Value_Number::GetNumber<Double>(*pValue) :
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
T_Num Value_Number::GetNumberRanged(T_Num numMin, T_Num numMax) const
{
	if ((_num < static_cast<Double>(numMin) || static_cast<Double>(numMax) < _num) && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "the number must be between %g and %g",
					 static_cast<Double>(numMin), static_cast<Double>(numMax));
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
T_Num Value_Number::GetNumberNonNeg() const
{
	if (_num < 0 && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "negative value is not acceptable");
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumList(const ValueList& values)
{
	NumList<T_Num> nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Number::GetNumberRaw(*pValue);
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumListRanged(const ValueList& values, T_Num numMin, T_Num numMax)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	Double numMinDbl = static_cast<Double>(numMin);
	Double numMaxDbl = static_cast<Double>(numMax);
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Number::GetNumberRaw(*pValue);
		if ((numRaw < numMinDbl || numMaxDbl < numRaw)) {
			Error::Issue(ErrorType::RangeError, "the number must be between %g and %g", numMinDbl, numMaxDbl);
			break;
		}
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumListNonNeg(const ValueList& values)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Number::GetNumberRaw(*pValue);
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
