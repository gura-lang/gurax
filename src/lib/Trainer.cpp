//==============================================================================
// Trainer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Trainer
//------------------------------------------------------------------------------
Trainer::Trainer(TrainOptimizer* pTrainOptimizer) : _pTrainOptimizer(pTrainOptimizer), _pNodeBottom(new TrainNode_Bottom())
{
}

bool Trainer::CreateFromExpr(const Expr& exprModel, const SymbolSet& inputs)
{
	RefPtr<TrainNode> pNode(CreateNode(exprModel, inputs));
	if (!pNode) return false;
	pNode->AddConnectorDst(GetNodeBottom().GetConnectorSrc());
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
	GetNodeBottom().Print(0);
}

TrainNode* Trainer::CreateNode(const Expr& expr, const SymbolSet& symbolsInput)
{
	if (expr.IsType<Expr_Block>()) {
		TrainNode *pNodeRtn = nullptr;
		const Expr_Block& exprEx = dynamic_cast<const Expr_Block&>(expr);
		const Expr* pExprEach = exprEx.GetExprElemFirst();
		if (!pExprEach) {
			// returns dummy node
			return nullptr;
		}
		for ( ; pExprEach->GetExprNext(); pExprEach = pExprEach->GetExprNext()) {
			RefPtr<TrainNode> pNode(CreateNode(*pExprEach, symbolsInput));
			if (!pNode) return nullptr;
			_nodeOwner.push_back(pNode.release());
		}
		RefPtr<TrainNode> pNode(CreateNode(*pExprEach, symbolsInput));
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
		RefPtr<TrainNode> pNode(CreateNode(exprEx.GetExprRight(), symbolsInput));
		if (!pNode) return nullptr;
		if (_nodeMap.find(pSymbol) != _nodeMap.end()) {
			Error::Issue(ErrorType::SyntaxError, "duplicated assignment to the identifier %s", pSymbol->GetName());
			return nullptr;
		}
		_nodeMap[pSymbol] = pNode.get();
		return pNode.release();
	} else if (expr.IsType<Expr_UnaryOp>()) {
		const Expr_UnaryOp& exprEx = dynamic_cast<const Expr_UnaryOp&>(expr);
		RefPtr<TrainNode> pNode(CreateNodeUnary(exprEx, symbolsInput));
		return pNode.release();
	} else if (expr.IsType<Expr_BinaryOp>()) {
		const Expr_BinaryOp& exprEx = dynamic_cast<const Expr_BinaryOp&>(expr);
		RefPtr<TrainNode> pNode(exprEx.GetOperator()->IsType(OpType::Gear)?
			CreateNodeGear(exprEx, symbolsInput) : CreateNodeBinary(exprEx, symbolsInput));
		return pNode.release();
	} else if (expr.IsType<Expr_Identifier>()) {
		const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(expr);
		const Symbol* pSymbol = exprEx.GetSymbol();
		TrainNode *pNodeFound = FindNode(pSymbol);
		if (pNodeFound != nullptr) return pNodeFound;
		TrainNode::Trait trait = TrainNode::Trait::Input;
		TrainOptimizer::Instance* pTrainOptimizer = nullptr;
		if (!symbolsInput.IsSet(pSymbol)) {
			trait = TrainNode::Trait::Variable;
			pTrainOptimizer = CreateOptimizerInstance();
		}
		RefPtr<TrainNode_Head> pNode(new TrainNode_Head(expr.Reference(), trait, pTrainOptimizer));
		return pNode.release();
	} else {
		TrainNode::Trait trait = TrainNode::Trait::Constant;
		TrainOptimizer::Instance* pTrainOptimizer = nullptr;
		if (!expr.IsType<Expr_Value>()) {
			trait = TrainNode::Trait::Variable;
			pTrainOptimizer = CreateOptimizerInstance();
		}
		RefPtr<TrainNode_Head> pNode(new TrainNode_Head(expr.Reference(), trait, pTrainOptimizer));
		return pNode.release();
	}
	return nullptr;
}

TrainNode* Trainer::CreateNodeUnary(const Expr_UnaryOp& exprEx, const SymbolSet& symbolsInput)
{
	const Operator* pOperator = exprEx.GetOperator();
	RefPtr<TrainNode_Unary> pNode;
	if (pOperator->IsType(OpType::Pos)) {
		//pNode.reset(new TrainNode_Pos());
	} else if (pOperator->IsType(OpType::Neg)) {
		pNode.reset(new TrainNode_Neg());
	} else {
		Error::Issue(ErrorType::ValueError, "unsupported operator: %s", pOperator->GetName());
		return nullptr;
	}
	RefPtr<TrainNode> pNodeChild(CreateNode(exprEx.GetExprChild(), symbolsInput));
	if (!pNodeChild) return nullptr;
	pNodeChild->AddConnectorDst(pNode->GetConnectorSrc());
	return pNode.release();
}

TrainNode* Trainer::CreateNodeBinary(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput)
{
	const Operator *pOperator = exprEx.GetOperator();
	RefPtr<TrainNode_Binary> pNode;
	if (pOperator->IsType(OpType::Add)) {
		pNode.reset(new TrainNode_Add());
	} else if (pOperator->IsType(OpType::Sub)) {
		pNode.reset(new TrainNode_Sub());
	} else if (pOperator->IsType(OpType::Mul)) {
		pNode.reset(new TrainNode_Mul());
	} else if (pOperator->IsType(OpType::Div)) {
		pNode.reset(new TrainNode_Div());
	} else if (pOperator->IsType(OpType::Pow)) {
		pNode.reset(new TrainNode_Pow());
	} else if (pOperator->IsType(OpType::Dot)) {
		pNode.reset(new TrainNode_Dot());
	} else {
		Error::Issue(ErrorType::ValueError, "unsupported operator: %s", pOperator->GetName());
		return nullptr;
	}
	RefPtr<TrainNode> pNodeLeft(CreateNode(exprEx.GetExprLeft(), symbolsInput));
	RefPtr<TrainNode> pNodeRight(CreateNode(exprEx.GetExprRight(), symbolsInput));
	if (!pNodeLeft || !pNodeRight) return nullptr;
	pNodeLeft->AddConnectorDst(pNode->GetConnectorSrcLeft());
	pNodeRight->AddConnectorDst(pNode->GetConnectorSrcRight());
	_nodeOwner.push_back(pNodeLeft.release());
	_nodeOwner.push_back(pNodeRight.release());
	return pNode.release();
}

TrainNode* Trainer::CreateNodeGear(const Expr_BinaryOp& exprEx, const SymbolSet& symbolsInput)
{
#if 0
	Value value = exprEx.GetRight()->Exec(env);
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
	TrainNode::Connector *pConnectorSrc = pNode->GetConnectorSrc();
	TrainNode *pNodeRtn = pNode.get();
	_nodeOwner.push_back(pNode.release());
	return (CreateNode(env, exprEx.GetLeft(), pConnectorSrc, symbolsInput) == nullptr)?
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
