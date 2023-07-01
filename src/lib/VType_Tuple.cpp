//==============================================================================
// VType_Tuple.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Tuple, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Tuple, `en)}

${help.ComposeMethodHelp(Tuple, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Tuple() {block?}
Gurax_DeclareConstructor(Tuple)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Tuple` instance.
)""");
}

Gurax_ImplementConstructor(Tuple)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	return argument.ReturnValue(processor, new Value_Tuple(pValueOwner.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Tuple#Each() {`block?}
Gurax_DeclareMethod(Tuple, Each)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce, DeclBlock::Flag::Quote);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(Tuple, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(valueThis.GenIterator());
	if (!pIterator) return Value::nil();
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Tuple#first
Gurax_DeclareProperty_R(Tuple, first)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The first element in the tuple, or `nil` if the tuple is empty.
)""");
}

Gurax_ImplementPropertyGetter(Tuple, first)
{
	auto& valueThis = GetValueThis(valueTarget);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	if (valueOwner.empty()) return Value::nil();
	return valueOwner.front()->Reference();
}

// Tuple#last
Gurax_DeclareProperty_R(Tuple, last)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The last element in the tuple, or `nil` if the tuple is empty.
)""");
}

Gurax_ImplementPropertyGetter(Tuple, last)
{
	auto& valueThis = GetValueThis(valueTarget);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	if (valueOwner.empty()) return Value::nil();
	return valueOwner.back()->Reference();
}

// Tuple#len
Gurax_DeclareProperty_R(Tuple, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The number of elements in the tuple.
)""");
}

Gurax_ImplementPropertyGetter(Tuple, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueOwner().size());
}

// Tuple#tuple
Gurax_DeclareProperty_R(Tuple, tuple)
{
	Declare(VTYPE_Tuple, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts into a Tuple instance.
)""");
}

Gurax_ImplementPropertyGetter(Tuple, tuple)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.Reference();
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Tuple == Tuple
Gurax_ImplementOpBinary(Eq, Tuple, Tuple)
{
	const ValueList& valuesL = Value_Tuple::GetValueOwner(valueL);
	const ValueList& valuesR = Value_Tuple::GetValueOwner(valueR);
	return new Value_Bool(valuesL.IsEqualTo(valuesR));
}

// Tuple >= Tuple
Gurax_ImplementOpBinary(Ge, Tuple, Tuple)
{
	const ValueList& valuesL = Value_Tuple::GetValueOwner(valueL);
	const ValueList& valuesR = Value_Tuple::GetValueOwner(valueR);
	return new Value_Bool(!valuesL.IsLessThan(valuesR));
}

// Tuple > Tuple
Gurax_ImplementOpBinary(Gt, Tuple, Tuple)
{
	const ValueList& valuesL = Value_Tuple::GetValueOwner(valueL);
	const ValueList& valuesR = Value_Tuple::GetValueOwner(valueR);
	return new Value_Bool(valuesR.IsLessThan(valuesL));
}

// Tuple <= Tuple
Gurax_ImplementOpBinary(Le, Tuple, Tuple)
{
	const ValueList& valuesL = Value_Tuple::GetValueOwner(valueL);
	const ValueList& valuesR = Value_Tuple::GetValueOwner(valueR);
	return new Value_Bool(!valuesR.IsLessThan(valuesL));
}

// Tuple < Tuple
Gurax_ImplementOpBinary(Lt, Tuple, Tuple)
{
	const ValueList& valuesL = Value_Tuple::GetValueOwner(valueL);
	const ValueList& valuesR = Value_Tuple::GetValueOwner(valueR);
	return new Value_Bool(valuesL.IsLessThan(valuesR));
}

// Tuple != Tuple
Gurax_ImplementOpBinary(Ne, Tuple, Tuple)
{
	const ValueList& valuesL = Value_Tuple::GetValueOwner(valueL);
	const ValueList& valuesR = Value_Tuple::GetValueOwner(valueR);
	return new Value_Bool(!valuesL.IsEqualTo(valuesR));
}

//------------------------------------------------------------------------------
// VType_Tuple
//------------------------------------------------------------------------------
VType_Tuple VTYPE_Tuple("Tuple");

void VType_Tuple::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Tuple));
	// Assignment of method
	Assign(Gurax_CreateMethod(Tuple, Each));
	// Assignment of property
	Assign(Gurax_CreateProperty(Tuple, first));
	Assign(Gurax_CreateProperty(Tuple, last));
	Assign(Gurax_CreateProperty(Tuple, len));
	Assign(Gurax_CreateProperty(Tuple, tuple));
	// Assignment of operator
	Gurax_AssignOpBinary(Eq, Tuple, Tuple);
	Gurax_AssignOpBinary(Ge, Tuple, Tuple);
	Gurax_AssignOpBinary(Gt, Tuple, Tuple);
	Gurax_AssignOpBinary(Le, Tuple, Tuple);
	Gurax_AssignOpBinary(Lt, Tuple, Tuple);
	Gurax_AssignOpBinary(Ne, Tuple, Tuple);
}

Value* VType_Tuple::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.HasCustomProp()) {
		return new Value_Tuple(value.GetCustomProps().Reference());
	}
	return nullptr;
}

#if 0
Value* VType_Tuple::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Iterator)) {
		Iterator& iterator = Value_Iterator::GetIterator(value);
		if (!iterator.MustBeFinite()) return Value::nil();
		return new Value_Tuple(ValueOwner::CreateFromIterator(iterator, false));
	} else if (value.IsType(VTYPE_List)) {
		return new Value_Tuple(Value_List::GetValueOwner(value).Clone());
	}
	return nullptr;
}
#endif

//------------------------------------------------------------------------------
// Value_Tuple
//------------------------------------------------------------------------------
VType& Value_Tuple::vtype = VTYPE_Tuple;

String Value_Tuple::ToString(const StringStyle& ss) const
{
	if (ss.IsBracket()) {
		return ToStringGeneric(ss, String().Format("%zuitems", GetValueOwner().size()));
	}
	return GetValueOwner().ToString(StringStyle(StringStyle::Flag::Quote |
				StringStyle::Flag::NilVisible | StringStyle::Flag::WithParenthesis));
}

bool Value_Tuple::FeedExpandToArgument(Frame& frame, Argument& argument)
{
	const ValueOwner& valueOwner = GetValueOwner();
	for (const Value* pValueElem : valueOwner) {
		if (!argument.CheckArgSlotToFeed()) return false;
		argument.FeedValue(frame, pValueElem->Reference());
		if (Error::IsIssued()) return false;
	}
	return true;
}

bool Value_Tuple::DoEmptyIndexGet(Value** ppValue) const
{
	const ValueOwner& valueOwner = GetValueOwner();
	*ppValue = new Value_List(valueOwner.Reference());
	return true;
}

bool Value_Tuple::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_Tuple::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const ValueOwner& valueOwner = GetValueOwner();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, valueOwner.size(), &idx)) return false;
	*ppValue = valueOwner.Get(idx).Reference();
	return true;
}

bool Value_Tuple::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	ValueOwner& valueOwner = GetValueOwner();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, valueOwner.size(), &idx)) return false;
	valueOwner.Set(idx, pValue.release());
	return true;
}

Iterator* Value_Tuple::DoGenIterator() const
{
	return new Iterator_Each(GetValueOwner().Reference());
}

bool Value_Tuple::DoSerialize(Stream& stream) const
{
	return GetValueOwner().Serialize(stream);
}

Value* VType_Tuple::DoDeserialize(Stream& stream) const
{
	RefPtr<ValueOwner> pValueOwner(ValueOwner::Deserialize(stream));
	return pValueOwner? new Value_Tuple(pValueOwner.release()) : nullptr;
}

}
