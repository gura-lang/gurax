//==============================================================================
// Imp_Number.h
//==============================================================================
#ifndef GURAX_IMP_NUMBER_H
#define GURAX_IMP_NUMBER_H
#include "Basement.h"
#include "Number.h"

namespace Gurax {

template<typename T_Num>
String Number<T_Num>::ToString(T_Num num)
{
	Int64 numInt = static_cast<Int64>(num);
	return (num == numInt)?
		String().Format(Number::GetFormatterFormat_Int(), numInt) :
		String().Format(Number::GetFormatterFormat_Float(), static_cast<Double>(num));
}

}

#endif
