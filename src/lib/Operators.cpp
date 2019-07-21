//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

// ~Number
Gurax_ImplementOpUnary(Inv, Number)
{
	Int num = Value_Number::GetNumber<Int>(value);
	return new Value_Number(~num);
}

// -Number
Gurax_ImplementOpUnary(Neg, Number)
{
	Double num = Value_Number::GetNumber<Double>(value);
	return new Value_Number(-num);
}

// !Any
Gurax_ImplementOpUnary(Not, Any)
{
	return value.GetBool()? Value::false_() : Value::true_();
}

// +Number
Gurax_ImplementOpUnary(Pos, Number)
{
	return value.Clone();
}

// Number ..
Gurax_ImplementOpUnary(PostSeq, Number)
{
	int num = Value_Number::GetNumber<Int>(value);
	return new Value_Iterator(new Iterator_Counter(num, 1));
}

// Number + Number
Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// String + String
Gurax_ImplementOpBinary(Add, String, String)
{
	String strL = Value_String::GetStringSTL(valueL);
	const char* strR = Value_String::GetString(valueR);
	strL += strR;
	return new Value_String(strL);
}

// Number & Number
Gurax_ImplementOpBinary(And, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL & numR);
}

// Number <=> Number
Gurax_ImplementOpBinary(Cmp, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	int rslt = (numL < numR)? -1 : (numL > numR)? +1 : 0;
	return new Value_Number(rslt);
}

// Number <+> Number
Gurax_ImplementOpBinary(Concat, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number in Number
Gurax_ImplementOpBinary(Contains, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL == numR);
}

// Number <^> Number
Gurax_ImplementOpBinary(Cross, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number <-> Number
Gurax_ImplementOpBinary(Difference, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL - numR);
}

// Number / Number
Gurax_ImplementOpBinary(Div, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Number(numL / numR);
}

// Number <.> Number
Gurax_ImplementOpBinary(Dot, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number == Number
Gurax_ImplementOpBinary(Eq, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL == numR);
}

// Symbol == Symbol
Gurax_ImplementOpBinary(Eq, Symbol, Symbol)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(pSymbolL->IsIdentical(pSymbolR));
}

// Expr == Expr
Gurax_ImplementOpBinary(Eq, Expr, Expr)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(exprL.IsEqualTo(exprR));
}

// Symbol == Expr
Gurax_ImplementOpBinary(Eq, Symbol, Expr)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(pSymbolL->IsIdentical(exprR));
}

// Expr == Symbol
Gurax_ImplementOpBinary(Eq, Expr, Symbol)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(pSymbolR->IsIdentical(exprL));
}

// Number <*> Number
Gurax_ImplementOpBinary(Gear, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number >= Number
Gurax_ImplementOpBinary(Ge, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL >= numR);
}

// Number > Number
Gurax_ImplementOpBinary(Gt, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL > numR);
}

// Number <&> Number
Gurax_ImplementOpBinary(Intersection, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL & numR);
}

// Number <= Number
Gurax_ImplementOpBinary(Le, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL <= numR);
}

// Number < Number
Gurax_ImplementOpBinary(Lt, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL < numR);
}

// Number % Number
Gurax_ImplementOpBinary(Mod, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Number(std::fmod(numL, numR));
}

// Number %% Number
Gurax_ImplementOpBinary(ModMod, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(std::fmod(numL, numR));
}

// Number * Number
Gurax_ImplementOpBinary(Mul, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number != Number
Gurax_ImplementOpBinary(Ne, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL != numR);
}

// Number | Number
Gurax_ImplementOpBinary(Or, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL | numR);
}

// Number => Number
Gurax_ImplementOpBinary(Pair, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number ** Number
Gurax_ImplementOpBinary(Pow, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(std::pow(numL, numR));
}

// Number .. Number
Gurax_ImplementOpBinary(Seq, Number, Number)
{
	int numL = Value_Number::GetNumber<Int>(valueL);
	int numR = Value_Number::GetNumber<Int>(valueR);
	int idxBegin = 0, idxEnd = 0, idxStep = 0;
	if (numL <= numR) {
		idxBegin = numL, idxEnd = numR + 1, idxStep = 1;
	} else {
		idxBegin = numL, idxEnd = numR - 1, idxStep = -1;
	}
	return new Value_Iterator(new Iterator_Range(idxBegin, idxEnd, idxStep));
}

// Number << Number
Gurax_ImplementOpBinary(Shl, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL << numR);
}

// Number >> Number
Gurax_ImplementOpBinary(Shr, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL >> numR);
}

// Number - Number
Gurax_ImplementOpBinary(Sub, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL - numR);
}

// Number ||| Number
Gurax_ImplementOpBinary(Union, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number ^ Number
Gurax_ImplementOpBinary(Xor, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL ^ numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpUnary(Inv,			Number);
	Gurax_AssignOpUnary(Neg,			Number);
	Gurax_AssignOpUnary(Not,			Any);
	Gurax_AssignOpUnary(Pos,			Number);
	Gurax_AssignOpUnary(PostSeq,		Number);
	Gurax_AssignOpBinary(Add,			Number, Number);
	Gurax_AssignOpBinary(Add,			String, String);
	Gurax_AssignOpBinary(And,			Number, Number);
	Gurax_AssignOpBinary(Cmp,			Number, Number);
	Gurax_AssignOpBinary(Concat,		Number, Number);
	Gurax_AssignOpBinary(Contains,		Number, Number);
	Gurax_AssignOpBinary(Cross,			Number, Number);
	Gurax_AssignOpBinary(Difference,	Number, Number);
	Gurax_AssignOpBinary(Div,			Number, Number);
	Gurax_AssignOpBinary(Dot,			Number, Number);
	Gurax_AssignOpBinary(Eq,			Number, Number);
	Gurax_AssignOpBinary(Eq,			Symbol, Symbol);
	Gurax_AssignOpBinary(Eq,			Expr, Expr);
	Gurax_AssignOpBinary(Eq,			Symbol, Expr);
	Gurax_AssignOpBinary(Eq,			Expr, Symbol);
	Gurax_AssignOpBinary(Gear,			Number, Number);
	Gurax_AssignOpBinary(Ge,			Number, Number);
	Gurax_AssignOpBinary(Gt,			Number, Number);
	Gurax_AssignOpBinary(Intersection,	Number, Number);
	Gurax_AssignOpBinary(Le,			Number, Number);
	Gurax_AssignOpBinary(Lt,			Number, Number);
	Gurax_AssignOpBinary(Mod,			Number, Number);
	Gurax_AssignOpBinary(ModMod,		Number, Number);
	Gurax_AssignOpBinary(Mul,			Number, Number);
	Gurax_AssignOpBinary(Ne,			Number, Number);
	Gurax_AssignOpBinary(Or,			Number, Number);
	Gurax_AssignOpBinary(Pair,			Number, Number);
	Gurax_AssignOpBinary(Pow,			Number, Number);
	Gurax_AssignOpBinary(Seq,			Number, Number);
	Gurax_AssignOpBinary(Shl,			Number, Number);
	Gurax_AssignOpBinary(Shr,			Number, Number);
	Gurax_AssignOpBinary(Sub,			Number, Number);
	Gurax_AssignOpBinary(Union,			Number, Number);
	Gurax_AssignOpBinary(Xor,			Number, Number);
}

}
