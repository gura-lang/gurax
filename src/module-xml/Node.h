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

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Node : public Referable {
public:
	enum class Type { None, CData, Comment, Element, Text, XmlDecl };
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
	virtual Value* CreateValue() const = 0;
	virtual bool Compose(Stream& stream) const = 0;
public:
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
// IteratorFactory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IteratorFactory {
public:
	virtual Iterator* CreateIterator(NodeOwner* pNodeOwner) const = 0;
};

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Each : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Each");
public:
	class GURAX_DLLDECLARE IteratorFactoryEx : public IteratorFactory {
	public:
		virtual Iterator* CreateIterator(NodeOwner* pNodeOwner) const {
			return new Iterator_Each(pNodeOwner);
		}
	};
private:
	RefPtr<NodeOwner> _pNodeOwner;
	size_t _idx;
public:
	Iterator_Each(NodeOwner* pNodeOwner) : _pNodeOwner(pNodeOwner), _idx(0) {}
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
// Iterator_EachElement
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachElement : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_EachElement");
private:
	RefPtr<NodeOwner> _pNodeOwner;
	String _tagName;
	size_t _idx;
public:
	Iterator_EachElement(NodeOwner* pNodeOwner, String tagName) :
					_pNodeOwner(pNodeOwner), _tagName(tagName), _idx(0) {}
public:
	NodeOwner& GetNodeOwner() { return *_pNodeOwner; }
	const NodeOwner& GetNodeOwner() const { return *_pNodeOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_EachText
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachText : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_EachText");
private:
	RefPtr<NodeOwner> _pNodeOwner;
	size_t _idx;
public:
	Iterator_EachText(NodeOwner* pNodeOwner) : _pNodeOwner(pNodeOwner), _idx(0) {}
public:
	NodeOwner& GetNodeOwner() { return *_pNodeOwner; }
	const NodeOwner& GetNodeOwner() const { return *_pNodeOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

#if 0
//------------------------------------------------------------------------------
// Iterator_Walk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Walk : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Walk");
private:
	std::unique_ptr<IteratorFactory> _pIteratorFactory;
	IteratorList _iteratorStack;
public:
	Iterator_Walk(IteratorFactory* pIteratorFactory, NodeOwner* pNodeOwner) {
		_pIteratorFactory.reset(pIteratorFactory);
		_iteratorStack.push_back(pIteratorFactory->CreateIterator(pNodeOwner));
	}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};
#endif

Gurax_EndModuleScope(xml)

#endif
