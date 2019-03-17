//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

// ~Number
Gurax_ImplementOpPreUnary(Inv, Number)
{
	Int num = dynamic_cast<const Value_Number*>(&value)->GetInt();
	return new Value_Number(~num);
}

// -Number
Gurax_ImplementOpPreUnary(Neg, Number)
{
	Double num = dynamic_cast<const Value_Number*>(&value)->GetDouble();
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

// `Expr
Gurax_ImplementOpPreUnary(Quote, Expr)
{
	return value.Clone();
}

// Number + Number
Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Number(numL + numR);
}

// Number == Number
Gurax_ImplementOpBinary(Eq, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL == numR);
}

// Number >= Number
Gurax_ImplementOpBinary(Ge, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL >= numR);
}

// Number > Number
Gurax_ImplementOpBinary(Gt, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL > numR);
}

// Number <= Number
Gurax_ImplementOpBinary(Le, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL <= numR);
}

// Number < Number
Gurax_ImplementOpBinary(Lt, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL < numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpPreUnary(Inv, Number);
	Gurax_AssignOpPreUnary(Neg, Number);
	Gurax_AssignOpPreUnary(Not, Number);
	Gurax_AssignOpPreUnary(Pos, Number);
	Gurax_AssignOpPreUnary(Quote, Expr);
	Gurax_AssignOpBinary(Add, Number, Number);
	Gurax_AssignOpBinary(Eq, Number, Number);
	Gurax_AssignOpBinary(Ge, Number, Number);
	Gurax_AssignOpBinary(Gt, Number, Number);
	Gurax_AssignOpBinary(Le, Number, Number);
	Gurax_AssignOpBinary(Lt, Number, Number);
}

}
