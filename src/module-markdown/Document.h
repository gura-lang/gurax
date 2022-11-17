//==============================================================================
// Document.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_DOCUMENT_H
#define GURAX_MODULE_MARKDOWN_DOCUMENT_H
#include <gurax.h>
#include "Item.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Document : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Document);
public:
	enum class Stat {
		LineTop,
		LineHead,
		LineHeadTable,
		LineHeadNL,
		BlockQuote,
		EqualAtHead,
		AsteriskAtHead,
		PlusAtHead,
		HyphenAtHead,
		DigitAtHead,
		DigitDotAtHead,
		BackquoteAtHead,
		BackquoteAtHead2nd,
		SetextHeaderHead,
		SetextHeaderPre,
		SetextHeader,
		SetextHeaderPost,
		AtxHeader1,
		AtxHeader2,
		UListItemPre,
		OListItemPre,
		ListItem,
		ListItem_LineHead,
		ListItem_BlockQuoteAtHead,
		ListItem_AsteriskAtHead,
		ListItem_PlusAtHead,
		ListItem_HyphenAtHead,
		ListItem_DigitAtHead,
		ListItem_DigitDotAtHead,
		ListItemNL,
		ListItemNL_AsteriskAtHead,
		ListItemNL_PlusAtHead,
		ListItemNL_HyphenAtHead,
		ListItemNL_DigitAtHead,
		ListItemNL_DigitDotAtHead,
		CodeBlock,
		CodeBlock_LineHead,
		FencedCodeBlockAttr,
		FencedCodeBlock,
		FencedCodeBlock_LineHead,
		FencedCodeBlock_LineHead2nd,
		FencedCodeBlock_LineHead3rd,
		FencedCodeBlock_SkipToEOL,
		CodeBlockUnderBlockQuote,
		Backquote,
		Code,
		CodeEsc,
		CodeEsc_Backquote,
		Text,
		SkipWhiteAfterPipe,
		SkipTableGuideRow,
		Asterisk,
		AsteriskEmphasis,
		AsteriskStrong,
		AsteriskStrongEnd,
		Underscore,
		UnderscoreEmphasis,
		UnderscoreEmphasisPost,
		UnderscoreStrong,
		UnderscoreStrongEnd,
		UnderscoreStrongPost,
		Tilda,
		TildaStrike,
		TildaStrikeEnd,
		DecorationPost,
		Entity,
		AngleBracketFirst,
		AngleBracket,
		CommentStartFirst,
		CommentStartSecond,
		Comment,
		CommentEndFirst,
		CommentEndSecond,
		LinkAltTextPre,
		LinkAltText,
		LinkText,
		LinkTextPost,
		LinkRefId,
		LinkURLPre,
		LinkURL,
		LinkURLAngle,
		LinkURLAnglePost,
		LinkTitleDoubleQuote,
		LinkTitleSingleQuote,
		LinkTitlePost,
		RefereeRefId,
		RefereeRefIdPost,
		RefereeURLPreWhite,
		RefereeURLPre,
		RefereeURL,
		RefereeURLAngle,
		RefereeURLAnglePost,
		RefereeTitleDoubleQuote,
		RefereeTitleSingleQuote,
		RefereeTitleParenthesis,
		RefereeTitlePost,
		Escape,
		EscapeInLink,
	};
	class StatStack : public ListBase<Stat> {
	public:
		void Push(Stat stat) { push_back(stat); }
		Stat Pop() {
			Stat stat = back();
			pop_back();
			return stat;
		}
	};
private:
	bool _resolvedFlag;
	bool _decoPrecedingFlag;
	int _iTableRow;
	int _iTableCol;
	Stat _stat;
	int _iLine;
	int _iCol;
	char _chPrev;
	StatStack _statStack;
	int _indentLevel;
	int _indentLevelTableTop;
	int _headerLevel;
	int _headerLevelOffset;
	int _quoteLevel;
	int _cntEmptyLine;
	String _text;
	String _textAhead;
	String _field;
	RefPtr<ItemOwner> _pItemOwner;
	RefPtr<ItemOwner> _pItemRefereeOwner;
	RefPtr<Item> _pItemRoot;
	RefPtr<Item> _pItemLink;
	ItemList _itemsLinkReferrer;
	ItemStack _itemStack;
	ItemStack _itemStackTag;
	ItemOwnerStack _itemOwnerStack;
	AlignList _alignList;
public:
	// Constructor
	Document();
	// Copy constructor/operator
	Document(const Document& src) = delete;
	Document& operator=(const Document& src) = delete;
	// Move constructor/operator
	Document(Document&& src) = delete;
	Document& operator=(Document&& src) noexcept = delete;
protected:
	~Document() = default;
public:
	void SetHeaderLevelOffset(int headerLevelOffset) { _headerLevelOffset = headerLevelOffset; }
	bool ParseCharSeq(CharSeq& charSeq);
	bool ParseStream(Stream& stream) { return ParseCharSeq(stream); }
	bool ParseString(const char* str);
	void AddItemReferee(Item* pItem);
	void ResolveReference();
	const Item& GetItemRoot() { return *_pItemRoot; }
	const ItemOwner& GetItemRefereeOwner() const { return *_pItemRefereeOwner; }
private:
	bool FeedChars(const String& text);
	bool FeedChar(char ch);
	bool CheckSpecialChar(char ch);
	bool AdjustBlockQuote();
	void AppendJointSpace();
	void FlushText(Item::Type type, bool stripLeftFlag, bool stripRightFlag);
	void FlushItem(Item::Type type, bool stripLeftFlag, bool stripRightFlag);
	void FlushElement(bool stripLeftFlag = false, bool stripRightFlag = false);
	void BeginTable();
	void EndTable();
	void BeginTableRow();
	void EndTableRow();
	void FlushTableCol(bool eolFlag);
	void BeginCodeBlock(const char* textInit);
	void EndCodeBlock();
	void BeginFencedCodeBlock();
	void EndFencedCodeBlock();
	//void BeginCodeBlockInList(const char* textInit);
	//void EndCodeBlockInList();
	void BeginListItem(Item::Type type);
	void EndListItem();
	void BeginDecoration(Item::Type type);
	void EndDecoration();
	void CancelDecoration(const char* textAhead);
	void ReplaceDecoration(Item::Type type, const char* textAhead);
	void BeginTag(const char* tagName, const char* attrs, bool closedFlag, bool markdownAcceptableFlag);
	bool EndTag(const char* tagName);
	int GetIndentLevel() const;
	int GetIndentLevelForCodeBlock() const;
	void UpdateIndentLevelItemBody(int indentLevelItemBody);
	bool IsWithin(Item::Type type) const;
	static Item::Type HeaderLevelToItemType(int headerLevel);
	static bool IsAtxHeader2(const char* text);
	static bool IsHorzRule(const char* text);
	static bool IsLink(const char* text);
	static bool IsBeginTag(const char* text, String& tagName,
						   String& attrs, bool& closedFlag, bool& markdownAcceptableFlag);
	static bool IsEndTag(const char* text, String& tagName);
	bool IsWordChar(char ch) {
		return (String::GetCTypes(ch) &
				(String::CType::Alpha | String::CType::Digit |
				 String::CType::UTF8First | String::CType::UTF8Follower)) != 0;
	}
	static bool IsEOL(char ch) { return ch == '\n'; }
	static bool IsEOF(char ch) { return ch == '\0'; }
	static bool IsDigit(char ch) { return '0' <= ch && ch <= '9'; }
	void AdvanceTableRow() { if (_iTableRow >= 0) _iTableRow++; }
	bool IsTableMode() const { return _iTableRow >= 0; }
	bool IsTableFirstRow() const { return _iTableRow == 0; }
	bool IsTableGuideRow() const { return _iTableRow == 1; }
	bool IsTableTrailingRow() const { return _iTableRow >= 2; }
	bool IsWithinTag() const { return !_itemStackTag.empty(); }
	bool IsMarkdownAcceptable() const {
		return _itemStackTag.empty() || _itemStackTag.back()->GetMarkdownAcceptableFlag();
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Document& other) const { return this == &other; }
	bool IsEqualTo(const Document& other) const { return IsIdentical(other); }
	bool IsLessThan(const Document& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(markdown)

#endif
