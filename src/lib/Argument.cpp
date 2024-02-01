//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(Processor& processor, Value* pValueCar, DeclCallable* pDeclCallable, Attribute* pAttr,
				DeclCallable::Flags flags, Value* pValueThis, Expr_Block* pExprOfBlock) :
	_pValueCar(pValueCar), _pFrameForVType(pValueCar->GetFrameForVType(processor)), _pDeclCallable(pDeclCallable), _pAttr(pAttr), _flags(flags),
	_pValueThis(pValueThis), _pExprOfBlock(pExprOfBlock), _pArgSlotToFeed(nullptr),
	_mapMode(MapMode::None)
{
	const DeclArgOwner &declArgOwner = _pDeclCallable->GetDeclArgOwner();
	DeclArgOwner::const_iterator ppDeclArg = declArgOwner.begin();
	if (ppDeclArg != declArgOwner.end()) {
		DeclArg* pDeclArg = *ppDeclArg++;
		_pArgSlotFirst.reset(pDeclArg->GetArgSlotFactory().Create(pDeclArg->Reference()));
		ArgSlot* pArgSlotLast = _pArgSlotFirst.get();
		while (ppDeclArg != declArgOwner.end()) {
			DeclArg* pDeclArg = *ppDeclArg++;
			ArgSlot* pArgSlot = pDeclArg->GetArgSlotFactory().Create(pDeclArg->Reference());
			pArgSlotLast->SetNext(pArgSlot);
			pArgSlotLast = pArgSlot;
		}			
	}
	if (!_pDeclCallable->GetSymbolOfDict()->IsEmpty()) {
		_pValueOfDict.reset(new Value_Dict());
	}
	_pArgSlotToFeed = _pArgSlotFirst.get();
}

Argument::Argument(Processor& processor, const Function& function, DeclCallable::Flags flags) :
	Argument(processor, function.GetDeclCallable().Reference(), flags)
{
}

Function* Argument::CreateBlockFunction(Frame& frameOuter, const Symbol* pSymbol, bool holdFrameFlag) const
{
	return _pExprOfBlock? Function::CreateBlockFunction(frameOuter, pSymbol, *_pExprOfBlock, holdFrameFlag) : nullptr;
}

bool Argument::CheckArgSlotToFeed() const
{
	if (!_pArgSlotToFeed) {
		if (!IsSet(DeclCallable::Flag::CutExtraArgs)) {
			Error::Issue(ErrorType::ArgumentError, "too many arguments");
			return false;
		}
	} else if (!_pArgSlotToFeed->IsVacant()) {
		Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
		return false;
	} else if (_pArgSlotToFeed->IsVType(VTYPE_Quote)) {
		Error::Issue(ErrorType::ArgumentError, "invalid argument assignment");
		return false;
	}
	return true;
};

size_t Argument::CountArgSlot() const
{
	size_t cnt = 0;
	for (const ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) cnt++;
	return cnt;
}

void Argument::ResetAllValues()
{
	for (ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		pArgSlot->ResetValue();
	}
	if (_pValueOfDict) _pValueOfDict->GetValueDict().Clear();
}

bool Argument::FeedValues(Processor& processor, Frame& frameForVType, const ValueList& values)
{
	for (const Value* pValue : values) {
		if (!_pArgSlotToFeed) {
			if (!IsSet(DeclCallable::Flag::CutExtraArgs)) {
				Error::Issue(ErrorType::ArgumentError, "too many arguments");
				return false;
			}
		}
		FeedValue(processor, frameForVType, pValue->Reference());
		if (Error::IsIssued()) return false;
	}
	return true;
}

bool Argument::CompleteFeedValue(Processor& processor)
{
	for (ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (pArgSlot->HasValidValue()) {
			// nothing to do
		} else if (const Expr* pExprDefault = pArgSlot->GetDeclArg().GetExprDefault()) {
			RefPtr<Value> pValue(processor.ProcessPUnit(pExprDefault->GetPUnitFirst()));
			if (Error::IsIssued()) return false;
			pArgSlot->FeedValue(processor, *this, processor.GetFrameCur(), pValue.release());
		} else {
			Error::Issue(ErrorType::ArgumentError, "lacking value for argument '%s'",
						pArgSlot->GetDeclArg().GetSymbol()->GetName());
			return false;
		}
	}
	return true;
}

void Argument::DoCall(Processor& processor)
{
	const PUnit* pPUnitCur = processor.GetPUnitCur();
	if (!CompleteFeedValue(processor)) return;
	processor.SetPUnitCur(pPUnitCur);
	const DeclBlock& declBlock = _pDeclCallable->GetDeclBlock();
	if (_pExprOfBlock) {
		if (declBlock.IsOccurZero()) {
			Error::Issue(ErrorType::ArgumentError, "block can not be specified");
			return;
		}
	} else {
		if (declBlock.IsOccurOnce()) {
			Error::Issue(ErrorType::ArgumentError, "block is necessary");
			return;
		}
	}
	GetValueCar().Call(processor, *this);
}

bool Argument::ReadyToPickValue(Processor& processor, Frame& frame)
{
	for (ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (!pArgSlot->ReadyToPickValue(processor, frame)) return false;
	}
	return _pValueThis->ReadyToPickValueWithoutCast();
}

void Argument::AssignToFrame(Processor& processor, Frame& frame, Frame& frameOuter) const
{
	for (const ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		pArgSlot->AssignToFrame(processor, frame);
	}
	if (GetValueThis().IsValid()) {
		// assign to symbol "this"
		AssignThisToFrame(processor, frame, _pValueThis->PickValue());
	}
	do {
		// assign to symbol declared as dict%
		const Symbol* pSymbol = GetDeclCallable().GetSymbolOfDict();
		if (!pSymbol->IsEmpty()) frame.AssignFromArgument(processor, pSymbol, GetValueOfDict()->Reference());
	} while (0);
	do {
		// assign to symbol declared as arg%%
		const Symbol* pSymbol = GetDeclCallable().GetSymbolOfAccessor();
		if (!pSymbol->IsEmpty()) frame.AssignFromArgument(processor, pSymbol, new Value_Argument(Reference()));
	} while (0);
	do {
		// assign to symbol declared as {block}
		const DeclBlock& declBlock = GetDeclCallable().GetDeclBlock();
		const Symbol* pSymbol = declBlock.GetSymbol();
		if (pSymbol->IsEmpty()) {
			// nothing to do
		} else if (!GetExprOfBlock()) {
			frame.Assign(pSymbol, Value::nil());
		} else if (declBlock.IsSet(DeclBlock::Flag::Quote)) {
			frame.Assign(pSymbol, new Value_Expr(GetExprOfBlock()->Reference()));
		} else {
			frame.Assign(Function::CreateBlockFunction(frameOuter, pSymbol, *GetExprOfBlock(), false));
		}
	} while (0);
}

Value* Argument::ReturnIterator(Processor& processor, RefPtr<Iterator> pIterator)
{
	const Expr_Block* pExprOfBlock = GetExprOfBlock();
	if (pExprOfBlock) {
		return pIterator->Each(processor, *pExprOfBlock, GetFlags());
	} else if (IsSet(DeclCallable::Flag::List)) {
		RefPtr<ValueOwner> pValueOwner(ValueOwner::CreateFromIterator(*pIterator, false));
		if (Error::IsIssued()) return Value::nil();
		return new Value_List(pValueOwner.release());
	} else if (IsSet(DeclCallable::Flag::XList)) {
		RefPtr<ValueOwner> pValueOwner(ValueOwner::CreateFromIterator(*pIterator, true));
		if (Error::IsIssued()) return Value::nil();
		return new Value_List(pValueOwner.release());
	} else {
		return new Value_Iterator(pIterator.release());
	}
}

String Argument::ToString(const StringStyle& ss) const
{
	String str;
	str += GetValueCar().ToString(StringStyle(ss).SetQuoteSymbol());
	str += ":(";
	for (const ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (pArgSlot != GetArgSlotFirst()) str += ss.GetComma();
		str += pArgSlot->ToString(StringStyle(ss).SetQuoteSymbol());
	}
	if (GetValueOfDict()) {
		if (GetArgSlotFirst()) str += ss.GetComma();
		str += "(";
		str += GetValueOfDict()->ToString(StringStyle(ss).SetQuoteSymbol());
		str += ")%";
	}
	str += ")";
	str += GetAttr().ToString(ss);
	str += DeclCallable::FlagsToString(GetFlags());
	if (GetExprOfBlock()) {
		str += ss.IsCram()? "{" : " {";
		str += GetDeclCallable().GetDeclBlock().GetSymbol()->GetName();
		str += "}";
	}
	return str;
}

}
