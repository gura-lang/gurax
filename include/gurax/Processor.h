//==============================================================================
// Processor.h
//==============================================================================
#ifndef GURAX_PROCESSOR_H
#define GURAX_PROCESSOR_H
#include "Composer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Processor : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Processor);
private:
	PUnitStack _punitStack;
	RefPtr<ValueStack> _pValueStack;
	RefPtr<FrameStack> _pFrameStack;
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
	static Processor* Normal();
	static Processor* Debug();
public:
	PUnitStack& GetPUnitStack() { return _punitStack; }
	const PUnitStack& GetPUnitStack() const { return _punitStack; }
	bool IsPUnitStackEmpty() const { return GetPUnitStack().empty(); }
	void PushPUnit(const PUnit* pPUnit) { GetPUnitStack().Push(pPUnit); }
	const PUnit* PopPUnit() { return GetPUnitStack().Pop(); }
	const PUnit* PeekPUnit(size_t offset) { return GetPUnitStack().Peek(offset); }
public:
	ValueStack& GetValueStack() { return *_pValueStack; }
	const ValueStack& GetValueStack() const { return *_pValueStack; }
	bool IsValueStackEmpty() const { return GetValueStack().empty(); }
	void PushValue(Value* pValue) { GetValueStack().Push(pValue); }
	Value* PopValue() { return GetValueStack().Pop(); }
	Value* PeekValue(size_t offset) { return GetValueStack().Peek(offset); }
	void PopValueToDiscard() { Value::Delete(PopValue()); }
	void RemoveValue(size_t offset) { GetValueStack().Remove(offset); }
public:
	FrameStack& GetFrameStack() { return *_pFrameStack; }
	const FrameStack& GetFrameStack() const { return *_pFrameStack; }
	void PushFrame(Frame* pFrame) { GetFrameStack().Push(pFrame); }
	Frame& PushFrame_Function() {
		Frame* pFrame = new Frame_Function(GetFrameCur().GetFrameOuter()->Reference());
		PushFrame(pFrame);
		return *pFrame;
	}
	Frame& PushFrame_Block() {
		Frame* pFrame = new Frame_Block(GetFrameCur().GetFrameOuter()->Reference());
		PushFrame(pFrame);
		return *pFrame;
	}
	void PopFrame() { GetFrameStack().Pop(); }
	Frame& GetFrameCur() { return *GetFrameStack().GetCur(); }
public:
	void Call(const PUnit* pPUnit, Argument& argument);
	void Run(const Composer& composer) { Run(composer.GetPUnitFirst()); }
public:
	virtual void Run(const PUnit* pPUnit) = 0;
};

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
class Processor_Normal : public Processor {
public:
	// Virtual function of Processor
	virtual void Run(const PUnit* pPUnit) override;
};

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
class Processor_Debug : public Processor {
public:
	// Virtual function of Processor
	virtual void Run(const PUnit* pPUnit) override;
};

}

#endif
