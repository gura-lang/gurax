//==============================================================================
// VType_Complex.h
//==============================================================================
#ifndef GURAX_VTYPE_COMPLEX_H
#define GURAX_VTYPE_COMPLEX_H
#include "VType_Object.h"
#include "Complex.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Complex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Complex : public VType {
public:
	static const SerialId serialId = 0x00000013;
public:
	VType_Complex() : VType(serialId) {}
	explicit VType_Complex(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Complex(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Complex VTYPE_Complex;

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
	static VType& vtype;
public:
	// Constructor
	explicit Value_Complex(VType& vtype = VTYPE_Complex) :
		Value_Object(vtype), _num(0.) {}
	explicit Value_Complex(const Complex& num, VType& vtype = VTYPE_Complex) :
		Value_Object(vtype), _num(num) {}
	explicit Value_Complex(const std::complex<Double>& num, VType& vtype = VTYPE_Complex) :
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
	const Complex& GetComplex() const { return _num; }
public:
	static const Complex& GetComplex(const Value& value) {
		return dynamic_cast<const Value_Complex&>(value).GetComplex();
	}
	static Complex GetComplexRobust(const Value& value) {
		return
			value.IsType(VTYPE_Complex)? dynamic_cast<const Value_Complex&>(value).GetComplex() :
			value.IsType(VTYPE_Number)? Complex(dynamic_cast<const Value_Number&>(value).GetNumber<Double>()) :
			Complex::Zero;
	}
public:
	static ComplexList GetComplexList(const ValueList& values);
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return static_cast<size_t>(GetComplex().real()); }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetComplex() == Value_Complex::GetComplex(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetComplex().real() < Value_Complex::GetComplex(value).real() :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	//virtual bool IsAsDictKey() const override { return true; }
	//virtual bool Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

}

#endif
