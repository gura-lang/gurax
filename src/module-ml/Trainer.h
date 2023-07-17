//==============================================================================
// Trainer.h
//==============================================================================
#ifndef GURAX_MODULE_ML_TRAINER_H
#define GURAX_MODULE_ML_TRAINER_H
#include <gurax.h>
#include "Node.h"
#include "NodeMap.h"
#include "Optimizers.h"

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
	class GearController : public Gear::Controller {
	public:
		virtual void InitArray(Array& array, size_t nInputs) const {
			array.FillRandomNormal(0, ::sqrt(1. / nInputs), Random::Global());
		}
		virtual bool IsTraining() const { return true; }
	};
public:
	RefPtr<Processor> _pProcessor;
	Composer _composer;
	RefPtr<Expr> _pExprModel;
	SymbolList _symbolsInput;
	RefPtr<Optimizer> _pOptimizer;
	RefPtr<Node_Bottom> _pNodeBottom;
	RefPtr<NodeOwner> _pNodeOwner;
	RefPtr<NodeMap> _pNodeMap;
	NodeList_Input _nodesInput;
public:
	// Constructor
	Trainer(Processor* pProcessor, Expr* pExprModel, SymbolList symbolsInput, Optimizer* pOptimizer);
	// Copy constructor/operator
	Trainer(const Trainer& src) = delete;
	Trainer& operator=(const Trainer& src) = delete;
	// Move constructor/operator
	Trainer(Trainer&& src) noexcept = delete;
	Trainer& operator=(Trainer&& src) noexcept = delete;
protected:
	~Trainer() = default;
public:
	static void Initialize();
	Processor& GetProcessor() { return *_pProcessor; }
	bool CreateFromExpr();
	void Reset();
	bool EvalForward(const ValueList& valuesInput);
	bool EvalBackward(const Array& arrayCorrect);
	const Array& GetResult() const;
	Double CalcMeanSquareError(const Array& arrayCorrect) const;
	Double CalcCrossEntropyError(const Array& arrayCorrect, Double epsilon) const;
	Node_Bottom& GetNodeBottom() { return *_pNodeBottom; }
	const Node_Bottom& GetNodeBottom() const { return *_pNodeBottom; }
	NodeOwner& GetNodeOwner() { return *_pNodeOwner; }
	const NodeOwner& GetNodeOwner() const { return *_pNodeOwner; }
	const Expr& GetExprModel() const { return *_pExprModel; }
	const Optimizer& GetOptimizer() const { return *_pOptimizer; }
	const NodeMap& GetNodeMap() const { return *_pNodeMap; }
	Node* FindNode(const Symbol* pSymbol) const { return _pNodeMap->FindNode(pSymbol); }
	const SymbolList& GetSymbolsInput() { return  _symbolsInput; }
	void Print(Stream& stream) const;
private:
	Node* CreateNode(const Expr& expr);
	Node* CreateNodeUnary(const Expr_UnaryOp& exprEx);
	Node* CreateNodeBinary(const Expr_BinaryOp& exprEx);
	Node* CreateNodeGear(const Expr_BinaryOp& exprEx);
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
