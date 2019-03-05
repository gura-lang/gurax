//==============================================================================
// DeclCallable.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclCallable
//------------------------------------------------------------------------------
const DeclCallable* DeclCallable::Empty = nullptr;

void DeclCallable::Bootup()
{
	Empty = new DeclCallable();
}

DeclCallable::DeclCallable() : _pVType(&VTYPE_Any), _flags(0), _pAttr(new Attribute())
{
}

bool DeclCallable::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, const Expr_Block* pExprBlock)
{
	_declArgOwner.reserve(exprLinkCdr.CountSequence());
	for (const Expr* pExpr = exprLinkCdr.GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		RefPtr<DeclArg> pDeclArg(DeclArg::CreateFromExpr(pExpr));
		if (!pDeclArg) {
			Clear();
			return false;
		}
		_declArgOwner.push_back(pDeclArg.release());
	}
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		Flags flag = SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
	if (pExprBlock) {
		const char* strError = "invalid format of block declaration";
		if (pExprBlock->HasExprParam()) {
			Error::Issue(ErrorType::DeclarationError, strError);
			return false;
		}
		Flags flags = DeclBlock::Flag::None;
		const DeclBlock::Occur* pOccur = nullptr;
		if (pExprBlock->CountExprElem() != 1) {
			Error::Issue(ErrorType::DeclarationError, strError);
			return false;
		}
		const Expr* pExpr = pExprBlock->GetExprLinkElem().GetExprHead();
		while (pExpr->IsType<Expr_UnaryOp>()) {
			const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
			if (pExprEx->GetOperator()->IsType(OpType::Quote)) {
				if (flags & DeclBlock::Flag::Quote) {
					Error::Issue(ErrorType::DeclarationError, strError);
					return false;
				}
				flags |= DeclBlock::Flag::Quote;
			} else if (pExprEx->GetOperator()->IsType(OpType::PostQuestion)) {
				if (pOccur) {
					Error::Issue(ErrorType::DeclarationError, strError);
					return false;
				}
				pOccur = &DeclBlock::Occur::ZeroOrOnce;
			} else {
				Error::Issue(ErrorType::DeclarationError, strError);
				return false;
			}
			pExpr = pExprEx->GetExprChild();
		}
		GetDeclBlock().SetFlags(flags).SetOccur(pOccur? *pOccur : DeclBlock::Occur::Once);
		if (pExpr->IsType<Expr_Identifier>()) {
			const Expr_Identifier* pExprEx = dynamic_cast<const Expr_Identifier*>(pExpr);
			GetDeclBlock().SetSymbol(pExprEx->GetSymbol());
		} else {
			Error::Issue(ErrorType::DeclarationError, strError);
			return false;
		}
	}
	return true;
}

void DeclCallable::Clear()
{
	_declArgOwner.Clear();
	_flags = 0;
	_pAttr.reset(new Attribute());
}

bool DeclCallable::CheckAttribute(const Attribute& attr) const
{
	for (const Symbol* pSymbol: attr.GetSymbols()) {
		if (!GetAttr().GetSymbolSetOpt().IsSet(pSymbol)) {
			Error::Issue(ErrorType::ArgumentError, "unacceptable attribute symbol: %s", pSymbol->GetName());
			return false;
		}
	}
	return true;
}

String DeclCallable::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "(";
	rtn += GetDeclArgOwner().ToString(ss);
	rtn += ")";
	rtn += FlagsToString(_flags);
	rtn += GetAttr().ToString(ss);
	if (!GetDeclBlock().IsOccurZero()) {
		rtn += ss.IsCram()? "{" : " {";
		rtn += GetDeclBlock().ToString(ss);
		rtn += "}";
	}
	return rtn;
}

DeclCallable::Flags DeclCallable::SymbolsToFlags(const SymbolList& symbols)
{
	Flags flags = 0;
	for (const Symbol* pSymbol : symbols) flags |= SymbolToFlag(pSymbol);
	return flags;
}

String DeclCallable::FlagsToString(Flags flags)
{
	String rtn;
	for (Flags flag = 1; flags; flag <<= 1, flags >>= 1) {
		if (flags & 1) {
			rtn += ':';
			rtn += FlagToSymbol(flag)->GetName();
		}
	}
	return rtn;
}

}
