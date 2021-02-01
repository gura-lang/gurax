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
class OpEntry_math_Ceil_T<Value_mpz, Value_mpz> : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = Value_mpz::GetEntity(value);
		return new Value_mpz(num);
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
class OpEntry_math_Floor_T<Value_mpz, Value_mpz> : public OpEntry {
public:
	virtual Value* EvalUnary(Processor& processor, Value& value) const {
		auto& num = Value_mpz::GetEntity(value);
		return new Value_mpz(num);
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
	AssignOpUnary_T(Inv, mpz, mpz);
	// Neg: -num
	AssignOpUnary_T(Neg, mpz, mpz);
	AssignOpUnary_T(Neg, mpq, mpq);
	AssignOpUnary_T(Neg, mpf, mpf);
	// Not: !num
	AssignOpUnary_T(Not, Bool, mpz);
	AssignOpUnary_T(Not, Bool, mpq);
	AssignOpUnary_T(Not, Bool, mpf);
	// Add: num + num
	AssignOpBinary_T(Add, mpz, mpz, mpz);
	AssignOpBinary_T(Add, mpq, mpz, mpq);
	AssignOpBinary_T(Add, mpf, mpz, mpf);
	AssignOpBinary_T(Add, mpz, mpz, Number);
	AssignOpBinary_T(Add, mpq, mpq, mpz);
	AssignOpBinary_T(Add, mpq, mpq, mpq);
	AssignOpBinary_T(Add, mpf, mpq, mpf);
	AssignOpBinary_T(Add, mpq, mpq, Number);
	AssignOpBinary_T(Add, mpf, mpf, mpz);
	AssignOpBinary_T(Add, mpf, mpf, mpq);
	AssignOpBinary_T(Add, mpf, mpf, mpf);
	AssignOpBinary_T(Add, mpf, mpf, Number);
	AssignOpBinary_T(Add, mpz, Number, mpz);
	AssignOpBinary_T(Add, mpq, Number, mpq);
	AssignOpBinary_T(Add, mpf, Number, mpf);
	// Sub: num - num
	AssignOpBinary_T(Sub, mpz, mpz, mpz);
	AssignOpBinary_T(Sub, mpq, mpz, mpq);
	AssignOpBinary_T(Sub, mpf, mpz, mpf);
	AssignOpBinary_T(Sub, mpz, mpz, Number);
	AssignOpBinary_T(Sub, mpq, mpq, mpz);
	AssignOpBinary_T(Sub, mpq, mpq, mpq);
	AssignOpBinary_T(Sub, mpf, mpq, mpf);
	AssignOpBinary_T(Sub, mpq, mpq, Number);
	AssignOpBinary_T(Sub, mpf, mpf, mpz);
	AssignOpBinary_T(Sub, mpf, mpf, mpq);
	AssignOpBinary_T(Sub, mpf, mpf, mpf);
	AssignOpBinary_T(Sub, mpf, mpf, Number);
	AssignOpBinary_T(Sub, mpz, Number, mpz);
	AssignOpBinary_T(Sub, mpq, Number, mpq);
	AssignOpBinary_T(Sub, mpf, Number, mpf);
	// Mul: num * num
	AssignOpBinary_T(Mul, mpz, mpz, mpz);
	AssignOpBinary_T(Mul, mpq, mpz, mpq);
	AssignOpBinary_T(Mul, mpf, mpz, mpf);
	AssignOpBinary_T(Mul, mpz, mpz, Number);
	AssignOpBinary_T(Mul, mpq, mpq, mpz);
	AssignOpBinary_T(Mul, mpq, mpq, mpq);
	AssignOpBinary_T(Mul, mpf, mpq, mpf);
	AssignOpBinary_T(Mul, mpq, mpq, Number);
	AssignOpBinary_T(Mul, mpf, mpf, mpz);
	AssignOpBinary_T(Mul, mpf, mpf, mpq);
	AssignOpBinary_T(Mul, mpf, mpf, mpf);
	AssignOpBinary_T(Mul, mpf, mpf, Number);
	AssignOpBinary_T(Mul, mpz, Number, mpz);
	AssignOpBinary_T(Mul, mpq, Number, mpq);
	AssignOpBinary_T(Mul, mpf, Number, mpf);
	// Div: num / num
	AssignOpBinary_T(Div, mpz, mpz, mpz);
	AssignOpBinary_T(Div, mpq, mpz, mpq);
	AssignOpBinary_T(Div, mpf, mpz, mpf);
	AssignOpBinary_T(Div, mpz, mpz, Number);
	AssignOpBinary_T(Div, mpq, mpq, mpz);
	AssignOpBinary_T(Div, mpq, mpq, mpq);
	AssignOpBinary_T(Div, mpf, mpq, mpf);
	AssignOpBinary_T(Div, mpq, mpq, Number);
	AssignOpBinary_T(Div, mpf, mpf, mpz);
	AssignOpBinary_T(Div, mpf, mpf, mpq);
	AssignOpBinary_T(Div, mpf, mpf, mpf);
	AssignOpBinary_T(Div, mpf, mpf, Number);
	AssignOpBinary_T(Div, mpz, Number, mpz);
	AssignOpBinary_T(Div, mpq, Number, mpq);
	AssignOpBinary_T(Div, mpf, Number, mpf);
	// Mod: num % num
	AssignOpBinary_T(Mod, mpz, mpz, mpz);
	AssignOpBinary_T(Mod, mpz, mpz, Number);
	AssignOpBinary_T(Mod, mpz, Number, mpz);
	// And: num & num
	AssignOpBinary_T(And, mpz, mpz, mpz);
	AssignOpBinary_T(And, mpz, mpz, Number);
	AssignOpBinary_T(And, mpz, Number, mpz);
	// Or: num | num
	AssignOpBinary_T(Or, mpz, mpz, mpz);
	AssignOpBinary_T(Or, mpz, mpz, Number);
	AssignOpBinary_T(Or, mpz, Number, mpz);
	// Xor: num | num
	AssignOpBinary_T(Xor, mpz, mpz, mpz);
	AssignOpBinary_T(Xor, mpz, mpz, Number);
	AssignOpBinary_T(Xor, mpz, Number, mpz);
	// Eq: num == num
	AssignOpBinary_T(Eq, Bool, mpz, mpz);
	AssignOpBinary_T(Eq, Bool, mpz, mpq);
	AssignOpBinary_T(Eq, Bool, mpz, mpf);
	AssignOpBinary_T(Eq, Bool, mpz, Number);
	AssignOpBinary_T(Eq, Bool, mpq, mpz);
	AssignOpBinary_T(Eq, Bool, mpq, mpq);
	AssignOpBinary_T(Eq, Bool, mpq, mpf);
	AssignOpBinary_T(Eq, Bool, mpq, Number);
	AssignOpBinary_T(Eq, Bool, mpf, mpz);
	AssignOpBinary_T(Eq, Bool, mpf, mpq);
	AssignOpBinary_T(Eq, Bool, mpf, mpf);
	AssignOpBinary_T(Eq, Bool, mpf, Number);
	AssignOpBinary_T(Eq, Bool, Number, mpz);
	AssignOpBinary_T(Eq, Bool, Number, mpq);
	AssignOpBinary_T(Eq, Bool, Number, mpf);
	// Ne: num != num
	AssignOpBinary_T(Ne, Bool, mpz, mpz);
	AssignOpBinary_T(Ne, Bool, mpz, mpq);
	AssignOpBinary_T(Ne, Bool, mpz, mpf);
	AssignOpBinary_T(Ne, Bool, mpz, Number);
	AssignOpBinary_T(Ne, Bool, mpq, mpz);
	AssignOpBinary_T(Ne, Bool, mpq, mpq);
	AssignOpBinary_T(Ne, Bool, mpq, mpf);
	AssignOpBinary_T(Ne, Bool, mpq, Number);
	AssignOpBinary_T(Ne, Bool, mpf, mpz);
	AssignOpBinary_T(Ne, Bool, mpf, mpq);
	AssignOpBinary_T(Ne, Bool, mpf, mpf);
	AssignOpBinary_T(Ne, Bool, mpf, Number);
	AssignOpBinary_T(Ne, Bool, Number, mpz);
	AssignOpBinary_T(Ne, Bool, Number, mpq);
	AssignOpBinary_T(Ne, Bool, Number, mpf);
	// Lt: num < num
	AssignOpBinary_T(Lt, Bool, mpz, mpz);
	AssignOpBinary_T(Lt, Bool, mpz, mpq);
	AssignOpBinary_T(Lt, Bool, mpz, mpf);
	AssignOpBinary_T(Lt, Bool, mpz, Number);
	AssignOpBinary_T(Lt, Bool, mpq, mpz);
	AssignOpBinary_T(Lt, Bool, mpq, mpq);
	AssignOpBinary_T(Lt, Bool, mpq, mpf);
	AssignOpBinary_T(Lt, Bool, mpq, Number);
	AssignOpBinary_T(Lt, Bool, mpf, mpz);
	AssignOpBinary_T(Lt, Bool, mpf, mpq);
	AssignOpBinary_T(Lt, Bool, mpf, mpf);
	AssignOpBinary_T(Lt, Bool, mpf, Number);
	AssignOpBinary_T(Lt, Bool, Number, mpz);
	AssignOpBinary_T(Lt, Bool, Number, mpq);
	AssignOpBinary_T(Lt, Bool, Number, mpf);
	// Le: num <= num
	AssignOpBinary_T(Le, Bool, mpz, mpz);
	AssignOpBinary_T(Le, Bool, mpz, mpq);
	AssignOpBinary_T(Le, Bool, mpz, mpf);
	AssignOpBinary_T(Le, Bool, mpz, Number);
	AssignOpBinary_T(Le, Bool, mpq, mpz);
	AssignOpBinary_T(Le, Bool, mpq, mpq);
	AssignOpBinary_T(Le, Bool, mpq, mpf);
	AssignOpBinary_T(Le, Bool, mpq, Number);
	AssignOpBinary_T(Le, Bool, mpf, mpz);
	AssignOpBinary_T(Le, Bool, mpf, mpq);
	AssignOpBinary_T(Le, Bool, mpf, mpf);
	AssignOpBinary_T(Le, Bool, mpf, Number);
	AssignOpBinary_T(Le, Bool, Number, mpz);
	AssignOpBinary_T(Le, Bool, Number, mpq);
	AssignOpBinary_T(Le, Bool, Number, mpf);
	// Gt: num > num
	AssignOpBinary_T(Gt, Bool, mpz, mpz);
	AssignOpBinary_T(Gt, Bool, mpz, mpq);
	AssignOpBinary_T(Gt, Bool, mpz, mpf);
	AssignOpBinary_T(Gt, Bool, mpz, Number);
	AssignOpBinary_T(Gt, Bool, mpq, mpz);
	AssignOpBinary_T(Gt, Bool, mpq, mpq);
	AssignOpBinary_T(Gt, Bool, mpq, mpf);
	AssignOpBinary_T(Gt, Bool, mpq, Number);
	AssignOpBinary_T(Gt, Bool, mpf, mpz);
	AssignOpBinary_T(Gt, Bool, mpf, mpq);
	AssignOpBinary_T(Gt, Bool, mpf, mpf);
	AssignOpBinary_T(Gt, Bool, mpf, Number);
	AssignOpBinary_T(Gt, Bool, Number, mpz);
	AssignOpBinary_T(Gt, Bool, Number, mpq);
	AssignOpBinary_T(Gt, Bool, Number, mpf);
	// Ge: num >= num
	AssignOpBinary_T(Ge, Bool, mpz, mpz);
	AssignOpBinary_T(Ge, Bool, mpz, mpq);
	AssignOpBinary_T(Ge, Bool, mpz, mpf);
	AssignOpBinary_T(Ge, Bool, mpz, Number);
	AssignOpBinary_T(Ge, Bool, mpq, mpz);
	AssignOpBinary_T(Ge, Bool, mpq, mpq);
	AssignOpBinary_T(Ge, Bool, mpq, mpf);
	AssignOpBinary_T(Ge, Bool, mpq, Number);
	AssignOpBinary_T(Ge, Bool, mpf, mpz);
	AssignOpBinary_T(Ge, Bool, mpf, mpq);
	AssignOpBinary_T(Ge, Bool, mpf, mpf);
	AssignOpBinary_T(Ge, Bool, mpf, Number);
	AssignOpBinary_T(Ge, Bool, Number, mpz);
	AssignOpBinary_T(Ge, Bool, Number, mpq);
	AssignOpBinary_T(Ge, Bool, Number, mpf);
	// Cmp: num <=> num
	AssignOpBinary_T(Cmp, Number, mpz, mpz);
	AssignOpBinary_T(Cmp, Number, mpz, mpq);
	AssignOpBinary_T(Cmp, Number, mpz, mpf);
	AssignOpBinary_T(Cmp, Number, mpz, Number);
	AssignOpBinary_T(Cmp, Number, mpq, mpz);
	AssignOpBinary_T(Cmp, Number, mpq, mpq);
	AssignOpBinary_T(Cmp, Number, mpq, mpf);
	AssignOpBinary_T(Cmp, Number, mpq, Number);
	AssignOpBinary_T(Cmp, Number, mpf, mpz);
	AssignOpBinary_T(Cmp, Number, mpf, mpq);
	AssignOpBinary_T(Cmp, Number, mpf, mpf);
	AssignOpBinary_T(Cmp, Number, mpf, Number);
	AssignOpBinary_T(Cmp, Number, Number, mpz);
	AssignOpBinary_T(Cmp, Number, Number, mpq);
	AssignOpBinary_T(Cmp, Number, Number, mpf);
	// math.Abs
	AssignOpUnary_T(math_Abs, mpz, mpz);
	AssignOpUnary_T(math_Abs, mpq, mpq);
	AssignOpUnary_T(math_Abs, mpf, mpf);
	// math.Ceil
	AssignOpUnary_T(math_Ceil, mpz, mpz);
	//AssignOpUnary_T(math_Ceil, mpq, mpq);
	AssignOpUnary_T(math_Ceil, mpf, mpf);
	// math.Floor
	AssignOpUnary_T(math_Floor, mpz, mpz);
	//AssignOpUnary_T(math_Floor, mpq, mpq);
	AssignOpUnary_T(math_Floor, mpf, mpf);
	// math.Sqrt
	AssignOpUnary_T(math_Sqrt, mpz, mpz);
	//AssignOpUnary_T(math_Sqrt, mpq, mpq);
	AssignOpUnary_T(math_Sqrt, mpf, mpf);
}

Gurax_EndModuleScope(gmp)
