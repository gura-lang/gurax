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

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// markdown.Item#CountDescendant(type:Symbol)
Gurax_DeclareMethod(Item, CountDescendant)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("type", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Count the number of descendant items of the specified type.");
}

Gurax_ImplementMethod(Item, CountDescendant)
{
	// Target
	Item& item = GetValueThis(argument).GetItem();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	Item::Type type = Item::NameToType(pSymbol->GetName());
	if (type == Item::Type::None) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for item type: `%s", pSymbol->GetName());
		return Value::nil();
	}
	// Function body
	const ItemOwner *pItemOwner = item.GetItemOwner();
	size_t cnt = pItemOwner? Item::CountByType(*pItemOwner, type, true) : 0;
	return new Value_Number(cnt);
}

// markdown.Item#Print(indent?:Number):void
Gurax_DeclareMethod(Item, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("indent", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Prints structured content of the item.\n"
		"Argument `indent` specifies an indentation level and is set to zero when omitted.\n");
}

Gurax_ImplementMethod(Item, Print)
{
	// Target
	Item& item = GetValueThis(argument).GetItem();
	// Arguments
	ArgPicker args(argument);
	int indentLevel = args.IsValid()? args.PickNumberNonNeg<int>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	item.Print(Basement::Inst.GetStreamCOut(), indentLevel);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// markdown.Item#type
Gurax_DeclareProperty_R(Item, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, type)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	return new Value_Symbol(Symbol::Add(item.GetTypeName()));
}

#if 0
// markdown.Item#text:nil
Gurax_DeclareProperty_R(Item, text)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, text)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const char* text = item.GetText();
	return text? new Value_String(text) : Value::nil();
}

// markdown.Item#children:nil
Gurax_DeclareProperty_R(Item, children)
{
	Declare(VTYPE_Iterator, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, children)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const ItemOwner* pItemOwner = item.GetItemOwner();
	return pItemOwner? new Value_Iterator(new Iterator_Item(pItemOwner->Reference()) : Value::nil();
}

// markdown.Item#url:nil
Gurax_DeclareProperty_R(Item, url)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, url)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *url = pItem->GetURL();
	if (url == nullptr) return Value::Nil;
	return Value(url);
}

// markdown.Item#title:nil
Gurax_DeclareProperty_R(Item, title)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, title)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *title = pItem->GetTitle();
	if (title == nullptr) return Value::Nil;
	return Value(title);
}

// markdown.Item#attrs:nil
Gurax_DeclareProperty_R(Item, attrs)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Item, attrs)
{
	Item *pItem = Object_item::GetObject(valueThis)->GetItem();
	const char *rtn = pItem->GetAttrs();
	if (rtn == nullptr) return Value::Nil;
	return Value(rtn);
}

// markdown.Item#align:nil
Gurax_DeclareProperty_R(Item, align)
{
	Declare(VTYPE_Symbol, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"`` `none``, `` `left``, `` `center``, `` `right``");
}

Gurax_ImplementPropertyGetter(Item, align)
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
	Assign(Gurax_CreateMethod(Item, CountDescendant));
	Assign(Gurax_CreateMethod(Item, Print));
	// Assignment of property
	Assign(Gurax_CreateProperty(Item, type));
#if 0
	Assign(Gurax_CreateProperty(Item, text));
	Assign(Gurax_CreateProperty(Item, children));
	Assign(Gurax_CreateProperty(Item, url));
	Assign(Gurax_CreateProperty(Item, title));
	Assign(Gurax_CreateProperty(Item, attrs));
	Assign(Gurax_CreateProperty(Item, align));
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
