//==============================================================================
// Stream.h
//==============================================================================
#ifndef GURAX_STREAM_H
#define GURAX_STREAM_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stream);
public:
	// Constructor
	Stream() {}
	// Copy constructor/operator
	Stream(const Stream& src) = delete;
	Stream& operator=(const Stream& src) = delete;
	// Move constructor/operator
	Stream(Stream&& src) = delete;
	Stream& operator=(Stream&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Stream() = default;
};

}

#endif
