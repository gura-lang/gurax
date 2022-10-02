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
	enum class Type { None, CData, Comment, Element, Text };
	class SymbolAssoc_Type : public SymbolAssoc<Type, Type::None> {
	public:
		SymbolAssoc_Type() {
			Assoc(Gurax_Symbol(cdata),		Type::CData);
			Assoc(Gurax_Symbol(comment),	Type::Comment);
			Assoc(Gurax_Symbol(element),	Type::Element);
			Assoc(Gurax_Symbol(text),		Type::Text);
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
	Type GetType() const { return _type; }
	virtual Value* CreateValue() const = 0;
	virtual void Compose(Stream& stream) const = 0;
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
// Iterator_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Node : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Node");
private:
	RefPtr<NodeOwner> _pNodeOwner;
	size_t _idx;
public:
	Iterator_Node(NodeOwner* pNodeOwner) : _pNodeOwner(pNodeOwner), _idx(0) {}
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

Gurax_EndModuleScope(xml)

#endif
