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
	// Add: num + num
	AssignOpBinary_T(Add, mpz, mpz, mpz);
	AssignOpBinary_T(Add, mpz, mpz, Number);
	AssignOpBinary_T(Add, mpz, Number, mpz);
	AssignOpBinary_T(Add, mpq, mpq, mpq);
	AssignOpBinary_T(Add, mpq, mpq, Number);
	AssignOpBinary_T(Add, mpq, Number, mpq);
	AssignOpBinary_T(Add, mpf, mpf, mpf);
	AssignOpBinary_T(Add, mpf, mpf, Number);
	AssignOpBinary_T(Add, mpf, Number, mpf);
	// Sub: num - num
	AssignOpBinary_T(Sub, mpz, mpz, mpz);
	AssignOpBinary_T(Sub, mpz, mpz, Number);
	AssignOpBinary_T(Sub, mpz, Number, mpz);
	AssignOpBinary_T(Sub, mpq, mpq, mpq);
	AssignOpBinary_T(Sub, mpq, mpq, Number);
	AssignOpBinary_T(Sub, mpq, Number, mpq);
	AssignOpBinary_T(Sub, mpf, mpf, mpf);
	AssignOpBinary_T(Sub, mpf, mpf, Number);
	AssignOpBinary_T(Sub, mpf, Number, mpf);
	// Mul: num * num
	AssignOpBinary_T(Mul, mpz, mpz, mpz);
	AssignOpBinary_T(Mul, mpz, mpz, Number);
	AssignOpBinary_T(Mul, mpz, Number, mpz);
	AssignOpBinary_T(Mul, mpq, mpq, mpq);
	AssignOpBinary_T(Mul, mpq, mpq, Number);
	AssignOpBinary_T(Mul, mpq, Number, mpq);
	AssignOpBinary_T(Mul, mpf, mpf, mpf);
	AssignOpBinary_T(Mul, mpf, mpf, Number);
	AssignOpBinary_T(Mul, mpf, Number, mpf);
	// Div: num / num
	AssignOpBinary_T(Div, mpz, mpz, mpz);
	AssignOpBinary_T(Div, mpz, mpz, Number);
	AssignOpBinary_T(Div, mpz, Number, mpz);
	AssignOpBinary_T(Div, mpq, mpq, mpq);
	AssignOpBinary_T(Div, mpq, mpq, Number);
	AssignOpBinary_T(Div, mpq, Number, mpq);
	AssignOpBinary_T(Div, mpf, mpf, mpf);
	AssignOpBinary_T(Div, mpf, mpf, Number);
	AssignOpBinary_T(Div, mpf, Number, mpf);
	// Eq: num == num
	AssignOpBinary_T(Eq, Bool, mpz, mpz);
	AssignOpBinary_T(Eq, Bool, mpz, Number);
	AssignOpBinary_T(Eq, Bool, Number, mpz);
	AssignOpBinary_T(Eq, Bool, mpq, mpq);
	AssignOpBinary_T(Eq, Bool, mpq, Number);
	AssignOpBinary_T(Eq, Bool, Number, mpq);
	AssignOpBinary_T(Eq, Bool, mpf, mpf);
	AssignOpBinary_T(Eq, Bool, mpf, Number);
	AssignOpBinary_T(Eq, Bool, Number, mpf);
	// Ne: num == num
	AssignOpBinary_T(Ne, Bool, mpz, mpz);
	AssignOpBinary_T(Ne, Bool, mpz, Number);
	AssignOpBinary_T(Ne, Bool, Number, mpz);
	AssignOpBinary_T(Ne, Bool, mpq, mpq);
	AssignOpBinary_T(Ne, Bool, mpq, Number);
	AssignOpBinary_T(Ne, Bool, Number, mpq);
	AssignOpBinary_T(Ne, Bool, mpf, mpf);
	AssignOpBinary_T(Ne, Bool, mpf, Number);
	AssignOpBinary_T(Ne, Bool, Number, mpf);
	// Lt: num < num
	AssignOpBinary_T(Lt, Bool, mpz, mpz);
	AssignOpBinary_T(Lt, Bool, mpz, Number);
	AssignOpBinary_T(Lt, Bool, Number, mpz);
	AssignOpBinary_T(Lt, Bool, mpq, mpq);
	AssignOpBinary_T(Lt, Bool, mpq, Number);
	AssignOpBinary_T(Lt, Bool, Number, mpq);
	AssignOpBinary_T(Lt, Bool, mpf, mpf);
	AssignOpBinary_T(Lt, Bool, mpf, Number);
	AssignOpBinary_T(Lt, Bool, Number, mpf);
	// Le: num <= num
	AssignOpBinary_T(Le, Bool, mpz, mpz);
	AssignOpBinary_T(Le, Bool, mpz, Number);
	AssignOpBinary_T(Le, Bool, Number, mpz);
	AssignOpBinary_T(Le, Bool, mpq, mpq);
	AssignOpBinary_T(Le, Bool, mpq, Number);
	AssignOpBinary_T(Le, Bool, Number, mpq);
	AssignOpBinary_T(Le, Bool, mpf, mpf);
	AssignOpBinary_T(Le, Bool, mpf, Number);
	AssignOpBinary_T(Le, Bool, Number, mpf);
	// Gt: num > num
	AssignOpBinary_T(Gt, Bool, mpz, mpz);
	AssignOpBinary_T(Gt, Bool, mpz, Number);
	AssignOpBinary_T(Gt, Bool, Number, mpz);
	AssignOpBinary_T(Gt, Bool, mpq, mpq);
	AssignOpBinary_T(Gt, Bool, mpq, Number);
	AssignOpBinary_T(Gt, Bool, Number, mpq);
	AssignOpBinary_T(Gt, Bool, mpf, mpf);
	AssignOpBinary_T(Gt, Bool, mpf, Number);
	AssignOpBinary_T(Gt, Bool, Number, mpf);
	// Ge: num >= num
	AssignOpBinary_T(Ge, Bool, mpz, mpz);
	AssignOpBinary_T(Ge, Bool, mpz, Number);
	AssignOpBinary_T(Ge, Bool, Number, mpz);
	AssignOpBinary_T(Ge, Bool, mpq, mpq);
	AssignOpBinary_T(Ge, Bool, mpq, Number);
	AssignOpBinary_T(Ge, Bool, Number, mpq);
	AssignOpBinary_T(Ge, Bool, mpf, mpf);
	AssignOpBinary_T(Ge, Bool, mpf, Number);
	AssignOpBinary_T(Ge, Bool, Number, mpf);
	AssignOpUnary_T(math_Sqrt, mpz, mpz);
	//AssignOpUnary_T(math_Sqrt, mpq, mpq);
	AssignOpUnary_T(math_Sqrt, mpf, mpf);
}

Gurax_EndModuleScope(gmp)
