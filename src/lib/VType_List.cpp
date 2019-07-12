//==============================================================================
// VType_List.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// List#Add(value+):reduce
Gurax_DeclareMethod(List, Add)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::OnceOrMore, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(List, Add)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	for (Value* pValue : values) {
		valueTypedOwner.Add(pValue->Reference());
	}
	return argument.GetValueThis().Reference();
}

// List#Append(value+):reduce
Gurax_DeclareMethod(List, Append)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::OnceOrMore, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(List, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	for (Value* pValue : values) {
		if (pValue->IsType(VTYPE_List)) {
			valueTypedOwner.Append(Value_List::GetValueTypedOwner(*pValue));
		} else if (pValue->IsType(VTYPE_Iterator)) {
			valueTypedOwner.Append(Value_Iterator::GetIterator(*pValue));
		} else {
			valueTypedOwner.Add(pValue->Reference());
		}
	}
	return argument.GetValueThis().Reference();
}

// List#Clear():reduce
Gurax_DeclareMethod(List, Clear)
{
	Declare(VTYPE_List, Flag::Reduce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(List, Clear)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetValueTypedOwner().Clear();
	return argument.GetValueThis().Reference();
}

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
// Implementation of property
//------------------------------------------------------------------------------
// List#first
Gurax_DeclareProperty_R(List, first)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The first element in the list, or `nil` if the list is empty.");
}

Gurax_ImplementPropertyGetter(List, first)
{
	auto& valueThis = GetValueThis(valueTarget);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	if (valueOwner.empty()) return Value::nil();
	return valueOwner.front()->Reference();
}

// List#isEmpty
Gurax_DeclareProperty_R(List, isEmpty)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A boolean value indicating whether the list is empty or not.");
}

Gurax_ImplementPropertyGetter(List, isEmpty)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetValueOwner().empty());
}

// List#last
Gurax_DeclareProperty_R(List, last)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The last element in the list, or `nil` if the list is empty.");
}

Gurax_ImplementPropertyGetter(List, last)
{
	auto& valueThis = GetValueThis(valueTarget);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	if (valueOwner.empty()) return Value::nil();
	return valueOwner.back()->Reference();
}

// List#len
Gurax_DeclareProperty_R(List, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The number of elements in the list.");
}

Gurax_ImplementPropertyGetter(List, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueOwner().size());
}

// List#vtypeOfElem
Gurax_DeclareProperty_R(List, vtypeOfElem)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The value type of elements in the list.");
}

Gurax_ImplementPropertyGetter(List, vtypeOfElem)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_VType(*valueThis.GetValueTypedOwner().GetVTypeOfElems());
}

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
VType_List VTYPE_List("List");

void VType_List::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(List, Add));
	Assign(Gurax_CreateMethod(List, Append));
	Assign(Gurax_CreateMethod(List, Clear));
	Assign(Gurax_CreateMethod(List, Each));
	// Assignment of property
	Assign(Gurax_CreateProperty(List, first));
	Assign(Gurax_CreateProperty(List, isEmpty));
	Assign(Gurax_CreateProperty(List, last));
	Assign(Gurax_CreateProperty(List, len));
	Assign(Gurax_CreateProperty(List, vtypeOfElem));
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
	return DeclCallable::IsMappable(declArg, flags);
#if 0
	if ((flags & (DeclCallable::Flag::NoMap | DeclCallable::Flag::Map)) != DeclCallable::Flag::Map) {
		return false;
	}
	if (declArg.GetVType().IsListOrIterator()) return false;
	return true;
#endif
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
		if (!GetValueTypedOwner().IndexGet(pValueIndex, &pValue)) return Value::nil();
		return pValue;
	} else {
		RefPtr<ValueTypedOwner> pValuesRtn(new ValueTypedOwner());
		pValuesRtn->Reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			Value* pValue = nullptr;
			if (!GetValueTypedOwner().IndexGet(pValueIndex, &pValue)) return Value::nil();
			pValuesRtn->Add(pValue);
		}
		return new Value_List(pValuesRtn.release());
	}
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

Iterator* Value_List::DoGenIterator() const
{
	return new ValueTypedOwner::Iterator_Each(GetValueTypedOwner().Reference());
}

}
