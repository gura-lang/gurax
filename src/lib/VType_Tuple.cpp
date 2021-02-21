//==============================================================================
// VType_Tuple.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Tuple() {block?}
Gurax_DeclareConstructor(Tuple)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Tuple` instance.");
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Tuple#first
Gurax_DeclareProperty_R(Tuple, first)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The first element in the tuple, or `nil` if the tuple is empty.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The last element in the tuple, or `nil` if the tuple is empty.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The number of elements in the tuple.");
}

Gurax_ImplementPropertyGetter(Tuple, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueOwner().size());
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Tuple));
	// Assignment of method
	// Assignment of property
	Assign(Gurax_CreateProperty(Tuple, first));
	Assign(Gurax_CreateProperty(Tuple, last));
	Assign(Gurax_CreateProperty(Tuple, len));
	// Assignment of operator
	Gurax_AssignOpBinary(Eq, Tuple, Tuple);
	Gurax_AssignOpBinary(Ge, Tuple, Tuple);
	Gurax_AssignOpBinary(Gt, Tuple, Tuple);
	Gurax_AssignOpBinary(Le, Tuple, Tuple);
	Gurax_AssignOpBinary(Lt, Tuple, Tuple);
	Gurax_AssignOpBinary(Ne, Tuple, Tuple);
}

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

Value* Value_Tuple::DoIndexGet(const Index& index) const
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.empty()) {
		return Clone();
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		Value* pValue = nullptr;
		if (!GetValueOwner().IndexGet(valueIndex, &pValue, true)) return Value::nil();
		return pValue;
	} else {
		RefPtr<ValueOwner> pValuesRtn(new ValueOwner());
		pValuesRtn->reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			Value* pValue = nullptr;
			if (!GetValueOwner().IndexGet(*pValueIndex, &pValue, true)) return Value::nil();
			pValuesRtn->push_back(pValue);
		}
		return new Value_Tuple(pValuesRtn.release());
	}
}

bool Value_Tuple::DoEmptyIndexGet2(Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return Value::undefined();
}

bool Value_Tuple::DoEmptyIndexSet2(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_Tuple::DoIndexGet2(const Value& valueIndex, Value** ppValue) const
{
	const ValueOwner& valueOwner = GetValueOwner();
	size_t posMax = valueOwner.size();
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int pos = valueIndexEx.GetNumber<Int>();
		if (pos < 0) pos += posMax;
		if (0 <= pos && static_cast<size_t>(pos) < posMax) {
			*ppValue = valueOwner.Get(pos).Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %d exceeds the list's size of %zu", pos, posMax);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		Int pos = static_cast<Int>(valueIndexEx.GetBool());
		if (0 <= pos && static_cast<size_t>(pos) < posMax) {
			*ppValue = valueOwner.Get(pos).Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %s exceeds the list's size of %zu",
			valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str(), posMax);
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

bool Value_Tuple::DoIndexSet2(const Value& valueIndex, RefPtr<Value> pValue)
{
	ValueOwner& valueOwner = GetValueOwner();
	size_t posMax = valueOwner.size();
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int pos = valueIndexEx.GetNumber<Int>();
		if (pos < 0) pos += posMax;
		if (0 <= pos && static_cast<size_t>(pos) < posMax) {
			valueOwner.Set(pos, pValue.release());
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %d exceeds the list's size of %zu", pos, posMax);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		Int pos = static_cast<Int>(valueIndexEx.GetBool());
		if (static_cast<size_t>(pos) < posMax) {
			valueOwner.Set(pos, pValue.release());
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %s exceeds the list's size of %zu",
			valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str(), posMax);
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

Iterator* Value_Tuple::DoGenIterator() const
{
	return new Iterator_Each(GetValueOwner().Reference());
}

}
