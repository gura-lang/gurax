//==============================================================================
// NodeStruct.h
//==============================================================================
#ifndef GURAX_MODULE_ML_NODESTRUCT_H
#define GURAX_MODULE_ML_NODESTRUCT_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// NodeStruct
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeStruct : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(NodeStruct);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.NodeStruct");
private:
	using Map = std::unordered_map<const Symbol*, Node*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
	Map _map;
public:
	// Constructor
	NodeStruct() {}
	// Copy constructor/operator
	NodeStruct(const NodeStruct& src) = delete;
	NodeStruct& operator=(const NodeStruct& src) = delete;
	// Move constructor/operator
	NodeStruct(NodeStruct&& src) noexcept = delete;
	NodeStruct& operator=(NodeStruct&& src) noexcept = delete;
protected:
	~NodeStruct();
public:
	Node* FindNode(const Symbol* pSymbol) const {
		auto iter = _map.find(pSymbol);
		return (iter == _map.end())? nullptr : iter->second;
	}
	void AddNode(const Symbol* pSymbol, Node* pNode) { _map[pSymbol] = pNode; }
	Map& GetMap() { return _map; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const NodeStruct& other) const { return this == &other; }
	bool IsEqualTo(const NodeStruct& other) const { return IsIdentical(other); }
	bool IsLessThan(const NodeStruct& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// NodeStructList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeStructList : public ListBase<NodeStruct*> {
};

//------------------------------------------------------------------------------
// NodeStructOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeStructOwner : public NodeStructList {
public:
	~NodeStructOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
