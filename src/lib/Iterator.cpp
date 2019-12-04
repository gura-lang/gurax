//==============================================================================
// Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
Value* Iterator::And()
{
	RefPtr<Value> pValueElem(NextValue());
	if (!pValueElem) return Value::nil();
	for (;;) {
		if (!pValueElem->GetBool()) return pValueElem.release();
		RefPtr<Value> pValueNext(NextValue());
		if (!pValueNext) break;
		pValueElem.reset(pValueNext.release());
	}
	return pValueElem.release();
}

bool Iterator::Contains(const Value& value)
{
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		if (pValueElem->IsEqualTo(&value)) return true;
	}
	return false;
}

size_t Iterator::Count(const Value& value)
{
	size_t cnt = 0;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		if (pValueElem->IsEqualTo(&value)) cnt++;
	}
	return cnt;
}

size_t Iterator::CountTrue()
{
	size_t cnt = 0;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		if (pValueElem->GetBool()) cnt++;
	}
	return cnt;
}

size_t Iterator::CountIf(Processor& processor, const Function& function)
{
	size_t cnt = 0;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
	}
	return cnt;
}

Value* Iterator::Each(Processor& processor, const Expr_Block& exprOfBlock, DeclCallable::Flags flags)
{
	RefPtr<Value> pValueRtn(Value::nil());
	const DeclArgOwner& declArgOwner = exprOfBlock.GetDeclCallable().GetDeclArgOwner();
	if (declArgOwner.size() > 2) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of block parameters");
		return Value::nil();
	}
	bool skipNilFlag = false;
	if ((flags & DeclCallable::Flag::Iter) || (skipNilFlag = flags & DeclCallable::Flag::XIter)) {
		RefPtr<Iterator> pIterator(new Iterator_DoEach(
									   processor.Reference(), processor.CreateFrame<Frame_Scope>(),
									   exprOfBlock.Reference(), Reference(), skipNilFlag));
		pValueRtn.reset(new Value_Iterator(pIterator.release()));
	} else {
		size_t nArgs = declArgOwner.size();
		bool contFlag = true;
		size_t idx = 0;
		Frame& frame = processor.PushFrame<Frame_Block>();
		if ((flags & DeclCallable::Flag::List) || (skipNilFlag = flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueOwner> pValueOwner(new ValueOwner());
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				if (nArgs > 0) {
					frame.AssignWithCast(*declArgOwner[0], *pValueElem);
					if (Error::IsIssued()) break;
					if (nArgs > 1) {
						RefPtr<Value> pValueIdx(new Value_Number(idx));
						frame.AssignWithCast(*declArgOwner[1], *pValueIdx);
						if (Error::IsIssued()) break;
					}
				}
				idx++;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				Processor::Event event = processor.GetEvent();
				processor.ClearEvent();
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (Processor::IsEventBreak(event)) {
					contFlag = false;
					if (pValue->IsUndefined()) break;
				}
				if (skipNilFlag) {
					if (pValue->IsValid()) pValueOwner->push_back(pValue.release());
				} else {
					pValueOwner->push_back(pValue->IsValid()? pValue.release() : Value::nil());
				}
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				if (nArgs > 0) {
					frame.AssignWithCast(*declArgOwner[0], *pValueElem);
					if (Error::IsIssued()) break;
					if (nArgs > 1) {
						RefPtr<Value> pValueIdx(new Value_Number(idx));
						frame.AssignWithCast(*declArgOwner[1], *pValueIdx);
						if (Error::IsIssued()) break;
					}
				}
				idx++;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			if (pValueRtn->IsUndefined()) pValueRtn.reset(Value::nil());
		}
		processor.PopFrame();
	}
	if (Error::IsIssued()) return Value::nil();
	return pValueRtn.release();
}

String Iterator::Join(const char* sep)
{
	StringStyle ss = StringStyle().AsValue();
	String str;
	RefPtr<Value> pValueElem(NextValue());
	if (!pValueElem) return str;
	str += pValueElem->ToString(ss);
	for (;;) {
		pValueElem.reset(NextValue());
		if (!pValueElem) break;
		str += sep;
		str += pValueElem->ToString(ss);
	}
	return str;
}

Value* Iterator::Mean(Processor& processor)
{
	size_t cnt = 0;
	RefPtr<Value> pValueSum(Sum(processor, &cnt));
	if (!pValueSum->IsValid()) return Value::nil();
	RefPtr<Value> pValueNum(new Value_Number(cnt));
	return Operator::Div->EvalBinary(processor, *pValueSum, *pValueNum);
}

Value* Iterator::Or()
{
	RefPtr<Value> pValueElem(NextValue());
	if (!pValueElem) return Value::nil();
	for (;;) {
		if (pValueElem->GetBool()) return pValueElem.release();
		RefPtr<Value> pValueNext(NextValue());
		if (!pValueNext) break;
		pValueElem.reset(pValueNext.release());
	}
	return pValueElem.release();
}

Value* Iterator::Prod(Processor& processor)
{
	RefPtr<Value> pValueAccum(NextValue());
	if (!pValueAccum) return Value::nil();
	while (!pValueAccum->IsZero()) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		pValueAccum.reset(Operator::Mul->EvalBinary(processor, *pValueAccum, *pValueElem));
		if (Error::IsIssued()) return Value::nil();
	}
	return pValueAccum.release();
}

Value* Iterator::Std(Processor& processor)
{
	return Value::nil();
}

Value* Iterator::Sum(Processor& processor)
{
	RefPtr<Value> pValueAccum(NextValue());
	if (!pValueAccum) return Value::nil();
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		pValueAccum.reset(Operator::Add->EvalBinary(processor, *pValueAccum, *pValueElem));
		if (Error::IsIssued()) return Value::nil();
	}
	return pValueAccum.release();
}

Value* Iterator::Sum(Processor& processor, size_t* pCnt)
{
	size_t cnt = 0;
	*pCnt = 0;
	RefPtr<Value> pValueAccum(NextValue());
	if (!pValueAccum) return Value::nil();
	cnt++;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		cnt++;
		pValueAccum.reset(Operator::Add->EvalBinary(processor, *pValueAccum, *pValueElem));
		if (Error::IsIssued()) return Value::nil();
	}
	*pCnt = cnt;
	return pValueAccum.release();
}

Value* Iterator::Var(Processor& processor)
{
	return Value::nil();
}

ValueOwner* Iterator::Tail(size_t n)
{
	ValueDeque valueDeque;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		valueDeque.push_back(pValueElem.release());
		if (valueDeque.size() > n) {
			Value::Delete(valueDeque.front());
			valueDeque.pop_front();
		}
	}
	if (Error::IsIssued()) {
		valueDeque.DeleteEach();
		return nullptr;
	}
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(valueDeque.size());
	std::copy(valueDeque.begin(), valueDeque.end(), std::back_inserter(*pValueOwner));
	return pValueOwner.release();
}

bool Iterator::MustBeFinite() const
{
	if (IsFinite()) return true;
	Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
	return false;
}

String Iterator::ToString(const StringStyle& ss) const
{
	String str;
	return str;
}

//------------------------------------------------------------------------------
// IteratorList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// IteratorOwner
//------------------------------------------------------------------------------
void IteratorOwner::Clear()
{
	for (Iterator* pIterator : *this) Iterator::Delete(pIterator);
	clear();
}

//------------------------------------------------------------------------------
// IteratorDequeOwner
//------------------------------------------------------------------------------
void IteratorDequeOwner::Clear()
{
	for (Iterator* pIterator : *this) Iterator::Delete(pIterator);
	clear();
}

}
