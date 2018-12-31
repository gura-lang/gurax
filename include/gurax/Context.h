//==============================================================================
// Context.h
//==============================================================================
#ifndef GURAX_CONTEXT_H
#define GURAX_CONTEXT_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Context
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Context {
private:
	RefPtr<ObjectStack> _pObjectStack;
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
	static void PushStack(Object* pObject) { GetGlobal().GetObjectStack().Push(pObject); }
	static Object* PopStack() { return GetGlobal().GetObjectStack().Pop(); }
	static Object* PeekStack(size_t offset) { return GetGlobal().GetObjectStack().Peek(offset); }
	ObjectStack& GetObjectStack() { return *_pObjectStack; }
};

}

#endif
