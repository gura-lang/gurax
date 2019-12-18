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
class GURAX_DLLDECLARE VType_Number : public VType {
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
	static VType& vtype;
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
	template<typename T_Num> T_Num GetNumberPos() const;
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
	template<typename T_Num> static T_Num GetNumberPos(const Value& value) {
		return dynamic_cast<const Value_Number&>(value).GetNumberPos<T_Num>();
	}
public:
	template<typename T_Num>
	static NumList<T_Num> GetNumList(const ValueList& values);
	template<typename T_Num>
	static NumList<T_Num> GetNumListRanged(const ValueList& values, T_Num numMin, T_Num numMax);
	template<typename T_Num>
	static NumList<T_Num> GetNumListNonNeg(const ValueList& values);
	template<typename T_Num>
	static NumList<T_Num> GetNumListPos(const ValueList& values);
public:
	// Virtual functions of Value
	virtual bool IsZero() const override { return _num == 0.; }
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

}

#endif
