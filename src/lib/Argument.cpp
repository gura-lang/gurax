//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(Value* pValueCar, DeclCallable* pDeclCallable, Attribute* pAttr,
				   Value* pValueThis, Expr_Block* pExprOfBlock) :
	_pValueCar(pValueCar), _pDeclCallable(pDeclCallable), _pAttr(pAttr),
	_pValueThis(pValueThis), _pExprOfBlock(pExprOfBlock), _flags(0), _pArgSlotToFeed(nullptr)
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
	_flags = GetDeclCallable().GetFlags() | DeclCallable::SymbolsToFlags(GetAttr().GetSymbols());
	_pArgSlotToFeed = _pArgSlotFirst.get();
}

Argument::Argument(const Function& function) : Argument(function.GetDeclCallable().Reference())
{
}
	
void Argument::ResetAllValues()
{
	for (ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		pArgSlot->ResetValue();
	}
	if (_pValueOfDict) _pValueOfDict->GetValueDict().Clear();
}

Function* Argument::CreateFunctionOfBlock(Frame& frameParent) const
{
	if (!GetExprOfBlock()) return nullptr;
	RefPtr<FunctionCustom>
		pFunction(new FunctionCustom(
					  Function::Type::Function,
					  GetExprOfBlock()->GetDeclCallable().GetDeclBlock().GetSymbol(),
					  GetExprOfBlock()->GetDeclCallable().Reference(),
					  GetExprOfBlock()->GetPUnitTop()));
	pFunction->SetFrameParent(frameParent);
	return pFunction.release();
}

Function* Argument::CreateFunctionOfBlock(Frame& frameParent, RefPtr<Argument>& pArgument) const
{
	Function* pFunction = CreateFunctionOfBlock(frameParent);
	if (pFunction) pArgument.reset(new Argument(*pFunction));
	return pFunction;
}

Value* Argument::DoCall(Processor& processor)
{
	for (const ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (!pArgSlot->HasValidValue()) {
			Error::Issue(ErrorType::ArgumentError, "not enough argument");
			return nullptr;
		}
	}
	const DeclBlock& declBlock = _pDeclCallable->GetDeclBlock();
	if (_pExprOfBlock) {
		if (declBlock.IsOccurZero()) {
			Error::Issue(ErrorType::ArgumentError, "block is unnecessary");
			return nullptr;
		}
	} else {
		if (declBlock.IsOccurOnce()) {
			Error::Issue(ErrorType::ArgumentError, "block is necessary");
			return nullptr;
		}
	}
	return GetValueCar().DoCall(processor, *this);
}

void Argument::AssignToFrame(Frame& frame) const
{
	for (const ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		pArgSlot->AssignToFrame(frame);
	}
	do {
		// assign to symbol declared as dict%
		const Symbol* pSymbol = GetDeclCallable().GetSymbolOfDict();
		if (!pSymbol->IsEmpty()) frame.AssignValueOfArgument(pSymbol, GetValueOfDict()->Reference());
	} while (0);
	do {
		// assign to symbol declared as arg%%
		const Symbol* pSymbol = GetDeclCallable().GetSymbolOfAccessor();
		if (!pSymbol->IsEmpty()) frame.AssignValueOfArgument(pSymbol, new Value_Argument(Reference()));
	} while (0);
	if (GetExprOfBlock()) {
		// assign to symbol declared as {block}
		const DeclBlock& declBlock = GetDeclCallable().GetDeclBlock();
		const Symbol* pSymbol = declBlock.GetSymbol();
		if (declBlock.GetFlags() & DeclBlock::Flag::Quote) {
			frame.AssignValue(pSymbol, new Value_Expr(GetExprOfBlock()->Reference()));
		} else {
			RefPtr<FunctionCustom>
				pFunction(new FunctionCustom(
							  Function::Type::Function, pSymbol, GetDeclCallable().Reference(),
							  GetExprOfBlock()->GetPUnitTop()));
			frame.AssignFunction(pFunction.release());
		}
	}
}

String Argument::ToString(const StringStyle& ss) const
{
	String str;
	str += GetValueCar().ToString(StringStyle(ss).Digest());
	str += '(';
	for (const ArgSlot* pArgSlot = GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (pArgSlot != GetArgSlotFirst()) str += ss.GetComma();
		str += pArgSlot->ToString(StringStyle(ss).Digest());
	}
	if (GetValueOfDict()) {
		if (GetArgSlotFirst()) str += ss.GetComma();
		str += "(";
		str += GetValueOfDict()->ToString(StringStyle(ss).Digest());
		str += ")%";
	}
	str += ')';
	str += GetAttr().ToString(ss);
	if (GetExprOfBlock()) {
		str += ss.IsCram()? "{" : " {";
		str += GetDeclCallable().GetDeclBlock().GetSymbol()->GetName();
		str += "}";
	}
	return str;
}

}
