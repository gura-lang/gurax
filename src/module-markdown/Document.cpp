//==============================================================================
// Document.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------
Document::Document() :
	_resolvedFlag(false), _decoPrecedingFlag(false),
	_iTableRow(-1), _iTableCol(0), _stat(Stat::LineTop), _iLine(0), _iCol(0), _chPrev('\0'),
	_indentLevel(0), _indentLevelTableTop(0), _headerLevel(0), _headerLevelOffset(0),
	_quoteLevel(0), _cntEmptyLine(0), _pItemOwner(new ItemOwner()), _pItemRefereeOwner(new ItemOwner())
{
	_statStack.Push(Stat::LineTop);
	_pItemRoot.reset(new Item(Item::Type::Root, new ItemOwner()));
	_itemStack.push_back(_pItemRoot.get());
}

bool Document::ParseCharSeq(CharSeq& charSeq)
{
	enum class StatEx {
		FirstRowTop,
		FirstRowBody,
		GuideRowTop,
		GuideRowBody,
		TrailingRowTop,
		TrailingRowHead,
		TrailingRowBody,
		SkipToEOL,
	} statEx = StatEx::FirstRowTop;
	_iLine = 0;
	_iCol = 0;
	_chPrev = '\0';
	String textPrefetch;
	String guide;
	StringList guideList;
	for (;;) {
		char ch;
		textPrefetch.clear();
		int nTrailingRows = 0;
		bool pipeFoundFlag = false;
		bool prefetchFlag = true;
		statEx = StatEx::FirstRowTop;
		int indentLevelForCodeBlock = GetIndentLevelForCodeBlock();
		int indentLevel = 0;
		_indentLevelTableTop = 0;
		while (prefetchFlag && (ch = charSeq.GetChar())) {
			textPrefetch += ch;
			Gurax_BeginPushbackRegionEx(char, 16, ch);
			if (statEx == StatEx::FirstRowTop) {
				if (ch == '|') {
					pipeFoundFlag = true;
					statEx = StatEx::FirstRowBody;
				} else if (IsEOL(ch)) {
					prefetchFlag = false;
				} else {
					pipeFoundFlag = false;
					statEx = StatEx::FirstRowBody;
				}
			} else if (statEx == StatEx::FirstRowBody) {
				if (ch == '|') {
					pipeFoundFlag = true;
				} else if (IsEOL(ch)) {
					if (pipeFoundFlag) {
						indentLevel = 0;
						statEx = StatEx::GuideRowTop;
					} else {
						prefetchFlag = false;
					}
				} else {
					// nothing to do 
				}
			} else if (statEx == StatEx::GuideRowTop) {
				if (ch == ' ') {
					indentLevel++;
				} else if (ch == '\t') {
					indentLevel += WIDTH_Tab;
				} else if (indentLevel >= indentLevelForCodeBlock) {
					Gurax_PushbackEx(ch);
					statEx = StatEx::SkipToEOL;
				} else {
					if (ch == '|') {
						pipeFoundFlag = true;
						_indentLevelTableTop = indentLevel + 1;
					} else {
						pipeFoundFlag = false;
						Gurax_PushbackEx(ch);
					}
					guideList.clear();
					guide.clear();
					statEx = StatEx::GuideRowBody;
				}
			} else if (statEx == StatEx::GuideRowBody) {
				if (ch == '|') {
					pipeFoundFlag = true;
					guideList.push_back(String::Strip(guide.c_str(), true, true));
					guide.clear();
				} else if (IsEOL(ch)) {
					if (pipeFoundFlag) {
						if (!guide.empty()) {
							guideList.push_back(String::Strip(guide.c_str(), true, true));
						}
						statEx = StatEx::TrailingRowTop;
					} else {
						prefetchFlag = false;
					}
				} else if (String::IsWhite(ch) || ch == '-' || ch == ':') {
					guide += ch;
				} else {
					statEx = StatEx::SkipToEOL;
				}
			} else if (statEx == StatEx::TrailingRowTop) {
				if (ch == '|') {
					pipeFoundFlag = true;
					statEx = StatEx::TrailingRowBody;
				} else if (String::IsWhite(ch) || IsEOL(ch)) {
					Gurax_PushbackEx(ch);
					statEx = StatEx::TrailingRowHead;
				} else {
					pipeFoundFlag = false;
					statEx = StatEx::TrailingRowBody;
				}
			} else if (statEx == StatEx::TrailingRowHead) {
				if (String::IsWhite(ch)) {
					// nothing to do
				} else if (IsEOL(ch)) {
					// detected a blank line
					prefetchFlag = false;
				} else {
					Gurax_PushbackEx(ch);
					statEx = StatEx::TrailingRowBody;
				}
			} else if (statEx == StatEx::TrailingRowBody) {
				if (ch == '|') {
					pipeFoundFlag = true;
				} else if (IsEOL(ch)) {
					nTrailingRows++;
					statEx = StatEx::TrailingRowTop;
				} else {
					// nothing to do
				}
			} else if (statEx == StatEx::SkipToEOL) {
				if (IsEOL(ch)) {
					prefetchFlag = false;
				} else {
					// nothing to do
				}
			}
			Gurax_EndPushbackRegionEx();
		}
		if (textPrefetch.empty()) {
			if (!FeedChar('\0')) return false;
			break;
		}
		if (nTrailingRows == 0) {
			if (!FeedChars(textPrefetch)) return false;
		} else {
			_alignList.clear();
			for (const String& guide : guideList) {
				Align align = Align::Left;
				if (guide.empty()) {
					align = Align::Left;
				} else {
					bool colonLeftFlag = (guide[0] == ':');
					bool colonRightFlag = (guide[guide.size() - 1] == ':');
					if (colonLeftFlag && colonRightFlag) {
						align = Align::Center;
					} else if (colonLeftFlag) {
						align = Align::Left;
					} else if (colonRightFlag) {
						align = Align::Right;
					} else {
						align = Align::Left;
					}
				}
				_alignList.push_back(align);
			}
			if (_stat == Stat::ListItemNL && !String::IsWhite(textPrefetch.front())) {
				EndListItem();
				_itemStack.ClearListItem();
			} else {
				FlushItem(Item::Type::Paragraph, false, false);
			}
			BeginTable();
			Stat statPrev = _stat;
			_stat = Stat::LineTop;
			if (!FeedChars(textPrefetch)) return false;
			EndTable();
			_stat = statPrev;
		}
	}
	return true;
}

bool Document::ParseString(const char* str)
{
	String::CharSeq charSeq(str);
	return ParseCharSeq(charSeq);
}

void Document::AddItemReferee(Item* pItem)
{
	_pItemRefereeOwner->push_back(pItem);
	_resolvedFlag = false;
}

void Document::ResolveReference()
{
	if (_resolvedFlag) return;
	for (Item* pItemLink : _itemsLinkReferrer) {
		const char* refId = pItemLink->GetRefId();
		Item* pItemRef = _pItemRefereeOwner->FindByRefId(refId);
		if (pItemRef != nullptr) {
			const char* url = pItemRef->GetURL();
			const char* title = pItemRef->GetTitle();
			if (url != nullptr) pItemLink->SetURL(url);
			if (title != nullptr) pItemLink->SetTitle(title);
		}
	}
	_resolvedFlag = true;
}

bool Document::FeedChars(const String& text)
{
	for (char ch : text) {
		if (!FeedChar(ch)) return false;
	}
	return true;
}

bool Document::FeedChar(char ch)
{
	Gurax_BeginPushbackRegionEx(char, 16, ch);
	//::printf("'%c' %d\n", ch, _stat);
	switch (_stat) {
	case Stat::LineTop: {
		_indentLevel = 0;
		if (!IsTableMode()) {
			Gurax_PushbackEx(ch);
			_stat = Stat::LineHead;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::LineHeadTable;
		}
		break;
	}
	case Stat::LineHead: {
		if (!IsMarkdownAcceptable()) {
			// When within a tag, ignore special characters except for '<'.
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		} else if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			int indentLevelBase = GetIndentLevel();
			_indentLevel = (_indentLevel - indentLevelBase) / INDENT_CodeBlock * INDENT_CodeBlock + indentLevelBase;
			Gurax_PushbackEx(ch);
			BeginCodeBlock(nullptr);
			_stat = Stat::CodeBlock;
		} else if (ch == '>') {
			_indentLevel = -1;
			_quoteLevel = 1;
			_stat = Stat::BlockQuote;
		} else if (ch == '=') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::EqualAtHead;
		} else if (ch == '#' && _indentLevel <= 0) {
			FlushItem(Item::Type::Paragraph, false, false);
			_headerLevel = 1;
			_stat = Stat::SetextHeaderHead;
		} else if (ch == '*') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::AsteriskAtHead;
		} else if (ch == '+') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::PlusAtHead;
		} else if (ch == '-') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::HyphenAtHead;
		} else if (IsDigit(ch)) {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::DigitAtHead;
		} else if (ch == '`') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::BackquoteAtHead;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			FlushItem(Item::Type::Paragraph, false, false);
			_indentLevel = 0;
			_stat = Stat::LineHeadNL;
		} else if (ch == '[') {
			AppendJointSpace();
			_pItemLink.reset(new Item(Item::Type::Referee));
			_textAhead.clear();
			_textAhead += ch;
			_field.clear();
			_stat = Stat::RefereeRefId;
		} else {
			if (_decoPrecedingFlag) _text += ' ';
			AppendJointSpace();
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		_decoPrecedingFlag = false;
		break;
	}
	case Stat::LineHeadTable: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (IsEOL(ch)) {
			_indentLevel = 0;
		} else {
			BeginTableRow();
			if (ch != '|' || _indentLevel >= _indentLevelTableTop) {
				Gurax_PushbackEx(ch);
			}
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::LineHeadNL: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (ch == '>') {
			Gurax_PushbackEx(ch);
			_stat = Stat::LineHead;
		} else {
			_quoteLevel = 0;
			AdjustBlockQuote();
			Gurax_PushbackEx(ch);
			_stat = Stat::LineHead;
		}
		break;
	}
	case Stat::BlockQuote: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			AdjustBlockQuote();
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else if (ch == '>') {
			_indentLevel = -1;
			_quoteLevel++;
		} else {
			AdjustBlockQuote();
			Gurax_PushbackEx(ch);
			_stat = Stat::LineHead;
		}
		break;
	}
	case Stat::EqualAtHead: {
		if (ch == '=') {
			_textAhead += ch;
			_stat = Stat::AtxHeader1;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::AtxHeader1;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::AsteriskAtHead: {
		if (ch == ' ' || ch == '\t') {
			FlushItem(Item::Type::Paragraph, false, false);
			_stat = Stat::UListItemPre;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			AppendJointSpace();
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(Stat::Text);
			Gurax_PushbackEx(ch);
			_stat = Stat::Asterisk;
		}
		break;
	}
	case Stat::PlusAtHead: {
		if (ch == ' ' || ch == '\t') {
			FlushItem(Item::Type::Paragraph, false, false);
			_stat = Stat::UListItemPre;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::HyphenAtHead: {
		if (ch == '-') {
			_textAhead += ch;
			_stat = Stat::AtxHeader2;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::AtxHeader2;
		} else if (ch == ' ' || ch == '\t') {
			FlushItem(Item::Type::Paragraph, false, false);
			_stat = Stat::UListItemPre;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::DigitAtHead: {
		if (IsDigit(ch)) {
			_textAhead += ch;
		} else if (ch == '.') {
			_textAhead += ch;
			_stat = Stat::DigitDotAtHead;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::DigitDotAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::OListItemPre;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::BackquoteAtHead: {
		if (ch == '`') {
			_textAhead += ch;
			_stat = Stat::BackquoteAtHead2nd;
		} else {
			if (_decoPrecedingFlag) _text += ' ';
			AppendJointSpace();
			Gurax_PushbackEx(ch);
			Gurax_PushbackEx('`');
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::BackquoteAtHead2nd: {
		if (ch == '`') {
			_field.clear();
			_stat = Stat::FencedCodeBlockAttr;
		} else {
			if (_decoPrecedingFlag) _text += ' ';
			AppendJointSpace();
			Gurax_PushbackEx(ch);
			Gurax_PushbackEx('`');
			Gurax_PushbackEx('`');
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::SetextHeaderHead: {
		if (ch == '#') {
			_headerLevel++;
		} else if (ch == ' ' || ch == '\t') {
			_stat = Stat::SetextHeaderPre;
		} else {
			_text.clear();
			Gurax_PushbackEx(ch);
			_stat = Stat::SetextHeader;
		}
		break;
	}
	case Stat::SetextHeaderPre: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else {
			_text.clear();
			Gurax_PushbackEx(ch);
			_stat = Stat::SetextHeader;
		}
		break;
	}
	case Stat::SetextHeader: {
		if (CheckSpecialChar(ch)) {
			// nothing to do
		} else if (ch == '#') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::SetextHeaderPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			int headerLevel = _headerLevel + _headerLevelOffset;
			FlushItem(HeaderLevelToItemType(headerLevel), false, true);
			if (IsEOF(ch)) Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::SetextHeaderPost: {
		if (ch == '#') {
			_textAhead += ch;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::SetextHeader;
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::SetextHeader;
		}
		break;
	}
	case Stat::AtxHeader1: {
		if (ch == '=') {
			_textAhead += ch;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			int headerLevel = 1 + _headerLevelOffset;
			FlushItem(HeaderLevelToItemType(headerLevel), false, false);
			if (IsEOF(ch)) Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::AtxHeader2: {
		if (ch == '-') {
			_textAhead += ch;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			Item* pItemParent = _itemStack.back();
			FlushText(Item::Type::Text, false, false);
			if (!_pItemOwner->empty()) {
				int headerLevel = 2 + _headerLevelOffset;
				Item* pItem = new Item(HeaderLevelToItemType(headerLevel), _pItemOwner.release());
				pItemParent->GetItemOwner()->push_back(pItem);
				_pItemOwner.reset(new ItemOwner());
			} else if (IsHorzRule(_textAhead.c_str())) {
				Item* pItem = new Item(Item::Type::HorzRule);
				pItemParent->GetItemOwner()->push_back(pItem);
			} else {
				_text += _textAhead;
			}
			if (IsEOF(ch)) Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::UListItemPre: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else {
			BeginListItem(Item::Type::UList);
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::OListItemPre: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else {
			BeginListItem(Item::Type::OList);
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItem: {
		if (CheckSpecialChar(ch)) {
			// nothing to do
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_indentLevel = 0;
			if (IsEOF(ch)) Gurax_PushbackEx(ch);
			_stat = Stat::ListItem_LineHead;
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::ListItem_LineHead: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (ch == '>') {
			_indentLevel = -1;
			_quoteLevel = 1;
			_stat = Stat::ListItem_BlockQuoteAtHead;
		} else if (ch == '*') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItem_AsteriskAtHead;
		} else if (ch == '+') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItem_PlusAtHead;
		} else if (ch == '-') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItem_HyphenAtHead;
		} else if (IsDigit(ch)) {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItem_DigitAtHead;
		} else if (IsEOL(ch)) {
			_indentLevel = 0;
			_stat = Stat::ListItemNL;
		} else if (IsEOF(ch)) {
			EndListItem();
			_itemStack.ClearListItem();
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			UpdateIndentLevelItemBody(_indentLevel);
			_text += ' ';
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItem_BlockQuoteAtHead: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else if (ch == '>') {
			_indentLevel = -1;
			_quoteLevel++;
		} else {
			AdjustBlockQuote();
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem_LineHead;
		}
		break;
	}
	case Stat::ListItem_AsteriskAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::UListItemPre;
		} else {
			_text += ' ';
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(Stat::ListItem);
			Gurax_PushbackEx(ch);
			_stat = Stat::Asterisk;
		}
		break;
	}
	case Stat::ListItem_PlusAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::UListItemPre;
		} else {
			_text += ' ';
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItem_HyphenAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::UListItemPre;
		} else {
			_text += ' ';
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItem_DigitAtHead: {
		if (IsDigit(ch)) {
			_textAhead += ch;
		} else if (ch == '.') {
			_textAhead += ch;
			_stat = Stat::ListItem_DigitDotAtHead;
		} else {
			_text += ' ';
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItem_DigitDotAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::OListItemPre;
		} else {
			_text += ' ';
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItemNL: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			EndListItem();
			_itemStack.ClearListItem();
			if (IsEOF(ch)) Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(nullptr);
			_stat = Stat::CodeBlock;
		} else if (ch == '*') {
			UpdateIndentLevelItemBody(_indentLevel);
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItemNL_AsteriskAtHead;
		} else if (ch == '+') {
			UpdateIndentLevelItemBody(_indentLevel);
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItemNL_PlusAtHead;
		} else if (ch == '-') {
			UpdateIndentLevelItemBody(_indentLevel);
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItemNL_HyphenAtHead;
		} else if (IsDigit(ch)) {
			UpdateIndentLevelItemBody(_indentLevel);
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::ListItemNL_DigitAtHead;
		} else if (_indentLevel <= 0) {
			EndListItem();
			_itemStack.ClearListItem();
			AdjustBlockQuote();
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			UpdateIndentLevelItemBody(_indentLevel);
 			FlushItem(Item::Type::Paragraph, false, false);
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItemNL_AsteriskAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::UListItemPre;
		} else if (_indentLevel <= 0) {
			EndListItem();
			_itemStack.ClearListItem();
			_stat = Stat::LineTop;
			if (!FeedChars(String(_textAhead))) return false;
			Gurax_PushbackEx(ch);
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			FlushItem(Item::Type::Paragraph, false, false);
			Gurax_PushbackEx(ch);
			_statStack.Push(Stat::ListItem);
			_stat = Stat::Asterisk;
		}
		break;
	}
	case Stat::ListItemNL_PlusAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::UListItemPre;
		} else if (_indentLevel <= 0) {
			EndListItem();
			_itemStack.ClearListItem();
			_stat = Stat::LineTop;
			if (!FeedChars(String(_textAhead))) return false;
			Gurax_PushbackEx(ch);
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
 			FlushItem(Item::Type::Paragraph, false, false);
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItemNL_HyphenAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::UListItemPre;
		} else if (_indentLevel <= 0) {
			EndListItem();
			_itemStack.ClearListItem();
			_stat = Stat::LineTop;
			if (!FeedChars(String(_textAhead))) return false;
			Gurax_PushbackEx(ch);
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
 			FlushItem(Item::Type::Paragraph, false, false);
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItemNL_DigitAtHead: {
		if (IsDigit(ch)) {
			_textAhead += ch;
		} else if (ch == '.') {
			_textAhead += ch;
			_stat = Stat::ListItemNL_DigitDotAtHead;
		} else if (_indentLevel <= 0) {
			EndListItem();
			_itemStack.ClearListItem();
			_stat = Stat::LineTop;
			if (!FeedChars(String(_textAhead))) return false;
			Gurax_PushbackEx(ch);
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
			_text += ' ';
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::ListItemNL_DigitDotAtHead: {
		if (ch == ' ' || ch == '\t') {
			_stat = Stat::OListItemPre;
		} else if (_indentLevel <= 0) {
			EndListItem();
			_itemStack.ClearListItem();
			_stat = Stat::LineTop;
			if (!FeedChars(String(_textAhead))) return false;
			Gurax_PushbackEx(ch);
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			BeginCodeBlock(_textAhead.c_str());
			_stat = Stat::CodeBlock;
		} else {
 			FlushItem(Item::Type::Paragraph, false, false);
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::ListItem;
		}
		break;
	}
	case Stat::CodeBlock: {
		if (IsEOL(ch) || IsEOF(ch)) {
			Item* pItemParent = _itemStack.back();
			do {
				Item* pItem = new Item(Item::Type::Text, _text);
				_pItemOwner->push_back(pItem);
				_text.clear();
			} while (0);
			do {
				Item* pItem = new Item(Item::Type::Line, _pItemOwner.release());
				pItemParent->GetItemOwner()->push_back(pItem);
				_pItemOwner.reset(new ItemOwner());
			} while (0);
			_cntEmptyLine = 0;
			_indentLevel = 0;
			_stat = Stat::CodeBlock_LineHead;
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::CodeBlock_LineHead: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (IsEOL(ch)) {
			_cntEmptyLine++;
			_indentLevel = 0;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Item* pItemParent = _itemStack.back();
			for (int i = 0; i < _cntEmptyLine; i++) {
				ItemOwner* pItemOwner = new ItemOwner();
				do {
					Item* pItem = new Item(Item::Type::Line, pItemOwner);
					pItemParent->GetItemOwner()->push_back(pItem);
				} while (0);
				do {
					Item* pItem = new Item(Item::Type::Text, _text);
					pItemOwner->push_back(pItem);
				} while (0);
			}
			_text.clear();
			for (int i = 0; i < _indentLevel - GetIndentLevelForCodeBlock(); i++) _text += ' ';
			Gurax_PushbackEx(ch);
			_stat = Stat::CodeBlock;
		} else if (ch == '>' && _indentLevel == 0) {
			_indentLevel = -1;
			_quoteLevel = 1;
			_stat = Stat::CodeBlockUnderBlockQuote;
		} else {
			Gurax_PushbackEx(ch);
			EndCodeBlock();
			_stat = !IsWithin(Item::Type::ListItem)? Stat::LineTop :
				(_cntEmptyLine == 0)? Stat::ListItem_LineHead : Stat::ListItemNL;
		}
		break;
	}
	case Stat::FencedCodeBlockAttr: {
		if (IsEOL(ch) || IsEOF(ch)) {
			BeginFencedCodeBlock();
			_stat = Stat::FencedCodeBlock;
		} else {
			_field += ch;
		}
		break;
	}
	case Stat::FencedCodeBlock: {
		if (IsEOL(ch) || IsEOF(ch)) {
			Item* pItemParent = _itemStack.back();
			do {
				Item* pItem = new Item(Item::Type::Text, _text);
				_pItemOwner->push_back(pItem);
				_text.clear();
			} while (0);
			do {
				Item* pItem = new Item(Item::Type::Line, _pItemOwner.release());
				pItemParent->GetItemOwner()->push_back(pItem);
				_pItemOwner.reset(new ItemOwner());
			} while (0);
			_indentLevel = 0;
			_stat = Stat::FencedCodeBlock_LineHead;
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::FencedCodeBlock_LineHead: {
		if (ch == '`') {
			_textAhead.clear();
			_textAhead += ch;
			_stat = Stat::FencedCodeBlock_LineHead2nd;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::FencedCodeBlock;
		}
		break;
	}
	case Stat::FencedCodeBlock_LineHead2nd: {
		if (ch == '`') {
			_textAhead += ch;
			_stat = Stat::FencedCodeBlock_LineHead3rd;
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::FencedCodeBlock;
		}
		break;
	}
	case Stat::FencedCodeBlock_LineHead3rd: {
		if (ch == '`') {
			_stat = Stat::FencedCodeBlock_SkipToEOL;
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::FencedCodeBlock;
		}
		break;
	}
	case Stat::FencedCodeBlock_SkipToEOL: {
		if (IsEOL(ch) || IsEOF(ch)) {
			EndFencedCodeBlock();
			_stat = IsWithin(Item::Type::ListItem)? Stat::ListItem_LineHead : Stat::LineTop;
		} else {
			// nothing to do
		}
		break;
	}
	case Stat::CodeBlockUnderBlockQuote: {
		if (ch == ' ') {
			_indentLevel += 1;
		} else if (ch == '\t') {
			_indentLevel += WIDTH_Tab;
		} else if (_indentLevel >= GetIndentLevelForCodeBlock()) {
			Gurax_PushbackEx(ch);
			if (AdjustBlockQuote()) {
				EndCodeBlock();
				BeginCodeBlock(_textAhead.c_str());
				_stat = Stat::CodeBlock;
			} else {
				for (int i = 0; i < _indentLevel - GetIndentLevelForCodeBlock(); i++) _text += ' ';
				_stat = Stat::CodeBlock;
			}
		} else if (ch == '>') {
			_indentLevel = -1;
			_quoteLevel++;
		} else {
			Gurax_PushbackEx(ch);
			EndCodeBlock();
			AdjustBlockQuote();
			_stat = Stat::LineTop;
		}
		break;
	}
	case Stat::Backquote: {
		if (ch == '`') {
			_stat = Stat::CodeEsc;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Code;
		}
		break;
	}
	case Stat::Code: {
		if (ch == '`') {
			FlushText(Item::Type::Code, true, true);
			_stat = Stat::DecorationPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			FlushText(Item::Type::Code, true, true);
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::CodeEsc: {
		if (ch == '`') {
			_stat = Stat::CodeEsc_Backquote;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			FlushText(Item::Type::Code, true, true);
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::CodeEsc_Backquote: {
		if (ch == '`') {
			FlushText(Item::Type::Code, true, true);
			_stat = _statStack.Pop();
		} else {
			_text += '`';
			Gurax_PushbackEx(ch);
			_stat = Stat::CodeEsc;
		}
		break;
	}
	case Stat::Text: {
		if (CheckSpecialChar(ch)) {
			// nothing to do
		} else if (ch == '|') {
			if (IsTableMode()) {
				FlushTableCol(false);
				_stat = Stat::SkipWhiteAfterPipe;
			} else {
				_text += ch;
			}
		} else if (IsEOL(ch)) {
			if (IsTableMode()) {
				FlushTableCol(true);
				EndTableRow();
				if (IsTableGuideRow()) {
					_stat = Stat::SkipTableGuideRow;
				} else {
					_stat = Stat::LineTop;
				}
			} else if (IsMarkdownAcceptable()) {
				if (String::EndsWith<CharCase>(_text.c_str(), "  ") != nullptr) {
					FlushText(Item::Type::Text, false, true);
					Item* pItem = new Item(Item::Type::LineBreak);
					_pItemOwner->push_back(pItem);
				}
				_stat = Stat::LineTop;
			} else {
				_text += ch;
			}
		} else if (IsEOF(ch)) {
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::SkipWhiteAfterPipe: {
		if (String::IsWhite(ch)) {
			// nothing to do
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::SkipTableGuideRow: {
		if (IsEOL(ch)) {
			AdvanceTableRow();
			_stat = Stat::LineTop;
		} else {
			// nothing to do
		}
		break;
	}
	case Stat::Asterisk: {
		if (ch == '*') {
			BeginDecoration(Item::Type::Strong);
			_stat = Stat::AsteriskStrong;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			BeginDecoration(Item::Type::Emphasis);
			Gurax_PushbackEx(ch);
			_stat = Stat::AsteriskEmphasis;
		}
		break;
	}
	case Stat::AsteriskEmphasis: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::Escape;
		} else if (ch == '`') {
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(_stat);
			_stat = Stat::Backquote;
		} else if (ch == '*') {
			EndDecoration();
			_stat = Stat::DecorationPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			CancelDecoration("*");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::AsteriskStrong: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::Escape;
		} else if (ch == '`') {
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(_stat);
			_stat = Stat::Backquote;
		} else if (ch == '*') {
			_stat = Stat::AsteriskStrongEnd;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			CancelDecoration("**");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::AsteriskStrongEnd: {
		if (ch == '*') {
			EndDecoration();
			_stat = Stat::DecorationPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			ReplaceDecoration(Item::Type::Emphasis, "*");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			FlushText(Item::Type::Text, true, true);
			BeginDecoration(Item::Type::Emphasis);
			_statStack.Push(Stat::AsteriskStrong);
			Gurax_PushbackEx(ch);
			_stat = Stat::AsteriskEmphasis;
		}
		break;
	}
	case Stat::Underscore: {
		if (ch == '_') {
			BeginDecoration(Item::Type::Strong);
			_stat = Stat::UnderscoreStrong;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			BeginDecoration(Item::Type::Emphasis);
			Gurax_PushbackEx(ch);
			_stat = Stat::UnderscoreEmphasis;
		}
		break;
	}
	case Stat::UnderscoreEmphasis: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::Escape;
		} else if (ch == '`') {
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(_stat);
			_stat = Stat::Backquote;
		} else if (ch == '_') {
			_stat = Stat::UnderscoreEmphasisPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			CancelDecoration("_");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::UnderscoreEmphasisPost: {
		if (IsWordChar(ch)) {
			_text += '_';
			Gurax_PushbackEx(ch);
			_stat = Stat::UnderscoreEmphasis;
		} else {
			EndDecoration();
			Gurax_PushbackEx(ch);
			_stat = Stat::DecorationPost;
		}
		break;
	}
	case Stat::UnderscoreStrong: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::Escape;
		} else if (ch == '`') {
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(_stat);
			_stat = Stat::Backquote;
		} else if (ch == '_') {
			_stat = Stat::UnderscoreStrongEnd;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			CancelDecoration("__");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::UnderscoreStrongEnd: {
		if (ch == '_') {
			_stat = Stat::UnderscoreStrongPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			ReplaceDecoration(Item::Type::Emphasis, "_");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			FlushText(Item::Type::Text, true, true);
			BeginDecoration(Item::Type::Emphasis);
			_statStack.Push(Stat::UnderscoreStrong);
			Gurax_PushbackEx(ch);
			_stat = Stat::UnderscoreEmphasis;
		}
		break;
	}
	case Stat::UnderscoreStrongPost: {
		if (IsWordChar(ch)) {
			_text += "__";
			Gurax_PushbackEx(ch);
			_stat = Stat::UnderscoreStrong;
		} else {
			EndDecoration();
			Gurax_PushbackEx(ch);
			_stat = Stat::DecorationPost;
		}
		break;
	}
	case Stat::Tilda: {
		if (ch == '~') {
			BeginDecoration(Item::Type::Strike);
			_stat = Stat::TildaStrike;
		} else {
			_text += '~';
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		}
		break;
	}
	case Stat::TildaStrike: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::Escape;
		} else if (ch == '`') {
			FlushText(Item::Type::Text, false, false);
			_statStack.Push(_stat);
			_stat = Stat::Backquote;
		} else if (ch == '~') {
			_stat = Stat::TildaStrikeEnd;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			CancelDecoration("~~");
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_text += ch;
		}
		break;
	}
	case Stat::TildaStrikeEnd: {
		if (ch == '~') {
			EndDecoration();
			_stat = Stat::DecorationPost;
		} else {
			CancelDecoration("~~");
			_text += '~';
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		}
		break;
	}
	case Stat::DecorationPost: {
		_stat = _statStack.Pop();
		if (_stat == Stat::Text && IsEOL(ch)) {
			_decoPrecedingFlag = true;
		}
		Gurax_PushbackEx(ch);
		break;
	}
	case Stat::Entity: {
		if (ch == ';') {
			FlushText(Item::Type::Text, false, false);
			Item* pItem = new Item(Item::Type::Entity, _field);
			_pItemOwner->push_back(pItem);
			_stat = _statStack.Pop();
 		} else if (String::IsAlpha(ch)) {
			_textAhead += ch;
			_field += ch;
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		}
		break;
	}
	case Stat::AngleBracketFirst: {
		if (ch == '!') {
			_stat = Stat::CommentStartFirst;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::AngleBracket;
		}
		break;
	}
	case Stat::CommentStartFirst: {
		if (ch == '-') {
			_stat = Stat::CommentStartSecond;
		} else {
			Gurax_PushbackEx(ch);
			Gurax_PushbackEx('!');
			_stat = Stat::AngleBracket;
		}
		break;
	}
	case Stat::CommentStartSecond: {
		if (ch == '-') {
			FlushText(Item::Type::Text, false, false);
			_text = "<!--";
			_stat = Stat::Comment;
		} else {
			_textAhead += "!-";
			_field += "!-";
			Gurax_PushbackEx(ch);
			_stat = Stat::AngleBracket;
		}
		break;
	}
	case Stat::Comment: {
		_text += ch;
		if (ch == '-') {
			_stat = Stat::CommentEndFirst;
		} else {
			// nothing to do
		}
		break;
	}
	case Stat::CommentEndFirst: {
		_text += ch;
		if (ch == '-') {
			_stat = Stat::CommentEndSecond;
		} else {
			_stat = Stat::Comment;
		}
		break;
	}
	case Stat::CommentEndSecond: {
		_text += ch;
		if (ch == '>') {
			FlushText(Item::Type::Comment, false, false);
			_stat = _statStack.Pop();
		} else {
			_stat = Stat::Comment;
		}
		break;
	}
	case Stat::AngleBracket: {
		if (ch == '>') {
			String tagName, attrs;
			bool closedFlag = false;
			bool markdownAcceptableFlag = false;
			if (IsLink(_field.c_str())) {
				FlushText(Item::Type::Text, false, false);
				Item* pItemLink = new Item(Item::Type::Link, new ItemOwner());
				pItemLink->SetURL(_field);
				_pItemOwner->push_back(pItemLink);
				do {
					Item* pItem = new Item(Item::Type::Text, _field);
					pItemLink->GetItemOwner()->push_back(pItem);
				} while (0);
			} else if (IsBeginTag(_field.c_str(), tagName, attrs, closedFlag, markdownAcceptableFlag)) {
				const char* p = nullptr;
				int headerLevelShift = 0;
				if ((p = String::StartsWith<CharICase>(tagName.c_str(), "gurax.headerdown")) != nullptr) {
					headerLevelShift = +1;
				} else if ((p = String::StartsWith<CharICase>(tagName.c_str(), "gurax.headerup")) != nullptr) {
					headerLevelShift = -1;
				}
				if (p == nullptr) {
					BeginTag(tagName.c_str(), attrs.c_str(), closedFlag, markdownAcceptableFlag);
				} else {
					if (!closedFlag) {
						Error::Issue(ErrorType::FormatError, "the tag must be used as a single one.");
						return false;
					}
					if (*p != '\0') {
						char* pEnd = nullptr;
						ULong nMultiply = ::strtoul(p, &pEnd, 10);
						if (*pEnd != '\0' || nMultiply > 5) {
							Error::Issue(ErrorType::FormatError, "invalid tag name");
							return false;
						}
						headerLevelShift *= nMultiply;
					}
					_headerLevelOffset += headerLevelShift;
				}
			} else if (IsEndTag(_field.c_str(), tagName)) {
				if (!EndTag(tagName.c_str())) {
					Error::Issue(ErrorType::FormatError, "unbalanced tags at line %d", _iLine + 1);
					return false;
				}
			} else {
				_text += _textAhead;
				_text += ch;
			}
			_stat = _statStack.Pop();
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkAltTextPre: {
		if (ch == '[') {
			_textAhead += ch;
			_stat = Stat::LinkAltText;
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		}
		break;
	}
	case Stat::LinkAltText: {
		if (ch == ']') {
			_textAhead += ch;
			_pItemLink->SetText(_field.Strip(true, true));
			_stat = Stat::LinkTextPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkText: {
		if (ch == ']') {
			_textAhead += ch;
			do {
				Item* pItem = new Item(Item::Type::Text, _field.Strip(true, true));
				_pItemLink->GetItemOwner()->push_back(pItem);
			} while (0);
			_stat = Stat::LinkTextPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkTextPost: {
		if (ch == '[') {
			_field.clear();
			_stat = Stat::LinkRefId;
		} else if (ch == '(') {
			_textAhead += ch;
			_stat = Stat::LinkURLPre;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		}
		break;
	}
	case Stat::LinkRefId: {
		if (ch == ']') {
			FlushText(Item::Type::Text, false, false);
			_pItemLink->SetRefId(_field);
			_itemsLinkReferrer.push_back(_pItemLink.get());
			_pItemOwner->push_back(_pItemLink.release());
			_stat = _statStack.Pop();
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkURLPre: {
		if (ch == ' ' || ch == '\t') {
			_textAhead += ch;
		} else if (ch == '<') {
			_field.clear();
			_textAhead += ch;
			_stat = Stat::LinkURLAngle;
		} else {
			_field.clear();
			Gurax_PushbackEx(ch);
			_stat = Stat::LinkURL;
		}
		break;
	}
	case Stat::LinkURL: {
		if (ch == '"') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_field.clear();
			_stat = Stat::LinkTitleDoubleQuote;
		} else if (ch == '\'') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_field.clear();
			_stat = Stat::LinkTitleSingleQuote;
		} else if (ch == ')') {
			FlushText(Item::Type::Text, false, false);
			_pItemLink->SetURL(_field.Strip(true, true));
			_pItemOwner->push_back(_pItemLink.release());
			_decoPrecedingFlag = true;
			_stat = _statStack.Pop();
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkURLAngle: {
		if (ch == '>') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_stat = Stat::LinkURLAnglePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkURLAnglePost: {
		if (ch == '"') {
			_textAhead += ch;
			_field.clear();
			_stat = Stat::LinkTitleDoubleQuote;
		} else if (ch == '\'') {
			_textAhead += ch;
			_field.clear();
			_stat = Stat::LinkTitleSingleQuote;
		} else if (ch == ')') {
			FlushText(Item::Type::Text, false, false);
			_pItemOwner->push_back(_pItemLink.release());
			_decoPrecedingFlag = true;
			_stat = _statStack.Pop();
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
		}
		break;
	}
	case Stat::LinkTitleDoubleQuote: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::EscapeInLink;
		} else if (ch == '"') {
			_pItemLink->SetTitle(_field.c_str());
			_textAhead += ch;
			_stat = Stat::LinkTitlePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkTitleSingleQuote: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::EscapeInLink;
		} else if (ch == '\'') {
			_pItemLink->SetTitle(_field.c_str());
			_textAhead += ch;
			_stat = Stat::LinkTitlePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::LinkTitlePost: {
		if (ch == ' ' || ch == '\t') {
			_textAhead += ch;
		} else if (ch == ')') {
			FlushText(Item::Type::Text, false, false);
			_pItemOwner->push_back(_pItemLink.release());
			_decoPrecedingFlag = true;
			_stat = _statStack.Pop();
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = _statStack.Pop();
		}
		break;
	}
	case Stat::RefereeRefId: {
		if (ch == ']') {
			_pItemLink->SetRefId(_field);
			_textAhead += ch;
			_stat = Stat::RefereeRefIdPost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::RefereeRefIdPost: {
		if (ch == ':') {
			_textAhead += ch;
			_stat = Stat::RefereeURLPreWhite;
		} else {
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
			if (!FeedChars(String(_textAhead))) return false;
		}
		break;
	}
	case Stat::RefereeURLPreWhite: {
		if (ch == ' ' || ch == '\t') {
			_textAhead += ch;
			_stat = Stat::RefereeURLPre;
		} else {
			AppendJointSpace();
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::RefereeURLPre: {
		if (ch == ' ' || ch == '\t') {
			_textAhead += ch;
		} else if (ch == '<') {
			_field.clear();
			_stat = Stat::RefereeURLAngle;
		} else {
			_field.clear();
			Gurax_PushbackEx(ch);
			_stat = Stat::RefereeURL;
		}
		break;
	}
	case Stat::RefereeURL: {
		if (ch == '"') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_field.clear();
			_stat = Stat::RefereeTitleDoubleQuote;
		} else if (ch == '\'') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_field.clear();
			_stat = Stat::RefereeTitleSingleQuote;
		} else if (ch == '(') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_field.clear();
			_stat = Stat::RefereeTitleParenthesis;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			FlushText(Item::Type::Text, false, false);
			_pItemLink->SetURL(_field.Strip(true, true));
			AddItemReferee(_pItemLink.release());
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::RefereeURLAngle: {
		if (ch == '>') {
			_pItemLink->SetURL(_field.Strip(true, true));
			_textAhead += ch;
			_stat = Stat::RefereeURLAnglePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::RefereeURLAnglePost: {
		if (ch == '"') {
			_textAhead += ch;
			_field.clear();
			_stat = Stat::RefereeTitleDoubleQuote;
		} else if (ch == '\'') {
			_textAhead += ch;
			_field.clear();
			_stat = Stat::RefereeTitleSingleQuote;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			FlushText(Item::Type::Text, false, false);
			AddItemReferee(_pItemLink.release());
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
		}
		break;
	}
	case Stat::RefereeTitleDoubleQuote: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::EscapeInLink;
		} else if (ch == '"') {
			_pItemLink->SetTitle(_field.c_str());
			_textAhead += ch;
			_stat = Stat::RefereeTitlePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::RefereeTitleSingleQuote: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::EscapeInLink;
		} else if (ch == '\'') {
			_pItemLink->SetTitle(_field.c_str());
			_textAhead += ch;
			_stat = Stat::RefereeTitlePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::RefereeTitleParenthesis: {
		if (ch == '\\') {
			_statStack.Push(_stat);
			_stat = Stat::EscapeInLink;
		} else if (ch == ')') {
			_pItemLink->SetTitle(_field.c_str());
			_textAhead += ch;
			_stat = Stat::RefereeTitlePost;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_textAhead += ch;
			_field += ch;
		}
		break;
	}
	case Stat::RefereeTitlePost: {
		if (ch == ' ' || ch == '\t') {
			_textAhead += ch;
		} else if (IsEOL(ch) || IsEOF(ch)) {
			FlushText(Item::Type::Text, false, false);
			AddItemReferee(_pItemLink.release());
			Gurax_PushbackEx(ch);
			_stat = Stat::LineTop;
		} else {
			_text += _textAhead;
			Gurax_PushbackEx(ch);
			_stat = Stat::Text;
		}
		break;
	}
	case Stat::Escape: {
		_text += ch;
		_stat = _statStack.Pop();
		break;
	}
	case Stat::EscapeInLink: {
		_textAhead += ch;
		_field += ch;
		_stat = _statStack.Pop();
		break;
	}
	}
	Gurax_EndPushbackRegionEx();
	if (IsEOL(ch)) {
		_iLine++;
		_iCol = 0;
	} else if (ch == '\t') {
		_iCol = (_iCol / WIDTH_Tab) * WIDTH_Tab + WIDTH_Tab;
	} else {
		_iCol++;
	}
	_chPrev = ch;
	return true;
}

bool Document::CheckSpecialChar(char ch)
{
	if (ch == '\\') {
		if (!IsMarkdownAcceptable()) return false;
		_statStack.Push(_stat);
		_stat = Stat::Escape;
		return true;
	} else if (ch == '`') {
		if (!IsMarkdownAcceptable()) return false;
		FlushText(Item::Type::Text, false, false);
		_statStack.Push(_stat);
		_stat = Stat::Backquote;
		return true;
	} else if (ch == '*') {
		if (!IsMarkdownAcceptable()) return false;
		FlushText(Item::Type::Text, false, false);
		_statStack.Push(_stat);
		_stat = Stat::Asterisk;
		return true;
	} else if (ch == '_' && !IsWordChar(_chPrev)) {
		if (!IsMarkdownAcceptable()) return false;
		FlushText(Item::Type::Text, false, false);
		_statStack.Push(_stat);
		_stat = Stat::Underscore;
		return true;
	} else if (ch == '~') {
		if (!IsMarkdownAcceptable()) return false;
		FlushText(Item::Type::Text, false, false);
		_statStack.Push(_stat);
		_stat = Stat::Tilda;
		return true;
	} else if (ch == '&') {
		_textAhead.clear();
		_field.clear();
		_textAhead += ch;
		_statStack.Push(_stat);
		_stat = Stat::Entity;
		return true;
	} else if (ch == '<') {
		_textAhead.clear();
		_field.clear();
		_textAhead += ch;
		_statStack.Push(_stat);
		_stat = Stat::AngleBracketFirst;
		return true;
	} else if (ch == '[') {
		if (!IsMarkdownAcceptable()) return false;
		_pItemLink.reset(new Item(Item::Type::Link, new ItemOwner()));
		_textAhead.clear();
		_field.clear();
		_textAhead += ch;
		_statStack.Push(_stat);
		_stat = Stat::LinkText;
		return true;
	} else if (ch == '!') {
		if (!IsMarkdownAcceptable()) return false;
		_pItemLink.reset(new Item(Item::Type::Image));
		_textAhead.clear();
		_field.clear();
		_textAhead += ch;
		_statStack.Push(_stat);
		_stat = Stat::LinkAltTextPre;
		return true;
	}
	return false;
}

bool Document::AdjustBlockQuote()
{
	bool adjustFlag = false;
	int quoteLevel = _itemStack.CountQuoteLevel();
	if (quoteLevel < _quoteLevel) {
		FlushItem(Item::Type::Paragraph, false, false);
		for ( ; quoteLevel < _quoteLevel; quoteLevel++) {
			Item* pItemParent = _itemStack.back();
			Item* pItem = new Item(Item::Type::BlockQuote, new ItemOwner());
			pItemParent->GetItemOwner()->push_back(pItem);
			_itemStack.push_back(pItem);
		}
		adjustFlag = true;
	} else if (quoteLevel > _quoteLevel) {
		FlushItem(Item::Type::Paragraph, false, false);
		while (quoteLevel > _quoteLevel) {
			Item* pItem = _itemStack.back();
			if (pItem->IsBlockQuote()) quoteLevel--;
			_itemStack.pop_back();
		}
		adjustFlag = true;
	}
	return adjustFlag;
}

void Document::AppendJointSpace()
{
	if (!_text.empty() && !String::IsWhite(_text[_text.size() - 1])) _text += ' ';
}

void Document::FlushText(Item::Type type, bool stripLeftFlag, bool stripRightFlag)
{
	String text = String::Strip(_text.c_str(), stripLeftFlag, stripRightFlag);
	if (text.empty()) {
		// nothing to do
	} else if (!_pItemOwner->empty() && _pItemOwner->back()->GetType() == type) {
		_pItemOwner->back()->AppendText(text);
	} else {
		Item* pItem = new Item(type, text);
		_pItemOwner->push_back(pItem);
	}
	_text.clear();
}

void Document::FlushItem(Item::Type type, bool stripLeftFlag, bool stripRightFlag)
{
	Item* pItemParent = _itemStack.back();
	FlushText(Item::Type::Text, stripLeftFlag, stripRightFlag);
	if (!pItemParent->GetItemOwner()->empty() && pItemParent->GetItemOwner()->back()->IsInlineTag()) {
		pItemParent->GetItemOwner()->Store(*_pItemOwner);
		_pItemOwner.reset(new ItemOwner());
	} else {
		_pItemOwner->StripTextAtFront(true, false);
		if (!_pItemOwner->empty()) {
			Item* pItem = new Item(type, _pItemOwner.release());
			pItemParent->GetItemOwner()->push_back(pItem);
			_pItemOwner.reset(new ItemOwner());
		}
	}
}

void Document::FlushElement(bool stripLeftFlag, bool stripRightFlag)
{
	Item* pItemParent = _itemStack.back();
	FlushText(Item::Type::Text, stripLeftFlag, stripRightFlag);
	if (pItemParent->GetItemOwner()->empty()) {
		_pItemOwner->StripTextAtFront(true, false);
		pItemParent->GetItemOwner()->Store(*_pItemOwner);
		_pItemOwner.reset(new ItemOwner());
	} else if (pItemParent->GetItemOwner()->back()->IsInlineTag()) {
		pItemParent->GetItemOwner()->Store(*_pItemOwner);
		_pItemOwner.reset(new ItemOwner());
	} else {
		_pItemOwner->StripTextAtFront(true, false);
		if (!_pItemOwner->empty()) {
			Item* pItem = new Item(Item::Type::Paragraph, _pItemOwner.release());
			pItemParent->GetItemOwner()->push_back(pItem);
			_pItemOwner.reset(new ItemOwner());
		}
	}
}

void Document::BeginTable()
{
	Item* pItemParent = _itemStack.back();
	Item* pItem = new Item(Item::Type::Tag, new ItemOwner());
	pItem->SetText("table");
	pItemParent->GetItemOwner()->push_back(pItem);
	_itemStack.push_back(pItem);
	_iTableRow = 0;
}

void Document::EndTable()
{
	while (!_itemStack.empty()) {
		Item* pItem = _itemStack.back();
		_itemStack.pop_back();
		if (pItem->IsTag() && ::strcmp(pItem->GetText(), "table") == 0) break;
	}
	_iTableRow = -1;
}

void Document::BeginTableRow()
{
	Item* pItemParent = _itemStack.back();
	Item* pItem = new Item(Item::Type::Tag, new ItemOwner());
	pItem->SetText("tr");
	pItemParent->GetItemOwner()->push_back(pItem);
	_itemStack.push_back(pItem);
	_iTableCol = 0;
}

void Document::EndTableRow()
{
	_itemStack.pop_back();
	AdvanceTableRow();
}

void Document::FlushTableCol(bool eolFlag)
{
	bool stripLeftFlag = false, stripRightFlag = true;
	Item* pItemParent = _itemStack.back();
	FlushText(Item::Type::Text, stripLeftFlag, stripRightFlag);
	if (!eolFlag || !_pItemOwner->empty()) {
		_pItemOwner->StripTextAtFront(true, false);
		Item* pItem = new Item(Item::Type::Tag, _pItemOwner.release());
		pItem->SetText(IsTableFirstRow()? "th" : "td");
		Align align = (static_cast<size_t>(_iTableCol) < _alignList.size())? _alignList[_iTableCol] : Align::Left;
		pItem->SetAlign(align);
		if (align == Align::Center) {
			pItem->SetAttrs("style=\"text-align:center\"");
		} else if (align == Align::Right) {
			pItem->SetAttrs("style=\"text-align:right\"");
		}
		pItemParent->GetItemOwner()->push_back(pItem);
		_pItemOwner.reset(new ItemOwner());
		_iTableCol++;
	}
}

void Document::BeginCodeBlock(const char* textInit)
{
	FlushItem(Item::Type::Paragraph, false, false);
	for (int i = 0; i < _indentLevel - GetIndentLevelForCodeBlock(); i++) _text += ' ';
	if (textInit != nullptr) _text += textInit;
	do {
		Item* pItemParent = _itemStack.back();
		Item* pItem = new Item(Item::Type::CodeBlock, new ItemOwner());
		pItem->SetIndentLevel(_indentLevel);
		pItemParent->GetItemOwner()->push_back(pItem);
		_itemStack.push_back(pItem);
	} while (0);
}

void Document::EndCodeBlock()
{
	_itemStack.pop_back();
}

void Document::BeginFencedCodeBlock()
{
	FlushItem(Item::Type::Paragraph, false, false);
	do {
		Item* pItemParent = _itemStack.back();
		Item* pItem = new Item(Item::Type::CodeBlock, new ItemOwner());
		pItem->SetIndentLevel(_indentLevel);
		pItemParent->GetItemOwner()->push_back(pItem);
		_itemStack.push_back(pItem);
	} while (0);
}

void Document::EndFencedCodeBlock()
{
	_itemStack.pop_back();
}

// type must be Type::UList or Type::OList
void Document::BeginListItem(Item::Type type)
{
	Item* pItemParent = _itemStack.back();
	while (_indentLevel < pItemParent->GetIndentLevel()) {
		if (pItemParent->IsRoot() || pItemParent->IsBlockQuote() || pItemParent->IsTag()) break;
		if (pItemParent->IsListItem()) {
			EndListItem();
		} else {
			_itemStack.pop_back();
		}
		pItemParent = _itemStack.back();
	}
	if (pItemParent->IsListItem()) {
		if (_indentLevel == pItemParent->GetIndentLevel()) {
			EndListItem();
			pItemParent = _itemStack.back();
		} else {
			FlushElement();
		}
	}
	if (pItemParent->IsRoot() || pItemParent->IsBlockQuote() || pItemParent->IsTag() ||
		pItemParent->GetIndentLevel() < _indentLevel) {
		Item* pItem = new Item(type, new ItemOwner());
		pItem->SetIndentLevel(_indentLevel);
		pItemParent->GetItemOwner()->push_back(pItem);
		_itemStack.push_back(pItem);
	} else if (pItemParent->GetType() != type) {
		_itemStack.pop_back();
		Item* pItemParent = _itemStack.back();
		Item* pItem = new Item(type, new ItemOwner());
		pItem->SetIndentLevel(_indentLevel);
		pItemParent->GetItemOwner()->push_back(pItem);
		_itemStack.push_back(pItem);
	}
	do {
		Item* pItemParent = _itemStack.back();
		Item* pItem = new Item(Item::Type::ListItem, new ItemOwner());
		pItem->SetIndentLevel(_indentLevel);
		pItem->SetIndentLevelItemBody(_iCol);
		pItemParent->GetItemOwner()->push_back(pItem);
		_itemStack.push_back(pItem);
	} while (0);
}

void Document::EndListItem()
{
	if (_itemStack.back()->IsListItem()) {
		// EndTag() may already have ended the list.
		FlushElement();
		_itemStack.pop_back();
	}
}

void Document::BeginDecoration(Item::Type type)
{
	Item* pItem = new Item(type, new ItemOwner());
	_pItemOwner->push_back(pItem);
	_itemOwnerStack.Push(_pItemOwner.release());
	_pItemOwner.reset(pItem->GetItemOwner()->Reference());
}

void Document::EndDecoration()
{
	FlushText(Item::Type::Text, false, false);
	_pItemOwner.reset(_itemOwnerStack.Pop());
}

void Document::CancelDecoration(const char* textAhead)
{
	_text.insert(0, textAhead);
	FlushText(Item::Type::Text, false, false);
	_pItemOwner.reset(_itemOwnerStack.Pop());
	Item* pItemToCancel = _pItemOwner->back();
	_pItemOwner->pop_back();
	ItemOwner& itemOwnerToCancel =* pItemToCancel->GetItemOwner();
	ItemOwner::iterator ppItem = itemOwnerToCancel.begin();
	if (ppItem != itemOwnerToCancel.end() && (*ppItem)->IsText() &&
		!_pItemOwner->empty() && _pItemOwner->back()->IsText()) {
		_pItemOwner->back()->AppendText((*ppItem)->GetText());
		ppItem++;
	}
	for ( ; ppItem != itemOwnerToCancel.end(); ppItem++) {
		_pItemOwner->push_back((*ppItem)->Reference());
	}
	Item::Delete(pItemToCancel);
}

void Document::ReplaceDecoration(Item::Type type, const char* textAhead)
{
	_text.insert(0, textAhead);
	FlushText(Item::Type::Text, false, false);
	_pItemOwner.reset(_itemOwnerStack.Pop());
	Item* pItemToReplace = _pItemOwner->back();
	pItemToReplace->SetType(type);
}

// Marks the beginning of HTML tag.
void Document::BeginTag(const char* tagName, const char* attrs, bool closedFlag, bool markdownAcceptableFlag)
{
	Item* pItemParent = _itemStack.back();
	FlushElement();
	Item* pItem = new Item(Item::Type::Tag);
	pItem->SetMarkdownAcceptableFlag(markdownAcceptableFlag);
	pItem->SetText(tagName);
	if (attrs[0] != '\0') pItem->SetAttrs(attrs);
	pItemParent->GetItemOwner()->push_back(pItem);
	if (!closedFlag) {
		pItem->SetItemOwner(new ItemOwner());
		_itemStack.push_back(pItem);
		_itemStackTag.push_back(pItem);
	}
}

// Marks the ending of HTML tag.
bool Document::EndTag(const char* tagName)
{
	if (!IsWithinTag() || ::strcmp(_itemStackTag.back()->GetText(), tagName) != 0) {
		return false;
	}
	FlushElement(false, true);
	bool listItemFoundFlag = false;
	for (;;) {
		Item* pItem = _itemStack.back();
		_itemStack.pop_back();
		if (pItem->IsListItem()) {
			listItemFoundFlag = true;
		} else if (pItem->IsTag()) {
			break;
		}
	}
	_itemStackTag.pop_back();
	// Modify the stat value in the stack if list item has existed.
	if (listItemFoundFlag && !_statStack.empty() && _statStack.back() == Stat::ListItem) {
		_statStack.Pop();
		_statStack.Push(Stat::Text);
	}
	return true;
}

int Document::GetIndentLevel() const
{
	for (auto ppItem = _itemStack.rbegin(); ppItem != _itemStack.rend(); ppItem++) {
		const Item* pItem = *ppItem;
		if (pItem->IsListItem()) {
			return pItem->GetIndentLevelItemBody();
		}
	}
	return 0;
}

int Document::GetIndentLevelForCodeBlock() const
{
	return GetIndentLevel() + INDENT_CodeBlock;
}

void Document::UpdateIndentLevelItemBody(int indentLevelItemBody)
{
	for (Item* pItem : _itemStack) {
		if (pItem->IsListItem()) {
			pItem->SetIndentLevelItemBody(indentLevelItemBody);
			break;
		}
	}
}

bool Document::IsWithin(Item::Type type) const
{
	for (auto ppItem = _itemStack.rbegin(); ppItem != _itemStack.rend(); ppItem++) {
		const Item* pItem = *ppItem;
		if (pItem->GetType() == type) return true;
	}
	return false;
}

Item::Type Document::HeaderLevelToItemType(int headerLevel)
{
	return
		(headerLevel <= 1)? Item::Type::Header1 :
		(headerLevel == 2)? Item::Type::Header2 :
		(headerLevel == 3)? Item::Type::Header3 :
		(headerLevel == 4)? Item::Type::Header4 :
		(headerLevel == 5)? Item::Type::Header5 :
		(headerLevel == 6)? Item::Type::Header6 :
		Item::Type::Header6;
}

bool Document::IsAtxHeader2(const char* text)
{
	for (const char* p = text; ; p++) {
		char ch = *p;
		::printf("[%c]\n", ch);
		if (ch != '-') return false;
	}
	return true;
}

bool Document::IsHorzRule(const char* text)
{
	return ::strlen(text) >= 3;
}

bool Document::IsLink(const char* text)
{
	enum class StatEx {
		Begin,
		Head,
		EMail,
		EMailDot,
		EMailAfterDot,
		URL,
	} statEx = StatEx::Begin;
	String head;
	for (const char *p = text; ; p++) {
		char ch = *p;
		switch (statEx) {
		case StatEx::Begin: {
			if (String::IsAlpha(ch)) {
				head += ch;
				statEx = StatEx::Head;
			} else {
				return false;
			}
			break;
		}
		case StatEx::Head: {
			if (String::IsAlpha(ch)) {
				head += ch;
			} else if (ch == '@') {
				statEx = StatEx::EMail;
			} else if (ch == ':') {
				statEx = StatEx::URL;
			} else {
				return false;
			}
			break;
		}
		case StatEx::EMail: {
			if (String::IsAlpha(ch)) {
				// nothing to do
			} else if (ch == '.') {
				statEx = StatEx::EMailDot;
			} else {
				return false;
			}
			break;
		}
		case StatEx::EMailDot: {
			if (String::IsAlpha(ch)) {
				statEx = StatEx::EMailAfterDot;
			} else {
				return false;
			}
			break;
		}
		case StatEx::EMailAfterDot: {
			if (String::IsAlpha(ch)) {
				// nothing to do
			} else if (ch == '.') {
				statEx = StatEx::EMailDot;
			} else if (ch == '\0') {
				// nothing to do
			} else {
				return false;
			}
			break;
		}
		case StatEx::URL: {
			if (String::IsURIC(ch)) {
				// nothing to do
			} else if (ch == '\0') {
				if (!(head == "http" || head == "https" || head == "ftp")) {
					return false;
				}
			} else {
				return false;
			}
			break;
		}
		}
		if (ch == '\0') break;
	}
	return true;
}

bool Document::IsBeginTag(const char* text, String& tagName,
						  String& attrs, bool& closedFlag, bool& markdownAcceptableFlag)
{
	enum class StatEx {
		Begin,
		AfterSpecialChar,
		TagName,
		AttrsPre,
		Attrs,
		Slash,
	} statEx = StatEx::Begin;
	tagName.clear();
	attrs.clear();
	closedFlag = false;
	markdownAcceptableFlag = false;
	for (const char* p = text; ; p++) {
		char ch = *p;
		switch (statEx) {
		case StatEx::Begin: {
			if (IsTagNameFirst(ch)) {
				tagName += ch;
				statEx = StatEx::TagName;
			} else if (ch == '@') {
				// A special form of tag <@tag> within which MarkDown format is acceptable.
				markdownAcceptableFlag = true;
				statEx = StatEx::AfterSpecialChar;
			} else {
				return false;
			}
			break;
		}
		case StatEx::AfterSpecialChar: {
			if (IsTagNameFirst(ch)) {
				tagName += ch;
				statEx = StatEx::TagName;
			} else {
				return false;
			}
			break;
		}
		case StatEx::TagName: {
			if (IsTagNameFollower(ch)) {
				tagName += ch;
			} else if (ch == '/') {
				statEx = StatEx::Slash;
			} else if (ch == '\0') {
				// nothing to do
			} else if (ch == ' ' || ch == '\t') {
				statEx = StatEx::AttrsPre;
			} else {
				return false;
			}
			break;
		}
		case StatEx::AttrsPre: {
			if (ch == ' ' || ch == '\t') {
				// nothing to do
			} else if (String::IsAlpha(ch)) {
				attrs += ch;
				statEx = StatEx::Attrs;
			} else if (ch == '/') {
				statEx = StatEx::Slash;
			} else if (ch == '\0') {
				return false;	// not allow "<hoge  >"
			} else {
				return false;
			}
			break;
		}
		case StatEx::Attrs: {
			if (ch == '\0') {
				// nothing to do
			} else if (ch == '/') {
				statEx = StatEx::Slash;
			} else {
				attrs += ch;
			}
			break;
		}
		case StatEx::Slash: {
			if (ch == '\0') {
				closedFlag = true;
			} else {
				attrs += '/';
				attrs += ch;
				statEx = StatEx::Attrs;
			}
			break;
		}
		}
		if (ch == '\0') break;
	}
	return true;
}

bool Document::IsEndTag(const char* text, String& tagName)
{
	enum class StatEx {
		Begin,
		TagNameFirst,
		AfterSpecialChar,
		TagName,
	} statEx = StatEx::Begin;
	tagName.clear();
	for (const char *p = text; ; p++) {
		char ch = *p;
		switch (statEx) {
		case StatEx::Begin: {
			if (ch == '/') {
				statEx = StatEx::TagNameFirst;
			} else {
				return false;
			}
			break;
		}
		case StatEx::TagNameFirst: {
			if (IsTagNameFirst(ch)) {
				tagName += ch;
				statEx = StatEx::TagName;
			} else if (ch == '@') {
				// A special form of tag: </@tag>.
				statEx = StatEx::AfterSpecialChar;
			} else {
				return false;
			}
			break;
		}
		case StatEx::AfterSpecialChar: {
			if (IsTagNameFirst(ch)) {
				tagName += ch;
				statEx = StatEx::TagName;
			} else {
				return false;
			}
			break;
		}
		case StatEx::TagName: {
			if (IsTagNameFollower(ch)) {
				tagName += ch;
			} else if (ch == '\0') {
				// nothing to do
			} else {
				return false;
			}
			break;
		}
		}
		if (ch == '\0') break;
	}
	return true;
}

String Document::ToString(const StringStyle& ss) const
{
	return "Document";
}

Gurax_EndModuleScope(markdown)
