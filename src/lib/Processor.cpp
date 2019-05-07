//==============================================================================
// Processor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
Processor::Processor() :
	_pValueStack(new ValueStack()), _pFrameStack(new FrameStack()),
	_pPUnitNext(nullptr), _contFlag(true), _resumeFlag(true), _event(Event::None)
{
	GetPUnitStack().reserve(1024);
	GetValueStack().reserve(1024);
	GetFrameStack().reserve(1024);
	PushFrame(Basement::Inst.GetFrame().Reference());
	//PushPUnit(nullptr);
}

Processor* Processor::Create(bool debugFlag)
{
	return debugFlag?
		dynamic_cast<Processor*>(new Processor_Debug()) :
		dynamic_cast<Processor*>(new Processor_Normal());
}

Frame& Processor::PushFrameForFunction(const Function& function, bool dynamicScopeFlag)
{
	if (dynamicScopeFlag) return PushFrame<Frame_Scope>();
	Frame* pFrame = new Frame_Scope(function.LockFrameParent());
	PushFrame(pFrame);
	return *pFrame;
}

Value* Processor::ProcessExpr(const Expr& expr)
{
	if (!expr.GetPUnitFirst()) return Value::nil();
	ProcessPUnit(expr.GetPUnitFirst());
	return Error::IsIssued()? Value::nil() : PopValue();
}

void Processor::Print() const
{
	Stream& stream = *Stream::COut;
	stream.Printf("PUnitStack: %zupcs\n", GetPUnitStack().size());
	stream.Printf("ValueStack: %zupcs\n", GetValueStack().size());
	stream.Printf("FrameStack: %zupcs\n", GetFrameStack().size());
	stream.Printf("PUnitNext: %s\n", GetPUnitNext()? GetPUnitNext()->ToString().c_str() : "null");
	stream.Printf("contFlag=%s, resumeFlag=%s, event=%s\n",
				  GetContFlag()? "true" : "false", GetResumeFlag()? "true" : "false",
				  IsEventBreak()? "Break" : IsEventContinue()? "Continue" : "None");
}

//------------------------------------------------------------------------------
// Processor::ExceptionInfo
//------------------------------------------------------------------------------
Processor::ExceptionInfo::ExceptionInfo(const Processor& processor, const PUnit* pPUnitCatch) :
	_sizePUnitStack(processor.GetPUnitStack().size()),
	_sizeValueStack(processor.GetValueStack().size()),
	_sizeFrameStack(processor.GetFrameStack().size()),
	_pPUnitCatch(pPUnitCatch)
{}

void Processor::ExceptionInfo::UpdateProcessor(Processor& processor)
{
	processor.GetPUnitStack().Shrink(_sizePUnitStack);
	processor.GetValueStack().Shrink(_sizeValueStack);
	processor.GetFrameStack().Shrink(_sizeFrameStack);
	processor.SetPUnitNext(_pPUnitCatch);
}

//------------------------------------------------------------------------------
// Processor::ExceptionInfoStack
//------------------------------------------------------------------------------
void Processor::ExceptionInfoStack::Clear()
{
	for (ExceptionInfo* pExceptionInfo : *this) delete pExceptionInfo;
	clear();
}

void Processor::ExceptionInfoStack::Shrink(size_t cnt)
{
	if (cnt >= size()) return;
	auto ppExceptionInfoEnd = rbegin() + size() - cnt;
	for (auto ppExceptionInfo = rbegin(); ppExceptionInfo != ppExceptionInfoEnd; ppExceptionInfo++) {
		delete *ppExceptionInfo;
	}
	erase(begin() + cnt, end());
}

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
void Processor_Normal::RunLoop(const PUnit* pPUnit)
{
	_pPUnitNext = pPUnit;
	if (!_pPUnitNext) return;
	if (_pPUnitNext->IsBeginSequence()) {
		const PUnit* pPUnitSentinel = _pPUnitNext->GetPUnitSentinel();
		_pPUnitNext = _pPUnitNext->GetPUnitCont();	// skip PUnit_BeginSequence
		if (pPUnitSentinel->IsEndSequence()) {
			do {
				while (_contFlag) {
					_pPUnitNext->Exec(*this);
				}
				
			} while (_contFlag);
		} else {
			do {
				while (_contFlag && _pPUnitNext != pPUnitSentinel) {
					_pPUnitNext->Exec(*this);
				}
				
			} while (_contFlag && _pPUnitNext != pPUnitSentinel);
		}
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		do {
			while (_contFlag) {
				_pPUnitNext->Exec(*this);
			}
			
		} while (_contFlag);
	}
	_contFlag = _resumeFlag;
}

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
void Processor_Debug::RunLoop(const PUnit* pPUnit)
{
	auto PrintPUnit = [](Stream& stream, const PUnit* pPUnit) {
		stream.Printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
	};
	auto PrintStack = [this](Stream& stream) {
		stream.Printf("%s\n", GetValueStack().ToString(StringStyle().Digest()).c_str());
	};
	_pPUnitNext = pPUnit;
	if (!_pPUnitNext) return;
	Stream& stream = *Stream::COut;
	const PUnit* pPUnitSentinel = nullptr;
	stream.Printf("---- Processor Begin ----\n");
	if (_pPUnitNext->IsBeginSequence()) {
		pPUnitSentinel = _pPUnitNext->GetPUnitSentinel();
		_pPUnitNext = _pPUnitNext->GetPUnitCont();	// skip PUnit_BeginSequence
		if (pPUnitSentinel->IsEndSequence()) pPUnitSentinel = nullptr;
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		PrintPUnit(stream, _pPUnitNext);
		_pPUnitNext->Exec(*this);
	}
	do {
		while (_contFlag && _pPUnitNext != pPUnitSentinel) {
			PrintStack(stream);
			PrintPUnit(stream, _pPUnitNext);
			_pPUnitNext->Exec(*this);
		}
		
	} while (_contFlag && _pPUnitNext != pPUnitSentinel);
	_contFlag = _resumeFlag;
	stream.Printf("---- Processor End ----\n");
}

}
