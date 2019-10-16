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
class ArgFeeder {
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
};

}

#endif
