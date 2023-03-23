//==============================================================================
// TrainNode.h
//==============================================================================
#ifndef GURAX_TRAINNODE_H
#define GURAX_TRAINNODE_H
#include "Array.h"

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
	enum class Trait { Variable, Constant, Input, };
	class Connector {
	private:
		TrainNode* _pNodeSrc;
		TrainNode* _pNodeDst;
		RefPtr<Array> _pArrayGrad;
	public:
		Connector(TrainNode* pNodeDst) : _pNodeSrc(nullptr), _pNodeDst(pNodeDst) {}
		TrainNode* GetNodeSrc() { return _pNodeSrc; }
		TrainNode* GetNodeDst() { return _pNodeDst; }
		const TrainNode* GetNodeSrc() const { return _pNodeSrc; }
		const TrainNode* GetNodeDst() const { return _pNodeDst; }
		void SetNodeSrc(TrainNode* pNodeSrc) { _pNodeSrc = pNodeSrc; }
		void SetArrayGrad(Array* pArrayGrad) { _pArrayGrad.reset(pArrayGrad); }
		//Array* GetArrayFwd() { return _pNodeSrc->GetArrayFwd(); }
		Array* GetArrayGrad() { return _pArrayGrad.get(); }
		const Array* GetArrayGrad() const { return _pArrayGrad.get(); }
		RefPtr<Array>& GetArrayGradRef() { return _pArrayGrad; }
		//const Array* GetArrayFwd() const { return _pNodeSrc->GetArrayFwd(); }
	};
	class ConnectorList : public ListBase<Connector*> {
	public:
		ConnectorList() {}
	};

private:
	const char* _nodeTypeName;
	ConnectorList _connectorsDst;
	RefPtr<Array> _pArrayFwd;
public:
	// Constructor
	explicit TrainNode(const char* nodeTypeName) : _nodeTypeName(nodeTypeName) {}
	explicit TrainNode(const char* nodeTypeName, Connector* pConnectorDst);
	// Copy constructor/operator
	TrainNode(const TrainNode& src) = delete;
	TrainNode& operator=(const TrainNode& src) = delete;
	// Move constructor/operator
	TrainNode(TrainNode&& src) noexcept = delete;
	TrainNode& operator=(TrainNode&& src) noexcept = delete;
protected:
	~TrainNode() = default;
public:
	const char* GetNodeTypeName() const { return _nodeTypeName; }
	void AddConnectorDst(Connector* pConnectorDst) { _connectorsDst.push_back(pConnectorDst); }
	Array* GetArrayFwd() { return _pArrayFwd.get(); }
	RefPtr<Array>& GetArrayFwdRef() { return _pArrayFwd; }
	virtual bool IsHead() { return false; }
	virtual bool IsBottom() { return false; }
	virtual bool IsUnary() { return false; }
	virtual bool IsBinary() { return false; }
	virtual bool IsGear() { return false; }
	virtual bool IsVulnerable() const = 0;
	virtual void Reset() {}
	virtual bool EvalForward() = 0;
	virtual bool EvalBackward() = 0;
	//virtual bool GatherMemberSymbol(SymbolList& symbols);
	//virtual Value DoGetProp(const Symbol* pSymbol, const SymbolSet& attrs, bool& evaluatedFlag);
	virtual String ToString() const = 0;
	virtual void Print(int indentLevel) const;
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
