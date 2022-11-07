//==============================================================================
// Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------
RefPtr<Expr> Expr::Empty;

void Expr::Bootup()
{
	Empty.reset(new Expr_Empty());
}

void Expr::ComposeOrNil(Composer& composer)
{
	PUnit* pPUnitMarked = composer.PeekPUnitCont();
	Compose(composer);
	if (Error::IsIssued()) return;
	if (pPUnitMarked == composer.PeekPUnitCont()) { // when nothing has been yielded
		composer.Add_Value(Value::nil(), *this);
	}
}

Iterator* Expr::EachParam() const
{
	return Iterator::Empty->Reference();
}

Iterator* Expr::EachElem() const
{
	return Iterator::Empty->Reference();
}

Iterator* Expr::EachPUnit() const
{
	const PUnit* pPUnit = GetPUnitFirst();
	const PUnit* pPUnitSentinel = GetPUnitEnd();
	if (pPUnit && pPUnit->GetPUnitSentinel()) {
		pPUnitSentinel = pPUnit->GetPUnitSentinel();
		pPUnit = pPUnit->GetPUnitAdjacent();	// skip SequenceBegin/ArgSlotBegin/ArgSlotNamed
	}
	return new Iterator_PUnit(pPUnit, pPUnitSentinel);
}

int Expr::CalcIndentLevel() const
{
	int indentLevel = 0;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), indentLevel++) ;
	return indentLevel;
}

bool Expr::Prepare()
{
	Visitor_Prepare visitor;
	return Traverse(visitor);
}

SymbolList Expr::GatherArgSymbols() const
{
	SymbolList symbolList;
	Visitor_GatherArgSymbols visitor(symbolList);
	const_cast<Expr*>(this)->Traverse(visitor);
	return symbolList;
}

Value* Expr::Eval(Processor& processor) const
{
	if (!GetPUnitFirst()) return Value::nil();
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitFirst()));
	processor.ClearEvent();
	return pValue.release();
}

Value* Expr::Eval(Processor& processor, Event& event) const
{
	if (!GetPUnitFirst()) return Value::nil();
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitFirst()));
	event = processor.GetEvent();
	processor.ClearEvent();
	return pValue.release();
}

Value* Expr::Eval(Processor& processor, Argument& argument) const
{
	if (!GetPUnitFirst()) return Value::nil();
	if (!argument.CompleteFeedValue(processor)) return Value::nil();
	Frame& frameCur = processor.GetFrameCur();
	argument.AssignToFrame(processor.PushFrame<Frame_Block>(), frameCur);
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitFirst()));
	processor.PopFrame();
	processor.ClearEvent();
	return pValue.release();
}

Value* Expr::Eval(Processor& processor, Argument& argument, Event& event) const
{
	if (!GetPUnitFirst()) return Value::nil();
	if (!argument.CompleteFeedValue(processor)) return Value::nil();
	Frame& frameCur = processor.GetFrameCur();
	argument.AssignToFrame(processor.PushFrame<Frame_Block>(), frameCur);
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitFirst()));
	event = processor.GetEvent();
	processor.PopFrame();
	processor.ClearEvent();
	return pValue.release();
}

size_t Expr::CountSequence(const Expr* pExpr)
{
	size_t nExprs = 0;
	for ( ; pExpr; pExpr = pExpr->GetExprNext(), nExprs++) ;
	return nExprs;
}

void Expr::ComposeSequence(Composer& composer, Expr* pExpr) const
{
	PUnit* pPUnitMarked = composer.PeekPUnitCont();
	if (pExpr) {
		pExpr->Compose(composer);
		if (Error::IsIssued()) return;
		pExpr = pExpr->GetExprNext();
	}
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		composer.FlushDiscard();
		pExpr->Compose(composer);
		if (Error::IsIssued()) return;
	}
	if (pPUnitMarked == composer.PeekPUnitCont()) { // when nothing has been yielded
		composer.Add_Value(Value::nil(), *this);
	}
	// [Value]
}

void Expr::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	Error::Issue(ErrorType::SyntaxError, "invalid class definition");
}

void Expr::ComposeWithinLister(Composer& composer)
{
	ComposeOrNil(composer);														// [List Any]
	composer.Add_ListElem(0, false, false, *this);								// [List]
}

void Expr::ComposeWithinTuple(Composer& composer)
{
	ComposeOrNil(composer);														// [Tuple Any]
	composer.Add_TupleElem(0, false, *this);									// [Tuple]
}

void Expr::ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeWithinAssignment(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeWithinAssignmentInClass(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeWithinArgSlot(Composer& composer)
{
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	SetPUnitFirst(pPUnitOfArgSlot);
	composer.Add_ArgSlotBegin(*this);											// [Argument]
	Compose(composer);															// [Argument Any]
	if (Error::IsIssued()) return;
	pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
	composer.Add_ArgSlotEnd(*this);												// [Argument]
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	SetPUnitEnd(composer.PeekPUnitCont());
}

bool Expr::IsPureAssign() const
{
	return IsType<Expr_Assign>() && !InspectOperator();
}

String Expr::TextizeExprList(const StringStyle& ss, const Expr* pExpr, int indentLevel)
{
	String str;
	String indent = ss.MakeIndent(indentLevel);
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		str += indent;
		str += pExpr->ToString(ss, indentLevel);
		str += '\n';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr::Visitor_GatherArgSymbols
//------------------------------------------------------------------------------
bool Expr::Visitor_GatherArgSymbols::Visit(Expr* pExpr)
{
	if (pExpr->IsType<Expr_Identifier>()) {
		const Symbol* pSymbol = dynamic_cast<Expr_Identifier*>(pExpr)->GetSymbol();
		if (*pSymbol->GetName() == '$' && !_symbolList.DoesContain(pSymbol)) {
			_symbolList.push_back(pSymbol);
		}
	}
	return true;
}

//------------------------------------------------------------------------------
// ExprList
//------------------------------------------------------------------------------
const ExprList ExprList::Empty;

bool ExprList::Traverse(Expr::Visitor& visitor)
{
	for (Expr* pExpr : *this) {
		if (!pExpr->Traverse(visitor)) return false;
	}
	return true;
}

void ExprList::Compose(Composer& composer)
{
	auto ppExpr = begin();
	if (ppExpr != end()) {
		Expr* pExpr = *ppExpr++;
		pExpr->Compose(composer);
	}
	while (ppExpr != end()) {
		Expr* pExpr = *ppExpr++;
		composer.FlushDiscard();
		pExpr->Compose(composer);
		if (Error::IsIssued()) return;
	}
	// [Value]
}

void ExprList::SetExprParent(const Expr* pExprParent)
{
	for (Expr* pExpr : *this) pExpr->SetExprParent(pExprParent);
}

//------------------------------------------------------------------------------
// ExprOwner
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ExprLink
//------------------------------------------------------------------------------
size_t ExprLink::CountSequence() const
{
	size_t cnt = 0;
	for (const Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext(), cnt++) ;
	return cnt;
}

void ExprLink::SetExprParent(const Expr* pExprParent)
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->SetExprParent(pExprParent);
	}
}

bool ExprLink::Traverse(Expr::Visitor& visitor)
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (!pExpr->Traverse(visitor)) return false;
	}
	return true;
}

void ExprLink::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) const
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeWithinClass(composer, pDottedSymbol.Reference(), publicFlag);
		if (Error::IsIssued()) return;
		composer.FlushDiscard();
	}
}

void ExprLink::ComposeWithinArgSlot(Composer& composer) const
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeWithinArgSlot(composer);
		if (Error::IsIssued()) return;
	}
}

Iterator* ExprLink::CreateIterator() const
{
	return new Iterator_ExprLink(Reference());
}

//------------------------------------------------------------------------------
// Expr_Empty
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Empty::typeInfo(TypeId::Empty, "Empty");

//------------------------------------------------------------------------------
// Expr_Node
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Unary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Binary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Collector
//------------------------------------------------------------------------------
void Expr_Collector::AddExprElem(Expr* pExprElem)
{
	pExprElem->SetExprParent(this);
	_pExprLinkElem->AddExpr(pExprElem);
}

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
void Expr_Composite::AddExprParam(Expr* pExprParam)
{
	pExprParam->SetExprParent(this);
	_pExprLinkParam->AddExpr(pExprParam);
}

//------------------------------------------------------------------------------
// Expr_Member
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Member::typeInfo(TypeId::Member, "Member");

void Expr_Member::Compose(Composer& composer)
{
	GetExprTarget().ComposeOrNil(composer);										// [Target]
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		composer.Add_MemberGet_Normal(
					GetSymbol(), GetAttr().Reference(), *this);					// [Member] or [Prop]
		break;
	}
	case MemberMode::MapAlong: {
		composer.Add_MemberGet_MapAlong(
					GetSymbol(), GetAttr().Reference(), *this);					// [Member] or [Prop]
		break;
	}
	case MemberMode::MapToList: {
		composer.Add_MemberGet_MapToList(
					GetSymbol(), GetAttr().Reference(), *this);					// [Member] or [Prop]
		break;
	}
	case MemberMode::MapToIter: {
		composer.Add_MemberGet_MapToIter(
					GetSymbol(), GetAttr().Reference(), *this);					// [Member] or [Prop]
		break;
	}
	default: {
		break;
	}
	}
}

void Expr_Member::ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in lister assigment");
		return;
	}
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		GetExprTarget().ComposeOrNil(composer);									// [Assigned Target]
		composer.Add_MemberSet_Normal(GetSymbol(), GetAttr().Reference(), true, *this); // [Assigned]
		composer.FlushDiscard();
		break;
	}
	case MemberMode::MapAlong: case MemberMode::MapToList: case MemberMode::MapToIter: {
		Error::Issue_UnimplementedOperation();
		break;
	}
	default:
		break;
	}
}

void Expr_Member::ComposeWithinAssignment(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	GetExprTarget().ComposeOrNil(composer);										// [Target]
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		exprAssigned.ComposeOrNil(composer);									// [Target Assigned]
		if (pOp) {
			composer.Add_MemberOpApply_Normal(
				GetSymbol(), GetAttr().Reference(), pOp, false, *this);			// [Assigned]
		} else {
			composer.Add_MemberSet_Normal(
				GetSymbol(), GetAttr().Reference(), false, *this);				// [Assigned]
		}
		break;
	}
	case MemberMode::MapAlong: {
		bool mapAssignedFlag = true;
		exprAssigned.ComposeOrNil(composer);									// [Target Assigned]
		if (pOp) {
			Error::Issue_UnimplementedOperation();
			//composer.Add_MemberOpApply_Map(GetSymbol(),
			//	GetAttr().Reference(), pOp, mapAssignedFlag, false, *this);		// [Assigned]
		} else {
			composer.Add_MemberSet_Map(GetSymbol(),
				GetAttr().Reference(), mapAssignedFlag, false, *this);			// [Assigned]
		}
		break;
	}
	case MemberMode::MapToList: case MemberMode::MapToIter: {
		bool mapAssignedFlag = false;
		exprAssigned.ComposeOrNil(composer);									// [Target Assigned]
		if (pOp) {
			Error::Issue_UnimplementedOperation();
			//composer.Add_MemberOpApply_Map(GetSymbol(),
			//	GetAttr().Reference(), pOp, mapAssignedFlag, false, *this);		// [Assigned]
		} else {
			composer.Add_MemberSet_Map(GetSymbol(),
				GetAttr().Reference(), mapAssignedFlag, false, *this);			// [Assigned]
		}
		break;
	}
	default:
		break;
	}
}

const Symbol* Expr_Member::GetMemberModeAsSymbol() const
{
	return
		(_memberMode == MemberMode::Normal)? Gurax_Symbol(normal) :
		(_memberMode == MemberMode::MapAlong)? Gurax_Symbol(mapAlong) :
		(_memberMode == MemberMode::MapToIter)? Gurax_Symbol(mapToIter) :
		(_memberMode == MemberMode::MapToList)? Gurax_Symbol(mapToList) :
		Symbol::Empty;
}

String Expr_Member::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	const Expr& exprTarget = GetExprTarget();
	str += exprTarget.ToString(ss, indentLevel);
	str += MemberModeToSymbol(GetMemberMode())->GetName();
	str += GetSymbol()->ToString();
	str += GetAttr().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Value : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Value::typeInfo(TypeId::Value, "Value");

void Expr_Value::Compose(Composer& composer)
{
	composer.Add_Value(GetValue().Reference(), *this);							// [Value]
}

void Expr_Value::ComposeWithinArgSlot(Composer& composer)
{
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	SetPUnitFirst(pPUnitOfArgSlot);
	composer.Add_ArgSlot_Value(GetValue().Reference(), *this);					// [Argument]
	Compose(composer);
	if (Error::IsIssued()) return;
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	SetPUnitEnd(composer.PeekPUnitCont());
}

String Expr_Value::ToString(const StringStyle& ss, int indentLevel) const
{
	return HasSource()? GetSourceSTL() : GetValue().ToString();
}

Value* Expr_Value::InspectValue() const
{
	return GetValue().Reference();
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo(TypeId::Identifier, "Identifier");

DeclCallable* Expr_Identifier::RetrieveDeclCallable() const
{
	RefPtr<Value> pValue(Basement::Inst.GetFrame().Retrieve(GetSymbol()));
	return pValue? DeclCallable::Reference(pValue->GetDeclCallable()) : nullptr;
}

void Expr_Identifier::Compose(Composer& composer)
{
	const Symbol* pSymbol = GetSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(__file__))) {
		composer.Add_Value(new Value_String(GetPathNameSrc()), *this);			// [Value]
	} else if (pSymbol->IsIdentical(Gurax_Symbol(__line__))) {
		composer.Add_Value(new Value_Number(GetLineNoTop()), *this);			// [Value]
	} else {
		RefPtr<Value> pValue(Basement::Inst.GetFrame().Retrieve(pSymbol));
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = dynamic_cast<Value_Function&>(*pValue).GetFunction();
			if (func.IsTypeStatement()) {
				RefPtr<Expr> pExprParent(LockExprParent());
				if (!pExprParent || pExprParent->IsShortCircuitOperator() || pExprParent->IsCollector()) {
					RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
					pExprCaller->SetExprCar(new Expr_Identifier(pSymbol));
					func.Compose(composer, *pExprCaller);
					return;
				}
			}
		}
		composer.Add_Lookup(pSymbol, *this);									// [Value]
	}
}

void Expr_Identifier::ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in lister assigment");
		return;
	}
	bool externFlag = false;
	if (!ParseAttr(&externFlag)) return;
	composer.Add_AssignToSymbol(GetSymbol(), externFlag, *this);				// [Assigned]
	composer.FlushDiscard();
}

void Expr_Identifier::ComposeWithinAssignment(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	bool externFlag = false;
	if (!ParseAttr(&externFlag)) return;
	if (pOp) {
		composer.Add_Lookup(GetSymbol(), *this);								// [Any]
		exprAssigned.ComposeOrNil(composer);									// [Any Right]
		composer.Add_BinaryOp(pOp, *this);										// [Assigned]
	} else {
		exprAssigned.ComposeOrNil(composer);									// [Assigned]
	}
	composer.Add_AssignToSymbol(GetSymbol(), externFlag, *this);				// [Assigned]
}

void Expr_Identifier::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	PropSlot::Flags flags = publicFlag? PropSlot::Flag::Public : 0;
	composer.Add_AssignPropSlot(GetSymbol(), pDottedSymbol.release(), flags, GetAttr(), false, *this);
	composer.FlushDiscard();													// [VType]
}
	
void Expr_Identifier::ComposeWithinAssignmentInClass(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in property assigment");
		return;
	}
	PropSlot::Flags flags = publicFlag? PropSlot::Flag::Public : 0;
	exprAssigned.ComposeOrNil(composer);										// [VType Value]
	composer.Add_AssignPropSlot(GetSymbol(), pDottedSymbol.release(), flags, GetAttr(), true, *this);
	composer.FlushDiscard();													// [VType]
}

void Expr_Identifier::ComposeWithinArgSlot(Composer& composer)
{
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	SetPUnitFirst(pPUnitOfArgSlot);
	if (GetSymbol()->IsIdentical(Gurax_Symbol(__file__))) {
		composer.Add_ArgSlot_Value(new Value_String(GetPathNameSrc()), *this);	// [Argument]
	} else if (GetSymbol()->IsIdentical(Gurax_Symbol(__line__))) {
		composer.Add_ArgSlot_Value(new Value_Number(GetLineNoTop()), *this);	// [Argument]
	} else {
		composer.Add_ArgSlot_Lookup(GetSymbol(), *this);						// [Argument]
	}
	Compose(composer);															// [Argument]
	if (Error::IsIssued()) return;
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	SetPUnitEnd(composer.PeekPUnitCont());
}

String Expr_Identifier::ToString(const StringStyle& ss, const char* strInsert) const
{
	String str;
	str += GetSymbol()->ToString();
	str += strInsert;
	str += GetAttr().ToString(ss);
	return str;
}

size_t Expr_Identifier::CalcHash() const
{
	return GetSymbol()->CalcHash();
}

bool Expr_Identifier::IsEqualTo(const Expr& expr) const
{
	if (!expr.IsType<Expr_Identifier>()) return false;
	return GetSymbol()->IsIdentical(dynamic_cast<const Expr_Identifier&>(expr).GetSymbol());
}

bool Expr_Identifier::IsLessThan(const Expr& expr) const
{
	return expr.IsType<Expr_Identifier>()?
		(::strcmp(GetSymbol()->GetName(), dynamic_cast<const Expr_Identifier&>(expr).GetSymbol()->GetName()) < 0) :
		GetTypeId() < expr.GetTypeId();
}

bool Expr_Identifier::ParseAttr(bool* pExternFlag) const
{
	*pExternFlag = false;
	for (const Symbol* pSymbol : GetAttr().GetSymbols()) {
		if (pSymbol->IsIdentical(Gurax_Symbol(extern_))) {
			*pExternFlag = true;
		} else {
			Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid attribute for assignment");
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
// Expr_String : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_String::typeInfo(TypeId::String, "String");

void Expr_String::Compose(Composer& composer)
{
	RefPtr<Value> pValue(new Value_String(GetSegmentReferable().Reference()));
	composer.Add_Value(pValue.release(), *this);								// [Value]
}

void Expr_String::ComposeWithinArgSlot(Composer& composer)
{
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	SetPUnitFirst(pPUnitOfArgSlot);
	RefPtr<Value> pValue(new Value_String(GetSegmentReferable().Reference()));
	composer.Add_ArgSlot_Value(pValue.release(), *this);						// [Argument]
	Compose(composer);
	if (Error::IsIssued()) return;
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	SetPUnitEnd(composer.PeekPUnitCont());
}

String Expr_String::ToString(const StringStyle& ss, int indentLevel) const
{
	String str = GetSegmentSTL();
	str = ss.IsDQuoteString()? str.Enquote('"') : str.EnquoteAuto();
	return str;
}

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Suffixed::typeInfo(TypeId::Suffixed, "Suffixed");

void Expr_Suffixed::Compose(Composer& composer)
{
	const SuffixMgr* pSuffixMgr = Basement::Inst.LookupSuffixMgr(GetMode(), GetSymbol());
	if (pSuffixMgr) {
		pSuffixMgr->Compose(composer, GetSegmentReferable(), this);
	} else {
		composer.Add_Suffixed(GetSegmentReferable().Reference(), GetMode(), GetSymbol(), *this);
	}
}

String Expr_Suffixed::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	if (GetMode() == SuffixMgr::Mode::Binary) str += "b";
	str += (GetMode() == SuffixMgr::Mode::Number)? GetSegmentSTL() : GetSegmentSTL().EnquoteAuto();
	str += GetSymbol()->GetName();
	return str;
}

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo(TypeId::UnaryOp, "UnaryOp");

void Expr_UnaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		GetOperator()->ComposeUnary(composer, *this);							// [Result]
	} else {
		GetExprChild().ComposeOrNil(composer);									// [Any]
		composer.Add_UnaryOp(GetOperator(), *this);								// [Result]
	}
}

void Expr_UnaryOp::ComposeWithinLister(Composer& composer)
{
	if (GetOperator()->IsType(OpType::PostMul)) {
		GetExprChild().ComposeOrNil(composer);									// [List Any]
		composer.Add_ListElem(0, false, true, *this);							// [List]
	} else {
		Expr_Unary::ComposeWithinLister(composer);								// [List]
	}
}

void Expr_UnaryOp::ComposeWithinTuple(Composer& composer)
{
	if (GetOperator()->IsType(OpType::PostMul)) {
		GetExprChild().ComposeOrNil(composer);									// [Tuple Any]
		composer.Add_TupleElem(0, true, *this);									// [Tuple]
	} else {
		Expr_Unary::ComposeWithinTuple(composer);								// [Tuple]
	}
}

void Expr_UnaryOp::ComposeWithinArgSlot(Composer& composer)
{
	if (GetOperator()->IsType(OpType::PostMul)) {
		PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
		SetPUnitFirst(pPUnitOfArgSlot);
		composer.Add_ArgSlotBegin(*this);										// [Argument]
		GetExprChild().ComposeOrNil(composer);									// [Argument Any]
		pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_ArgSlotEnd_Expand(*this);									// [Argument]
		pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
		SetPUnitEnd(composer.PeekPUnitCont());
	} else {
		Expr_Unary::ComposeWithinArgSlot(composer);
	}
}

String Expr_UnaryOp::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::Unary: {
		bool requireParFlag = GetExprChild().IsType<Expr_UnaryOp>() || GetExprChild().IsType<Expr_BinaryOp>();
		str += GetOperator()->GetSymbol()->GetName();
		if (requireParFlag) str += '(';
		str += GetExprChild().ToString(ss, indentLevel);
		if (requireParFlag) str += ')';
		break;
	}
	case OpStyle::UnaryPost: {
		if (GetExprChild().IsType<Expr_Identifier>()) {
			const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(GetExprChild());
			str += exprEx.ToString(ss, GetOperator()->GetSymbol()->GetName());
		} else if (GetExprChild().IsType<Expr_Indexer>()) {
			const Expr_Indexer& exprEx = dynamic_cast<const Expr_Indexer&>(GetExprChild());
			str += exprEx.ToString(ss, GetOperator()->GetSymbol()->GetName());
		} else {
			bool requireParFlag = GetExprChild().IsType<Expr_UnaryOp>() || GetExprChild().IsType<Expr_BinaryOp>();
			if (requireParFlag) str += '(';
			str += GetExprChild().ToString(ss, indentLevel);
			if (requireParFlag) str += ')';
			str += GetOperator()->GetSymbol()->GetName();
		}
		break;
	}
	case OpStyle::MathUnary: {
		str += GetOperator()->GetSymbol()->GetName();
		str += '(';
		str += GetExprChild().ToString(ss, indentLevel);
		str += ')';
		break;
	}
	default:
		break;
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_BinaryOp : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_BinaryOp::typeInfo(TypeId::BinaryOp, "BinaryOp");

void Expr_BinaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		GetOperator()->ComposeBinary(composer, *this);
	} else {
		GetExprLeft().ComposeOrNil(composer);									// [Left]
		GetExprRight().ComposeOrNil(composer);									// [Left Right]
		composer.Add_BinaryOp(GetOperator(), *this);							// [Result]
	}
}

void Expr_BinaryOp::ComposeWithinLister(Composer& composer)
{
	if (GetOperator()->IsType(OpType::Seq)) {
		GetExprLeft().ComposeOrNil(composer);									// [List Left]
		GetExprRight().ComposeOrNil(composer);									// [List Left Right]
		composer.Add_BinaryOp(GetOperator(), *this);							// [List Result]
		composer.Add_ListElem(0, false, true, *this);							// [List]
	} else {
		Expr_Binary::ComposeWithinLister(composer);								// [List]
	}
}

void Expr_BinaryOp::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	if (GetOperator()->IsType(OpType::As)) {
		pDottedSymbol.reset(DottedSymbol::CreateFromExpr(GetExprRight()));
		if (!pDottedSymbol) return;
		GetExprLeft().ComposeWithinClass(composer, pDottedSymbol.release(), publicFlag);
	} else {
		Expr_Binary::ComposeWithinLister(composer);								// [List]
	}
}

void Expr_BinaryOp::ComposeWithinArgSlot(Composer& composer)
{
	Expr_Binary::ComposeWithinArgSlot(composer);
}

void Expr_BinaryOp::ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	if (GetOperator()->IsType(OpType::As)) {
		pDottedSymbol.reset(DottedSymbol::CreateFromExpr(GetExprRight()));
		if (!pDottedSymbol) return;
		GetExprLeft().ComposeWithinAssignment(composer, exprAssigned, pOp, pDottedSymbol.release());
	} else {
		Expr_Binary::ComposeWithinAssignment(composer, exprAssigned, pOp, pDottedSymbol.release());
	}
}

void Expr_BinaryOp::ComposeWithinAssignmentInClass(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	if (GetOperator()->IsType(OpType::As)) {
		pDottedSymbol.reset(DottedSymbol::CreateFromExpr(GetExprRight()));
		if (!pDottedSymbol) return;
		GetExprLeft().ComposeWithinAssignmentInClass(composer, exprAssigned, pOp, pDottedSymbol.release(), publicFlag);
	} else {
		Expr_Binary::ComposeWithinAssignmentInClass(composer, exprAssigned, pOp, pDottedSymbol.release(), publicFlag);
	}
}

String Expr_BinaryOp::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::Binary: {
		do {
			bool needParenFlag =
				GetExprLeft().IsType<Expr_BinaryOp>() || GetExprLeft().IsType<Expr_UnaryOp>();
			if (needParenFlag) str += '(';
			str += GetExprLeft().ToString(ss, indentLevel);
			if (needParenFlag) str += ')';
		} while (0);
		if (!ss.IsCram()) str += ' ';
		str += GetOperator()->GetSymbol()->GetName();
		if (!ss.IsCram()) str += ' ';
		do {
			bool needParenFlag =
				GetExprRight().IsType<Expr_BinaryOp>() || GetExprRight().IsType<Expr_UnaryOp>();
			if (needParenFlag) str += '(';
			str += GetExprRight().ToString(ss, indentLevel);
			if (needParenFlag) str += ')';
		} while (0);
		break;
	}
	case OpStyle::MathBinary: {
		str += GetOperator()->GetSymbol()->GetName();
		str += '(';
		str += GetExprLeft().ToString(ss, indentLevel);
		str += ss.GetComma();
		if (!ss.IsCram()) str += ' ';
		str += GetExprRight().ToString(ss, indentLevel);
		str += ')';
		break;
	}
	default:
		break;
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Assign : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Assign::typeInfo(TypeId::Assign, "Assign");

bool Expr_Assign::DoPrepare()
{
	if (GetExprLeft().IsType<Expr_Caller>()) {
		Expr_Caller& exprEx = dynamic_cast<Expr_Caller&>(GetExprLeft());
		return exprEx.PrepareDeclCallable();
	}
	return true;
}

bool Expr_Assign::IsDeclArgWithDefault(Expr_Binary** ppExpr) const
{
	if (GetOperator()) return false;
	*ppExpr = const_cast<Expr_Assign*>(this);
	return true;
}

void Expr_Assign::Compose(Composer& composer)
{
	GetExprLeft().ComposeWithinAssignment(composer, GetExprRight(), GetOperator(), nullptr); // [Assigned]
}

void Expr_Assign::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	GetExprLeft().ComposeWithinAssignmentInClass(
		composer, GetExprRight(), GetOperator(), pDottedSymbol.release(), publicFlag); // [Assigned]
}

void Expr_Assign::ComposeWithinArgSlot(Composer& composer)
{
	const Expr* pExprLeft = &GetExprLeft();
	if (pExprLeft->IsBinaryOp(OpType::As)) {
		pExprLeft = &dynamic_cast<const Expr_BinaryOp*>(pExprLeft)->GetExprLeft();
	}
	if (GetOperator() || !pExprLeft->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::ArgumentError, *this,
						 "invalid declaration of named argument");
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(pExprLeft)->GetSymbol();
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	GetExprRight().SetPUnitFirst(pPUnitOfArgSlot);
	composer.Add_NamedArgSlotBegin(pSymbol, GetExprRight().Reference(), *this);	// [Argument ArgSlot]
	GetExprRight().ComposeOrNil(composer);										// [Argument ArgSlot Assigned]
	pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
	composer.Add_NamedArgSlotEnd(*this);										// [Argument]
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	GetExprRight().SetPUnitEnd(composer.PeekPUnitCont());
}

String Expr_Assign::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	str += GetExprLeft().ToString(ss, indentLevel);
	if (!ss.IsCram()) str += ' ';
	if (GetOperator()) str += GetOperator()->GetSymbol()->GetName();
	str += '=';
	if (!ss.IsCram()) str += ' ';
	str += GetExprRight().ToString(ss, indentLevel);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Root : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Root::typeInfo(TypeId::Root, "Root");

void Expr_Root::Compose(Composer& composer)
{
	SetPUnitFirst(composer.PeekPUnitCont());
	//PUnit* pPUnitOfSequenceBegin = PeekPUnitCont();
	//Add_SequenceBegin(expr);													// []
	ComposeSequence(composer, GetExprElemFirst());								// [Any]
	//pPUnitOfSequenceBegin->SetPUnitSentinel(PeekPUnitCont());
	composer.Add_Return(*this);
	composer.Add_Terminate();
	SetPUnitEnd(composer.PeekPUnitCont());
}

String Expr_Root::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	if (ss.IsMultiLine()) {
		String indent = ss.MakeIndent(indentLevel);
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != GetExprElemFirst()) str += indent;
			str += pExpr->ToString(ss, indentLevel);
			str += '\n';
		}
	} else {
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ';';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss, indentLevel);
		}
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Block::typeInfo(TypeId::Block, "Block");

bool Expr_Block::DoPrepare()
{
	return HasCallerAsParent()? PrepareDeclCallable() : true;
}

void Expr_Block::Compose(Composer& composer)
{
	if (!HasCallerAsParent() && HasExprParam()) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(*this);
		SetPUnitSubFirst(composer.PeekPUnitCont());
		PUnit* pPUnitSequence = composer.PeekPUnitCont();
		composer.Add_SequenceBegin(*this);										// []
		GetExprLinkParam().ComposeWithinArgSlot(composer);						// []
		pPUnitSequence->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_Return(*this);												// [Any]
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	}
	ComposeSequence(composer, GetExprElemFirst());								// [Any]
}

void Expr_Block::ComposeWithinLister(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, *this);										// [List List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeWithinLister(composer);									// [List List]
	}	
	composer.Add_ListElem(0, false, false, *this);								// [List]
}

bool Expr_Block::HasCallerAsParent() const
{
	RefPtr<Expr> pExprParent(LockExprParent());
	return pExprParent && pExprParent->IsType<Expr_Caller>();
}

Value* Expr_Block::EvalEasy(Processor& processor, RefPtr<Value> pValueArg) const
{
	RefPtr<Argument> pArgument(Argument::CreateForBlockCall(processor, *this));
	ArgFeeder args(*pArgument, processor.GetFrameCur());
	if (!args.FeedValue(pValueArg.release())) return Value::nil();
	return Eval(processor, *pArgument);
}

Value* Expr_Block::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2) const
{
	RefPtr<Argument> pArgument(Argument::CreateForBlockCall(processor, *this));
	ArgFeeder args(*pArgument, processor.GetFrameCur());
	if (!args.FeedValue(pValueArg1.release())) return Value::nil();
	if (!args.FeedValue(pValueArg2.release())) return Value::nil();
	return Eval(processor, *pArgument);
}

String Expr_Block::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	if (ss.IsMultiLine()) {
		String indent = ss.MakeIndent(indentLevel);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += '{';
		if (HasExprParam()) {
			str += '|';
			const Expr* pExprFirst = GetExprParamFirst();
			for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
				if (pExpr != pExprFirst) {
					str += ',';
					if (!ss.IsCram()) str += ' ';
				}
				str += pExpr->ToString(ss, indentLevel);
			}
			str += '|';
		}
		str += '\n';
		str += TextizeExprList(ss, GetExprElemFirst(), indentLevel + 1);
		//for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		//	str += indentDown;
		//	str += pExpr->ToString(ss, indentLevel + 1);
		//	str += '\n';
		//}
		str += indent;
		str += "}";
	} else {
		str += '{';
		if (HasExprParam()) {
			str += '|';
			const Expr* pExprFirst = GetExprParamFirst();
			for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
				if (pExpr != pExprFirst) {
					str += ',';
					if (!ss.IsCram()) str += ' ';
				}
				str += pExpr->ToString(ss, indentLevel);
			}
			str += '|';
			if (!ss.IsCram() && HasExprElem()) str += ' ';
		}
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss, indentLevel);
		}
		str += '}';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Tuple : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Tuple::typeInfo(TypeId::Tuple, "Tuple");

void Expr_Tuple::Compose(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateTuple(nExprs, *this);									// [Tuple]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeWithinTuple(composer);
		//pExpr->ComposeOrNil(composer);										// [Tuple Elem]
		//composer.Add_TupleElem(0, false, *this);								// [Tuple]
	}	
}

String Expr_Tuple::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	if (GetExprLinkElem().CountSequence() == 1) {
		str += '(';
		str += GetExprLinkElem().GetExprFirst()->ToString(ss, indentLevel);
		str += ",)";
	} else if (ss.IsMultiLine()) {
		String indent = ss.MakeIndent(indentLevel);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += "(\n";
		str += TextizeExprList(ss, GetExprElemFirst(), indentLevel + 1);
		//for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		//	str += indentDown;
		//	str += pExpr->ToString(ss, indentLevel + 1);
		//	str += '\n';
		//}
		str += indent;
		str += ")";
	} else {
		str += '(';
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss, indentLevel);
		}
		str += ')';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Lister::typeInfo(TypeId::Lister, "Lister");

void Expr_Lister::Compose(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, *this);										// [List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeWithinLister(composer);									// [List]
	}
}

void Expr_Lister::ComposeWithinAssignment(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	exprAssigned.ComposeOrNil(composer);										// [Assigned]
	composer.Add_GenIterator_ForLister(*this);									// [Assigned Iterator]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		composer.Add_EvalIterator(0, true, *this);								// [Assigned Iterator Value]
		pExpr->ComposeWithinValueAssignment(composer, pOp, pDottedSymbol.release());
																				// [Assigned Iterator]
		if (Error::IsIssued()) return;
	}
	composer.Add_DiscardValue(*this);											// [Assigned]
}

String Expr_Lister::ToString(const StringStyle& ss, int indentLevel) const
{
	String str;
	if (ss.IsMultiLine()) {
		String indent = ss.MakeIndent(indentLevel);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += "[\n";
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			str += indentDown;
			str += pExpr->ToString(ss, indentLevel + 1);
			str += '\n';
		}
		str += indent;
		str += "]";
	} else {
		str += '[';
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss, indentLevel);
		}
		str += ']';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Indexer::typeInfo(TypeId::Indexer, "Indexer");

void Expr_Indexer::Compose(Composer& composer)
{
	GetExprCar().ComposeOrNil(composer);										// [Car]
	size_t nExprs = GetExprLinkParam().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, *this);					// [Index(Car)]
	for (Expr* pExprParam = GetExprParamFirst(); pExprParam; pExprParam = pExprParam->GetExprNext()) {
		pExprParam->ComposeOrNil(composer);										// [Index(Car) Param]
		composer.Add_FeedIndex(*pExprParam);									// [Index(Car)]
	}
	composer.Add_IndexGet(*this);												// [Elems]
}

void Expr_Indexer::ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	GetExprCar().ComposeOrNil(composer);										// [Elems Car]
	size_t nExprs = GetExprLinkParam().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, *this);					// [Elems Index(Car)]
	for (Expr* pExprParam = GetExprParamFirst(); pExprParam; pExprParam = pExprParam->GetExprNext()) {
		pExprParam->ComposeOrNil(composer);										// [Elems Index(Car) Param]
		composer.Add_FeedIndex(*pExprParam);									// [Elems Index(Car)]
	}
	if (pOp) {
		Error::Issue_UnimplementedOperation();
		return;
		//composer.Add_IndexOpApply(pOp, true, *this);							// [Rtn]
	} else {
		composer.Add_IndexSet(true, *this);										// [Elems]
	}
	composer.FlushDiscard();
}

void Expr_Indexer::ComposeWithinAssignment(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	GetExprCar().ComposeOrNil(composer);										// [Car]
	size_t nExprs = GetExprLinkParam().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, *this);					// [Index(Car)]
	for (Expr* pExprParam = GetExprParamFirst(); pExprParam; pExprParam = pExprParam->GetExprNext()) {
		pExprParam->ComposeOrNil(composer);										// [Index(Car) Param]
		composer.Add_FeedIndex(*pExprParam);									// [Index(Car)]
	}
	exprAssigned.ComposeOrNil(composer);										// [Index(Car) Elems]
	if (pOp) {
		composer.Add_IndexOpApply(pOp, false, *this);							// [Rtn]
	} else {
		composer.Add_IndexSet(false, *this);									// [Elems]
	}
}

void Expr_Indexer::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	if (!GetExprCar().IsType<Expr_Identifier>() || HasExprParam()) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid format of property declaration");
		return;
	}
	PropSlot::Flags flags = PropSlot::Flag::ListVar | (publicFlag? PropSlot::Flag::Public : 0);
	const Expr_Identifier& exprCar = dynamic_cast<Expr_Identifier&>(GetExprCar());
	composer.Add_AssignPropSlot(exprCar.GetSymbol(), pDottedSymbol.release(), flags, GetAttr(), false, *this);
	composer.FlushDiscard();													// [VType]
}

void Expr_Indexer::ComposeWithinAssignmentInClass(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in property assigment");
		return;
	}
	if (!GetExprCar().IsType<Expr_Identifier>() || HasExprParam()) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid format of property declaration");
		return;
	}
	PropSlot::Flags flags = PropSlot::Flag::ListVar | (publicFlag? PropSlot::Flag::Public : 0);
	const Expr_Identifier& exprCar = dynamic_cast<Expr_Identifier&>(GetExprCar());
	exprAssigned.ComposeOrNil(composer);										// [VType Value]
	composer.Add_AssignPropSlot(exprCar.GetSymbol(), pDottedSymbol.release(), flags, GetAttr(), true, *this);
	composer.FlushDiscard();													// [VType]
}

String Expr_Indexer::ToString(const StringStyle& ss, const char* strInsert, int indentLevel) const
{
	String str;
	str += _pExprCar->ToString(ss, indentLevel);
	str += '[';
	const Expr* pExprParamFirst = GetExprParamFirst();
	for (const Expr* pExprParam = pExprParamFirst; pExprParam; pExprParam = pExprParam->GetExprNext()) {
		if (pExprParam != pExprParamFirst) {
			str += ',';
			if (!ss.IsCram()) str += ' ';
		}
		str += pExprParam->ToString(ss, indentLevel);
	}
	str += ']';
	str += strInsert;
	str += GetAttr().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Caller::typeInfo(TypeId::Caller, "Caller");

void Expr_Caller::Compose(Composer& composer)
{
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromExpr(GetExprCar()));
	if (pDottedSymbol) {
		RefPtr<Value> pValue(Basement::Inst.GetFrame().Retrieve(*pDottedSymbol));
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = Value_Function::GetFunction(*pValue);
			if (func.IsTypeStatement()) {
				func.Compose(composer, *this);									// [Result]
				return;
			}
		}
	}
	GetExprCar().ComposeOrNil(composer);										// [Car]
	Expr_Block* pExprOfBlock = GetExprOfBlock();
	if (pExprOfBlock) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(*this);
		composer.ComposeAsSequence(*pExprOfBlock);
		composer.Add_Return(*pExprOfBlock);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		if (pExprOfBlock->IsDelegation()) {
			// Block-delegation format: f() {{block}}
			//pExprOfBlock->GetExprParamFirst()->ComposeOrNil(composer);		// [Any]
			pExprOfBlock->GetExprElemFirst()->ComposeOrNil(composer);			// [Any]
			composer.Add_ArgumentDelegation(GetAttr().Reference(), *this);		// [Argument]
		} else {
			composer.Add_Argument(GetAttr().Reference(),
								  pExprOfBlock->Reference(), false, *this);		// [Argument]
		}
	} else {
		composer.Add_Argument(GetAttr().Reference(), nullptr, false, *this);	// [Argument]
	}
	GetExprLinkParam().ComposeWithinArgSlot(composer);							// [Argument]
	if (Error::IsIssued()) return;
	composer.Add_Call(*this);													// [Result]
}

void Expr_Caller::ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	const char* errMsg = "invalid class definition";
	if (!GetExprCar().IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, errMsg);
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier&>(GetExprCar()).GetSymbol();
	if (!pSymbol->IsIdentical(Gurax_Symbol(public_)) || HasExprParam()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, errMsg);
		return;
	}
	GetExprOfBlock()->GetExprLinkElem().ComposeWithinClass(composer, pDottedSymbol.release(), true);
}

void Expr_Caller::ComposeWithinAssignment(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in function assigment");
		return;
	}
	if (GetExprCar().IsType<Expr_Member>()) {
		RefPtr<Function> pFunction(GenerateFunction(composer, Function::Type::Method, exprAssigned, pDottedSymbol.release()));
		if (!pFunction) return;
		if (!pFunction->IsSet(Function::Flag::OfClass)) pFunction->OrFlags(Function::Flag::OfInstance);
		Expr_Member& exprCarEx = dynamic_cast<Expr_Member&>(GetExprCar());
		if (exprCarEx.GetMemberMode() != MemberMode::Normal) {
			Error::IssueWith(ErrorType::SyntaxError, *this, "invalid method assignment");
			return;
		}
		exprCarEx.GetExprTarget().ComposeOrNil(composer);						// [Target]
		composer.Add_AssignMethod(pFunction.release(), false, *this);			// [Value]
	} else {
		RefPtr<Function> pFunction(GenerateFunction(composer, Function::Type::Function, exprAssigned, pDottedSymbol.release()));
		if (!pFunction) return;
		pFunction->SetType(Function::Type::Function);
		composer.Add_AssignFunction(pFunction.release(), *this);				// [Value]
	}
}

void Expr_Caller::ComposeWithinAssignmentInClass(
	Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in function assigment");
		return;
	}
	RefPtr<Function> pFunction(GenerateFunction(composer, Function::Type::Method, exprAssigned, pDottedSymbol.release()));
	if (!pFunction) return;
	composer.Add_AssignMethod(pFunction.release(), true, *this);				// [VType]
	composer.FlushDiscard();													// [VType]
}

Function* Expr_Caller::GenerateFunction(
	Composer& composer, DeclCallable::Type type, Expr& exprAssigned, RefPtr<DottedSymbol> pDottedSymbol)
{
	const Symbol* pSymbol = nullptr;
	if (GetExprCar().IsType<Expr_Identifier>()) {
		const Expr_Identifier& exprCarEx = dynamic_cast<const Expr_Identifier&>(GetExprCar());
		pSymbol = exprCarEx.GetSymbol();
	} else if (GetExprCar().IsType<Expr_Member>()) {
		const Expr_Member& exprCarEx = dynamic_cast<const Expr_Member&>(GetExprCar());
		pSymbol = exprCarEx.GetSymbol();
	} else {
		Error::IssueWith(ErrorType::SyntaxError, *this, "identifier is expected");
		return nullptr;
	}
	ExprList exprsHelp;
	do {
		Expr* pExpr = &exprAssigned;
		while (pExpr->IsBinaryOp(OpType::ModMod)) {
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			exprsHelp.push_back(&pExprEx->GetExprRight());
			pExpr = &pExprEx->GetExprLeft();
		}
		exprsHelp.push_back(pExpr);
	} while (0);
	Expr* pExprBody = nullptr;
	RefPtr<HelpHolder> pHelpHolder(new HelpHolder());
	if (exprsHelp.size() == 1) {
		pExprBody = exprsHelp.front();
	} else {
		auto ppExpr = exprsHelp.rbegin();
		pExprBody = *ppExpr++;
		for ( ; ppExpr != exprsHelp.rend(); ppExpr++) {
			const Expr* pExpr = *ppExpr;
			if (pExpr->IsType<Expr_String>()) {
				const Expr_String& exprEx = dynamic_cast<const Expr_String&>(*pExpr);
				pHelpHolder->AddHelp(Gurax_Symbol(en), exprEx.GetSegmentReferable().Reference());
			} else if (pExpr->IsSuffixed(SuffixMgr::Mode::String)) {
				const Expr_Suffixed& exprEx = dynamic_cast<const Expr_Suffixed&>(*pExpr);
				pHelpHolder->AddHelp(exprEx.GetSymbol(), exprEx.GetSegmentReferable().Reference());
			} else {
				Error::IssueWith(ErrorType::SyntaxError, *pExpr, "invalid expression for help");
				return nullptr;
			}
		}
	}
	if (!pExprBody) {
		Error::IssueWith(ErrorType::SyntaxError, *this, "no function body");
		return nullptr;
	}
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_Jump(*this);
	pExprBody->SetPUnitFirst(composer.PeekPUnitCont());
	pExprBody->ComposeOrNil(composer);
	if (GetAttr().IsSet(Gurax_Symbol(void_))) {
		composer.Add_DiscardValue(*this);
		composer.Add_Value(Value::nil(), *this);
	}
	composer.Add_Return(*this);
	for (Expr* pExprParam = GetExprParamFirst(); pExprParam; pExprParam = pExprParam->GetExprNext()) {
		Expr_Binary* pExprParamEx = nullptr;
		if (!pExprParam->IsDeclArgWithDefault(&pExprParamEx)) continue;
		Expr& exprDefaultArg = pExprParamEx->GetExprRight();
		PUnit* pPUnitDefaultArg = composer.PeekPUnitCont();
		exprDefaultArg.SetPUnitFirst(pPUnitDefaultArg);
		composer.Add_SequenceBegin(exprDefaultArg);
		exprDefaultArg.ComposeOrNil(composer);
		pPUnitDefaultArg->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_Return(exprDefaultArg);
		exprDefaultArg.SetPUnitEnd(composer.PeekPUnitCont());
	}
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	pExprBody->SetPUnitEnd(composer.PeekPUnitCont());
	if (pDottedSymbol) _pDeclCallable->SetDottedSymbol(pDottedSymbol.release());
	return new FunctionCustom(type, pSymbol, GetDeclCallable().Reference(), pExprBody->Reference(), pHelpHolder.release());
}

// This method is used by Template.
DeclCallable* Expr_Caller::RetrieveDeclCallable() const
{
	if (GetExprCar().IsType<Expr_Identifier>()) {
		const Expr_Identifier& exprCar = dynamic_cast<const Expr_Identifier&>(GetExprCar());
		RefPtr<Value> pValue(Basement::Inst.GetFrame().Retrieve(exprCar.GetSymbol()));
		return pValue? DeclCallable::Reference(pValue->GetDeclCallable()) : nullptr;
	} else if (GetExprCar().IsType<Expr_Member>()) {
		const Expr_Member& exprCar = dynamic_cast<const Expr_Member&>(GetExprCar());
		if (exprCar.GetExprTarget().IsType<Expr_Identifier>() &&
			dynamic_cast<const Expr_Identifier&>(exprCar.GetExprTarget()).GetSymbol()->
				IsIdentical(Gurax_Symbol(__tmpl__))) {
			RefPtr<Value> pValue(VTYPE_Template.GetFrameOfMember().Retrieve(exprCar.GetSymbol()));
			return pValue? DeclCallable::Reference(pValue->GetDeclCallable()) : nullptr;
		}
	}
	return nullptr;
}

String Expr_Caller::ToString(const StringStyle& ss, int indentLevel) const
{
	bool argListFlag = HasExprParam() || !GetAttr().IsEmpty() || !HasExprOfBlock();
	String str;
	str += _pExprCar->ToString(ss, indentLevel);
	if (argListFlag) {
		if (!ss.IsCram() && _pExprCar->IsType<Expr_Identifier>() &&
			dynamic_cast<Expr_Identifier*>(_pExprCar.get())->GetSymbol()->IsFlowControl()) {
			str += ' ';
		}
		str += '(';
		const Expr* pExprFirst = GetExprParamFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss, indentLevel);
		}
		str += ')';
	}
	str += GetAttr().ToString(ss);
	if (HasExprOfBlock()) {
		if (!ss.IsCram()) str += ' ';
		str += GetExprOfBlock()->ToString(ss, indentLevel);
	}
	if (HasExprTrailer()) {
		if (!ss.IsCram()) str += ' ';
		str += GetExprTrailer()->ToString(ss, indentLevel);
	}
	return str;
}

void Expr_Caller::SetExprTrailer(Expr_Caller* pExprTrailer)
{
	_pExprTrailer.reset(pExprTrailer);
	if (_pExprTrailer) _pExprTrailer->SetExprParent(this);
}

Expr_Caller& Expr_Caller::GetExprTrailerLast()
{
	Expr_Caller* pExpr = this;
	for ( ; pExpr->GetExprTrailer(); pExpr = pExpr->GetExprTrailer()) ;
	return *pExpr;
}

//------------------------------------------------------------------------------
// Iterator_ExprLink
//------------------------------------------------------------------------------
size_t Iterator_ExprLink::GetLength() const
{
	return _pExprLink->CountSequence();
}

Value* Iterator_ExprLink::DoNextValue()
{
	if (!_pExprCur) return nullptr;
	RefPtr<Value> pValue(new Value_Expr(_pExprCur->Reference()));
	_pExprCur = _pExprCur->GetExprNext();
	return pValue.release();
}

String Iterator_ExprLink::ToString(const StringStyle& ss) const
{
	String str;
	str += "ExprLink";
	return str;
}

}
