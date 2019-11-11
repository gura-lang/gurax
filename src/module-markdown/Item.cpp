//==============================================================================
// Item.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
#if 0
const Item::TypeNamePair Item::_typeNamePairs[] = {
	{ TYPE_None,			"none",			},
	{ TYPE_Root,			"root",			},	// container
	{ TYPE_Header1,			"h1",			},	// container
	{ TYPE_Header2,			"h2",			},	// container
	{ TYPE_Header3,			"h3",			},	// container
	{ TYPE_Header4,			"h4",			},	// container
	{ TYPE_Header5,			"h5",			},	// container
	{ TYPE_Header6,			"h6",			},	// container
	{ TYPE_Paragraph,		"p",			},	// container
	{ TYPE_BlockQuote,		"blockquote",	},	// container
	{ TYPE_Emphasis,		"em",			},	// container
	{ TYPE_Strong,			"strong",		},	// container
	{ TYPE_Strike,			"strike",		},	// container
	{ TYPE_CodeBlock,		"codeblock",	},	// container
	{ TYPE_OList,			"ol",			},	// container
	{ TYPE_UList,			"ul",			},	// container
	{ TYPE_ListItem,		"li",			},	// container
	{ TYPE_Line,			"line",			},	// container
	{ TYPE_Link,			"a",			},	// container
	{ TYPE_Image,			"img",			},	// text
	{ TYPE_Text,			"text",			},	// text
	{ TYPE_Comment,			"comment",		},	// text
	{ TYPE_Code,			"code",			},	// text
	{ TYPE_Entity,			"entity",		},	// text
	{ TYPE_Tag,				"tag",			},	// container and text (attributes)
	{ TYPE_HorzRule,		"hr",			},	// no-content
	{ TYPE_LineBreak,		"br",			},	// no-content
	{ TYPE_Referee,			"referee",		},	// no-content
};

Item::Item(Type type) :
	_cntRef(1), _type(type), _align(ALIGN_None),
	_indentLevel(0), _indentLevelItemBody(0), _markdownAcceptableFlag(true)
{
}

Item::Item(Type type, ItemOwner *pItemOwner) :
	_cntRef(1), _type(type), _pItemOwner(pItemOwner), _align(ALIGN_None),
	_indentLevel(0), _indentLevelItemBody(0), _markdownAcceptableFlag(true)
{
}

Item::Item(Type type, const String &text) :
	_cntRef(1), _type(type), _pText(new String(text)), _align(ALIGN_None),
	_indentLevel(0), _indentLevelItemBody(0), _markdownAcceptableFlag(true)
{
}

// return true if the stripped result turns out be an empty string.
bool Item::StripText(bool stripLeftFlag, bool stripRightFlag)
{
	const char *text = GetText();
	if (text == nullptr) return false;
	SetText(Strip(text, stripLeftFlag, stripRightFlag));
	return *GetText() == '\0';
}

const char *Item::GetTypeName() const
{
	for (int i = 0; i < ArraySizeOf(_typeNamePairs); i++) {
		if (_typeNamePairs[i].type == _type) return _typeNamePairs[i].name;
	}
	return "?";
}

void Item::Print(Signal &sig, Stream &stream, int indentLevel) const
{
	for (int i = 0; i < indentLevel; i++) stream.Print(sig, "  ");
	stream.Print(sig, "<");
	stream.Print(sig, GetTypeName());
	if (_pURL.get() != nullptr) {
		stream.Print(sig, " url='");
		stream.Print(sig, _pURL->c_str());
		stream.Print(sig, "'");
	}
	if (_pTitle.get() != nullptr) {
		stream.Print(sig, " title='");
		stream.Print(sig, _pTitle->c_str());
		stream.Print(sig, "'");
	}
	if (_pRefId.get() != nullptr) {
		stream.Print(sig, " refid='");
		stream.Print(sig, _pRefId->c_str());
		stream.Print(sig, "'");
	}
	if (_pAttrs.get() != nullptr) {
		stream.Print(sig, " attrs='");
		stream.Print(sig, _pAttrs->c_str());
		stream.Print(sig, "'");
	}
	stream.Print(sig, ">");
	if (_pText.get() != nullptr) {
		stream.Print(sig, "'");
		stream.Print(sig, _pText->c_str());
		stream.Print(sig, "'");
	}
	stream.Print(sig, "\n");
	if (!_pItemOwner.IsNull()) {
		_pItemOwner->Print(sig, stream, indentLevel + 1);
	}
}

const char *Item::TypeToName(Type type)
{
	for (int i = 0; i < ArraySizeOf(_typeNamePairs); i++) {
		if (_typeNamePairs[i].type == type) return _typeNamePairs[i].name;
	}
	return "?";
}

Item::Type Item::NameToType(const char *name)
{
	for (int i = 0; i < ArraySizeOf(_typeNamePairs); i++) {
		if (::strcmp(_typeNamePairs[i].name, name) == 0) return _typeNamePairs[i].type;
	}
	return TYPE_None;
}
#endif

String Item::ToString(const StringStyle& ss) const
{
	return "Item";
}

#if 0
//------------------------------------------------------------------------------
// ItemList
//------------------------------------------------------------------------------
Item *ItemList::FindByRefId(const char *refId) const
{
	if (refId == nullptr) return nullptr;
	foreach_const (ItemList, ppItem, *this) {
		Item *pItem = *ppItem;
		if (pItem->GetRefId() != nullptr &&
					::strcasecmp(pItem->GetRefId(), refId) == 0) {
			return pItem;
		}
	}
	return nullptr;
}

size_t ItemList::CountByType(Item::Type type, bool recursiveFlag) const
{
	size_t cnt = 0;
	foreach_const (ItemList, ppItem, *this) {
		Item *pItem = *ppItem;
		if (pItem->GetType() == type) cnt++;
		if (recursiveFlag) {
			ItemOwner *pItemOwner = pItem->GetItemOwner();
			if (pItemOwner != nullptr) cnt += pItemOwner->CountByType(type, recursiveFlag);
		}
	}
	return cnt;
}

void ItemList::Print(Signal &sig, Stream &stream, int indentLevel) const
{
	foreach_const (ItemList, ppItem, *this) {
		const Item *pItem = *ppItem;
		pItem->Print(sig, stream, indentLevel);
	}
}

//------------------------------------------------------------------------------
// ItemOwner
//------------------------------------------------------------------------------
ItemOwner::~ItemOwner()
{
	Clear();
}

void ItemOwner::Clear()
{
	foreach (ItemOwner, ppItem, *this) {
		Item *pItem = *ppItem;
		Item::Delete(pItem);
	}
	clear();
}

void ItemOwner::Store(const ItemList &itemList)
{
	foreach_const (ItemList, ppItem, itemList) {
		const Item *pItem = *ppItem;
		push_back(pItem->Reference());
	}
}

void ItemOwner::StripTextAtFront(bool stripLeftFlag, bool stripRightFlag)
{
	if (!empty()) {
		Item *pItem = front();
		if (pItem->IsText() && pItem->StripText(stripLeftFlag, stripRightFlag)) {
			erase(begin());
			Item::Delete(pItem);
		}
	}
}

//------------------------------------------------------------------------------
// ItemOwnerStack
//------------------------------------------------------------------------------
ItemOwnerStack::~ItemOwnerStack()
{
	Clear();
}

void ItemOwnerStack::Clear()
{
	foreach (ItemOwnerStack, ppItemOwner, *this) {
		ItemOwner *pItemOwner = *ppItemOwner;
		ItemOwner::Delete(pItemOwner);
	}
	clear();
}

//------------------------------------------------------------------------------
// ItemStack
//------------------------------------------------------------------------------
void ItemStack::ClearListItem()
{
	foreach (ItemStack, ppItem, *this) {
		Item *pItem = *ppItem;
		if (pItem->Is_list()) {
			erase(ppItem, end());
			break;
		}
	}
}

int ItemStack::CountQuoteLevel() const
{
	int quoteLevel = 0;
	foreach_const (ItemStack, ppItem, *this) {
		Item *pItem = *ppItem;
		if (pItem->IsBlockQuote()) quoteLevel++;
	}
	return quoteLevel;
}

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
