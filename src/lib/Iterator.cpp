//==============================================================================
// Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
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
	} else if (declArgOwner.size() == 0) {
		// iterable#Each { .. }
		bool listFlag = false;
		bool contFlag = true;
		processor.PushFrame<Frame_Scope>();
		if ((listFlag = flags & DeclCallable::Flag::List) || (flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueOwner> pValueOwner(new ValueOwner());
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (!pValue->IsUndefined() && (listFlag || pValue->IsValid())) {
					pValueOwner->push_back(pValue.release());
				}
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
		}
		processor.PopFrame();
	} else if (declArgOwner.size() == 1) {
		// iterable#Each {|elem| .. }
		bool listFlag = false;
		bool contFlag = true;
		Frame& frame = processor.PushFrame<Frame_Scope>();
		if ((listFlag = flags & DeclCallable::Flag::List) || (flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueOwner> pValueOwner(new ValueOwner());
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				frame.AssignWithCast(*declArgOwner[0], *pValueElem);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (!pValue->IsUndefined() && (listFlag || pValue->IsValid())) {
					pValueOwner->push_back(pValue.release());
				}
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				frame.AssignWithCast(*declArgOwner[0], *pValueElem);
				if (Error::IsIssued()) break;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
		}
		processor.PopFrame();
	} else { // declArgOwner.size() == 2
		// iterable#Each {|elem, idx| .. }
		bool listFlag = false;
		bool contFlag = true;
		size_t idx = 0;
		Frame& frame = processor.PushFrame<Frame_Scope>();
		if ((listFlag = flags & DeclCallable::Flag::List) || (flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueOwner> pValueOwner(new ValueOwner());
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				frame.AssignWithCast(*declArgOwner[0], *pValueElem);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValueIdx(new Value_Number(idx));
				idx++;
				frame.AssignWithCast(*declArgOwner[1], *pValueIdx);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (!pValue->IsUndefined() && (listFlag || pValue->IsValid())) {
					pValueOwner->push_back(pValue.release());
				}
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueElem(NextValue());
				if (!pValueElem) break;
				frame.AssignWithCast(*declArgOwner[0], *pValueElem);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValueIdx(new Value_Number(idx));
				idx++;
				frame.AssignWithCast(*declArgOwner[1], *pValueIdx);
				if (Error::IsIssued()) break;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
		}
		processor.PopFrame();
	}
	if (Error::IsIssued()) return Value::nil();
	return pValueRtn.release();
}

bool Iterator::MustBeFinite() const
{
	if (IsFinite()) return true;
	Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
	return false;
}

Iterator* Iterator::Clone() const
{
	//*********************
	return Reference();
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

}
