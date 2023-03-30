//==============================================================================
// Trainer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Trainer
//------------------------------------------------------------------------------
bool Trainer::CreateFromExpr(const Expr& exprModel, const SymbolSet& inputs)
{
	return true;
}

void Trainer::Reset()
{
#if 0
	_nodeOwner.Reset(env);
#endif
}

bool Trainer::EvalForward()
{
#if 0
	return _nodeOwner.EvalForward(env) && _pNodeBottom->EvalForward(env);
#endif
	return false;
}

bool Trainer::EvalBackward(const Array& arrayCorrect)
{
#if 0
	return _pNodeBottom->EvalBackwardTop(env, pArrayCorrect) && _nodeOwner.EvalBackward(env);
#endif
	return false;
}

const Array* Trainer::GetResult() const
{
#if 0
	return _pNodeBottom->GetArrayFwd();
#endif
	return nullptr;
}

Double Trainer::CalcMeanSquareError(const Array& arrayCorrect) const
{
#if 0
	const Array *pArrayResult = GetResult();
	if (!Array::CheckSameShape(sig, pArrayResult, pArrayCorrect)) return 0;
	// not implemented yet
	return 0;
#endif
	return 0;
}

Double Trainer::CalcCrossEntropyError(const Array& arrayCorrect, Double epsilon) const
{
#if 0
	const Array *pArrayResult = GetResult();
	if (!Array::CheckSameShape(sig, pArrayResult, pArrayCorrect)) return 0;
	// not implemented yet
	return 0;
#endif
	return 0;
}

TrainNode* Trainer::FindNode(const Symbol* pSymbol) const
{
#if 0
	NodeMap::const_iterator iter = _nodeMap.find(pSymbol);
	return (iter == _nodeMap.end())? nullptr : iter->second;
#endif
	return nullptr;
}

void Trainer::Print() const
{
#if 0
	_pNodeBottom->Print(0);
#endif
}

TrainNode* Trainer::CreateNode(const Expr& expr, TrainNode::Connector& connector, const SymbolSet& symbolsInput)
{
#if 0
	if (pExpr->IsType(EXPRTYPE_Block)) {
		Node *pNodeRtn = nullptr;
		const Expr_Block *pExprEx = dynamic_cast<const Expr_Block *>(pExpr);
		const ExprOwner &exprOwner = pExprEx->GetExprOwner();
		foreach_const (ExprOwner, ppExprEach, exprOwner) {
			const Expr *pExprEach = *ppExprEach;
			Node::Connector *pConnectorEach = (ppExprEach + 1 == exprOwner.end())? pConnector : nullptr;
			pNodeRtn = CreateNode(env, pExprEach, pConnectorEach, symbolsInput);
			if (pNodeRtn == nullptr) return nullptr;
		}
		return pNodeRtn;
	}
	if (pExpr->IsType(EXPRTYPE_Assign)) {
		const Expr_Assign *pExprEx = dynamic_cast<const Expr_Assign *>(pExpr);
		if (pExprEx->GetOperatorToApply() != nullptr) {
			env.SetError(ERR_SyntaxError, "invalid assignment");
			return nullptr;
		}
		if (!pExprEx->GetLeft()->IsIdentifier()) {
			env.SetError(ERR_SyntaxError, "assignment to an identifier is only supported");
			return nullptr;
		}
		const Symbol *pSymbol = dynamic_cast<const Expr_Identifier *>(pExprEx->GetLeft())->GetSymbol();
		Node *pNode = CreateNode(env, pExprEx->GetRight(), pConnector, symbolsInput);
		if (pNode == nullptr) return nullptr;
		if (_nodeMap.find(pSymbol) != _nodeMap.end()) {
			env.SetError(ERR_SyntaxError, "duplicated assignment to the identifier %s", pSymbol->GetName());
			return nullptr;
		}
		_nodeMap[pSymbol] = pNode;
		return pNode;
	} else if (pExpr->IsType(EXPRTYPE_UnaryOp)) {
		const Expr_UnaryOp *pExprEx = dynamic_cast<const Expr_UnaryOp *>(pExpr);
		return CreateNodeUnary(env, pExprEx, pConnector, symbolsInput);
	} else if (pExpr->IsType(EXPRTYPE_BinaryOp)) {
		const Expr_BinaryOp *pExprEx = dynamic_cast<const Expr_BinaryOp *>(pExpr);
		return pExprEx->GetOperator()->IsOpType(OPTYPE_Gear)?
			CreateNodeGear(env, pExprEx, pConnector, symbolsInput) :
			CreateNodeBinary(env, pExprEx, pConnector, symbolsInput);
	} else if (pExpr->IsIdentifier()) {
		const Expr_Identifier *pExprEx = dynamic_cast<const Expr_Identifier *>(pExpr);
		const Symbol *pSymbol = pExprEx->GetSymbol();
		Node *pNodeFound = FindNode(pSymbol);
		if (pNodeFound != nullptr) return pNodeFound;
		Node::Trait trait = Node::TRAIT_Input;
		Optimizer::Instance *pOptimizerInst = nullptr;
		if (!symbolsInput.IsSet(pSymbol)) {
			trait = Node::TRAIT_Variable;
			pOptimizerInst = _pOptimizer->CreateInstance();
		}
		AutoPtr<NodeHead> pNode(new NodeHead(pConnector, Expr::Reference(pExpr), trait, pOptimizerInst));
		_nodeOwner.push_back(pNode.get());
		return pNode.release();
	} else {
		Node::Trait trait = Node::TRAIT_Constant;
		Optimizer::Instance *pOptimizerInst = nullptr;
		if (!pExpr->IsValue()) {
			trait = Node::TRAIT_Variable;
			pOptimizerInst = _pOptimizer->CreateInstance();
		}
		AutoPtr<NodeHead> pNode(new NodeHead(pConnector, Expr::Reference(pExpr), trait, pOptimizerInst));
		_nodeOwner.push_back(pNode.get());
		return pNode.release();
	}
#endif
	return nullptr;
}

TrainNode* Trainer::CreateNodeUnary(const Expr_UnaryOp& exprEx, TrainNode::Connector& connector, const SymbolSet& symbolsInput)
{
#if 0
	const Operator* pOperator = exprEx.GetOperator();
	RefPtr<TrainNode_Unary> pNode;
	if (pOperator->IsType(OpType::Pos)) {
		pNode.reset(new TrainNode_Pos(pConnector));
	} else if (pOperator->IsType(OpType::Neg)) {
		pNode.reset(new TrainNode_Neg(pConnector));
	} else {
		Error::Issue(ErrorType::ValueError, "unsupported operator: %s", pOperator->GetName());
		return nullptr;
	}
	Node::Connector *pConnectorSrc = pNode->GetConnectorSrc();
	Node *pNodeRtn = pNode.get();
	_nodeOwner.push_back(pNode.release());
	return
		(CreateNode(env, pExprEx->GetChild(), pConnectorSrc, symbolsInput) == nullptr)?
		nullptr : pNodeRtn;
#endif
	return nullptr;
}

TrainNode* Trainer::CreateNodeBinary(const Expr_BinaryOp& exprEx, TrainNode::Connector& connector, const SymbolSet& symbolsInput)
{
#if 0
	const Operator *pOperator = pExprEx->GetOperator();
	AutoPtr<NodeBinary> pNode;
	if (pOperator->IsOpType(OPTYPE_Add)) {
		pNode.reset(new NodeBinary_Add(pConnector));
	} else if (pOperator->IsOpType(OPTYPE_Sub)) {
		pNode.reset(new NodeBinary_Sub(pConnector));
	} else if (pOperator->IsOpType(OPTYPE_Mul)) {
		pNode.reset(new NodeBinary_Mul(pConnector));
	} else if (pOperator->IsOpType(OPTYPE_Div)) {
		pNode.reset(new NodeBinary_Div(pConnector));
	} else if (pOperator->IsOpType(OPTYPE_Pow)) {
		pNode.reset(new NodeBinary_Pow(pConnector));
	} else if (pOperator->IsOpType(OPTYPE_Dot)) {
		pNode.reset(new NodeBinary_Dot(pConnector));
	} else {
		env.SetError(ERR_ValueError, "unsupported operator: %s", pOperator->GetName());
		return nullptr;
	}
	Node::Connector *pConnectorSrcLeft = pNode->GetConnectorSrcLeft();
	Node::Connector *pConnectorSrcRight = pNode->GetConnectorSrcRight();
	Node *pNodeRtn = pNode.get();
	_nodeOwner.push_back(pNode.release());
	return
		(CreateNode(env, pExprEx->GetLeft(), pConnectorSrcLeft, symbolsInput) == nullptr) ||
		(CreateNode(env, pExprEx->GetRight(), pConnectorSrcRight, symbolsInput) == nullptr)?
		nullptr : pNodeRtn;
#endif
	return nullptr;
}

TrainNode* Trainer::CreateNodeGear(const Expr_BinaryOp& exprEx, TrainNode::Connector& connector, const SymbolSet& symbolsInput)
{
#if 0
	Value value = pExprEx->GetRight()->Exec(env);
	if (env.IsSignalled()) return nullptr;
	if (!value.IsInstanceOf(VTYPE_gear)) {
		env.SetError(ERR_ValueError, "gear instance is expected as a right-side operand of a gear operator");
		return nullptr;
	}
	NodeGearCreatorMap::iterator iter = _nodeGearCreatorMap.find(value.GetValueType());
	if (iter == _nodeGearCreatorMap.end()) {
		env.SetError(ERR_ValueError, "unsupported gear type: %s", value.MakeValueTypeName().c_str());
		return nullptr;
	}
	const NodeGear::Creator *pCreator = iter->second;
	AutoPtr<NodeGear> pNode(pCreator->Create(value, pConnector, this));
	Node::Connector *pConnectorSrc = pNode->GetConnectorSrc();
	Node *pNodeRtn = pNode.get();
	_nodeOwner.push_back(pNode.release());
	return (CreateNode(env, pExprEx->GetLeft(), pConnectorSrc, symbolsInput) == nullptr)?
		nullptr : pNodeRtn;
#endif
	return nullptr;
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

}
