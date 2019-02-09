//==============================================================================
// Context.h
//==============================================================================
#ifndef GURAX_CONTEXT_H
#define GURAX_CONTEXT_H
#include "Frame.h"
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Context
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Context {
private:
	RefPtr<ValueStack> _pValueStack;
	RefPtr<Frame> _pFrame;
	static Context _context;
public:
	// Constructor
	Context();
	// Copy constructor/operator
	Context(const Context& src) = delete;
	Context& operator=(const Context& src) = delete;
	// Move constructor/operator
	Context(Context&& src) = delete;
	Context& operator=(Context&& src) noexcept = delete;
	// Destructor
	~Context() = default;
public:
	static Context& GetGlobal() { return _context; }
	static Frame* GetFrame() { return GetGlobal()._pFrame.get(); }
	static void PushStack(Value* pValue) { GetGlobal().GetValueStack().Push(pValue); }
	static Value* PopStack() { return GetGlobal().GetValueStack().Pop(); }
	static Value* PeekStack(size_t offset) { return GetGlobal().GetValueStack().Peek(offset); }
	ValueStack& GetValueStack() { return *_pValueStack; }
};

}

#endif
