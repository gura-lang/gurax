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
	Frame* pFrame = new Frame_Scope(function.LockFrameOuter());
	PushFrame(pFrame);
	return *pFrame;
}

Value* Processor::ProcessExpr(const Expr& expr)
{
	if (!expr.GetPUnitFirst()) return Value::nil();
	ProcessPUnit(expr.GetPUnitFirst());
	return Error::IsIssued()? Value::nil() : PopValue();
}

void Processor::ClearError()
{
	Error::Clear();
	_contFlag = true;
	_resumeFlag = true;
	_event = Event::None;
}

void Processor::PrepareExceptionHandling()
{
	GetExceptionInfoStack().Push(nullptr);
}

bool Processor::DoExceptionHandling()
{
	if (Error::GetLastError()) {
		std::unique_ptr<ExceptionInfo> pExceptionInfo(GetExceptionInfoStack().Pop());
		if (pExceptionInfo) {
			Error::ClearIssuedFlag();
			_contFlag = _resumeFlag = true;
			pExceptionInfo->UpdateProcessor(*this);
			return true;
		} else {
			Error::SetIssuedFlag();
			return false;
		}
	} else {
		GetExceptionInfoStack().ShrinkUntilNull();
		return false;
	}
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
	//::printf("PUnitStack: %zu->%zu, ", processor.GetPUnitStack().size(), _sizePUnitStack);
	//::printf("ValueStack: %zu->%zu, ", processor.GetValueStack().size(), _sizeValueStack);
	//::printf("FrameStack: %zu->%zu\n", processor.GetFrameStack().size(), _sizeFrameStack);
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

void Processor::ExceptionInfoStack::ShrinkUntilNull()
{
	//while (!empty()) {
	for (;;) {
		std::unique_ptr<ExceptionInfo> pExceptionInfo(Pop());
		if (!pExceptionInfo) break;
	}
}

void Processor::ExceptionInfoStack::Print() const
{
	Stream& stream = *Stream::COut;
	stream.Printf("[");
	for (auto ppExceptionInfo = begin(); ppExceptionInfo != end(); ppExceptionInfo++) {
		if (ppExceptionInfo != begin()) stream.Printf(", ");
		stream.Printf("%p", *ppExceptionInfo);
	}
	stream.Printf("]\n");
}

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
void Processor_Normal::RunLoop(const PUnit* pPUnit)
{
	_pPUnitNext = pPUnit;
	if (!_pPUnitNext) return;
	PrepareExceptionHandling();
	if (_pPUnitNext->IsBeginSequence()) {
		const PUnit* pPUnitSentinel = _pPUnitNext->GetPUnitSentinel();
		_pPUnitNext = _pPUnitNext->GetPUnitCont();	// skip BeginSequence/ArgSlot/ArgSlotNamed
		if (pPUnitSentinel->IsEndSequence()) {
			do {
				while (_contFlag) {
					_pPUnitNext->Exec(*this);
				}
				if (!DoExceptionHandling()) break;
			} while (_contFlag);
		} else {
			do {
				while (_contFlag && _pPUnitNext != pPUnitSentinel) {
					_pPUnitNext->Exec(*this);
				}
				if (!DoExceptionHandling()) break;
			} while (_contFlag && _pPUnitNext != pPUnitSentinel);
		}
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		do {
			while (_contFlag) {
				_pPUnitNext->Exec(*this);
			}
			if (!DoExceptionHandling()) break;
		} while (_contFlag);
	}
	_contFlag = _resumeFlag;
}

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
void Processor_Debug::RunLoop(const PUnit* pPUnit)
{
	auto PrintPUnit = [](Stream& stream, int nestLevel, const PUnit* pPUnit) {
		String seqIdStr = pPUnit->MakeSeqIdString();
		stream.Printf("%*s%s %s\n", nestLevel * 2, "", seqIdStr.c_str(), pPUnit->ToString().c_str());
		return seqIdStr.size();
	};
	auto PrintStack = [this](Stream& stream, int nestLevel, size_t wdSeqId) {
		stream.Printf("%*s%*s %s\n", nestLevel * 2, "", wdSeqId, "",
					  GetValueStack().ToString(StringStyle().Digest()).c_str());
	};
	_pPUnitNext = pPUnit;
	if (!_pPUnitNext) return;
	Stream& stream = *Stream::COut;
	const PUnit* pPUnitSentinel = nullptr;
	_nestLevel++;
	stream.Printf("%*s---- Processor Begin at %s ----\n",
				  _nestLevel * 2, "", _pPUnitNext->MakeSeqIdString().c_str());
	PrepareExceptionHandling();
	size_t wdSeqId = 0;
	if (_pPUnitNext->IsBeginSequence()) {
		pPUnitSentinel = _pPUnitNext->GetPUnitSentinel();
		_pPUnitNext = _pPUnitNext->GetPUnitCont();	// skip BeginSequence/ArgSlot/ArgSlotNamed
		if (pPUnitSentinel->IsEndSequence()) pPUnitSentinel = nullptr;
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		wdSeqId = PrintPUnit(stream, _nestLevel, _pPUnitNext);
		_pPUnitNext->Exec(*this);
	}
	do {
		while (_contFlag && _pPUnitNext != pPUnitSentinel) {
			PrintStack(stream, _nestLevel, wdSeqId);
			wdSeqId = PrintPUnit(stream, _nestLevel, _pPUnitNext);
			_pPUnitNext->Exec(*this);
		}
		if (!DoExceptionHandling()) break;
	} while (_contFlag && _pPUnitNext != pPUnitSentinel);
	_contFlag = _resumeFlag;
	stream.Printf("%*s---- Processor End ----\n", _nestLevel * 2, "");
	_nestLevel--;
}

}
