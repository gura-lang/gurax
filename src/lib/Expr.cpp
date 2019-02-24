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

void Expr::ExecInAssignment(Processor& processor, const Expr* pExprAssigned, const Operator* pOperator) const
{
	Error::IssueWith(ErrorType::InvalidOperation, Reference(), "invalid assignment");
}

void Expr::ComposeInAssignment(
	PUnitComposer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
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

void ExprList::Exec(Processor& processor) const
{
	for (const Expr* pExpr : *this) {
		do {
			pExpr->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		Value::Delete(processor.PopStack());
	}
}

void ExprList::Compose(PUnitComposer& composer) const
{
	for (const Expr* pExpr : *this) {
		pExpr->Compose(composer);
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

void Expr_Value::Exec(Processor& processor) const
{
	do {
		// PUnit_Value
		processor.PushStack(GetValue()->Clone());
	} while (0);
}

void Expr_Value::Compose(PUnitComposer& composer) const
{
	composer.Add(new PUnit_Value(GetValue()->Clone()));	// -> [Value]
}

String Expr_Value::ToString(const StringStyle& ss) const
{
	return HasSource()? GetSourceSTL() : GetValue()->ToString();
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Exec(Processor& processor) const
{
	do {
		// PUnit_Lookup
		const Value* pValue = processor.GetFrame().LookupValue(GetSymbol());
		if (!pValue) {
			Error::IssueWith(ErrorType::ValueError, Reference(), "symbol not found: %s", GetSymbol()->GetName());
			return;
		}
		processor.PushStack(pValue->Reference());
	} while (0);
}

void Expr_Identifier::Compose(PUnitComposer& composer) const
{
	composer.Add(new PUnit_Lookup(GetSymbol()));		// -> [Value]
}

void Expr_Identifier::ExecInAssignment(Processor& processor, const Expr* pExprAssigned, const Operator* pOperator) const
{
	if (pOperator) {
		do {
			// PUnit_Lookup
			const Value* pValue = processor.GetFrame().LookupValue(GetSymbol());
			if (!pValue) {
				Error::IssueWith(ErrorType::ValueError, Reference(), "symbol not found: %s", GetSymbol()->GetName());
				return;
			}
			processor.PushStack(pValue->Reference());
		} while (0);
		do {
			pExprAssigned->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		do {
			// PUnit_BinaryOp
			RefPtr<Value> pValueRight(processor.PopStack());
			RefPtr<Value> pValueLeft(processor.PopStack());
			RefPtr<Value> pValue(pOperator->EvalBinary(pValueLeft.release(), pValueRight.release()));
			if (!pValue) return;
			processor.PushStack(pValue.release());
		} while (0);
		do {
			// PUnit_Assign
			RefPtr<Value> pValueAssigned(processor.PeekStack(0)->Reference());
			processor.GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
		} while (0);
	} else {
		do {
			pExprAssigned->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		do {
			// PUnit_Assign
			RefPtr<Value> pValueAssigned(processor.PeekStack(0)->Reference());
			processor.GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
		} while (0);
	}
}

void Expr_Identifier::ComposeInAssignment(
	PUnitComposer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
	if (pOperator) {
		composer.Add(new PUnit_Lookup(GetSymbol()));	// -> [Value]
		pExprAssigned->Compose(composer);				// -> [Value ValueRight]
		composer.Add(new PUnit_BinaryOp(pOperator));	// -> [ValueAssigned]
		composer.Add(new PUnit_Assign(GetSymbol()));	// -> [ValueAssigned]
	} else {
		pExprAssigned->Compose(composer);				// -> [ValueAssigned]
		composer.Add(new PUnit_Assign(GetSymbol()));	// -> [ValueAssigned]
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

void Expr_Suffixed::Exec(Processor& processor) const
{
}

void Expr_Suffixed::Compose(PUnitComposer& composer) const
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

void Expr_Embedded::Exec(Processor& processor) const
{
}

void Expr_Embedded::Compose(PUnitComposer& composer) const
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

void Expr_UnaryOp::Exec(Processor& processor) const
{
	do {
		GetExprChild()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	do {
		// PUnit_UnaryOp
		RefPtr<Value> pValueChild(processor.PopStack());
		RefPtr<Value> pValue(GetOperator()->EvalUnary(pValueChild.release()));
		if (!pValue) return;
		processor.PushStack(pValue.release());
	} while (0);
}

void Expr_UnaryOp::Compose(PUnitComposer& composer) const
{
	GetExprChild()->Compose(composer);					// -> [Value]
	composer.Add(new PUnit_UnaryOp(GetOperator()));		// -> [ValueResult]
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

void Expr_BinaryOp::Exec(Processor& processor) const
{
	do {
		GetExprLeft()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	do {
		GetExprRight()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	do {
		// PUnit_BinaryOp
		RefPtr<Value> pValueRight(processor.PopStack());
		RefPtr<Value> pValueLeft(processor.PopStack());
		RefPtr<Value> pValue(GetOperator()->EvalBinary(pValueLeft.release(), pValueRight.release()));
		if (!pValue) return;
		processor.PushStack(pValue.release());
	} while (0);
}

void Expr_BinaryOp::Compose(PUnitComposer& composer) const
{
	GetExprLeft()->Compose(composer);					// -> [ValueLeft]
	GetExprRight()->Compose(composer);					// -> [ValueLeft ValueRight]
	composer.Add(new PUnit_BinaryOp(GetOperator()));	// -> [ValueResult]
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

void Expr_Assign::Exec(Processor& processor) const
{
	GetExprLeft()->ExecInAssignment(processor, GetExprRight(), GetOperator());
}

void Expr_Assign::Compose(PUnitComposer& composer) const
{
	GetExprLeft()->ComposeInAssignment(composer, GetExprRight(), GetOperator());
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

void Expr_Member::Exec(Processor& processor) const
{
	do {
		GetExprTarget()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	do {
		// PUnit_Member
		RefPtr<Value> pValueTarget(processor.PopStack());
		Value* pValue = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
		if (!pValue) {
			Error::IssueWith(ErrorType::ValueError, Reference(), "symbol not found: %s", GetSymbol()->GetName());
			return;
		}
		if (pValue->IsCallable()) {
			processor.PushStack(new Value_Member(pValueTarget.release(), pValue->Reference()));
		} else {
			processor.PushStack(pValue->Reference());
		}
	} while (0);
}

void Expr_Member::Compose(PUnitComposer& composer) const
{
	GetExprTarget()->Compose(composer);									// -> [ValueTarget]
	composer.Add(new PUnit_Member(GetSymbol(), GetAttr().Reference()));	// -> [ValueMember] or [ValueProp]
}

void Expr_Member::ExecInAssignment(Processor& processor, const Expr* pExprAssigned, const Operator* pOperator) const
{
	do {
		GetExprTarget()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	if (pOperator) {
		do {
			// PUnit_PropGet
			Value* pValueTarget = processor.PeekStack(0);
			Value* pValue = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
			if (!pValue) {
				Error::IssueWith(ErrorType::ValueError, Reference(), "undefined symbol: %s", GetSymbol()->GetName());
				return;
			}
			processor.PushStack(pValue->Reference());
		} while (0);
		do {
			pExprAssigned->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		do {
			// PUnit_BinaryOp
			RefPtr<Value> pValueRight(processor.PopStack());
			RefPtr<Value> pValueLeft(processor.PopStack());
			RefPtr<Value> pValue(pOperator->EvalBinary(pValueLeft.release(), pValueRight.release()));
			if (!pValue) return;
			processor.PushStack(pValue.release());
		} while (0);
	} else {
		do {
			pExprAssigned->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
	}
	do {
		// PUnit_PropSet
		RefPtr<Value> pValueProp(processor.PopStack());
		RefPtr<Value> pValueTarget(processor.PopStack());
		pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr());
		processor.PushStack(pValueProp.release());
	} while (0);
}

void Expr_Member::ComposeInAssignment(
	PUnitComposer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
{
	GetExprTarget()->Compose(composer);								// -> [ValueTarget]
	if (pOperator) {
		composer.Add(
			new PUnit_PropGet(GetSymbol(), GetAttr().Reference()));	// -> [ValueTarget ValueProp]
		pExprAssigned->Compose(composer);							// -> [ValueTarget ValueProp ValueRight]
		composer.Add(new PUnit_BinaryOp(pOperator));				// -> [ValueTarget ValueAssigned]
	} else {
		pExprAssigned->Compose(composer);							// -> [ValueTarget ValueAssigned]
	}
	composer.Add(
		new PUnit_PropSet(GetSymbol(), GetAttr().Reference()));		// -> [ValueAssigned]
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

void Expr_Root::Exec(Processor& processor) const
{
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Exec(processor);
		if (Error::IsIssued()) return;
		Value::Delete(processor.PopStack());
	}
}

void Expr_Root::Compose(PUnitComposer& composer) const
{
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);
	}
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

void Expr_Block::Exec(Processor& processor) const
{
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Exec(processor);
		if (Error::IsIssued()) return;
		Value::Delete(processor.PopStack());
	}
}

void Expr_Block::Compose(PUnitComposer& composer) const
{
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);
	}
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

void Expr_Iterer::Exec(Processor& processor) const
{
	do {
		RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
		pValueTypedOwner->Reserve(GetExprLinkElem().GetSize());
		processor.PushStack(new Value_Iterator(new Iterator_Each(pValueTypedOwner.release())));
	} while (0);
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		do {
			pExpr->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		do {
			RefPtr<Value> pValue(processor.PopStack());
			Iterator& iterator =
				dynamic_cast<Value_Iterator*>(processor.PeekStack(0))->GetIterator();
			ValueTypedOwner& valueTypedOwner =
				dynamic_cast<Iterator_Each*>(&iterator)->GetValueTypedOwner();
			valueTypedOwner.Add(pValue.release());
		} while (0);
	}
}

void Expr_Iterer::Compose(PUnitComposer& composer) const
{
}

String Expr_Iterer::ToString(const StringStyle& ss) const
{
	String rtn;
	if (GetExprLinkElem().GetSize() == 1) {
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

void Expr_Lister::Exec(Processor& processor) const
{
	do {
		// PUnit_CreateList
		RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
		pValueTypedOwner->Reserve(GetExprLinkElem().GetSize());
		processor.PushStack(new Value_List(pValueTypedOwner.release()));
	} while (0);
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		do {
			pExpr->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		do {
			// PUnit_AddList
			RefPtr<Value> pValue(processor.PopStack());
			ValueTypedOwner& valueTypedOwner =
				dynamic_cast<Value_List*>(processor.PeekStack(0))->GetValueTypedOwner();
			valueTypedOwner.Add(pValue.release());
		} while (0);
	}
}

void Expr_Lister::Compose(PUnitComposer& composer) const
{
	composer.Add(new PUnit_CreateList());						// -> [ValueList]
	for (const Expr* pExpr = GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);								// -> [ValueList Value]
		composer.Add(new PUnit_AddList());						// -> [ValueList]
	}	
}

void Expr_Lister::ExecInAssignment(Processor& processor, const Expr* pExprAssigned, const Operator* pOperator) const
{
}

void Expr_Lister::ComposeInAssignment(
	PUnitComposer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
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

void Expr_Indexer::Exec(Processor& processor) const
{
	do {
		GetExprCar()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	do {
		// PUnit_Index
		RefPtr<Value> pValueCar(processor.PopStack());
		RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
		processor.PushStack(new Value_Index(pIndex.release()));
	} while (0);
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		do {
			pExpr->Exec(processor);
			if (Error::IsIssued()) return;
		} while (0);
		do {
			// PUnit_FeedIndex
			RefPtr<Value> pValue(processor.PopStack());
			Index& index = dynamic_cast<Value_Index*>(processor.PeekStack(0))->GetIndex();
			index.FeedValue(pValue.release());
		} while (0);
	}
	do {
		// PUnit_IndexGet
		RefPtr<Value_Index> pValue(dynamic_cast<Value_Index*>(processor.PopStack()));
		Index& index = pValue->GetIndex();
		RefPtr<Value> pValueRtn(index.IndexGet());
		if (Error::IsIssued()) return;
		processor.PushStack(pValueRtn.release());
	} while (0);
}

void Expr_Indexer::Compose(PUnitComposer& composer) const
{
	GetExprCar()->Compose(composer);									// -> [ValueCar]
	composer.Add(new PUnit_Index(GetAttr().Reference()));				// -> [ValueIndex]
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);										// -> [ValueIndex Value]
		composer.Add(new PUnit_FeedIndex());							// -> [ValueIndex]
	}
	composer.Add(new PUnit_IndexGet());									// -> [ValueElems]
}

void Expr_Indexer::ExecInAssignment(Processor& processor, const Expr* pExprAssigned, const Operator* pOperator) const
{
}

void Expr_Indexer::ComposeInAssignment(
	PUnitComposer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
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

void Expr_Caller::Exec(Processor& processor) const
{
	do {
		GetExprCar()->Exec(processor);
		if (Error::IsIssued()) return;
	} while (0);
	do {
		// PUnit_Argument
		RefPtr<Value> pValueCar(processor.PopStack());
		const DeclCaller* pDeclCaller = pValueCar->GetDeclCaller();
		if (!pDeclCaller) {
			Error::IssueWith(ErrorType::ValueError, Reference(),
						 "value type %s can not be called", pValueCar->GetVType().MakeFullName().c_str());
			return;
		}
		if (!pDeclCaller->CheckAttribute(GetAttr())) return;
		RefPtr<Argument> pArgument(
			new Argument(pValueCar.release(), pDeclCaller->Reference(), GetAttr().Reference(), Value::nil()));
		processor.PushStack(new Value_Argument(pArgument.release()));
	} while (0);
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<const Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			const Expr_BinaryOp* pExprEx = dynamic_cast<const Expr_BinaryOp*>(pExpr);
			if (!pExprEx->GetExprLeft()->IsType<Expr_Identifier>()) {
				Error::IssueWith(ErrorType::ArgumentError, Reference(), "named argument must be specified by a symbol");
				return;
			}
			do {
				const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(pExprEx->GetExprLeft())->GetSymbol();
				// PUnit_ArgSlotNamed
				Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekStack(0))->GetArgument();
				ArgSlot* pArgSlot = argument.FindArgSlot(pSymbol);
				if (!pArgSlot) {
					Error::IssueWith(ErrorType::ArgumentError, Reference(),
									 "can't find argument with a name: %s", pSymbol->GetName());
					return;
				}
				if (!pArgSlot->IsVacant()) {
					Error::IssueWith(ErrorType::ArgumentError, Reference(), "duplicated assignment of argument");
					return;
				}
				if (pArgSlot->IsVType(VTYPE_Quote)) {
					pArgSlot->FeedValue(new Value_Expr(pExprEx->GetExprRight()->Reference()));
					goto skip1;
				}
				processor.PushStack(new Value_ArgSlot(pArgSlot->Reference()));
			} while (0);
			do {
				pExprEx->GetExprRight()->Exec(processor);
				if (Error::IsIssued()) return;
			} while (0);
			do {
				// PUnit_FeedArgSlotNamed
				RefPtr<Value> pValue(processor.PopStack());
				ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(processor.PopStack())->GetArgSlot();
				argSlot.FeedValue(pValue.release());
			} while (0);
		skip1:;
		} else {
			do {
				// PUnit_ArgSlot
				Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekStack(0))->GetArgument();
				ArgSlot* pArgSlot = argument.GetArgSlotToFeed(); // this may be nullptr
				if (!pArgSlot) {
					Error::IssueWith(ErrorType::ArgumentError, Reference(), "too many arguments");
					return;
				}
				if (!pArgSlot->IsVacant()) {
					Error::IssueWith(ErrorType::ArgumentError, Reference(), "duplicated assignment of argument");
					return;
				}
				if (pArgSlot->IsVType(VTYPE_Quote)) {
					argument.FeedValue(new Value_Expr(pExpr->Reference()));
					goto skip2;
				}
			} while (0);
			do {
				pExpr->Exec(processor);
				if (Error::IsIssued()) return;
			} while (0);
			do {
				// PUnit_FeedArgSlot
				RefPtr<Value> pValue(processor.PopStack());
				Index& index = dynamic_cast<Value_Index*>(processor.PeekStack(0))->GetIndex();
				index.FeedValue(pValue.release());
			} while (0);
		skip2:;
		}
	}
	do {
		// PUnit_Call
		RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopStack()));
		Argument& argument = pValue->GetArgument();
		if (!argument.CheckValidity()) return;
		RefPtr<Value> pValueRtn(argument.Call(processor.GetFrame()));
		if (Error::IsIssued()) return;
		processor.PushStack(pValueRtn.release());
	} while (0);
}

void Expr_Caller::Compose(PUnitComposer& composer) const
{
	GetExprCar()->Compose(composer);
	composer.Add(new PUnit_Argument(GetAttr().Reference()));		// -> [ValueArgument]
	for (const Expr* pExpr = GetExprCdrHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<const Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			const Expr_BinaryOp* pExprEx = dynamic_cast<const Expr_BinaryOp*>(pExpr);
			if (!pExprEx->GetExprLeft()->IsType<Expr_Identifier>()) {
				Error::IssueWith(ErrorType::ArgumentError, pExpr->Reference(),
								 "named argument must be specified by a symbol");
				return;
			}
			const Symbol* pSymbol = dynamic_cast<const Expr_Identifier*>(pExprEx->GetExprLeft())->GetSymbol();
			auto pPUnit1 = new PUnit_ArgSlotNamed(pSymbol, pExprEx->GetExprRight()->Reference());
			composer.Add(pPUnit1);									// -> [ValueArgument ValueArgSlot]
			pExprEx->GetExprRight()->Compose(composer);				// -> [ValueArgument ValueArgSlot Value]
			auto pPUnit2 = new PUnit_FeedArgSlotNamed();
			composer.Add(pPUnit2);									// -> [ValueArgument]
			pPUnit1->SetPUnitAtMerging(pPUnit2);
		} else {
			auto pPUnit1 = new PUnit_ArgSlot(pExpr->Reference());
			composer.Add(pPUnit1);									// -> [ValueArgument]
			pExpr->Compose(composer);								// -> [ValueArgument Value]
			auto pPUnit2 = new PUnit_FeedArgSlot();
			composer.Add(pPUnit2);									// -> [ValueArgument]
			pPUnit1->SetPUnitAtMerging(pPUnit2);
		}
	}
	composer.Add(new PUnit_Call());									// -> [ValueResult]
}

void Expr_Caller::ExecInAssignment(Processor& processor, const Expr* pExprAssigned, const Operator* pOperator) const
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
	do {
		RefPtr<Function> pFunction(new FunctionCustom(pExprCarEx->GetSymbol(), GetDeclCaller().Reference()));
		RefPtr<Value> pValueAssigned(new Value_Function(pFunction.release()));
		// PUnit_AssignValue
		processor.GetFrame().AssignValue(pExprCarEx->GetSymbol(), pValueAssigned.release());
	} while (0);
}

void Expr_Caller::ComposeInAssignment(
	PUnitComposer& composer, const Expr* pExprAssigned, const Operator* pOperator) const
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
