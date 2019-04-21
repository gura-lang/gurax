//==============================================================================
// IteratorIF.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// IteratorIF
//------------------------------------------------------------------------------
Value* IteratorIF::Each(Processor& processor, const Expr_Block& exprOfBlock)
{
	const DeclArgOwner& declArgOwner = exprOfBlock.GetDeclCallable().GetDeclArgOwner();
	if (declArgOwner.size() >= 3) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of block parameters");
		return Value::nil();
	}
	// Function body
	Frame& frame = processor.PushFrame<Frame_Scope>();
	Value* pValueEach = nullptr;
	RefPtr<Value> pValueRtn;
	if (declArgOwner.size() == 0) {
		while ((pValueEach = NextValue()) && processor.GetContFlag()) {
			pValueRtn.reset(processor.Process(exprOfBlock));
		}
	} else if (declArgOwner.size() == 1) {
		while ((pValueEach = NextValue()) && processor.GetContFlag()) {
			frame.Assign(*declArgOwner[0], *pValueEach);
			if (Error::IsIssued()) break;
			pValueRtn.reset(processor.Process(exprOfBlock));
		}
	} else if (declArgOwner.size() == 2) {
		size_t idx = 0;
		while ((pValueEach = NextValue()) && processor.GetContFlag()) {
			frame.Assign(*declArgOwner[0], *pValueEach);
			if (Error::IsIssued()) break;
			RefPtr<Value> pValueIdx(new Value_Number(idx));
			frame.Assign(*declArgOwner[1], *pValueIdx);
			if (Error::IsIssued()) break;
			pValueRtn.reset(processor.Process(exprOfBlock));
			idx++;
		}
	}
	processor.PopFrame();
	if (Error::IsIssued()) return Value::nil();
	return pValueRtn.release();
}

}
