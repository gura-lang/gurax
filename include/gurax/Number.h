//==============================================================================
// Number
//==============================================================================
#ifndef GURAX_NUMBER_H
#define GURAX_NUMBER_H
#include "MemoryPool.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Number
//------------------------------------------------------------------------------
template<typename T_Num>
class Number {
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
};

//------------------------------------------------------------------------------
// NumList
//------------------------------------------------------------------------------
template<typename T_Num>
class NumList : public std::vector<T_Num, Allocator<T_Num> >
{
public:
	using std::vector<T_Num, Allocator<T_Num> >::vector;
public:
	NumList& Sort() { std::sort(this->begin(), this->end()); return *this; }
	NumList& Sort(SortOrder sortOrder) {
		SortListByOrder<NumList, typename Number<T_Num>::LessThan, typename Number<T_Num>::GreaterThan>(
			*this, sortOrder);
		return *this;
	}
	NumList& Unique() { this->erase(std::unique(this->begin(), this->end()), this->end()); return *this; }
};

//------------------------------------------------------------------------------
// NumDeque
//------------------------------------------------------------------------------
template<typename T_Num>
class NumDeque : public std::deque<T_Num, Allocator<T_Num> >
{
public:
	using std::deque<T_Num, Allocator<T_Num> >::vector;
};

}

#endif
