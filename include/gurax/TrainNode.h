//==============================================================================
// TrainNode.h
//==============================================================================
#ifndef GURAX_TRAINNODE_H
#define GURAX_TRAINNODE_H
#include "Array.h"
#include "Gear.h"
#include "TrainOptimizer.h"

namespace Gurax {

class Trainer; 
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
		TrainNode& GetNodeSrc() { return *_pNodeSrc; }
		TrainNode& GetNodeDst() { return *_pNodeDst; }
		const TrainNode& GetNodeSrc() const { return *_pNodeSrc; }
		const TrainNode& GetNodeDst() const { return *_pNodeDst; }
		void SetNodeSrc(TrainNode* pNodeSrc) { _pNodeSrc = pNodeSrc; }
		void SetArrayGrad(Array* pArrayGrad) { _pArrayGrad.reset(pArrayGrad); }
		Array& GetArrayFwd() { return _pNodeSrc->GetArrayFwd(); }
		Array& GetArrayGrad() { return *_pArrayGrad; }
		RefPtr<Array>& GetArrayGradRefPtr() { return _pArrayGrad; }
		const Array& GetArrayFwd() const { return _pNodeSrc->GetArrayFwd(); }
		const Array& GetArrayGrad() const { return *_pArrayGrad; }
	};
	class ConnectorList : public ListBase<Connector*> {
	public:
		ConnectorList() {}
	};
protected:
	const char* _nodeTypeName;
	ConnectorList _connectorsDst;
	RefPtr<Array> _pArrayFwd;
public:
	// Constructor
	explicit TrainNode(const char* nodeTypeName) : _nodeTypeName(nodeTypeName) {}
	TrainNode(const char* nodeTypeName, Connector* pConnectorDst);
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
	Array& GetArrayFwd() { return *_pArrayFwd; }
	const Array& GetArrayFwd() const { return *_pArrayFwd; }
	RefPtr<Array>& GetArrayFwdRefPtr() { return _pArrayFwd; }
	virtual bool IsHead() const { return false; }
	virtual bool IsBottom() const { return false; }
	virtual bool IsUnary() const { return false; }
	virtual bool IsBinary() const { return false; }
	virtual bool IsGear() const { return false; }
	virtual bool IsVulnerable() const = 0;
	virtual void Reset() {}
	virtual bool EvalForward(Processor& processor) = 0;
	virtual bool EvalBackward(Processor& processor) = 0;
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
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

//------------------------------------------------------------------------------
// TrainNode_Head
//------------------------------------------------------------------------------
class TrainNode_Head : public TrainNode {
protected:
	RefPtr<Expr> _pExpr;
	RefPtr<Array> _pArrayGradAdj;
	Trait _trait;
	RefPtr<TrainOptimizer::Instance> _pTrainOptimizer;
public:
	TrainNode_Head(Connector* pConnectorDst, Expr* pExpr, Trait trait, TrainOptimizer::Instance* pTrainOptimizer) :
		TrainNode("Head", pConnectorDst), _pExpr(pExpr), _trait(trait), _pTrainOptimizer(pTrainOptimizer) {}
	bool IsVariable() const { return _trait == Trait::Variable; }
	bool IsConstant() const { return _trait == Trait::Constant; }
	bool IsInput() const { return _trait == Trait::Input; }
	virtual bool IsHead() const { return true; }
	virtual void Reset();
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Bottom
//------------------------------------------------------------------------------
class TrainNode_Bottom : public TrainNode {
private:
	Connector _connectorSrc;
	RefPtr<Array> _pArrayCorrect;
public:
	TrainNode_Bottom() : TrainNode("Bottom"), _connectorSrc(this) {}
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	Array& GetArrayCorrect() { return *_pArrayCorrect; }
	const Array& GetArrayCorrect() const { return *_pArrayCorrect; }
	virtual bool IsBottom() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	bool EvalBackwardTop(const Array& arrayCorrect);
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Unary
//------------------------------------------------------------------------------
class TrainNode_Unary : public TrainNode {
protected:
	Connector _connectorSrc;
public:
	TrainNode_Unary(const char* nodeTypeName, Connector* pConnectorDst) : TrainNode(nodeTypeName, pConnectorDst), _connectorSrc(this) {}
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	virtual bool IsUnary() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Neg
//------------------------------------------------------------------------------
class TrainNode_Neg : public TrainNode_Unary {
public:
	TrainNode_Neg(Connector* pConnectorDst) : TrainNode_Unary("Neg", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Binary
//------------------------------------------------------------------------------
class TrainNode_Binary : public TrainNode {
protected:
	Connector _connectorSrcLeft;
	Connector _connectorSrcRight;
public:
	TrainNode_Binary(const char* nodeTypeName, Connector* pConnectorDst) :
			TrainNode(nodeTypeName, pConnectorDst), _connectorSrcLeft(this), _connectorSrcRight(this) {}
	Connector& GetConnectorSrcLeft() { return _connectorSrcLeft; }
	Connector& GetConnectorSrcRight() { return _connectorSrcRight; }
	const Connector& GetConnectorSrcLeft() const { return _connectorSrcLeft; }
	const Connector& GetConnectorSrcRight() const { return _connectorSrcRight; }
	virtual bool IsBinary() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Add
//------------------------------------------------------------------------------
class TrainNode_Add : public TrainNode_Binary {
public:
	TrainNode_Add(Connector* pConnectorDst) : TrainNode_Binary("Add", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Sub
//------------------------------------------------------------------------------
class TrainNode_Sub : public TrainNode_Binary {
public:
	TrainNode_Sub(Connector* pConnectorDst) : TrainNode_Binary("Sub", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Mul
//------------------------------------------------------------------------------
class TrainNode_Mul : public TrainNode_Binary {
public:
	TrainNode_Mul(Connector* pConnectorDst) : TrainNode_Binary("Mul", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Div
//------------------------------------------------------------------------------
class TrainNode_Div : public TrainNode_Binary {
public:
	TrainNode_Div(Connector* pConnectorDst) : TrainNode_Binary("Div", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Pow
//------------------------------------------------------------------------------
class TrainNode_Pow : public TrainNode_Binary {
private:
	RefPtr<Array> _pArrayWork;
public:
	TrainNode_Pow(Connector* pConnectorDst) : TrainNode_Binary("Pow", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Dot
//------------------------------------------------------------------------------
class TrainNode_Dot : public TrainNode_Binary {
private:
	RefPtr<Array> _pArrayFwdLeftTrans;
	RefPtr<Array> _pArrayFwdRightTrans;
public:
	TrainNode_Dot(Connector* pConnectorDst) : TrainNode_Binary("Dot", pConnectorDst) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Gear
//------------------------------------------------------------------------------
class TrainNode_Gear : public TrainNode {
public:
	class Creator {
	public:
		virtual TrainNode_Gear* Create(const Value &value, Connector* pConnectorDst, const Trainer& trainer) const = 0;
	};
protected:
	RefPtr<Gear> _pGear;
	Connector _connectorSrc;
public:
	TrainNode_Gear(Gear* pGear, Connector* pConnectorDst) : TrainNode(pGear->GetName(), pConnectorDst), _pGear(pGear), _connectorSrc(this) {}
	Gear& GetGear() { return *_pGear; }
	const Gear& GetGear() const { return *_pGear; }
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	virtual bool IsGear() const { return true; }
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

}

#endif
