//==============================================================================
// ArgFeeder.h
//==============================================================================
#ifndef GURAX_ARGFEEDER_H
#define GURAX_ARGFEEDER_H
#include "Argument.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgFeeder
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgFeeder {
private:
	Argument& _argument;
	Frame& _frame;
	ArgSlot* _pArgSlot;
public:
	// Constructor
	ArgFeeder(Argument& argument, Frame& frame) :
			_argument(argument), _frame(frame), _pArgSlot(argument.GetArgSlotFirst()) {
		argument.ResetAllValues();
	}
	// Copy constructor/operator
	ArgFeeder(const ArgFeeder& src) = delete;
	ArgFeeder& operator=(const ArgFeeder& src) = delete;
	// Move constructor/operator
	ArgFeeder(ArgFeeder&& src) = delete;
	ArgFeeder& operator=(ArgFeeder&& src) noexcept = delete;
	// Destructor
	~ArgFeeder() = default;
public:
	bool IsValid() const { return _pArgSlot != nullptr; }
public:
	bool FeedValue(Value* pValue);
	bool FeedValues(const ValueList& values);
	bool FeedValues() { return true; }
	template<typename T_Head, typename... T_Tail>
	bool FeedValues(T_Head pValue, T_Tail... pValueTail) {
		return FeedValue(pValue) && FeedValues(pValueTail...);
	}
};

}

#endif
