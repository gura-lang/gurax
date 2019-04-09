//==============================================================================
// Basement.h
//==============================================================================
#ifndef GURAX_BASEMENT_H
#define GURAX_BASEMENT_H
#include "Frame.h"
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Basement
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Basement {
private:
	RefPtr<Frame> _pFrame;
	static Basement _basement;
public:
	// Constructor
	Basement();
	// Copy constructor/operator
	Basement(const Basement& src) = delete;
	Basement& operator=(const Basement& src) = delete;
	// Move constructor/operator
	Basement(Basement&& src) = delete;
	Basement& operator=(Basement&& src) noexcept = delete;
	// Destructor
	~Basement() = default;
public:
	void DoPrepare();
public:
	static void Prepare() { return _basement.DoPrepare(); }
	static Frame& GetFrame() { return *_basement._pFrame; }
};

}

#endif
