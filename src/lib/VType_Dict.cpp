//==============================================================================
// VType_Dict.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Dict, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Dict, `en)}

${help.ComposeMethodHelp(Dict, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of statement
//------------------------------------------------------------------------------
// %{block}
Gurax_DeclareStatementAlias(_create_dict_, "%")
{
	Declare(VTYPE_Dict, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Dict` instance from key-value pairs described in the `block`.
There are several acceptable manners to describe key-value pairs.

1. Desribes a key-value pair concatenated with `=>` operator:
   eg. ``%{key1 => value1, key2 => value2, key3 => value3}``

2. Desribes each key-value pair surrounded by brackets:
   eg. ``%{{key1, value1}, {key2, value2}, {key3, value3}}``

3. Describes keys and values alternatively:
   eg. ``%{key1, value1, key2, value2, key3, value3}``

Value types that can be used as dictionary keys are `Number`, `String`, and `Symbol`.

```
d1 = %{ 3 => 100, 5 => 200, 9 => 80 }
d2 = %{ 'apple' => 100, 'grape' => 200, 'banana' => 80 }
d3 = %{ `apple => 100, `grape => 200, `banana => 80 }
```
)""");
}

Gurax_ImplementStatement(_create_dict_)
{
	Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
	composer.Add_CreateDict(exprCaller);										// [Dict]
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			// %{ .. key => value .. }
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			pExprEx->GetExprLeft().ComposeOrNil(composer);						// [Dict Key]
			pExprEx->GetExprRight().ComposeOrNil(composer);						// [Dict Key Elem]
		} else if (pExpr->IsType<Expr_Block>()) {
			// %{ .. {key, value} .. }
			Expr_Block* pExprEx = dynamic_cast<Expr_Block*>(pExpr);
			if (pExprEx->CountExprElem() != 2) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								"block is expected to have a format of {key, value}");
				return;
			}
			Expr* pExprElem = pExprEx->GetExprElemFirst();
			pExprElem->ComposeOrNil(composer);									// [Dict Key]
			pExprElem = pExprElem->GetExprNext();
			pExprElem->ComposeOrNil(composer);									// [Dict Key Elem]
		} else {
			// %{ .. key, value .. }
			pExpr->ComposeOrNil(composer);										// [Dict Key]
			pExpr = pExpr->GetExprNext();
			if (!pExpr) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								"value is missing in the initialization list for dictionary");
				return;
			}
			pExpr->ComposeOrNil(composer);										// [Dict Key Elem]
		}
		composer.Add_DictElem(0, exprCaller);									// [Dict]
	}
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Dict#Append(dict as Dict):Dict:reduce:[overwrite,strict,timid]
Gurax_DeclareMethod(Dict, Append)
{
	Declare(VTYPE_Dict, Flag::Reduce);
	DeclareArg("dict", VTYPE_Dict, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(overwrite));
	DeclareAttrOpt(Gurax_Symbol(strict));
	DeclareAttrOpt(Gurax_Symbol(timid));
	AddHelp(Gurax_Symbol(en), u8R"""(
Appends items stored in another `Dict` instance to the target.

If a key of the added item already exists in the target dictionary, it would be overwritten.
This behavior can be altered with the following attributes:

- `:overwrite` .. overwrite the existing one (default)
- `:strict` .. raises an error
- `:timid` .. keeps the existing one
)""");
}

Gurax_ImplementMethod(Dict, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const ValueDict& valDict = args.PickValueDict();
	// Function body
	ValueDict::StoreMode storeMode =
		argument.IsSet(Gurax_Symbol(strict))? ValueDict::StoreMode::Strict :
		argument.IsSet(Gurax_Symbol(timid))? ValueDict::StoreMode::Timid :
		ValueDict::StoreMode::Overwrite;
	if (!valueThis.GetValueDict().Store(valDict, storeMode)) return Value::nil();
	return argument.GetValueThis().Reference();
}

// Dict#Clear()
Gurax_DeclareMethod(Dict, Clear)
{
	Declare(VTYPE_Dict, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Clears all the items in the target dictionary.
)""");
}

Gurax_ImplementMethod(Dict, Clear)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetValueDict().Clear();
	return argument.GetValueThis().Reference();
}

// Dict#Each() {block?}
Gurax_DeclareMethod(Dict, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Dict, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new ValueDict::
		Iterator_Each<ValueDict::IterItem::Pair>(valueThis.GetValueDict().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Dict#EachKey() {block?}
Gurax_DeclareMethod(Dict, EachKey)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Dict, EachKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new ValueDict::
		Iterator_Each<ValueDict::IterItem::Key>(valueThis.GetValueDict().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Dict#EachValue() {block?}
Gurax_DeclareMethod(Dict, EachValue)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Dict, EachValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new ValueDict::
		Iterator_Each<ValueDict::IterItem::Value>(valueThis.GetValueDict().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Dict#Erase(key as Any):map
Gurax_DeclareMethod(Dict, Erase)
{
	Declare(VTYPE_Dict, Flag::Reduce);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Erases an item that has a key that matches with the specified one
)""");
}

Gurax_ImplementMethod(Dict, Erase)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& key = args.PickValue();
	// Function body
	valueThis.GetValueDict().Erase(key);
	return argument.GetValueThis().Reference();
}

// Dict#Get(key as Any, default?:noMap as Any):map:[raise]
Gurax_DeclareMethod(Dict, Get)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::NoMap);
	DeclareAttrOpt(Gurax_Symbol(raise));
	AddHelp(Gurax_Symbol(en), u8R"""(
Seeks a value that is associated with the specified `key`.

The method would return the value `default`
when the specified key doesn't exist in the dictionary.
If the argument is omitted, the default value is `nil`.

When the attribute `:raise` is specified,
an error occurs when the specified key doesn't exist.

Calling this method with `:raise` attribute behaves the same as index operator.
The following two codes have the same effect:

- `v = d['foo']`
- `v = d.Get('foo'):raise`
)""");
}

Gurax_ImplementMethod(Dict, Get)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& key = args.PickValue();
	const Value& valueDefault = args.IsValid()? args.PickValue() : Value::C_nil();
	// Function body
	const Value* pValue = valueThis.GetValueDict().Lookup(key);
	if (pValue) {
		return pValue->Reference();
	} else if (argument.IsSet(Gurax_Symbol(raise))) {
		ValueDict::IssueError_KeyNotFound(key);
		return Value::nil();
	} else {
		return valueDefault.Reference();
	}
}

// Dict#HasKey(key as Any):map
Gurax_DeclareMethod(Dict, HasKey)
{
	Declare(VTYPE_Bool, Flag::Map);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the specified `key` exists in the target dictionary.
)""");
}

Gurax_ImplementMethod(Dict, HasKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& key = args.PickValue();
	// Function body
	const Value* pValue = valueThis.GetValueDict().Lookup(key);
	return new Value_Bool(pValue);
}

// Dict#IsEmpty()
Gurax_DeclareMethod(Dict, IsEmpty)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the dictionary has no entries.
)""");
}

Gurax_ImplementMethod(Dict, IsEmpty)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetValueDict().GetMap().empty());
}

// Dict#Put(key as Any, value as Any):map:reduce:[overwrite,strict,timid]
Gurax_DeclareMethod(Dict, Put)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(overwrite));
	DeclareAttrOpt(Gurax_Symbol(strict));
	DeclareAttrOpt(Gurax_Symbol(timid));
	AddHelp(Gurax_Symbol(en), u8R"""(
Appends items stored in another `Dict` instance to the target.

If a key of the added item already exists in the target dictionary, it would be overwritten.
This behavior can be altered with the following attributes:

- `:overwrite` .. overwrite the existing one (default)
- `:strict` .. raises an error
- `:timid` .. keeps the existing one
)""");
}

Gurax_ImplementMethod(Dict, Put)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& key = args.PickValue();
	const Value& value = args.PickValue();
	// Function body
	ValueDict::StoreMode storeMode =
		argument.IsSet(Gurax_Symbol(strict))? ValueDict::StoreMode::Strict :
		argument.IsSet(Gurax_Symbol(timid))? ValueDict::StoreMode::Timid :
		ValueDict::StoreMode::Overwrite;
	if (!valueThis.GetValueDict().Store(key, value, storeMode)) return Value::nil();
	return argument.GetValueThis().Reference();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Dict#len
Gurax_DeclareProperty_R(Dict, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The number of items in the dictionary.
)""");
}

Gurax_ImplementPropertyGetter(Dict, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueDict().GetMap().size());
}

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
VType_Dict VTYPE_Dict("Dict");

void VType_Dict::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of statement
	frameOuter.Assign(Gurax_CreateStatement(_create_dict_));
	// Assignment of method
	Assign(Gurax_CreateMethod(Dict, Append));
	Assign(Gurax_CreateMethod(Dict, Clear));
	Assign(Gurax_CreateMethod(Dict, Each));
	Assign(Gurax_CreateMethod(Dict, EachKey));
	Assign(Gurax_CreateMethod(Dict, EachValue));
	Assign(Gurax_CreateMethod(Dict, Erase));
	Assign(Gurax_CreateMethod(Dict, Get));
	Assign(Gurax_CreateMethod(Dict, HasKey));
	Assign(Gurax_CreateMethod(Dict, IsEmpty));
	Assign(Gurax_CreateMethod(Dict, Put));
	// Assignment of property
	Assign(Gurax_CreateProperty(Dict, len));
}

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------
VType& Value_Dict::vtype = VTYPE_Dict;

String Value_Dict::ToString(const StringStyle& ss) const
{
	if (ss.IsBracket()) {
		return ToStringGeneric(ss, String().Format("%zuitems", GetValueDict().GetMap().size()));
	}
	return GetValueDict().ToString(ss);
}

bool Value_Dict::DoEmptyIndexGet(Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return Value::undefined();
}

bool Value_Dict::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_Dict::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const Value* pValue = GetValueDict().Lookup(valueIndex);
	if (pValue) {
		*ppValue = pValue->Reference();
		return true;
	}
	ValueDict::IssueError_KeyNotFound(valueIndex);
	return false;
}

bool Value_Dict::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	GetValueDict().Assign(valueIndex.Reference(), pValue.release());
	return true;
}

}
