//==============================================================================
// Node.h
//==============================================================================
#ifndef GURAX_MODULE_XML_NODE_H
#define GURAX_MODULE_XML_NODE_H
#include <gurax.h>
#include "Attr.h"

Gurax_BeginModuleScope(xml)

class NodeOwner;

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Node : public Referable {
public:
	enum class Type { None, CData, Comment, Element, Text };
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

Gurax_EndModuleScope(xml)

#endif
