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
	ArgSlot* _pArgSlot;
public:
	// Constructor
	ArgFeeder(Argument& argument) : _argument(argument), _pArgSlot(argument.GetArgSlotFirst()) {
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
	bool FeedValue(Frame& frame, Value* pValue);
	bool FeedValues(Frame& frame, const ValueList& values);
	bool FeedValues(Frame& frame) { return true; }
	template<typename T_Head, typename... T_Tail>
	bool FeedValues(Frame& frame, T_Head pValue, T_Tail... pValueTail) {
		return FeedValue(frame, pValue) && FeedValues(frame, pValueTail...);
	}
};

}

#endif
