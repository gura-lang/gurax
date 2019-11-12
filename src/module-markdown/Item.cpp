//==============================================================================
// Item.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
const Item::TypeNamePair Item::_typeNamePairs[] = {
	{ Type::None,			"none",			},
	{ Type::Root,			"root",			},	// container
	{ Type::Header1,		"h1",			},	// container
	{ Type::Header2,		"h2",			},	// container
	{ Type::Header3,		"h3",			},	// container
	{ Type::Header4,		"h4",			},	// container
	{ Type::Header5,		"h5",			},	// container
	{ Type::Header6,		"h6",			},	// container
	{ Type::Paragraph,		"p",			},	// container
	{ Type::BlockQuote,		"blockquote",	},	// container
	{ Type::Emphasis,		"em",			},	// container
	{ Type::Strong,			"strong",		},	// container
	{ Type::Strike,			"strike",		},	// container
	{ Type::CodeBlock,		"codeblock",	},	// container
	{ Type::OList,			"ol",			},	// container
	{ Type::UList,			"ul",			},	// container
	{ Type::ListItem,		"li",			},	// container
	{ Type::Line,			"line",			},	// container
	{ Type::Link,			"a",			},	// container
	{ Type::Image,			"img",			},	// text
	{ Type::Text,			"text",			},	// text
	{ Type::Comment,		"comment",		},	// text
	{ Type::Code,			"code",			},	// text
	{ Type::Entity,			"entity",		},	// text
	{ Type::Tag,			"tag",			},	// container and text (attributes)
	{ Type::HorzRule,		"hr",			},	// no-content
	{ Type::LineBreak,		"br",			},	// no-content
	{ Type::Referee,		"referee",		},	// no-content
};

Item::Item(Type type) :
	_type(type), _align(Align::None),
	_indentLevel(0), _indentLevelItemBody(0), _markdownAcceptableFlag(true)
{
}

Item::Item(Type type, ItemOwner* pItemOwner) :
	_type(type), _pItemOwner(pItemOwner), _align(Align::None),
	_indentLevel(0), _indentLevelItemBody(0), _markdownAcceptableFlag(true)
{
}

Item::Item(Type type, const String& text) :
	_type(type), _pText(new String(text)), _align(Align::None),
	_indentLevel(0), _indentLevelItemBody(0), _markdownAcceptableFlag(true)
{
}

void Item::AppendText(const String& text)
{
	if (_pText.get() == nullptr) {
		_pText.reset(new String(text));
	} else {
		*_pText += text;
	}
}

// return true if the stripped result turns out be an empty string.
bool Item::StripText(bool stripLeftFlag, bool stripRightFlag)
{
	const char* text = GetText();
	if (!text) return false;
	SetText(String::Strip(text, stripLeftFlag, stripRightFlag));
	return *GetText() == '\0';
}

const char *Item::GetTypeName() const
{
	for (int i = 0; i < ArraySizeOf(_typeNamePairs); i++) {
		if (_typeNamePairs[i].type == _type) return _typeNamePairs[i].name;
	}
	return "?";
}

void Item::Print(Stream& stream, int indentLevel) const
{
	for (int i = 0; i < indentLevel; i++) stream.Print("  ");
	stream.Print("<");
	stream.Print(GetTypeName());
	if (_pURL) {
		stream.Print(" url='");
		stream.Print(_pURL->c_str());
		stream.Print("'");
	}
	if (_pTitle) {
		stream.Print(" title='");
		stream.Print(_pTitle->c_str());
		stream.Print("'");
	}
	if (_pRefId) {
		stream.Print(" refid='");
		stream.Print(_pRefId->c_str());
		stream.Print("'");
	}
	if (_pAttrs) {
		stream.Print(" attrs='");
		stream.Print(_pAttrs->c_str());
		stream.Print("'");
	}
	stream.Print(">");
	if (_pText) {
		stream.Print("'");
		stream.Print(_pText->c_str());
		stream.Print("'");
	}
	stream.Print("\n");
	if (_pItemOwner) {
		_pItemOwner->Print(stream, indentLevel + 1);
	}
}

const char *Item::TypeToName(Type type)
{
	for (int i = 0; i < ArraySizeOf(_typeNamePairs); i++) {
		if (_typeNamePairs[i].type == type) return _typeNamePairs[i].name;
	}
	return "?";
}

Item::Type Item::NameToType(const char* name)
{
	for (int i = 0; i < ArraySizeOf(_typeNamePairs); i++) {
		if (::strcmp(_typeNamePairs[i].name, name) == 0) return _typeNamePairs[i].type;
	}
	return Type::None;
}

size_t Item::CountByType(const ItemList& itemList, Type type, bool recursiveFlag)
{
	size_t cnt = 0;
	for (Item* pItem : itemList) {
		if (pItem->GetType() == type) cnt++;
		if (recursiveFlag) {
			ItemOwner *pItemOwner = pItem->GetItemOwner();
			if (pItemOwner != nullptr) cnt += CountByType(*pItemOwner, type, recursiveFlag);
		}
	}
	return cnt;
}

String Item::ToString(const StringStyle& ss) const
{
	return "Item";
}

//------------------------------------------------------------------------------
// ItemList
//------------------------------------------------------------------------------
Item* ItemList::FindByRefId(const char* refId) const
{
	if (!refId) return nullptr;
	for (Item* pItem : *this) {
		if (pItem->GetRefId() && ::strcasecmp(pItem->GetRefId(), refId) == 0) {
			return pItem;
		}
	}
	return nullptr;
}


void ItemList::Print(Stream& stream, int indentLevel) const
{
	for (const Item* pItem : *this) pItem->Print(stream, indentLevel);
}

//------------------------------------------------------------------------------
// ItemOwner
//------------------------------------------------------------------------------
void ItemOwner::Clear()
{
	for (Item* pItem : *this) Item::Delete(pItem);
	clear();
}

void ItemOwner::Store(const ItemList &itemList)
{
	for (const Item* pItem : itemList) push_back(pItem->Reference());
}

void ItemOwner::StripTextAtFront(bool stripLeftFlag, bool stripRightFlag)
{
	if (!empty()) {
		Item* pItem = front();
		if (pItem->IsText() && pItem->StripText(stripLeftFlag, stripRightFlag)) {
			erase(begin());
			Item::Delete(pItem);
		}
	}
}

//------------------------------------------------------------------------------
// ItemOwnerStack
//------------------------------------------------------------------------------
void ItemOwnerStack::Clear()
{
	for (ItemOwner* pItemOwner : *this) ItemOwner::Delete(pItemOwner);
	clear();
}

//------------------------------------------------------------------------------
// ItemStack
//------------------------------------------------------------------------------
void ItemStack::ClearListItem()
{
	for (auto ppItem = begin(); ppItem != end(); ppItem++) {
		Item* pItem = *ppItem;
		if (pItem->Is_list()) {
			erase(ppItem, end());
			break;
		}
	}
}

int ItemStack::CountQuoteLevel() const
{
	int quoteLevel = 0;
	for (Item* pItem : *this) if (pItem->IsBlockQuote()) quoteLevel++;
	return quoteLevel;
}

#if 0
//------------------------------------------------------------------------------
// Iterator_item
//------------------------------------------------------------------------------
Iterator_item::Iterator_item(ItemOwner *pItemOwner) :
						Iterator(Finite), _idxItem(0), _pItemOwner(pItemOwner)
{
}

Iterator *Iterator_item::GetSource()
{
	return nullptr;
}

bool Iterator_item::DoNext(Environment &env, Value &value)
{
	if (_idxItem < _pItemOwner->size()) {
		Item *pItem = (*_pItemOwner)[_idxItem++];
		value = Value(new Object_item(pItem->Reference()));
		return true;
	}
	return false;
}

String Iterator_item::ToString() const
{
	String rtn;
	rtn += "<iterator:markdown.item";
	rtn += ">";
	return rtn;
}

void Iterator_item::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}
#endif

Gurax_EndModuleScope(markdown)
