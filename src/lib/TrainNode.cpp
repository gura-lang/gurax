//==============================================================================
// TrainNode.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainNode
//------------------------------------------------------------------------------
void TrainNode::AddConnectorDst(Connector& connectorDst)
{
	connectorDst.SetNodeSrc(this);
	_connectorsDst.push_back(&connectorDst);
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
		return GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(type))) {
		return new Value_Symbol(Symbol::Add(GetNodeTypeName()));
	}
	return Value::nil();
}

void TrainNode::Print(Stream& stream, int indentLevel) const
{
	stream.Printf("%-*s%s\n", indentLevel * 2, "", ToString(StringStyle::Empty).c_str());
}

String TrainNode::ToString(const StringStyle& ss) const
{
	return String().Format("TrainNode");
}

//------------------------------------------------------------------------------
// TrainNodeList
//------------------------------------------------------------------------------
void TrainNodeList::Reset()
{
	for (TrainNode* pNode : *this)  pNode->Reset();
}

bool TrainNodeList::EvalForward(Processor& processor)
{
	for (TrainNode* pNode : *this) {
		if (!pNode->EvalForward(processor)) return false;
	}
	return true;
}

bool TrainNodeList::EvalBackward(Processor& processor)
{
	for (auto ppNode = rbegin(); ppNode != rend(); ppNode++) {
		TrainNode* pNode = *ppNode;
		if (!pNode->EvalBackward(processor)) return false;
	}
	return true;
}


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
bool TrainNode_Head::IsVulnerable() const
{
	return IsVariable();
}

void TrainNode_Head::Reset()
{
	_pTrainOptimizer->Reset();
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
	if (_pTrainOptimizer) {
		if (!_pTrainOptimizer->Update(processor, _pArrayFwd, (*ppConnectorDst)->GetArrayGrad())) return false;
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

String TrainNode_Head::ToString(const StringStyle& ss) const
{
	String str;
	str += GetNodeTypeName();
	str += ":";
	str += _pExpr->ToString();
	return str;
}

void TrainNode_Head::Print(Stream& stream, int indentLevel) const
{
	TrainNode::Print(stream, indentLevel);
}

//-----------------------------------------------------------------------------
// TrainNode_Bottom
//-----------------------------------------------------------------------------
bool TrainNode_Bottom::IsVulnerable() const
{
	return GetConnectorSrc().GetNodeSrc().IsVulnerable();
}

bool TrainNode_Bottom::EvalForward(Processor& processor)
{
	//::printf("NodeBottom::EvalForward(Processor& processor)\n");
	_pArrayFwd.reset(GetConnectorSrc().GetArrayFwd().Reference());
	return true;
}

bool TrainNode_Bottom::EvalBackward(Processor& processor)
{
	// nothing to do
	return true;
}

bool TrainNode_Bottom::EvalBackwardTop(Processor& processor, const Array& arrayCorrect)
{
	_pArrayCorrect.reset(arrayCorrect.Reference());
	if (GetConnectorSrc().GetNodeSrc().IsVulnerable()) {
		if (!Array::Sub(GetConnectorSrc().GetArrayGradRefPtr(), GetConnectorSrc().GetArrayFwd(), arrayCorrect)) return false;
	}
	return true;
}

bool TrainNode_Bottom::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Bottom::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Bottom::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", &GetConnectorSrc().GetArrayFwd(), &GetConnectorSrc().GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Bottom::Print(Stream& stream, int indentLevel) const
{
	TrainNode::Print(stream, indentLevel);
	GetConnectorSrc().GetNodeSrc().Print(stream, indentLevel + 1);
}

//-----------------------------------------------------------------------------
// TrainNode_Unary
//-----------------------------------------------------------------------------
bool TrainNode_Unary::IsVulnerable() const
{
	return GetConnectorSrc().GetNodeSrc().IsVulnerable();
}

bool TrainNode_Unary::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Unary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Unary::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", &GetConnectorSrc().GetArrayFwd(), &GetConnectorSrc().GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Unary::Print(Stream& stream, int indentLevel) const
{
	TrainNode::Print(stream, indentLevel);
	GetConnectorSrc().GetNodeSrc().Print(stream, indentLevel + 1);
}

//-----------------------------------------------------------------------------
// TrainNode_Neg
//-----------------------------------------------------------------------------
bool TrainNode_Neg::EvalForward(Processor& processor)
{
	return Array::Neg(_pArrayFwd, GetConnectorSrc().GetArrayFwd());
}

bool TrainNode_Neg::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (GetConnectorSrc().GetNodeSrc().IsVulnerable()) {
		// inputGrad = -outputGrad
		if (!Array::Neg(GetConnectorSrc().GetArrayGradRefPtr(), (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Binary
//-----------------------------------------------------------------------------
bool TrainNode_Binary::IsVulnerable() const
{
	return
		GetConnectorSrcLeft().GetNodeSrc().IsVulnerable() ||
		GetConnectorSrcRight().GetNodeSrc().IsVulnerable();
}

bool TrainNode_Binary::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.push_back(Gurax_Symbol(inputLeft));
	symbols.push_back(Gurax_Symbol(inputRight));
	symbols.push_back(Gurax_Symbol(inputGradLeft));
	symbols.push_back(Gurax_Symbol(inputGradRight));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Binary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(inputLeft))) {
		return GetConnectorSrcLeft().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputRight))) {
		return GetConnectorSrcRight().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGradLeft))) {
		return GetConnectorSrcLeft().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGradRight))) {
		return GetConnectorSrcRight().GetArrayGrad().ToValue();
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Binary::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p][fwd:%p,grad:%p]",
			&GetConnectorSrcLeft().GetArrayFwd(), &GetConnectorSrcLeft().GetArrayGrad(),
			&GetConnectorSrcRight().GetArrayFwd(), &GetConnectorSrcRight().GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Binary::Print(Stream& stream, int indentLevel) const
{
	TrainNode::Print(stream, indentLevel);
	GetConnectorSrcLeft().GetNodeSrc().Print(stream, indentLevel + 1);
	GetConnectorSrcRight().GetNodeSrc().Print(stream, indentLevel + 1);
}

//-----------------------------------------------------------------------------
// TrainNode_Add
//-----------------------------------------------------------------------------
bool TrainNode_Add::EvalForward(Processor& processor)
{
	return Array::Add(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool TrainNode_Add::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	const Array& arrayGrad = (*ppConnectorDst)->GetArrayGrad();
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradLeft = outputGrad
		GetConnectorSrcLeft().SetArrayGrad(arrayGrad.Reference());
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradRight = outputGrad
		GetConnectorSrcRight().SetArrayGrad(arrayGrad.Reference());
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Sub
//-----------------------------------------------------------------------------
bool TrainNode_Sub::EvalForward(Processor& processor)
{
	return Array::Sub(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool TrainNode_Sub::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradLeft = outputGrad
		GetConnectorSrcLeft().SetArrayGrad((*ppConnectorDst)->GetArrayGrad().Reference());
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradRight = -outputGrad
		if (!Array::Neg(GetConnectorSrcRight().GetArrayGradRefPtr(), (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Mul
//-----------------------------------------------------------------------------
bool TrainNode_Mul::EvalForward(Processor& processor)
{
	return Array::Mul(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool TrainNode_Mul::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradLeft = outputGrad * inputRight
		if (!Array::Mul(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradRight = outputGrad * inputLeft
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), GetConnectorSrcLeft().GetArrayFwd())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Div
//-----------------------------------------------------------------------------
bool TrainNode_Div::EvalForward(Processor& processor)
{
	return Array::Div(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool TrainNode_Div::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradLeft = outputGrad / inputRight
		if (!Array::Div(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradRight = -outputGrad * inputLeft / (inputRight * inputRight) = -outputGrad * output / inputRight
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), GetArrayFwd())) return false;
		if (!Array::Div(GetConnectorSrcRight().GetArrayGradRefPtr(),
						GetConnectorSrcRight().GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
		if (!Array::Neg(GetConnectorSrcRight().GetArrayGradRefPtr(),
						GetConnectorSrcRight().GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Pow
//-----------------------------------------------------------------------------
bool TrainNode_Pow::EvalForward(Processor& processor)
{
	return Array::Pow(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool TrainNode_Pow::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradLeft = outputGrad * inputRight * inputLeft ** (inputRight - 1) = outputGrad * output * inputRight / inputLeft
		if (!Array::Mul(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), GetArrayFwd())) return false;
		if (!Array::Mul(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						GetConnectorSrcLeft().GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
		if (!Array::Div(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						GetConnectorSrcLeft().GetArrayGrad(), GetConnectorSrcLeft().GetArrayFwd())) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradRight = outputGrad * log(inputLeft) * inputLeft ** inputRight = outputGrad * output * log(inputLeft)
		//if (!Array::Math_log(_pArrayWork, GetConnectorSrcLeft().GetArrayFwd())) return false;
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), GetArrayFwd())) return false;
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						GetConnectorSrcRight().GetArrayGrad(), *_pArrayWork)) return false;
	}	
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Dot
//-----------------------------------------------------------------------------
bool TrainNode_Dot::EvalForward(Processor& processor)
{
	return Array::Dot(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool TrainNode_Dot::EvalBackward(Processor& processor)
{
	ConnectorList::iterator ppConnectorDst = _connectorsDst.begin();
	if (ppConnectorDst == _connectorsDst.end()) return true;
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradLeft = outputGrad |.| transpose(inputRight)
		GetConnectorSrcRight().GetArrayFwd().Transpose(_pArrayFwdRightTrans);
		if (!Array::Dot(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						(*ppConnectorDst)->GetArrayGrad(), *_pArrayFwdRightTrans)) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradRight = transpose(inputLeft) |.| outputGrad
		GetConnectorSrcLeft().GetArrayFwd().Transpose(_pArrayFwdLeftTrans);
		if (!Array::Dot(GetConnectorSrcRight().GetArrayGradRefPtr(),
						*_pArrayFwdLeftTrans, (*ppConnectorDst)->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Gear
//-----------------------------------------------------------------------------
bool TrainNode_Gear::GatherMemberSymbol(SymbolList& symbols)
{
	symbols.push_back(Gurax_Symbol(gear));
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Gear::DoGetProperty(const Symbol* pSymbol, const Attribute& attr)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(gear))) {
		return new Value_Gear(GetGear().Reference());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Gear::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetNodeTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", &GetConnectorSrc().GetArrayFwd(), &GetConnectorSrc().GetArrayGrad());
	str += buff;
	return str;
}

void TrainNode_Gear::Print(Stream& stream, int indentLevel) const
{
	TrainNode::Print(stream, indentLevel);
	//GetConnectorSrc().GetNodeSrc().Print(Stream& stream, indentLevel + 1);
}

}
