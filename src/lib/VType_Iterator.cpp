//==============================================================================
// VType_Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Iterator#Each() {`block}
Gurax_DeclareMethod(Iterator, Each)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Iterator, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(valueThis.GetIterator().Clone());
	return pIterator->Each(processor, *argument.GetExprOfBlock(), argument.GetFlags());
}

// Iterator#IsFinite()
Gurax_DeclareMethod(Iterator, IsFinite)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the iterator is a finite one.");
}

Gurax_ImplementMethod(Iterator, IsFinite)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const Iterator& iterator = valueThis.GetIterator();
	return new Value_Bool(!iterator.IsInfinite());
}

// Iterator#IsInfinite()
Gurax_DeclareMethod(Iterator, IsInfinite)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the iterator is a infinite one.");
}

Gurax_ImplementMethod(Iterator, IsInfinite)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const Iterator& iterator = valueThis.GetIterator();
	return new Value_Bool(iterator.IsInfinite());
}

// Iterator#NextValue()
Gurax_DeclareMethod(Iterator, NextValue)
{
	Declare(VTYPE_Iterator, Flag::None);
}

Gurax_ImplementMethod(Iterator, NextValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iterator = valueThis.GetIterator();
	// Function body
	RefPtr<Value> pValue(iterator.NextValue());
	return pValue? pValue.release() : Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Iterator
//------------------------------------------------------------------------------
VType_Iterator VTYPE_Iterator("Iterator");

void VType_Iterator::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Iterator, Each));
	Assign(Gurax_CreateMethod(Iterator, IsFinite));
	Assign(Gurax_CreateMethod(Iterator, IsInfinite));
	Assign(Gurax_CreateMethod(Iterator, NextValue));
	// Assignment of property
}

Value* VType_Iterator::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_List)) {
		return new Value_Iterator(Value_List::GetValueTypedOwner(value).GenerateIterator());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Iterator
//------------------------------------------------------------------------------
String Value_Iterator::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetIterator().ToString(StringStyle().Digest());
	str += ">";
	return str;
}

String Value_Iterator::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

bool Value_Iterator::IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const
{
	return DeclCallable::IsMappable(declArg, flags);
}

void Value_Iterator::UpdateMapMode(Argument& argument) const
{
	argument.SetMapMode(Argument::MapMode::ToIter);
}

const DeclCallable* Value_Iterator::GetDeclCallable()
{
	RefPtr<Value> pValueElem(GetIterator().PeekValue());
	return pValueElem? pValueElem->GetDeclCallable() : nullptr;
}

void Value_Iterator::DoCall(Processor& processor, Argument& argument)
{
	const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
	if (pPUnitOfCaller->GetDiscardValueFlag()) {
		if (GetIterator().MustBeFinite()) {
			for (;;) {
				RefPtr<Value> pValue(GetIterator().NextValue());
				if (!pValue) break;
				pValue->DoEval(processor, argument);
			}
		}
	} else {
		RefPtr<Value> pValueRtn(DoEval(processor, argument));
		if (Error::IsIssued()) return;
		processor.PushValue(pValueRtn.release());
	}
	processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
}

Value* Value_Iterator::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<Iterator> pIterator(new Iterator_IteratorEvaluator(
								   processor.Reference(), GetIterator().Reference(), argument.Reference()));
	return new Value_Iterator(pIterator.release());
}

Iterator* Value_Iterator::DoGenIterator() const
{
	return GetIterator().Clone();
}

}
