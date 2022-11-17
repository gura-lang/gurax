//==============================================================================
// ThreadCustom.h
//==============================================================================
#ifndef GURAX_THREADCUSTOM_H
#define GURAX_THREADCUSTOM_H
#include "Function.h"
#include "OAL.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ThreadCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ThreadCustom : public OAL::Thread {
protected:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Argument> _pArgument;
public:
	ThreadCustom(Processor& processor, Function* pFunction, Argument* pArgument);
	virtual void Run() override;
};

}

#endif
