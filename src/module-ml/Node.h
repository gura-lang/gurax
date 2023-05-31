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
	virtual String GetTypeName() const = 0;
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
	virtual String GetTypeName() const override;
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
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
		_pExpr(pExpr), _trait(trait), _pOptimizerInst(pOptimizerInst) {}
	const Expr& GetExpr() const { return *_pExpr; }
	bool IsVariable() const { return _trait == Trait::Variable; }
	bool IsConstant() const { return _trait == Trait::Constant; }
	bool IsInput() const { return _trait == Trait::Input; }
	const char* GetTraitName() const;
	virtual String GetTypeName() const override { return "Head"; }
	virtual bool IsHead() const { return true; }
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
// Node_Input
//------------------------------------------------------------------------------
class Node_Input : public Node_SingleOut {
protected:
	RefPtr<Array> _pArray;
public:
	Node_Input() {}
	const Array& GetArray() const { return *_pArray; }
	virtual String GetTypeName() const override { return "Input"; }
	virtual bool IsHead() const { return true; }
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
	virtual String GetTypeName() const override { return "Bottom"; }
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
	virtual String GetTypeName() const override { return "Neg"; }
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
	virtual String GetTypeName() const override { return "Add"; }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Sub
//------------------------------------------------------------------------------
class Node_Sub : public Node_Binary {
public:
	Node_Sub() {}
	virtual String GetTypeName() const override { return "Sub"; }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Mul
//------------------------------------------------------------------------------
class Node_Mul : public Node_Binary {
public:
	Node_Mul() {}
	virtual String GetTypeName() const override { return "Mul"; }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Div
//------------------------------------------------------------------------------
class Node_Div : public Node_Binary {
public:
	Node_Div() {}
	virtual String GetTypeName() const override { return "Div"; }
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
	virtual String GetTypeName() const override { return "Pow"; }
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
	virtual String GetTypeName() const override { return "Dot"; }
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
};

//------------------------------------------------------------------------------
// Node_Gear
//------------------------------------------------------------------------------
class Node_Gear : public Node_Unary {
private:
	RefPtr<Expr> _pExprRight;
	RefPtr<Gear> _pGear;
public:
	Node_Gear(Expr* pExprRight) : _pExprRight(pExprRight) {}
	virtual String GetTypeName() const override {
		return String().Format("Gear:%s", _pGear? _pGear->GetName() : "nil");
	}
	virtual bool EvalForward(Processor& processor) override;
	virtual bool EvalBackward(Processor& processor) override;
	virtual bool GatherMemberSymbol(SymbolList& symbols) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const;
};

Gurax_EndModuleScope(ml)

#endif
