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
// VType_Iterator
//------------------------------------------------------------------------------
VType_Iterator VTYPE_Iterator("Iterator");

void VType_Iterator::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Iterator, Each));
	Assign(Gurax_CreateMethod(Iterator, NextValue));
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
	if ((flags & (DeclCallable::Flag::NoMap | DeclCallable::Flag::Map)) != DeclCallable::Flag::Map) {
		return false;
	}
	if (declArg.GetVType().IsListOrIterator()) return false;
	return true;
}

void Value_Iterator::UpdateMapMode(Argument& argument) const
{
	argument.SetMapMode(Argument::MapMode::ToIter);
}

Iterator* Value_Iterator::DoGenIterator() const
{
	return GetIterator().Clone();
}

}
