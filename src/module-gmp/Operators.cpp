//==============================================================================
// Operators.cpp
//==============================================================================
#include "stdafx.h"

#define AssignOpBinary_T(opType, typeNameRtn, typeNameL, typeNameR) \
Operator::opType->AssignEntry(VTYPE_##typeNameL, VTYPE_##typeNameR, new OpEntry_##opType##_T<Value_##typeNameRtn, Value_##typeNameL, Value_##typeNameR>())

#define AssignOpUnary_T(opType, typeNameRtn, typeName) \
Operator::opType->AssignEntry(VTYPE_##typeName, new OpEntry_##opType##_T<Value_##typeNameRtn, Value_##typeName>())

Gurax_BeginModuleScope(gmp)

inline bool IsZero(const mpz_class& num) { return mpz_sgn(num.get_mpz_t()) == 0; }
inline bool IsZero(const mpq_class& num) { return mpq_sgn(num.get_mpq_t()) == 0; }
inline bool IsZero(const mpf_class& num) { return mpf_sgn(num.get_mpf_t()) == 0; }
inline bool IsZero(Double num) { return num == 0; }

template<typename T_ValueRtn, typename T_Value>
class OpEntry_Inv_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(~num);

	}
};

template<typename T_ValueRtn, typename T_Value>
class OpEntry_Neg_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(-num);

	}
};

template<typename T_ValueRtn, typename T_Value>
class OpEntry_Not_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(IsZero(num));

	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Add_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL + numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Add_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL + numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Add_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL + numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Sub_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL - numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Sub_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL - numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Sub_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL - numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Mul_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL * numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Mul_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL * numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Mul_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL * numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Div_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		if (IsZero(numR)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return Value::nil();
		}
		return new T_ValueRtn(numL / numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Div_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		if (IsZero(numR)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return Value::nil();
		}
		return new T_ValueRtn(numL / numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Div_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		if (IsZero(numR)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return Value::nil();
		}
		return new T_ValueRtn(numL / numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Mod_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		if (IsZero(numR)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return Value::nil();
		}
		return new T_ValueRtn(numL % numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Mod_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Int64 numR = Value_Number::GetNumber<Int64>(valueR);
		if (IsZero(numR)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return Value::nil();
		}
		return new T_ValueRtn(numL % numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Mod_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Int64 numL = Value_Number::GetNumber<Int64>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		if (IsZero(numR)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return Value::nil();
		}
		return new T_ValueRtn(numL % numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Eq_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL == numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Eq_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL == numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Eq_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL == numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Ne_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL != numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Ne_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL != numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Ne_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL != numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Lt_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL < numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Lt_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL < numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Lt_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL < numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Le_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL <= numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Le_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL <= numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Le_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL <= numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Gt_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL > numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Gt_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL > numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Gt_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL > numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Ge_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL >= numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Ge_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL >= numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Ge_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL >= numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Cmp_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(::cmp(numL, numR));
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Cmp_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(::cmp(numL, numR));
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Cmp_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(::cmp(numL, numR));
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_And_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL & numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_And_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL & numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_And_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL & numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Or_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL | numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Or_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL | numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Or_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL | numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL, typename T_ValueR>
class OpEntry_Xor_T : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL ^ numR);
	}
};

template<typename T_ValueRtn, typename T_ValueL>
class OpEntry_Xor_T<T_ValueRtn, T_ValueL, Value_Number> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		auto& numL = T_ValueL::GetEntity(valueL);
		Double numR = Value_Number::GetNumber<Double>(valueR);
		return new T_ValueRtn(numL ^ numR);
	}
};

template<typename T_ValueRtn, typename T_ValueR>
class OpEntry_Xor_T<T_ValueRtn, Value_Number, T_ValueR> : public OpEntry {
public:
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const {
		Double numL = Value_Number::GetNumber<Double>(valueL);
		auto& numR = T_ValueR::GetEntity(valueR);
		return new T_ValueRtn(numL ^ numR);
	}
};

template<typename T_ValueRtn, typename T_Value>
class OpEntry_math_Abs_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(::abs(num));

	}
};

template<typename T_ValueRtn, typename T_Value>
class OpEntry_math_Ceil_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(::ceil(num));

	}
};

template<>
class OpEntry_math_Ceil_T<Value_Int, Value_Int> : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = Value_Int::GetEntity(value);
		return new Value_Int(num);
	}
};

template<typename T_ValueRtn, typename T_Value>
class OpEntry_math_Floor_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(::floor(num));

	}
};

template<>
class OpEntry_math_Floor_T<Value_Int, Value_Int> : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = Value_Int::GetEntity(value);
		return new Value_Int(num);
	}
};

template<typename T_ValueRtn, typename T_Value>
class OpEntry_math_Sqrt_T : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = T_Value::GetEntity(value);
		return new T_ValueRtn(::sqrt(num));

	}
};

void AssignOperators()
{
	// Inv: ~num
	AssignOpUnary_T(Inv, Int, Int);
	// Neg: -num
	AssignOpUnary_T(Neg, Int, Int);
	AssignOpUnary_T(Neg, Rational, Rational);
	AssignOpUnary_T(Neg, Float, Float);
	// Not: !num
	AssignOpUnary_T(Not, Bool, Int);
	AssignOpUnary_T(Not, Bool, Rational);
	AssignOpUnary_T(Not, Bool, Float);
	// Add: num + num
	AssignOpBinary_T(Add, Int, Int, Int);
	AssignOpBinary_T(Add, Rational, Int, Rational);
	AssignOpBinary_T(Add, Float, Int, Float);
	AssignOpBinary_T(Add, Int, Int, Number);
	AssignOpBinary_T(Add, Rational, Rational, Int);
	AssignOpBinary_T(Add, Rational, Rational, Rational);
	AssignOpBinary_T(Add, Float, Rational, Float);
	AssignOpBinary_T(Add, Rational, Rational, Number);
	AssignOpBinary_T(Add, Float, Float, Int);
	AssignOpBinary_T(Add, Float, Float, Rational);
	AssignOpBinary_T(Add, Float, Float, Float);
	AssignOpBinary_T(Add, Float, Float, Number);
	AssignOpBinary_T(Add, Int, Number, Int);
	AssignOpBinary_T(Add, Rational, Number, Rational);
	AssignOpBinary_T(Add, Float, Number, Float);
	// Sub: num - num
	AssignOpBinary_T(Sub, Int, Int, Int);
	AssignOpBinary_T(Sub, Rational, Int, Rational);
	AssignOpBinary_T(Sub, Float, Int, Float);
	AssignOpBinary_T(Sub, Int, Int, Number);
	AssignOpBinary_T(Sub, Rational, Rational, Int);
	AssignOpBinary_T(Sub, Rational, Rational, Rational);
	AssignOpBinary_T(Sub, Float, Rational, Float);
	AssignOpBinary_T(Sub, Rational, Rational, Number);
	AssignOpBinary_T(Sub, Float, Float, Int);
	AssignOpBinary_T(Sub, Float, Float, Rational);
	AssignOpBinary_T(Sub, Float, Float, Float);
	AssignOpBinary_T(Sub, Float, Float, Number);
	AssignOpBinary_T(Sub, Int, Number, Int);
	AssignOpBinary_T(Sub, Rational, Number, Rational);
	AssignOpBinary_T(Sub, Float, Number, Float);
	// Mul: num * num
	AssignOpBinary_T(Mul, Int, Int, Int);
	AssignOpBinary_T(Mul, Rational, Int, Rational);
	AssignOpBinary_T(Mul, Float, Int, Float);
	AssignOpBinary_T(Mul, Int, Int, Number);
	AssignOpBinary_T(Mul, Rational, Rational, Int);
	AssignOpBinary_T(Mul, Rational, Rational, Rational);
	AssignOpBinary_T(Mul, Float, Rational, Float);
	AssignOpBinary_T(Mul, Rational, Rational, Number);
	AssignOpBinary_T(Mul, Float, Float, Int);
	AssignOpBinary_T(Mul, Float, Float, Rational);
	AssignOpBinary_T(Mul, Float, Float, Float);
	AssignOpBinary_T(Mul, Float, Float, Number);
	AssignOpBinary_T(Mul, Int, Number, Int);
	AssignOpBinary_T(Mul, Rational, Number, Rational);
	AssignOpBinary_T(Mul, Float, Number, Float);
	// Div: num / num
	AssignOpBinary_T(Div, Int, Int, Int);
	AssignOpBinary_T(Div, Rational, Int, Rational);
	AssignOpBinary_T(Div, Float, Int, Float);
	AssignOpBinary_T(Div, Int, Int, Number);
	AssignOpBinary_T(Div, Rational, Rational, Int);
	AssignOpBinary_T(Div, Rational, Rational, Rational);
	AssignOpBinary_T(Div, Float, Rational, Float);
	AssignOpBinary_T(Div, Rational, Rational, Number);
	AssignOpBinary_T(Div, Float, Float, Int);
	AssignOpBinary_T(Div, Float, Float, Rational);
	AssignOpBinary_T(Div, Float, Float, Float);
	AssignOpBinary_T(Div, Float, Float, Number);
	AssignOpBinary_T(Div, Int, Number, Int);
	AssignOpBinary_T(Div, Rational, Number, Rational);
	AssignOpBinary_T(Div, Float, Number, Float);
	// Mod: num % num
	AssignOpBinary_T(Mod, Int, Int, Int);
	AssignOpBinary_T(Mod, Int, Int, Number);
	AssignOpBinary_T(Mod, Int, Number, Int);
	// And: num & num
	AssignOpBinary_T(And, Int, Int, Int);
	AssignOpBinary_T(And, Int, Int, Number);
	AssignOpBinary_T(And, Int, Number, Int);
	// Or: num | num
	AssignOpBinary_T(Or, Int, Int, Int);
	AssignOpBinary_T(Or, Int, Int, Number);
	AssignOpBinary_T(Or, Int, Number, Int);
	// Xor: num | num
	AssignOpBinary_T(Xor, Int, Int, Int);
	AssignOpBinary_T(Xor, Int, Int, Number);
	AssignOpBinary_T(Xor, Int, Number, Int);
	// Eq: num == num
	AssignOpBinary_T(Eq, Bool, Int, Int);
	AssignOpBinary_T(Eq, Bool, Int, Rational);
	AssignOpBinary_T(Eq, Bool, Int, Float);
	AssignOpBinary_T(Eq, Bool, Int, Number);
	AssignOpBinary_T(Eq, Bool, Rational, Int);
	AssignOpBinary_T(Eq, Bool, Rational, Rational);
	AssignOpBinary_T(Eq, Bool, Rational, Float);
	AssignOpBinary_T(Eq, Bool, Rational, Number);
	AssignOpBinary_T(Eq, Bool, Float, Int);
	AssignOpBinary_T(Eq, Bool, Float, Rational);
	AssignOpBinary_T(Eq, Bool, Float, Float);
	AssignOpBinary_T(Eq, Bool, Float, Number);
	AssignOpBinary_T(Eq, Bool, Number, Int);
	AssignOpBinary_T(Eq, Bool, Number, Rational);
	AssignOpBinary_T(Eq, Bool, Number, Float);
	// Ne: num != num
	AssignOpBinary_T(Ne, Bool, Int, Int);
	AssignOpBinary_T(Ne, Bool, Int, Rational);
	AssignOpBinary_T(Ne, Bool, Int, Float);
	AssignOpBinary_T(Ne, Bool, Int, Number);
	AssignOpBinary_T(Ne, Bool, Rational, Int);
	AssignOpBinary_T(Ne, Bool, Rational, Rational);
	AssignOpBinary_T(Ne, Bool, Rational, Float);
	AssignOpBinary_T(Ne, Bool, Rational, Number);
	AssignOpBinary_T(Ne, Bool, Float, Int);
	AssignOpBinary_T(Ne, Bool, Float, Rational);
	AssignOpBinary_T(Ne, Bool, Float, Float);
	AssignOpBinary_T(Ne, Bool, Float, Number);
	AssignOpBinary_T(Ne, Bool, Number, Int);
	AssignOpBinary_T(Ne, Bool, Number, Rational);
	AssignOpBinary_T(Ne, Bool, Number, Float);
	// Lt: num < num
	AssignOpBinary_T(Lt, Bool, Int, Int);
	AssignOpBinary_T(Lt, Bool, Int, Rational);
	AssignOpBinary_T(Lt, Bool, Int, Float);
	AssignOpBinary_T(Lt, Bool, Int, Number);
	AssignOpBinary_T(Lt, Bool, Rational, Int);
	AssignOpBinary_T(Lt, Bool, Rational, Rational);
	AssignOpBinary_T(Lt, Bool, Rational, Float);
	AssignOpBinary_T(Lt, Bool, Rational, Number);
	AssignOpBinary_T(Lt, Bool, Float, Int);
	AssignOpBinary_T(Lt, Bool, Float, Rational);
	AssignOpBinary_T(Lt, Bool, Float, Float);
	AssignOpBinary_T(Lt, Bool, Float, Number);
	AssignOpBinary_T(Lt, Bool, Number, Int);
	AssignOpBinary_T(Lt, Bool, Number, Rational);
	AssignOpBinary_T(Lt, Bool, Number, Float);
	// Le: num <= num
	AssignOpBinary_T(Le, Bool, Int, Int);
	AssignOpBinary_T(Le, Bool, Int, Rational);
	AssignOpBinary_T(Le, Bool, Int, Float);
	AssignOpBinary_T(Le, Bool, Int, Number);
	AssignOpBinary_T(Le, Bool, Rational, Int);
	AssignOpBinary_T(Le, Bool, Rational, Rational);
	AssignOpBinary_T(Le, Bool, Rational, Float);
	AssignOpBinary_T(Le, Bool, Rational, Number);
	AssignOpBinary_T(Le, Bool, Float, Int);
	AssignOpBinary_T(Le, Bool, Float, Rational);
	AssignOpBinary_T(Le, Bool, Float, Float);
	AssignOpBinary_T(Le, Bool, Float, Number);
	AssignOpBinary_T(Le, Bool, Number, Int);
	AssignOpBinary_T(Le, Bool, Number, Rational);
	AssignOpBinary_T(Le, Bool, Number, Float);
	// Gt: num > num
	AssignOpBinary_T(Gt, Bool, Int, Int);
	AssignOpBinary_T(Gt, Bool, Int, Rational);
	AssignOpBinary_T(Gt, Bool, Int, Float);
	AssignOpBinary_T(Gt, Bool, Int, Number);
	AssignOpBinary_T(Gt, Bool, Rational, Int);
	AssignOpBinary_T(Gt, Bool, Rational, Rational);
	AssignOpBinary_T(Gt, Bool, Rational, Float);
	AssignOpBinary_T(Gt, Bool, Rational, Number);
	AssignOpBinary_T(Gt, Bool, Float, Int);
	AssignOpBinary_T(Gt, Bool, Float, Rational);
	AssignOpBinary_T(Gt, Bool, Float, Float);
	AssignOpBinary_T(Gt, Bool, Float, Number);
	AssignOpBinary_T(Gt, Bool, Number, Int);
	AssignOpBinary_T(Gt, Bool, Number, Rational);
	AssignOpBinary_T(Gt, Bool, Number, Float);
	// Ge: num >= num
	AssignOpBinary_T(Ge, Bool, Int, Int);
	AssignOpBinary_T(Ge, Bool, Int, Rational);
	AssignOpBinary_T(Ge, Bool, Int, Float);
	AssignOpBinary_T(Ge, Bool, Int, Number);
	AssignOpBinary_T(Ge, Bool, Rational, Int);
	AssignOpBinary_T(Ge, Bool, Rational, Rational);
	AssignOpBinary_T(Ge, Bool, Rational, Float);
	AssignOpBinary_T(Ge, Bool, Rational, Number);
	AssignOpBinary_T(Ge, Bool, Float, Int);
	AssignOpBinary_T(Ge, Bool, Float, Rational);
	AssignOpBinary_T(Ge, Bool, Float, Float);
	AssignOpBinary_T(Ge, Bool, Float, Number);
	AssignOpBinary_T(Ge, Bool, Number, Int);
	AssignOpBinary_T(Ge, Bool, Number, Rational);
	AssignOpBinary_T(Ge, Bool, Number, Float);
	// Cmp: num <=> num
	AssignOpBinary_T(Cmp, Number, Int, Int);
	AssignOpBinary_T(Cmp, Number, Int, Rational);
	AssignOpBinary_T(Cmp, Number, Int, Float);
	AssignOpBinary_T(Cmp, Number, Int, Number);
	AssignOpBinary_T(Cmp, Number, Rational, Int);
	AssignOpBinary_T(Cmp, Number, Rational, Rational);
	AssignOpBinary_T(Cmp, Number, Rational, Float);
	AssignOpBinary_T(Cmp, Number, Rational, Number);
	AssignOpBinary_T(Cmp, Number, Float, Int);
	AssignOpBinary_T(Cmp, Number, Float, Rational);
	AssignOpBinary_T(Cmp, Number, Float, Float);
	AssignOpBinary_T(Cmp, Number, Float, Number);
	AssignOpBinary_T(Cmp, Number, Number, Int);
	AssignOpBinary_T(Cmp, Number, Number, Rational);
	AssignOpBinary_T(Cmp, Number, Number, Float);
	// math.Abs
	AssignOpUnary_T(math_Abs, Int, Int);
	AssignOpUnary_T(math_Abs, Rational, Rational);
	AssignOpUnary_T(math_Abs, Float, Float);
	// math.Ceil
	AssignOpUnary_T(math_Ceil, Int, Int);
	//AssignOpUnary_T(math_Ceil, Rational, Rational);
	AssignOpUnary_T(math_Ceil, Float, Float);
	// math.Floor
	AssignOpUnary_T(math_Floor, Int, Int);
	//AssignOpUnary_T(math_Floor, Rational, Rational);
	AssignOpUnary_T(math_Floor, Float, Float);
	// math.Sqrt
	AssignOpUnary_T(math_Sqrt, Int, Int);
	//AssignOpUnary_T(math_Sqrt, Rational, Rational);
	AssignOpUnary_T(math_Sqrt, Float, Float);
}

Gurax_EndModuleScope(gmp)
