//==============================================================================
// TrainNode.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainNode
//------------------------------------------------------------------------------
TrainNode::TrainNode(const char* nodeTypeName, Connector* pConnectorDst) : _nodeTypeName(nodeTypeName)
{
	if (pConnectorDst) {
		pConnectorDst->SetNodeSrc(this);
		_connectorsDst.push_back(pConnectorDst);
	}
}

bool TrainNode::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.push_back(Gurax_Symbol(output));
	symbols.push_back(Gurax_Symbol(type));
	return true;
}

Value* TrainNode::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(output))) {
		return new Value_Array(GetArrayFwd()->Reference());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(type))) {
		return new Value_Symbol(Symbol::Add(GetNodeTypeName()));
	}
	return Value::nil();
}

void TrainNode::Print(int indentLevel) const
{
	::printf("%-*s%s\n", indentLevel * 2, "", ToString(StringStyle::Empty).c_str());
}

String TrainNode::ToString(const StringStyle& ss) const
{
	return String().Format("TrainNode");
}

//------------------------------------------------------------------------------
// TrainNodeList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TrainNodeOwner
//------------------------------------------------------------------------------
void TrainNodeOwner::Clear()
{
	for (TrainNode* pTrainNode : *this) TrainNode::Delete(pTrainNode);
	clear();
}

//-----------------------------------------------------------------------------
// TrainNode_Head
//-----------------------------------------------------------------------------
bool TrainNode_Head::IsHead() { return true; }

bool TrainNode_Head::IsVulnerable() const
{
	return IsVariable();
}

void TrainNode_Head::Reset()
{
	//_pTrainOptimizer->Reset();
}

bool TrainNode_Head::EvalForward(Processor& processor)
{
	//::printf("TrainNode_Head::EvalForward(Processor& processor)\n");
	if (_pArrayFwd.IsNull() || IsInput()) {
		RefPtr<Value> pValue(_pExpr->Eval(processor));
		if (Error::IsIssued()) return false;
		if (pValue->IsType(VTYPE_Number)) {
			_pArrayFwd.reset(Array::CreateScalar(Array::ElemType::Double, Value_Number::GetNumber<Double>(*pValue)));
		} else if (pValue->IsType(VTYPE_Complex)) {
			_pArrayFwd.reset(Array::CreateScalar(Array::ElemType::Complex, Value_Complex::GetComplex(*pValue)));
		} else if (pValue->IsType(VTYPE_Array)) {
			_pArrayFwd.reset(Value_Array::GetArray(*pValue).Reference());
		//} else if (pValue->IsType(VTYPE_Gear)) {
		
		} else {
			Error::Issue(ErrorType::ValueError, "variable must be an array");
			return false;
		}
	}
	return true;
}

bool TrainNode_Head::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_pTrainOptimizer.get() != nullptr) {
		//if (!_pTrainOptimizer->Update(processor, _pArrayFwd, (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

bool TrainNode_Head::GatherMemberSymbol(SymbolList& symbols)
{
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Head::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Head::ToString() const
{
	String str;
	str += GetNodeTypeName();
	str += ":";
	str += _pExpr->ToString();
	return str;
}

void TrainNode_Head::Print(int indentLevel) const
{
	Print(indentLevel);
}

#if 0
//-----------------------------------------------------------------------------
// TrainNode_Bottom
//-----------------------------------------------------------------------------
bool TrainNode_Bottom::IsBottom() { return true; }

bool TrainNode_Bottom::IsVulnerable() const
{
	return _connectorSrc.GetNodeSrc()->IsVulnerable();
}

bool TrainNode_Bottom::EvalForward(Processor& processor)
{
	//::printf("NodeBottom::EvalForward(Processor& processor)\n");
	_pArrayFwd.reset(_connectorSrc.GetArrayFwd()->Reference());
	return true;
}

bool TrainNode_Bottom::EvalBackward(Processor& processor)
{
	// nothing to do
	return true;
}

bool TrainNode_Bottom::EvalBackwardTop(const Array *pArrayCorrect)
{
	_pArrayCorrect.reset(pArrayCorrect->Reference());
	if (_connectorSrc.GetNodeSrc()->IsVulnerable()) {
		if (!Array::Sub(env, _connectorSrc.GetArrayGradAutoPtr(),
						_connectorSrc.GetArrayFwd(), pArrayCorrect)) return false;
	}
	return true;
}

bool TrainNode_Bottom::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.insert(Gura_Symbol(input));
	symbols.insert(Gura_Symbol(inputgrad));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Bottom::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gura_Symbol(input))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrc.GetArrayFwd()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(inputgrad))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrc.GetArrayGrad()));
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Bottom::ToString() const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", _connectorSrc.GetArrayFwd(), _connectorSrc.GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Bottom::Print(int indentLevel) const
{
	Print(indentLevel);
	_connectorSrc.GetNodeSrc()->Print(indentLevel + 1);
}

//-----------------------------------------------------------------------------
// TrainNode_Unary
//-----------------------------------------------------------------------------
bool TrainNode_Unary::IsUnary() { return true; }

bool TrainNode_Unary::IsVulnerable() const
{
	return _connectorSrc.GetNodeSrc()->IsVulnerable();
}

bool TrainNode_Unary::EvalForward(Processor& processor)
{
	//::printf("NodeUnary::EvalForward(Processor& processor)\n");
	return Array::ApplyUnaryFunc(
		env, _unaryFuncPack, _pArrayFwd, GetConnectorSrc()->GetArrayFwd());
}

bool TrainNode_Unary::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.insert(Gura_Symbol(input));
	symbols.insert(Gura_Symbol(inputgrad));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Unary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gura_Symbol(input))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrc.GetArrayFwd()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(inputgrad))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrc.GetArrayGrad()));
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Unary::ToString() const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", _connectorSrc.GetArrayFwd(), _connectorSrc.GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Unary::Print(int indentLevel) const
{
	Print(indentLevel);
	_connectorSrc.GetNodeSrc()->Print(indentLevel + 1);
}

//-----------------------------------------------------------------------------
// TrainNode_Pos
//-----------------------------------------------------------------------------
bool TrainNode_Pos::EvalBackward(Processor& processor)
{
	if (_connectorSrc.GetNodeSrc()->IsVulnerable()) {
		ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
		if (ppConnectorDst == _connectorsDst.end()) return true;
		// grad_src = grad_out
		_connectorSrc.SetArrayGrad((*ppConnectorDst)->GetArrayGrad()->Reference());
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Neg
//-----------------------------------------------------------------------------
bool TrainNode_Neg::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_connectorSrc.GetNodeSrc()->IsVulnerable()) {
		// grad_src = -grad_out
		if (!Array::Neg(env, _connectorSrc.GetArrayGradAutoPtr(), (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Binary
//-----------------------------------------------------------------------------
bool TrainNode_Binary::IsBinary() { return true; }

bool TrainNode_Binary::IsVulnerable() const
{
	return
		_connectorSrcLeft.GetNodeSrc()->IsVulnerable() ||
		_connectorSrcRight.GetNodeSrc()->IsVulnerable();
}

bool TrainNode_Binary::EvalForward(Processor& processor)
{
	//::printf("NodeBinary::EvalForward(Processor& processor)\n");
	return Array::ApplyBinaryFunc(
			env, _binaryFuncPack, _pArrayFwd,
			GetConnectorSrcLeft()->GetArrayFwd(),
			GetConnectorSrcRight()->GetArrayFwd());
}

bool TrainNode_Binary::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.insert(Gura_Symbol(input_at_left));
	symbols.insert(Gura_Symbol(input_at_right));
	symbols.insert(Gura_Symbol(inputgrad_at_left));
	symbols.insert(Gura_Symbol(inputgrad_at_right));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Binary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gura_Symbol(input_at_left))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrcLeft.GetArrayFwd()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(input_at_right))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrcRight.GetArrayFwd()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(inputgrad_at_left))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrcLeft.GetArrayGrad()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(inputgrad_at_right))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrcRight.GetArrayGrad()));
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Binary::ToString() const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p][fwd:%p,grad:%p]",
			_connectorSrcLeft.GetArrayFwd(), _connectorSrcLeft.GetArrayGrad(),
			_connectorSrcRight.GetArrayFwd(), _connectorSrcRight.GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Binary::Print(int indentLevel) const
{
	Print(indentLevel);
	_connectorSrcLeft.GetNodeSrc()->Print(indentLevel + 1);
	_connectorSrcRight.GetNodeSrc()->Print(indentLevel + 1);
}

//-----------------------------------------------------------------------------
// TrainNode_Add
//-----------------------------------------------------------------------------
bool TrainNode_Add::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	const Array *pArrayGrad = (*ppConnectorDst)->GetArrayGrad();
	if (_connectorSrcLeft.GetNodeSrc()->IsVulnerable()) {
		// grad_left = grad_out
		_connectorSrcLeft.SetArrayGrad(pArrayGrad->Reference());
	}
	if (_connectorSrcRight.GetNodeSrc()->IsVulnerable()) {
		// grad_right = grad_out
		_connectorSrcRight.SetArrayGrad(pArrayGrad->Reference());
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Sub
//-----------------------------------------------------------------------------
bool TrainNode_Sub::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_connectorSrcLeft.GetNodeSrc()->IsVulnerable()) {
		// grad_left = grad_out
		_connectorSrcLeft.SetArrayGrad((*ppConnectorDst)->GetArrayGrad()->Reference());
	}
	if (_connectorSrcRight.GetNodeSrc()->IsVulnerable()) {
		// grad_right = -grad_out
		if (!Array::Neg(env, _connectorSrcRight.GetArrayGradAutoPtr(), (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Mul
//-----------------------------------------------------------------------------
bool TrainNode_Mul::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_connectorSrcLeft.GetNodeSrc()->IsVulnerable()) {
		// grad_left = grad_out * right
		if (!Array::Mul(env, _connectorSrcLeft.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _connectorSrcRight.GetArrayFwd())) return false;
	}
	if (_connectorSrcRight.GetNodeSrc()->IsVulnerable()) {
		// grad_right = grad_out * left
		if (!Array::Mul(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _connectorSrcLeft.GetArrayFwd())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Div
//-----------------------------------------------------------------------------
bool TrainNode_Div::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_connectorSrcLeft.GetNodeSrc()->IsVulnerable()) {
		// grad_left = grad_out / right
		if (!Array::Div(env, _connectorSrcLeft.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _connectorSrcRight.GetArrayFwd())) return false;
	}
	if (_connectorSrcRight.GetNodeSrc()->IsVulnerable()) {
		// grad_right = -grad_out * left / (right * right) = -grad_out * out / right
		if (!Array::Mul(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _pArrayFwd.get())) return false;
		if (!Array::Div(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						_connectorSrcRight.GetArrayGrad(), _connectorSrcRight.GetArrayFwd())) return false;
		if (!Array::Neg(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						_connectorSrcRight.GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Pow
//-----------------------------------------------------------------------------
bool TrainNode_Pow::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_connectorSrcLeft.GetNodeSrc()->IsVulnerable()) {
		// grad_left = grad_out * right * left ** (right - 1) = grad_out * out * right / left
		if (!Array::Mul(env, _connectorSrcLeft.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _pArrayFwd.get())) return false;
		if (!Array::Mul(env, _connectorSrcLeft.GetArrayGradAutoPtr(),
						_connectorSrcLeft.GetArrayGrad(), _connectorSrcRight.GetArrayFwd())) return false;
		if (!Array::Div(env, _connectorSrcLeft.GetArrayGradAutoPtr(),
						_connectorSrcLeft.GetArrayGrad(), _connectorSrcLeft.GetArrayFwd())) return false;
	}
	if (_connectorSrcRight.GetNodeSrc()->IsVulnerable()) {
		// grad_right = grad_out * log(left) * left ** right = grad_out * out * log(left)
		if (!Array::Math_log(env, _pArrayWork, _connectorSrcLeft.GetArrayFwd())) return false;
		if (!Array::Mul(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _pArrayFwd.get())) return false;
		if (!Array::Mul(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						_connectorSrcRight.GetArrayGrad(), _pArrayWork.get())) return false;
	}	
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Dot
//-----------------------------------------------------------------------------
bool TrainNode_Dot::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (_connectorSrcLeft.GetNodeSrc()->IsVulnerable()) {
		// grad_left = grad_out |.| trans(right)
		_connectorSrcRight.GetArrayFwd()->Transpose2d(_pArrayFwdRightTrans);
		if (!Array::Dot(env, _connectorSrcLeft.GetArrayGradAutoPtr(),
						(*ppConnectorDst)->GetArrayGrad(), _pArrayFwdRightTrans.get())) return false;
	}
	if (_connectorSrcRight.GetNodeSrc()->IsVulnerable()) {
		// grad_right = trans(left) |.| grad_out
		_connectorSrcLeft.GetArrayFwd()->Transpose2d(_pArrayFwdLeftTrans);
		if (!Array::Dot(env, _connectorSrcRight.GetArrayGradAutoPtr(),
						_pArrayFwdLeftTrans.get(), (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Gear
//-----------------------------------------------------------------------------
bool TrainNode_Gear::IsGear() { return true; }

bool TrainNode_Gear::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.insert(Gura_Symbol(gear));
	symbols.insert(Gura_Symbol(input));
	symbols.insert(Gura_Symbol(inputgrad));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Gear::DoGetProp(const Symbol *pSymbol,
								   const SymbolSet &attrs, bool &evaluatedFlag)
{
	if (pSymbol->IsIdentical(Gura_Symbol(gear))) {
		evaluatedFlag = true;
		return Value(_pGear->ToObject());
	} else if (pSymbol->IsIdentical(Gura_Symbol(input))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrc.GetArrayFwd()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(inputgrad))) {
		evaluatedFlag = true;
		return Array::ToValue(env, Array::Reference(_connectorSrc.GetArrayGrad()));
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Gear::ToString() const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", _connectorSrc.GetArrayFwd(), _connectorSrc.GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Gear::Print(int indentLevel) const
{
	Print(indentLevel);
	_connectorSrc.GetNodeSrc()->Print(indentLevel + 1);
}
#endif

}
