//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_ImplementOpPreUnary(Pos, Number)
{
	return pObject->Clone();
}

Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = dynamic_cast<const Object_Number*>(pObjectL)->GetDouble();
	Double numR = dynamic_cast<const Object_Number*>(pObjectR)->GetDouble();
	return new Object_Number(numL + numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpPreUnary(Pos, Number);
	Gurax_AssignOpBinary(Add, Number, Number);
}

}
