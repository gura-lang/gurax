//==============================================================================
// VType_List.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
	DeclareArg("value", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
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

// List#Combination(n:Number) {block?}
Gurax_DeclareMethod(List, Combination)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that generates lists that contain elements picked up\n"
		"from the original list in a combination manner.\n");
}

Gurax_ImplementMethod(List, Combination)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Erase(idx*:Number):reduce
Gurax_DeclareMethod(List, Erase)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "idx", VTYPE_number, OCCUR_ZeroOrMore);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Erases elements at the specified indices.");
}

Gurax_ImplementMethod(List, Erase)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Get(index:Number):map:flat
Gurax_DeclareMethod(List, Get)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map | FLAG_Flat);
	DeclareArg(env, "index", VTYPE_number);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a value stored at the specified index in the list.\n"
		"An error occurs when the index is out of range.");
}

Gurax_ImplementMethod(List, Get)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Insert(idx:Number, elem+):reduce
Gurax_DeclareMethod(List, Insert)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "idx", VTYPE_number);
	DeclareArg(env, "elem", VTYPE_any, OCCUR_OnceOrMore);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Insert specified items to the list from the selected index.");
}

Gurax_ImplementMethod(List, Insert)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Permutation(n?:Number) {block?}
Gurax_DeclareMethod(List, Permutation)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that generates lists that contain elements picked up\n"
		"from the original list in a permutation manner.\n");
}

Gurax_ImplementMethod(List, Permutation)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Put(index:Number, value:nomap):reduce:map
Gurax_DeclareMethod(List, Put)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "index", VTYPE_number);
	DeclareArg(env, "value", VTYPE_any, OCCUR_Once, FLAG_NoMap);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Stores a value at the specified index in the list.\n"
		"An error occurs when the index is out of range.");
}

Gurax_ImplementMethod(List, Put)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Shuffle():reduce
Gurax_DeclareMethod(List, Shuffle)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Shuffle the order of the list content based on random numbers.");
}

Gurax_ImplementMethod(List, Shuffle)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Shift():[raise]
Gurax_DeclareMethod(List, Shift)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(raise));
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Shifts the elements of the list. If the content of the list is [1, 2, 3, 4],\n"
		"it becomes [2, 3, 4] after calling this method. In default, no error occurs\n"
		"even when the list is empty. To raise an error for executing this method on\n"
		"an empty list, specify :raise attribute.");
}

Gurax_ImplementMethod(List, Shift)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method common to both Iterator and List
//-----------------------------------------------------------------------------
// List#After(criteria) {block?}
Gurax_DeclareMethod(List, After)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, After)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Align(n:Number, value?):map {block?}
Gurax_DeclareMethod(List, Align)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number);
	DeclareArg(env, "value", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Align)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#And()
Gurax_DeclareMethod(List, And)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, And)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#ArgMax():[last_index,indices]
Gurax_DeclareMethod(List, ArgMax)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(last_index));
	DeclareAttr(Gurax_Symbol(indices));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, ArgMax)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#ArgMin():[last_index,indices]
Gurax_DeclareMethod(List, ArgMin)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(last_index));
	DeclareAttr(Gurax_Symbol(indices));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, ArgMin)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Before(criteria) {block?}
Gurax_DeclareMethod(List, Before)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Before)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Contains(value)
Gurax_DeclareMethod(List, Contains)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "value", VTYPE_any);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Contains)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Count(criteria?)
Gurax_DeclareMethod(List, Count)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any, OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Count)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Cycle(n?:Number) {block?}
Gurax_DeclareMethod(List, Cycle)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Cycle)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
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

// List#Filter(criteria?) {block?}
Gurax_DeclareMethod(List, Filter)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Filter)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Find(criteria?):[index]
Gurax_DeclareMethod(List, Find)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(index));
	DeclareArg(env, "criteria", VTYPE_any, OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Find)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Flatten():[dfs,bfs] {block?}
Gurax_DeclareMethod(List, Flatten)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(dfs));
	DeclareAttr(Gurax_Symbol(bfs));
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Flatten)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Fold(n:number, nstep?:number):map:[iteritem,neat] {block?}
Gurax_DeclareMethod(List, Fold)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number);
	DeclareArg(env, "nstep", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(iteritem));
	DeclareAttr(Gurax_Symbol(neat));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Fold)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Format(format:String):map {block?}
Gurax_DeclareMethod(List, Format)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "format", VTYPE_string);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Format)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Head(n:number):map {block?}
Gurax_DeclareMethod(List, Head)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Head)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Join(sep?:String):map
Gurax_DeclareMethod(List, Join)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "sep", VTYPE_string, OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Join)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Joinb()
Gurax_DeclareMethod(List, Joinb)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Joinb)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Map(func:Function) {block?}
Gurax_DeclareMethod(List, Map)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "func", VTYPE_function);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Map)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Max():[index,last_index,indices]
Gurax_DeclareMethod(List, Max)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(index));
	DeclareAttr(Gurax_Symbol(last_index));
	DeclareAttr(Gurax_Symbol(indices));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Max)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Mean()
Gurax_DeclareMethod(List, Mean)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Mean)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Min():[index,last_index,indices]
Gurax_DeclareMethod(List, Min)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(index));
	DeclareAttr(Gurax_Symbol(last_index));
	DeclareAttr(Gurax_Symbol(indices));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Min)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#NilTo(replace) {block?}
Gurax_DeclareMethod(List, NilTo)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "replace", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, NilTo)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Offset(n:Number):map {block?}
Gurax_DeclareMethod(List, Offset)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_Once);
	DeclareArg(env, "n", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Offset)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Or()
Gurax_DeclareMethod(List, Or)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Or)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Pack(format:String)
Gurax_DeclareMethod(List, Pack)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "format", VTYPE_string);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Pack)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#PingPong(n?:Number):[sticky,sticky@top,sticky@btm] {block?}
Gurax_DeclareMethod(List, PingPong)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(sticky));
	DeclareAttr(Gurax_Symbol(sticky_at_top));
	DeclareAttr(Gurax_Symbol(sticky_at_btm));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, PingPong)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Print(stream?:Stream:w):void
Gurax_DeclareMethod(List, Print)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Print)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Printf(format:String, stream?:Stream:w):void
Gurax_DeclareMethod(List, Printf)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "format", VTYPE_string);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Printf)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Println(stream?:Stream:w):void
Gurax_DeclareMethod(List, Println)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Println)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Prod()
Gurax_DeclareMethod(List, Prod)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Prod)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Rank(directive?):[stable] {block?}
Gurax_DeclareMethod(List, Rank)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "directive", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(stable));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Rank)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Reduce(accum) {block}
Gurax_DeclareMethod(List, Reduce)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "accum", VTYPE_any);
	DeclareBlock(OCCUR_Once);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Reduce)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Replace(value, replace) {block?}
Gurax_DeclareMethod(List, Replace)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "value", VTYPE_any);
	DeclareArg(env, "replace", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Replace)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Reverse() {block?}
Gurax_DeclareMethod(List, Reverse)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Reverse)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#RoundOff(threshold:number => 1e-10) {block?}
Gurax_DeclareMethod(List, RoundOff)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "threshold", VTYPE_number, OCCUR_Once, FLAG_None, 0,
											new Expr_Value(RoundOffThreshold));
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, RoundOff)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#RunLength() {block?}
Gurax_DeclareMethod(List, RunLength)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, RunLength)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Since(criteria) {block?}
Gurax_DeclareMethod(List, Since)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Since)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Skip(n:Number):map {block?}
Gurax_DeclareMethod(List, Skip)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Skip)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#SkipNil() {block?}
Gurax_DeclareMethod(List, SkipNil)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, SkipNil)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Sort(directive?, keys[]?):[stable] {block?}
Gurax_DeclareMethod(List, Sort)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "directive", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareArg(env, "keys", VTYPE_any, OCCUR_ZeroOrOnce, FLAG_ListVar);
	DeclareAttr(Gurax_Symbol(stable));
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Sort)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Std():[p]
Gurax_DeclareMethod(List, Std)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(p));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Std)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Sum()
Gurax_DeclareMethod(List, Sum)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Sum)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Tail(n:number):map {block?}
Gurax_DeclareMethod(List, Tail)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Tail)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Until(criteria) {block?}
Gurax_DeclareMethod(List, Until)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Until)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#Var():[p]
Gurax_DeclareMethod(List, Var)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(p));
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, Var)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
#endif
	return Value::nil();
}

// List#While(criteria) {block?}
Gurax_DeclareMethod(List, While)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "criteria", VTYPE_any);
	DeclareBlock(OCCUR_ZeroOrOnce);
	LinkHelp(env.LookupClass(VTYPE_iterator), GetSymbol());
#endif
}

Gurax_ImplementMethod(List, While)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	// Function body
	ValueTypedOwner& valueTypedOwner = valueThis.GetValueTypedOwner();
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
	// Assignment of method specific to List
	Assign(Gurax_CreateMethod(List, Add));
	Assign(Gurax_CreateMethod(List, Append));
	Assign(Gurax_CreateMethod(List, Clear));
	Assign(Gurax_CreateMethod(List, Combination));
	Assign(Gurax_CreateMethod(List, Erase));
	Assign(Gurax_CreateMethod(List, Get));
	Assign(Gurax_CreateMethod(List, Insert));
	Assign(Gurax_CreateMethod(List, Permutation));
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
	Assign(Gurax_CreateProperty(List, isEmpty));
	Assign(Gurax_CreateProperty(List, last));
	Assign(Gurax_CreateProperty(List, len));
	Assign(Gurax_CreateProperty(List, vtypeOfElem));
}

Value* VType_List::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Iterator)) {
		RefPtr<Iterator> pIterator(Value_Iterator::GetIterator(value).Clone());
		return new Value_List(ValueTypedOwner::CreateFromIterator(*pIterator));
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
	processor.PushValue(pValueRtn.release());
	processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
}

Value* Value_List::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (Value* pValueElem : GetValueOwner()) {
		if (!argument.GetDeclCallable().IsIdentical(pValueElem->GetDeclCallable())) {
			Error::Issue(ErrorType::ValueError,
						 "member mapping cannot be applied to a list that contains different type of values");
			return Value::nil();
		}
		RefPtr<Value> pValueRtn(pValueElem->DoEval(processor, argument));
		if (Error::IsIssued()) return Value::nil();
		pValueOwner->push_back(pValueRtn.release());
	}
	return new Value_List(new ValueTypedOwner(pValueOwner.release()));
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
