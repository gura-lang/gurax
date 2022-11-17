//==============================================================================
// test-Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Error)
{
	Error::Issue(ErrorType::ArgumentError, "message");
	Error::Issue(ErrorType::CodecError, "message");
	Error::Issue(ErrorType::DeclarationError, "message");
	Error::Issue(ErrorType::IndexError, "message");
	Error::Issue(ErrorType::InvalidOperation, "message");
	Error::Issue(ErrorType::SyntaxError, "message");
	Error::Issue(ErrorType::TypeError, "message");
	Error::Issue(ErrorType::ValueError, "message");
	Error::Print(*Stream::CErr);
}

}
