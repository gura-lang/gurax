//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

// ~Number
Gurax_ImplementOpPreUnary(Inv, Number)
{
	Int num = dynamic_cast<const Value_Number&>(value).GetInt();
	return new Value_Number(~num);
}

// -Number
Gurax_ImplementOpPreUnary(Neg, Number)
{
	Double num = dynamic_cast<const Value_Number&>(value).GetDouble();
	return new Value_Number(-num);
}

// !Number
Gurax_ImplementOpPreUnary(Not, Number)
{
	return Value::false_();
}

// +Number
Gurax_ImplementOpPreUnary(Pos, Number)
{
	return value.Clone();
}

// Number + Number
Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL + numR);
}

// Number & Number
Gurax_ImplementOpBinary(And, Number, Number)
{
	Int numL = dynamic_cast<const Value_Number&>(valueL).GetInt();
	Int numR = dynamic_cast<const Value_Number&>(valueR).GetInt();
	return new Value_Number(numL & numR);
}

// Number <=> Number
Gurax_ImplementOpBinary(Cmp, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	int rslt = (numL < numR)? -1 : (numL > numR)? +1 : 0;
	return new Value_Number(rslt);
}

// Number <+> Number
Gurax_ImplementOpBinary(Concat, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL + numR);
}

// Number in Number
Gurax_ImplementOpBinary(Contains, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL == numR);
}

// Number <^> Number
Gurax_ImplementOpBinary(Cross, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL * numR);
}

// Number <-> Number
Gurax_ImplementOpBinary(Difference, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL - numR);
}

// Number / Number
Gurax_ImplementOpBinary(Div, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Number(numL / numR);
}

// Number <.> Number
Gurax_ImplementOpBinary(Dot, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL * numR);
}

// Number == Number
Gurax_ImplementOpBinary(Eq, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Bool(numL == numR);
}

// Number <*> Number
Gurax_ImplementOpBinary(Gear, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL * numR);
}

// Number >= Number
Gurax_ImplementOpBinary(Ge, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Bool(numL >= numR);
}

// Number > Number
Gurax_ImplementOpBinary(Gt, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Bool(numL > numR);
}

// Number <&> Number
Gurax_ImplementOpBinary(Intersection, Number, Number)
{
	Int numL = dynamic_cast<const Value_Number&>(valueL).GetInt();
	Int numR = dynamic_cast<const Value_Number&>(valueR).GetInt();
	return new Value_Number(numL & numR);
}

// Number <= Number
Gurax_ImplementOpBinary(Le, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Bool(numL <= numR);
}

// Number < Number
Gurax_ImplementOpBinary(Lt, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Bool(numL < numR);
}

// Number % Number
Gurax_ImplementOpBinary(Mod, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Number(std::fmod(numL, numR));
}

// Number %% Number
Gurax_ImplementOpBinary(ModMod, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(std::fmod(numL, numR));
}

// Number * Number
Gurax_ImplementOpBinary(Mul, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL * numR);
}

// Number != Number
Gurax_ImplementOpBinary(Ne, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Bool(numL != numR);
}

// Number | Number
Gurax_ImplementOpBinary(Or, Number, Number)
{
	Int numL = dynamic_cast<const Value_Number&>(valueL).GetInt();
	Int numR = dynamic_cast<const Value_Number&>(valueR).GetInt();
	return new Value_Number(numL | numR);
}

// Number => Number
Gurax_ImplementOpBinary(Pair, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL + numR);
}

// Number ** Number
Gurax_ImplementOpBinary(Pow, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(std::pow(numL, numR));
}

// Number .. Number
Gurax_ImplementOpBinary(Seq, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL + numR);
}

// Number << Number
Gurax_ImplementOpBinary(Shl, Number, Number)
{
	Int numL = dynamic_cast<const Value_Number&>(valueL).GetInt();
	Int numR = dynamic_cast<const Value_Number&>(valueR).GetInt();
	return new Value_Number(numL << numR);
}

// Number >> Number
Gurax_ImplementOpBinary(Shr, Number, Number)
{
	Int numL = dynamic_cast<const Value_Number&>(valueL).GetInt();
	Int numR = dynamic_cast<const Value_Number&>(valueR).GetInt();
	return new Value_Number(numL >> numR);
}

// Number - Number
Gurax_ImplementOpBinary(Sub, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL - numR);
}

// Number ||| Number
Gurax_ImplementOpBinary(Union, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number&>(valueL).GetDouble();
	Double numR = dynamic_cast<const Value_Number&>(valueR).GetDouble();
	return new Value_Number(numL + numR);
}

// Number ^ Number
Gurax_ImplementOpBinary(Xor, Number, Number)
{
	Int numL = dynamic_cast<const Value_Number&>(valueL).GetInt();
	Int numR = dynamic_cast<const Value_Number&>(valueR).GetInt();
	return new Value_Number(numL ^ numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpPreUnary(Inv,			Number);
	Gurax_AssignOpPreUnary(Neg,			Number);
	Gurax_AssignOpPreUnary(Not,			Number);
	Gurax_AssignOpPreUnary(Pos,			Number);
	Gurax_AssignOpBinary(Add,			Number, Number);
	Gurax_AssignOpBinary(And,			Number, Number);
	Gurax_AssignOpBinary(Cmp,			Number, Number);
	Gurax_AssignOpBinary(Concat,		Number, Number);
	Gurax_AssignOpBinary(Contains,		Number, Number);
	Gurax_AssignOpBinary(Cross,			Number, Number);
	Gurax_AssignOpBinary(Difference,	Number, Number);
	Gurax_AssignOpBinary(Div,			Number, Number);
	Gurax_AssignOpBinary(Dot,			Number, Number);
	Gurax_AssignOpBinary(Eq,			Number, Number);
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
