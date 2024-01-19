//==============================================================================
// Processor.h
//==============================================================================
#ifndef GURAX_PROCESSOR_H
#define GURAX_PROCESSOR_H
#include "Composer.h"
#include "ListBase.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Processor : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Processor);
public:
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
	class ExceptionInfoStack : public ListBase<ExceptionInfo*> {
	public:
		~ExceptionInfoStack() { Clear(); }
		void Clear();
		ExceptionInfo* Peek(int offset) { return *(rbegin() + offset); }
		void Push(ExceptionInfo* pExceptionInfo);
		ExceptionInfo* Pop();
		void Shrink(size_t cnt);
		void ShrinkUntilNull();
		void Print() const;
	};
protected:
	PUnitStack _punitStack;
	RefPtr<ValueStack> _pValueStack;
	RefPtr<FrameStack> _pFrameStack;
	ExceptionInfoStack _exceptionInfoStack;
	const PUnit* _pPUnitCur;
	bool _contFlag;
	bool _resumeFlag;
	Event _event;
public:
	// Constructor
	Processor(Frame* pFrame);
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
	void ReplaceValue(size_t offset, Value* pValue) { GetValueStack().Replace(offset, pValue); }
	void DiscardValue() { Value::Delete(PopValue()); }
	void RemoveValue(size_t offset) { GetValueStack().Remove(offset); }
	void RemoveValues(size_t offset, size_t cnt) { GetValueStack().Remove(offset, cnt); }
public:
	FrameStack& GetFrameStack() { return *_pFrameStack; }
	const FrameStack& GetFrameStack() const { return *_pFrameStack; }
	void ClearFrameStack() { GetFrameStack().Clear(); }
	Frame& PushFrame(Frame* pFrame) { GetFrameStack().Push(pFrame); return *pFrame; }
	template<typename T_Frame> Frame* CreateFrame() { return new T_Frame(GetFrameCur().Reference()); }
	template<typename T_Frame> Frame& PushFrame() { return PushFrame(CreateFrame<T_Frame>()); }
	Frame& BeginFunction(const Function& function, bool dynamicScopeFlag);
	void EndFunction(bool discardFlag);
	void PopFrame() { GetFrameStack().Pop(); }
	Frame& GetFrameCur() { return *GetFrameStack().GetCur(); }
public:
	ExceptionInfoStack& GetExceptionInfoStack() { return _exceptionInfoStack; }
	const ExceptionInfoStack& GetExceptionInfoStack() const { return _exceptionInfoStack; }
	void TryBlockBegin(const PUnit* pPUnitCatch) {
		GetExceptionInfoStack().Push(new ExceptionInfo(*this, pPUnitCatch));
	}
	ExceptionInfo* TryBlockEnd() { return GetExceptionInfoStack().Pop(); }
public:
	void SetPUnitCur(const PUnit* pPUnitCur) { _pPUnitCur = pPUnitCur; }
	const PUnit* GetPUnitCur() const { return _pPUnitCur; }
	void ExitRunLoop(const PUnit* pPUnitCur = nullptr) {
		_pPUnitCur = pPUnitCur; _contFlag = false, _resumeFlag = true;
	}
	void ErrorDone() { _contFlag = _resumeFlag = false; }
	void Terminate() { _contFlag = _resumeFlag = false; }
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
	bool IsEventNone() const { return _event == Event::None; }
	bool IsEventBreak() const { return _event == Event::Break; }
	bool IsEventContinue() const { return _event == Event::Continue; }
	static bool IsEventNone(Event event) { return event == Event::None; }
	static bool IsEventBreak(Event event) { return event == Event::Break; }
	static bool IsEventContinue(Event event) { return event == Event::Continue; }
public:
	Value* ProcessPUnit(const PUnit* pPUnit, const PUnit* pPUnitSentinel = nullptr);
	virtual void RunLoop(const PUnit* pPUnit, const PUnit* pPUnitSentinel) = 0;
	virtual Processor* CreateSubProcessor() = 0;
public:
	void Print() const;
};

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Processor_Normal : public Processor {
public:
	// Constructor
	Processor_Normal(Frame* pFrame) : Processor(pFrame) {}
protected:
	// Virtual function of Processor
	virtual void RunLoop(const PUnit* pPUnit, const PUnit* pPunitSentinel) override;
	virtual Processor* CreateSubProcessor() override;
};

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Processor_Debug : public Processor {
private:
	int _nestLevel;
public:
	// Constructor
	Processor_Debug(Frame* pFrame, int nestLevel = -1) : Processor(pFrame), _nestLevel(nestLevel) {}
protected:
	// Virtual function of Processor
	virtual void RunLoop(const PUnit* pPUnit, const PUnit* pPunitSentinel) override;
	virtual Processor* CreateSubProcessor() override;
};

}

#endif
