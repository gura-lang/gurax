//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_ImplementOpUnary(Pos, number)
{
	return pObject->Clone();
}

Gurax_ImplementOpBinary(Add, number, number)
{
	Double numL = dynamic_cast<const Object_number*>(pObjectL)->GetDouble();
	Double numR = dynamic_cast<const Object_number*>(pObjectR)->GetDouble();
	return new Object_number(numL + numR);
}

void Operators::Bootup()
{
	Gurax_AssignOpUnary(Pos, number);
	Gurax_AssignOpBinary(Add, number, number);
}

}
