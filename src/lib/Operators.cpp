//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_ImplementOpPreUnary(Pos, Number)
{
	return value.Clone();
}

Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Number(numL + numR);
}

Gurax_ImplementOpBinary(Eq, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL == numR);
}

Gurax_ImplementOpBinary(Ge, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL >= numR);
}

Gurax_ImplementOpBinary(Gt, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL > numR);
}

Gurax_ImplementOpBinary(Le, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL <= numR);
}

Gurax_ImplementOpBinary(Lt, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(&valueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(&valueR)->GetDouble();
	return new Value_Bool(numL < numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpPreUnary(Pos, Number);
	Gurax_AssignOpBinary(Add, Number, Number);
	Gurax_AssignOpBinary(Eq, Number, Number);
	Gurax_AssignOpBinary(Ge, Number, Number);
	Gurax_AssignOpBinary(Gt, Number, Number);
	Gurax_AssignOpBinary(Le, Number, Number);
	Gurax_AssignOpBinary(Lt, Number, Number);
}

}
