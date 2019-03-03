//==============================================================================
// Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------
int Expr::CalcIndentLevel() const
{
	int indentLevel = 0;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), indentLevel++) ;
	return indentLevel;
}

String Expr::MakeIndent(const StringStyle& ss) const
{
	String rtn;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), rtn += ss.GetIndentUnit()) ;
	return rtn;
}

size_t Expr::CountSequence(const Expr* pExpr)
{
	size_t nExprs = 0;
	for ( ; pExpr; pExpr = pExpr->GetExprNext(), nExprs++) ;
	return nExprs;
}

void Expr::ComposeSequence(Composer& composer, const Expr* pExpr)
{
	const Expr* pExprPrev = nullptr;
	if (pExpr) {
		pExpr->Compose(composer);
		pExprPrev = pExpr;
		pExpr = pExpr->GetExprNext();
	}
	while (pExpr) {
		composer.Add_PopToDiscard(pExprPrev);
		pExpr->Compose(composer);
		pExprPrev = pExpr;
		pExpr = pExpr->GetExprNext();
	}
	// [Value]
}

void Expr::ComposeForArgSlot(Composer& composer, const Expr* pExpr)
{
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ComposeForArgSlot(composer);
		if (Error::IsIssued()) return;
	}
}

void Expr::ComposeForArgSlot(Composer& composer) const
{
	auto pPUnit = composer.AddF_ArgSlot(this);		// [ValueArgument]
	Compose(composer);								// [ValueArgument Value]
	composer.Add_FeedArgSlot(this);					// [ValueArgument]
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

void Expr::ComposeForAssignment(
	Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
	Error::IssueWith(ErrorType::InvalidOperation, Reference(), "invalid assignment");
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

void ExprList::Compose(Composer& composer) const
{
	const Expr* pExprPrev = nullptr;
	auto ppExpr = begin();
	if (ppExpr != end()) {
		const Expr* pExpr = *ppExpr++;
		pExpr->Compose(composer);
		pExprPrev = pExpr;
	}
	while (ppExpr != end()) {
		const Expr* pExpr = *ppExpr++;
		composer.Add_PopToDiscard(pExprPrev);
		pExpr->Compose(composer);
		pExprPrev = pExpr;
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
	for (const Expr* pExpr = GetExprHead(); pExpr; pExpr = pExpr->GetExprNext(), cnt++) ;
	return cnt;
}

void ExprLink::SetExprParent(const Expr* pExprParent)
{
	for (Expr* pExpr = GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->SetExprParent(pExprParent);
	}
}

bool ExprLink::Traverse(Expr::Visitor& visitor)
{
	for (Expr* pExpr = GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (!pExpr->Traverse(visitor)) return false;
	}
	return true;
}

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

void Expr_Value::Compose(Composer& composer) const
{
	composer.Add_Value(this, GetValue());	// [Value]
}

String Expr_Value::ToString(const StringStyle& ss) const
{
	return HasSource()? GetSourceSTL() : GetValue()->ToString();
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Compose(Composer& composer) const
{
	composer.Add_Lookup(this, GetSymbol());		// [Value]
}

void Expr_Identifier::ComposeForAssignment(
	Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
	if (pOperator) {
		composer.Add_Lookup(this, GetSymbol());			// [Value]
		pExprAssigned->Compose(composer);				// [Value ValueRight]
		composer.Add_BinaryOp(this, pOperator);			// [ValueAssigned]
	} else {
		pExprAssigned->Compose(composer);				// [ValueAssigned]
	}
	composer.Add_AssignToSymbol(this, GetSymbol());		// [ValueAssigned]
}

String Expr_Identifier::ToString(const StringStyle& ss, const char* strInsert) const
{
	String rtn;
	rtn += GetSymbol()->ToString();
	rtn += strInsert;
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Suffixed::typeInfo;

void Expr_Suffixed::Compose(Composer& composer) const
{
}

String Expr_Suffixed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += IsNumber()? GetSegmentSTL() : GetSegmentSTL().MakeQuoted(true);
	rtn += GetSuffix()->GetName();
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Embedded : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Embedded::typeInfo;

void Expr_Embedded::Compose(Composer& composer) const
{
}

String Expr_Embedded::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += 'e';
	rtn += GetStringSTL().MakeQuoted(true);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo;

void Expr_UnaryOp::Compose(Composer& composer) const
{
	GetExprChild()->Compose(composer);			// [Value]
	composer.Add_UnaryOp(this, GetOperator());	// [ValueResult]
}

String Expr_UnaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpPreUnary: {
		bool requireParFlag = GetExprChild()->IsType<Expr_UnaryOp>() || GetExprChild()->IsType<Expr_BinaryOp>();
		rtn += GetOperator()->GetSymbol();
		if (requireParFlag) rtn += '(';
		rtn += GetExprChild()->ToString(ss);
		if (requireParFlag) rtn += ')';
		break;
	}
	case OpStyle::OpPostUnary: {
		if (GetExprChild()->IsType<Expr_Identifier>()) {
			const Expr_Identifier* pExprEx = dynamic_cast<const Expr_Identifier*>(GetExprChild());
			rtn += pExprEx->ToString(ss, GetOperator()->GetSymbol());
		} else if (GetExprChild()->IsType<Expr_Indexer>()) {
			const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(GetExprChild());
			rtn += pExprEx->ToString(ss, GetOperator()->GetSymbol());
		} else {
			bool requireParFlag = GetExprChild()->IsType<Expr_UnaryOp>() || GetExprChild()->IsType<Expr_BinaryOp>();
			if (requireParFlag) rtn += '(';
			rtn += GetExprChild()->ToString(ss);
			if (requireParFlag) rtn += ')';
			rtn += GetOperator()->GetSymbol();
		}
		break;
	}
	case OpStyle::MathUnary: {
		rtn += GetOperator()->GetSymbol();
		rtn += '(';
		rtn += GetExprChild()->ToString(ss);
		rtn += ')';
		break;
	}
	default:
		break;
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_BinaryOp : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_BinaryOp::typeInfo;

void Expr_BinaryOp::Compose(Composer& composer) const
{
	GetExprLeft()->Compose(composer);			// [ValueLeft]
	GetExprRight()->Compose(composer);			// [ValueLeft ValueRight]
	composer.Add_BinaryOp(this, GetOperator());	// [ValueResult]
}

void Expr_BinaryOp::ComposeForArgSlot(Composer& composer) const
{
	if (!GetOperator()->IsType(OpType::Pair)) {
		Expr::ComposeForArgSlot(composer);
		return;
	}
	if (!GetExprLeft()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::ArgumentError, Reference(),
						 "named argument must be specified by a symbol");
		return;
	}
	const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprLeft())->GetSymbol();
	auto pPUnit = composer.AddF_ArgSlotNamed(this, pSymbol, GetExprRight());
													// [ValueArgument ValueArgSlot]
	GetExprRight()->Compose(composer);				// [ValueArgument ValueArgSlot Value]
	composer.Add_FeedArgSlotNamed(this);			// [ValueArgument]
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

String Expr_BinaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpBinary: {
		rtn += '(';
		rtn += GetExprLeft()->ToString(ss);
		rtn += ')';
		if (!ss.IsCram()) rtn += ' ';
		rtn += GetOperator()->GetSymbol();
		if (!ss.IsCram()) rtn += ' ';
		rtn += '(';
		rtn += GetExprRight()->ToString(ss);
		rtn += ')';
		break;
	}
	case OpStyle::MathBinary: {
		rtn += GetOperator()->GetSymbol();
		rtn += '(';
		rtn += GetExprLeft()->ToString(ss);
		rtn += ss.GetComma();
		if (!ss.IsCram()) rtn += ' ';
		rtn += GetExprRight()->ToString(ss);
		rtn += ')';
		break;
	}
	default:
		break;
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Assign : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Assign::typeInfo;

bool Expr_Assign::DoPrepare()
{
	if (GetExprLeft()->IsType<Expr_Caller>()) {
		Expr_Caller*pExprEx = dynamic_cast<Expr_Caller*>(GetExprLeft());
		return pExprEx->PrepareDeclCallable();
	}
	return true;
}

void Expr_Assign::Compose(Composer& composer) const
{
	GetExprLeft()->ComposeForAssignment(composer, GetExprRight(), GetOperator()); // [ValueAssigned]
}

String Expr_Assign::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetExprLeft()->ToString(ss);
	if (!ss.IsCram()) rtn += ' ';
	if (GetOperator()) rtn += GetOperator()->GetSymbol();
	rtn += '=';
	if (!ss.IsCram()) rtn += ' ';
	rtn += GetExprRight()->ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Member : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Member::typeInfo;

void Expr_Member::Compose(Composer& composer) const
{
	GetExprTarget()->Compose(composer);						// [ValueTarget]
	composer.Add_Member(this, GetSymbol(), GetAttr());		// [ValueMember] or [ValueProp]
}

void Expr_Member::ComposeForAssignment(
	Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
	GetExprTarget()->Compose(composer);						// [ValueTarget]
	if (pOperator) {
		composer.Add_PropGet(this, GetSymbol(), GetAttr());	// [ValueTarget ValueProp]
		pExprAssigned->Compose(composer);					// [ValueTarget ValueProp ValueRight]
		composer.Add_BinaryOp(this, pOperator);				// [ValueTarget ValueAssigned]
	} else {
		pExprAssigned->Compose(composer);					// [ValueTarget ValueAssigned]
	}
	composer.Add_PropSet(this, GetSymbol(), GetAttr());		// [ValueAssigned]
}

String Expr_Member::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetExprTarget()->ToString(ss);
	rtn += MemberModeToSymbol(GetMemberMode())->GetName();
	rtn += GetSymbol()->ToString();
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Root : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Root::typeInfo;

void Expr_Root::Compose(Composer& composer) const
{
	ComposeSequence(composer, GetExprElemHead());			// [Value]
}

String Expr_Root::ToString(const StringStyle& ss) const
{
	String rtn;
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			rtn += indent;
			rtn += pExpr->ToString(ss);
			rtn += '\n';
		}
	} else {
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				rtn += ';';
				if (!ss.IsCram()) rtn += ' ';
			}
			rtn += pExpr->ToString(ss);
		}
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Block::typeInfo;

bool Expr_Block::DoPrepare()
{
	return PrepareDeclCallable();
}

void Expr_Block::Compose(Composer& composer) const
{
	ComposeSequence(composer, GetExprElemHead());			// [Value]
}

String Expr_Block::ToString(const StringStyle& ss) const
{
	String rtn;
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		rtn += indent;
		rtn += '{';
		if (HasExprParam()) {
			rtn += '|';
			bool firstFlag = true;
			for (const Expr* pExpr = GetExprParamHead(); pExpr; pExpr = pExpr->GetExprNext()) {
				if (firstFlag) {
					firstFlag = false;
				} else {
					rtn += ',';
					if (!ss.IsCram()) rtn += ' ';
				}
				rtn += pExpr->ToString(ss);
			}
			rtn += '|';
		}
		rtn += '\n';
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			rtn += indentDown;
			rtn += pExpr->ToString(ss);
			rtn += '\n';
		}
		rtn += indent;
		rtn += "}\n";
	} else {
		rtn += '{';
		if (HasExprParam()) {
			rtn += '|';
			bool firstFlag = true;
			for (const Expr* pExpr = GetExprParamHead(); pExpr; pExpr = pExpr->GetExprNext()) {
				if (firstFlag) {
					firstFlag = false;
				} else {
					rtn += ',';
					if (!ss.IsCram()) rtn += ' ';
				}
				rtn += pExpr->ToString(ss);
			}
			rtn += '|';
			if (!ss.IsCram() && HasExprElem()) rtn += ' ';
		}
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				rtn += ';';
				if (!ss.IsCram()) rtn += ' ';
			}
			rtn += pExpr->ToString(ss);
		}
		rtn += '}';
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Iterer : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Iterer::typeInfo;

void Expr_Iterer::Compose(Composer& composer) const
{
}

String Expr_Iterer::ToString(const StringStyle& ss) const
{
	String rtn;
	if (GetExprLinkElem().CountSequence() == 1) {
		rtn += '(';
		rtn += GetExprLinkElem().GetExprHead()->ToString(ss);
		rtn += ",)";
	} else if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		rtn += indent;
		rtn += "(\n";
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			rtn += indentDown;
			rtn += pExpr->ToString(ss);
			rtn += '\n';
		}
		rtn += indent;
		rtn += ")\n";
	} else {
		rtn += '(';
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				rtn += ',';
				if (!ss.IsCram()) rtn += ' ';
			}
			rtn += pExpr->ToString(ss);
		}
		rtn += ')';
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Lister::typeInfo;

void Expr_Lister::Compose(Composer& composer) const
{
	size_t nExprs = GetExprLinkElem().CountSequence();
	composer.Add_CreateList(this, nExprs);					// [ValueList]
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);							// [ValueList Value]
		composer.Add_AddList(this);							// [ValueList]
	}	
}

void Expr_Lister::ComposeForAssignment(
	Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
}

String Expr_Lister::ToString(const StringStyle& ss) const
{
	String rtn;
	if (ss.IsMultiLine()) {
		String indent = MakeIndent(ss);
		String indentDown = indent;
		indentDown += ss.GetIndentUnit();
		rtn += indent;
		rtn += "[\n";
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			rtn += indentDown;
			rtn += pExpr->ToString(ss);
			rtn += '\n';
		}
		rtn += indent;
		rtn += "]\n";
	} else {
		rtn += '[';
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				rtn += ',';
				if (!ss.IsCram()) rtn += ' ';
			}
			rtn += pExpr->ToString(ss);
		}
		rtn += ']';
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Indexer::typeInfo;

void Expr_Indexer::Compose(Composer& composer) const
{
	GetExprCar()->Compose(composer);						// [ValueCar]
	size_t nExprs = GetExprLinkCdr().CountSequence();
	composer.Add_Index(this, GetAttr(), nExprs);			// [ValueIndex]
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);							// [ValueIndex Value]
		composer.Add_FeedIndex(this);						// [ValueIndex]
	}
	composer.Add_IndexGet(this);							// [ValueElems]
}

void Expr_Indexer::ComposeForAssignment(
	Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
}

String Expr_Indexer::ToString(const StringStyle& ss, const char* strInsert) const
{
	String rtn;
	rtn += _pExprCar->ToString(ss);
	rtn += '[';
	bool firstFlag = true;
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (firstFlag) {
			firstFlag = false;
		} else {
			rtn += ',';
			if (!ss.IsCram()) rtn += ' ';
		}
		rtn += pExpr->ToString(ss);
	}
	rtn += ']';
	rtn += strInsert;
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Caller::typeInfo;

void Expr_Caller::Compose(Composer& composer) const
{
	if (GetExprCar()->IsType<Expr_Identifier>()) {
		const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprCar())->GetSymbol();
		Value* pValue = Context::GetFrame().LookupValue(pSymbol);
		if (pValue && pValue->IsType(VTYPE_Function)) {
			const Function& func = dynamic_cast<Value_Function*>(pValue)->GetFunction();
			if (func.IsTypeStatement()) {
				func.Compose(composer, this);				// [ValueResult]
				return;
			}
		}
	}
	GetExprCar()->Compose(composer);						// [ValueCar]
	composer.Add_Argument(this, GetAttr());					// [ValueArgument]
	Expr::ComposeForArgSlot(composer, GetExprCdrHead());	// [ValueArgument]
	if (Error::IsIssued()) return;
	composer.Add_Call(this);								// [ValueResult]
}

void Expr_Caller::ComposeForAssignment(
	Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
	if (pOperator) {
		Error::IssueWith(ErrorType::SyntaxError, Reference(), "operator can not be applied in function assigment");
		return;
	}
	if (GetExprCar()->IsType<Expr_Identifier>()) {
		Error::IssueWith(ErrorType::SyntaxError, Reference(), "identifier is expected");
		return;
	}
	const Expr_Identifier* pExprCarEx = dynamic_cast<const Expr_Identifier*>(GetExprCar());
	RefPtr<Function> pFunction(
		new FunctionCustom(Function::Type::Function, pExprCarEx->GetSymbol(), GetDeclCallable().Reference()));
	composer.Add_AssignFunction(this, pFunction.get());		// [Value]
}

String Expr_Caller::ToString(const StringStyle& ss) const
{
	bool argListFlag = HasExprCdr() || !GetAttr().IsEmpty() || !HasExprBlock();
	String rtn;
	rtn += _pExprCar->ToString(ss);
	if (argListFlag) {
		if (!ss.IsCram() && _pExprCar->IsType<Expr_Identifier>() &&
			dynamic_cast<Expr_Identifier*>(_pExprCar.get())->GetSymbol()->IsFlowControl()) {
			rtn += ' ';
		}
		rtn += '(';
		bool firstFlag = true;
		for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				rtn += ',';
				if (!ss.IsCram()) rtn += ' ';
			}
			rtn += pExpr->ToString(ss);
		}
		rtn += ')';
	}
	rtn += GetAttr().ToString(ss);
	if (HasExprBlock()) {
		if (!ss.IsCram()) rtn += ' ';
		rtn += GetExprBlock()->ToString(ss);
	}
	if (HasExprTrailer()) {
		if (!ss.IsCram()) rtn += ' ';
		rtn += GetExprTrailer()->ToString(ss);
	}
	return rtn;
}

void Expr_Caller::SetExprTrailer(Expr_Caller* pExprTrailer)
{
	_pExprTrailer.reset(pExprTrailer);
	if (_pExprTrailer) _pExprTrailer->SetExprParent(this);
}

void Expr_Caller::AppendExprTrailer(Expr_Caller* pExprTrailer)
{
#if 0
	if (_pExprBlock.IsNull()) {
		SetBlock(new Expr_Block());
		_implicitBlockFlag = true;
	}
	if (_implicitBlockFlag) {
		_pExprBlock->AddExpr(pExprCaller);
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

}
