//==============================================================================
// Item.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
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

void Item::Print(Stream& stream, int indentLevel) const
{
	for (int i = 0; i < indentLevel; i++) stream.Print("  ");
	stream.Print("<");
	stream.Print(SymbolAssoc_Type::GetInstance().ToSymbol(GetType())->GetName());
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
		stream.Print(_pText->EnquoteAuto().c_str());
	}
	stream.Print("\n");
	if (_pItemOwner) {
		_pItemOwner->Print(stream, indentLevel + 1);
	}
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

//------------------------------------------------------------------------------
// Iterator_Item
//------------------------------------------------------------------------------
Value* Iterator_Item::DoNextValue()
{
	if (_idx >= GetItemOwner().size()) return nullptr;
	const Item* pItem = (*_pItemOwner)[_idx++];
	return new Value_Item(pItem->Reference());
}

String Iterator_Item::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "markdown.Item";
	return rtn;
}

Gurax_EndModuleScope(markdown)
