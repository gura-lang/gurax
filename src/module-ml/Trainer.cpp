//==============================================================================
// Trainer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Trainer
//------------------------------------------------------------------------------
std::function<Double (const Array& arrayFwdOut, const Array& arrayTrain)> CalcMeanSquareErrorTbl[Array::ElemTypeIdMax];
std::function<Double (const Array& arrayFwdOut, const Array& arrayTrain)> CalcCrossEntropyErrorTbl[Array::ElemTypeIdMax];

template<typename T_Elem> Double CalcMeanSquareError_T(const Array& arrayFwdOut, const Array& arrayTrain)
{
	Double rtn = 0;
	const T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdOutEnd = pFwdOut + arrayFwdOut.GetDimSizes().CalcLength();
	const T_Elem* pTrain = arrayTrain.GetPointerC<T_Elem>();
	for ( ; pFwdOut != pFwdOutEnd; pFwdOut++, pTrain++) {
		Double tmp = *pFwdOut - *pTrain;
		rtn += tmp * tmp;
	}
	rtn /= 2;
	return rtn;
}

template<> Double CalcMeanSquareError_T<Complex>(const Array& arrayFwdOut, const Array& arrayTrain) { return 0; }
template<> Double CalcMeanSquareError_T<Half>(const Array& arrayFwdOut, const Array& arrayTrain) { return 0; }

template<typename T_Elem> Double CalcCrossEntropyError_T(const Array& arrayFwdOut, const Array& arrayTrain)
{
	Double rtn = 0;
	arrayFwdOut.GetDimSizes().CalcLength();
	const T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdOutEnd = pFwdOut + arrayFwdOut.GetDimSizes().CalcLength();
	const T_Elem* pTrain = arrayTrain.GetPointerC<T_Elem>();
	for ( ; pFwdOut != pFwdOutEnd; pFwdOut++, pTrain++) {
		rtn += *pTrain * std::log(*pFwdOut + 1.e-7);
	}
	rtn = -rtn;
	return rtn;
}

template<> Double CalcCrossEntropyError_T<Complex>(const Array& arrayFwdOut, const Array& arrayTrain) { return 0; }
template<> Double CalcCrossEntropyError_T<Half>(const Array& arrayFwdOut, const Array& arrayTrain) { return 0; }

Trainer::Trainer(Expr* pExprModel, Optimizer* pOptimizer) :
		_pExprModel(pExprModel), _pOptimizer(pOptimizer), _pNodeBottom(new Node_Bottom())
{
}

void Trainer::Initialize()
{
	Gurax_SetArrayFuncSingle(CalcMeanSquareErrorTbl, CalcMeanSquareError_T);
	Gurax_SetArrayFuncSingle(CalcCrossEntropyErrorTbl, CalcCrossEntropyError_T);
}

bool Trainer::CreateFromExpr(const SymbolSet& inputs)
{
	RefPtr<Node> pNode(CreateNode(GetExprModel(), inputs));
	if (!pNode) return false;
	_composer.Add_Terminate();
	pNode->Connect(GetNodeBottom().GetConnectorSrc());
	//_nodeOwner.push_back(pNode.release());
	return true;
}

void Trainer::Reset()
{
	GetNodeOwner().Reset();
}

bool Trainer::EvalForward(Processor& processor)
{
	return GetNodeOwner().EvalForward(processor) && GetNodeBottom().EvalForward(processor);
}

bool Trainer::EvalBackward(Processor& processor, const Array& arrayCorrect)
{
	return GetNodeBottom().EvalBackwardTop(processor, arrayCorrect) && GetNodeOwner().EvalBackward(processor);
}

const Array& Trainer::GetResult() const
{
	return GetNodeBottom().GetArrayFwd();
}

Double Trainer::CalcMeanSquareError(const Array& arrayCorrect) const
{
	const Array& arrayResult = GetResult();
	if (!arrayResult.HasSameShape(arrayCorrect)) {
		Error::Issue(ErrorType::RangeError, "unmathced size of arrays");
		return 0;
	}
	return CalcMeanSquareErrorTbl[arrayResult.GetElemType().id](arrayResult, arrayCorrect);
}

Double Trainer::CalcCrossEntropyError(const Array& arrayCorrect, Double epsilon) const
{
	const Array& arrayResult = GetResult();
	if (!arrayResult.HasSameShape(arrayCorrect)) return 0;
	return CalcCrossEntropyErrorTbl[arrayResult.GetElemType().id](arrayResult, arrayCorrect);
}

Node* Trainer::FindNode(const Symbol* pSymbol) const
{
	auto iter = _nodeMap.find(pSymbol);
	return (iter == _nodeMap.end())? nullptr : iter->second;
}

void Trainer::Print(Stream& stream) const
{
	GetNodeBottom().Print(stream, 0);
	stream.Println();
	size_t i = 0;
	for (const Node* pNode : _nodeOwner) {
		stream.Printf("#%d %s\n", i, pNode->ToString().c_str());
		i++;
	}
}

Node* Trainer::CreateNode(const Expr& expr, const SymbolSet& symbolsInput)
{
	//::printf("CreateNode(%s)\n", expr.ToString().c_str());
	if (expr.IsType<Expr_Block>()) {
		Node *pNodeRtn = nullptr;
		const Expr_Block& exprEx = dynamic_cast<const Expr_Block&>(expr);
		const Expr* pExprEach = exprEx.GetExprElemFirst();
		if (!pExprEach) {
			// returns dummy node
			return nullptr;
		}
		for ( ; pExprEach->GetExprNext(); pExprEach = pExprEach->GetExprNext()) {
			RefPtr<Node> pNode(CreateNode(*pExprEach, symbolsInput));
			if (!pNode) return nullptr;
			_nodeOwner.push_back(pNode.release());
		}
		RefPtr<Node> pNode(CreateNode(*pExprEach, symbolsInput));
		_nodeOwner.push_back(pNode.Reference());
		return pNode.release();
	} else if (expr.IsType<Expr_Assign>()) {
		const Expr_Assign& exprEx = dynamic_cast<const Expr_Assign&>(expr);
		if (exprEx.GetOperator() ) {
			Error::Issue(ErrorType::SyntaxError, "invalid assignment");
			return nullptr;
		}
		if (!exprEx.GetExprLeft().IsType<Expr_Identifier>()) {
			Error::Issue(ErrorType::SyntaxError, "only the assignment to an identifier is supported");
			return nullptr;
		}
		const Symbol* pSymbol = dynamic_cast<const Expr_Identifier&>(exprEx.GetExprLeft()).GetSymbol();
		RefPtr<Node> pNode(CreateNode(exprEx.GetExprRight(), symbolsInput));
		if (!pNode) return nullptr;
		if (_nodeMap.find(pSymbol) != _nodeMap.end()) {
			Error::Issue(ErrorType::SyntaxError, "duplicated assignment to the identifier %s", pSymbol->GetName());
			return nullptr;
		}
		_nodeMap[pSymbol] = pNode.get();
		return pNode.release();
	} else if (expr.IsType<Expr_UnaryOp>()) {
		const Expr_UnaryOp& exprEx = dynamic_cast<const Expr_UnaryOp&>(expr);
		RefPtr<Node> pNode(CreateNodeUnary(exprEx, symbolsInput));
		_nodeOwner.push_back(pNode.Reference());
		return pNode.release();
	} else if (expr.IsType<Expr_BinaryOp>()) {
		const Expr_BinaryOp& exprEx = dynamic_cast<const Expr_BinaryOp&>(expr);
		RefPtr<Node> pNode(exprEx.GetOperator()->IsType(OpType::Gear)?
			CreateNodeGear(exprEx, symbolsInput) : CreateNodeBinary(exprEx, symbolsInput));
		_nodeOwner.push_back(pNode.Reference());
		return pNode.release();
	} else if (expr.IsType<Expr_Identifier>()) {
		const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(expr);
		const Symbol* pSymbol = exprEx.GetSymbol();
		Node *pNodeFound = FindNode(pSymbol);
		if (pNodeFound) return pNodeFound;
		Node::Trait trait = Node::Trait::Input;
		RefPtr<Optimizer::Instance> pOptimizer;
		if (!symbolsInput.IsSet(pSymbol)) {
			trait = Node::Trait::Variable;
			pOptimizer.reset(CreateOptimizerInstance());
		}
		RefPtr<Expr> pExpr(expr.Reference());
		if (!pExpr->PrepareAndCompose(_composer)) return nullptr;
		RefPtr<Node> pNode(new Node_Head(pExpr.release(), trait, pOptimizer.release()));
		_nodeOwner.push_back(pNode.Reference());
		_nodeMap[pSymbol] = pNode.get();
		return pNode.release();
	} else if (expr.IsType<Expr_Value>()) {
		Node::Trait trait = Node::Trait::Constant;
		RefPtr<Optimizer::Instance> pOptimizer;
		RefPtr<Expr> pExpr(expr.Reference());
		if (!pExpr->PrepareAndCompose(_composer)) return nullptr;
		RefPtr<Node> pNode(new Node_Head(pExpr.release(), trait, pOptimizer.release()));
		_nodeOwner.push_back(pNode.Reference());
		return pNode.release();
	} else {
		Node::Trait trait = Node::Trait::Variable;
		RefPtr<Optimizer::Instance> pOptimizer(CreateOptimizerInstance());
		RefPtr<Expr> pExpr(expr.Reference());
		if (!pExpr->PrepareAndCompose(_composer)) return nullptr;
		RefPtr<Node> pNode(new Node_Head(pExpr.release(), trait, pOptimizer.release()));
		_nodeOwner.push_back(pNode.Reference());
		return pNode.release();
	}

	return nullptr;
}

Node* Trainer::CreateNodeUnary(const Expr_UnaryOp& exprEx, const SymbolSet& symbolsInput)
{
	const Operator* pOperator = exprEx.GetOperator();
	RefPtr<Node_Unary> pNode;
	if (pOperator->IsType(OpType::Pos)) {
		//pNode.reset(new Node_Pos());
	} else if (pOperator->IsType(OpType::Neg)) {
		pNode.reset(new Node_Neg());
	} else {
		Error::Issue(ErrorType::ValueError, "unsupported operator: %s", pOperator->GetName());
		return nullptr;
	}
	RefPtr<Node> pNodeChild(CreateNode(exprEx.GetExprChild(), symbolsInput));
	if (!pNodeChild) return nullptr;
	pNodeChild->Connect(pNode->GetConnectorSrc());
	//_nodeOwner.push_back(pNodeChild.release());
	return pNode.release();
}

Node* Trainer::CreateNodeBinary(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput)
{
	const Operator* pOperator = exprEx.GetOperator();
	RefPtr<Node_Binary> pNode;
	if (pOperator->IsType(OpType::Add)) {
		pNode.reset(new Node_Add());
	} else if (pOperator->IsType(OpType::Sub)) {
		pNode.reset(new Node_Sub());
	} else if (pOperator->IsType(OpType::Mul)) {
		pNode.reset(new Node_Mul());
	} else if (pOperator->IsType(OpType::Div)) {
		pNode.reset(new Node_Div());
	} else if (pOperator->IsType(OpType::Pow)) {
		pNode.reset(new Node_Pow());
	} else if (pOperator->IsType(OpType::Dot)) {
		pNode.reset(new Node_Dot());
	} else {
		Error::Issue(ErrorType::ValueError, "unsupported operator: %s", pOperator->GetName());
		return nullptr;
	}
	RefPtr<Node> pNodeLeft(CreateNode(exprEx.GetExprLeft(), symbolsInput));
	if (!pNodeLeft) return nullptr;
	RefPtr<Node> pNodeRight(CreateNode(exprEx.GetExprRight(), symbolsInput));
	if (!pNodeRight) return nullptr;
	pNodeLeft->Connect(pNode->GetConnectorSrcLeft());
	pNodeRight->Connect(pNode->GetConnectorSrcRight());
	return pNode.release();
}

Node* Trainer::CreateNodeGear(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput)
{
	RefPtr<Expr> pExpr(exprEx.GetExprRight().Reference());
	if (!pExpr->PrepareAndCompose(_composer)) return nullptr;
	RefPtr<Node_Gear> pNode(new Node_Gear(pExpr.release()));
	RefPtr<Node> pNodeChild(CreateNode(exprEx.GetExprLeft(), symbolsInput));
	if (!pNodeChild) return nullptr;
	pNodeChild->Connect(pNode->GetConnectorSrc());
	//_nodeOwner.push_back(pNodeChild.release());
	return pNode.release();
}

String Trainer::ToString(const StringStyle& ss) const
{
	return String().Format("Trainer");
}

//------------------------------------------------------------------------------
// TrainerList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TrainerOwner
//------------------------------------------------------------------------------
void TrainerOwner::Clear()
{
	for (Trainer* pTrainer : *this) Trainer::Delete(pTrainer);
	clear();
}

Gurax_EndModuleScope(ml)
