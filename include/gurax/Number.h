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
class NumList : public std::vector<T_Num>
{
public:
	using std::vector<T_Num>::vector;
public:
	NumList& Sort() { std::sort(this->begin(), this->end()); return *this; }
	NumList& Sort(SortOrder sortOrder);
	NumList& Unique() { this->erase(std::unique(this->begin(), this->end()), this->end()); return *this; }
	NumList& FillSeq(size_t n);
};

template<typename T_Num>
NumList<T_Num>& NumList<T_Num>::Sort(SortOrder sortOrder)
{
	SortListByOrder<NumList, typename Number<T_Num>::LessThan, typename Number<T_Num>::GreaterThan>(
		*this, sortOrder);
	return *this;
}

template<typename T_Num>
NumList<T_Num>& NumList<T_Num>::FillSeq(size_t n)
{
	this->reserve(n);
	for (size_t i = 0; i < n ; i++) this->push_back(static_cast<T_Num>(i));
	return *this;
}

//------------------------------------------------------------------------------
// NumDeque
//------------------------------------------------------------------------------
template<typename T_Num>
class NumDeque : public std::deque<T_Num>
{
public:
	using std::deque<T_Num>::deque;
};

}

#endif
