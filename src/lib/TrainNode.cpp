//==============================================================================
// TrainNode.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainNode
//------------------------------------------------------------------------------
bool TrainNode::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(output));
	symbols.push_back(Gurax_Symbol(type));
	return true;
}

Value* TrainNode::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
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
		//::printf("*%s\n", pNode->ToString().c_str());
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

//------------------------------------------------------------------------------
// TrainNode_SingleOut
//------------------------------------------------------------------------------
void TrainNode_SingleOut::Connect(Connector& connectorDst)
{
	connectorDst.SetNodeSrc(this);
	_pConnectorDst = &connectorDst;
}

bool TrainNode_SingleOut::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(nodeDst));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_SingleOut::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(nodeDst))) {
		return new Value_TrainNode(_pConnectorDst->GetNodeDst().Reference());
	}
	return TrainNode::DoGetProperty(pSymbol, attr);
}

//------------------------------------------------------------------------------
// TrainNode_Branch
//------------------------------------------------------------------------------
void TrainNode_Branch::Connect(Connector& connectorDst)
{
	connectorDst.SetNodeSrc(this);
	_connectorsDst.push_back(&connectorDst);
}

bool TrainNode_Branch::GatherMemberSymbol(SymbolList& symbols) const
{
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Branch::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	return TrainNode::DoGetProperty(pSymbol, attr);
}

//-----------------------------------------------------------------------------
// TrainNode_Head
//-----------------------------------------------------------------------------
const char* TrainNode_Head::GetTraitName() const
{
	return IsVariable()? "variable" : IsConstant()? "constant" : IsInput()? "input" : "unknown";
}

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
	//::printf("%s\n", GetExpr().ToString(StringStyle::Empty).c_str());
	if (_pArrayFwd.IsNull() || IsInput()) {
		RefPtr<Value> pValue(GetExpr().Eval(processor));
		if (Error::IsIssued()) return false;
		if (pValue->IsType(VTYPE_Number)) {
			_pArrayFwd.reset(Array::CreateScalar(Array::ElemType::Double, Value_Number::GetNumber<Double>(*pValue)));
		} else if (pValue->IsType(VTYPE_Complex)) {
			_pArrayFwd.reset(Array::CreateScalar(Array::ElemType::Complex, Value_Complex::GetComplex(*pValue)));
		} else if (pValue->IsType(VTYPE_Array)) {
			_pArrayFwd.reset(Value_Array::GetArray(*pValue).Reference());
		} else if (pValue->IsType(VTYPE_Gear)) {
		
		} else {
			Error::Issue(ErrorType::ValueError, "variable must be an array");
			return false;
		}
	}
	return true;
}

bool TrainNode_Head::EvalBackward(Processor& processor)
{
	if (_pTrainOptimizer) {
		if (!_pTrainOptimizer->Update(processor, _pArrayFwd, _pConnectorDst->GetArrayGrad())) return false;
	}
	return true;
}

bool TrainNode_Head::GatherMemberSymbol(SymbolList& symbols) const
{
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Head::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	return TrainNode::DoGetProperty(pSymbol, attr);
}

String TrainNode_Head::ToString(const StringStyle& ss) const
{
	return String().Format("%s(%s):%s", GetNodeTypeName(), GetTraitName(), GetExpr().ToString().c_str());
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

bool TrainNode_Bottom::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	symbols.push_back(Gurax_Symbol(nodeSrc));
	return TrainNode::GatherMemberSymbol(symbols);
}

Value* TrainNode_Bottom::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrc))) {
		return new Value_TrainNode(GetConnectorSrc().GetNodeSrc().Reference());
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

bool TrainNode_Unary::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	symbols.push_back(Gurax_Symbol(nodeSrc));
	return TrainNode_SingleOut::GatherMemberSymbol(symbols);
}

Value* TrainNode_Unary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrc))) {
		return new Value_TrainNode(GetConnectorSrc().GetNodeSrc().Reference());
	}
	return TrainNode_SingleOut::DoGetProperty(pSymbol, attr);
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
	if (GetConnectorSrc().GetNodeSrc().IsVulnerable()) {
		// inputGrad = -outputGrad
		if (!Array::Neg(GetConnectorSrc().GetArrayGradRefPtr(), _pConnectorDst->GetArrayGrad())) return false;
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

bool TrainNode_Binary::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(inputL));
	symbols.push_back(Gurax_Symbol(inputR));
	symbols.push_back(Gurax_Symbol(inputGradL));
	symbols.push_back(Gurax_Symbol(inputGradR));
	symbols.push_back(Gurax_Symbol(nodeSrcL));
	symbols.push_back(Gurax_Symbol(nodeSrcR));
	return TrainNode_SingleOut::GatherMemberSymbol(symbols);
}

Value* TrainNode_Binary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(inputL))) {
		return GetConnectorSrcLeft().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputR))) {
		return GetConnectorSrcRight().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGradL))) {
		return GetConnectorSrcLeft().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGradR))) {
		return GetConnectorSrcRight().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrcL))) {
		return new Value_TrainNode(GetConnectorSrcLeft().GetNodeSrc().Reference());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrcR))) {
		return new Value_TrainNode(GetConnectorSrcRight().GetNodeSrc().Reference());
	}
	return TrainNode_SingleOut::DoGetProperty(pSymbol, attr);
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
	const Array& arrayGrad = _pConnectorDst->GetArrayGrad();
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradL = outputGrad
		GetConnectorSrcLeft().SetArrayGrad(arrayGrad.Reference());
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradR = outputGrad
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
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradL = outputGrad
		GetConnectorSrcLeft().SetArrayGrad(_pConnectorDst->GetArrayGrad().Reference());
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradR = -outputGrad
		if (!Array::Neg(GetConnectorSrcRight().GetArrayGradRefPtr(), _pConnectorDst->GetArrayGrad())) return false;
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
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradL = outputGrad * inputR
		if (!Array::Mul(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradR = outputGrad * inputL
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), GetConnectorSrcLeft().GetArrayFwd())) return false;
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
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradL = outputGrad / inputR
		if (!Array::Div(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradR = -outputGrad * inputL / (inputR * inputR) = -outputGrad * output / inputR
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), GetArrayFwd())) return false;
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
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradL = outputGrad * inputR * inputL ** (inputR - 1) = outputGrad * output * inputR / inputL
		if (!Array::Mul(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), GetArrayFwd())) return false;
		if (!Array::Mul(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						GetConnectorSrcLeft().GetArrayGrad(), GetConnectorSrcRight().GetArrayFwd())) return false;
		if (!Array::Div(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						GetConnectorSrcLeft().GetArrayGrad(), GetConnectorSrcLeft().GetArrayFwd())) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradR = outputGrad * log(inputL) * inputL ** inputR = outputGrad * output * log(inputL)
		//if (!Array::Math_log(_pArrayWork, GetConnectorSrcLeft().GetArrayFwd())) return false;
		if (!Array::Mul(GetConnectorSrcRight().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), GetArrayFwd())) return false;
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
	if (GetConnectorSrcLeft().GetNodeSrc().IsVulnerable()) {
		// inputGradL = outputGrad |.| transpose(inputR)
		GetConnectorSrcRight().GetArrayFwd().Transpose(_pArrayFwdRightTrans);
		if (!Array::Dot(GetConnectorSrcLeft().GetArrayGradRefPtr(),
						_pConnectorDst->GetArrayGrad(), *_pArrayFwdRightTrans)) return false;
	}
	if (GetConnectorSrcRight().GetNodeSrc().IsVulnerable()) {
		// inputGradR = transpose(inputL) |.| outputGrad
		GetConnectorSrcLeft().GetArrayFwd().Transpose(_pArrayFwdLeftTrans);
		if (!Array::Dot(GetConnectorSrcRight().GetArrayGradRefPtr(),
						*_pArrayFwdLeftTrans, _pConnectorDst->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// TrainNode_Gear
//-----------------------------------------------------------------------------
bool TrainNode_Gear::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(gear));
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	return TrainNode_SingleOut::GatherMemberSymbol(symbols);
}

Value* TrainNode_Gear::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(gear))) {
		return new Value_Gear(GetGear().Reference());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	}
	return TrainNode_SingleOut::DoGetProperty(pSymbol, attr);
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
