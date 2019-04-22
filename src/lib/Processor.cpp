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
	_pPUnitCur(nullptr), _contFlag(true), _resumeFlag(true), _event(Event::None)
{
	GetPUnitStack().reserve(1024);
	GetValueStack().reserve(1024);
	GetFrameStack().reserve(1024);
	PushFrame(Basement::Inst.GetFrame().Reference());
	PushPUnit(nullptr);
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
	if (!expr.GetPUnitTop()) return Value::nil();
	ProcessPUnit(expr.GetPUnitTop());
	return Error::IsIssued()? Value::nil() : PopValue();
}

//------------------------------------------------------------------------------
// Processor_Normal
//------------------------------------------------------------------------------
void Processor_Normal::RunLoop(const PUnit* pPUnit)
{
	_pPUnitCur = pPUnit;
	if (!_pPUnitCur) return;
	if (_pPUnitCur->IsBeginQuote()) {
		const PUnit* pPUnitSentinel = _pPUnitCur->GetPUnitSentinel();
		_pPUnitCur = _pPUnitCur->GetPUnitCont();	// skip PUnit_BeginQuote
		while (_contFlag && _pPUnitCur != pPUnitSentinel) _pPUnitCur->Exec(*this);
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		while (_contFlag) _pPUnitCur->Exec(*this);
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
	_pPUnitCur = pPUnit;
	if (!_pPUnitCur) return;
	Stream& stream = *Stream::COut;
	const PUnit* pPUnitSentinel = nullptr;
	stream.Printf("---- Processor Begin ----\n");
	if (_pPUnitCur->IsBeginQuote()) {
		pPUnitSentinel = _pPUnitCur->GetPUnitSentinel();
		_pPUnitCur = _pPUnitCur->GetPUnitCont();	// skip PUnit_BeginQuote
	} else {
		PushPUnit(nullptr);	// push a terminator so that Return exits the loop
		PrintPUnit(stream, _pPUnitCur);
		_pPUnitCur->Exec(*this);
	}
	while (_contFlag && _pPUnitCur != pPUnitSentinel) {
		PrintStack(stream);
		PrintPUnit(stream, _pPUnitCur);
		_pPUnitCur->Exec(*this);
	}
	_contFlag = _resumeFlag;
	stream.Printf("---- Processor End ----\n");
}

}
