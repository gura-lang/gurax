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
protected:
	PUnitStack _punitStack;
	RefPtr<ValueStack> _pValueStack;
	RefPtr<FrameStack> _pFrameStack;
	const PUnit* _pPUnitCur;
	bool _contFlag;
	bool _resumeFlag;
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
	static Processor* Create(bool debugFlag);
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
	void DiscardValue() { Value::Delete(PopValue()); }
	void RemoveValue(size_t offset) { GetValueStack().Remove(offset); }
	void RemoveValues(size_t offset, size_t cnt) { GetValueStack().Remove(offset, cnt); }
	void SetNext(const PUnit* pPUnit) { _pPUnitCur = pPUnit; }
	void SetNext(const PUnit* pPUnit, bool contFlag) { _pPUnitCur = pPUnit; _contFlag = contFlag; }
	void ErrorDone() { _pPUnitCur = nullptr; _contFlag = false; _resumeFlag = false; }
	void Terminate() { _pPUnitCur = nullptr; _contFlag = false; _resumeFlag = false; }
	const PUnit* GetPUnitCur() const { return _pPUnitCur; }
public:
	FrameStack& GetFrameStack() { return *_pFrameStack; }
	const FrameStack& GetFrameStack() const { return *_pFrameStack; }
	void PushFrame(Frame* pFrame) { GetFrameStack().Push(pFrame); }
	Frame& PushFrame_Function(const Function& function, bool dynamicScopeFlag);
	Frame& PushFrame_Block();
	void PopFrame() { GetFrameStack().Pop(); }
	Frame& GetFrameCur() { return *GetFrameStack().GetCur(); }
	void Process(const PUnit* pPUnit) { RunLoop(pPUnit); }
	void Process(const Composer& composer) { Process(composer.GetPUnitFirst()); }
	Value* Process(const Expr& expr);
protected:
	virtual void RunLoop(const PUnit* pPUnit) = 0;
};

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
class Processor_Normal : public Processor {
protected:
	// Virtual function of Processor
	virtual void RunLoop(const PUnit* pPUnit) override;
};

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
class Processor_Debug : public Processor {
protected:
	// Virtual function of Processor
	virtual void RunLoop(const PUnit* pPUnit) override;
};

}

#endif
