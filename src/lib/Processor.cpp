//==============================================================================
// Processor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
Processor::Processor(Frame* pFrame) :
	_pValueStack(new ValueStack()), _pFrameStack(new FrameStack()),
	_pPUnitCur(nullptr), _contFlag(true), _resumeFlag(true), _event(Event::None)
{
	GetPUnitStack().reserve(1024);
	GetValueStack().reserve(1024);
	GetFrameStack().reserve(1024);
	PushFrame(pFrame);
}

Processor* Processor::Create(bool debugFlag)
{
	RefPtr<Frame> pFrame(Basement::Inst.GetFrame().Reference());
	if (debugFlag) {
		return new Processor_Debug(pFrame.release());
	} else {
		return new Processor_Normal(pFrame.release());
	}
}

Frame& Processor::BeginFunction(const Function& function, bool dynamicScopeFlag)
{
	_pValueStack->push_back(nullptr);
	return dynamicScopeFlag?
		PushFrame<Frame_Function>() :
		PushFrame(new Frame_Function(function.LockFrameOuter()));
}

void Processor::EndFunction(bool discardFlag)
{
	for (;;) {
		bool doneFlag = _pFrameStack->GetCur()->IsFrameOfFunction();
		_pFrameStack->Pop();
		if (doneFlag) break;
	}
#if 1
	RefPtr<Value> pValueRtn(_pValueStack->Pop());
	if (pValueRtn) {
		for (;;) {
			RefPtr<Value> pValue(_pValueStack->Pop());
			if (!pValue) break;
		}
		if (!discardFlag) _pValueStack->push_back(pValueRtn.release());
	}
#endif
}

Value* Processor::ProcessPUnit(const PUnit* pPUnit, const PUnit* pPUnitSentinel)
{
	if (!pPUnit) return Value::nil();
	RunLoop(pPUnit, pPUnitSentinel);
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
		if (Error::IsIssued() && GetPUnitCur()) {
			Error::GetErrorOwner().SetExpr(*GetPUnitCur()->GetExprSrc());
		}
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
	stream.Printf("PUnitCur: %s\n", GetPUnitCur()? GetPUnitCur()->ToString().c_str() : "null");
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
	processor.SetPUnitCur(_pPUnitCatch);
}

//------------------------------------------------------------------------------
// Processor::ExceptionInfoStack
//------------------------------------------------------------------------------
void Processor::ExceptionInfoStack::Clear()
{
	for (ExceptionInfo* pExceptionInfo : *this) delete pExceptionInfo;
	clear();
}

void Processor::ExceptionInfoStack::Push(ExceptionInfo* pExceptionInfo)
{
	//::printf("**ExceptionInfoStack::Push()***\n");
	push_back(pExceptionInfo);
}

Processor::ExceptionInfo* Processor::ExceptionInfoStack::Pop()
{
	//::printf("**ExceptionInfoStack::Pop()***\n");
	if (empty()) return nullptr;
	ExceptionInfo* pExceptionInfo = back();
	pop_back();
	return pExceptionInfo;
}

void Processor::ExceptionInfoStack::Shrink(size_t cnt)
{
	//::printf("**ExceptionInfoStack::Shrink()***\n");
	if (cnt >= size()) return;
	auto ppExceptionInfoEnd = rbegin() + size() - cnt;
	for (auto ppExceptionInfo = rbegin(); ppExceptionInfo != ppExceptionInfoEnd; ppExceptionInfo++) {
		delete *ppExceptionInfo;
	}
	erase(begin() + cnt, end());
}

void Processor::ExceptionInfoStack::ShrinkUntilNull()
{
	//::printf("**ExceptionInfoStack::ShrinkUntilNull()***\n");
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
Processor* Processor_Normal::CreateSubProcessor()
{
	return new Processor_Normal(GetFrameCur().Reference());
}

void Processor_Normal::RunLoop(const PUnit* pPUnit, const PUnit* pPUnitSentinel)
{
	_pPUnitCur = pPUnit;
	if (!_pPUnitCur) return;
	PrepareExceptionHandling();
	if (pPUnitSentinel) {
		do {
			while (_contFlag && _pPUnitCur != pPUnitSentinel) {
				_pPUnitCur->Exec(*this);
			}
			if (!DoExceptionHandling()) break;
		} while (_contFlag && _pPUnitCur != pPUnitSentinel);
	} else if (_pPUnitCur->IsSequenceBegin()) {
		pPUnitSentinel = _pPUnitCur->GetPUnitSentinel();
		_pPUnitCur = _pPUnitCur->GetPUnitCont();	// skip SequenceBegin/ArgSlot/ArgSlotNamed
		if (pPUnitSentinel->IsSequenceEnd()) {
			do {
				while (_contFlag) {
					_pPUnitCur->Exec(*this);
				}
				if (!DoExceptionHandling()) break;
			} while (_contFlag);
		} else {
			do {
				while (_contFlag && _pPUnitCur != pPUnitSentinel) {
					_pPUnitCur->Exec(*this);
				}
				if (!DoExceptionHandling()) break;
			} while (_contFlag && _pPUnitCur != pPUnitSentinel);
		}
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		do {
			while (_contFlag) {
				_pPUnitCur->Exec(*this);
			}
			if (!DoExceptionHandling()) break;
		} while (_contFlag);
	}
	_contFlag = _resumeFlag;
}

//------------------------------------------------------------------------------
// Processor_Debug
//------------------------------------------------------------------------------
Processor* Processor_Debug::CreateSubProcessor()
{
	return new Processor_Debug(GetFrameCur().Reference(), _nestLevel);
}

void Processor_Debug::RunLoop(const PUnit* pPUnit, const PUnit* pPUnitSentinel)
{
	auto PrintPUnit = [](Stream& stream, int nestLevel, const PUnit* pPUnit) {
		String seqIdStr = pPUnit->MakeSeqIdString();
		stream.Printf("%*s%s %s\n", nestLevel * 2, "", seqIdStr.c_str(), pPUnit->ToString().c_str());
		return seqIdStr.size();
	};
	auto PrintStack = [this](Stream& stream, int nestLevel, size_t wdSeqId) {
		stream.Printf("%*s%*s %s\n", nestLevel * 2, "", wdSeqId, "",
			GetValueStack().ToString(StringStyle(StringStyle::Flag::Quote |
			StringStyle::Flag::NilVisible | StringStyle::Flag::WithSquare)).c_str());
	};
	_pPUnitCur = pPUnit;
	if (!_pPUnitCur) return;
	Stream& stream = *Stream::COut;
	_nestLevel++;
	stream.Printf("%*s---- Processor Begin at %s ----\n",
				  _nestLevel * 2, "", _pPUnitCur->MakeSeqIdString().c_str());
	PrepareExceptionHandling();
	size_t wdSeqId = 0;
	if (pPUnitSentinel) {
		// nothing to do
	} else if (_pPUnitCur->IsSequenceBegin()) {
		pPUnitSentinel = _pPUnitCur->GetPUnitSentinel();
		_pPUnitCur = _pPUnitCur->GetPUnitCont();	// skip SequenceBegin/ArgSlot/ArgSlotNamed
		if (pPUnitSentinel->IsSequenceEnd()) pPUnitSentinel = nullptr;
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		wdSeqId = PrintPUnit(stream, _nestLevel, _pPUnitCur);
		_pPUnitCur->Exec(*this);
	}
	do {
		while (_contFlag && _pPUnitCur != pPUnitSentinel) {
			PrintStack(stream, _nestLevel, wdSeqId);
			wdSeqId = PrintPUnit(stream, _nestLevel, _pPUnitCur);
			_pPUnitCur->Exec(*this);
		}
		if (!DoExceptionHandling()) break;
	} while (_contFlag && _pPUnitCur != pPUnitSentinel);
	_contFlag = _resumeFlag;
	stream.Printf("%*s---- Processor End ----\n", _nestLevel * 2, "");
	_nestLevel--;
}

}
