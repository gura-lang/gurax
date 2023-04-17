//==============================================================================
// Trainer.h
//==============================================================================
#ifndef GURAX_MODULE_ML_TRAINER_H
#define GURAX_MODULE_ML_TRAINER_H
#include <gurax.h>
#include "Node.h"
#include "Optimizer.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Trainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Trainer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Trainer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Trainer");
public:
	//using NodeGearCreatorMap = std::map<ValueType, const NodeGear::Creator*>;
public:
	Composer _composer;
	RefPtr<Expr> _pExprModel;
	RefPtr<Optimizer> _pOptimizer;
	RefPtr<Node_Bottom> _pNodeBottom;
	NodeOwner _nodeOwner;
	NodeMap _nodeMap;
	//static NodeGearCreatorMap _nodeGearCreatorMap;
public:
	// Constructor
	Trainer(Expr* pExprModel, Optimizer* pOptimizer);
	// Copy constructor/operator
	Trainer(const Trainer& src) = delete;
	Trainer& operator=(const Trainer& src) = delete;
	// Move constructor/operator
	Trainer(Trainer&& src) noexcept = delete;
	Trainer& operator=(Trainer&& src) noexcept = delete;
protected:
	~Trainer() = default;
public:
	bool CreateFromExpr(const SymbolSet& inputs);
	void Reset();
	bool EvalForward(Processor& processor);
	bool EvalBackward(Processor& processor, const Array& arrayCorrect);
	const Array& GetResult() const;
	Double CalcMeanSquareError(const Array& arrayCorrect) const;
	Double CalcCrossEntropyError(const Array& arrayCorrect, Double epsilon) const;
	Node_Bottom& GetNodeBottom() { return *_pNodeBottom; }
	const Node_Bottom& GetNodeBottom() const { return *_pNodeBottom; }
	NodeOwner& GetNodeOwner() { return _nodeOwner; }
	const NodeOwner& GetNodeOwner() const { return _nodeOwner; }
	const Expr& GetExprModel() const { return *_pExprModel; }
	const Optimizer& GetOptimizer() const { return *_pOptimizer; }
	Optimizer::Instance* CreateOptimizerInstance() const { return _pOptimizer->CreateInstance(); }
	Node* FindNode(const Symbol* pSymbol) const;
	void Print(Stream& stream) const;
	//static void RegisterNodeGearCreator(ValueType valType, const NodeGear::Creator* pCreator) {
	//	_nodeGearCreatorMap[valType] = pCreator;
	//}
private:
	Node* CreateNode(const Expr& expr, const SymbolSet& symbolsInput);
	Node* CreateNodeUnary(const Expr_UnaryOp& exprEx, const SymbolSet& symbolsInput);
	Node* CreateNodeBinary(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput);
	Node* CreateNodeGear(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Trainer& other) const { return this == &other; }
	bool IsEqualTo(const Trainer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Trainer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// TrainerList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainerList : public ListBase<Trainer*> {
};

//------------------------------------------------------------------------------
// TrainerOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainerOwner : public TrainerList {
public:
	~TrainerOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
