//==============================================================================
// Item.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_ITEM_H
#define GURAX_MODULE_MARKDOWN_ITEM_H
#include <gurax.h>

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Item : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Item);
public:
	// Constructor
	Item() {}
	// Copy constructor/operator
	Item(const Item& src) = delete;
	Item& operator=(const Item& src) = delete;
	// Move constructor/operator
	Item(Item&& src) = delete;
	Item& operator=(Item&& src) noexcept = delete;
protected:
	~Item() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Item& other) const { return this == &other; }
	bool IsEqualTo(const Item& other) const { return IsIdentical(other); }
	bool IsLessThan(const Item& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

#if 0
class Item {
public:
	enum Type {
		TYPE_None,
		TYPE_Root,			// container, can be a parent
		TYPE_Header1,		// container
		TYPE_Header2,		// container
		TYPE_Header3,		// container
		TYPE_Header4,		// container
		TYPE_Header5,		// container
		TYPE_Header6,		// container
		TYPE_Paragraph,		// container
		TYPE_BlockQuote,	// container, can be a parent
		TYPE_Emphasis,		// container
		TYPE_Strong,		// container
		TYPE_Strike,		// container
		TYPE_CodeBlock,		// container, can be a parent
		TYPE_OList,			// container, can be a parent
		TYPE_UList,			// container, can be a parent
		TYPE_ListItem,		// container, can be a parent
		TYPE_Line,			// container
		TYPE_Link,			// container
		TYPE_Image,			// text
		TYPE_Text,			// text
		TYPE_Comment,		// text
		TYPE_Code,			// text
		TYPE_Entity,		// text
		TYPE_Tag,			// container and text (attributes), can be a parent
		TYPE_HorzRule,		// no-content
		TYPE_LineBreak,		// no-content
		TYPE_Referee,		// no-content
	};
	struct TypeNamePair {
		Type type;
		const char *name;
	};
private:
	static const TypeNamePair _typeNamePairs[];
private:
	int _cntRef;
	Type _type;
	AutoPtr<ItemOwner> _pItemOwner;
	std::unique_ptr<String> _pText;
	std::unique_ptr<String> _pURL;		// valid when type is Link or Image
	std::unique_ptr<String> _pTitle;	// valid when type is Link or Image
	std::unique_ptr<String> _pRefId;	// valid when type is Link or Image
	std::unique_ptr<String> _pAttrs;	// valid when type is Tag
	Align _align;						// valid when type is Tag
	int _indentLevel;
	int _indentLevelItemBody;			// valid when type is ListItem
	bool _markdownAcceptableFlag;
public:
	Gura_DeclareReferenceAccessor(Item);
public:
	Item(Type type);
	Item(Type type, ItemOwner *pItemOwner);
	Item(Type type, const String &text);
private:
	inline ~Item() {}
public:
	inline void SetType(Item::Type type) { _type = type; }
	inline const Type GetType() const { return _type; }
	inline bool IsRoot() const { return _type == TYPE_Root; }
	inline bool IsBlockQuote() const { return _type == TYPE_BlockQuote; }
	inline bool Is_list() const { return _type == TYPE_UList || _type == TYPE_OList; }
	inline bool IsListItem() const { return _type == TYPE_ListItem; }
	inline bool IsTag() const { return _type == TYPE_Tag; }
	inline bool IsInlineTag() const { return _type == TYPE_Tag && IsInlineTagName(GetText()); }
	inline bool IsText() const { return _type == TYPE_Text; }
	inline bool IsOwner() const { return !_pItemOwner.IsNull(); }
	inline void SetItemOwner(ItemOwner *pItemOwner) { _pItemOwner.reset(pItemOwner); }
	inline ItemOwner *GetItemOwner() { return _pItemOwner.get(); }
	inline const ItemOwner *GetItemOwner() const { return _pItemOwner.get(); }
	inline const char *GetText() const {
		return (_pText.get() == nullptr)? nullptr : _pText->c_str();
	}
	inline const char *GetURL() const {
		return (_pURL.get() == nullptr)? nullptr : _pURL->c_str();
	}
	inline const char *GetTitle() const {
		return (_pTitle.get() == nullptr)? nullptr : _pTitle->c_str();
	}
	inline const char *GetRefId() const {
		return (_pRefId.get() == nullptr)? nullptr : _pRefId->c_str();
	}
	inline const char *GetAttrs() const {
		return (_pAttrs.get() == nullptr)? nullptr : _pAttrs->c_str();
	}
	inline Align GetAlign() const { return _align; }
	inline void SetText(const String &text) { _pText.reset(new String(text)); }
	inline void AppendText(const String &text) {
		if (_pText.get() == nullptr) {
			_pText.reset(new String(text));
		} else {
			*_pText += text;
		}
	}
	inline void SetURL(const String &url) { _pURL.reset(new String(url)); }
	inline void SetTitle(const String &title) { _pTitle.reset(new String(title)); }
	inline void SetRefId(const String &refId) { _pRefId.reset(new String(refId)); }
	inline void SetAttrs(const String &attrs) { _pAttrs.reset(new String(attrs)); }
	inline void SetAlign(Align align) { _align = align; }
	inline void ClearURL() { _pURL.reset(nullptr); }
	inline void ClearTitle() { _pTitle.reset(nullptr); }
	inline void ClearRefId() { _pRefId.reset(nullptr); }
	inline void SetIndentLevel(int indentLevel) { _indentLevel = indentLevel; }
	inline void SetIndentLevelItemBody(int indentLevelItemBody) {
		_indentLevelItemBody = indentLevelItemBody;
	}
	inline void SetMarkdownAcceptableFlag(bool markdownAcceptableFlag) {
		_markdownAcceptableFlag = markdownAcceptableFlag;
	}
	inline int GetIndentLevel() const { return _indentLevel; }
	inline int GetIndentLevelItemBody() const { return _indentLevelItemBody; }
	inline bool GetMarkdownAcceptableFlag() const { return _markdownAcceptableFlag; }
	bool StripText(bool stripLeftFlag, bool stripRightFlag);
	const char *GetTypeName() const;
	void Print(Signal &sig, Stream &stream, int indentLevel) const;
	static const char *TypeToName(Type type);
	static Type NameToType(const char *name);
};

//------------------------------------------------------------------------------
// ItemList
//------------------------------------------------------------------------------
class ItemList : public std::vector<Item *> {
public:
	Item *FindByRefId(const char *refId) const;
	size_t CountByType(Item::Type type, bool recursiveFlag) const;
	void Print(Signal &sig, Stream &stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// ItemOwner
//------------------------------------------------------------------------------
class ItemOwner : public ItemList {
public:
	int _cntRef;
public:
	Gura_DeclareReferenceAccessor(ItemOwner);
public:
	inline ItemOwner() : _cntRef(1) {}
private:
	~ItemOwner();
public:
	void Clear();
	void Store(const ItemList &itemList);
	void StripTextAtFront(bool stripLeftFLag, bool stripRightFlag);
};

//------------------------------------------------------------------------------
// ItemOwnerStack
//------------------------------------------------------------------------------
class ItemOwnerStack : public std::vector<ItemOwner *> {
public:
	~ItemOwnerStack();
	void Clear();
	inline void Push(ItemOwner *pItemOwner) { push_back(pItemOwner); }
	inline ItemOwner *Pop() {
		ItemOwner *pItemOwner = back();
		pop_back();
		return pItemOwner;
	}
};

//------------------------------------------------------------------------------
// ItemStack
//------------------------------------------------------------------------------
class ItemStack : public ItemList {
public:
	void ClearListItem();
	int CountQuoteLevel() const;
};

//------------------------------------------------------------------------------
// Iterator_item
//------------------------------------------------------------------------------

#endif

Gurax_EndModuleScope(markdown)

#endif
