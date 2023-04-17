//==============================================================================
// Node.h
//==============================================================================
#ifndef GURAX_MODULE_ML_NODE_H
#define GURAX_MODULE_ML_NODE_H
#include <gurax.h>
#include "Optimizer.h"

Gurax_BeginModuleScope(ml)

class Trainer; 
//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Node : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Node);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Node");
public:
	enum class Trait { Variable, Constant, Input, };
	class Connector {
	private:
		Node* _pNodeSrc;
		Node* _pNodeDst;
		RefPtr<Array> _pArrayGrad;
	public:
		Connector() : _pNodeSrc(nullptr), _pNodeDst(nullptr) {}
		Connector(const Connector& connector) :
			_pNodeSrc(connector._pNodeSrc), _pNodeDst(connector._pNodeDst), _pArrayGrad(connector._pArrayGrad.Reference()) {}
		Connector(Node* pNodeDst) : _pNodeSrc(nullptr), _pNodeDst(pNodeDst) {}
		Node& GetNodeSrc() { return *_pNodeSrc; }
		Node& GetNodeDst() { return *_pNodeDst; }
		const Node& GetNodeSrc() const { return *_pNodeSrc; }
		const Node& GetNodeDst() const { return *_pNodeDst; }
		void SetNodeSrc(Node* pNodeSrc) { _pNodeSrc = pNodeSrc; }
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
	explicit Node(const char* nodeTypeName) : _nodeTypeName(nodeTypeName) {}
	// Copy constructor/operator
	Node(const Node& src) = delete;
	Node& operator=(const Node& src) = delete;
	// Move constructor/operator
	Node(Node&& src) noexcept = delete;
	Node& operator=(Node&& src) noexcept = delete;
protected:
	~Node() = default;
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
	bool IsIdentical(const Node& other) const { return this == &other; }
	bool IsEqualTo(const Node& other) const { return IsIdentical(other); }
	bool IsLessThan(const Node& other) const { return this < &other; }
};

//------------------------------------------------------------------------------
// NodeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeList : public ListBase<Node*> {
public:
	void Reset();
	bool EvalForward(Processor& processor);
	bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// NodeOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NodeOwner : public NodeList {
public:
	~NodeOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// NodeMap
//------------------------------------------------------------------------------
using NodeMap = std::unordered_map<const Symbol*, Node*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;

//------------------------------------------------------------------------------
// Node_SingleOut
//------------------------------------------------------------------------------
class Node_SingleOut : public Node {
protected:
	Connector* _pConnectorDst;
public:
	Node_SingleOut(const char* nodeTypeName) : Node(nodeTypeName), _pConnectorDst(nullptr) {}
	virtual void Connect(Connector& connectorDst) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

//------------------------------------------------------------------------------
// Node_Branch
//------------------------------------------------------------------------------
class Node_Branch : public Node {
protected:
	RefPtr<Array> _pArrayGrad;
	ConnectorList _connectorsDst;
public:
	Node_Branch() : Node("Branch") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	virtual void Connect(Connector& connectorDst) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

//------------------------------------------------------------------------------
// Node_Head
//------------------------------------------------------------------------------
class Node_Head : public Node_SingleOut {
protected:
	RefPtr<Expr> _pExpr;
	RefPtr<Array> _pArrayGradAdj;
	Trait _trait;
	RefPtr<Optimizer::Instance> _pOptimizerInst;
public:
	Node_Head(Expr* pExpr, Trait trait, Optimizer::Instance* pOptimizerInst) :
		Node_SingleOut("Head"), _pExpr(pExpr), _trait(trait), _pOptimizerInst(pOptimizerInst) {}
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
// Node_Bottom
//------------------------------------------------------------------------------
class Node_Bottom : public Node_SingleOut {
private:
	Connector _connectorSrc;
	RefPtr<Array> _pArrayCorrect;
public:
	Node_Bottom() : Node_SingleOut("Bottom"), _connectorSrc(this) {}
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
// Node_Unary
//------------------------------------------------------------------------------
class Node_Unary : public Node_SingleOut {
protected:
	Connector _connectorSrc;
public:
	Node_Unary(const char* nodeTypeName) : Node_SingleOut(nodeTypeName), _connectorSrc(this) {}
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
// Node_Neg
//------------------------------------------------------------------------------
class Node_Neg : public Node_Unary {
public:
	Node_Neg() : Node_Unary("Neg") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Binary
//------------------------------------------------------------------------------
class Node_Binary : public Node_SingleOut {
protected:
	Connector _connectorSrcLeft;
	Connector _connectorSrcRight;
public:
	Node_Binary(const char* nodeTypeName) : Node_SingleOut(nodeTypeName), _connectorSrcLeft(this), _connectorSrcRight(this) {}
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
// Node_Add
//------------------------------------------------------------------------------
class Node_Add : public Node_Binary {
public:
	Node_Add() : Node_Binary("Add") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Sub
//------------------------------------------------------------------------------
class Node_Sub : public Node_Binary {
public:
	Node_Sub() : Node_Binary("Sub") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Mul
//------------------------------------------------------------------------------
class Node_Mul : public Node_Binary {
public:
	Node_Mul() : Node_Binary("Mul") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Div
//------------------------------------------------------------------------------
class Node_Div : public Node_Binary {
public:
	Node_Div() : Node_Binary("Div") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Pow
//------------------------------------------------------------------------------
class Node_Pow : public Node_Binary {
private:
	RefPtr<Array> _pArrayWork;
public:
	Node_Pow() : Node_Binary("Pow") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Dot
//------------------------------------------------------------------------------
class Node_Dot : public Node_Binary {
private:
	RefPtr<Array> _pArrayFwdLeftTrans;
	RefPtr<Array> _pArrayFwdRightTrans;
public:
	Node_Dot() : Node_Binary("Dot") {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
};

//------------------------------------------------------------------------------
// Node_Gear
//------------------------------------------------------------------------------
class Node_Gear : public Node_Unary {
private:
	RefPtr<Expr> _pExprRight;
	RefPtr<Gear> _pGear;
public:
	Node_Gear(Expr* pExprRight) : Node_Unary("Gear"), _pExprRight(pExprRight) {}
	virtual bool EvalForward(Processor& processor);
	virtual bool EvalBackward(Processor& processor);
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

Gurax_EndModuleScope(ml)

#endif
