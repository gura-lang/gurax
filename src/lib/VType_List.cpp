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
		"Repeats the process in `block` for each element in the target iterable instance.\n"
		"The `block` takes block parameters in one of the following forms:\n"
		"\n"
		"- `iterable#Each { .. }` .. no parameter\n"
		"- `iterable#Each {|elem| .. }` .. Element instance\n"
		"- `iterable#Each {|elem, idx| .. }` .. Element instance and index counter\n");
}

Gurax_ImplementMethod(List, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(valueThis.DoGenIterator());
	return pIterator->Each(processor, *argument.GetExprOfBlock(), argument.GetFlags());
}

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
VType_List VTYPE_List("List");

void VType_List::DoPrepare(Frame& frameOuter)
{
	// VType settings
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

bool Value_List::IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const
{
	if ((flags & (DeclCallable::Flag::NoMap | DeclCallable::Flag::Map)) != DeclCallable::Flag::Map) {
		return false;
	}
	if (declArg.GetVType().IsListOrIterator()) return false;
	return true;
}

void Value_List::UpdateMapMode(Argument& argument) const
{
	if (argument.IsMapNone()) argument.SetMapMode(Argument::MapMode::ToList);
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
	return new Iterator_ListElem(GetValueTypedOwner().Reference());
}

}
