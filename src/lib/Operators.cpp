//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_ImplementOpPreUnary(Pos, Number)
{
	return pValue->Clone();
}

Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = dynamic_cast<const Value_Number*>(pValueL)->GetDouble();
	Double numR = dynamic_cast<const Value_Number*>(pValueR)->GetDouble();
	return new Value_Number(numL + numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpPreUnary(Pos, Number);
	Gurax_AssignOpBinary(Add, Number, Number);
}

}
