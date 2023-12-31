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
	static String formatterFormat_Int64;
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
	static int Cmp(T_Num numL, T_Num numR) { return (numL < numR)? -1 : (numL > numR)? +1 : 0; }
	static String& ToString(String& str, T_Num num) { return str.Format(formatterFormat_Int.c_str(), num); }
	static String ToString(T_Num num) { String str; return ToString(str, num); }
};

template<> String& Number<Int64>::ToString(String& str, Int64 num)
{
	return str.Format(formatterFormat_Int64.c_str(), num);
}

template<> String& Number<UInt64>::ToString(String& str, UInt64 num)
{
	return str.Format(formatterFormat_Int64.c_str(), num);
}

template<> String& Number<Half>::ToString(String& str, Half num)
{
	Float numFloat = static_cast<Float>(num);
	Int64 numInt = static_cast<Int64>(numFloat);
	if (numFloat == numInt) {
		return str.Format(formatterFormat_Int64.c_str(), numInt);
	} else {
		return str.Format(formatterFormat_Float.c_str(), numFloat);
	}
}

template<> String& Number<Float>::ToString(String& str, Float num)
{
	Int64 numInt = static_cast<Int64>(num);
	if (num == numInt) {
		return str.Format(formatterFormat_Int64.c_str(), numInt);
	} else {
		return str.Format(formatterFormat_Float.c_str(), num);
	}
}

template<> String& Number<Double>::ToString(String& str, Double num)
{
	Int64 numInt = static_cast<Int64>(num);
	if (num == numInt) {
		return str.Format(formatterFormat_Int64.c_str(), numInt);
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
	NumList(const_iterator first, const_iterator last) : ListBase<T_Num>(first, last) {}
public:
	static NumList Create(T_Num v1) {
		NumList numList; numList.reserve(1);
		numList.push_back(v1);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2) {
		NumList numList; numList.reserve(2);
		numList.push_back(v1); numList.push_back(v2);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2, T_Num v3) {
		NumList numList; numList.reserve(3);
		numList.push_back(v1); numList.push_back(v2); numList.push_back(v3);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2, T_Num v3, T_Num v4) {
		NumList numList; numList.reserve(4);
		numList.push_back(v1); numList.push_back(v2); numList.push_back(v3); numList.push_back(v4);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2, T_Num v3, T_Num v4, T_Num v5) {
		NumList numList; numList.reserve(5);
		numList.push_back(v1); numList.push_back(v2); numList.push_back(v3);
		numList.push_back(v4); numList.push_back(v5);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2, T_Num v3, T_Num v4, T_Num v5, T_Num v6) {
		NumList numList; numList.reserve(6);
		numList.push_back(v1); numList.push_back(v2); numList.push_back(v3);
		numList.push_back(v4); numList.push_back(v5); numList.push_back(v6);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2, T_Num v3, T_Num v4, T_Num v5, T_Num v6, T_Num v7) {
		NumList numList; numList.reserve(7);
		numList.push_back(v1); numList.push_back(v2); numList.push_back(v3); numList.push_back(v4);
		numList.push_back(v5); numList.push_back(v6); numList.push_back(v7);
		return numList;
	}
	static NumList Create(T_Num v1, T_Num v2, T_Num v3, T_Num v4, T_Num v5, T_Num v6, T_Num v7, T_Num v8) {
		NumList numList; numList.reserve(8);
		numList.push_back(v1); numList.push_back(v2); numList.push_back(v3); numList.push_back(v4);
		numList.push_back(v5); numList.push_back(v6); numList.push_back(v7); numList.push_back(v8);
		return numList;
	}
public:
	NumList& Sort() { std::sort(NumList::begin(), NumList::end()); return *this; }
	NumList& Sort(SortOrder sortOrder);
	NumList& Unique() { NumList::erase(std::unique(NumList::begin(), NumList::end()), NumList::end()); return *this; }
	NumList& Clear() { NumList::clear(); return *this; }
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
