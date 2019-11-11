//==============================================================================
// Item.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_ITEM_H
#define GURAX_MODULE_MARKDOWN_ITEM_H
#include <gurax.h>
#include "Common.h"

Gurax_BeginModuleScope(markdown)

class Item;

//------------------------------------------------------------------------------
// ItemList
//------------------------------------------------------------------------------
class ItemList : public std::vector<Item*> {
public:
	Item* FindByRefId(const char* refId) const;
	//size_t CountByType(Item::Type type, bool recursiveFlag) const;
	void Print(Stream& stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// ItemOwner
//------------------------------------------------------------------------------
class ItemOwner : public ItemList, public Referable {
public:
	Gurax_DeclareReferable(ItemOwner);
public:
	ItemOwner() {}
private:
	~ItemOwner() { Clear(); }
public:
	void Clear();
	void Store(const ItemList& itemList);
	void StripTextAtFront(bool stripLeftFLag, bool stripRightFlag);
};

//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Item : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Item);
public:
	enum class Type {
		None,
		Root,			// container, can be a parent
		Header1,		// container
		Header2,		// container
		Header3,		// container
		Header4,		// container
		Header5,		// container
		Header6,		// container
		Paragraph,		// container
		BlockQuote,		// container, can be a parent
		Emphasis,		// container
		Strong,			// container
		Strike,			// container
		CodeBlock,		// container, can be a parent
		OList,			// container, can be a parent
		UList,			// container, can be a parent
		ListItem,		// container, can be a parent
		Line,			// container
		Link,			// container
		Image,			// text
		Text,			// text
		Comment,		// text
		Code,			// text
		Entity,			// text
		Tag,			// container and text (attributes), can be a parent
		HorzRule,		// no-content
		LineBreak,		// no-content
		Referee,		// no-content
	};
	struct TypeNamePair {
		Type type;
		const char* name;
	};
private:
	static const TypeNamePair _typeNamePairs[];
private:
	Type _type;
	RefPtr<ItemOwner> _pItemOwner;
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
	Item(Type type);
	Item(Type type, ItemOwner *pItemOwner);
	Item(Type type, const String &text);
private:
	~Item() {}
public:
	void SetType(Item::Type type) { _type = type; }
	const Type GetType() const { return _type; }
	bool IsRoot() const { return _type == TYPE_Root; }
	bool IsBlockQuote() const { return _type == TYPE_BlockQuote; }
	bool Is_list() const { return _type == TYPE_UList || _type == TYPE_OList; }
	bool IsListItem() const { return _type == TYPE_ListItem; }
	bool IsTag() const { return _type == TYPE_Tag; }
	bool IsInlineTag() const { return _type == TYPE_Tag && IsInlineTagName(GetText()); }
	bool IsText() const { return _type == TYPE_Text; }
	bool IsOwner() const { return !_pItemOwner.IsNull(); }
	void SetItemOwner(ItemOwner *pItemOwner) { _pItemOwner.reset(pItemOwner); }
	ItemOwner *GetItemOwner() { return _pItemOwner.get(); }
	const ItemOwner *GetItemOwner() const { return _pItemOwner.get(); }
	const char *GetText() const {
		return (_pText.get() == nullptr)? nullptr : _pText->c_str();
	}
	const char *GetURL() const {
		return (_pURL.get() == nullptr)? nullptr : _pURL->c_str();
	}
	const char *GetTitle() const {
		return (_pTitle.get() == nullptr)? nullptr : _pTitle->c_str();
	}
	const char *GetRefId() const {
		return (_pRefId.get() == nullptr)? nullptr : _pRefId->c_str();
	}
	const char *GetAttrs() const {
		return (_pAttrs.get() == nullptr)? nullptr : _pAttrs->c_str();
	}
	Align GetAlign() const { return _align; }
	void SetText(const String &text) { _pText.reset(new String(text)); }
	void AppendText(const String &text) {
		if (_pText.get() == nullptr) {
			_pText.reset(new String(text));
		} else {
			*_pText += text;
		}
	}
	void SetURL(const String &url) { _pURL.reset(new String(url)); }
	void SetTitle(const String &title) { _pTitle.reset(new String(title)); }
	void SetRefId(const String &refId) { _pRefId.reset(new String(refId)); }
	void SetAttrs(const String &attrs) { _pAttrs.reset(new String(attrs)); }
	void SetAlign(Align align) { _align = align; }
	void ClearURL() { _pURL.reset(nullptr); }
	void ClearTitle() { _pTitle.reset(nullptr); }
	void ClearRefId() { _pRefId.reset(nullptr); }
	void SetIndentLevel(int indentLevel) { _indentLevel = indentLevel; }
	void SetIndentLevelItemBody(int indentLevelItemBody) {
		_indentLevelItemBody = indentLevelItemBody;
	}
	void SetMarkdownAcceptableFlag(bool markdownAcceptableFlag) {
		_markdownAcceptableFlag = markdownAcceptableFlag;
	}
	int GetIndentLevel() const { return _indentLevel; }
	int GetIndentLevelItemBody() const { return _indentLevelItemBody; }
	bool GetMarkdownAcceptableFlag() const { return _markdownAcceptableFlag; }
	bool StripText(bool stripLeftFlag, bool stripRightFlag);
	const char *GetTypeName() const;
	void Print(Signal &sig, Stream &stream, int indentLevel) const;
	static const char *TypeToName(Type type);
	static Type NameToType(const char *name);
};
#endif

//------------------------------------------------------------------------------
// ItemOwnerStack
//------------------------------------------------------------------------------
class ItemOwnerStack : public std::vector<ItemOwner*> {
public:
	~ItemOwnerStack() { Clear(); }
	void Clear();
	void Push(ItemOwner* pItemOwner) { push_back(pItemOwner); }
	ItemOwner* Pop() {
		ItemOwner* pItemOwner = back();
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

Gurax_EndModuleScope(markdown)

#endif
