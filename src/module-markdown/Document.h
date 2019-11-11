//==============================================================================
// Document.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_DOCUMENT_H
#define GURAX_MODULE_MARKDOWN_DOCUMENT_H
#include <gurax.h>

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Document : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Document);
public:
	// Constructor
	Document() {}
	// Copy constructor/operator
	Document(const Document& src) = delete;
	Document& operator=(const Document& src) = delete;
	// Move constructor/operator
	Document(Document&& src) = delete;
	Document& operator=(Document&& src) noexcept = delete;
protected:
	~Document() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Document& other) const { return this == &other; }
	bool IsEqualTo(const Document& other) const { return IsIdentical(other); }
	bool IsLessThan(const Document& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

#if 0
class Document {
private:
	enum Stat {
		STAT_LineTop,
		STAT_LineHead,
		STAT_LineHeadTable,
		STAT_LineHeadNL,
		STAT_BlockQuote,
		STAT_EqualAtHead,
		STAT_AsteriskAtHead,
		STAT_PlusAtHead,
		STAT_HyphenAtHead,
		STAT_DigitAtHead,
		STAT_DigitDotAtHead,
		STAT_BackquoteAtHead,
		STAT_BackquoteAtHead2nd,
		STAT_SetextHeaderHead,
		STAT_SetextHeaderPre,
		STAT_SetextHeader,
		STAT_SetextHeaderPost,
		STAT_AtxHeader1,
		STAT_AtxHeader2,
		STAT_UListItemPre,
		STAT_OListItemPre,
		STAT_ListItem,
		STAT_ListItem_LineHead,
		STAT_ListItem_BlockQuoteAtHead,
		STAT_ListItem_AsteriskAtHead,
		STAT_ListItem_PlusAtHead,
		STAT_ListItem_HyphenAtHead,
		STAT_ListItem_DigitAtHead,
		STAT_ListItem_DigitDotAtHead,
		STAT_ListItemNL,
		STAT_ListItemNL_AsteriskAtHead,
		STAT_ListItemNL_PlusAtHead,
		STAT_ListItemNL_HyphenAtHead,
		STAT_ListItemNL_DigitAtHead,
		STAT_ListItemNL_DigitDotAtHead,
		STAT_CodeBlock,
		STAT_CodeBlock_LineHead,
		STAT_FencedCodeBlockAttr,
		STAT_FencedCodeBlock,
		STAT_FencedCodeBlock_LineHead,
		STAT_FencedCodeBlock_LineHead2nd,
		STAT_FencedCodeBlock_LineHead3rd,
		STAT_FencedCodeBlock_SkipToEOL,
		STAT_CodeBlockUnderBlockQuote,
		STAT_Backquote,
		STAT_Code,
		STAT_CodeEsc,
		STAT_CodeEsc_Backquote,
		STAT_Text,
		STAT_SkipWhiteAfterPipe,
		STAT_SkipTableGuideRow,
		STAT_Asterisk,
		STAT_AsteriskEmphasis,
		STAT_AsteriskStrong,
		STAT_AsteriskStrongEnd,
		STAT_Underscore,
		STAT_UnderscoreEmphasis,
		STAT_UnderscoreEmphasisPost,
		STAT_UnderscoreStrong,
		STAT_UnderscoreStrongEnd,
		STAT_UnderscoreStrongPost,
		STAT_Tilda,
		STAT_TildaStrike,
		STAT_TildaStrikeEnd,
		STAT_DecorationPost,
		STAT_Entity,
		STAT_AngleBracketFirst,
		STAT_AngleBracket,
		STAT_CommentStartFirst,
		STAT_CommentStartSecond,
		STAT_Comment,
		STAT_CommentEndFirst,
		STAT_CommentEndSecond,
		STAT_LinkAltTextPre,
		STAT_LinkAltText,
		STAT_LinkText,
		STAT_LinkTextPost,
		STAT_LinkRefId,
		STAT_LinkURLPre,
		STAT_LinkURL,
		STAT_LinkURLAngle,
		STAT_LinkURLAnglePost,
		STAT_LinkTitleDoubleQuote,
		STAT_LinkTitleSingleQuote,
		STAT_LinkTitlePost,
		STAT_RefereeRefId,
		STAT_RefereeRefIdPost,
		STAT_RefereeURLPreWhite,
		STAT_RefereeURLPre,
		STAT_RefereeURL,
		STAT_RefereeURLAngle,
		STAT_RefereeURLAnglePost,
		STAT_RefereeTitleDoubleQuote,
		STAT_RefereeTitleSingleQuote,
		STAT_RefereeTitleParenthesis,
		STAT_RefereeTitlePost,
		STAT_Escape,
		STAT_EscapeInLink,
	};
	class StatStack : public std::vector<Stat> {
	public:
		inline void Push(Stat stat) { push_back(stat); }
		inline Stat Pop() {
			Stat stat = back();
			pop_back();
			return stat;
		}
	};
private:
	int _cntRef;
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
	AutoPtr<ItemOwner> _pItemOwner;
	AutoPtr<ItemOwner> _pItemRefereeOwner;
	AutoPtr<Item> _pItemRoot;
	AutoPtr<Item> _pItemLink;
	ItemList _itemsLinkReferrer;
	ItemStack _itemStack;
	ItemStack _itemStackTag;
	ItemOwnerStack _itemOwnerStack;
	AlignList _alignList;
public:
	Gura_DeclareReferenceAccessor(Document);
public:
	Document();
private:
	inline ~Document() {}
public:
	bool ParseStream(Signal &sig, SimpleStream &stream);
	bool ParseString(Signal &sig, const char *text);
	void AddItemReferee(Item *pItem);
	void ResolveReference();
	inline const Item *GetItemRoot() { return _pItemRoot.get(); }
	inline const ItemOwner *GetItemRefereeOwner() const {
		return _pItemRefereeOwner.get();
	}
private:
	bool _ParseString(Signal &sig, String text);
	bool ParseChar(Signal &sig, char ch);
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
	void BeginCodeBlock(const char *textInit);
	void EndCodeBlock();
	void BeginFencedCodeBlock();
	void EndFencedCodeBlock();
	//void BeginCodeBlockInList(const char *textInit);
	//void EndCodeBlockInList();
	void BeginListItem(Item::Type type);
	void EndListItem();
	void BeginDecoration(Item::Type type);
	void EndDecoration();
	void CancelDecoration(const char *textAhead);
	void ReplaceDecoration(Item::Type type, const char *textAhead);
	void BeginTag(const char *tagName, const char *attrs, bool closedFlag, bool markdownAcceptableFlag);
	bool EndTag(const char *tagName);
	int GetIndentLevel() const;
	int GetIndentLevelForCodeBlock() const;
	void UpdateIndentLevelItemBody(int indentLevelItemBody);
	bool IsWithin(Item::Type type) const;
	static Item::Type HeaderLevelToItemType(int headerLevel);
	static bool IsAtxHeader2(const char *text);
	static bool IsHorzRule(const char *text);
	static bool IsLink(const char *text);
	static bool IsBeginTag(const char *text, String &tagName,
						   String &attrs, bool &closedFlag, bool &markdownAcceptableFlag);
	static bool IsEndTag(const char *text, String &tagName);
	inline bool IsWordChar(char ch) {
		return (GetCType(ch) &
				(CTYPE_Alpha | CTYPE_Digit | CTYPE_UTF8First | CTYPE_UTF8Follower)) != 0;
	}
	inline static bool IsEOL(char ch) { return ch == '\n'; }
	inline static bool IsEOF(char ch) { return ch == '\0'; }
	inline static bool IsDigit(char ch) { return '0' <= ch && ch <= '9'; }
	inline void AdvanceTableRow() { if (_iTableRow >= 0) _iTableRow++; }
	inline bool IsTableMode() const { return _iTableRow >= 0; }
	inline bool IsTableFirstRow() const { return _iTableRow == 0; }
	inline bool IsTableGuideRow() const { return _iTableRow == 1; }
	inline bool IsTableTrailingRow() const { return _iTableRow >= 2; }
	inline bool IsWithinTag() const { return !_itemStackTag.empty(); }
	inline bool IsMarkdownAcceptable() const {
		return _itemStackTag.empty() || _itemStackTag.back()->GetMarkdownAcceptableFlag();
	}
};
#endif

Gurax_EndModuleScope(markdown)

#endif
