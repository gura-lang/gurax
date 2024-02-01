//==============================================================================
// VType_Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

${help.ComposePropertyHelp(Iterator, `en)}

# Operator

The following operators are prepared:

- `Iterator[]` ... Creates a `List` from the `Iterator`.

# Cast Operation

The following cast operations are prepared:

- `List as Iterator` ... Turns a `List` into an `Iterator`.
- `Tuple as Iterator` ... Turns a `Tuple` into an `Iterator`.

${help.ComposeConstructorHelp(Iterator, `en)}

${help.ComposeMethodHelp(Iterator, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method specific to Iterator
//-----------------------------------------------------------------------------
// Iterator#IsFinite()
Gurax_DeclareMethod(Iterator, IsFinite)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the iterator is finite.
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
イテレータが有限のとき `true` を返します。
)""");
}

Gurax_ImplementMethod(Iterator, IsFinite)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return new Value_Bool(iteratorThis.IsFinite());
}

// Iterator#IsInfinite()
Gurax_DeclareMethod(Iterator, IsInfinite)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the iterator is infinite.
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
イテレータが無限のとき `true` を返します。
)""");
}

Gurax_ImplementMethod(Iterator, IsInfinite)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return new Value_Bool(iteratorThis.IsInfinite());
}

// Iterator#IsLenDetermined()
Gurax_DeclareMethod(Iterator, IsLenDetermined)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
)""");
}

Gurax_ImplementMethod(Iterator, IsLenDetermined)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return new Value_Bool(iteratorThis.IsLenDetermined());
}

// Iterator#IsRewindable()
Gurax_DeclareMethod(Iterator, IsRewindable)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
)""");
}

Gurax_ImplementMethod(Iterator, IsRewindable)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return new Value_Bool(iteratorThis.IsRewindable());
}

// Iterator#MakeRewindable() {block?}
Gurax_DeclareMethod(Iterator, MakeRewindable)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
)""");
}

Gurax_ImplementMethod(Iterator, MakeRewindable)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	if (!iteratorThis.MustBeFinite()) return Value::nil();
	RefPtr<Iterator> pIterator(new Iterator_Rewindable(iteratorThis.Reference()));
	return argument.ReturnValue(processor, new Value_Iterator(pIterator.release()));
}

// Iterator#NextValue()
Gurax_DeclareMethod(Iterator, NextValue)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns the next element value of the iterator.
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
イテレータの次の要素を返します。
)""");
}

Gurax_ImplementMethod(Iterator, NextValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	RefPtr<Value> pValue(iteratorThis.NextValue());
	return pValue? pValue.release() : Value::nil();
}

// Iterator#Rewind()
Gurax_DeclareMethod(Iterator, Rewind)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
)""");
}

Gurax_ImplementMethod(Iterator, Rewind)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	if (!iteratorThis.IsRewindable()) {
		Error::Issue(ErrorType::IteratorError, "the iterator is not rewindable");
		return Value::nil();
	}
	iteratorThis.Rewind();
	return valueThis.Reference();
}

// Iterator#Skip(n as Number):void
Gurax_DeclareMethod(Iterator, Skip)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Skip)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iterThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberNonNeg<size_t>();
	// Function body
	if (iterThis.Skip(n)) return Value::nil();
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method common to both Iterator and List
//-----------------------------------------------------------------------------
// Iterator#After(criteria) {block?}
Gurax_DeclareMethod(Iterator, After)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that returns a sequence of elements from the target iterable after the condition specified by `criteria` is met.

`criteria` is a `Function` or an iterable.

A function as the criteria has a format `f(value as Any)` or `f(value as Any, idx as Number)` where `value` is each element value and `idx` is the index
starting from zero. It is supposed to return a `Bool` value by determining whether `value` matches the condition.

```
[3, 1, 4, 1, 5, 9].After(Function(value) {value >= 4}):list // Returns [1, 5, 9]
```d

An iterable as the criteria is a sequence of `Bool` values that is scanned along with the target iterable.

```
[3, 1, 4, 1, 5, 9].After([false, false, true, false, false, false]):list // Returns [1, 5, 9]
```
)""");
}

Gurax_ImplementMethod(Iterator, After)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Since(processor, argument, iteratorSrc, false);
}

// Iterator#Align(n as Number, valueStuff?):map {block?}
Gurax_DeclareMethod(Iterator, Align)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("valueStuff", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that returns `n` pieces of elements from the source iterable.
If the source iterable has fewer elements, the rest will be filled with the value `valueStuff`
or `nil` when the argument is omitted.
)""");
}

Gurax_ImplementMethod(Iterator, Align)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Align(processor, argument, iteratorSrc);
}

Value* VType_Iterator::Method_Align(Processor& processor, Argument& argument, Iterator& iteratorSrc)
{
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberPos<size_t>();
	RefPtr<Value> pValueStuff(args.IsValid()? args.PickValue().Reference() : Value::nil());
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Align(iteratorSrc.Reference(), n, pValueStuff.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#And()
Gurax_DeclareMethod(Iterator, And)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns the last value if all the values are determined as `true`, and returns `false` otherwise.

```
[true, true, true].And()           // Returns true
[true, false, true].And()          // Returns false
['apple', 'grape', 'orange'].And() // Returns 'orange'
['apple', false, 'orange'].And()   // Returns false
```
)""");
}

Gurax_ImplementMethod(Iterator, And)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.And();
}

// Iterator#ArgMax():[lastIndex,indices]
Gurax_DeclareMethod(Iterator, ArgMax)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(lastIndex));
	DeclareAttrOpt(Gurax_Symbol(indices));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, ArgMax)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_ArgMax(argument, iteratorThis);
}

Value* VType_Iterator::Method_ArgMax(Argument& argument, Iterator& iteratorThis)
{
	if (argument.IsSet(Gurax_Symbol(lastIndex))) {
		Int idxFound = 0;
		RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::LessThanOrEqualTo>(&idxFound));
		return pValue? new Value_Number(idxFound) : Value::nil();
	} else if (argument.IsSet(Gurax_Symbol(indices))) {
		NumList<Int> idxFoundList;
		idxFoundList.reserve(16);
		RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::LessThan>(idxFoundList));
		return pValue? new Value_List(ValueTypedOwner::CreateFromNumList<Int>(idxFoundList)) : Value::nil();
	} else {
		Int idxFound = 0;
		RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::LessThan>(&idxFound));
		return pValue? new Value_Number(idxFound) : Value::nil();
	}
}

// Iterator#ArgMin():[lastIndex,indices]
Gurax_DeclareMethod(Iterator, ArgMin)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(lastIndex));
	DeclareAttrOpt(Gurax_Symbol(indices));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, ArgMin)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_ArgMin(argument, iteratorThis);
}

Value* VType_Iterator::Method_ArgMin(Argument& argument, Iterator& iteratorThis)
{
	if (argument.IsSet(Gurax_Symbol(lastIndex))) {
		Int idxFound = 0;
		RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::GreaterThanOrEqualTo>(&idxFound));
		return pValue? new Value_Number(idxFound) : Value::nil();
	} else if (argument.IsSet(Gurax_Symbol(indices))) {
		NumList<Int> idxFoundList;
		idxFoundList.reserve(16);
		RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::GreaterThan>(idxFoundList));
		return pValue? new Value_List(ValueTypedOwner::CreateFromNumList<Int>(idxFoundList)) : Value::nil();
	} else {
		Int idxFound = 0;
		RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::GreaterThan>(&idxFound));
		return pValue? new Value_Number(idxFound) : Value::nil();
	}
}

// Iterator#Before(criteria) {block?}
Gurax_DeclareMethod(Iterator, Before)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Before)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Until(processor, argument, iteratorSrc, false);
}

// Iterator#Combination(n as Number) {block?}
Gurax_DeclareMethod(Iterator, Combination)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that generates lists that contain elements picked up
from the original iterable in a combination rule.
)""");
}

Gurax_ImplementMethod(Iterator, Combination)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<ValueTypedOwner> pValueTypedOwner(ValueTypedOwner::CreateFromIterator(valueThis.GetIterator(), false));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return VType_Iterator::Method_Combination(processor, argument, *pValueTypedOwner);
}

Value* VType_Iterator::Method_Combination(
	Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner)
{
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (n > valueTypedOwner.GetSize()) {
		Error::Issue(ErrorType::RangeError, "range over");
		return Value::nil();
	}
	RefPtr<Iterator> pIterator(new Iterator_Combination(valueTypedOwner.GetValueOwnerReference(), n));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Contains(value)
Gurax_DeclareMethod(Iterator, Contains)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the iterable contains an element that equals to the given argument `value`.
)""");
}

Gurax_ImplementMethod(Iterator, Contains)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	if (!iteratorThis.MustBeFinite()) return Value::nil();
	return new Value_Bool(iteratorThis.Contains(value));
}

// Iterator#Count(value):map
Gurax_DeclareMethod(Iterator, Count)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns the number of elements in the iterable that equals to the given argument `value`.
)""");
}

Gurax_ImplementMethod(Iterator, Count)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	size_t cnt = iteratorThis.Count(value);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// Iterator#CountFalse()
Gurax_DeclareMethod(Iterator, CountFalse)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns the number of elements in the iterable that are recognized as `false`.
)""");
}

Gurax_ImplementMethod(Iterator, CountFalse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	size_t cnt = iteratorThis.CountFalse();
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// Iterator#CountIf(criteria as Function)
Gurax_DeclareMethod(Iterator, CountIf)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("criteria", VTYPE_Function, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns the number of elements in the iterable that passes the specified criteria function.
The function `criteria` takes a single argument and returns a `Bool` value
after determininig if the given value passes its criteria.
)""");
}

Gurax_ImplementMethod(Iterator, CountIf)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	const Function& criteria = args.PickFunction();
	// Function body
	size_t cnt = iteratorThis.CountIf(processor, criteria);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// Iterator#CountTrue()
Gurax_DeclareMethod(Iterator, CountTrue)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns the number of elements in the iterable that are recognized as `true`.
)""");
}

Gurax_ImplementMethod(Iterator, CountTrue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	size_t cnt = iteratorThis.CountTrue();
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// Iterator#Cycle(n? as Number) {block?}
Gurax_DeclareMethod(Iterator, Cycle)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Cycle)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<ValueTypedOwner> pValueTypedOwner(ValueTypedOwner::CreateFromIterator(valueThis.GetIterator(), false));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return VType_Iterator::Method_Cycle_List(processor, argument, *pValueTypedOwner);
}

Value* VType_Iterator::Method_Cycle_List(
	Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner)
{
	if (valueTypedOwner.IsEmpty()) {
		Error::Issue(ErrorType::RangeError, "empty list can not be specified");
		return Value::nil();
	}
	// Arguments
	ArgPicker args(argument);
	Int n = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Cycle_List(valueTypedOwner.GetValueOwnerReference(), n));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Each() {`block?}
Gurax_DeclareMethod(Iterator, Each)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce, DeclBlock::Flag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"""(
Repeats the process in `block` for each element in the target iterable instance.
The `block` takes block parameters in one of the following forms:

- `iterable#Each { .. }` .. no parameter
- `iterable#Each {|elem| .. }` .. Element instance
- `iterable#Each {|elem, pos| .. }` .. Element instance and index counter

If `block` is not specified, it creates an iterator that iterates each item in the iterable.
When the iterable is an iterator, its cloned value will be created.
)""");
}

Gurax_ImplementMethod(Iterator, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	if (!argument.HasExprOfBlock()) return valueThis.Reference();
	return iteratorThis.Each(processor, *argument.GetExprOfBlock(), argument.GetFlags());
}

// Iterator#Filter(criteria?) {block?}
Gurax_DeclareMethod(Iterator, Filter)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Filter)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Filter(processor, argument, iteratorSrc);
}

Value* VType_Iterator::Method_Filter(Processor& processor, Argument& argument, Iterator& iteratorSrc)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Value> pValue(args.IsValid()? args.PickValue().Reference() : Value::nil());
	// Function body
	RefPtr<Iterator> pIterator;
	if (!pValue->IsValid()) {
		pIterator.reset(new Iterator_SkipFalse(iteratorSrc.Reference()));
	} else if (pValue->IsType(VTYPE_Function)) {
		pIterator.reset(
			new Iterator_FilterWithFunc(
				processor.Reference(), Value_Function::GetFunction(*pValue).Reference(),
				iteratorSrc.Reference()));
	} else if (pValue->IsIterable()) {
		pIterator.reset(
			new Iterator_FilterWithIter(pValue->GenIterator(), iteratorSrc.Reference()));
	} else {
		Error::Issue(ErrorType::ValueError, "function or iterable must be specified");
		return Value::nil();
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Find(criteria?):[index]
Gurax_DeclareMethod(Iterator, Find)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(index));
	DeclareArg("criteria", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Find)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Find(processor, argument, iteratorSrc);
}

Value* VType_Iterator::Method_Find(Processor& processor, Argument& argument, Iterator& iteratorSrc)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Value> pValue(args.IsValid()? args.PickValue().Reference() : Value::nil());
	bool indexFlag = argument.IsSet(Gurax_Symbol(index));
	// Function body
	RefPtr<Value> pValueRtn(Value::nil());
	if (!pValue->IsValid()) {
		for (size_t idx = 0; ; idx++) {
			RefPtr<Value> pValueSrc(iteratorSrc.NextValue());
			if (!pValueSrc) break;
			if (pValueSrc->GetBool()) {
				pValueRtn.reset(indexFlag? new Value_Number(idx) : pValueSrc.release());
				break;
			}
		}
	} else if (pValue->IsType(VTYPE_Function)) {
		Function& func = Value_Function::GetFunction(*pValue);
		RefPtr<Frame> pFrame(func.LockFrameOuter());
		if (!pFrame) return Value::nil();
		RefPtr<Argument> pArgument(new Argument(processor, func));
		for (size_t idx = 0; ; idx++) {
			RefPtr<Value> pValueSrc(iteratorSrc.NextValue());
			if (!pValueSrc) break;
			if (pArgument->HasArgSlot()) {
				ArgFeeder args(*pArgument, *pFrame);
				if (!args.FeedValue(processor, pValueSrc.Reference())) return Value::nil();
				if (args.IsValid() && !args.FeedValue(processor, new Value_Number(idx))) return Value::nil();
			}
			RefPtr<Value> pValueResult(func.Eval(processor, *pArgument));
			if (pValueResult->GetBool()) {
				pValueRtn.reset(indexFlag? new Value_Number(idx) : pValueSrc.release());
				break;
			}
		}
	} else if (pValue->IsIterable()) {
		RefPtr<Iterator> pIteratorCriteria(pValue->GenIterator());
		for (size_t idx = 0; ; idx++) {
			RefPtr<Value> pValueSrc(iteratorSrc.NextValue());
			if (!pValueSrc) break;
			RefPtr<Value> pValueCriteria(pIteratorCriteria->NextValue());
			if (!pValueCriteria) break;
			if (pValueCriteria->GetBool()) {
				pValueRtn.reset(indexFlag? new Value_Number(idx) : pValueSrc.release());
				break;
			}
		}
	} else {
		Error::Issue(ErrorType::ValueError, "function or iterable must be specified");
		return Value::nil();
	}
	return pValueRtn.release();
}

// Iterator#Flatten():[dfs,bfs] {block?}
Gurax_DeclareMethod(Iterator, Flatten)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(dfs));
	DeclareAttrOpt(Gurax_Symbol(bfs));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Flatten)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	if (!iteratorSrc.MustBeFinite()) return Value::nil();
	return VType_Iterator::Method_Flatten(processor, argument, iteratorSrc);
}

Value* VType_Iterator::Method_Flatten(Processor& processor, Argument& argument, Iterator& iteratorSrc)
{
	// Arguments
	SearchMode searchMode =
		argument.IsSet(Gurax_Symbol(dfs))? SearchMode::DepthFirst :
		argument.IsSet(Gurax_Symbol(bfs))? SearchMode::BreadthFirst :
		SearchMode::DepthFirst;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Flatten(iteratorSrc.Reference(), searchMode));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Fold(size as Number, advance? as Number):map:[iterItem,neat] {block?}
Gurax_DeclareMethod(Iterator, Fold)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("advance", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(iterItem));
	DeclareAttrOpt(Gurax_Symbol(neat));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");

}

Gurax_ImplementMethod(Iterator, Fold)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Fold(processor, argument, iteratorSrc);
}

Value* VType_Iterator::Method_Fold(Processor& processor, Argument& argument, Iterator& iteratorSrc)
{
	// Arguments
	ArgPicker args(argument);
	size_t nSize = args.PickNumberPos<size_t>();
	size_t nAdvance = args.IsValid()? args.PickNumberPos<size_t>() : nSize;
	if (Error::IsIssued()) return Value::nil();
	bool itemAsIterFlag = argument.IsSet(Gurax_Symbol(iterItem));
	bool neatFlag = argument.IsSet(Gurax_Symbol(neat));
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Fold(
								iteratorSrc.Reference(), nSize, nAdvance, itemAsIterFlag, neatFlag));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Head(n:nil as Number):map {block?}
Gurax_DeclareMethod(Iterator, Head)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::Nil);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Head)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	if (!args.IsValid()) return argument.ReturnIterator(processor, iteratorSrc.Reference());
	size_t n = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Head(iteratorSrc.Reference(), n));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Join(sep? as String):map
Gurax_DeclareMethod(Iterator, Join)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("sep", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	StringStyle::DeclareAttrOpt(*this);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `String` that joins `String` elements from the iterable with a separator `sep`.
Elements that are not `String` are converted to `String` before the jointing.
)""");
}

Gurax_ImplementMethod(Iterator, Join)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	const char* sep = args.IsValid()? args.PickString() : "";
	StringStyle ss(StringStyle::ToFlags(argument));
	// Function body
	String str;
	iteratorThis.Join(str, sep, ss);
	return new Value_String(str);
}

// Iterator#Joinb()
Gurax_DeclareMethod(Iterator, Joinb)
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Binary` that joins `Binary` elements from the iterable.
An error is issued if elements other than `Binary` are found.
)""");
}

Gurax_ImplementMethod(Iterator, Joinb)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	// Function body
	Binary buff;
	if (!iteratorThis.Joinb(buff)) return Value::nil();
	return new Value_Binary(buff);
}

// Iterator#Map(func as Function) {block?}
Gurax_DeclareMethod(Iterator, Map)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("func", VTYPE_Function, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Map)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#Max()
Gurax_DeclareMethod(Iterator, Max)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Max)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::LessThan>());
	return pValue? pValue.release() : Value::nil();
}

// Iterator#Mean()
Gurax_DeclareMethod(Iterator, Mean)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Mean)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.Mean(processor);
}

// Iterator#Min()
Gurax_DeclareMethod(Iterator, Min)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Min)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	RefPtr<Value> pValue(iteratorThis.FindMinMax<Value::GreaterThan>());
	return pValue? pValue.release() : Value::nil();
}

// Iterator#NilTo(replace) {block?}
Gurax_DeclareMethod(Iterator, NilTo)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, NilTo)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#Offset(offset as Number):map:[raise] {block?}
Gurax_DeclareMethod(Iterator, Offset)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareBlock(BlkOccur::Once);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Offset)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	Int offset = args.PickNumberNonNeg<Int>();
	bool raiseFlag = argument.IsSet(Gurax_Symbol(raise));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Offset(iteratorThis.Reference(), offset, raiseFlag));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Or()
Gurax_DeclareMethod(Iterator, Or)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Or)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.Or();
}

// Iterator#Pack(format as String)
Gurax_DeclareMethod(Iterator, Pack)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Pack)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#Permutation(n? as Number) {block?}
Gurax_DeclareMethod(Iterator, Permutation)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that generates lists that contain elements picked up
from the original iterable in a permutation rule.
)""");
}

Gurax_ImplementMethod(Iterator, Permutation)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<ValueTypedOwner> pValueTypedOwner(ValueTypedOwner::CreateFromIterator(valueThis.GetIterator(), false));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return VType_Iterator::Method_Permutation(processor, argument, *pValueTypedOwner);
}

Value* VType_Iterator::Method_Permutation(
	Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner)
{
	// Arguments
	ArgPicker args(argument);
	bool validFlag_n = false;
	size_t n = (validFlag_n = args.IsValid())? args.PickNumberPos<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (n > valueTypedOwner.GetSize()) {
		Error::Issue(ErrorType::RangeError, "range over");
		return Value::nil();
	}
	RefPtr<Iterator> pIterator;
	if (validFlag_n && n < valueTypedOwner.GetSize()) {
		pIterator.reset(new Iterator_PartialPermutation(
							valueTypedOwner.GetValueOwnerReference(), n));
	} else {
		pIterator.reset(new Iterator_Permutation(
							valueTypedOwner.GetValueOwnerReference()));
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#PingPong(n? as Number):[sticky,sticky@top,sticky@btm] {block?}
Gurax_DeclareMethod(Iterator, PingPong)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(sticky));
	DeclareAttrOpt(Gurax_Symbol(sticky_at_top));
	DeclareAttrOpt(Gurax_Symbol(sticky_at_btm));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, PingPong)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<ValueTypedOwner> pValueTypedOwner(ValueTypedOwner::CreateFromIterator(valueThis.GetIterator(), false));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return VType_Iterator::Method_PingPong(processor, argument, *pValueTypedOwner);
}

Value* VType_Iterator::Method_PingPong(
	Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner)
{
	if (valueTypedOwner.IsEmpty()) {
		Error::Issue(ErrorType::RangeError, "empty list can not be specified");
		return Value::nil();
	}
	// Arguments
	ArgPicker args(argument);
	Int n = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	bool stickyFlag = argument.IsSet(Gurax_Symbol(sticky));
	bool stickyFlagTop = stickyFlag || argument.IsSet(Gurax_Symbol(sticky_at_top));
	bool stickyFlagBtm = stickyFlag || argument.IsSet(Gurax_Symbol(sticky_at_btm));
	// Function body
	RefPtr<Iterator> pIterator;
	if (valueTypedOwner.GetSize() >= 2) {
		pIterator.reset(new Iterator_PingPong(valueTypedOwner.GetValueOwnerReference(), n,
											stickyFlagTop, stickyFlagBtm));
	} else if (n < 0) {
		pIterator.reset(new Iterator_Const(valueTypedOwner.GetValueOwner().front()->Reference()));
	} else {
		pIterator.reset(new Iterator_ConstN(valueTypedOwner.GetValueOwner().front()->Reference(), n));
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Prod()
Gurax_DeclareMethod(Iterator, Prod)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Prod)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.Prod(processor);
}

// Iterator#Rank(directive?):[stable] {block?}
Gurax_DeclareMethod(Iterator, Rank)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("directive", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(stable));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Rank)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#Reduce(accum) {block}
Gurax_DeclareMethod(Iterator, Reduce)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("accum", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::Once);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Reduce)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#Replace(value, replace) {block?}
Gurax_DeclareMethod(Iterator, Replace)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Replace)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#Reverse() {block?}
Gurax_DeclareMethod(Iterator, Reverse)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Reverse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<ValueTypedOwner> pValueTypedOwner(ValueTypedOwner::CreateFromIterator(valueThis.GetIterator(), false));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return VType_Iterator::Method_Reverse(processor, argument, *pValueTypedOwner);
}

Value* VType_Iterator::Method_Reverse(
	Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner)
{
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Reverse(valueTypedOwner.GetValueOwnerReference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#RoundOff(threshold? as number) {block?}
Gurax_DeclareMethod(Iterator, RoundOff)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("threshold", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, RoundOff)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
#endif
	return Value::nil();
}

// Iterator#RunLength() {block?}
Gurax_DeclareMethod(Iterator, RunLength)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, RunLength)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_RunLength(iteratorSrc.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Since(criteria) {block?}
Gurax_DeclareMethod(Iterator, Since)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Since)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Since(processor, argument, iteratorSrc, true);
}

Value* VType_Iterator::Method_Since(Processor& processor, Argument& argument,
									Iterator& iteratorSrc, bool includeFirstFlag)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Value> pValue(args.PickValue().Reference());
	// Function body
	RefPtr<Iterator> pIterator;
	if (pValue->IsType(VTYPE_Function)) {
		pIterator.reset(
			new Iterator_SinceWithFunc(
				processor.Reference(), Value_Function::GetFunction(*pValue).Reference(),
				iteratorSrc.Reference(), includeFirstFlag));
	} else if (pValue->IsIterable()) {
			pIterator.reset(
			new Iterator_SinceWithIter(pValue->GenIterator(), iteratorSrc.Reference(), includeFirstFlag));
	} else {
		Error::Issue(ErrorType::ValueError, "function or iterable must be specified");
		return Value::nil();
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#SkipFalse() {block?}
Gurax_DeclareMethod(Iterator, SkipFalse)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, SkipFalse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_SkipFalse(iteratorSrc.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#SkipNil() {block?}
Gurax_DeclareMethod(Iterator, SkipNil)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, SkipNil)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_SkipNil(iteratorSrc.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Sort(directive?, keys[]?):[stable] {block?}
Gurax_DeclareMethod(Iterator, Sort)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("directive", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("keys", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	DeclareAttrOpt(Gurax_Symbol(stable));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Sort)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<ValueTypedOwner> pValueTypedOwner(ValueTypedOwner::CreateFromIterator(valueThis.GetIterator(), false));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return VType_Iterator::Method_Sort(processor, argument, *pValueTypedOwner);
}

Value* VType_Iterator::Method_Sort(
	Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner)
{
	// Arguments
	ArgPicker args(argument);
	bool validFlag_directive = false;
	bool validFlag_keys = false;
	const Value& directive = (validFlag_directive = args.IsValid())? args.PickValue() : Value::C_nil();
	const ValueList& keys = (validFlag_keys = args.IsValid())? args.PickList() : ValueList::Empty;
	bool stableFlag = argument.IsSet(Gurax_Symbol(stable));
	// Function body
	RefPtr<ValueTypedOwner> pValueTypedOwner;
	RefPtr<ValueOwner> pValueOwner;
	if (validFlag_keys) {
		if (valueTypedOwner.GetSize() < keys.size()) {
			Error::Issue(ErrorType::RangeError, "the length of keys must be equal to that of values");
			return Value::nil();
		}
		pValueOwner.reset(new ValueOwner());
		pValueOwner->reserve(valueTypedOwner.GetSize());
		auto ppValueKey = keys.begin();
		auto ppValue = valueTypedOwner.GetValueOwner().begin();
		for ( ; ppValueKey != keys.end(); ppValueKey++, ppValue++) {
			pValueOwner->push_back(new Value_KeyValuePair((*ppValueKey)->Reference(), (*ppValue)->Reference()));
		}
	} else {
		pValueTypedOwner.reset(valueTypedOwner.Clone());
		pValueOwner.reset(pValueTypedOwner->GetValueOwnerToSort().Reference());
	}
	if (!validFlag_directive) {
		if (stableFlag) {
			pValueOwner->StableSort(SortOrder::Ascend);
		} else {
			pValueOwner->Sort(SortOrder::Ascend);
		}
	} else if (directive.IsType(VTYPE_Expr)) {
		RefPtr<Value_Symbol> pValueCasted(directive.Cast<Value_Symbol>(processor));
		if (!pValueCasted) return Value::nil();
		const Symbol* pSymbol = dynamic_cast<const Value_Symbol&>(*pValueCasted).GetSymbol();
		SortOrder sortOrder =
			pSymbol->IsIdentical(Gurax_Symbol(ascend))? SortOrder::Ascend :
			pSymbol->IsIdentical(Gurax_Symbol(descend))? SortOrder::Descend :
			SortOrder::None;
		if (sortOrder == SortOrder::None) {
			Error::Issue(ErrorType::ValueError, "acceptable symbol is `ascend or `descend");
			return Value::nil();
		}
		if (stableFlag) {
			pValueOwner->StableSort(sortOrder);
		} else {
			pValueOwner->Sort(sortOrder);
		}
	} else if (directive.IsType(VTYPE_Function)) {
		const Function& function = dynamic_cast<const Value_Function&>(directive).GetFunction();
		if (stableFlag) {
			pValueOwner->StableSort(processor, function);
		} else {
			pValueOwner->Sort(processor, function);
		}
	} else {
		Error::Issue(ErrorType::ValueError, "argument 'directive' must be a symbol or a function");
		return Value::nil();
	}
	if (Error::IsIssued()) return Value::nil();
	if (validFlag_keys) {
		RefPtr<ValueOwner> pValueOwnerResult(new ValueOwner());
		pValueOwnerResult->reserve(pValueOwner->size());
		for (Value* pValue : *pValueOwner) {
			pValueOwnerResult->push_back(pValue->GetValue().Reference());
		}
		pValueTypedOwner.reset(new ValueTypedOwner(pValueOwnerResult.release()));
	}
	return new Value_List(pValueTypedOwner.release());
}

// Iterator#Std():[p]
Gurax_DeclareMethod(Iterator, Std)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(p));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Std)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.Std(processor);
}

// Iterator#Sum()
Gurax_DeclareMethod(Iterator, Sum)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Sum)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.Sum(processor);
}

// Iterator#Tail(n as Number):map {block?}
Gurax_DeclareMethod(Iterator, Tail)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Tail)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iterator = valueThis.GetIterator();
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<ValueOwner> pValueOwner(iterator.Tail(n));
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnIterator(processor, new Iterator_Each(pValueOwner.release()));
}

// Iterator#Uniq() {block?}
Gurax_DeclareMethod(Iterator, Uniq)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Uniq)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Uniq(iteratorSrc.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Until(criteria) {block?}
Gurax_DeclareMethod(Iterator, Until)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Until)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_Until(processor, argument, iteratorSrc, true);
}

Value* VType_Iterator::Method_Until(Processor& processor, Argument& argument,
									Iterator& iteratorSrc, bool includeLastFlag)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Value> pValue(args.PickValue().Reference());
	// Function body
	RefPtr<Iterator> pIterator;
	if (pValue->IsType(VTYPE_Function)) {
		pIterator.reset(
			new Iterator_UntilWithFunc(
				processor.Reference(), Value_Function::GetFunction(*pValue).Reference(),
				iteratorSrc.Reference(), includeLastFlag));
	} else if (pValue->IsIterable()) {
		pIterator.reset(
			new Iterator_UntilWithIter(pValue->GenIterator(), iteratorSrc.Reference(), includeLastFlag));
	} else {
		Error::Issue(ErrorType::ValueError, "function or iterable must be specified");
		return Value::nil();
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// Iterator#Var():[p]
Gurax_DeclareMethod(Iterator, Var)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(p));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Var)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorThis = valueThis.GetIterator();
	// Function body
	return iteratorThis.Var(processor);
}

// Iterator#While(criteria) {block?}
Gurax_DeclareMethod(Iterator, While)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, While)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Iterator& iteratorSrc = valueThis.GetIterator();
	// Function body
	return VType_Iterator::Method_While(processor, argument, iteratorSrc);
}

Value* VType_Iterator::Method_While(Processor& processor, Argument& argument, Iterator& iteratorSrc)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Value> pValue(args.PickValue().Reference());
	// Function body
	RefPtr<Iterator> pIterator;
	if (pValue->IsType(VTYPE_Function)) {
		pIterator.reset(
			new Iterator_WhileWithFunc(
				processor.Reference(), Value_Function::GetFunction(*pValue).Reference(),
				iteratorSrc.Reference()));
	} else if (pValue->IsIterable()) {
		pIterator.reset(
			new Iterator_WhileWithIter(pValue->GenIterator(), iteratorSrc.Reference()));
	} else {
		Error::Issue(ErrorType::ValueError, "function or iterable must be specified");
		return Value::nil();
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// #len
Gurax_DeclareProperty_R(Iterator, len)
{
	Declare(VTYPE_Number, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
The number of elements in the iterator.
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
イテレータ中の要素数。
)""");
}

Gurax_ImplementPropertyGetter(Iterator, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Iterator& iterator = valueThis.GetIterator();
	return iterator.IsLenDetermined()? new Value_Number(iterator.GetLength()) : Value::nil();
}

// Iterator#tuple
Gurax_DeclareProperty_R(Iterator, tuple)
{
	Declare(VTYPE_Tuple, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Tuple` from the `Iterator`.
)""");
}

Gurax_ImplementPropertyGetter(Iterator, tuple)
{
	auto& valueThis = GetValueThis(valueTarget);
	Iterator& iterator = valueThis.GetIterator();
	RefPtr<ValueOwner> pValueOwner(ValueOwner::CreateFromIterator(iterator, false));
	if (Error::IsIssued()) return Value::nil();
	return new Value_Tuple(pValueOwner.release());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Iterator |+| Iterator
Gurax_ImplementOpBinary(Concat, Iterator, Iterator)
{
	Iterator& iteratorL = Value_Iterator::GetIterator(valueL);
	Iterator& iteratorR = Value_Iterator::GetIterator(valueR);
	return new Value_Iterator(new Iterator_Concat(iteratorL.Reference(), iteratorR.Reference()));
}

//------------------------------------------------------------------------------
// VType_Iterator
//------------------------------------------------------------------------------
VType_Iterator VTYPE_Iterator("Iterator");

void VType_Iterator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method specific to Iterator
	Assign(Gurax_CreateMethod(Iterator, IsFinite));
	Assign(Gurax_CreateMethod(Iterator, IsInfinite));
	Assign(Gurax_CreateMethod(Iterator, IsLenDetermined));
	Assign(Gurax_CreateMethod(Iterator, IsRewindable));
	Assign(Gurax_CreateMethod(Iterator, MakeRewindable));
	Assign(Gurax_CreateMethod(Iterator, NextValue));
	Assign(Gurax_CreateMethod(Iterator, Rewind));
	Assign(Gurax_CreateMethod(Iterator, Skip));
	// Assignment of method common to both Iterator and List
	Assign(Gurax_CreateMethod(Iterator, After));
	Assign(Gurax_CreateMethod(Iterator, Align));
	Assign(Gurax_CreateMethod(Iterator, And));
	Assign(Gurax_CreateMethod(Iterator, ArgMax));
	Assign(Gurax_CreateMethod(Iterator, ArgMin));
	Assign(Gurax_CreateMethod(Iterator, Before));
	Assign(Gurax_CreateMethod(Iterator, Combination));
	Assign(Gurax_CreateMethod(Iterator, Contains));
	Assign(Gurax_CreateMethod(Iterator, Count));
	Assign(Gurax_CreateMethod(Iterator, CountFalse));
	Assign(Gurax_CreateMethod(Iterator, CountIf));
	Assign(Gurax_CreateMethod(Iterator, CountTrue));
	Assign(Gurax_CreateMethod(Iterator, Cycle));
	Assign(Gurax_CreateMethod(Iterator, Each));
	Assign(Gurax_CreateMethod(Iterator, Filter));
	Assign(Gurax_CreateMethod(Iterator, Find));
	Assign(Gurax_CreateMethod(Iterator, Flatten));
	Assign(Gurax_CreateMethod(Iterator, Fold));
	Assign(Gurax_CreateMethod(Iterator, Head));
	Assign(Gurax_CreateMethod(Iterator, Join));
	Assign(Gurax_CreateMethod(Iterator, Joinb));
	Assign(Gurax_CreateMethod(Iterator, Map));
	Assign(Gurax_CreateMethod(Iterator, Max));
	Assign(Gurax_CreateMethod(Iterator, Mean));
	Assign(Gurax_CreateMethod(Iterator, Min));
	Assign(Gurax_CreateMethod(Iterator, NilTo));
	Assign(Gurax_CreateMethod(Iterator, Offset));
	Assign(Gurax_CreateMethod(Iterator, Or));
	Assign(Gurax_CreateMethod(Iterator, Pack));
	Assign(Gurax_CreateMethod(Iterator, Permutation));
	Assign(Gurax_CreateMethod(Iterator, PingPong));
	Assign(Gurax_CreateMethod(Iterator, Prod));
	Assign(Gurax_CreateMethod(Iterator, Rank));
	Assign(Gurax_CreateMethod(Iterator, Reduce));
	Assign(Gurax_CreateMethod(Iterator, Replace));
	Assign(Gurax_CreateMethod(Iterator, Reverse));
	Assign(Gurax_CreateMethod(Iterator, RoundOff));
	Assign(Gurax_CreateMethod(Iterator, RunLength));
	Assign(Gurax_CreateMethod(Iterator, Since));
	Assign(Gurax_CreateMethod(Iterator, SkipFalse));
	Assign(Gurax_CreateMethod(Iterator, SkipNil));
	Assign(Gurax_CreateMethod(Iterator, Sort));
	Assign(Gurax_CreateMethod(Iterator, Std));
	Assign(Gurax_CreateMethod(Iterator, Sum));
	Assign(Gurax_CreateMethod(Iterator, Tail));
	Assign(Gurax_CreateMethod(Iterator, Uniq));
	Assign(Gurax_CreateMethod(Iterator, Until));
	Assign(Gurax_CreateMethod(Iterator, Var));
	Assign(Gurax_CreateMethod(Iterator, While));
	// Assignment of property
	Assign(Gurax_CreateProperty(Iterator, len));
	Assign(Gurax_CreateProperty(Iterator, tuple));
	// Assignment of operator
	Gurax_AssignOpBinary(Concat, Iterator, Iterator);
}

Value* VType_Iterator::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_List)) {
		return new Value_Iterator(Value_List::GetValueTypedOwner(value).GenerateIterator());
	} else if (value.IsType(VTYPE_Tuple)) {
		return new Value_Iterator(new Iterator_Each(Value_Tuple::GetValueOwner(value).Reference()));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Iterator
//------------------------------------------------------------------------------
VType& Value_Iterator::vtype = VTYPE_Iterator;

String Value_Iterator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetIterator().ToString(StringStyle::Quote_NilVisible));
}

bool Value_Iterator::IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const
{
	return DeclCallable::IsMappable(declArg, flags);
}

void Value_Iterator::UpdateMapMode(Argument& argument) const
{
	argument.SetMapMode(Argument::MapMode::ToIter);
}

bool Value_Iterator::FeedExpandToArgument(Processor& processor, Frame& frame, Argument& argument)
{
	Iterator& iterator = GetIterator();
	for (;;) {
		RefPtr<Value> pValueElem(iterator.NextValue());
		if (!pValueElem) break;
		if (!argument.CheckArgSlotToFeed()) return false;
		argument.FeedValue(processor, frame, pValueElem.release());
		if (Error::IsIssued()) return false;
	}
	return !Error::IsIssued();
}

const DeclCallable* Value_Iterator::GetDeclCallable()
{
	RefPtr<Value> pValueElem(GetIterator().PeekValue());
	return pValueElem? pValueElem->GetDeclCallable() : DeclCallable::Wildcard.get();
}

void Value_Iterator::DoCall(Processor& processor, Argument& argument)
{
	const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
	if (pPUnitOfCaller->GetDiscardValueFlag()) {
		if (GetIterator().MustBeFinite()) {
			for (;;) {
				RefPtr<Value> pValue(GetIterator().NextValue());
				if (!pValue) break;
				Value::Delete(pValue->Eval(processor, argument));
			}
		}
	} else {
		RefPtr<Value> pValueRtn(Eval(processor, argument));
		if (Error::IsIssued()) return;
		processor.PushValue(pValueRtn.release());
	}
	processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
}

Value* Value_Iterator::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<Iterator> pIterator(new Iterator_IteratorEvaluator(
								processor.Reference(), GetIterator().Reference(), argument.Reference()));
	return new Value_Iterator(pIterator.release());
}

bool Value_Iterator::DoEmptyIndexGet(Value** ppValue) const
{
	Iterator& iterator = GetIterator();
	if (!iterator.MustBeFinite()) return false;
	*ppValue = new Value_List(ValueTypedOwner::CreateFromIterator(iterator, false));
	return true;
}

bool Value_Iterator::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "index-access is not supported");
	return false;
}

bool Value_Iterator::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError, "index-access is not supported");
	return false;
}

bool Value_Iterator::DoSingleIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "index-access is not supported");
	return false;
}

Iterator* Value_Iterator::DoGenIterator() const
{
	return GetIterator().Reference();
}

}
