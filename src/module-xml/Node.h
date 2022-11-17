//==============================================================================
// Node.h
//==============================================================================
#ifndef GURAX_MODULE_XML_NODE_H
#define GURAX_MODULE_XML_NODE_H
#include <gurax.h>
#include "Attr.h"
#include "Symbols.h"

Gurax_BeginModuleScope(xml)

class NodeOwner;
class Element;

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
class Node : public Referable {
public:
	enum class Type { None, CData, Comment, Element, Text, XmlDecl };
	struct TypeMask {
		static const UInt32 None	= 0;
		static const UInt32 CData	= (1 << 0);
		static const UInt32 Comment	= (1 << 1);
		static const UInt32 Element	= (1 << 2);
		static const UInt32 Text	= (1 << 3);
		static const UInt32 XmlDecl	= (1 << 4);
		static const UInt32 Any		= CData | Comment | Element | Text | XmlDecl;
	};
	class SymbolAssoc_Type : public SymbolAssoc<Type, Type::None> {
	public:
		SymbolAssoc_Type() {
			Assoc(Gurax_Symbol(cdata),		Type::CData);
			Assoc(Gurax_Symbol(comment),	Type::Comment);
			Assoc(Gurax_Symbol(element),	Type::Element);
			Assoc(Gurax_Symbol(text),		Type::Text);
			Assoc(Gurax_Symbol(xmldecl),	Type::XmlDecl);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Type());
		}
	};
public:
	// Referable declaration
	Gurax_DeclareReferable(Node);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Node");
private:
	Type _type;
	RefPtr<WeakPtr> _pwNodeParent;
public:
	// Constructor
	Node(Type type) : _type(type) {}
	// Copy constructor/operator
	Node(const Node& src) = delete;
	Node& operator=(const Node& src) = delete;
	// Move constructor/operator
	Node(Node&& src) noexcept = delete;
	Node& operator=(Node&& src) noexcept = delete;
protected:
	~Node() = default;
public:
	void SetNodeParent(const Node& nodeParent) { _pwNodeParent.reset(nodeParent.GetWeakPtr()); }
	Node* LockNodeParent() const { return _pwNodeParent? _pwNodeParent->Lock() : nullptr; }
	Type GetType() const { return _type; }
	size_t GetDepth() const;
	virtual bool IsElement(const char* tagName) const { return false; }
	virtual bool CheckTypeMask(UInt32 typeMask, const char* tagName) const = 0;
	virtual const char* GetText() const { return ""; }
	virtual Value* CreateValue() const = 0;
	virtual bool Compose(Stream& stream) const = 0;
public:
	static String ExtractField(const char** pPath);
	static UInt32 GetTypeMask(const Attribute& attr);
	static Type SymbolToType(const Symbol* pSymbol) {
		return SymbolAssoc_Type::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* TypeToSymbol(Type type) {
		return SymbolAssoc_Type::GetInstance().ToSymbol(type);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Node& other) const { return this == &other; }
	bool IsEqualTo(const Node& other) const { return IsIdentical(other); }
	bool IsLessThan(const Node& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// NodeList
//------------------------------------------------------------------------------
class NodeList : public ListBase<Node*> {
public:
	const Element* FindElement(const char* tagName) const;
};

//------------------------------------------------------------------------------
// NodeOwner
//------------------------------------------------------------------------------
class NodeOwner : public NodeList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(NodeOwner);
public:
	NodeOwner() {}
	~NodeOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// NodePicker
//------------------------------------------------------------------------------
class NodePicker {
private:
	RefPtr<NodeOwner> _pNodes;
	size_t _idx;
public:
	NodePicker(NodeOwner* pNodes) : _pNodes(pNodes), _idx(0) {}
	const Node* Next();
};

//------------------------------------------------------------------------------
// NodePickerStack
//------------------------------------------------------------------------------
class NodePickerStack : public ListBase<NodePicker*> {
public:
	~NodePickerStack();
};

//------------------------------------------------------------------------------
// NodeWalker
//------------------------------------------------------------------------------
class NodeWalker {
private:
	bool _firstFlag;
	RefPtr<Element> _pElement;
	NodePickerStack _nodePickerStack;
public:
	NodeWalker(Element* pElement);
	const Node* Next();
};

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
class Iterator_Each : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Each");
private:
	RefPtr<NodeOwner> _pNodeOwner;
	UInt32 _typeMask;
	String _tagName;
	size_t _idx;
public:
	Iterator_Each(NodeOwner* pNodeOwner, UInt32 typeMask, String tagName);
public:
	NodeOwner& GetNodeOwner() { return *_pNodeOwner; }
	const NodeOwner& GetNodeOwner() const { return *_pNodeOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetNodeOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Walk
//------------------------------------------------------------------------------
class Iterator_Walk : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Walk");
private:
	NodeWalker _nodeWalker;
	UInt32 _typeMask;
	String _tagName;
public:
	Iterator_Walk(Element* pElement, UInt32 typeMask, String tagName);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
