//==============================================================================
// VTypeCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
VTypeCustom::VTypeCustom() : VType(Symbol::Empty), _pValuesPropInit(new ValueOwner())
{
	_pConstructor.reset(Function::Empty.Reference()); // _pConstructor must be initialized here
}

void VTypeCustom::AssignFunction(Function* pFunction)
{
	const Symbol* pSymbol = pFunction->GetSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(__init__))) {
		pFunction->DeclareBlock(Gurax_Symbol(block), DeclBlock::Occur::ZeroOrOnce);
		SetConstructor(new Constructor(*this, pFunction));
	} else {
		GetFrame().Assign(pSymbol, new Value_Function(pFunction));
	}
}

bool VTypeCustom::AssignPropHandler(Frame& frame, const Symbol* pSymbol, bool listVarFlag,
									const Attribute& attr, RefPtr<Value> pValueInit)
{
	size_t iProp = GetValuesPropInit().size();
	RefPtr<PropHandler> pPropHandler(new PropHandlerCustom(pSymbol, iProp));
	PropHandler::Flags flags = PropHandler::Flag::Readable | PropHandler::Flag::Writable;
	if (listVarFlag) flags |= PropHandler::Flag::ListVar;
	if (pValueInit->IsNil() || attr.IsSet(Gurax_Symbol(nil))) flags |= PropHandler::Flag::Nil;
	const VType *pVType = &VTYPE_Any;
	Value* pValue = frame.Lookup(attr.GetDottedSymbol());
	if (pValue && pValue->IsType(VTYPE_VType)) {
		pVType = &dynamic_cast<Value_VType*>(pValue)->GetVTypeThis();
		if (!pValueInit->IsNil()) {
			pValueInit.reset(pVType->Cast(*pValueInit, listVarFlag));
			if (!pValueInit) return false;
		}
	} else if (!pValueInit->IsNil()) {
		pVType = &pValueInit->GetVType();
	}
	GetValuesPropInit().push_back(pValueInit.release());
	pPropHandler->Declare(*pVType, flags);
	Assign(pPropHandler.release());
	return true;
}

void VTypeCustom::PrepareForAssignment(const Symbol* pSymbol)
{
	if (!_pSymbol->IsEmpty()) return;
	Function& constructor = GetConstructor();
	_pSymbol = pSymbol;
	if (constructor.IsEmpty()) {
		SetConstructor(new ConstructorDefault(*this, pSymbol));
	} else {
		constructor.SetSymbol(pSymbol);
	}
}

Value* VTypeCustom::DoCastFrom(const Value& value) const
{
	return value.Reference();
}

//------------------------------------------------------------------------------
// VTypeCustom::ConstructorDefault
//------------------------------------------------------------------------------
VTypeCustom::ConstructorDefault::ConstructorDefault(VTypeCustom& vtypeCustom, const Symbol* pSymbol) :
	Function(Type::Function, pSymbol), _vtypeCustom(vtypeCustom)
{
	GetDeclCallable().GetDeclBlock().
		SetSymbol(Gurax_Symbol(block)).SetOccur(DeclBlock::Occur::ZeroOrOnce).SetFlags(Flag::None);
}

Value* VTypeCustom::ConstructorDefault::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<ValueCustom> pValueThis(new ValueCustom(GetVTypeCustom()));
	if (!pValueThis->InitCustomProp()) return nullptr;
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return pValueThis.release();
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
	ArgFeeder args(*pArgumentSub);
	if (!args.FeedValue(frame, pValueThis.release())) return Value::nil();
	return pExprOfBlock->DoEval(processor, *pArgumentSub);
}

String VTypeCustom::ConstructorDefault::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// VTypeCustom::Constructor
//------------------------------------------------------------------------------
VTypeCustom::Constructor::Constructor(VTypeCustom& vtypeCustom, Function* pFuncInitializer) :
	Function(Type::Function, Symbol::Empty, pFuncInitializer->GetDeclCallable().Reference()),
	_vtypeCustom(vtypeCustom), _pFuncInitializer(pFuncInitializer)
{
}

Value* VTypeCustom::Constructor::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<ValueCustom> pValueThis(new ValueCustom(GetVTypeCustom()));
	if (!pValueThis->InitCustomProp()) return nullptr;
	argument.SetValueThis(pValueThis.Reference());
	RefPtr<Value> pValue(GetFuncInitializer().DoEval(processor, argument));
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return pValueThis.release();
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
	ArgFeeder args(*pArgumentSub);
	if (!args.FeedValue(frame, pValueThis.release())) return Value::nil();
	return pExprOfBlock->DoEval(processor, *pArgumentSub);
}

String VTypeCustom::Constructor::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
bool ValueCustom::InitCustomProp()
{
	const ValueOwner& valuesPropInit = GetVType().GetValuesPropInit();
	_pValuesProp->reserve(valuesPropInit.size());
	for (const Value* pValue : valuesPropInit) {
		RefPtr<Value> pValueCloned = pValue->Clone();
		if (!pValueCloned) {
			Error::Issue(ErrorType::PropertyError, "failed to initialize property");
			return false;
		}
		_pValuesProp->push_back(pValueCloned.release());
	}
	return true;
}

void ValueCustom::SetCustomProp(size_t iProp, Value* pValue)
{
	ValueOwner::iterator ppValue = _pValuesProp->begin() + iProp;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

String ValueCustom::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ">";
	return str;
}

String ValueCustom::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
