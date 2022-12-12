//==============================================================================
// Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
RefPtr<Iterator> Iterator::Empty;

void Iterator::Bootup()
{
	Empty.reset(new Iterator_Empty());
}

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
		if (pValueElem->IsEqualTo(value)) return true;
	}
	return false;
}

size_t Iterator::Count(const Value& value)
{
	size_t cnt = 0;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		if (pValueElem->IsEqualTo(value)) cnt++;
	}
	return cnt;
}

size_t Iterator::CountFalse()
{
	size_t cnt = 0;
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		if (!pValueElem->GetBool()) cnt++;
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
	Frame& frame = processor.GetFrameCur();
	size_t cnt = 0;
	RefPtr<Argument> pArgument(new Argument(processor, function));
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		ArgFeeder args(*pArgument, frame);
		args.FeedValue(pValueElem.release());
		RefPtr<Value> pValueRtn(function.Eval(processor, *pArgument));
		if (pValueRtn->GetBool()) cnt++;
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
	if ((flags & DeclCallable::Flag::Iter) || (skipNilFlag = (flags & DeclCallable::Flag::XIter))) {
		RefPtr<Iterator> pIterator(new Iterator_DoEach(
									   processor.Reference(), exprOfBlock.Reference(), Reference(), skipNilFlag));
		pValueRtn.reset(new Value_Iterator(pIterator.release()));
	} else {
		size_t nArgs = declArgOwner.size();
		bool contFlag = true;
		size_t idx = 0;
		Frame& frame = processor.PushFrame<Frame_Block>();
		if ((flags & DeclCallable::Flag::List) || (skipNilFlag = (flags & DeclCallable::Flag::XList))) {
			RefPtr<ValueOwner> pValueOwner(new ValueOwner());
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				if (nArgs > 0) {
					if (!frame.AssignWithCast(*declArgOwner[0], *pValueElem)) break;
					if (nArgs > 1) {
						RefPtr<Value> pValueIdx(new Value_Number(idx));
						if (!frame.AssignWithCast(*declArgOwner[1], *pValueIdx)) break;
					}
				}
				idx++;
				Event event;
				RefPtr<Value> pValue(exprOfBlock.Eval(processor, event));
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
					if (!frame.AssignWithCast(*declArgOwner[0], *pValueElem)) break;
					if (nArgs > 1) {
						RefPtr<Value> pValueIdx(new Value_Number(idx));
						if (!frame.AssignWithCast(*declArgOwner[1], *pValueIdx)) break;
					}
				}
				idx++;
				Event event;
				pValueRtn.reset(exprOfBlock.Eval(processor, event));
				if (Error::IsIssued()) break;
				contFlag = !Processor::IsEventBreak(event);
			} while (contFlag);
			if (pValueRtn->IsUndefined()) pValueRtn.reset(Value::nil());
		}
		processor.PopFrame();
	}
	if (Error::IsIssued()) return Value::nil();
	return pValueRtn.release();
}

void Iterator::Join(String& str, const char* sep, const StringStyle& ss)
{
	StringStyle ssMod(ss);
	//ssMod.UnsetQuoteString();
	RefPtr<Value> pValueElem(NextValue());
	if (!pValueElem) return;
	str += pValueElem->ToString(ssMod);
	for (;;) {
		pValueElem.reset(NextValue());
		if (!pValueElem) break;
		str += sep;
		str += pValueElem->ToString(ssMod);
	}
}

bool Iterator::Joinb(Binary& buff)
{
	for (;;) {
		RefPtr<Value> pValueElem(NextValue());
		if (!pValueElem) break;
		if (!pValueElem->IsType(VTYPE_Binary)) {
			Error::Issue(ErrorType::TypeError, "element must be of `Binary`");
			return false;
		}
		buff += Value_Binary::GetBinary(*pValueElem);
	}
	return true;
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
