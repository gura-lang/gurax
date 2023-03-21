//==============================================================================
// TrainNode.h
//==============================================================================
#ifndef GURAX_TRAINNODE_H
#define GURAX_TRAINNODE_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainNode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainNode : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(TrainNode);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("TrainNode");
public:
	// Constructor
	TrainNode() {}
	// Copy constructor/operator
	TrainNode(const TrainNode& src) = delete;
	TrainNode& operator=(const TrainNode& src) = delete;
	// Move constructor/operator
	TrainNode(TrainNode&& src) noexcept = delete;
	TrainNode& operator=(TrainNode&& src) noexcept = delete;
protected:
	~TrainNode() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const TrainNode& other) const { return this == &other; }
	bool IsEqualTo(const TrainNode& other) const { return IsIdentical(other); }
	bool IsLessThan(const TrainNode& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// TrainNodeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainNodeList : public ListBase<TrainNode*> {
};

//------------------------------------------------------------------------------
// TrainNodeOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainNodeOwner : public TrainNodeList {
public:
	~TrainNodeOwner() { Clear(); }
	void Clear();
};

}

#endif
