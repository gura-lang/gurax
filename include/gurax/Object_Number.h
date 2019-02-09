//==============================================================================
// Object_Number.h
//==============================================================================
#ifndef GURAX_OBJECT_NUMBER_H
#define GURAX_OBJECT_NUMBER_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Number
//------------------------------------------------------------------------------
class VTypeT_Number : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Number VType_Number;

//------------------------------------------------------------------------------
// Object_Number
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Number : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Number);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Number");
private:
	Double _num;
public:
	// Constructor
	explicit Object_Number(VType& vtype = VType_Number) :
		Object_Number(0., vtype) {}
	explicit Object_Number(Double num, VType& vtype = VType_Number) :
		Object_Object(vtype), _num(num) {}
	// Copy constructor/operator
	Object_Number(const Object_Number& src) :
		Object_Object(src), _num(src._num) {}
	Object_Number& operator=(const Object_Number& src) = delete;
	// Move constructor/operator
	Object_Number(Object_Number&& src) = delete;
	Object_Number& operator=(Object_Number&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Number() = default;
public:
	size_t GetSizeT() const		{ return static_cast<size_t>(_num); }
	Bool GetBool() const		{ return static_cast<Bool>(_num); }
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
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return GetSizeT(); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) && GetDouble() == dynamic_cast<const Object_Number*>(pObject)->GetDouble();
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetDouble() < dynamic_cast<const Object_Number*>(pObject)->GetDouble() :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
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
