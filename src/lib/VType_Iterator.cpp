//==============================================================================
// VType_Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
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
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
	// Assignment of method
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

Iterator* Value_Iterator::DoGenIterator()
{
	return GetIterator().Clone();
}

}
