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
#if 0
public:
	size_t GetSizeT() const		{ return static_cast<size_t>(_num); }
	Char GetChar() const		{ return static_cast<Char>(_num); }
	UChar GetUChar() const		{ return static_cast<UChar>(_num); }
	Short GetShort() const		{ return static_cast<Short>(_num); }
	UShort GetUShort() const	{ return static_cast<UShort>(_num); }
	Int GetInt() const			{ return static_cast<Int>(_num); }
	UInt GetUInt() const		{ return static_cast<UInt>(_num); }
	Long GetLong() const		{ return static_cast<Long>(_num); }
	ULong GetULong() const		{ return static_cast<ULong>(_num); }
	Int8 GetInt8() const		{ return static_cast<Int8>(_num); }
	UInt8 GetUInt8() const		{ return static_cast<UInt8>(_num); }
	Int16 GetInt16() const		{ return static_cast<Int16>(_num); }
	UInt16 GetUInt16() const	{ return static_cast<UInt16>(_num); }
	Int32 GetInt32() const		{ return static_cast<Int32>(_num); }
	UInt32 GetUInt32() const	{ return static_cast<UInt32>(_num); }
	Int64 GetInt64() const		{ return static_cast<Int64>(_num); }
	UInt64 GetUInt64() const	{ return static_cast<UInt64>(_num); }
	Float GetFloat() const		{ return static_cast<Float>(_num); }
	Double GetDouble() const	{ return _num; }
#endif
public:
	template<typename T_Num> T_Num GetNumber() const { return static_cast<T_Num>(_num); }
	template<typename T_Num> T_Num GetRanged(T_Num numMin, T_Num numMax) const;
	template<typename T_Num> T_Num GetNonNeg() const;
#if 0
public:
	static size_t GetSizeT(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetSizeT(); }
	static Char GetChar(const Value& value)		{ return dynamic_cast<const Value_Number&>(value).GetChar(); }
	static UChar GetUChar(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetUChar(); }
	static Short GetShort(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetShort(); }
	static UShort GetUShort(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetUShort(); }
	static Int GetInt(const Value& value)		{ return dynamic_cast<const Value_Number&>(value).GetInt(); }
	static UInt GetUInt(const Value& value)		{ return dynamic_cast<const Value_Number&>(value).GetUInt(); }
	static Long GetLong(const Value& value)		{ return dynamic_cast<const Value_Number&>(value).GetLong(); }
	static ULong GetULong(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetULong(); }
	static Int8 GetInt8(const Value& value)		{ return dynamic_cast<const Value_Number&>(value).GetInt8(); }
	static UInt8 GetUInt8(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetUInt8(); }
	static Int16 GetInt16(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetInt16(); }
	static UInt16 GetUInt16(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetUInt16(); }
	static Int32 GetInt32(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetInt32(); }
	static UInt32 GetUInt32(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetUInt32(); }
	static Int64 GetInt64(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetInt64(); }
	static UInt64 GetUInt64(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetUInt64(); }
	static Float GetFloat(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetFloat(); }
	static Double GetDouble(const Value& value)	{ return dynamic_cast<const Value_Number&>(value).GetDouble(); }
#endif
public:
	template<typename T_Num> static T_Num GetNumber(const Value& value) {
		return dynamic_cast<const Value_Number&>(value).GetNumber<T_Num>();
	}
	template<typename T_Num> static T_Num GetRanged(const Value& value, T_Num numMin, T_Num numMax) {
		return dynamic_cast<const Value_Number&>(value).GetRanged<T_Num>(numMin, numMax);
	}
	template<typename T_Num> static T_Num GetNonNeg(const Value& value) {
		return dynamic_cast<const Value_Number&>(value).GetNonNeg<T_Num>();
	}
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

template<typename T_Num> T_Num Value_Number::GetRanged(T_Num numMin, T_Num numMax) const
{
	if ((_num < static_cast<Double>(numMin) || static_cast<Double>(numMax) < _num) && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "the number must be between %g and %g",
					 static_cast<Double>(numMin), static_cast<Double>(numMax));
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num> T_Num Value_Number::GetNonNeg() const
{
	if (_num < 0 && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "negative value is not acceptable");
	}
	return static_cast<T_Num>(_num);
}

}

#endif
