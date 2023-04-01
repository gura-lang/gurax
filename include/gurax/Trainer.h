//==============================================================================
// Trainer.h
//==============================================================================
#ifndef GURAX_TRAINER_H
#define GURAX_TRAINER_H
#include "TrainNode.h"
#include "TrainOptimizer.h"

namespace Gurax {

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
	//using TrainNodeGearCreatorMap = std::map<ValueType, const NodeGear::Creator*>;
public:
	RefPtr<TrainOptimizer> _pTrainOptimizer;
	RefPtr<TrainNode_Bottom> _pNodeBottom;
	TrainNodeOwner _nodeOwner;
	TrainNodeMap _nodeMap;
	RefPtr<Expr> _pExprModel;
	//static NodeGearCreatorMap _nodeGearCreatorMap;
public:
	// Constructor
	Trainer() {}
	// Copy constructor/operator
	Trainer(const Trainer& src) = delete;
	Trainer& operator=(const Trainer& src) = delete;
	// Move constructor/operator
	Trainer(Trainer&& src) noexcept = delete;
	Trainer& operator=(Trainer&& src) noexcept = delete;
protected:
	~Trainer() = default;
public:
	bool CreateFromExpr(const Expr& exprModel, const SymbolSet& inputs);
	void Reset();
	bool EvalForward();
	bool EvalBackward(const Array& arrayCorrect);
	const Array* GetResult() const;
	Double CalcMeanSquareError(const Array& arrayCorrect) const;
	Double CalcCrossEntropyError(const Array& arrayCorrect, Double epsilon) const;
	TrainNode_Bottom& GetNodeBottom() { return *_pNodeBottom; }
	const TrainNode_Bottom& GetNodeBottom() const { return *_pNodeBottom; }
	const TrainNodeOwner& GetNodeOwner() const { return _nodeOwner; }
	const Expr& GetExprModel() const { return *_pExprModel; }
	TrainOptimizer::Instance* CreateOptimizerInstance() const { return _pTrainOptimizer->CreateInstance(); }
	TrainNode* FindNode(const Symbol* pSymbol) const;
	void Print() const;
	//static void RegisterNodeGearCreator(ValueType valType, const NodeGear::Creator* pCreator) {
	//	_nodeGearCreatorMap[valType] = pCreator;
	//}
private:
	TrainNode* CreateNode(const Expr& expr, const SymbolSet& symbolsInput);
	TrainNode* CreateNodeUnary(const Expr_UnaryOp& exprEx, const SymbolSet& symbolsInput);
	TrainNode* CreateNodeBinary(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput);
	TrainNode* CreateNodeGear(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput);
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

}

#endif
