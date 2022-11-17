//==============================================================================
// ValueDeque.h
//==============================================================================
#ifndef GURAX_VALUEDEQUE_H
#define GURAX_VALUEDEQUE_H
#include "Value.h"

namespace Gurax {

class Random;

//------------------------------------------------------------------------------
// ValueDeque
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueDeque : public std::deque<Value*> {
public:
	using std::deque<Value*>::deque;
public:
	static const ValueDeque Empty;
public:
	void IncCntRefOfEach() const;
	void DeleteEach();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueDeque& valueDeque) const { return this == &valueDeque; }
	bool IsEqualTo(const ValueDeque& valueDeque) const { return IsIdentical(valueDeque); }
	bool IsLessThan(const ValueDeque& valueDeque) const { return this < &valueDeque; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
