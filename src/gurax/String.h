//==============================================================================
// String.h
//==============================================================================
#ifndef GURAX_STRING_H
#define GURAX_STRING_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
class String : public std::string {
public:
	using std::string::string;	// inherits constructors
};

}

#endif
