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
	virtual void DoPrepare(Frame& frame) override;
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
private:
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
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return GetSizeT(); }
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) && GetDouble() == dynamic_cast<const Value_Number*>(pValue)->GetDouble();
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetDouble() < dynamic_cast<const Value_Number*>(pValue)->GetDouble() :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return std::to_string(_num);
	}
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
