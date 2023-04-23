//==============================================================================
// Number
//==============================================================================
#ifndef GURAX_NUMBER_H
#define GURAX_NUMBER_H
#include "MemoryPool.h"
#include "ListBase.h"
#include "Half.h"

namespace Gurax {

//------------------------------------------------------------------------------
// NumberBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NumberBase {
public:
	static String formatterFormat_Int;
	static String formatterFormat_Float;
public:
	static void Bootup();
};

//------------------------------------------------------------------------------
// Number
//------------------------------------------------------------------------------
template<typename T_Num>
class Number : public NumberBase {
public:
	struct LessThan {
		bool operator()(T_Num num1, T_Num num2) const { return num1 < num2; }
	};
	struct GreaterThan {
		bool operator()(T_Num num1, T_Num num2) const { return num1 > num2; }
	};
public:
	static const T_Num Max;
	static const T_Num Min;
public:
	static int GetSign(T_Num num) { return (num == 0)? 0 : (num > 0)? +1 : -1; }
	static String& ToString(String& str, T_Num num) { return str.Format(formatterFormat_Int.c_str(), num); }
	static String ToString(T_Num num) { String str; return ToString(str, num); }
};

template<> String& Number<Half>::ToString(String& str, Half num)
{
	Float numFloat = static_cast<Float>(num);
	Int64 numInt = static_cast<Int64>(numFloat);
	if (numFloat == numInt) {
		return str.Format(formatterFormat_Int.c_str(), numInt);
	} else {
		return str.Format(formatterFormat_Float.c_str(), numFloat);
	}
}

template<> String& Number<Float>::ToString(String& str, Float num)
{
	Int64 numInt = static_cast<Int64>(num);
	if (num == numInt) {
		return str.Format(formatterFormat_Int.c_str(), numInt);
	} else {
		return str.Format(formatterFormat_Float.c_str(), num);
	}
}

template<> String& Number<Double>::ToString(String& str, Double num)
{
	Int64 numInt = static_cast<Int64>(num);
	if (num == numInt) {
		return str.Format(formatterFormat_Int.c_str(), numInt);
	} else {
		return str.Format(formatterFormat_Float.c_str(), num);
	}
}

//------------------------------------------------------------------------------
// NumList
//------------------------------------------------------------------------------
template<typename T_Num>
class NumList : public ListBase<T_Num> {
public:
	NumList() {}
	NumList(size_t n) : ListBase<T_Num>(n) {}
	NumList(size_t n, T_Num num) : ListBase<T_Num>(n, num) {}
	NumList(std::initializer_list<T_Num> initList) : ListBase<T_Num>(initList) {}
public:
	NumList& Sort() { std::sort(ListBase<T_Num>::begin(), ListBase<T_Num>::end()); return *this; }
	NumList& Sort(SortOrder sortOrder);
	NumList& Unique() { ListBase<T_Num>::erase(std::unique(ListBase<T_Num>::begin(), ListBase<T_Num>::end()), ListBase<T_Num>::end()); return *this; }
	NumList& FillSeq(size_t n);
};

template<typename T_Num>
NumList<T_Num>& NumList<T_Num>::Sort(SortOrder sortOrder)
{
	//ListBase<T_Num>::SortByOrder<typename Number<T_Num>::LessThan, typename Number<T_Num>::GreaterThan>(sortOrder);
	if (sortOrder == SortOrder::Ascend) {
		typename Number<T_Num>::LessThan lessThan;
		std::sort(NumList<T_Num>::_container.begin(), NumList<T_Num>::_container.end(), lessThan);
	} else if (sortOrder == SortOrder::Descend) {
		typename Number<T_Num>::GreaterThan greaterThan;
		std::sort(NumList<T_Num>::_container.begin(), NumList<T_Num>::_container.end(), greaterThan);
	}
	return *this;
}

template<typename T_Num>
NumList<T_Num>& NumList<T_Num>::FillSeq(size_t n)
{
	ListBase<T_Num>::reserve(n);
	for (size_t i = 0; i < n ; i++) NumList<T_Num>::push_back(static_cast<T_Num>(i));
	return *this;
}

//------------------------------------------------------------------------------
// NumDeque
//------------------------------------------------------------------------------
template<typename T_Num>
class NumDeque {
public:
	using D = std::deque<T_Num>;
	D d;
};

}

#endif
