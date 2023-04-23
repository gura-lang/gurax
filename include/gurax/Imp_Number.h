//==============================================================================
// Imp_Number.h
//==============================================================================
#ifndef GURAX_IMP_NUMBER_H
#define GURAX_IMP_NUMBER_H
#include "Basement.h"
#include "Number.h"

namespace Gurax {

template<typename T_Num>
String& Number<T_Num>::ToString(String& str, T_Num num)
{
	Int64 numInt = static_cast<Int64>(num);
	if (num == numInt) {
		str.Format(formatterFormat_Int.c_str(), numInt);
	} else {
		str.Format(formatterFormat_Float.c_str(), static_cast<Double>(num));
	}
	return str;
}

}

#endif
