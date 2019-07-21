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

void Expr::ComposeInClass(Composer& composer, bool publicFlag)
{
	Error::Issue(ErrorType::SyntaxError, "invalid class definition");
}

void Expr::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeForAssignmentInClass(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator, bool publicFlag)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
}

void Expr::ComposeForArgSlot(Composer& composer, Expr* pExpr)
{
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeForArgSlot(composer);
		if (Error::IsIssued()) return;
	}
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

Value* Expr::DoEval(Processor& processor, Argument& argument) const
{
	if (!GetPUnitFirst()) return Value::nil();
	argument.AssignToFrame(processor.PushFrame<Frame_Block>());
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitFirst()));
	processor.PopFrame();
	processor.ClearEvent();
	return pValue.release();
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

void ExprLink::ComposeInClass(Composer& composer, bool publicFlag)
{
	for (Expr* pExpr = GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeInClass(composer, publicFlag);
		if (Error::IsIssued()) return;
		composer.FlushDiscard();
	}
}

//------------------------------------------------------------------------------
// Expr_Empty
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Empty::typeInfo;

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

Iterator* Expr_Collector::EachChild() const
{
	return new Iterator_Expr(_pExprLinkElem->Reference());
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
// Expr_Value : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Value::typeInfo;

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
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Compose(Composer& composer)
{
	const Symbol* pSymbol = GetSymbol();
	Value* pValue = Basement::Inst.GetFrame().Lookup(pSymbol);
	if (pValue && pValue->IsType(VTYPE_Function)) {
		const Function& func = dynamic_cast<Value_Function*>(pValue)->GetFunction();
		if (func.IsTypeStatement()) {
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(new Expr_Identifier(pSymbol));
			func.Compose(composer, *pExprCaller);
			return;
		}
	}
	composer.Add_Lookup(pSymbol, this);					// [Value]
}

void Expr_Identifier::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	if (pOperator) {
		composer.Add_Lookup(GetSymbol(), this);				// [Any]
		pExprAssigned->ComposeOrNil(composer);				// [Any Right]
		composer.Add_BinaryOp(pOperator, this);				// [Assigned]
	} else {
		pExprAssigned->ComposeOrNil(composer);				// [Assigned]
	}
	composer.Add_AssignToSymbol(GetSymbol(), this);			// [Assigned]
}

void Expr_Identifier::ComposeInClass(Composer& composer, bool publicFlag)
{
	PropHandler::Flags flags = publicFlag? PropHandler::Flag::Public : 0;
	composer.Add_AssignPropHandler(GetSymbol(), flags, GetAttr(), true, this);
	composer.FlushDiscard();										// [VType]
}
	
void Expr_Identifier::ComposeForAssignmentInClass(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator, bool publicFlag)
{
	if (pOperator) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in property assigment");
		return;
	}
	PropHandler::Flags flags = publicFlag? PropHandler::Flag::Public : 0;
	pExprAssigned->ComposeOrNil(composer);							// [VType Value]
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
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Suffixed::typeInfo;

void Expr_Suffixed::Compose(Composer& composer)
{
}

String Expr_Suffixed::ToString(const StringStyle& ss) const
{
	String str;
	str += IsNumber()? GetSegmentSTL() : GetSegmentSTL().MakeQuoted(true);
	str += GetSuffix()->GetName();
	return str;
}

//------------------------------------------------------------------------------
// Expr_Embedded : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Embedded::typeInfo;

void Expr_Embedded::Compose(Composer& composer)
{
}

String Expr_Embedded::ToString(const StringStyle& ss) const
{
	String str;
	str += 'e';
	str += GetStringSTL().MakeQuoted(true);
	return str;
}

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo;

void Expr_UnaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		GetOperator()->ComposeUnary(composer, *this);				// [Result]
	} else {
		GetExprChild()->ComposeOrNil(composer);						// [Any]
		composer.Add_UnaryOp(GetOperator(), this);					// [Result]
	}
}

String Expr_UnaryOp::ToString(const StringStyle& ss) const
{
	String str;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpPreUnary: {
		bool requireParFlag = GetExprChild()->IsType<Expr_UnaryOp>() || GetExprChild()->IsType<Expr_BinaryOp>();
		str += GetOperator()->GetSymbol();
		if (requireParFlag) str += '(';
		str += GetExprChild()->ToString(ss);
		if (requireParFlag) str += ')';
		break;
	}
	case OpStyle::OpPostUnary: {
		if (GetExprChild()->IsType<Expr_Identifier>()) {
			const Expr_Identifier* pExprEx = dynamic_cast<const Expr_Identifier*>(GetExprChild());
			str += pExprEx->ToString(ss, GetOperator()->GetSymbol());
		} else if (GetExprChild()->IsType<Expr_Indexer>()) {
			const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(GetExprChild());
			str += pExprEx->ToString(ss, GetOperator()->GetSymbol());
		} else {
			bool requireParFlag = GetExprChild()->IsType<Expr_UnaryOp>() || GetExprChild()->IsType<Expr_BinaryOp>();
			if (requireParFlag) str += '(';
			str += GetExprChild()->ToString(ss);
			if (requireParFlag) str += ')';
			str += GetOperator()->GetSymbol();
		}
		break;
	}
	case OpStyle::MathUnary: {
		str += GetOperator()->GetSymbol();
		str += '(';
		str += GetExprChild()->ToString(ss);
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
const Expr::TypeInfo Expr_BinaryOp::typeInfo;

#if 0
bool Expr_BinaryOp::IsDeclArgWithDefault(Expr_Binary** ppExpr) const
{
	if (!GetOperator()->IsType(OpType::Pair)) return false;
	*ppExpr = const_cast<Expr_BinaryOp*>(this);
	return true;
}
#endif

void Expr_BinaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		GetOperator()->ComposeBinary(composer, *this);
	} else {
		GetExprLeft()->ComposeOrNil(composer);							// [Left]
		GetExprRight()->ComposeOrNil(composer);							// [Left Right]
		composer.Add_BinaryOp(GetOperator(), this);						// [Result]
	}
}

String Expr_BinaryOp::ToString(const StringStyle& ss) const
{
	String str;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpBinary: {
		do {
			bool needParenFlag =
				GetExprLeft()->IsType<Expr_BinaryOp>() || GetExprLeft()->IsType<Expr_UnaryOp>();
			if (needParenFlag) str += '(';
			str += GetExprLeft()->ToString(ss);
			if (needParenFlag) str += ')';
		} while (0);
		if (!ss.IsCram()) str += ' ';
		str += GetOperator()->GetSymbol();
		if (!ss.IsCram()) str += ' ';
		do {
			bool needParenFlag =
				GetExprRight()->IsType<Expr_BinaryOp>() || GetExprRight()->IsType<Expr_UnaryOp>();
			if (needParenFlag) str += '(';
			str += GetExprRight()->ToString(ss);
			if (needParenFlag) str += ')';
		} while (0);
		break;
	}
	case OpStyle::MathBinary: {
		str += GetOperator()->GetSymbol();
		str += '(';
		str += GetExprLeft()->ToString(ss);
		str += ss.GetComma();
		if (!ss.IsCram()) str += ' ';
		str += GetExprRight()->ToString(ss);
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
const Expr::TypeInfo Expr_Assign::typeInfo;

bool Expr_Assign::DoPrepare()
{
	if (GetExprLeft()->IsType<Expr_Caller>()) {
		Expr_Caller* pExprEx = dynamic_cast<Expr_Caller*>(GetExprLeft());
		return pExprEx->PrepareDeclCallable();
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
	GetExprLeft()->ComposeForAssignment(composer, GetExprRight(), GetOperator()); // [Assigned]
}

void Expr_Assign::ComposeInClass(Composer& composer, bool publicFlag)
{
	GetExprLeft()->ComposeForAssignmentInClass(composer, GetExprRight(), GetOperator(), publicFlag); // [Assigned]
}

void Expr_Assign::ComposeForArgSlot(Composer& composer)
{
	if (GetOperator() || !GetExprLeft()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::ArgumentError, *this,
						 "invalid declaration of named argument");
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprLeft())->GetSymbol();
	PUnit* pPUnitOfArgSlot = composer.PeekPUnitCont();
	composer.Add_BeginArgSlotNamed(
		pSymbol, GetExprRight()->Reference(), this);					// [Argument ArgSlot]
	GetExprRight()->ComposeOrNil(composer);								// [Argument ArgSlot Assigned]
	pPUnitOfArgSlot->SetPUnitSentinel(composer.PeekPUnitCont());
	composer.Add_EndArgSlotNamed(this);									// [Argument]
	pPUnitOfArgSlot->SetPUnitBranchDest(composer.PeekPUnitCont());
	GetExprRight()->SetPUnitFirst(pPUnitOfArgSlot);
}

String Expr_Assign::ToString(const StringStyle& ss) const
{
	String str;
	str += GetExprLeft()->ToString(ss);
	if (!ss.IsCram()) str += ' ';
	if (GetOperator()) str += GetOperator()->GetSymbol();
	str += '=';
	if (!ss.IsCram()) str += ' ';
	str += GetExprRight()->ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Member : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Member::typeInfo;

void Expr_Member::Compose(Composer& composer)
{
	GetExprTarget()->ComposeOrNil(composer);									// [Target]
	switch (GetMemberMode()) {
	case MemberMode::Normal: {
		composer.Add_Member_Normal(GetSymbol(), GetAttr().Reference(), this);	// [Member] or [Prop]
		break;
	}
	case MemberMode::MapAlong: {
		composer.Add_Member_MapAlong(GetSymbol(), GetAttr().Reference(), this);	// [Member] or [Prop]
		break;
	}
	case MemberMode::MapToList: {
		composer.Add_Member_MapToList(GetSymbol(), GetAttr().Reference(), this);// [Member] or [Prop]
		break;
	}
	case MemberMode::MapToIter: {
		composer.Add_Member_MapToIter(GetSymbol(), GetAttr().Reference(), this);// [Member] or [Prop]
		break;
	}
	default: {
		composer.Add_Member_Normal(GetSymbol(), GetAttr().Reference(), this);	// [Member] or [Prop]
		break;
	}
	}
}

void Expr_Member::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	GetExprTarget()->ComposeOrNil(composer);								// [Target]
	if (pOperator) {
		composer.Add_PropGet(GetSymbol(), GetAttr().Reference(), this);		// [Target Prop]
		pExprAssigned->ComposeOrNil(composer);								// [Target Prop Right]
		composer.Add_BinaryOp(pOperator, this);								// [Target Assigned]
	} else {
		pExprAssigned->ComposeOrNil(composer);								// [Target Assigned]
	}
	composer.Add_PropSet(GetSymbol(), GetAttr().Reference(), this);			// [Assigned]
}

String Expr_Member::ToString(const StringStyle& ss) const
{
	String str;
	str += GetExprTarget()->ToString(ss);
	str += MemberModeToSymbol(GetMemberMode())->GetName();
	str += GetSymbol()->ToString();
	str += GetAttr().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Expr_Root : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Root::typeInfo;

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
const Expr::TypeInfo Expr_Block::typeInfo;

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
		Expr::ComposeForArgSlot(composer, GetExprParamFirst());
		pPUnitSequence->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_Return(this);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	}
	ComposeSequence(composer, GetExprElemFirst());					// [Any]
}

bool Expr_Block::HasCallerAsParent() const
{
	RefPtr<Expr> pExprParent(LockExprParent());
	return pExprParent && pExprParent->IsType<Expr_Caller>();
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
const Expr::TypeInfo Expr_Iterer::typeInfo;

void Expr_Iterer::Compose(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, this);						// [List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [List Elem]
		composer.Add_ListElem(0, false);						// [List]
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
const Expr::TypeInfo Expr_Lister::typeInfo;

void Expr_Lister::Compose(Composer& composer)
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(nExprs, this);						// [List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [List Elem]
		composer.Add_ListElem(0, false, pExpr);					// [List]
	}	
}

void Expr_Lister::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
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
const Expr::TypeInfo Expr_Indexer::typeInfo;

void Expr_Indexer::Compose(Composer& composer)
{
	GetExprCar()->ComposeOrNil(composer);						// [Car]
	size_t nExprs = GetExprLinkCdr().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, this);	// [Index(Car)]
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [Index(Car) Cdr]
		composer.Add_FeedIndex(pExpr);							// [Index(Car)]
	}
	composer.Add_IndexGet(this);								// [Elems]
}

void Expr_Indexer::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	GetExprCar()->ComposeOrNil(composer);						// [Car]
	size_t nExprs = GetExprLinkCdr().CountSequence();
	composer.Add_Index(GetAttr().Reference(), nExprs, this);	// [Index(Car)]
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [Index(Car) Cdr]
		composer.Add_FeedIndex(pExpr);							// [Index(Car)]
	}
	if (pOperator) {
		
	} else {
		pExprAssigned->ComposeOrNil(composer);					// [Index(Car) Elems]
	}
	composer.Add_IndexSet(this);								// [Elems]
}

void Expr_Indexer::ComposeInClass(Composer& composer, bool publicFlag)
{
	if (!GetExprCar()->IsType<Expr_Identifier>() || HasExprCdr()) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid format of property declaration");
		return;
	}
	PropHandler::Flags flags = PropHandler::Flag::ListVar | (publicFlag? PropHandler::Flag::Public : 0);
	const Expr_Identifier* pExprCar = dynamic_cast<Expr_Identifier*>(GetExprCar());
	composer.Add_AssignPropHandler(pExprCar->GetSymbol(), flags, GetAttr(), true, this);
	composer.FlushDiscard();										// [VType]
}

void Expr_Indexer::ComposeForAssignmentInClass(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator, bool publicFlag)
{
	if (pOperator) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in property assigment");
		return;
	}
	if (!GetExprCar()->IsType<Expr_Identifier>() || HasExprCdr()) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "invalid format of property declaration");
		return;
	}
	PropHandler::Flags flags = PropHandler::Flag::ListVar | (publicFlag? PropHandler::Flag::Public : 0);
	const Expr_Identifier* pExprCar = dynamic_cast<Expr_Identifier*>(GetExprCar());
	pExprAssigned->ComposeOrNil(composer);							// [VType Value]
	composer.Add_AssignPropHandler(pExprCar->GetSymbol(), flags, GetAttr(), false, this);
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
const Expr::TypeInfo Expr_Caller::typeInfo;

void Expr_Caller::Compose(Composer& composer)
{
	RefPtr<DottedSymbol> pDottedSymbol(DottedSymbol::CreateFromExpr(*GetExprCar()));
	if (pDottedSymbol) {
		Value* pValue = Basement::Inst.GetFrame().Lookup(*pDottedSymbol);
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = Value_Function::GetFunction(*pValue);
			if (func.IsTypeStatement()) {
				func.Compose(composer, *this);						// [Result]
				return;
			}
		}
	}
	GetExprCar()->ComposeOrNil(composer);							// [Car]
	composer.Add_Argument(GetAttr().Reference(),
						  Expr_Block::Reference(GetExprOfBlock()), this); // [Argument]
	Expr::ComposeForArgSlot(composer, GetExprCdrFirst());			// [Argument]
	if (Error::IsIssued()) return;
	if (GetExprOfBlock()) {
		PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
		composer.Add_Jump(this);
		composer.ComposeAsSequence(*GetExprOfBlock());
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	}
	composer.Add_Call(this);										// [Result]
}

void Expr_Caller::ComposeInClass(Composer& composer, bool publicFlag)
{
	const char* errMsg = "invalid class definition";
	if (!GetExprCar()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, errMsg);
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprCar())->GetSymbol();
	if (!pSymbol->IsIdentical(Gurax_Symbol(public_)) || HasExprCdr()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, errMsg);
		return;
	}
	GetExprOfBlock()->GetExprLinkElem().ComposeInClass(composer, true);
}

void Expr_Caller::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	if (pOperator) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in function assigment");
		return;
	}
	RefPtr<Function> pFunction(CreateFunction(composer, pExprAssigned, false));
	if (!pFunction) return;
	composer.Add_AssignFunction(pFunction.release(), this);			// [Value]
}

void Expr_Caller::ComposeForAssignmentInClass(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator, bool publicFlag)
{
	if (pOperator) {
		Error::IssueWith(ErrorType::SyntaxError, *this,
						 "operator can not be applied in function assigment");
		return;
	}
	RefPtr<Function> pFunction(CreateFunction(composer, pExprAssigned, true));
	if (!pFunction) return;
	composer.Add_AssignMethod(pFunction.release(), this);
	composer.FlushDiscard();										// [VType]
}

Function* Expr_Caller::CreateFunction(Composer& composer, Expr* pExprAssigned, bool withinClassFlag)
{
	if (!GetExprCar()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, "identifier is expected");
		return nullptr;
	}
	const Expr_Identifier* pExprCarEx = dynamic_cast<const Expr_Identifier*>(GetExprCar());
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_Jump(this);
	pExprAssigned->SetPUnitFirst(composer.PeekPUnitCont());
	pExprAssigned->ComposeOrNil(composer);
	composer.Add_Return(this);
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		Expr_Binary* pExprEx = nullptr;
		if (!pExpr->IsDeclArgWithDefault(&pExprEx)) continue;
		Expr* pExprDefaultArg = pExprEx->GetExprRight();
		PUnit* pPUnitDefaultArg = composer.PeekPUnitCont();
		composer.Add_BeginSequence(pExprDefaultArg);
		pExprDefaultArg->ComposeOrNil(composer);
		pPUnitDefaultArg->SetPUnitSentinel(composer.PeekPUnitCont());
		composer.Add_Return(pExprDefaultArg);
		pExprDefaultArg->SetPUnitFirst(pPUnitDefaultArg);
	}
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	Function::Type type = withinClassFlag? Function::Type::Method : Function::Type::Function;
	return new FunctionCustom(type, pExprCarEx->GetSymbol(),
							  GetDeclCallable().Reference(), pExprAssigned->Reference());
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

void Expr_Caller::AppendExprTrailer(Expr_Caller* pExprTrailer)
{
#if 0
	if (_pExprOfBlock.IsNull()) {
		SetBlock(new Expr_Block());
		_implicitBlockFlag = true;
	}
	if (_implicitBlockFlag) {
		_pExprOfBlock->AddExpr(pExprCaller);
	} else {
		GetLastTrailer()->SetTrailer(pExprCaller);
	}
#endif
	GetExprTrailerLast()->SetExprTrailer(pExprTrailer);
}

Expr_Caller* Expr_Caller::GetExprTrailerLast()
{
	Expr_Caller* pExpr = this;
	for ( ; pExpr->GetExprTrailer() != nullptr; pExpr = pExpr->GetExprTrailer()) ;
	return pExpr;
}

const Expr* Expr_Caller::GetTrailerSymbols(SymbolList& symbols) const
{
	for (const Expr* pExpr = GetExprTrailer(); pExpr; ) {
		if (!pExpr->IsType<Expr_Caller>()) return pExpr;
		const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
		const Expr* pExprCar = pExprEx->GetExprCar();
		if (!pExprCar->IsType<Expr_Identifier>()) return pExprCar;
		const Expr_Identifier* pExprCarEx = dynamic_cast<const Expr_Identifier*>(pExprCar);
		symbols.push_back(pExprCarEx->GetSymbol());
		pExpr = pExprEx->GetExprTrailer();
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Iterator_Expr
//------------------------------------------------------------------------------
size_t Iterator_Expr::GetLength() const
{
	return _pExprLinkElem->CountSequence();
}

Value* Iterator_Expr::DoNextValue()
{
	if (!_pExprCur) return nullptr;
	RefPtr<Value> pValue(new Value_Expr(_pExprCur->Reference()));
	_pExprCur = _pExprCur->GetExprNext();
	return pValue.release();
}

String Iterator_Expr::ToString(const StringStyle& ss) const
{
	String str;
	str += "Expr";
	return str;
}

}
