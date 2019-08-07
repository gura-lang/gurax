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
public:
	enum class Event { None, Break, Continue };
	class ExceptionInfo {
	private:
		size_t _sizePUnitStack;
		size_t _sizeValueStack;
		size_t _sizeFrameStack;
		const PUnit* _pPUnitCatch;
	public:
		// Constructor
		ExceptionInfo(const Processor& processor, const PUnit* pPUnitCatch);
		// Copy constructor/operator
		ExceptionInfo(const ExceptionInfo& src) = delete;
		ExceptionInfo& operator=(const ExceptionInfo& src) = delete;
		// Move constructor/operator
		ExceptionInfo(ExceptionInfo&& src) = delete;
		ExceptionInfo& operator=(ExceptionInfo&& src) noexcept = delete;
		// Destructor
		~ExceptionInfo() = default;
	public:
		void UpdateProcessor(Processor& processor);
	};
	class ExceptionInfoStack : public std::vector<ExceptionInfo*> {
	public:
		~ExceptionInfoStack() { Clear(); }
		void Clear();
		ExceptionInfo* Peek(int offset) { return *(rbegin() + offset); }
		void Push(ExceptionInfo* pExceptionInfo) { push_back(pExceptionInfo); }
		ExceptionInfo* Pop() {
			if (empty()) return nullptr;
			ExceptionInfo* pExceptionInfo = back(); pop_back(); return pExceptionInfo;
		}
		void Shrink(size_t cnt);
		void ShrinkUntilNull();
		void Print() const;
	};
protected:
	PUnitStack _punitStack;
	RefPtr<ValueStack> _pValueStack;
	RefPtr<FrameStack> _pFrameStack;
	ExceptionInfoStack _exceptionInfoStack;
	const Expr* _pExprCur;
	const PUnit* _pPUnitNext;
	bool _contFlag;
	bool _resumeFlag;
	Event _event;
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
	void ClearValueStack() { GetValueStack().Clear(); }
	void PushValue(Value* pValue) { GetValueStack().Push(pValue); }
	Value* PopValue() { return GetValueStack().Pop(); }
	Value& PeekValue(size_t offset) { return *GetValueStack().Peek(offset); }
	void DiscardValue() { Value::Delete(PopValue()); }
	void RemoveValue(size_t offset) { GetValueStack().Remove(offset); }
	void RemoveValues(size_t offset, size_t cnt) { GetValueStack().Remove(offset, cnt); }
public:
	FrameStack& GetFrameStack() { return *_pFrameStack; }
	const FrameStack& GetFrameStack() const { return *_pFrameStack; }
	void ClearFrameStack() { GetFrameStack().Clear(); }
	void PushFrame(Frame* pFrame) { GetFrameStack().Push(pFrame); }
	template<typename T_Frame> Frame& PushFrame();
	Frame& PushFrameForFunction(const Function& function, bool dynamicScopeFlag);
	void PopFrame() { GetFrameStack().Pop(); }
	Frame& GetFrameCur() { return *GetFrameStack().GetCur(); }
public:
	ExceptionInfoStack& GetExceptionInfoStack() { return _exceptionInfoStack; }
	const ExceptionInfoStack& GetExceptionInfoStack() const { return _exceptionInfoStack; }
	void BeginTryBlock(const PUnit* pPUnitCatch) {
		GetExceptionInfoStack().Push(new ExceptionInfo(*this, pPUnitCatch));
	}
	ExceptionInfo* EndTryBlock() { return GetExceptionInfoStack().Pop(); }
public:
	Value* EvalExpr(const Expr& expr, Argument& argument, Event* pEvent = nullptr);
public:
	void SetExprCur(const Expr* pExpr) { _pExprCur = pExpr; }
	const Expr& GetExprCur() const { return *_pExprCur; }
	void SetPUnitNext(const PUnit* pPUnitNext) { _pPUnitNext = pPUnitNext; }
	const PUnit* GetPUnitNext() const { return _pPUnitNext; }
	void ExitRunLoop(const PUnit* pPUnitNext = nullptr) {
		_pPUnitNext = pPUnitNext; _contFlag = false, _resumeFlag = true;
	}
	void ErrorDone() { _pPUnitNext = nullptr; _contFlag = false; _resumeFlag = false; }
	void Terminate() { _pPUnitNext = nullptr; _contFlag = false; _resumeFlag = false; }
	void ClearError();
	void PrepareExceptionHandling();
	bool DoExceptionHandling();
	bool GetContFlag() const { return _contFlag; }
	bool GetResumeFlag() const { return _resumeFlag; }
public:
	Event GetEvent() const { return _event; }
	void ClearEvent() { _event = Event::None; }
	void SetEventBreak() { _event = Event::Break; }
	void SetEventContinue() { _event = Event::Continue; }
	bool IsEventBreak() const { return _event == Event::Break; }
	bool IsEventContinue() const { return _event == Event::Continue; }
public:
	Value* ProcessPUnit(const PUnit* pPUnit);
	Value* ProcessExpr(const Expr& expr) { return ProcessPUnit(expr.GetPUnitFirst()); }
public:
	void Print() const;
protected:
	virtual void RunLoop(const PUnit* pPUnit) = 0;
};

template<typename T_Frame>
Frame& Processor::PushFrame()
{
	Frame* pFrame = new T_Frame(GetFrameCur().Reference());
	PushFrame(pFrame);
	return *pFrame;
}

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
private:
	int _nestLevel;
public:
	// Constructor
	Processor_Debug() : _nestLevel(-1) {}
protected:
	// Virtual function of Processor
	virtual void RunLoop(const PUnit* pPUnit) override;
};

}

#endif
