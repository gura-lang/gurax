//==============================================================================
// Processor.h
//==============================================================================
#ifndef GURAX_PROCESSOR_H
#define GURAX_PROCESSOR_H
#include "PUnit.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Processor {
private:
	PUnitStack _punitStack;
	RefPtr<ValueStack> _pValueStack;
	RefPtr<Frame> _pFrame;
public:
	// Constructor
	Processor();
	// Copy constructor/operator
	Processor(const Processor& src) = delete;
	Processor& operator=(const Processor& src) = delete;
	// Move constructor/operator
	Processor(Processor&& src) = delete;
	Processor& operator=(Processor&& src) noexcept = delete;
	// Destructor
	virtual ~Processor() = default;
public:
	PUnitStack& GetPUnitStack() { return _punitStack; }
	const PUnitStack& GetPUnitStack() const { return _punitStack; }
	bool IsPUnitStackEmpty() const { return GetPUnitStack().empty(); }
	void PushPUnit(const PUnit* pPUnit) { GetPUnitStack().Push(pPUnit); }
	const PUnit* PopPUnit() { return GetPUnitStack().Pop(); }
	const PUnit* PeekPUnit(size_t offset) { return GetPUnitStack().Peek(offset); }
	ValueStack& GetValueStack() { return *_pValueStack; }
	const ValueStack& GetValueStack() const { return *_pValueStack; }
	bool IsValueStackEmpty() const { return GetValueStack().empty(); }
	void PushValue(Value* pValue) { GetValueStack().Push(pValue); }
	Value* PopValue() { return GetValueStack().Pop(); }
	Value* PeekValue(size_t offset) { return GetValueStack().Peek(offset); }
	Frame& GetFrame() { return *_pFrame; }
	void Run(const PUnit* pPUnit);
};

}

#endif
