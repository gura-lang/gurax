//==============================================================================
// Node.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
bool Node::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(output));
	symbols.push_back(Gurax_Symbol(outputGrad));
	symbols.push_back(Gurax_Symbol(type));
	return true;
}

Value* Node::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(output))) {
		return GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(typeName))) {
		return new Value_String(GetTypeName());
	}
	return nullptr;
}

void Node::Print(Stream& stream, int indentLevel) const
{
	stream.Printf("%-*s%s\n", indentLevel * 2, "", ToString(StringStyle::Empty).c_str());
}

String Node::ToString(const StringStyle& ss) const
{
	return String().Format("Node");
}

//------------------------------------------------------------------------------
// NodeList
//------------------------------------------------------------------------------
void NodeList::Reset()
{
	for (Node* pNode : *this)  pNode->Reset();
}

bool NodeList::EvalForward(Processor& processor)
{
	for (Node* pNode : *this) {
		if (!pNode->EvalForward(processor)) return false;
	}
	return true;
}

bool NodeList::EvalBackward(Processor& processor)
{
	for (auto ppNode = rbegin(); ppNode != rend(); ppNode++) {
		Node* pNode = *ppNode;
		//::printf("*%s\n", pNode->ToString().c_str());
		if (!pNode->EvalBackward(processor)) return false;
	}
	return true;
}


//------------------------------------------------------------------------------
// NodeOwner
//------------------------------------------------------------------------------
void NodeOwner::Clear()
{
	for (Node* pNode : *this) Node::Delete(pNode);
	clear();
}

//------------------------------------------------------------------------------
// Node_SingleOut
//------------------------------------------------------------------------------
void Node_SingleOut::Connect(Connector& connectorDst)
{
	connectorDst.SetNodeSrc(this);
	_pConnectorDst = &connectorDst;
}

bool Node_SingleOut::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(nodeDst));
	symbols.push_back(Gurax_Symbol(outputGrad));
	return Node::GatherMemberSymbol(symbols);
}

Value* Node_SingleOut::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(nodeDst))) {
		return new Value_Node(_pConnectorDst->GetNodeDst().Reference());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(outputGrad))) {
		return _pConnectorDst->GetArrayGrad().ToValue();
	}
	return Node::DoGetProperty(pSymbol, attr);
}

//------------------------------------------------------------------------------
// Node_Branch
//------------------------------------------------------------------------------
void Node_Branch::Connect(Connector& connectorDst)
{
	connectorDst.SetNodeSrc(this);
	_connectorsDst.push_back(&connectorDst);
}

bool Node_Branch::EvalForward(Processor& processor)
{
	return true;
}

bool Node_Branch::EvalBackward(Processor& processor)
{
	auto ppConnector = _connectorsDst.begin();
	const Connector* pConnector = *ppConnector;
	_pArrayGrad.reset(pConnector->GetArrayGrad().Reference());
	ppConnector++;
	for ( ; ppConnector != _connectorsDst.end(); ppConnector++) {
		const Connector* pConnector = *ppConnector;
		Array::Add(_pArrayGrad, *_pArrayGrad, pConnector->GetArrayGrad());
	}
	return true;
}

bool Node_Branch::GatherMemberSymbol(SymbolList& symbols) const
{
	return Node::GatherMemberSymbol(symbols);
}

Value* Node_Branch::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	return Node::DoGetProperty(pSymbol, attr);
}

//-----------------------------------------------------------------------------
// Node_Head
//-----------------------------------------------------------------------------
const char* Node_Head::GetTraitName() const
{
	return IsVariable()? "variable" : IsConstant()? "constant" : IsInput()? "input" : "unknown";
}

bool Node_Head::IsVulnerable() const
{
	return IsVariable();
}

void Node_Head::Reset()
{
	_pOptimizerInst->Reset();
}

bool Node_Head::EvalForward(Processor& processor)
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
		} else {
			Error::Issue(ErrorType::ValueError, "variable must be an array");
			return false;
		}
	}
	return true;
}

bool Node_Head::EvalBackward(Processor& processor)
{
	if (_pOptimizerInst) {
		if (!_pOptimizerInst->Update(processor, _pArrayFwd, _pConnectorDst->GetArrayGrad())) return false;
	}
	return true;
}

bool Node_Head::GatherMemberSymbol(SymbolList& symbols) const
{
	return Node::GatherMemberSymbol(symbols);
}

Value* Node_Head::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	return Node::DoGetProperty(pSymbol, attr);
}

String Node_Head::ToString(const StringStyle& ss) const
{
	return String().Format("%s(%s):%s", GetTypeName().c_str(), GetTraitName(), GetExpr().ToString().c_str());
}

void Node_Head::Print(Stream& stream, int indentLevel) const
{
	Node::Print(stream, indentLevel);
}

//-----------------------------------------------------------------------------
// Node_Bottom
//-----------------------------------------------------------------------------
bool Node_Bottom::IsVulnerable() const
{
	return GetConnectorSrc().GetNodeSrc().IsVulnerable();
}

bool Node_Bottom::EvalForward(Processor& processor)
{
	//::printf("NodeBottom::EvalForward(Processor& processor)\n");
	_pArrayFwd.reset(GetConnectorSrc().GetArrayFwd().Reference());
	return true;
}

bool Node_Bottom::EvalBackward(Processor& processor)
{
	// nothing to do
	return true;
}

bool Node_Bottom::EvalBackwardTop(Processor& processor, const Array& arrayCorrect)
{
	_pArrayCorrect.reset(arrayCorrect.Reference());
	if (GetConnectorSrc().GetNodeSrc().IsVulnerable()) {
		if (!Array::Sub(GetConnectorSrc().GetArrayGradRefPtr(), GetConnectorSrc().GetArrayFwd(), arrayCorrect)) return false;
	}
	return true;
}

bool Node_Bottom::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	symbols.push_back(Gurax_Symbol(nodeSrc));
	return Node::GatherMemberSymbol(symbols);
}

Value* Node_Bottom::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrc))) {
		return new Value_Node(GetConnectorSrc().GetNodeSrc().Reference());
	}
	return Node::DoGetProperty(pSymbol, attr);
}

String Node_Bottom::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", &GetConnectorSrc().GetArrayFwd(), &GetConnectorSrc().GetArrayGrad());
	str += buff;
	return str;
}

void Node_Bottom::Print(Stream& stream, int indentLevel) const
{
	Node::Print(stream, indentLevel);
	GetConnectorSrc().GetNodeSrc().Print(stream, indentLevel + 1);
}

//-----------------------------------------------------------------------------
// Node_Unary
//-----------------------------------------------------------------------------
bool Node_Unary::IsVulnerable() const
{
	return GetConnectorSrc().GetNodeSrc().IsVulnerable();
}

bool Node_Unary::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(input));
	symbols.push_back(Gurax_Symbol(inputGrad));
	symbols.push_back(Gurax_Symbol(nodeSrc));
	return Node_SingleOut::GatherMemberSymbol(symbols);
}

Value* Node_Unary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(input))) {
		return GetConnectorSrc().GetArrayFwd().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(inputGrad))) {
		return GetConnectorSrc().GetArrayGrad().ToValue();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrc))) {
		return new Value_Node(GetConnectorSrc().GetNodeSrc().Reference());
	}
	return Node_SingleOut::DoGetProperty(pSymbol, attr);
}

String Node_Unary::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p]", &GetConnectorSrc().GetArrayFwd(), &GetConnectorSrc().GetArrayGrad());
	str += buff;
	return str;
}

void Node_Unary::Print(Stream& stream, int indentLevel) const
{
	Node::Print(stream, indentLevel);
	GetConnectorSrc().GetNodeSrc().Print(stream, indentLevel + 1);
}

//-----------------------------------------------------------------------------
// Node_Neg
//-----------------------------------------------------------------------------
bool Node_Neg::EvalForward(Processor& processor)
{
	return Array::Neg(_pArrayFwd, GetConnectorSrc().GetArrayFwd());
}

bool Node_Neg::EvalBackward(Processor& processor)
{
	if (GetConnectorSrc().GetNodeSrc().IsVulnerable()) {
		// inputGrad = -outputGrad
		if (!Array::Neg(GetConnectorSrc().GetArrayGradRefPtr(), _pConnectorDst->GetArrayGrad())) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Node_Binary
//-----------------------------------------------------------------------------
bool Node_Binary::IsVulnerable() const
{
	return
		GetConnectorSrcLeft().GetNodeSrc().IsVulnerable() ||
		GetConnectorSrcRight().GetNodeSrc().IsVulnerable();
}

bool Node_Binary::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(inputL));
	symbols.push_back(Gurax_Symbol(inputR));
	symbols.push_back(Gurax_Symbol(inputGradL));
	symbols.push_back(Gurax_Symbol(inputGradR));
	symbols.push_back(Gurax_Symbol(nodeSrcL));
	symbols.push_back(Gurax_Symbol(nodeSrcR));
	return Node_SingleOut::GatherMemberSymbol(symbols);
}

Value* Node_Binary::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
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
		return new Value_Node(GetConnectorSrcLeft().GetNodeSrc().Reference());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(nodeSrcR))) {
		return new Value_Node(GetConnectorSrcRight().GetNodeSrc().Reference());
	}
	return Node_SingleOut::DoGetProperty(pSymbol, attr);
}

String Node_Binary::ToString(const StringStyle& ss) const
{
	String str;
	char buff[128];
	str += GetTypeName();
	::sprintf(buff, " [fwd:%p,grad:%p][fwd:%p,grad:%p]",
			&GetConnectorSrcLeft().GetArrayFwd(), &GetConnectorSrcLeft().GetArrayGrad(),
			&GetConnectorSrcRight().GetArrayFwd(), &GetConnectorSrcRight().GetArrayGrad());
	str += buff;
	return str;
}

void Node_Binary::Print(Stream& stream, int indentLevel) const
{
	Node::Print(stream, indentLevel);
	GetConnectorSrcLeft().GetNodeSrc().Print(stream, indentLevel + 1);
	GetConnectorSrcRight().GetNodeSrc().Print(stream, indentLevel + 1);
}

//-----------------------------------------------------------------------------
// Node_Add
//-----------------------------------------------------------------------------
bool Node_Add::EvalForward(Processor& processor)
{
	return Array::Add(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool Node_Add::EvalBackward(Processor& processor)
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
// Node_Sub
//-----------------------------------------------------------------------------
bool Node_Sub::EvalForward(Processor& processor)
{
	return Array::Sub(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool Node_Sub::EvalBackward(Processor& processor)
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
// Node_Mul
//-----------------------------------------------------------------------------
bool Node_Mul::EvalForward(Processor& processor)
{
	return Array::Mul(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool Node_Mul::EvalBackward(Processor& processor)
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
// Node_Div
//-----------------------------------------------------------------------------
bool Node_Div::EvalForward(Processor& processor)
{
	return Array::Div(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool Node_Div::EvalBackward(Processor& processor)
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
// Node_Pow
//-----------------------------------------------------------------------------
bool Node_Pow::EvalForward(Processor& processor)
{
	return Array::Pow(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool Node_Pow::EvalBackward(Processor& processor)
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
// Node_Dot
//-----------------------------------------------------------------------------
bool Node_Dot::EvalForward(Processor& processor)
{
	return Array::Dot(_pArrayFwd, GetConnectorSrcLeft().GetArrayFwd(), GetConnectorSrcRight().GetArrayFwd());
}

bool Node_Dot::EvalBackward(Processor& processor)
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
// Node_Gear
//-----------------------------------------------------------------------------
bool Node_Gear::EvalForward(Processor& processor)
{
	if (!_pGear) {
		RefPtr<Value> pValue(_pExprRight->Eval(processor));
		if (Error::IsIssued()) return false;
		if (pValue->IsInstanceOf(VTYPE_Gear)) {
			_pGear.reset(Value_Gear::GetGear(*pValue).Reference());
		} else {
			Error::Issue(ErrorType::ValueError, "variable must be a Gear instance");
			return false;
		}
	}
	return _pGear->EvalForward(processor, _pArrayFwd, GetConnectorSrc().GetArrayFwd());
}

bool Node_Gear::EvalBackward(Processor& processor)
{
	if (!GetConnectorSrc().GetNodeSrc().IsVulnerable()) return true;
	return _pGear->EvalBackward(processor, GetConnectorSrc().GetArrayGradRefPtr(), _pConnectorDst->GetArrayGrad());
}

bool Node_Gear::GatherMemberSymbol(SymbolList& symbols) const
{
	symbols.push_back(Gurax_Symbol(gear));
	return Node_Unary::GatherMemberSymbol(symbols);
}

Value* Node_Gear::DoGetProperty(const Symbol* pSymbol, const Attribute& attr) const
{
	if (pSymbol->IsIdentical(Gurax_Symbol(gear))) {
		return _pGear? new Value_Gear(_pGear->Reference()) : Value::nil();
	}
	return Node_Unary::DoGetProperty(pSymbol, attr);
}

Gurax_EndModuleScope(ml)