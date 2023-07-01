//==============================================================================
// VType_List.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {


//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview



${help.ComposePropertyHelp(List, `en)}

# Operator

The operator `in` checks if a specified value is contained in the `List`.

- `Any in List` ... Returns `true` if the `List` instance contains the `Any` instance.

The operator `|+|` concats a `List` and another value. It works in the same way as `List#Append()` method.

- `List |+| List` ... Creates a `List` instance that combines the two `List` instances.
- `List |+| Iterator` ... Creates a `List` instance that appends elements of `Iterator` at the beginning of the left-sided `List` instance.
- `Any |+| List` ... Creates a `List` instance that appends `Any` instance at the beginning of the right-sided `List` instance.
- `List |+| Any` ... Creates a `List` instance that appends `Any` instance at the end of the left-sided `List` instance.


# Cast Operation

The following cast operations are prepared:

- `Iterator as List` ... Turns an `Iterator` into a `List`.
- `Array as List` ... Turns an `Array` into a `List`.
- `Tuple as List` ... Turns a `Tuple` into a `List`.


${help.ComposeConstructorHelp(List, `en)}

${help.ComposeMethodHelp(List, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of statement
//------------------------------------------------------------------------------
// @(callable?) {`block}
Gurax_DeclareStatementAlias(_at_, "@")
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("callable", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::Quote);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `List` instance after evaculating `block` as an element list.

```
@{1, 2, 3, 4, 5}                // generates [1, 2, 3, 4, 5]
@{'apple', 'orange', 'grape'}   // generates ['apple', 'orange', 'grape']
```

The element list can contain lists as follows:

```
@{[1, [2, 3]], [4, 5, 6]}       // generates [[1, [2, 3]], [4, 5, 6]]
```

You can also use brace brackets to specify inner lists.
This enables you to describe nested lists in a similar manner with C and Java.

```
@{{1, {2, 3}}, {4, 5, 6}}       // generates [[1, [2, 3]], [4, 5, 6]]
```

The argument `callable` is a callable object that is evaluated with each element of the list as arguments.

```
@(math.Abs) {-1, 3, 1, -2}     // generates [1, 3, 1, 2]
```

This has the same effect with follows:

```
@{math.Abs(-1), math.Abs(3), math.Abs(1), math.Abs(-2)}
```

The list creation with the callable is useful to create a list of structures. Consider the following structure:

```
Person = struct { name as String, age as Number }
```

The following code is to create a list of the structure:

```
@{Person('Taro', 23), Person('Hanako', 22), Person('Jiro', 25)}
```

Using the list creation with callable, this can be written as follows:

```
@(Person) {('Taro', 23), ('Hanako', 22), ('Jiro', 25)}
```
)""");
}

Gurax_ImplementStatement(_at_)
{
	ExprLink& exprLinkElem = exprCaller.GetExprOfBlock()->GetExprLinkElem();
	size_t nExprs = exprLinkElem.CountSequence();
	composer.Add_CreateList(nExprs, exprCaller);								// [List]
	if (exprCaller.GetExprParamFirst()) {
		exprCaller.GetExprParamFirst()->ComposeOrNil(composer);					// [List Car]
		for (Expr* pExpr = exprLinkElem.GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			composer.Add_Argument(exprCaller.GetAttr().Reference(), nullptr,
								  true, exprCaller);							// [List Car Argument]
			if (pExpr->IsType<Expr_Block>()) {
				// @{ .. {args*} .. }
				dynamic_cast<Expr_Block*>(pExpr)->GetExprLinkElem().ComposeWithinArgSlot(composer);
			} else {
				// @{ .. args .. }
				pExpr->ComposeWithinArgSlot(composer);
			}
			if (Error::IsIssued()) return;
			composer.Add_Call(exprCaller);										// [List Car Result]
			composer.Add_ListElem(1, false, false, exprCaller);					// [List Car]
		}
		composer.Add_DiscardValue(exprCaller);									// [List]
	} else {
		for (Expr* pExpr = exprLinkElem.GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			pExpr->ComposeWithinLister(composer);								// [List]
		}
	}
}

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// List.Zip(values+) {block?}
Gurax_DeclareClassMethod(List, Zip)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator generating lists that bind given argument values.
When the value is a list or an iterator, each item in it would be zipped.
)""");
}

Gurax_ImplementClassMethod(List, Zip)
{
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method specific to List
//-----------------------------------------------------------------------------
// List#Add(value+):reduce
Gurax_DeclareMethod(List, Add)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("value", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds values to `this` list.

```
[1, 2, 3].Add(4, 5, 6)        // generates [1, 2, 3, 4, 5, 6]
[1, 2, 3].Add([4, 5], [6, 7]) // generates [1, 2, 3, [4, 5], [6, 7]]
```
)""");
}

Gurax_ImplementMethod(List, Add)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	valueTypedOwner.Add(values);
	return argument.GetValueThis().Reference();
}

// List#Append(value+):reduce
Gurax_DeclareMethod(List, Append)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("value", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds values to `this` list.
If the added value is a list or an iterator, elements in it are added to the list.

```
[1, 2, 3].Append(4, 5, 6)        // generates [1, 2, 3, 4, 5, 6]
[1, 2, 3].Append([4, 5], [6, 7]) // generates [1, 2, 3, 4, 5, 6, 7]
```
)""");
}

Gurax_ImplementMethod(List, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	if (!valueTypedOwner.Append(values)) return Value::nil();
	return argument.GetValueThis().Reference();
}

// List#Clear():reduce
Gurax_DeclareMethod(List, Clear)
{
	Declare(VTYPE_List, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Clears all the elements of `this` list.
)""");
}

Gurax_ImplementMethod(List, Clear)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	valueTypedOwner.Clear();
	return argument.GetValueThis().Reference();
}

// List#Erase(pos* as Number):reduce
Gurax_DeclareMethod(List, Erase)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Erases elements at the specified indices.
)""");
}

Gurax_ImplementMethod(List, Erase)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	NumList<Int> posList = Value_Number::GetNumList<Int>(args.PickList());
	// Function body
	for (auto pPos = posList.begin(); pPos != posList.end(); pPos++) {
		if (*pPos < 0) *pPos += valueTypedOwner.GetSize();
	}
	posList.Sort(SortOrder::Descend).Unique();
	if (!valueTypedOwner.Erase(posList)) return Value::nil();
	return argument.GetValueThis().Reference();
}

// List#Get(pos as Number):map:flat:[raise]
Gurax_DeclareMethod(List, Get)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a value stored at the specified index in the list.
An error occurs when the index is out of range.
)""");
}

Gurax_ImplementMethod(List, Get)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	// Arguments
	ArgPicker args(argument);
	Int pos = args.PickNumber<Int>();
	if (Error::IsIssued()) return Value::nil();
	bool raiseFlag = argument.IsSet(Gurax_Symbol(raise));
	// Function body
	if (!valueOwner.FixPosition(&pos, raiseFlag)) return Value::nil();
	return valueOwner.Get(pos).Reference();
}

// List#Insert(pos as Number, values+):reduce
Gurax_DeclareMethod(List, Insert)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("elem", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Inserts items at the specified position in the list.
)""");
}

Gurax_ImplementMethod(List, Insert)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	Int pos = args.PickNumber<Int>();
	const ValueList& values = args.PickList();
	// Function body
	valueTypedOwner.Insert(pos, values);
	return argument.GetValueThis().Reference();
}

// List#IsEmpty()
Gurax_DeclareMethod(List, IsEmpty)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
A boolean value indicating whether the list is empty or not.
)""");
}

Gurax_ImplementMethod(List, IsEmpty)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetValueOwner().empty());
}

// List#Put(pos as Number, value:noMap as Any):reduce:map
Gurax_DeclareMethod(List, Put)
{
	Declare(VTYPE_List, Flag::Reduce | Flag::Map);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::NoMap);
	AddHelp(Gurax_Symbol(en), u8R"""(
Stores a value at the specified index in the list.
An error occurs when the index is out of range.
)""");
}

Gurax_ImplementMethod(List, Put)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	Int pos = args.PickNumber<Int>();
	const Value& value = args.PickValue();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	valueTypedOwner.Set(pos, value.Reference());
	return argument.GetValueThis().Reference();
}

// List#Shuffle(random? as Random):reduce
Gurax_DeclareMethod(List, Shuffle)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("random", VTYPE_Random, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Shuffle the order of the list content based on random numbers.
)""");
}

Gurax_ImplementMethod(List, Shuffle)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	Random& random = args.IsValid()? args.PickRandom() : Random::Global();
	// Function body
	valueTypedOwner.GetValueOwnerToSort().Shuffle(random);
	return argument.GetValueThis().Reference();
}

// List#Shift():[raise]
Gurax_DeclareMethod(List, Shift)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	AddHelp(Gurax_Symbol(en), u8R"""(
Shifts the elements of the list and returns the value of the shifted top element.
If the content of the list is `[1, 2, 3, 4]`,
it becomes `[2, 3, 4]` after calling this method. In default, no error occurs
even when the list is empty. To raise an error for executing this method on
an empty list, specify :raise attribute.
)""");
}

Gurax_ImplementMethod(List, Shift)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
	if (argument.IsSet(Gurax_Symbol(raise)) && valueTypedOwner.IsEmpty()) {
		Error::Issue(ErrorType::RangeError, "the list is empty");
		return Value::nil();
	}
	RefPtr<Value> pValue(valueTypedOwner.Shift());
	return pValue.release();
}

//-----------------------------------------------------------------------------
// Implementation of method common to both Iterator and List
//-----------------------------------------------------------------------------
// List#After(criteria) {block?}
Gurax_DeclareMethod(List, After)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, After)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Since(processor, argument, *pIteratorSrc, false);
}

// List#Align(n as Number, value? as Any):map {block?}
Gurax_DeclareMethod(List, Align)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Align)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Align(processor, argument, *pIteratorSrc);
}

// List#And()
Gurax_DeclareMethod(List, And)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, And)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->And();
}

// List#ArgMax():[lastIndex,indices]
Gurax_DeclareMethod(List, ArgMax)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(lastIndex));
	DeclareAttrOpt(Gurax_Symbol(indices));
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, ArgMax)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_ArgMax(argument, *pIteratorThis);
}

// List#ArgMin():[lastIndex,indices]
Gurax_DeclareMethod(List, ArgMin)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(lastIndex));
	DeclareAttrOpt(Gurax_Symbol(indices));
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, ArgMin)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_ArgMin(argument, *pIteratorThis);
}

// List#Before(criteria) {block?}
Gurax_DeclareMethod(List, Before)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Before)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Until(processor, argument, *pIteratorSrc, false);
}

// List#Combination(n as Number) {block?}
Gurax_DeclareMethod(List, Combination)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Combination)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	return VType_Iterator::Method_Combination(processor, argument, valueTypedOwner);
}

// List#Contains(value)
Gurax_DeclareMethod(List, Contains)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Contains)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	return new Value_Bool(valueTypedOwner.GetValueOwner().Contains(value));
}

// List#Count(value):map
Gurax_DeclareMethod(List, Count)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Count)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	size_t cnt = valueTypedOwner.GetValueOwner().Count(value);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// List#CountFalse()
Gurax_DeclareMethod(List, CountFalse)
{
	Declare(VTYPE_Number, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, CountFalse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
	size_t cnt = valueTypedOwner.GetValueOwner().CountFalse();
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// List#CountIf(criteria as Function)
Gurax_DeclareMethod(List, CountIf)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("criteria", VTYPE_Function, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, CountIf)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	const Function& criteria = args.PickFunction();
	// Function body
	size_t cnt = valueTypedOwner.GetValueOwner().CountIf(processor, criteria);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// List#CountTrue()
Gurax_DeclareMethod(List, CountTrue)
{
	Declare(VTYPE_Number, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, CountTrue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	// Function body
	size_t cnt = valueTypedOwner.GetValueOwner().CountTrue();
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(cnt);
}

// List#Cycle(n? as Number) {block?}
Gurax_DeclareMethod(List, Cycle)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Cycle)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	return VType_Iterator::Method_Cycle(processor, argument, valueTypedOwner);
}

// List#Each() {`block?}
Gurax_DeclareMethod(List, Each)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce, DeclBlock::Flag::Quote);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(valueThis.GenIterator());
	if (!pIterator) return Value::nil();
	return argument.ReturnIterator(processor, pIterator.release());
}

// List#Filter(criteria?) {block?}
Gurax_DeclareMethod(List, Filter)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Filter)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Filter(processor, argument, *pIteratorSrc);
}

// List#Find(criteria?):[index]
Gurax_DeclareMethod(List, Find)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(index));
	DeclareArg("criteria", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Find)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Find(processor, argument, *pIteratorSrc);
}

// List#Flatten():[dfs,bfs] {block?}
Gurax_DeclareMethod(List, Flatten)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(dfs));
	DeclareAttrOpt(Gurax_Symbol(bfs));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Flatten)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Flatten(processor, argument, *pIteratorSrc);
}

// List#Fold(size as number, advance? as number):map:[iterItem,neat] {block?}
Gurax_DeclareMethod(List, Fold)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("sizen", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("advance", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(iterItem));
	DeclareAttrOpt(Gurax_Symbol(neat));
	LinkHelp(VTYPE_Iterator, GetSymbol());

}

Gurax_ImplementMethod(List, Fold)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Fold(processor, argument, *pIteratorSrc);
}

// List#Head(n as number):map {block?}
Gurax_DeclareMethod(List, Head)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Head)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberNonNeg<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(
		new Iterator_Each(
			valueTypedOwner.GetValueOwnerReference(), 0, std::min(n, valueTypedOwner.GetSize())));
	return argument.ReturnIterator(processor, pIterator.release());
}

// List#Join(sep? as String):map
Gurax_DeclareMethod(List, Join)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("sep", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	StringStyle::DeclareAttrOpt(*this);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Join)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Arguments
	ArgPicker args(argument);
	const char* sep = args.IsValid()? args.PickString() : "";
	StringStyle ss(StringStyle::ToFlags(argument));
	// Function body
	String str;
	pIteratorThis->Join(str, sep, ss);
	return new Value_String(str);
}

// List#Joinb()
Gurax_DeclareMethod(List, Joinb)
{
	Declare(VTYPE_Binary, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Joinb)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	Binary buff;
	if (!pIteratorThis->Joinb(buff)) return Value::nil();
	return new Value_Binary(buff);
}

// List#Map(func as Function) {block?}
Gurax_DeclareMethod(List, Map)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("func", VTYPE_Function, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Map)
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

// List#Max()
Gurax_DeclareMethod(List, Max)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Max)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	RefPtr<Value> pValue(pIteratorThis->FindMinMax<Value::LessThan>());
	return pValue? pValue.release() : Value::nil();
}

// List#Mean()
Gurax_DeclareMethod(List, Mean)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Mean)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->Mean(processor);
}

// List#Min()
Gurax_DeclareMethod(List, Min)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Min)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	RefPtr<Value> pValue(pIteratorThis->FindMinMax<Value::GreaterThan>());
	return pValue? pValue.release() : Value::nil();
}

// List#NilTo(replace) {block?}
Gurax_DeclareMethod(List, NilTo)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, NilTo)
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

// List#Offset(offset as Number):map:[raise] {block?}
Gurax_DeclareMethod(List, Offset)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareBlock(BlkOccur::Once);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Offset)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	size_t offset = args.PickNumberNonNeg<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (argument.IsSet(Gurax_Symbol(raise))) {
		if (offset > valueTypedOwner.GetSize()) {
			Error::Issue(ErrorType::RangeError, "offset value exceeds the length of elements");
			return Value::nil();
		}
	}
	RefPtr<Iterator> pIterator(new Iterator_Each(valueTypedOwner.GetValueOwnerReference(), offset));
	return argument.ReturnIterator(processor, pIterator.release());
}

// List#Or()
Gurax_DeclareMethod(List, Or)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Or)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->Or();
}

// List#Pack(format as String)
Gurax_DeclareMethod(List, Pack)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Pack)
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

// List#Permutation(n? as Number) {block?}
Gurax_DeclareMethod(List, Permutation)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Permutation)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	return VType_Iterator::Method_Permutation(processor, argument, valueTypedOwner);
}

// List#PingPong(n? as Number):[sticky,sticky@top,sticky@btm] {block?}
Gurax_DeclareMethod(List, PingPong)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(sticky));
	DeclareAttrOpt(Gurax_Symbol(sticky_at_top));
	DeclareAttrOpt(Gurax_Symbol(sticky_at_btm));
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, PingPong)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	return VType_Iterator::Method_PingPong(processor, argument, valueTypedOwner);
}

// List#Prod()
Gurax_DeclareMethod(List, Prod)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Prod)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->Prod(processor);
}

// List#Rank(directive?):[stable] {block?}
Gurax_DeclareMethod(List, Rank)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("directive", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(stable));
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Rank)
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

// List#Reduce(accum) {block}
Gurax_DeclareMethod(List, Reduce)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("accum", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::Once);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Reduce)
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

// List#Replace(value, replace) {block?}
Gurax_DeclareMethod(List, Replace)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Replace)
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

// List#Reverse() {block?}
Gurax_DeclareMethod(List, Reverse)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Reverse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	return VType_Iterator::Method_Reverse(processor, argument, valueTypedOwner);
}

// List#RoundOff(threshold? as Number) {block?}
Gurax_DeclareMethod(List, RoundOff)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("threshold", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, RoundOff)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body

	return Value::nil();
}

// List#RunLength() {block?}
Gurax_DeclareMethod(List, RunLength)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, RunLength)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_RunLength(pIteratorThis.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// List#Since(criteria as Any) {block?}
Gurax_DeclareMethod(List, Since)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Since)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Since(processor, argument, *pIteratorSrc, true);
}

// List#SkipNil() {block?}
Gurax_DeclareMethod(List, SkipNil)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, SkipNil)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_SkipNil(pIteratorThis.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// List#Sort(directive? as Any, keys[]? as Any):[stable] {block?}
Gurax_DeclareMethod(List, Sort)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("directive", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("keys", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	DeclareAttrOpt(Gurax_Symbol(stable));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Sort)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Function body
	return VType_Iterator::Method_Sort(processor, argument, valueTypedOwner);
}

// List#Std():[p]
Gurax_DeclareMethod(List, Std)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(p));
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Std)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->Std(processor);
}

// List#Sum()
Gurax_DeclareMethod(List, Sum)
{
	Declare(VTYPE_Any, Flag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Sum)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->Sum(processor);
}

// List#Tail(n as number):map {block?}
Gurax_DeclareMethod(List, Tail)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Tail)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<ValueOwner> pValueOwner(valueTypedOwner.GetValueOwner().Tail(n));
	return argument.ReturnIterator(processor, new Iterator_Each(pValueOwner.release()));
}

// List#Uniq() {block?}
Gurax_DeclareMethod(List, Uniq)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Uniq)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return argument.ReturnIterator(processor, new Iterator_Uniq(pIteratorThis.release()));
}

// List#Until(criteria as Any) {block?}
Gurax_DeclareMethod(List, Until)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Until)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_Until(processor, argument, *pIteratorSrc, true);
}

// List#Var():[p]
Gurax_DeclareMethod(List, Var)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(p));
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Var)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return pIteratorThis->Var(processor);
}

// List#While(criteria) {block?}
Gurax_DeclareMethod(List, While)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, While)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorSrc(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	return VType_Iterator::Method_While(processor, argument, *pIteratorSrc);
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// List#first
Gurax_DeclareProperty_R(List, first)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The first element in the list, or `nil` if the list is empty.
)""");
}

Gurax_ImplementPropertyGetter(List, first)
{
	auto& valueThis = GetValueThis(valueTarget);
	const ValueOwner& valueOwner = valueThis.GetValueOwner();
	if (valueOwner.empty()) return Value::nil();
	return valueOwner.front()->Reference();
}

// List#last
Gurax_DeclareProperty_R(List, last)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The last element in the list, or `nil` if the list is empty.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
The number of elements in the list.
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
リスト中の要素数。
)""");
}

Gurax_ImplementPropertyGetter(List, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueOwner().size());
}

// List#tuple
Gurax_DeclareProperty_R(List, tuple)
{
	Declare(VTYPE_Tuple, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts into a `Tuple` instance.
)""");
	AddHelp(Gurax_Symbol(en), u8R"""(
`Tuple` インスタンスに変換。
)""");
}

Gurax_ImplementPropertyGetter(List, tuple)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Tuple(valueThis.GetValueOwner().Reference());
}

// List#vtypeOfElem
Gurax_DeclareProperty_R(List, vtypeOfElem)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The value type of elements in the list.
)""");
}

Gurax_ImplementPropertyGetter(List, vtypeOfElem)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_VType(valueThis.GetValueTypedOwner().GetVTypeOfElems());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Any in List
Gurax_ImplementOpBinary(Contains, Any, List)
{
	const ValueOwner& values = Value_List::GetValueTypedOwner(valueR).GetValueOwner();
	return new Value_Bool(values.Contains(valueL));
}

// List |+| List
Gurax_ImplementOpBinary(Concat, List, List)
{
	RefPtr<ValueTypedOwner> pValues(Value_List::GetValueTypedOwner(valueL).Reference());
	const ValueTypedOwner& valuesR = Value_List::GetValueTypedOwner(valueR);
	pValues->Add(valuesR);
	return new Value_List(pValues.release());
}

// List |+| Iterator
Gurax_ImplementOpBinary(Concat, List, Iterator)
{
	RefPtr<ValueTypedOwner> pValues(Value_List::GetValueTypedOwner(valueL).Reference());
	Iterator& iteratorR = Value_Iterator::GetIterator(valueR);
	if (!pValues->Add(iteratorR)) return Value::nil();
	return new Value_List(pValues.release());
}

// Any |+| List
Gurax_ImplementOpBinary(Concat, Any, List)
{
	RefPtr<ValueTypedOwner> pValues(new ValueTypedOwner());
	const ValueTypedOwner& valuesR = Value_List::GetValueTypedOwner(valueR);
	pValues->Add(valueL.Reference());
	pValues->Add(valuesR);
	return new Value_List(pValues.release());
}

// List |+| Any
Gurax_ImplementOpBinary(Concat, List, Any)
{
	RefPtr<ValueTypedOwner> pValues(Value_List::GetValueTypedOwner(valueL).Reference());
	pValues->Add(valueR.Reference());
	return new Value_List(pValues.release());
}

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
VType_List VTYPE_List("List");

void VType_List::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of statement
	frameOuter.Assign(Gurax_CreateStatement(_at_));
	// Assignment of method specific to List
	Assign(Gurax_CreateMethod(List, Add));
	Assign(Gurax_CreateMethod(List, Append));
	Assign(Gurax_CreateMethod(List, Clear));
	Assign(Gurax_CreateMethod(List, Erase));
	Assign(Gurax_CreateMethod(List, Get));
	Assign(Gurax_CreateMethod(List, Insert));
	Assign(Gurax_CreateMethod(List, IsEmpty));
	Assign(Gurax_CreateMethod(List, Put));
	Assign(Gurax_CreateMethod(List, Shift));
	Assign(Gurax_CreateMethod(List, Shuffle));
	// Assignment of method common to both Iterator and List
	Assign(Gurax_CreateMethod(List, After));
	Assign(Gurax_CreateMethod(List, Align));
	Assign(Gurax_CreateMethod(List, And));
	Assign(Gurax_CreateMethod(List, ArgMax));
	Assign(Gurax_CreateMethod(List, ArgMin));
	Assign(Gurax_CreateMethod(List, Before));
	Assign(Gurax_CreateMethod(List, Combination));
	Assign(Gurax_CreateMethod(List, Contains));
	Assign(Gurax_CreateMethod(List, Count));
	Assign(Gurax_CreateMethod(List, CountFalse));
	Assign(Gurax_CreateMethod(List, CountIf));
	Assign(Gurax_CreateMethod(List, CountTrue));
	Assign(Gurax_CreateMethod(List, Cycle));
	Assign(Gurax_CreateMethod(List, Each));
	Assign(Gurax_CreateMethod(List, Filter));
	Assign(Gurax_CreateMethod(List, Find));
	Assign(Gurax_CreateMethod(List, Flatten));
	Assign(Gurax_CreateMethod(List, Fold));
	Assign(Gurax_CreateMethod(List, Head));
	Assign(Gurax_CreateMethod(List, Join));
	Assign(Gurax_CreateMethod(List, Joinb));
	Assign(Gurax_CreateMethod(List, Map));
	Assign(Gurax_CreateMethod(List, Max));
	Assign(Gurax_CreateMethod(List, Mean));
	Assign(Gurax_CreateMethod(List, Min));
	Assign(Gurax_CreateMethod(List, NilTo));
	Assign(Gurax_CreateMethod(List, Offset));
	Assign(Gurax_CreateMethod(List, Or));
	Assign(Gurax_CreateMethod(List, Pack));
	Assign(Gurax_CreateMethod(List, Permutation));
	Assign(Gurax_CreateMethod(List, PingPong));
	Assign(Gurax_CreateMethod(List, Prod));
	Assign(Gurax_CreateMethod(List, Rank));
	Assign(Gurax_CreateMethod(List, Reduce));
	Assign(Gurax_CreateMethod(List, Replace));
	Assign(Gurax_CreateMethod(List, Reverse));
	Assign(Gurax_CreateMethod(List, RoundOff));
	Assign(Gurax_CreateMethod(List, RunLength));
	Assign(Gurax_CreateMethod(List, Since));
	Assign(Gurax_CreateMethod(List, SkipNil));
	Assign(Gurax_CreateMethod(List, Sort));
	Assign(Gurax_CreateMethod(List, Std));
	Assign(Gurax_CreateMethod(List, Sum));
	Assign(Gurax_CreateMethod(List, Tail));
	Assign(Gurax_CreateMethod(List, Uniq));
	Assign(Gurax_CreateMethod(List, Until));
	Assign(Gurax_CreateMethod(List, Var));
	Assign(Gurax_CreateMethod(List, While));
	// Assignment of property
	Assign(Gurax_CreateProperty(List, first));
	Assign(Gurax_CreateProperty(List, last));
	Assign(Gurax_CreateProperty(List, len));
	Assign(Gurax_CreateProperty(List, tuple));
	Assign(Gurax_CreateProperty(List, vtypeOfElem));
	// Assignment of operator
	Gurax_AssignOpBinary(Contains, Any, List);
	Gurax_AssignOpBinary(Concat, List, List);
	Gurax_AssignOpBinary(Concat, List, Iterator);
	Gurax_AssignOpBinary(Concat, Any, List);
	Gurax_AssignOpBinary(Concat, List, Any);
}

Value* VType_List::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Iterator)) {
		Iterator& iterator = Value_Iterator::GetIterator(value);
		RefPtr<ValueTypedOwner> pValues(ValueTypedOwner::CreateFromIterator(iterator, false));
		if (Error::IsIssued()) return Value::nil();
		return new Value_List(pValues.release());
	} else if (value.IsType(VTYPE_Array)) {
		const Array& array = Value_Array::GetArray(value);
		return array.ToList();
	} else if (value.IsType(VTYPE_Tuple)) {
		return new Value_List(Value_Tuple::GetValueOwner(value).Clone());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_List
//------------------------------------------------------------------------------
VType& Value_List::vtype = VTYPE_List;

String Value_List::ToString(const StringStyle& ss) const
{
	if (ss.IsBracket()) {
		return ToStringGeneric(ss, String().Format("%zuitems", GetValueOwner().size()));
	}
	return GetValueOwner().ToString(StringStyle(StringStyle::Flag::Quote |
					StringStyle::Flag::NilVisible | StringStyle::Flag::WithSquare));
}

bool Value_List::IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const
{
	return DeclCallable::IsMappable(declArg, flags);
}

void Value_List::UpdateMapMode(Argument& argument) const
{
	if (argument.IsMapNone()) argument.SetMapMode(Argument::MapMode::ToList);
}

bool Value_List::FeedExpandToArgument(Frame& frame, Argument& argument)
{
	const ValueOwner& valueOwner = GetValueOwner();
	for (const Value* pValueElem : valueOwner) {
		if (!argument.CheckArgSlotToFeed()) return false;
		argument.FeedValue(frame, pValueElem->Reference());
		if (Error::IsIssued()) return false;
	}
	return true;
}

const DeclCallable* Value_List::GetDeclCallable()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (valueOwner.empty()) return DeclCallable::Wildcard.get();
	Value* pValueElem = valueOwner.front();
	return pValueElem->GetDeclCallable();
}

// **** must handle attributes: :list, :xlist ****
Value* Value_List::DoEval(Processor& processor, Argument& argument) const
{
	if (GetValueOwner().empty()) return new Value_List(new ValueTypedOwner(new ValueOwner()));
	RefPtr<ValueOwner> pValueOwner;
	for (Value* pValueElem : GetValueOwner()) {
		if (!argument.GetDeclCallable().IsIdentical(pValueElem->GetDeclCallable())) {
			Error::Issue(ErrorType::ValueError,
						"member mapping cannot be applied to a list that contains different type of values");
			return Value::nil();
		}
		RefPtr<Value> pValueRtn(pValueElem->Eval(processor, argument));
		if (Error::IsIssued()) return Value::nil();
		if (!pValueOwner) pValueOwner.reset(new ValueOwner());
		pValueOwner->push_back(pValueRtn.release());
	}
	return pValueOwner? new Value_List(new ValueTypedOwner(pValueOwner.release())) : Value::nil();
}

bool Value_List::DoEmptyIndexGet(Value** ppValue) const
{
	*ppValue = Reference();
	return true;
}

bool Value_List::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_List::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const ValueTypedOwner& valueTypedOwner = GetValueTypedOwner();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, valueTypedOwner.GetSize(), &idx)) return false;
	*ppValue = valueTypedOwner.Get(idx).Reference();
	return true;
}

bool Value_List::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	ValueTypedOwner& valueTypedOwner = GetValueTypedOwner();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, valueTypedOwner.GetSize(), &idx)) return false;
	valueTypedOwner.Set(idx, pValue.release());
	return true;
}

Iterator* Value_List::DoGenIterator() const
{
	return GetValueTypedOwner().GenerateIterator();
}

bool Value_List::DoSerialize(Stream& stream) const
{
	return GetValueOwner().Serialize(stream);
}

Value* VType_List::DoDeserialize(Stream& stream) const
{
	RefPtr<ValueOwner> pValueOwner(ValueOwner::Deserialize(stream));
	return pValueOwner? new Value_List(pValueOwner.release()) : nullptr;
}

}
