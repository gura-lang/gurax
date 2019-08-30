//==============================================================================
// VType_List.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
#if 0
// List.Zip(values+) {block?}
Gurax_DeclareClassMethod(List, Zip)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("values", VTYPE_any, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), 
		"Creates an iterator generating lists that bind given argument values.\n"
		"When the value is a list or an iterator, each item in it would be zipped.\n");
}

Gurax_ImplementClassMethod(List, Zip)
{
	return Value::nil();
}
#endif

//-----------------------------------------------------------------------------
// Implementation of method specific to List
//-----------------------------------------------------------------------------
// List#Add(value+):reduce
Gurax_DeclareMethod(List, Add)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("value", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds values to the list.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Adds values to the list.\n"
		"If the value is a list of an iterator, elements they contain are added to the list.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Clears the content of the list.");
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

// List#Erase(pos*:Number):reduce
Gurax_DeclareMethod(List, Erase)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Erases elements at the specified indices.");
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

// List#Get(pos:Number):map:flat
Gurax_DeclareMethod(List, Get)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a value stored at the specified index in the list.\n"
		"An error occurs when the index is out of range.");
}

Gurax_ImplementMethod(List, Get)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
	// Arguments
	ArgPicker args(argument);
	Int pos = args.PickNumber<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	Value* pValue = valueTypedOwner.Get(pos);
	if (!pValue) return Value::nil();
	return pValue->Reference();
}

// List#Insert(pos:Number, values+):reduce
Gurax_DeclareMethod(List, Insert)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("elem", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Inserts items at the specified position in the list.");
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
	AddHelp(
		Gurax_Symbol(en),
		"A boolean value indicating whether the list is empty or not.");
}

Gurax_ImplementMethod(List, IsEmpty)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetValueOwner().empty());
}

// List#Put(pos:Number, value:nomap):reduce:map
Gurax_DeclareMethod(List, Put)
{
	Declare(VTYPE_List, Flag::Reduce | Flag::Map);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::NoMap);
	AddHelp(
		Gurax_Symbol(en), 
		"Stores a value at the specified index in the list.\n"
		"An error occurs when the index is out of range.");
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
	return Value::nil();
}

// List#Shuffle():reduce
Gurax_DeclareMethod(List, Shuffle)
{
	Declare(VTYPE_List, Flag::Reduce);
	AddHelp(
		Gurax_Symbol(en),
		"Shuffle the order of the list content based on random numbers.");
}

Gurax_ImplementMethod(List, Shuffle)
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

// List#Shift():[raise]
Gurax_DeclareMethod(List, Shift)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	AddHelp(
		Gurax_Symbol(en), 
		"Shifts the elements of the list. If the content of the list is `[1, 2, 3, 4]`,\n"
		"it becomes `[2, 3, 4]` after calling this method. In default, no error occurs\n"
		"even when the list is empty. To raise an error for executing this method on\n"
		"an empty list, specify :raise attribute.");
}

Gurax_ImplementMethod(List, Shift)
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

// List#Align(n:Number, value?):map {block?}
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

// List#ArgMax():[last_index,indices]
Gurax_DeclareMethod(List, ArgMax)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(last_index));
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

// List#ArgMin():[last_index,indices]
Gurax_DeclareMethod(List, ArgMin)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(last_index));
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

// List#Combination(n:Number) {block?}
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
	return VType_Iterator::Method_Combination(*this, processor, argument, valueTypedOwner);
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
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	return new Value_Bool(pIteratorThis->Contains(value));
}

// List#Count(criteria?)
Gurax_DeclareMethod(List, Count)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Count)
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

// List#Cycle(n?:Number) {block?}
Gurax_DeclareMethod(List, Cycle)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Cycle)
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
	RefPtr<Iterator> pIterator(valueThis.DoGenIterator());
	if (!argument.HasExprOfBlock()) return new Value_Iterator(pIterator.release());
	return pIterator->Each(processor, *argument.GetExprOfBlock(), argument.GetFlags());
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

// List#Fold(n:number, nstep?:number):map:[iteritem,neat] {block?}
Gurax_DeclareMethod(List, Fold)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nstep", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(iteritem));
	DeclareAttrOpt(Gurax_Symbol(neat));
	LinkHelp(VTYPE_Iterator, GetSymbol());

}

Gurax_ImplementMethod(List, Fold)
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

// List#Format(format:String):map {block?}
Gurax_DeclareMethod(List, Format)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Format)
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

// List#Head(n:number):map {block?}
Gurax_DeclareMethod(List, Head)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Head)
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

// List#Join(sep?:String):map
Gurax_DeclareMethod(List, Join)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("sep", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Join)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Function body
	// Arguments
	ArgPicker args(argument);
	const char* sep = args.IsValid()? args.PickString() : "";
	// Function body
	return new Value_String(pIteratorThis->Join(sep));
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

	return Value::nil();
}

// List#Map(func:Function) {block?}
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

// List#Offset(offset:Number):map:[raise] {block?}
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
	Int offset = args.PickNumberNonNeg<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (argument.IsSet(Gurax_Symbol(raise)) && !valueTypedOwner.CheckPosition(offset)) return Value::nil();
	RefPtr<Iterator> pIterator(new ValueTypedOwner::Iterator_Each(valueTypedOwner.Reference(), offset));
	return ReturnIterator(processor, argument, pIterator.release());
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

// List#Pack(format:String)
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

// List#Permutation(n?:Number) {block?}
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
	return VType_Iterator::Method_Permutation(*this, processor, argument, valueTypedOwner);
}

// List#PingPong(n?:Number):[sticky,sticky@top,sticky@btm] {block?}
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

// List#Print(stream?:Stream:w):void
Gurax_DeclareMethod(List, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Print)
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

// List#Printf(format:String, stream?:Stream:w):void
Gurax_DeclareMethod(List, Printf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Printf)
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

// List#Println(stream?:Stream:w):void
Gurax_DeclareMethod(List, Println)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Println)
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

// List#RoundOff(threshold?:number) {block?}
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

// List#Since(criteria) {block?}
Gurax_DeclareMethod(List, Since)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Since)
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

// List#Skip(n:Number):map {block?}
Gurax_DeclareMethod(List, Skip)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Skip)
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

// List#SkipNil() {block?}
Gurax_DeclareMethod(List, SkipNil)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, SkipNil)
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

// List#Sort(directive?, keys[]?):[stable] {block?}
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
	return VType_Iterator::Method_Sort(*this, processor, argument, valueTypedOwner);
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

// List#Tail(n:number):map {block?}
Gurax_DeclareMethod(List, Tail)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Tail)
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

// List#Until(criteria) {block?}
Gurax_DeclareMethod(List, Until)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("criteria", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	LinkHelp(VTYPE_Iterator, GetSymbol());
}

Gurax_ImplementMethod(List, Until)
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
	return new Value_VType(valueThis.GetValueTypedOwner().GetVTypeOfElems());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// List |+| List
Gurax_ImplementOpBinary(Concat, List, List)
{
	RefPtr<ValueTypedOwner> pValues(Value_List::GetValueTypedOwner(valueL).Reference());
	const ValueTypedOwner& valuesR = Value_List::GetValueTypedOwner(valueR);
	pValues->Add(valuesR);
	return new Value_List(pValues.release());
}

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
VType_List VTYPE_List("List");

void VType_List::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Mutable);
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
	Assign(Gurax_CreateMethod(List, Cycle));
	Assign(Gurax_CreateMethod(List, Each));
	Assign(Gurax_CreateMethod(List, Filter));
	Assign(Gurax_CreateMethod(List, Find));
	Assign(Gurax_CreateMethod(List, Flatten));
	Assign(Gurax_CreateMethod(List, Fold));
	Assign(Gurax_CreateMethod(List, Format));
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
	Assign(Gurax_CreateMethod(List, Print));
	Assign(Gurax_CreateMethod(List, Printf));
	Assign(Gurax_CreateMethod(List, Println));
	Assign(Gurax_CreateMethod(List, Prod));
	Assign(Gurax_CreateMethod(List, Rank));
	Assign(Gurax_CreateMethod(List, Reduce));
	Assign(Gurax_CreateMethod(List, Replace));
	Assign(Gurax_CreateMethod(List, Reverse));
	Assign(Gurax_CreateMethod(List, RoundOff));
	Assign(Gurax_CreateMethod(List, RunLength));
	Assign(Gurax_CreateMethod(List, Since));
	Assign(Gurax_CreateMethod(List, Skip));
	Assign(Gurax_CreateMethod(List, SkipNil));
	Assign(Gurax_CreateMethod(List, Sort));
	Assign(Gurax_CreateMethod(List, Std));
	Assign(Gurax_CreateMethod(List, Sum));
	Assign(Gurax_CreateMethod(List, Tail));
	Assign(Gurax_CreateMethod(List, Until));
	Assign(Gurax_CreateMethod(List, Var));
	Assign(Gurax_CreateMethod(List, While));
	// Assignment of property
	Assign(Gurax_CreateProperty(List, first));
	Assign(Gurax_CreateProperty(List, last));
	Assign(Gurax_CreateProperty(List, len));
	Assign(Gurax_CreateProperty(List, vtypeOfElem));
	// Assignment of operator
	Gurax_AssignOpBinary(Concat, List, List);
}

Value* VType_List::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Iterator)) {
		Iterator& iterator = Value_Iterator::GetIterator(value);
		return new Value_List(ValueTypedOwner::CreateFromIterator(iterator, false));
	}
	return nullptr;
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
}

void Value_List::UpdateMapMode(Argument& argument) const
{
	if (argument.IsMapNone()) argument.SetMapMode(Argument::MapMode::ToList);
}

const DeclCallable* Value_List::GetDeclCallable()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (valueOwner.empty()) return DeclCallable::Wildcard.get();
	Value* pValueElem = valueOwner.front();
	return pValueElem->GetDeclCallable();
}

void Value_List::DoCall(Processor& processor, Argument& argument)
{
	const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
	RefPtr<Value> pValueRtn(DoEval(processor, argument));
	if (Error::IsIssued()) return;
	if (!pPUnitOfCaller->GetDiscardValueFlag()) {
		processor.PushValue(pValueRtn.release());
	}
	processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
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
		RefPtr<Value> pValueRtn(pValueElem->DoEval(processor, argument));
		if (Error::IsIssued()) return Value::nil();
		if (!pValueOwner) pValueOwner.reset(new ValueOwner());
		pValueOwner->push_back(pValueRtn.release());
	}
	return pValueOwner? new Value_List(new ValueTypedOwner(pValueOwner.release())) : Value::nil();
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
		RefPtr<ValueOwner> pValuesRtn(new ValueOwner());
		pValuesRtn->reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			Value* pValue = nullptr;
			if (!GetValueTypedOwner().IndexGet(pValueIndex, &pValue)) return Value::nil();
			pValuesRtn->push_back(pValue);
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
	return GetValueTypedOwner().GenerateIterator();
}

}
