//==============================================================================
// BasicStatement.h
//==============================================================================
#ifndef GURAX_BASICSTATEMENT_H
#define GURAX_BASICSTATEMENT_H
#include "Function.h"

namespace Gurax {

class GURAX_DLLDECLARE BasicStatement {
public:
	static void Prepare(Processor& processor, Frame& frame);
};

}

#endif
