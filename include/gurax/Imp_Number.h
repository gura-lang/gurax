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
	return String().Printf(Basement::Inst.GetFormatForNumber(), static_cast<Double>(num));
}

}

#endif
