//==============================================================================
// VType_TrainNode.h
//==============================================================================
#ifndef GURAX_VTYPE_TRAINNODE_H
#define GURAX_VTYPE_TRAINNODE_H
#include "VType_Object.h"
#include "TrainNode.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_TrainNode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_TrainNode : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_TrainNode VTYPE_TrainNode;

//------------------------------------------------------------------------------
// Value_TrainNode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_TrainNode : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_TrainNode);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_TrainNode");
protected:
	RefPtr<TrainNode> _pTrainNode;
public:
	static VType& vtype;
public:
	// Constructor
	Value_TrainNode() = delete;
	explicit Value_TrainNode(TrainNode* pTrainNode, VType& vtype = VTYPE_TrainNode) :
		Value_Object(vtype), _pTrainNode(pTrainNode) {}
	// Copy constructor/operator
	Value_TrainNode(const Value_TrainNode& src) :
		Value_Object(src), _pTrainNode(src._pTrainNode->Reference()) {}
	Value_TrainNode& operator=(const Value_TrainNode& src) = delete;
	// Move constructor/operator
	Value_TrainNode(Value_TrainNode&& src) noexcept = delete;
	Value_TrainNode& operator=(Value_TrainNode&& src) noexcept = delete;
protected:
	// Destructor
	~Value_TrainNode() = default;
public:
	TrainNode& GetTrainNode() { return *_pTrainNode; }
	const TrainNode& GetTrainNode() const { return *_pTrainNode; }
public:
	static TrainNode& GetTrainNode(Value& value) {
		return dynamic_cast<Value_TrainNode&>(value).GetTrainNode();
	}
	static const TrainNode& GetTrainNode(const Value& value) {
		return dynamic_cast<const Value_TrainNode&>(value).GetTrainNode();
	}
	static TrainNode* GetEntityPtr(Value& value) { return &GetTrainNode(value); }
	static const TrainNode* GetEntityPtr(const Value& value) { return &GetTrainNode(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTrainNode().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTrainNode().IsEqualTo(Value_TrainNode::GetTrainNode(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTrainNode().IsLessThan(Value_TrainNode::GetTrainNode(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual void GatherMemberSymbol(SymbolList& symbolList) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag);
};

}

#endif
