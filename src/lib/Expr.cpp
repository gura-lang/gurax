//==============================================================================
// Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------
void Expr::ExecInArgument() const
{
	do {
		Argument& argument = dynamic_cast<Value_Argument*>(Context::PeekStack(0))->GetArgument();
		ArgSlot* pArgSlot = argument.GetArgSlotToFeed(); // this may be nullptr
		if (!pArgSlot) {
			Error::Issue(ErrorType::ArgumentError, "too many arguments");
			return;
		}
		if (!pArgSlot->IsVacant()) {
			Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
			return;
		}
		if (pArgSlot->IsVType(VTYPE_Quote)) {
			argument.FeedValue(new Value_Expr(Reference()));
			return;
		}
	} while (0);
	do {
		Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValue(Context::PopStack());
		Argument& argument = dynamic_cast<Value_Argument*>(Context::PeekStack(0))->GetArgument();
		argument.FeedValue(pValue.release());
	} while (0);
}

int Expr::CalcIndentLevel() const
{
	int indentLevel = 0;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), indentLevel++) ;
	return indentLevel;
}

String Expr::ComposeIndent(const StringStyle& ss) const
{
	String rtn;
	for (RefPtr<Expr> pExpr(Reference()); pExpr; pExpr.reset(pExpr->LockExprParent()), rtn += ss.GetIndentUnit()) ;
	return rtn;
}

void Expr::ExecInAssignment(const Expr* pExprAssigned, const Operator* pOperator) const
{
	Error::Issue(ErrorType::InvalidOperation, "invalid assignment");
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

void ExprList::Exec() const
{
	for (const Expr* pExpr : *this) {
		do {
			pExpr->Exec();
			if (Error::IsIssued()) return;
		} while (0);
		Value::Delete(Context::PopStack());
	}
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
size_t ExprLink::GetSize() const
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

void Expr_Value::Exec() const
{
	Context::PushStack(GetValue()->Clone());
}

String Expr_Value::ToString(const StringStyle& ss) const
{
	return HasSource()? GetSourceSTL() : GetValue()->ToString();
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Exec() const
{
	do {
		const Value* pValue = Context::GetFrame().LookupValue(GetSymbol());
		if (!pValue) {
			Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
			return;
		}
		Context::PushStack(pValue->Reference());
	} while (0);
}

void Expr_Identifier::ExecInAssignment(const Expr* pExprAssigned, const Operator* pOperator) const
{
	if (pOperator) {
		do {
			const Value* pValue = Context::GetFrame().LookupValue(GetSymbol());
			if (!pValue) {
				Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
				return;
			}
			Context::PushStack(pValue->Reference());
		} while (0);
		do {
			pExprAssigned->Exec();
			if (Error::IsIssued()) return;
		} while (0);
		do {
			RefPtr<Value> pValueRight(Context::PopStack());
			RefPtr<Value> pValueLeft(Context::PopStack());
			RefPtr<Value> pValue(pOperator->EvalBinary(pValueLeft.release(), pValueRight.release()));
			if (!pValue) return;
			Context::PushStack(pValue.release());
		} while (0);
		do {
			RefPtr<Value> pValueAssigned(Context::PeekStack(0)->Reference());
			Context::GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
		} while (0);
	} else {
		do {
			pExprAssigned->Exec();
			if (Error::IsIssued()) return;
		} while (0);
		do {
			RefPtr<Value> pValueAssigned(Context::PeekStack(0)->Reference());
			Context::GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
		} while (0);
	}
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

void Expr_Suffixed::Exec() const
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

void Expr_Embedded::Exec() const
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

void Expr_UnaryOp::Exec() const
{
	do {
		GetExprChild()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValueChild(Context::PopStack());
		RefPtr<Value> pValue(GetOperator()->EvalUnary(pValueChild.release()));
		if (!pValue) return;
		Context::PushStack(pValue.release());
	} while (0);
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

void Expr_BinaryOp::Exec() const
{
	do {
		GetExprLeft()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		GetExprRight()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValueRight(Context::PopStack());
		RefPtr<Value> pValueLeft(Context::PopStack());
		RefPtr<Value> pValue(GetOperator()->EvalBinary(pValueLeft.release(), pValueRight.release()));
		if (!pValue) return;
		Context::PushStack(pValue.release());
	} while (0);
}

void Expr_BinaryOp::ExecInArgument() const
{
	if (!GetOperator()->IsType(OpType::Pair)) {
		Expr_Binary::ExecInArgument();
		return;
	} else if (!GetExprLeft()->IsType<Expr_Identifier>()) {
		Error::Issue(ErrorType::ArgumentError, "named argument must be specified by a symbol");
		return;
	}
	do {
		Argument& argument = dynamic_cast<Value_Argument*>(Context::PeekStack(0))->GetArgument();
		const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(GetExprLeft())->GetSymbol();
		ArgSlot* pArgSlot = argument.FindArgSlot(pSymbol);
		if (!pArgSlot) {
			Error::Issue(ErrorType::ArgumentError, "can't find argument with a name: %s", pSymbol->GetName());
			return;
		}
		if (!pArgSlot->IsVacant()) {
			Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
			return;
		}
		if (pArgSlot->IsVType(VTYPE_Quote)) {
			pArgSlot->FeedValue(new Value_Expr(GetExprRight()->Reference()));
			return;
		}
		Context::PushStack(new Value_ArgSlot(pArgSlot->Reference()));
	} while (0);
	do {
		GetExprRight()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValue(Context::PopStack());
		ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(Context::PopStack())->GetArgSlot();
		argSlot.FeedValue(pValue.release());
	} while (0);
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
		return pExprEx->PrepareDeclCaller();
	}
	return true;
}

void Expr_Assign::Exec() const
{
	GetExprLeft()->ExecInAssignment(GetExprRight(), GetOperator());
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

void Expr_Member::Exec() const
{
	do {
		GetExprTarget()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValueTarget(Context::PopStack());
		Value* pValue = pValueTarget->LookupPropValue(GetSymbol(), GetAttr());
		if (!pValue) {
			Error::Issue(ErrorType::ValueError, "undefined symbol: %s", GetSymbol()->GetName());
			return;
		}
		if (pValue->IsCallable()) {
			Context::PushStack(new Value_Member(pValueTarget.release(), pValue->Reference()));
		} else {
			Context::PushStack(pValue->Reference());
		}
	} while (0);
}

void Expr_Member::ExecInAssignment(const Expr* pExprAssigned, const Operator* pOperator) const
{
	do {
		GetExprTarget()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	if (pOperator) {
		do {
			Value* pValueTarget = Context::PeekStack(0);
			Value* pValue = pValueTarget->LookupPropValue(GetSymbol(), GetAttr());
			if (!pValue) {
				Error::Issue(ErrorType::ValueError, "undefined symbol: %s", GetSymbol()->GetName());
				return;
			}
			Context::PushStack(pValue->Reference());
		} while (0);
		do {
			pExprAssigned->Exec();
			if (Error::IsIssued()) return;
		} while (0);
		do {
			RefPtr<Value> pValueRight(Context::PopStack());
			RefPtr<Value> pValueLeft(Context::PopStack());
			RefPtr<Value> pValue(pOperator->EvalBinary(pValueLeft.release(), pValueRight.release()));
			if (!pValue) return;
			Context::PushStack(pValue.release());
		} while (0);
	} else {
		do {
			pExprAssigned->Exec();
			if (Error::IsIssued()) return;
		} while (0);
	}
	do {
		RefPtr<Value> pValueAssigned(Context::PopStack());
		RefPtr<Value> pValueTarget(Context::PopStack());
		pValueTarget->AssignPropValue(GetSymbol(), pValueAssigned->Reference(), GetAttr());
		Context::PushStack(pValueAssigned.release());
	} while (0);
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

void Expr_Root::Exec() const
{
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Exec();
		if (Error::IsIssued()) return;
		Value::Delete(Context::PopStack());
	}
}

String Expr_Root::ToString(const StringStyle& ss) const
{
	String rtn;
	if (ss.IsMultiLine()) {
		String indent = ComposeIndent(ss);
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

void Expr_Block::Exec() const
{
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Exec();
		if (Error::IsIssued()) return;
		Value::Delete(Context::PopStack());
	}
}

String Expr_Block::ToString(const StringStyle& ss) const
{
	String rtn;
	if (ss.IsMultiLine()) {
		String indent = ComposeIndent(ss);
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

void Expr_Iterer::Exec() const
{
	do {
		RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
		pValueTypedOwner->Reserve(GetExprLinkElem().GetSize());
		Context::PushStack(new Value_Iterator(new Iterator_Each(pValueTypedOwner.release())));
	} while (0);
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		do {
			pExpr->Exec();
			if (Error::IsIssued()) return;
		} while (0);
		do {
			RefPtr<Value> pValue(Context::PopStack());
			Iterator& iterator =
				dynamic_cast<Value_Iterator*>(Context::PeekStack(0))->GetIterator();
			ValueTypedOwner& valueTypedOwner =
				dynamic_cast<Iterator_Each*>(&iterator)->GetValueTypedOwner();
			valueTypedOwner.Add(pValue.release());
		} while (0);
	}
}

String Expr_Iterer::ToString(const StringStyle& ss) const
{
	String rtn;
	if (GetExprLinkElem().GetSize() == 1) {
		rtn += '(';
		rtn += GetExprLinkElem().GetExprHead()->ToString(ss);
		rtn += ",)";
	} else if (ss.IsMultiLine()) {
		String indent = ComposeIndent(ss);
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

void Expr_Lister::Exec() const
{
	do {
		RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
		pValueTypedOwner->Reserve(GetExprLinkElem().GetSize());
		Context::PushStack(new Value_List(pValueTypedOwner.release()));
	} while (0);
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		do {
			pExpr->Exec();
			if (Error::IsIssued()) return;
		} while (0);
		do {
			RefPtr<Value> pValue(Context::PopStack());
			ValueTypedOwner& valueTypedOwner =
				dynamic_cast<Value_List*>(Context::PeekStack(0))->GetValueTypedOwner();
			valueTypedOwner.Add(pValue.release());
		} while (0);
	}
}

void Expr_Lister::ExecInAssignment(const Expr* pExprAssigned, const Operator* pOperator) const
{
}

String Expr_Lister::ToString(const StringStyle& ss) const
{
	String rtn;
	if (ss.IsMultiLine()) {
		String indent = ComposeIndent(ss);
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

void Expr_Indexer::Exec() const
{
	do {
		GetExprCar()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValueCar(Context::PopStack());
		RefPtr<Argument> pArgument(
			new Argument(DeclCaller::Empty->Reference(), GetAttr().Reference(), Value::nil(), pValueCar.release()));
		Context::PushStack(new Value_Argument(pArgument.release()));
	} while (0);
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ExecInArgument();
		if (Error::IsIssued()) return;
	}
	do {
		RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(Context::PopStack()));
		Argument& argument = pValue->GetArgument();
		if (!argument.CheckValidity()) return;
		argument.IndexAccess(Context::GetFrame());
	} while (0);
}

void Expr_Indexer::ExecInAssignment(const Expr* pExprAssigned, const Operator* pOperator) const
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

void Expr_Caller::Exec() const
{
	do {
		GetExprCar()->Exec();
		if (Error::IsIssued()) return;
	} while (0);
	do {
		RefPtr<Value> pValueCar(Context::PopStack());
		const DeclCaller* pDeclCaller = pValueCar->GetDeclCaller();
		if (!pDeclCaller) {
			Error::Issue(ErrorType::ValueError,
						 "value type %s can not be called", pValueCar->GetVType().MakeFullName().c_str());
			return;
		}
		if (!pDeclCaller->CheckAttribute(GetAttr())) return;
		RefPtr<Argument> pArgument(
			new Argument(pDeclCaller->Reference(), GetAttr().Reference(), Value::nil(), pValueCar.release()));
		Context::PushStack(new Value_Argument(pArgument.release()));
	} while (0);
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->ExecInArgument();
		if (Error::IsIssued()) return;
	}
	do {
		RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(Context::PopStack()));
		Argument& argument = pValue->GetArgument();
		if (!argument.CheckValidity()) return;
		argument.Call(Context::GetFrame());
	} while (0);
}

void Expr_Caller::ExecInAssignment(const Expr* pExprAssigned, const Operator* pOperator) const
{
	
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
