//==============================================================================
// Item.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_ITEM_H
#define GURAX_MODULE_MARKDOWN_ITEM_H
#include <gurax.h>
#include "Util.h"

Gurax_BeginModuleScope(markdown)

class Item;

//------------------------------------------------------------------------------
// ItemList
//------------------------------------------------------------------------------
class ItemList : public ListBase<Item*> {
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
	class SymbolAssoc_Type : public SymbolAssoc<Type, Type::None> {
	public:
		SymbolAssoc_Type() {
			Assoc(Symbol::Add("root"),			Type::Root);		// container, can be a parent
			Assoc(Symbol::Add("h1"),			Type::Header1);		// container
			Assoc(Symbol::Add("h2"),			Type::Header2);		// container
			Assoc(Symbol::Add("h3"),			Type::Header3);		// container
			Assoc(Symbol::Add("h4"),			Type::Header4);		// container
			Assoc(Symbol::Add("h5"),			Type::Header5);		// container
			Assoc(Symbol::Add("h6"),			Type::Header6);		// container
			Assoc(Symbol::Add("p"),				Type::Paragraph);	// container
			Assoc(Symbol::Add("blockquote"),	Type::BlockQuote);	// container, can be a parent
			Assoc(Symbol::Add("em"),			Type::Emphasis);	// container
			Assoc(Symbol::Add("strong"),		Type::Strong);		// container
			Assoc(Symbol::Add("strike"),		Type::Strike);		// container
			Assoc(Symbol::Add("codeblock"),		Type::CodeBlock);	// container, can be a parent
			Assoc(Symbol::Add("ol"),			Type::OList);		// container, can be a parent
			Assoc(Symbol::Add("ul"),			Type::UList);		// container, can be a parent
			Assoc(Symbol::Add("li"),			Type::ListItem);	// container, can be a parent
			Assoc(Symbol::Add("line"),			Type::Line);		// container
			Assoc(Symbol::Add("a"),				Type::Link);		// container
			Assoc(Symbol::Add("img"),			Type::Image);		// text
			Assoc(Symbol::Add("text"),			Type::Text);		// text
			Assoc(Symbol::Add("comment"),		Type::Comment);		// text
			Assoc(Symbol::Add("code"),			Type::Code);		// text
			Assoc(Symbol::Add("entity"),		Type::Entity);		// text
			Assoc(Symbol::Add("tag"),			Type::Tag);			// container and text (attributes), can be a parent
			Assoc(Symbol::Add("hr"),			Type::HorzRule);	// no-content
			Assoc(Symbol::Add("br"),			Type::LineBreak);	// no-content
			Assoc(Symbol::Add("referee"),		Type::Referee);		// no-content
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Type());
		}
	};
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
	Item(Type type);
	Item(Type type, ItemOwner* pItemOwner);
	Item(Type type, const String& text);
	// Copy constructor/operator
	Item(const Item& src) = delete;
	Item& operator=(const Item& src) = delete;
	// Move constructor/operator
	Item(Item&& src) = delete;
	Item& operator=(Item&& src) noexcept = delete;
protected:
	~Item() = default;
public:
	void SetType(Item::Type type) { _type = type; }
	const Type GetType() const { return _type; }
	bool IsRoot() const { return _type == Type::Root; }
	bool IsBlockQuote() const { return _type == Type::BlockQuote; }
	bool Is_list() const { return _type == Type::UList || _type == Type::OList; }
	bool IsListItem() const { return _type == Type::ListItem; }
	bool IsTag() const { return _type == Type::Tag; }
	bool IsInlineTag() const { return _type == Type::Tag && IsInlineTagName(GetText()); }
	bool IsText() const { return _type == Type::Text; }
	bool IsOwner() const { return _pItemOwner.get() != nullptr; }
	void SetItemOwner(ItemOwner* pItemOwner) { _pItemOwner.reset(pItemOwner); }
	ItemOwner* GetItemOwner() { return _pItemOwner.get(); }
	const ItemOwner* GetItemOwner() const { return _pItemOwner.get(); }
	const char* GetText() const { return _pText? _pText->c_str() : nullptr; }
	const char* GetURL() const { return _pURL? _pURL->c_str() : nullptr; }
	const char* GetTitle() const { return _pTitle? _pTitle->c_str() : nullptr; }
	const char* GetRefId() const { return _pRefId? _pRefId->c_str() : nullptr; }
	const char* GetAttrs() const { return _pAttrs? _pAttrs->c_str() : nullptr; }
	Align GetAlign() const { return _align; }
	void SetText(const String& text) { _pText.reset(new String(text)); }
	void AppendText(const String& text);
	void SetURL(const String& url) { _pURL.reset(new String(url)); }
	void SetTitle(const String& title) { _pTitle.reset(new String(title)); }
	void SetRefId(const String& refId) { _pRefId.reset(new String(refId)); }
	void SetAttrs(const String& attrs) { _pAttrs.reset(new String(attrs)); }
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
	void Print(Stream& stream, int indentLevel) const;
	static size_t CountByType(const ItemList& itemList, Type type, bool recursiveFlag);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Item& other) const { return this == &other; }
	bool IsEqualTo(const Item& other) const { return IsIdentical(other); }
	bool IsLessThan(const Item& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ItemOwnerStack
//------------------------------------------------------------------------------
class ItemOwnerStack : public ListBase<ItemOwner*> {
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
// Iterator_Item
//------------------------------------------------------------------------------
class Iterator_Item : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("markdown.Iterator_Item");
private:
	RefPtr<ItemOwner> _pItemOwner;
	size_t _idx;
public:
	Iterator_Item(ItemOwner* pItemOwner) : _pItemOwner(pItemOwner), _idx(0) {}
public:
	ItemOwner& GetItemOwner() { return *_pItemOwner; }
	const ItemOwner& GetItemOwner() const { return *_pItemOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetItemOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(markdown)

#endif
