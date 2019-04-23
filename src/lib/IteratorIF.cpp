//==============================================================================
// IteratorIF.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// IteratorIF
//------------------------------------------------------------------------------
Value* IteratorIF::Each(Processor& processor, const Expr_Block& exprOfBlock, DeclCallable::Flags flags)
{
	RefPtr<Value> pValueRtn(Value::nil());
	const DeclArgOwner& declArgOwner = exprOfBlock.GetDeclCallable().GetDeclArgOwner();
	Frame& frame = processor.PushFrame<Frame_Scope>();
	bool listFlag = false;
	bool contFlag = true;
	if (declArgOwner.size() == 0) {
		if ((listFlag = flags & DeclCallable::Flag::List) || (flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
			do {
				RefPtr<Value> pValueEach(NextValue());
				if (!pValueEach) break;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (!pValue->IsUndefined() && (listFlag || pValue->IsValid())) {
					pValueTypedOwner->Add(pValue.release());
				}
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueTypedOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueEach(NextValue());
				if (!pValueEach) break;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
		}
	} else if (declArgOwner.size() == 1) {
		if ((listFlag = flags & DeclCallable::Flag::List) || (flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
			do {
				RefPtr<Value> pValueEach(NextValue());
				if (!pValueEach) break;
				frame.Assign(*declArgOwner[0], *pValueEach);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (!pValue->IsUndefined() && (listFlag || pValue->IsValid())) {
					pValueTypedOwner->Add(pValue.release());
				}
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueTypedOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueEach(NextValue());
				if (!pValueEach) break;
				frame.Assign(*declArgOwner[0], *pValueEach);
				if (Error::IsIssued()) break;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
		}
	} else if (declArgOwner.size() == 2) {
		size_t idx = 0;
		if ((listFlag = flags & DeclCallable::Flag::List) || (flags & DeclCallable::Flag::XList)) {
			RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
			do {
				RefPtr<Value> pValueEach(NextValue());
				if (!pValueEach) break;
				frame.Assign(*declArgOwner[0], *pValueEach);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValueIdx(new Value_Number(idx));
				idx++;
				frame.Assign(*declArgOwner[1], *pValueIdx);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValue(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				// Statements of return and break possibly return undefined value.
				if (!pValue->IsUndefined() && (listFlag || pValue->IsValid())) {
					pValueTypedOwner->Add(pValue.release());
				}
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
			pValueRtn.reset(new Value_List(pValueTypedOwner.release()));
		} else {
			do {
				RefPtr<Value> pValueEach(NextValue());
				if (!pValueEach) break;
				frame.Assign(*declArgOwner[0], *pValueEach);
				if (Error::IsIssued()) break;
				RefPtr<Value> pValueIdx(new Value_Number(idx));
				idx++;
				frame.Assign(*declArgOwner[1], *pValueIdx);
				if (Error::IsIssued()) break;
				pValueRtn.reset(processor.ProcessExpr(exprOfBlock));
				if (Error::IsIssued()) break;
				contFlag = !processor.IsEventBreak();
				processor.ClearEvent();
			} while (contFlag);
		}
	} else {
		Error::Issue(ErrorType::ArgumentError, "invalid number of block parameters");
	}
	processor.PopFrame();
	if (Error::IsIssued()) return Value::nil();
	return pValueRtn.release();
}

}
