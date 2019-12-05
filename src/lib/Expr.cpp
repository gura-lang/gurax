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
	if (pPUnitMarked == composer.PeekPUnitCont()) { // when nothing has been yielded
		composer.Add_Value(Value::nil(), this);
	}
}

Iterator* Expr::EachPUnit() const
{
	const PUnit* pPUnitSentinel = nullptr;
	const PUnit* pPUnit = GetPUnitFirst();
	if (pPUnit && pPUnit->GetPUnitSentinel()) {
		pPUnitSentinel = pPUnit->GetPUnitSentinel();
		pPUnit = pPUnit->GetPUnitCont();	// skip BeginSequence/ArgSlot/ArgSlotNamed
	}
	return new Iterator_PUnit(pPUnit, pPUnitSentinel);
}

int Expr::CalcIndentLevel() const
{
	int indentLevel = 0;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), indentLevel++) ;
	return indentLevel;
}

String Expr::MakeIndent(const StringStyle& ss) const
{
	String str;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), str += ss.GetIndentUnit()) ;
	return str;
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
	RefPtr<Value> pValue(processor.ProcessExpr(*this));
	processor.ClearEvent();
	return pValue.release();
}

Value* Expr::Eval(Processor& processor, Event& event) const
{
	if (!GetPUnitFirst()) return Value::nil();
	RefPtr<Value> pValue(processor.ProcessExpr(*this));
	event = processor.GetEvent();
	processor.ClearEvent();
	return pValue.release();
}

Value* Expr::Eval(Processor& processor, Argument& argument) const
{
	if (!GetPUnitFirst()) return Value::nil();
	if (!argument.Compensate(processor)) return Value::nil();
	argument.AssignToFrame(processor.PushFrame<Frame_Block>());
	RefPtr<Value> pValue(processor.ProcessExpr(*this));
	processor.PopFrame();
	processor.ClearEvent();
	return pValue.release();
}

Value* Expr::Eval(Processor& processor, Argument& argument, Event& event) const
{
	if (!GetPUnitFirst()) return Value::nil();
	if (!argument.Compensate(processor)) return Value::nil();
	argument.AssignToFrame(processor.PushFrame<Frame_Block>());
	RefPtr<Value> pValue(processor.ProcessExpr(*this));
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
		pExpr = pExpr->GetExprNext();
	}
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		composer.FlushDiscard();
		pExpr->Compose(composer);
	}
	if (pPUnitMarked == composer.PeekPUnitCont()) { // when nothing has been yielded
		composer.Add_Value(Value::nil(), this);
	}
	// [Value]
}

void Expr::ComposeForClass(Composer& composer, bool publicFlag)
{
	Error::Issue(ErrorType::SyntaxError, "invalid class definition");
}

void Expr::ComposeForList(Composer& composer)
{
	ComposeOrNil(composer);											// [List Any]
	composer.Add_ListElem(0, false, false, this);					// [List]
}

void Expr::ComposeForValueAssignment(Composer& composer, const Operator* pOp)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeForAssignment(
	Composer& composer, Expr& exprAssigned, const Operator* pOp)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeForAssignmentInClass(
	Composer& composer, Expr& exprAssigned, const Operator* pOp, bool publicFlag)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeForArgSlot(Composer& composer)
{
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	composer.Add_BeginArgSlot(this);								// [Argument]
	Compose(composer);												// [Argument Any]
	pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
	composer.Add_EndArgSlot(this);									// [Argument]
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	SetPUnitFirst(pPUnitOfArgSlot);
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

void ExprLink::ComposeForClass(Composer& composer, bool publicFlag) const
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeForClass(composer, publicFlag);
		if (Error::IsIssued()) return;
		composer.FlushDiscard();
	}
}

void ExprLink::ComposeForArgSlot(Composer& composer) const
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeForArgSlot(composer);
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
const Expr::TypeInfo Expr_Empty::typeInfo("Empty");

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
void Expr_Composite::AddExprCdr(Expr* pExprCdr)
{
	pExprCdr->SetExprParent(this);
	_pExprLinkCdr->AddExpr(pExprCdr);
}

//------------------------------------------------------------------------------
// Expr_Member
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Member::typeInfo("Member");

void Expr_Member::Compose(Composer& composer)
{
	GetExprTarget().ComposeOrNil(composer);										// [Target]
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		composer.Add_MemberGet_Normal(GetSymbol(),
									  GetAttr().Reference(), this);				// [Member] or [Prop]
		break;
	}
	case MemberMode::MapAlong: {
		composer.Add_MemberGet_MapAlong(GetSymbol(),
										GetAttr().Reference(), this);			// [Member] or [Prop]
		break;
	}
	case MemberMode::MapToList: {
		composer.Add_MemberGet_MapToList(GetSymbol(),
										 GetAttr().Reference(), this);			// [Member] or [Prop]
		break;
	}
	case MemberMode::MapToIter: {
		composer.Add_MemberGet_MapToIter(GetSymbol(),
										 GetAttr().Reference(), this);			// [Member] or [Prop]
		break;
	}
	default: {
		break;
	}
	}
}

void Expr_Member::ComposeForValueAssignment(Composer& composer, const Operator* pOp)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in lister assigment");
		return;
	}
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		GetExprTarget().ComposeOrNil(composer);									// [Assigned Target]
		composer.Add_MemberSet_Normal(GetSymbol(), GetAttr().Reference(),
									  true, this);								// [Assigned]
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

void Expr_Member::ComposeForAssignment(
	Composer& composer, Expr& exprAssigned, const Operator* pOp)
{
	GetExprTarget().ComposeOrNil(composer);										// [Target]
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		exprAssigned.ComposeOrNil(composer);									// [Target Assigned]
		if (pOp) {
			composer.Add_MemberOpApply_Normal(GetSymbol(), GetAttr().Reference(), pOp,
								 false, this);									// [Assigned]
		} else {
			composer.Add_MemberSet_Normal(GetSymbol(), GetAttr().Reference(),
								 false, this);									// [Assigned]
		}
		break;
	}
	case MemberMode::MapAlong: {
		bool mapAssignedFlag = true;
		exprAssigned.ComposeOrNil(composer);									// [Target Assigned]
		if (pOp) {
			Error::Issue_UnimplementedOperation();
			//composer.Add_MemberOpApply_Map(GetSymbol(), GetAttr().Reference(), pOp,
			//					 mapAssignedFlag, false, this);					// [Assigned]
		} else {
			composer.Add_MemberSet_Map(GetSymbol(), GetAttr().Reference(),
									   mapAssignedFlag, false, this);			// [Assigned]
		}
		break;
	}
	case MemberMode::MapToList: case MemberMode::MapToIter: {
		bool mapAssignedFlag = false;
		exprAssigned.ComposeOrNil(composer);									// [Target Assigned]
		if (pOp) {
			Error::Issue_UnimplementedOperation();
			//composer.Add_MemberOpApply_Map(GetSymbol(), GetAttr().Reference(), pOp,
			//					 mapAssignedFlag, false, this);					// [Assigned]
		} else {
			composer.Add_MemberSet_Map(GetSymbol(), GetAttr().Reference(),
									   mapAssignedFlag, false, this);			// [Assigned]
		}
		break;
	}
	default:
		break;
	}
}

String Expr_Member::ToString(const StringStyle& ss) const
{
	String str;
	const Expr& exprTarget = GetExprTarget();
	str += exprTarget.ToString(ss);
	str += MemberModeToSymbol(GetMemberMode())->GetName();
	str += GetSymbol()->ToString();
	str += GetAttr().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Value : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Value::typeInfo("Value");

void Expr_Value::Compose(Composer& composer)
{
	composer.Add_Value(GetValue()->Clone(), this);	// [Value]
}

String Expr_Value::ToString(const StringStyle& ss) const
{
	return HasSource()? GetSourceSTL() : GetValue()->ToString();
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo("Identifier");

const DeclCallable* Expr_Identifier::LookupDeclCallable() const
{
	Value* pValue = Basement::Inst.GetFrame().Lookup(GetSymbol());
	return pValue? pValue->GetDeclCallable() : nullptr;
}

void Expr_Identifier::Compose(Composer& composer)
{
	const Symbol* pSymbol = GetSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(__file__))) {
		composer.Add_Value(new Value_String(GetPathNameSrc()), this);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(__line__))) {
		composer.Add_Value(new Value_Number(GetLineNoTop()), this);
	} else {
		Value* pValue = Basement::Inst.GetFrame().Lookup(pSymbol);
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = dynamic_cast<Value_Function*>(pValue)->GetFunction();
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
		composer.Add_Lookup(pSymbol, this);					// [Value]
	}
}

void Expr_Identifier::ComposeForValueAssignment(Composer& composer, const Operator* pOp)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in lister assigment");
		return;
	}
	composer.Add_AssignToSymbol(GetSymbol(), this);			// [Assigned]
	composer.FlushDiscard();
}

void Expr_Identifier::ComposeForAssignment(
	Composer& composer, Expr& exprAssigned, const Operator* pOp)
{
	if (pOp) {
		composer.Add_Lookup(GetSymbol(), this);				// [Any]
		exprAssigned.ComposeOrNil(composer);				// [Any Right]
		composer.Add_BinaryOp(pOp, this);				// [Assigned]
	} else {
		exprAssigned.ComposeOrNil(composer);				// [Assigned]
	}
	composer.Add_AssignToSymbol(GetSymbol(), this);			// [Assigned]
}

void Expr_Identifier::ComposeForClass(Composer& composer, bool publicFlag)
{
	PropHandler::Flags flags = publicFlag? PropHandler::Flag::Public : 0;
	composer.Add_AssignPropHandler(GetSymbol(), flags, GetAttr(), true, this);
	composer.FlushDiscard();										// [VType]
}
	
void Expr_Identifier::ComposeForAssignmentInClass(
	Composer& composer, Expr& exprAssigned, const Operator* pOp, bool publicFlag)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in property assigment");
		return;
	}
	PropHandler::Flags flags = publicFlag? PropHandler::Flag::Public : 0;
	exprAssigned.ComposeOrNil(composer);							// [VType Value]
	composer.Add_AssignPropHandler(GetSymbol(), flags, GetAttr(), false, this);
	composer.FlushDiscard();										// [VType]
}

String Expr_Identifier::ToString(const StringStyle& ss, const char* strInsert) const
{
	String str;
	str += GetSymbol()->ToString();
	str += strInsert;
	str += GetAttr().ToString(ss);
	return str;
}

bool Expr_Identifier::IsEqualTo(const Expr& expr) const
{
	if (!expr.IsType<Expr_Identifier>()) return false;
	const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(expr);
	return GetSymbol()->IsIdentical(exprEx.GetSymbol());
}

//------------------------------------------------------------------------------
// Expr_String : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_String::typeInfo("String");

void Expr_String::Compose(Composer& composer)
{
	composer.Add_Value(new Value_String(GetSegmentReferable().Reference()), this);	// [Value]
}

String Expr_String::ToString(const StringStyle& ss) const
{
	String str = GetSegmentSTL();
	if (!ss.IsAsValue()) str = str.MakeQuoted(true);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Suffixed::typeInfo("Suffixed");

void Expr_Suffixed::Compose(Composer& composer)
{
	const SuffixMgr* pSuffixMgr = Basement::Inst.LookupSuffixMgr(GetTarget(), GetSymbolSuffix());
	if (pSuffixMgr) {
		pSuffixMgr->Compose(composer, GetSegmentReferable(), this);
	} else {
		composer.Add_Suffixed(GetSegmentReferable().Reference(), GetTarget(), GetSymbolSuffix());
	}
}

String Expr_Suffixed::ToString(const StringStyle& ss) const
{
	String str;
	str += (GetTarget() == SuffixMgr::Target::Number)? GetSegmentSTL() : GetSegmentSTL().MakeQuoted(true);
	str += GetSymbolSuffix()->GetName();
	return str;
}

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo("UnaryOp");

void Expr_UnaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		GetOperator()->ComposeUnary(composer, *this);					// [Result]
	} else {
		GetExprChild().ComposeOrNil(composer);							// [Any]
		composer.Add_UnaryOp(GetOperator(), this);						// [Result]
	}
}

void Expr_UnaryOp::ComposeForList(Composer& composer)
{
	if (!GetOperator()->IsType(OpType::PostMul)) {
		Expr_Unary::ComposeForList(composer);							// [List]
		return;
	}
	GetExprChild().ComposeOrNil(composer);								// [List Any]
	composer.Add_ListElem(0, false, true, this);						// [List]
}

void Expr_UnaryOp::ComposeForArgSlot(Composer& composer)
{
	if (GetOperator()->IsType(OpType::PostMul)) {
		PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
		composer.Add_BeginArgSlot(this);								// [Argument]
		GetExprChild().ComposeOrNil(composer);							// [Argument Any]
		pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_EndArgSlotExpand(this);							// [Argument]
		pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
		SetPUnitFirst(pPUnitOfArgSlot);
	} else {
		Expr_Unary::ComposeForArgSlot(composer);
	}
}

String Expr_UnaryOp::ToString(const StringStyle& ss) const
{
	String str;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpPreUnary: {
		bool requireParFlag = GetExprChild().IsType<Expr_UnaryOp>() || GetExprChild().IsType<Expr_BinaryOp>();
		str += GetOperator()->GetSymbol();
		if (requireParFlag) str += '(';
		str += GetExprChild().ToString(ss);
		if (requireParFlag) str += ')';
		break;
	}
	case OpStyle::OpPostUnary: {
		if (GetExprChild().IsType<Expr_Identifier>()) {
			const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(GetExprChild());
			str += exprEx.ToString(ss, GetOperator()->GetSymbol());
		} else if (GetExprChild().IsType<Expr_Indexer>()) {
			const Expr_Indexer& exprEx = dynamic_cast<const Expr_Indexer&>(GetExprChild());
			str += exprEx.ToString(ss, GetOperator()->GetSymbol());
		} else {
			bool requireParFlag = GetExprChild().IsType<Expr_UnaryOp>() || GetExprChild().IsType<Expr_BinaryOp>();
			if (requireParFlag) str += '(';
			str += GetExprChild().ToString(ss);
			if (requireParFlag) str += ')';
			str += GetOperator()->GetSymbol();
		}
		break;
	}
	case OpStyle::MathUnary: {
		str += GetOperator()->GetSymbol();
		str += '(';
		str += GetExprChild().ToString(ss);
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
const Expr::TypeInfo Expr_BinaryOp::typeInfo("BinaryOp");

void Expr_BinaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		GetOperator()->ComposeBinary(composer, *this);
	} else {
		GetExprLeft().ComposeOrNil(composer);							// [Left]
		GetExprRight().ComposeOrNil(composer);							// [Left Right]
		composer.Add_BinaryOp(GetOperator(), this);						// [Result]
	}
}

void Expr_BinaryOp::ComposeForList(Composer& composer)
{
	if (GetOperator()->IsType(OpType::Seq)) {
		GetExprLeft().ComposeOrNil(composer);							// [List Left]
		GetExprRight().ComposeOrNil(composer);							// [List Left Right]
		composer.Add_BinaryOp(GetOperator(), this);						// [List Result]
		composer.Add_ListElem(0, false, true, this);					// [List]
	} else {
		Expr_Binary::ComposeForList(composer);							// [List]
	}
}

String Expr_BinaryOp::ToString(const StringStyle& ss) const
{
	String str;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpBinary: {
		do {
			bool needParenFlag =
				GetExprLeft().IsType<Expr_BinaryOp>() || GetExprLeft().IsType<Expr_UnaryOp>();
			if (needParenFlag) str += '(';
			str += GetExprLeft().ToString(ss);
			if (needParenFlag) str += ')';
		} while (0);
		if (!ss.IsCram()) str += ' ';
		str += GetOperator()->GetSymbol();
		if (!ss.IsCram()) str += ' ';
		do {
			bool needParenFlag =
				GetExprRight().IsType<Expr_BinaryOp>() || GetExprRight().IsType<Expr_UnaryOp>();
			if (needParenFlag) str += '(';
			str += GetExprRight().ToString(ss);
			if (needParenFlag) str += ')';
		} while (0);
		break;
	}
	case OpStyle::MathBinary: {
		str += GetOperator()->GetSymbol();
		str += '(';
		str += GetExprLeft().ToString(ss);
		str += ss.GetComma();
		if (!ss.IsCram()) str += ' ';
		str += GetExprRight().ToString(ss);
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
const Expr::TypeInfo Expr_Assign::typeInfo("Assign");

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
	GetExprLeft().ComposeForAssignment(composer, GetExprRight(), GetOperator()); // [Assigned]
}

void Expr_Assign::ComposeForClass(Composer& composer, bool publicFlag)
{
	GetExprLeft().ComposeForAssignmentInClass(composer, GetExprRight(), GetOperator(), publicFlag); // [Assigned]
}

void Expr_Assign::ComposeForArgSlot(Composer& composer)
{
	if (GetOperator() || !GetExprLeft().IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::ArgumentError, *this,
						 "invalid declaration of named argument");
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier&>(GetExprLeft()).GetSymbol();
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	composer.Add_BeginArgSlotNamed(
		pSymbol, GetExprRight().Reference(), this);					// [Argument ArgSlot]
	GetExprRight().ComposeOrNil(composer);							// [Argument ArgSlot Assigned]
	pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
	composer.Add_EndArgSlotNamed(this);								// [Argument]
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	GetExprRight().SetPUnitFirst(pPUnitOfArgSlot);
}

String Expr_Assign::ToString(const StringStyle& ss) const
{
	String str;
	str += GetExprLeft().ToString(ss);
	if (!ss.IsCram()) str += ' ';
	if (GetOperator()) str += GetOperator()->GetSymbol();
	str += '=';
	if (!ss.IsCram()) str += ' ';
	str += GetExprRight().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Root : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Root::typeInfo("Root");

void Expr_Root::Compose(Composer& composer)
{
	SetPUnitFirst(composer.PeekPUnitCont());
	//PUnit* pPUnitOfBeginSequence = PeekPUnitCont();
	//Add_BeginSequence(expr);											// []
	ComposeSequence(composer, GetExprElemFirst());						// [Any]
	//pPUnitOfBeginSequence->SetPUnitSentinel(PeekPUnitCont());
	composer.Add_Return(this);
	composer.Add_Terminate();
}

String Expr_Root::ToString(const StringStyle& ss) const
{
	String str;
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			str += indent;
			str += pExpr->ToString(ss);
			str += '\n';
		}
	} else {
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ';';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss);
		}
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Block::typeInfo("Block");

bool Expr_Block::DoPrepare()
{
	return HasCallerAsParent()? PrepareDeclCallable() : true;
}

void Expr_Block::Compose(Composer& composer)
{
	if (!HasCallerAsParent() && HasExprParam()) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(this);
		SetPUnitSubFirst(composer.PeekPUnitCont());
		PUnit* pPUnitSequence = composer.PeekPUnitCont();
		composer.Add_BeginSequence(this);
		//Expr::ComposeForArgSlot(composer, GetExprParamFirst());
		GetExprLinkParam().ComposeForArgSlot(composer);
		pPUnitSequence->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_Return(this);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	}
	ComposeSequence(composer, GetExprElemFirst());				// [Any]
}

void Expr_Block::ComposeForList(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, this);						// [List List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeForList(composer);						// [List List]
	}	
	composer.Add_ListElem(0, false, false, this);				// [List]
}

bool Expr_Block::HasCallerAsParent() const
{
	RefPtr<Expr> pExprParent(LockExprParent());
	return pExprParent && pExprParent->IsType<Expr_Caller>();
}

Value* Expr_Block::EvalEasy(Processor& processor, RefPtr<Value> pValueArg) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgument(Argument::CreateForBlockCall(*this));
	ArgFeeder args(*pArgument);
	if (!args.FeedValue(frame, pValueArg.release())) return Value::nil();
	return Eval(processor, *pArgument);
}

Value* Expr_Block::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgument(Argument::CreateForBlockCall(*this));
	ArgFeeder args(*pArgument);
	if (!args.FeedValue(frame, pValueArg1.release())) return Value::nil();
	if (!args.FeedValue(frame, pValueArg2.release())) return Value::nil();
	return Eval(processor, *pArgument);
}

String Expr_Block::ToString(const StringStyle& ss) const
{
	String str;
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += indent;
		str += '{';
		if (HasExprParam()) {
			str += '|';
			const Expr* pExprFirst = GetExprParamFirst();
			for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
				if (pExpr != pExprFirst) {
					str += ',';
					if (!ss.IsCram()) str += ' ';
				}
				str += pExpr->ToString(ss);
			}
			str += '|';
		}
		str += '\n';
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			str += indentDown;
			str += pExpr->ToString(ss);
			str += '\n';
		}
		str += indent;
		str += "}\n";
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
				str += pExpr->ToString(ss);
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
			str += pExpr->ToString(ss);
		}
		str += '}';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Iterer : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Iterer::typeInfo("Iterer");

void Expr_Iterer::Compose(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, this);						// [List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [List Elem]
		composer.Add_ListElem(0, false, false);					// [List]
	}	
	composer.Add_GenIterator(this);								// [Iterator]
}

String Expr_Iterer::ToString(const StringStyle& ss) const
{
	String str;
	if (GetExprLinkElem().CountSequence() == 1) {
		str += '(';
		str += GetExprLinkElem().GetExprFirst()->ToString(ss);
		str += ",)";
	} else if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += indent;
		str += "(\n";
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			str += indentDown;
			str += pExpr->ToString(ss);
			str += '\n';
		}
		str += indent;
		str += ")\n";
	} else {
		str += '(';
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss);
		}
		str += ')';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Lister::typeInfo("Lister");

void Expr_Lister::Compose(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, this);						// [List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeForList(composer);						// [List]
	}	
}

void Expr_Lister::ComposeForAssignment(
	Composer& composer, Expr& exprAssigned, const Operator* pOp)
{
	exprAssigned.ComposeOrNil(composer);						// [Assigned]
	composer.Add_GenIterator_ForLister(this);					// [Assigned Iterator]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		composer.Add_EvalIterator(0, true);						// [Assigned Iterator Value]
		pExpr->ComposeForValueAssignment(composer, pOp);	// [Assigned Iterator]
		if (Error::IsIssued()) return;
	}
	composer.Add_DiscardValue(this);							// [Assigned]
}

String Expr_Lister::ToString(const StringStyle& ss) const
{
	String str;
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		str += indent;
		str += "[\n";
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			str += indentDown;
			str += pExpr->ToString(ss);
			str += '\n';
		}
		str += indent;
		str += "]\n";
	} else {
		str += '[';
		const Expr* pExprFirst = GetExprElemFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss);
		}
		str += ']';
	}
	return str;
}

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Indexer::typeInfo("Indexer");

void Expr_Indexer::Compose(Composer& composer)
{
	GetExprCar().ComposeOrNil(composer);						// [Car]
	size_t nExprs = GetExprLinkCdr().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, this);	// [Index(Car)]
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [Index(Car) Cdr]
		composer.Add_FeedIndex(pExpr);							// [Index(Car)]
	}
	composer.Add_IndexGet(this);								// [Elems]
}

void Expr_Indexer::ComposeForValueAssignment(Composer& composer, const Operator* pOp)
{
	GetExprCar().ComposeOrNil(composer);						// [Elems Car]
	size_t nExprs = GetExprLinkCdr().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, this);	// [Elems Index(Car)]
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [Elems Index(Car) Cdr]
		composer.Add_FeedIndex(pExpr);							// [Elems Index(Car)]
	}
	if (pOp) {
		Error::Issue_UnimplementedOperation();
		return;
		//composer.Add_IndexOpApply(pOp, true, this);		// [Rtn]
	} else {
		composer.Add_IndexSet(true, this);						// [Elems]
	}
	composer.FlushDiscard();
}

void Expr_Indexer::ComposeForAssignment(
	Composer& composer, Expr& exprAssigned, const Operator* pOp)
{
	GetExprCar().ComposeOrNil(composer);						// [Car]
	size_t nExprs = GetExprLinkCdr().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, this);	// [Index(Car)]
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [Index(Car) Cdr]
		composer.Add_FeedIndex(pExpr);							// [Index(Car)]
	}
	exprAssigned.ComposeOrNil(composer);						// [Index(Car) Elems]
	if (pOp) {
		composer.Add_IndexOpApply(pOp, false, this);		// [Rtn]
	} else {
		composer.Add_IndexSet(false, this);						// [Elems]
	}
}

void Expr_Indexer::ComposeForClass(Composer& composer, bool publicFlag)
{
	if (!GetExprCar().IsType<Expr_Identifier>() || HasExprCdr()) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid format of property declaration");
		return;
	}
	PropHandler::Flags flags = PropHandler::Flag::ListVar | (publicFlag? PropHandler::Flag::Public : 0);
	const Expr_Identifier& exprCar = dynamic_cast<Expr_Identifier&>(GetExprCar());
	composer.Add_AssignPropHandler(exprCar.GetSymbol(), flags, GetAttr(), true, this);
	composer.FlushDiscard();										// [VType]
}

void Expr_Indexer::ComposeForAssignmentInClass(
	Composer& composer, Expr& exprAssigned, const Operator* pOp, bool publicFlag)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in property assigment");
		return;
	}
	if (!GetExprCar().IsType<Expr_Identifier>() || HasExprCdr()) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid format of property declaration");
		return;
	}
	PropHandler::Flags flags = PropHandler::Flag::ListVar | (publicFlag? PropHandler::Flag::Public : 0);
	const Expr_Identifier& exprCar = dynamic_cast<Expr_Identifier&>(GetExprCar());
	exprAssigned.ComposeOrNil(composer);							// [VType Value]
	composer.Add_AssignPropHandler(exprCar.GetSymbol(), flags, GetAttr(), false, this);
	composer.FlushDiscard();										// [VType]
}

String Expr_Indexer::ToString(const StringStyle& ss, const char* strInsert) const
{
	String str;
	str += _pExprCar->ToString(ss);
	str += '[';
	const Expr* pExprFirst = GetExprCdrFirst();
	for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr != pExprFirst) {
			str += ',';
			if (!ss.IsCram()) str += ' ';
		}
		str += pExpr->ToString(ss);
	}
	str += ']';
	str += strInsert;
	str += GetAttr().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Caller::typeInfo("Caller");

void Expr_Caller::Compose(Composer& composer)
{
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromExpr(GetExprCar()));
	if (pDottedSymbol) {
		Value* pValue = Basement::Inst.GetFrame().Lookup(*pDottedSymbol);
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = Value_Function::GetFunction(*pValue);
			if (func.IsTypeStatement()) {
				func.Compose(composer, *this);								// [Result]
				return;
			}
		}
	}
	GetExprCar().ComposeOrNil(composer);									// [Car]
	Expr_Block* pExprOfBlock = GetExprOfBlock();
	if (pExprOfBlock) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(this);
		composer.ComposeAsSequence(*pExprOfBlock);
		composer.Add_Return(pExprOfBlock);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		if (pExprOfBlock->IsDelegation()) {
			// Block-delegation format: f() {|block|}
			pExprOfBlock->GetExprParamFirst()->ComposeOrNil(composer);		// [Any]
			composer.Add_ArgumentDelegation(GetAttr().Reference(), this);	// [Argument]
		} else {
			composer.Add_Argument(GetAttr().Reference(),
								  pExprOfBlock->Reference(), false, this);	// [Argument]
		}
	} else {
		composer.Add_Argument(GetAttr().Reference(), nullptr, false, this);	// [Argument]
	}
	GetExprLinkCdr().ComposeForArgSlot(composer);							// [Argument]
	if (Error::IsIssued()) return;
	composer.Add_Call(this);												// [Result]
}

void Expr_Caller::ComposeForClass(Composer& composer, bool publicFlag)
{
	const char* errMsg = "invalid class definition";
	if (!GetExprCar().IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, errMsg);
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier&>(GetExprCar()).GetSymbol();
	if (!pSymbol->IsIdentical(Gurax_Symbol(public_)) || HasExprCdr()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, errMsg);
		return;
	}
	GetExprOfBlock()->GetExprLinkElem().ComposeForClass(composer, true);
}

void Expr_Caller::ComposeForAssignment(
	Composer& composer, Expr& exprAssigned, const Operator* pOp)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in function assigment");
		return;
	}
	if (GetExprCar().IsType<Expr_Member>()) {
		RefPtr<Function> pFunction(GenerateFunction(composer, exprAssigned));
		if (!pFunction) return;
		pFunction->SetType(GetAttr().IsSet(Gurax_Symbol(static_))?
						   Function::Type::ClassMethod : Function::Type::Method);
		Expr_Member& exprCarEx = dynamic_cast<Expr_Member&>(GetExprCar());
		if (exprCarEx.GetMemberMode() != MemberMode::Normal) {
			Error::IssueWith(ErrorType::SyntaxError, *this, "invalid method assignment");
			return;
		}
		exprCarEx.GetExprTarget().ComposeOrNil(composer);				// [Target]
		composer.Add_AssignMethod(pFunction.release(), false, this);	// [Value]
	} else {
		RefPtr<Function> pFunction(GenerateFunction(composer, exprAssigned));
		if (!pFunction) return;
		pFunction->SetType(Function::Type::Function);
		composer.Add_AssignFunction(pFunction.release(), this);			// [Value]
	}
}

void Expr_Caller::ComposeForAssignmentInClass(
	Composer& composer, Expr& exprAssigned, const Operator* pOp, bool publicFlag)
{
	if (pOp) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in function assigment");
		return;
	}
	RefPtr<Function> pFunction(GenerateFunction(composer, exprAssigned));
	if (!pFunction) return;
	pFunction->SetType(GetAttr().IsSet(Gurax_Symbol(static_))?
					   Function::Type::ClassMethod : Function::Type::Method);
	composer.Add_AssignMethod(pFunction.release(), true, this);			// [VType]
	composer.FlushDiscard();											// [VType]
}

Function* Expr_Caller::GenerateFunction(Composer& composer, Expr& exprAssigned)
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
	ExprList exprs;
	do {
		Expr* pExpr = &exprAssigned;
		while (pExpr->IsBinaryOp(OpType::ModMod)) {
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			exprs.push_back(&pExprEx->GetExprLeft());
			pExpr = &pExprEx->GetExprRight();
		}
		exprs.push_back(pExpr);
	} while (0);
	Expr* pExprBody = nullptr;
	RefPtr<HelpHolder> pHelpHolder(new HelpHolder());
	if (exprs.size() == 1) {
		pExprBody = exprs.front();
	} else {
		for (Expr* pExpr : exprs) {
			if (pExpr->IsType<Expr_String>()) {
				Expr_String& exprEx = dynamic_cast<Expr_String&>(*pExpr);
				pHelpHolder->AddHelp(Gurax_Symbol(en), exprEx.GetSegmentReferable().Reference());
			} else if (pExpr->IsSuffixed(SuffixMgr::Target::String)) {
				Expr_Suffixed& exprEx = dynamic_cast<Expr_Suffixed&>(*pExpr);
				pHelpHolder->AddHelp(exprEx.GetSymbolSuffix(), exprEx.GetSegmentReferable().Reference());
			} else if (pExprBody) {
				Error::IssueWith(ErrorType::SyntaxError, *this, "duplicated function body");
				return nullptr;
			} else {
				pExprBody = pExpr;
			}
		}
	}
	if (!pExprBody) {
		Error::IssueWith(ErrorType::SyntaxError, *this, "no function body");
		return nullptr;
	}
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_Jump(this);
	pExprBody->SetPUnitFirst(composer.PeekPUnitCont());
	pExprBody->ComposeOrNil(composer);
	if (GetAttr().IsSet(Gurax_Symbol(void_))) {
		composer.Add_DiscardValue(this);
		composer.Add_Value(Value::nil());
	}
	composer.Add_Return(this);
	for (Expr* pExprParam = GetExprCdrFirst(); pExprParam; pExprParam = pExprParam->GetExprNext()) {
		Expr_Binary* pExprParamEx = nullptr;
		if (!pExprParam->IsDeclArgWithDefault(&pExprParamEx)) continue;
		Expr& exprDefaultArg = pExprParamEx->GetExprRight();
		PUnit* pPUnitDefaultArg = composer.PeekPUnitCont();
		composer.Add_BeginSequence(&exprDefaultArg);
		exprDefaultArg.ComposeOrNil(composer);
		pPUnitDefaultArg->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_Return(&exprDefaultArg);
		exprDefaultArg.SetPUnitFirst(pPUnitDefaultArg);
	}
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	return new FunctionCustom(Function::Type::Function, pSymbol,
							  GetDeclCallable().Reference(), pExprBody->Reference(), pHelpHolder.release());
}

// This method is used by Template.
const DeclCallable* Expr_Caller::LookupDeclCallable() const
{
	if (GetExprCar().IsType<Expr_Identifier>()) {
		const Expr_Identifier& exprCar = dynamic_cast<const Expr_Identifier&>(GetExprCar());
		Value* pValue = Basement::Inst.GetFrame().Lookup(exprCar.GetSymbol());
		return pValue? pValue->GetDeclCallable() : nullptr;
	} else if (GetExprCar().IsType<Expr_Member>()) {
		const Expr_Member& exprCar = dynamic_cast<const Expr_Member&>(GetExprCar());
		if (exprCar.GetExprTarget().IsType<Expr_Identifier>() &&
			dynamic_cast<const Expr_Identifier&>(exprCar.GetExprTarget()).GetSymbol()->
				IsIdentical(Gurax_Symbol(this_))) {
			Value* pValue = VTYPE_Template.GetFrame().Lookup(exprCar.GetSymbol());
			return pValue? pValue->GetDeclCallable() : nullptr;
		}
	}
	return nullptr;
}

String Expr_Caller::ToString(const StringStyle& ss) const
{
	bool argListFlag = HasExprCdr() || !GetAttr().IsEmpty() || !HasExprOfBlock();
	String str;
	str += _pExprCar->ToString(ss);
	if (argListFlag) {
		if (!ss.IsCram() && _pExprCar->IsType<Expr_Identifier>() &&
			dynamic_cast<Expr_Identifier*>(_pExprCar.get())->GetSymbol()->IsFlowControl()) {
			str += ' ';
		}
		str += '(';
		const Expr* pExprFirst = GetExprCdrFirst();
		for (const Expr* pExpr = pExprFirst; pExpr; pExpr = pExpr->GetExprNext()) {
			if (pExpr != pExprFirst) {
				str += ',';
				if (!ss.IsCram()) str += ' ';
			}
			str += pExpr->ToString(ss);
		}
		str += ')';
	}
	str += GetAttr().ToString(ss);
	if (HasExprOfBlock()) {
		if (!ss.IsCram()) str += ' ';
		str += GetExprOfBlock()->ToString(ss);
	}
	if (HasExprTrailer()) {
		if (!ss.IsCram()) str += ' ';
		str += GetExprTrailer()->ToString(ss);
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
	for ( ; pExpr->GetExprTrailer() != nullptr; pExpr = pExpr->GetExprTrailer()) ;
	return *pExpr;
}

const Expr* Expr_Caller::GetTrailerSymbols(SymbolList& symbols) const
{
	for (const Expr* pExpr = GetExprTrailer(); pExpr; ) {
		if (!pExpr->IsType<Expr_Caller>()) return pExpr;
		const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
		const Expr& exprCar = pExprEx->GetExprCar();
		if (!exprCar.IsType<Expr_Identifier>()) return &exprCar;
		const Expr_Identifier& exprCarEx = dynamic_cast<const Expr_Identifier&>(exprCar);
		symbols.push_back(exprCarEx.GetSymbol());
		pExpr = pExprEx->GetExprTrailer();
	}
	return nullptr;
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
