//==============================================================================
// TrainNode.h
//==============================================================================
#ifndef GURAX_TRAINNODE_H
#define GURAX_TRAINNODE_H
#include "Array.h"
#include "TrainOptimizer.h"

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
		TrainNode& GetNodeSrc() { return *_pNodeSrc; }
		TrainNode& GetNodeDst() { return *_pNodeDst; }
		const TrainNode& GetNodeSrc() const { return *_pNodeSrc; }
		const TrainNode& GetNodeDst() const { return *_pNodeDst; }
		void SetNodeSrc(TrainNode* pNodeSrc) { _pNodeSrc = pNodeSrc; }
		void SetArrayGrad(Array* pArrayGrad) { _pArrayGrad.reset(pArrayGrad); }
		Array& GetArrayFwd() { return _pNodeSrc->GetArrayFwd(); }
		Array& GetArrayGrad() { return *_pArrayGrad; }
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
	Array& GetArrayFwd() { return *_pArrayFwd; }
	const Array& GetArrayFwd() const { return *_pArrayFwd; }
	virtual bool IsHead() { return false; }
	virtual bool IsBottom() { return false; }
	virtual bool IsUnary() { return false; }
	virtual bool IsBinary() { return false; }
	virtual bool IsGear() { return false; }
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
	RefPtr<TrainOptimizer> _pTrainOptimizer;
public:
	TrainNode_Head(Connector* pConnectorDst, Expr* pExpr, Trait trait, TrainOptimizer* pTrainOptimizer) :
		TrainNode("head", pConnectorDst), _pExpr(pExpr), _trait(trait), _pTrainOptimizer(pTrainOptimizer) {}
	bool IsVariable() const { return _trait == Trait::Variable; }
	bool IsConstant() const { return _trait == Trait::Constant; }
	bool IsInput() const { return _trait == Trait::Input; }
	virtual bool IsHead();
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
	TrainNode_Bottom() : TrainNode("bottom"), _connectorSrc(this) {}
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	virtual bool IsBottom();
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	bool EvalBackwardTop(const Array* pArrayCorrect);
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

#if 0
//------------------------------------------------------------------------------
// TrainNode_Unary
//------------------------------------------------------------------------------
class TrainNode_Unary : public TrainNode {
protected:
	const Array::UnaryFuncPack &_unaryFuncPack;
	Connector _connectorSrc;
public:
	TrainNode_Unary(const char* nodeTypeName, const Array::UnaryFuncPack &unaryFuncPack, Connector* pConnectorDst) :
		TrainNode(nodeTypeName, pConnectorDst), _unaryFuncPack(unaryFuncPack), _connectorSrc(this) {}
	Connector* GetConnectorSrc() { return &_connectorSrc; }
	const Connector* GetConnectorSrc() const { return &_connectorSrc; }
	virtual bool IsUnary();
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Pos
//------------------------------------------------------------------------------
class TrainNode_Pos : public TrainNode_Unary {
public:
	TrainNode_Pos(Connector* pConnectorDst) :
			TrainNode_Unary("unary@pos", Array::unaryFuncPack_Pos, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Neg
//------------------------------------------------------------------------------
class TrainNode_Neg : public TrainNode_Unary {
public:
	TrainNode_Neg(Connector* pConnectorDst) :
			TrainNode_Unary("unary@neg", Array::unaryFuncPack_Neg, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Binary
//------------------------------------------------------------------------------
class TrainNode_Binary : public TrainNode {
protected:
	const Array::BinaryFuncPack &_binaryFuncPack;
	Connector _connectorSrcLeft;
	Connector _connectorSrcRight;
public:
	TrainNode_Binary(const char* nodeTypeName, const Array::BinaryFuncPack &binaryFuncPack, Connector* pConnectorDst) :
			TrainNode(nodeTypeName, pConnectorDst), _binaryFuncPack(binaryFuncPack),
			_connectorSrcLeft(this), _connectorSrcRight(this) {}
	Connector* GetConnectorSrcLeft() { return &_connectorSrcLeft; }
	Connector* GetConnectorSrcRight() { return &_connectorSrcRight; }
	const Connector* GetConnectorSrcLeft() const { return &_connectorSrcLeft; }
	const Connector* GetConnectorSrcRight() const { return &_connectorSrcRight; }
	virtual bool IsBinary();
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
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
	TrainNode_Add(Connector* pConnectorDst) :
			TrainNode_Binary("binary@add", Array::binaryFuncPack_Add, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Sub
//------------------------------------------------------------------------------
class TrainNode_Sub : public TrainNode_Binary {
public:
	TrainNode_Sub(Connector* pConnectorDst) :
			TrainNode_Binary("binary@sub", Array::binaryFuncPack_Sub, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Mul
//------------------------------------------------------------------------------
class TrainNode_Mul : public TrainNode_Binary {
public:
	TrainNode_Mul(Connector* pConnectorDst) :
			TrainNode_Binary("binary@mul", Array::binaryFuncPack_Mul, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Div
//------------------------------------------------------------------------------
class TrainNode_Div : public TrainNode_Binary {
public:
	TrainNode_Div(Connector* pConnectorDst) :
			TrainNode_Binary("binary@div", Array::binaryFuncPack_Div, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Pow
//------------------------------------------------------------------------------
class TrainNode_Pow : public TrainNode_Binary {
private:
	RefPtr<Array> _pArrayWork;
public:
	TrainNode_Pow(Connector* pConnectorDst) :
			TrainNode_Binary("binary@pow", Array::binaryFuncPack_Pow, pConnectorDst) {}
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
	TrainNode_Dot(Connector* pConnectorDst) :
			TrainNode_Binary("binary@dot", Array::binaryFuncPack_Dot, pConnectorDst) {}
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// NodeGear
//------------------------------------------------------------------------------
class NodeGear : public TrainNode {
public:
	class Creator {
	public:
		virtual NodeGear* Create(const Value &value, Connector* pConnectorDst, const Trainer* pTrainer) const = 0;
	};
protected:
	RefPtr<Gear> _pGear;
	Connector _connectorSrc;
public:
	NodeGear(Gear* pGear, Connector* pConnectorDst) :
			TrainNode(pGear->GetName(), pConnectorDst), _pGear(pGear), _connectorSrc(this) {}
	Connector* GetConnectorSrc() { return &_connectorSrc; }
	const Connector* GetConnectorSrc() const { return &_connectorSrc; }
	virtual bool IsGear();
	virtual bool GatherMemberSymbol(SymbolList& symbols);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual String ToString() const;
	virtual void Print(int indentLevel) const;
};
#endif

}

#endif
