//==============================================================================
// VType_List.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// List#Each() {`block}
Gurax_DeclareMethod(List, Each)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(List, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	// Block
	const Expr_Block& exprOfBlock = *argument.GetExprOfBlock();
	const DeclArgOwner& declArgOwner = exprOfBlock.GetDeclCallable().GetDeclArgOwner();
	DeclArg* pDeclArg1st = (declArgOwner.size() >= 1)? declArgOwner[0] : nullptr;
	DeclArg* pDeclArg2nd = (declArgOwner.size() >= 2)? declArgOwner[1] : nullptr;
	if (declArgOwner.size() >= 3) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of block parameters");
		return Value::nil();
	}
	// Function body
	Frame& frame = processor.PushFrame<Frame_Scope>();
	size_t idx = 0;
	for (Value* pValueEach : valueOwner) {
		if (pDeclArg1st) {
			frame.Assign(*pDeclArg1st, *pValueEach);
			if (Error::IsIssued()) return Value::nil();
		}
		if (pDeclArg2nd) {
			RefPtr<Value> pValueIdx(new Value_Number(idx));
			frame.Assign(*pDeclArg2nd, *pValueIdx);
			if (Error::IsIssued()) return Value::nil();
		}
		RefPtr<Value> pValue(processor.Process(exprOfBlock));
		idx++;
	}
	processor.PopFrame();
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
VType_List VTYPE_List("List");

void VType_List::DoPrepare(Frame& frameOuter)
{
	SetAttrs(VTYPE_Object, Flag::Mutable);
	frameOuter.Assign(*this);
	// Assignment of method
	Assign(Gurax_CreateMethod(List, Each));
}

//------------------------------------------------------------------------------
// Value_List
//------------------------------------------------------------------------------
String Value_List::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%zuitems>", GetValueOwner().size());
	return str;
}

String Value_List::ToStringDetail(const StringStyle& ss) const
{
	return GetValueOwner().ToString(ss);
}

Value* Value_List::DoIndexGet(const Index& index) const
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		const Value* pValueIndex = valuesIndex.front();
		Value* pValue = nullptr;
		if (GetValueTypedOwner().IndexGet(pValueIndex, &pValue)) return pValue;
	} else {
	}
	return Value::nil();
}

void Value_List::DoIndexSet(const Index& index, Value* pValue)
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		const Value* pValueIndex = valuesIndex.front();
		GetValueTypedOwner().IndexSet(pValueIndex, pValue);
	} else {
	}
}

Iterator* Value_List::DoGenIterator()
{
	return new Iterator_Each(GetValueTypedOwner().Reference());
}

}
