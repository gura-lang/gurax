//==============================================================================
// TrainNode.h
//==============================================================================
#ifndef GURAX_MODULE_ML_TRAINNODE_H
#define GURAX_MODULE_ML_TRAINNODE_H
#include <gurax.h>
#include "TrainOptimizer.h"

Gurax_BeginModuleScope(ml)

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
		Connector() : _pNodeSrc(nullptr), _pNodeDst(nullptr) {}
		Connector(const Connector& connector) :
			_pNodeSrc(connector._pNodeSrc), _pNodeDst(connector._pNodeDst), _pArrayGrad(connector._pArrayGrad.Reference()) {}
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
		void operator=(const Connector& connector) {
			_pNodeSrc = connector._pNodeSrc, _pNodeDst = connector._pNodeDst, _pArrayGrad.reset(connector._pArrayGrad.Reference());
		}
	};
	class ConnectorList : public ListBase<Connector*> {
	public:
		ConnectorList() {}
	};
protected:
	const char* _nodeTypeName;
	RefPtr<Array> _pArrayFwd;
public:
	// Constructor
	explicit TrainNode(const char* nodeTypeName) : _nodeTypeName(nodeTypeName) {}
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
	virtual void Connect(Connector& connectorDst) = 0;
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
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
	virtual void Print(Stream& stream, int indentLevel) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const TrainNode& other) const { return this == &other; }
	bool IsEqualTo(const TrainNode& other) const { return IsIdentical(other); }
	bool IsLessThan(const TrainNode& other) const { return this < &other; }
};

//------------------------------------------------------------------------------
// TrainNodeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainNodeList : public ListBase<TrainNode*> {
public:
	void Reset();
	bool EvalForward(Processor& processor);
	bool EvalBackward(Processor& processor);
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
// TrainNodeMap
//------------------------------------------------------------------------------
using TrainNodeMap = std::unordered_map<const Symbol*, TrainNode*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;

//------------------------------------------------------------------------------
// TrainNode_SingleOut
//------------------------------------------------------------------------------
class TrainNode_SingleOut : public TrainNode {
protected:
	Connector* _pConnectorDst;
public:
	TrainNode_SingleOut(const char* nodeTypeName) : TrainNode(nodeTypeName), _pConnectorDst(nullptr) {}
	virtual void Connect(Connector& connectorDst) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

//------------------------------------------------------------------------------
// TrainNode_Branch
//------------------------------------------------------------------------------
class TrainNode_Branch : public TrainNode {
protected:
	RefPtr<Array> _pArrayGrad;
	ConnectorList _connectorsDst;
public:
	TrainNode_Branch() : TrainNode("Branch") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	virtual void Connect(Connector& connectorDst) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

//------------------------------------------------------------------------------
// TrainNode_Head
//------------------------------------------------------------------------------
class TrainNode_Head : public TrainNode_SingleOut {
protected:
	RefPtr<Expr> _pExpr;
	RefPtr<Array> _pArrayGradAdj;
	Trait _trait;
	RefPtr<TrainOptimizer::Instance> _pTrainOptimizerInst;
public:
	TrainNode_Head(Expr* pExpr, Trait trait, TrainOptimizer::Instance* pTrainOptimizerInst) :
		TrainNode_SingleOut("Head"), _pExpr(pExpr), _trait(trait), _pTrainOptimizerInst(pTrainOptimizerInst) {}
	const Expr& GetExpr() const { return *_pExpr; }
	bool IsVariable() const { return _trait == Trait::Variable; }
	bool IsConstant() const { return _trait == Trait::Constant; }
	bool IsInput() const { return _trait == Trait::Input; }
	const char* GetTraitName() const;
	virtual bool IsHead() const { return true; }
	virtual void Reset();
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
	virtual String ToString(const StringStyle& ss) const;
	virtual void Print(Stream& stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Bottom
//------------------------------------------------------------------------------
class TrainNode_Bottom : public TrainNode_SingleOut {
private:
	Connector _connectorSrc;
	RefPtr<Array> _pArrayCorrect;
public:
	TrainNode_Bottom() : TrainNode_SingleOut("Bottom"), _connectorSrc(this) {}
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	Array& GetArrayCorrect() { return *_pArrayCorrect; }
	const Array& GetArrayCorrect() const { return *_pArrayCorrect; }
	virtual bool IsBottom() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	bool EvalBackwardTop(Processor& processor, const Array& arrayCorrect);
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
	virtual String ToString(const StringStyle& ss) const;
	virtual void Print(Stream& stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Unary
//------------------------------------------------------------------------------
class TrainNode_Unary : public TrainNode_SingleOut {
protected:
	Connector _connectorSrc;
public:
	TrainNode_Unary(const char* nodeTypeName) : TrainNode_SingleOut(nodeTypeName), _connectorSrc(this) {}
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	virtual bool IsUnary() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
	virtual String ToString(const StringStyle& ss) const;
	virtual void Print(Stream& stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Neg
//------------------------------------------------------------------------------
class TrainNode_Neg : public TrainNode_Unary {
public:
	TrainNode_Neg() : TrainNode_Unary("Neg") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Binary
//------------------------------------------------------------------------------
class TrainNode_Binary : public TrainNode_SingleOut {
protected:
	Connector _connectorSrcLeft;
	Connector _connectorSrcRight;
public:
	TrainNode_Binary(const char* nodeTypeName) : TrainNode_SingleOut(nodeTypeName), _connectorSrcLeft(this), _connectorSrcRight(this) {}
	Connector& GetConnectorSrcLeft() { return _connectorSrcLeft; }
	Connector& GetConnectorSrcRight() { return _connectorSrcRight; }
	const Connector& GetConnectorSrcLeft() const { return _connectorSrcLeft; }
	const Connector& GetConnectorSrcRight() const { return _connectorSrcRight; }
	virtual bool IsBinary() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
	virtual String ToString(const StringStyle& ss) const;
	virtual void Print(Stream& stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// TrainNode_Add
//------------------------------------------------------------------------------
class TrainNode_Add : public TrainNode_Binary {
public:
	TrainNode_Add() : TrainNode_Binary("Add") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Sub
//------------------------------------------------------------------------------
class TrainNode_Sub : public TrainNode_Binary {
public:
	TrainNode_Sub() : TrainNode_Binary("Sub") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Mul
//------------------------------------------------------------------------------
class TrainNode_Mul : public TrainNode_Binary {
public:
	TrainNode_Mul() : TrainNode_Binary("Mul") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Div
//------------------------------------------------------------------------------
class TrainNode_Div : public TrainNode_Binary {
public:
	TrainNode_Div() : TrainNode_Binary("Div") {}
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
	TrainNode_Pow() : TrainNode_Binary("Pow") {}
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
	TrainNode_Dot() : TrainNode_Binary("Dot") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// TrainNode_Gear
//------------------------------------------------------------------------------
class TrainNode_Gear : public TrainNode_Unary {
private:
	RefPtr<Expr> _pExprRight;
	RefPtr<Gear> _pGear;
public:
	TrainNode_Gear(Expr* pExprRight) : TrainNode_Unary("Gear"), _pExprRight(pExprRight) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

Gurax_EndModuleScope(ml)

#endif
