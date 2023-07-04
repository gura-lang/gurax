//==============================================================================
// Node.h
//==============================================================================
#ifndef GURAX_MODULE_ML_NODE_H
#define GURAX_MODULE_ML_NODE_H
#include <gurax.h>
#include "Optimizers.h"
#include "Symbols.h"

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
	const Symbol* _pSymbol;
	RefPtr<Array> _pArrayFwd;
public:
	// Constructor
	Node();
	// Copy constructor/operator
	Node(const Node& src) = delete;
	Node& operator=(const Node& src) = delete;
	// Move constructor/operator
	Node(Node&& src) noexcept = delete;
	Node& operator=(Node&& src) noexcept = delete;
protected:
	~Node() = default;
public:
	void SetSymbol(const Symbol* pSymbol) { _pSymbol = pSymbol; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	virtual void Connect(Connector& connectorDst) = 0;
	Array& GetArrayFwd() { return *_pArrayFwd; }
	const Array& GetArrayFwd() const { return *_pArrayFwd; }
	RefPtr<Array>& GetArrayFwdRefPtr() { return _pArrayFwd; }
	const char* GetTypeName() const { return GetTypeSymbol()->GetName(); }
	virtual const Symbol* GetTypeSymbol() const = 0;
	virtual bool IsInput() const { return false; }
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
class GURAX_DLLDECLARE NodeOwner : public NodeList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(NodeOwner);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("NodeOwner");
protected:
	~NodeOwner() { Clear(); }
public:
	void Clear();
};

//------------------------------------------------------------------------------
// Node_SingleOut
//------------------------------------------------------------------------------
class Node_SingleOut : public Node {
protected:
	Connector* _pConnectorDst;
public:
	Node_SingleOut() : _pConnectorDst(nullptr) {}
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
	Node_Branch() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(branch); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
	virtual void Connect(Connector& connectorDst) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

//------------------------------------------------------------------------------
// Node_Expr
//------------------------------------------------------------------------------
class Node_Expr : public Node_SingleOut {
protected:
	RefPtr<Expr> _pExpr;
public:
	Node_Expr(Expr* pExpr) : _pExpr(pExpr) {}
	const Expr& GetExpr() const { return *_pExpr; }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const override;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const override;
	virtual void Print(Stream& stream, int indentLevel) const override;
};

//------------------------------------------------------------------------------
// Node_Variable
//------------------------------------------------------------------------------
class Node_Variable : public Node_Expr {
protected:
	RefPtr<Optimizer::Instance> _pOptimizerInst;
public:
	Node_Variable(Expr* pExpr, const Optimizer& optimizer) : Node_Expr(pExpr), _pOptimizerInst(optimizer.CreateInstance()) {}
	virtual bool IsVulnerable() const override { return true; }
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(variable); }
	virtual void Reset() override;
	virtual bool EvalBackward(Processor& processor) override;
	virtual String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// Node_Const
//------------------------------------------------------------------------------
class Node_Const : public Node_Expr {
public:
	Node_Const(Expr* pExpr) : Node_Expr(pExpr) {}
	virtual bool IsVulnerable() const { return false; }
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(const_); }
	virtual bool EvalBackward(Processor& processor) override { return true; }
	virtual String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// Node_Input
//------------------------------------------------------------------------------
class Node_Input : public Node_SingleOut {
protected:
	RefPtr<Array> _pArray;	// maybe nullptr
public:
	Node_Input() {}
	void SetArray(Array* pArray) { _pArray.reset(pArray); }
	const Array& GetArray() const { return *_pArray; }
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(input); }
	virtual bool IsInput() const { return true; }
	virtual void Reset();
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
	virtual String ToString(const StringStyle& ss) const;
	virtual void Print(Stream& stream, int indentLevel) const;
};

//------------------------------------------------------------------------------
// NodeList_Input
//------------------------------------------------------------------------------
using NodeList_Input = ListBase<Node_Input*>;

//------------------------------------------------------------------------------
// Node_Bottom
//------------------------------------------------------------------------------
class Node_Bottom : public Node_SingleOut {
private:
	Connector _connectorSrc;
	RefPtr<Array> _pArrayCorrect;
public:
	Node_Bottom() : _connectorSrc(this) {}
	Connector& GetConnectorSrc() { return _connectorSrc; }
	const Connector& GetConnectorSrc() const { return _connectorSrc; }
	Array& GetArrayCorrect() { return *_pArrayCorrect; }
	const Array& GetArrayCorrect() const { return *_pArrayCorrect; }
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(bottom); }
	virtual bool IsBottom() const { return true; }
	virtual bool IsVulnerable() const;
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
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
	Node_Unary() : _connectorSrc(this) {}
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
	Node_Neg() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(neg); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Binary
//------------------------------------------------------------------------------
class Node_Binary : public Node_SingleOut {
protected:
	Connector _connectorSrcLeft;
	Connector _connectorSrcRight;
public:
	Node_Binary() : _connectorSrcLeft(this), _connectorSrcRight(this) {}
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
	Node_Add() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(add); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Sub
//------------------------------------------------------------------------------
class Node_Sub : public Node_Binary {
public:
	Node_Sub() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(sub); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Mul
//------------------------------------------------------------------------------
class Node_Mul : public Node_Binary {
public:
	Node_Mul() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(mul); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Div
//------------------------------------------------------------------------------
class Node_Div : public Node_Binary {
public:
	Node_Div() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(div); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Pow
//------------------------------------------------------------------------------
class Node_Pow : public Node_Binary {
private:
	RefPtr<Array> _pArrayWork;
public:
	Node_Pow() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(pow); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Dot
//------------------------------------------------------------------------------
class Node_Dot : public Node_Binary {
private:
	RefPtr<Array> _pArrayFwdLeftTrans;
	RefPtr<Array> _pArrayFwdRightTrans;
public:
	Node_Dot() {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(dot); }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Gear
//------------------------------------------------------------------------------
class Node_Gear : public Node_Unary {
private:
	RefPtr<Optimizer> _pOptimizer;
	RefPtr<Expr> _pExprRight;
	RefPtr<Gear> _pGear;
public:
	Node_Gear(Optimizer* pOptimizer, Expr* pExprRight) : _pOptimizer(pOptimizer), _pExprRight(pExprRight) {}
	virtual const Symbol* GetTypeSymbol() const override { return Gurax_Symbol(gear); }
	const Optimizer& GetOptimizer() const { return *_pOptimizer; }
	virtual bool IsVulnerable() const override;
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

Gurax_EndModuleScope(ml)

#endif
