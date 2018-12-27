//==============================================================================
// Frame.h
//==============================================================================
#ifndef GURAX_FRAME_H
#define GURAX_FRAME_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame);
public:
	// Constructor
	Frame() {}
	// Copy constructor/operator
	Frame(const Frame& src) = delete;
	Frame& operator=(const Frame& src) = delete;
	// Move constructor/operator
	Frame(Frame&& src) = delete;
	Frame& operator=(Frame&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Frame() = default;
};

}

#endif
