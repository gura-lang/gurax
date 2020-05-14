//==============================================================================
// VType_Dict.cpp
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
// Implementation of statement
//------------------------------------------------------------------------------
// %{block}
Gurax_DeclareStatementAlias(_create_dict_, "%")
{
	Declare(VTYPE_Dict, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Dict` instance.\n"
		"\n"
		"The `block` contains a sequence of key-value pairs in the format below:\n"
		"\n"
		"- `{key1 => value1, key2 => value2, key3 => value3}`\n"
		"- `{{key1, value1}, {key2, value2}, {key3, value3}}``\n"
		"- `{key1, value1, key2, value2, key3, value3}`\n"
		"\n"
		"You can use `Number`, `String` or `Symbol` value for the dictionary keys.\n"
		"\n"
		"Below is an example using a block:"
		"\n"
		"    d = %{\n"
		"        'apple' => 100, 'grape' => 200, 'banana' => 80\n"
		"    }\n");
}

Gurax_ImplementStatement(_create_dict_)
{
	Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
	composer.Add_CreateDict(&exprCaller);						// [Dict]
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			// %{ .. key => value .. }
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			pExprEx->GetExprLeft().ComposeOrNil(composer);		// [Dict Key]
			pExprEx->GetExprRight().ComposeOrNil(composer);		// [Dict Key Elem]
		} else if (pExpr->IsType<Expr_Block>()) {
			// %{ .. {key, value} .. }
			Expr_Block* pExprEx = dynamic_cast<Expr_Block*>(pExpr);
			if (pExprEx->CountExprElem() != 2) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "block is expected to have a format of {key, value}");
				return;
			}
			Expr* pExprElem = pExprEx->GetExprElemFirst();
			pExprElem->ComposeOrNil(composer);					// [Dict Key]
			pExprElem = pExprElem->GetExprNext();
			pExprElem->ComposeOrNil(composer);					// [Dict Key Elem]
		} else {
			// %{ .. key, value .. }
			pExpr->ComposeOrNil(composer);						// [Dict Key]
			pExpr = pExpr->GetExprNext();
			if (!pExpr) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "value is missing in the initialization list for dictionary");
				return;
			}
			pExpr->ComposeOrNil(composer);						// [Dict Key Elem]
		}
		composer.Add_DictElem(0, &exprCaller);					// [Dict]
	}
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Dict#Append(dict:Dict):Dict:reduce:[overwrite,strict,timid]
Gurax_DeclareMethod(Dict, Append)
{
	Declare(VTYPE_Dict, Flag::Reduce);
	DeclareArg("dict", VTYPE_Dict, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(overwrite));
	DeclareAttrOpt(Gurax_Symbol(strict));
	DeclareAttrOpt(Gurax_Symbol(timid));
	AddHelp(
		Gurax_Symbol(en),
		"Appends items stored in another `Dict` instance to the target.\n"
		"\n"
		"If a key of the added item already exists in the target dictionary, it would be overwritten.\n"
		"This behavior can be altered with the following attributes:\n"
		"\n"
		"- `:overwrite` .. overwrite the existing one (default)\n"
		"- `:strict` .. raises an error\n"
		"- `:timid` .. keeps the existing one\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Clears all the items in the target dictionary.");
}

Gurax_ImplementMethod(Dict, Clear)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetValueDict().Clear();
	return argument.GetValueThis().Reference();
}

// Dict#Erase(key):map
Gurax_DeclareMethod(Dict, Erase)
{
	Declare(VTYPE_Dict, Flag::Reduce);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Erases an item that has a key that matches with the specified one");
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

// Dict#Get(key, default?:noMap):map:[raise]
Gurax_DeclareMethod(Dict, Get)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::NoMap);
	DeclareAttrOpt(Gurax_Symbol(raise));
	AddHelp(
		Gurax_Symbol(en),
		"Seeks a value that is associated with the specified `key`.\n"
		"\n"
		"The method would return the value `default`\n"
		"when the specified key doesn't exist in the dictionary.\n"
		"If the argument is omitted, the default value is `nil`.\n"
		"\n"
		"When the attribute `:raise` is specified,\n"
		"an error occurs when the specified key doesn't exist.\n"
		"\n"
		"Calling this method with `:raise` attribute behaves the same as index operator.\n"
		"The following two codes have the same effect:\n"
		"\n"
		"- `v = d['foo']`\n"
		"- `v = d.Get('foo'):raise`\n");
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

// Dict#HasKey(key):map
Gurax_DeclareMethod(Dict, HasKey)
{
	Declare(VTYPE_Bool, Flag::Map);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the specified `key` exists in the target dictionary.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the dictionary has no entries.");
}

Gurax_ImplementMethod(Dict, IsEmpty)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetValueDict().empty());
}

// Dict#Put(key, value):map:reduce:[overwrite,strict,timid]
Gurax_DeclareMethod(Dict, Put)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("key", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(overwrite));
	DeclareAttrOpt(Gurax_Symbol(strict));
	DeclareAttrOpt(Gurax_Symbol(timid));
	AddHelp(
		Gurax_Symbol(en),
		"Appends items stored in another `Dict` instance to the target.\n"
		"\n"
		"If a key of the added item already exists in the target dictionary, it would be overwritten.\n"
		"This behavior can be altered with the following attributes:\n"
		"\n"
		"- `:overwrite` .. overwrite the existing one (default)\n"
		"- `:strict` .. raises an error\n"
		"- `:timid` .. keeps the existing one\n");
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
// Dict#items
Gurax_DeclareProperty_R(Dict, items)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A list of key-value pairs.");
}

Gurax_ImplementPropertyGetter(Dict, items)
{
	return Value::nil();
}

// Dict#keys
Gurax_DeclareProperty_R(Dict, keys)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A list of keys.");
}

Gurax_ImplementPropertyGetter(Dict, keys)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<ValueOwner> pValueOwner(valueThis.GetValueDict().GetKeys());
	pValueOwner->Sort();
	return new Value_List(new ValueTypedOwner(pValueOwner.release()));
}

// Dict#len
Gurax_DeclareProperty_R(Dict, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The number of items in the dictionary.");
}

Gurax_ImplementPropertyGetter(Dict, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueDict().size());
}

// Dict#values
Gurax_DeclareProperty_R(Dict, values)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A list of values.");
}

Gurax_ImplementPropertyGetter(Dict, values)
{
	//auto& valueThis = GetValueThis(valueTarget);
#if 0
	RefPtr<ValueOwner> pValueOwner(valueThis.GetValueDict().GetKeys());
	pValueOwner->Sort();
	VType* pVType = pValueOwner->GetVTypeOfElems();
	return new Value_List(new ValueTypedOwner(pVType, pValueOwner.release()));
#endif
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
VType_Dict VTYPE_Dict("Dict");

void VType_Dict::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of statement
	frameOuter.Assign(Gurax_CreateStatement(_create_dict_));
	// Assignment of method
	Assign(Gurax_CreateMethod(Dict, Append));
	Assign(Gurax_CreateMethod(Dict, Clear));
	Assign(Gurax_CreateMethod(Dict, Erase));
	Assign(Gurax_CreateMethod(Dict, Get));
	Assign(Gurax_CreateMethod(Dict, HasKey));
	Assign(Gurax_CreateMethod(Dict, IsEmpty));
	Assign(Gurax_CreateMethod(Dict, Put));
	// Assignment of property
	Assign(Gurax_CreateProperty(Dict, items));
	Assign(Gurax_CreateProperty(Dict, keys));
	Assign(Gurax_CreateProperty(Dict, len));
	Assign(Gurax_CreateProperty(Dict, values));
}

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------
VType& Value_Dict::vtype = VTYPE_Dict;

String Value_Dict::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%zuitems>", GetValueDict().size());
	return str;
}

String Value_Dict::ToStringDetail(const StringStyle& ss) const
{
	return GetValueDict().ToString(ss);
}

Value* Value_Dict::DoIndexGet(const Index& index) const
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		const Value* pValueIndex = valuesIndex.front();
		const Value* pValue = GetValueDict().Lookup(*pValueIndex);
		if (!pValue) {
			ValueDict::IssueError_KeyNotFound(*pValueIndex);
			return Value::nil();
		}
		return pValue->Reference();
	} else {
		RefPtr<ValueOwner> pValuesRtn(new ValueOwner());
		pValuesRtn->reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			const Value* pValue = GetValueDict().Lookup(*pValueIndex);
			if (!pValue) {
				ValueDict::IssueError_KeyNotFound(*pValueIndex);
				return Value::nil();
			}
			pValuesRtn->push_back(pValue->Reference());
		}
		return new Value_List(pValuesRtn.release());
	}
}

void Value_Dict::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		const Value* pValueIndex = valuesIndex.front();
		GetValueDict().Assign(pValueIndex->Reference(), pValue.release());
	} else {
		Error::Issue_UnimplementedOperation();
	}
}

Value* Value_Dict::DoIndexOpApply(const Index& index, Value& value, Processor& processor, const Operator& op)
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		const Value* pValueIndex = valuesIndex.front();
		Value* pValueL = GetValueDict().Lookup(*pValueIndex);
		if (!pValueL) {
			ValueDict::IssueError_KeyNotFound(*pValueIndex);
			return Value::nil();
		}
		RefPtr<Value> pValueRtn(op.EvalBinary(processor, *pValueL, value));
		if (pValueRtn->IsUndefined()) return Value::nil();
		GetValueDict().Assign(pValueIndex->Reference(), pValueRtn.Reference());
		return pValueRtn.release();
	} else {
		Error::Issue_UnimplementedOperation();
		return Value::nil();
	}
}

}
