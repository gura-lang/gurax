//==============================================================================
// VType_Item.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(markdown.Item, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(markdown.Item, `en)}

${help.ComposeMethodHelp(markdown.Item, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// markdown.Item() {block?}
Gurax_DeclareConstructor(Item)
{
	Declare(VTYPE_Item, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Item` instance.
)**");
}

Gurax_ImplementConstructor(Item)
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Count the number of descendant items of the specified type.
)**");
}

Gurax_ImplementMethod(Item, CountDescendant)
{
	// Target
	Item& item = GetValueThis(argument).GetItem();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	Item::Type type = Item::SymbolAssoc_Type::GetInstance().ToAssociated(pSymbol);
	if (type == Item::Type::None) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for item type: `%s", pSymbol->GetName());
		return Value::nil();
	}
	// Function body
	const ItemOwner* pItemOwner = item.GetItemOwner();
	size_t cnt = pItemOwner? Item::CountByType(*pItemOwner, type, true) : 0;
	return new Value_Number(cnt);
}

// markdown.Item#Print(indent?:Number):void
Gurax_DeclareMethod(Item, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("indent", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Prints structured content of the item.
Argument `indent` specifies an indentation level and is set to zero when omitted.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Item, type)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	return new Value_Symbol(Item::SymbolAssoc_Type::GetInstance().ToSymbol(item.GetType()));
}

// markdown.Item#text:nil
Gurax_DeclareProperty_R(Item, text)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Item, text)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const char* str = item.GetText();
	return str? new Value_String(str) : Value::nil();
}

// markdown.Item#children:nil
Gurax_DeclareProperty_R(Item, children)
{
	Declare(VTYPE_Iterator, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Item, children)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const ItemOwner* pItemOwner = item.GetItemOwner();
	return pItemOwner? new Value_Iterator(new Iterator_Item(pItemOwner->Reference())) : Value::nil();
}

// markdown.Item#url:nil
Gurax_DeclareProperty_R(Item, url)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Item, url)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const char* str = item.GetURL();
	return str? new Value_String(str) : Value::nil();
}

// markdown.Item#title:nil
Gurax_DeclareProperty_R(Item, title)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Item, title)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const char* str = item.GetTitle();
	return str? new Value_String(str) : Value::nil();
}

// markdown.Item#attrs:nil
Gurax_DeclareProperty_R(Item, attrs)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Item, attrs)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	const char* str = item.GetAttrs();
	return str? new Value_String(str) : Value::nil();
}

// markdown.Item#align
Gurax_DeclareProperty_R(Item, align)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
`` `none``, `` `left``, `` `center``, `` `right``
)**");
}

Gurax_ImplementPropertyGetter(Item, align)
{
	Item& item = GetValueThis(valueTarget).GetItem();
	return new Value_Symbol(SymbolAssoc_Align::GetInstance().ToSymbol(item.GetAlign()));
}

//------------------------------------------------------------------------------
// VType_Item
//------------------------------------------------------------------------------
VType_Item VTYPE_Item("Item");

void VType_Item::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Item));
	// Assignment of method
	Assign(Gurax_CreateMethod(Item, CountDescendant));
	Assign(Gurax_CreateMethod(Item, Print));
	// Assignment of property
	Assign(Gurax_CreateProperty(Item, type));
	Assign(Gurax_CreateProperty(Item, text));
	Assign(Gurax_CreateProperty(Item, children));
	Assign(Gurax_CreateProperty(Item, url));
	Assign(Gurax_CreateProperty(Item, title));
	Assign(Gurax_CreateProperty(Item, attrs));
	Assign(Gurax_CreateProperty(Item, align));
}

//------------------------------------------------------------------------------
// Value_Item
//------------------------------------------------------------------------------
VType& Value_Item::vtype = VTYPE_Item;

String Value_Item::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetItem().ToString(ss));
}

Gurax_EndModuleScope(markdown)
