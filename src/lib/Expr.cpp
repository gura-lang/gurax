//==============================================================================
// Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------
const Expr* Expr::Empty = nullptr;

void Expr::Bootup()
{
	Empty = new Expr_Empty();
}

Value* Expr::DoEval(Processor& processor) const
{
	if (!GetPUnitTop()) return Value::nil();
	processor.PushPUnit(nullptr);	// push a terminator so that Return exits the loop
	processor.RunLoop(GetPUnitTop());
	return Error::IsIssued()? Value::nil() : processor.PopValue();
}

void Expr::ComposeOrNil(Composer& composer)
{
	auto pPUnitMarked = composer.PeekPUnitCont();
	Compose(composer);
	if (pPUnitMarked == composer.PeekPUnitCont()) { // when nothing has been yielded
		composer.Add_Value(*this, Value::nil());
	}
}

Iterator* Expr::EachPUnit() const
{
	const PUnit* pPUnitExit = nullptr;
	const PUnit* pPUnit = GetPUnitTop();
	if (pPUnit && pPUnit->GetPUnitExit()) {
		pPUnitExit = pPUnit->GetPUnitExit();
		pPUnit = pPUnit->GetPUnitCont();	// skip PUnit_ExitPoint
	}
	return new Iterator_EachPUnit(pPUnit, pPUnitExit, true);
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

void Expr::ComposeSequence(Composer& composer, Expr* pExpr)
{
	if (pExpr) {
		pExpr->Compose(composer);
		pExpr = pExpr->GetExprNext();
	}
	while (pExpr) {
		composer.Flush(true);
		pExpr->Compose(composer);
		pExpr = pExpr->GetExprNext();
	}
	// [Value]
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
	auto pPUnitOfBranch = composer.Add_ArgSlot(*this);				// [Argument]
	SetPUnitTop(composer.PeekPUnitCont());
	auto pPUnitOfExitPoint = composer.Add_ExitPoint(*this);			// [Argument]
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	Compose(composer);												// [Argument Any]
	pPUnitOfExitPoint->SetPUnitExit(composer.PeekPUnitCont());
	composer.Add_FeedArgSlot(*this);								// [Argument]
	pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
}

void Expr::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	Error::IssueWith(ErrorType::InvalidOperation, *this, "invalid assignment");
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
		composer.Flush(true);
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
	composer.Add_Value(*this, GetValue()->Clone());	// [Value]
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
	Value* pValue = Context::GetFrame().Lookup(pSymbol);
	if (pValue && pValue->IsType(VTYPE_Function)) {
		const Function& func = dynamic_cast<Value_Function*>(pValue)->GetFunction();
		if (func.IsTypeStatement()) {
			RefPtr<Expr_Caller> pExprCaller(new Expr_Caller());
			pExprCaller->SetExprCar(new Expr_Identifier(pSymbol));
			func.Compose(composer, *pExprCaller);
			return;
		}
	}
	composer.Add_Lookup(*this, pSymbol);					// [Value]
}

void Expr_Identifier::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	if (pOperator) {
		composer.Add_Lookup(*this, GetSymbol());			// [Any]
		pExprAssigned->ComposeOrNil(composer);				// [Any Right]
		composer.Add_BinaryOp(*this, pOperator);			// [Assigned]
	} else {
		pExprAssigned->ComposeOrNil(composer);				// [Assigned]
	}
	composer.Add_AssignToSymbol(*this, GetSymbol());		// [Assigned]
}

String Expr_Identifier::ToString(const StringStyle& ss, const char* strInsert) const
{
	String str;
	str += GetSymbol()->ToString();
	str += strInsert;
	str += GetAttr().ToString(ss);
	return str;
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
		auto pPUnitOfBranch = composer.Add_ValueAndJump(
			*this, new Value_Expr(GetExprChild()->Reference()));	// [Any]
		GetExprChild()->SetPUnitTop(composer.PeekPUnitCont());
		GetExprChild()->ComposeOrNil(composer);						// [Any]
		composer.Add_Return(*this);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	} else {
		GetExprChild()->ComposeOrNil(composer);						// [Any]
	}
	composer.Add_UnaryOp(*this, GetOperator());						// [Result]
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

void Expr_BinaryOp::Compose(Composer& composer)
{
	if (GetOperator()->GetRawFlag()) {
		do {
			auto pPUnitOfBranch = composer.Add_ValueAndJump(
				*this, new Value_Expr(GetExprLeft()->Reference()));		// [Left]
			GetExprLeft()->SetPUnitTop(composer.PeekPUnitCont());
			GetExprLeft()->ComposeOrNil(composer);						// [Any]
			composer.Add_Return(*this);
			pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		} while (0);
		do {
			auto pPUnitOfBranch = composer.Add_ValueAndJump(
				*this, new Value_Expr(GetExprRight()->Reference()));	// [Left Right]
			GetExprRight()->SetPUnitTop(composer.PeekPUnitCont());
			GetExprRight()->ComposeOrNil(composer);						// [Any]
			composer.Add_Return(*this);
			pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
		} while (0);
	} else {
		GetExprLeft()->ComposeOrNil(composer);							// [Left]
		GetExprRight()->ComposeOrNil(composer);							// [Left Right]
	}
	composer.Add_BinaryOp(*this, GetOperator());						// [Result]
}

void Expr_BinaryOp::ComposeForArgSlot(Composer& composer)
{
	if (!GetOperator()->IsType(OpType::Pair)) {
		Expr::ComposeForArgSlot(composer);
		return;
	}
	if (!GetExprLeft()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::ArgumentError, *this,
						 "named argument must be specified by a symbol");
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprLeft())->GetSymbol();
	auto pPUnitOfBranch = composer.Add_ArgSlotNamed(
		*this, pSymbol, GetExprRight()->Reference());					// [Argument ArgSlot]
	GetExprRight()->SetPUnitTop(composer.PeekPUnitCont());
	auto pPUnitOfExitPoint = composer.Add_ExitPoint(*this);				// [Argument ArgSlot]
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	GetExprRight()->ComposeOrNil(composer);								// [Argument ArgSlot Assigned]
	pPUnitOfExitPoint->SetPUnitExit(composer.PeekPUnitCont());
	composer.Add_FeedArgSlotNamed(*this);								// [Argument]
	pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
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

void Expr_Assign::Compose(Composer& composer)
{
	GetExprLeft()->ComposeForAssignment(composer, GetExprRight(), GetOperator()); // [Assigned]
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
	GetExprTarget()->ComposeOrNil(composer);								// [Target]
	composer.Add_Member(*this, GetSymbol(), GetAttr().Reference());			// [Member] or [Prop]
}

void Expr_Member::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	GetExprTarget()->ComposeOrNil(composer);								// [Target]
	if (pOperator) {
		composer.Add_PropGet(*this, GetSymbol(), GetAttr().Reference());	// [Target Prop]
		pExprAssigned->ComposeOrNil(composer);								// [Target Prop Right]
		composer.Add_BinaryOp(*this, pOperator);							// [Target Assigned]
	} else {
		pExprAssigned->ComposeOrNil(composer);								// [Target Assigned]
	}
	composer.Add_PropSet(*this, GetSymbol(), GetAttr().Reference());		// [Assigned]
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
	ComposeSequence(composer, GetExprElemFirst());						// [Any]
	composer.Add_Return(*this);
	composer.Add_Terminate(*this);
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
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
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
	return PrepareDeclCallable();
}

void Expr_Block::Compose(Composer& composer)
{
	ComposeSequence(composer, GetExprElemFirst());						// [Any]
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
			bool firstFlag = true;
			for (const Expr* pExpr = GetExprParamFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
				if (firstFlag) {
					firstFlag = false;
				} else {
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
			bool firstFlag = true;
			for (const Expr* pExpr = GetExprParamFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
				if (firstFlag) {
					firstFlag = false;
				} else {
					str += ',';
					if (!ss.IsCram()) str += ' ';
				}
				str += pExpr->ToString(ss);
			}
			str += '|';
			if (!ss.IsCram() && HasExprElem()) str += ' ';
		}
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				str += ';';
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
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
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
	composer.Add_CreateList(*this, nExprs);						// [List]
	for (Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [List Elem]
		composer.Add_ListElem(*this, 0);						// [List]
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
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
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
	composer.Add_Index(*this, GetAttr().Reference(), nExprs);	// [Index(Car)]
	for (Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeOrNil(composer);							// [Index(Car) Assigned]
		composer.Add_FeedIndex(*this);							// [Index(Car)]
	}
	composer.Add_IndexGet(*this);								// [Elems]
}

void Expr_Indexer::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
}

String Expr_Indexer::ToString(const StringStyle& ss, const char* strInsert) const
{
	String str;
	str += _pExprCar->ToString(ss);
	str += '[';
	bool firstFlag = true;
	for (const Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (firstFlag) {
			firstFlag = false;
		} else {
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
	if (GetExprCar()->IsType<Expr_Identifier>()) {
		const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprCar())->GetSymbol();
		Value* pValue = Context::GetFrame().Lookup(pSymbol);
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = dynamic_cast<Value_Function*>(pValue)->GetFunction();
			if (func.IsTypeStatement()) {
				func.Compose(composer, *this);						// [Result]
				return;
			}
		}
	}
	GetExprCar()->ComposeOrNil(composer);							// [Car]
	composer.Add_Argument(*this, GetAttr().Reference(),
						  Expr_Block::Reference(GetExprOfBlock()));	// [Argument]
	Expr::ComposeForArgSlot(composer, GetExprCdrFirst());			// [Argument]
	if (Error::IsIssued()) return;
	if (GetExprOfBlock()) {
		auto pPUnitOfBranch = composer.Add_Jump(*this);
		GetExprOfBlock()->SetPUnitTop(composer.PeekPUnitCont());
		GetExprOfBlock()->ComposeOrNil(composer);
		composer.Add_Return(*this);
		pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	}
	composer.Add_Call(*this);										// [Result]
}

void Expr_Caller::ComposeForAssignment(
	Composer& composer, Expr* pExprAssigned, const Operator* pOperator)
{
	if (pOperator) {
		Error::IssueWith(ErrorType::SyntaxError, *this, "operator can not be applied in function assigment");
		return;
	}
	if (!GetExprCar()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::SyntaxError, *this, "identifier is expected");
		return;
	}
	const Expr_Identifier* pExprCarEx = dynamic_cast<const Expr_Identifier*>(GetExprCar());
	RefPtr<FunctionCustom> pFunction(
		new FunctionCustom(Function::Type::Function, pExprCarEx->GetSymbol(), GetDeclCallable().Reference()));
	auto pPUnitOfBranch = composer.Add_AssignFunction(*this, pFunction->Reference());	// [Value]
	pFunction->SetPUnitBody(composer.PeekPUnitCont());
	pExprAssigned->ComposeOrNil(composer);
	composer.Add_Return(*this);
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
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
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprCdrFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
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

}
