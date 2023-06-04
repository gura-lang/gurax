//==============================================================================
// NodeMap.h
//==============================================================================
#ifndef GURAX_MODULE_ML_NodeMap_H
#define GURAX_MODULE_ML_NodeMap_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// NodeMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeMap : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(NodeMap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.NodeMap");
private:
	using Map = std::unordered_map<const Symbol*, Node*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
	Map _map;
public:
	// Constructor
	NodeMap() {}
	// Copy constructor/operator
	NodeMap(const NodeMap& src) = delete;
	NodeMap& operator=(const NodeMap& src) = delete;
	// Move constructor/operator
	NodeMap(NodeMap&& src) noexcept = delete;
	NodeMap& operator=(NodeMap&& src) noexcept = delete;
protected:
	~NodeMap();
public:
	Node* FindNode(const Symbol* pSymbol) const {
		auto iter = _map.find(pSymbol);
		return (iter == _map.end())? nullptr : iter->second;
	}
	void AddNode(const Symbol* pSymbol, Node* pNode) { _map[pSymbol] = pNode; pNode->SetSymbol(pSymbol); }
	Map& GetMap() { return _map; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const NodeMap& other) const { return this == &other; }
	bool IsEqualTo(const NodeMap& other) const { return IsIdentical(other); }
	bool IsLessThan(const NodeMap& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// NodeMapList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeMapList : public ListBase<NodeMap*> {
};

//------------------------------------------------------------------------------
// NodeMapOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeMapOwner : public NodeMapList {
public:
	~NodeMapOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
