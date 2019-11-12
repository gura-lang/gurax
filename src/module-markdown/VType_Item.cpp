//==============================================================================
// VType_Item.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// markdown.Item() {block?}
Gurax_DeclareFunction(Item)
{
	Declare(VTYPE_Item, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Item` instance.");
}

Gurax_ImplementFunction(Item)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Item> pItem(new Item(Item::Type::None));
	return argument.ReturnValue(processor, new Value_Item(pItem.release()));
}

#if 0
//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// markdown.Item#MethodSkeleton(num1:Number, num2:Number):reduce
Gurax_DeclareMethod(Item, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::Reduce);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Item, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

// markdown.item#countdescendant(type:symbol)
Gurax_DeclareMethod(item, countdescendant)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "type", VTYPE_symbol);
	AddHelp(
		Gurax_Symbol(en),
		"Count the number of descendant items of the specified type.");
}

Gurax_ImplementMethod(item, countdescendant)
{
	Item *pItem = Object_item::GetObjectThis(arg)->GetItem();
	const Symbol *pSymbol = arg.GetSymbol(0);
	Item::Type type = Item::NameToType(pSymbol->GetName());
	if (type == Item::TYPE_None) {
		env.SetError(ERR_ValueError, "invalid symbol for item type: `%s", pSymbol->GetName());
		return Value::Nil;
	}
	const ItemOwner *pItemOwner = pItem->GetItemOwner();
	size_t cnt = (pItemOwner == nullptr)? 0 : Item::CountByType(*pItemOwner, type, true);
	return Value(cnt);
}

// markdown.item#print(indent?:number):void
Gurax_DeclareMethod(item, print)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indent", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Prints structured content of the item.\n"
		"Argument `indent` specifies an indentation level and is set to zero when omitted.\n");
}

Gurax_ImplementMethod(item, print)
{
	Signal &sig = env.GetSignal();
	Item *pItem = Object_item::GetObjectThis(arg)->GetItem();
	int indentLevel = arg.Is_number(0)? arg.GetInt(0) : 0;
	pItem->Print(sig, *env.GetConsole(), indentLevel);
	return Value::Nil;
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// markdown.Item#propSkeleton
Gurax_DeclareProperty_R(Item, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// markdown.item#type
Gurax_DeclareProperty_R(item, type)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(item, type)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	return Value(Symbol::Add(pItem->GetTypeName()));
}

// markdown.item#text
Gurax_DeclareProperty_R(item, text)
{
	SetPropAttr(VTYPE_string, FLAG_Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(item, text)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *text = pItem->GetText();
	if (text == nullptr) return Value::Nil;
	return Value(text);
}

// markdown.item#children
Gurax_DeclareProperty_R(item, children)
{
	SetPropAttr(VTYPE_iterator);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(item, children)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const ItemOwner *pItemOwner = pItem->GetItemOwner();
	if (pItemOwner == nullptr) return Value::Nil;
	Iterator *pIterator = new Iterator_item(pItemOwner->Reference());
	return Value(new Object_iterator(env, pIterator));
}

// markdown.item#url
Gurax_DeclareProperty_R(item, url)
{
	SetPropAttr(VTYPE_string, FLAG_Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(item, url)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *url = pItem->GetURL();
	if (url == nullptr) return Value::Nil;
	return Value(url);
}

// markdown.item#title
Gurax_DeclareProperty_R(item, title)
{
	SetPropAttr(VTYPE_string, FLAG_Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(item, title)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *title = pItem->GetTitle();
	if (title == nullptr) return Value::Nil;
	return Value(title);
}

// markdown.item#attrs
Gurax_DeclareProperty_R(item, attrs)
{
	SetPropAttr(VTYPE_string, FLAG_Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(item, attrs)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *rtn = pItem->GetAttrs();
	if (rtn == nullptr) return Value::Nil;
	return Value(rtn);
}

// markdown.item#align
Gurax_DeclareProperty_R(item, align)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gurax_Symbol(en),
		"`` `none``, `` `left``, `` `center``, `` `right``");
}

Gurax_ImplementPropertyGetter(item, align)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	Align align = pItem->GetAlign();
	return Value(
		(align == ALIGN_Left)? Gurax_Symbol(left) :
		(align == ALIGN_Center)? Gurax_Symbol(center) :
		(align == ALIGN_Right)? Gurax_Symbol(right) : Gurax_Symbol(none));
}
#endif

//------------------------------------------------------------------------------
// VType_Item
//------------------------------------------------------------------------------
VType_Item VTYPE_Item("Item");

void VType_Item::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(Item));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Item, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Item, propSkeleton));
#if 0
	// Assignment of property
	Gurax_AssignProperty(item, type);
	Gurax_AssignProperty(item, text);
	Gurax_AssignProperty(item, children);
	Gurax_AssignProperty(item, url);
	Gurax_AssignProperty(item, title);
	Gurax_AssignProperty(item, attrs);
	Gurax_AssignProperty(item, align);
	// Assignment of method
	Gurax_AssignMethod(item, countdescendant);
	Gurax_AssignMethod(item, print);
	// Assignment of value
	Gurax_AssignValue(item, Value(Reference()));
#endif
}

//------------------------------------------------------------------------------
// Value_Item
//------------------------------------------------------------------------------
VType& Value_Item::vtype = VTYPE_Item;

#if 0
Object *Object_item::Clone() const
{
	return nullptr;
}

#if 0
bool Object_item::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = GetSignal();
	if (!Object::DoDirProp(env, symbols)) return false;
	symbols.insert(Gurax_Symbol(type));
	symbols.insert(Gurax_Symbol(text));
	symbols.insert(Gurax_Symbol(children));
	symbols.insert(Gurax_Symbol(url));
	symbols.insert(Gurax_Symbol(title));
	symbols.insert(Gurax_Symbol(attrs));
	symbols.insert(Gurax_Symbol(align));
	return true;
}

Value Object_item::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gurax_Symbol(type))) {
		return Value(Symbol::Add(_pItem->GetTypeName()));
	} else if (pSymbol->IsIdentical(Gurax_Symbol(text))) {
		const char *text = _pItem->GetText();
		if (text == nullptr) return Value::Nil;
		return Value(text);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(children))) {
		const ItemOwner *pItemOwner = _pItem->GetItemOwner();
		if (pItemOwner == nullptr) return Value::Nil;
		Iterator *pIterator = new Iterator_item(pItemOwner->Reference());
		return Value(new Object_iterator(env, pIterator));
	} else if (pSymbol->IsIdentical(Gurax_Symbol(url))) {
		const char *url = _pItem->GetURL();
		if (url == nullptr) return Value::Nil;
		return Value(url);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(title))) {
		const char *title = _pItem->GetTitle();
		if (title == nullptr) return Value::Nil;
		return Value(title);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(attrs))) {
		const char *attrs = _pItem->GetAttrs();
		if (attrs == nullptr) return Value::Nil;
		return Value(attrs);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(align))) {
		Align align = _pItem->GetAlign();
		return Value(
			(align == ALIGN_Left)? Gurax_Symbol(left) :
			(align == ALIGN_Center)? Gurax_Symbol(center) :
			(align == ALIGN_Right)? Gurax_Symbol(right) : Gurax_Symbol(none));
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value Object_item::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}
#endif

String Object_item::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<markdown.item:";
	rtn += _pItem->GetTypeName();
	rtn += ">";
	return rtn;
}
#endif

Gurax_EndModuleScope(markdown)
