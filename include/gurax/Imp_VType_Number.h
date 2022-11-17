//==============================================================================
// Imp_VType_Number.h
//==============================================================================
#ifndef GURAX_IMP_VTYPE_NUMBER_H
#define GURAX_IMP_VTYPE_NUMBER_H
#include "VType_Number.h"
#include "Imp_Number.h"

namespace Gurax {

template<typename T_Num>
T_Num Value_Number::GetNumberRanged(T_Num numMin, T_Num numMax) const
{
	if ((_num < static_cast<Double>(numMin) || static_cast<Double>(numMax) < _num) && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "the number must be between %s and %s",
					 Number<Double>::ToString(static_cast<Double>(numMin)).c_str(),
					 Number<Double>::ToString(static_cast<Double>(numMax)).c_str());
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
T_Num Value_Number::GetNumberNonNeg() const
{
	if (_num < 0 && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "negative value is not acceptable");
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
T_Num Value_Number::GetNumberPos() const
{
	if ((_num < 0 || static_cast<T_Num>(_num) == 0) && !Error::IsIssued()) {
		Error::Issue(ErrorType::RangeError, "must be positive value");
	}
	return static_cast<T_Num>(_num);
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumList(const ValueList& values)
{
	NumList<T_Num> nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = GetNumberRaw(*pValue);
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumListRanged(const ValueList& values, T_Num numMin, T_Num numMax)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	Double numMinDbl = static_cast<Double>(numMin);
	Double numMaxDbl = static_cast<Double>(numMax);
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Number::GetNumberRaw(*pValue);
		if ((numRaw < numMinDbl || numMaxDbl < numRaw)) {
			Error::Issue(ErrorType::RangeError, "the number must be between %s and %s",
						 Number<Double>::ToString(numMinDbl).c_str(),
						 Number<Double>::ToString(numMaxDbl).c_str());
			break;
		}
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumListNonNeg(const ValueList& values)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Number::GetNumberRaw(*pValue);
		if (numRaw < 0) {
			Error::Issue(ErrorType::RangeError, "negative value is not acceptable");
			break;
		}
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

template<typename T_Num>
NumList<T_Num> Value_Number::GetNumListPos(const ValueList& values)
{
	NumList<T_Num> nums;
	if (Error::IsIssued()) return nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		Double numRaw = Value_Number::GetNumberRaw(*pValue);
		if (numRaw < 0 || static_cast<T_Num>(numRaw) == 0) {
			Error::Issue(ErrorType::RangeError, "must be positive value");
			break;
		}
		nums.push_back(static_cast<T_Num>(numRaw));
	}
	return nums;
}

}

#endif
