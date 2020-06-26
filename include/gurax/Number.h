//==============================================================================
// Number
//==============================================================================
#ifndef GURAX_NUMBER_H
#define GURAX_NUMBER_H
#include "MemoryPool.h"

namespace Gurax {

//------------------------------------------------------------------------------
// NumberBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NumberBase {
protected:
	static String _formatterFormat_Int;
	static String _formatterFormat_Float;
public:
	static void SetFormatterFormat_Int(String formatterFormat) {
		_formatterFormat_Int = formatterFormat;
	}
	static void SetFormatterFormat_Float(String formatterFormat) {
		_formatterFormat_Float = formatterFormat;
	}
	static const char* GetFormatterFormat_Int() {
		return _formatterFormat_Int.c_str();
	}
	static const char* GetFormatterFormat_Float() {
		return _formatterFormat_Float.c_str();
	}
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
	static String ToString(T_Num num);
};

//------------------------------------------------------------------------------
// NumList
//------------------------------------------------------------------------------
template<typename T_Num>
class NumList {
public:
	using V = std::vector<T_Num>;
	V v;
public:
	NumList() {}
	NumList(size_t n) : v(n) {}
	NumList(size_t n, T_Num num) : v(n, num) {}
	NumList(std::initializer_list<T_Num> initList) : v(initList) {}
public:
	NumList& Sort() { std::sort(v.begin(), v.end()); return *this; }
	NumList& Sort(SortOrder sortOrder);
	NumList& Unique() { v.erase(std::unique(v.begin(), v.end()), v.end()); return *this; }
	NumList& FillSeq(size_t n);
};

template<typename T_Num>
NumList<T_Num>& NumList<T_Num>::Sort(SortOrder sortOrder)
{
	SortCollectionByOrder<NumList::V, typename Number<T_Num>::LessThan, typename Number<T_Num>::GreaterThan>(
		v, sortOrder);
	return *this;
}

template<typename T_Num>
NumList<T_Num>& NumList<T_Num>::FillSeq(size_t n)
{
	v.reserve(n);
	for (size_t i = 0; i < n ; i++) v.push_back(static_cast<T_Num>(i));
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
