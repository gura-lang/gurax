//==============================================================================
// DeclCallable.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclCallable
//------------------------------------------------------------------------------
RefPtr<DeclCallable> DeclCallable::Empty;
RefPtr<DeclCallable> DeclCallable::EmptyWithBlock;
RefPtr<DeclCallable> DeclCallable::EmptyWithOptionalBlock;
RefPtr<DeclCallable> DeclCallable::Wildcard;

void DeclCallable::Bootup()
{
	Empty.reset(new DeclCallable());
	EmptyWithBlock.reset(new DeclCallable());
	EmptyWithOptionalBlock.reset(new DeclCallable());
	Wildcard.reset(new DeclCallable());
	EmptyWithBlock->GetDeclBlock().SetOccur(DeclBlock::Occur::Once).SetFlags(Flag::None);
	EmptyWithOptionalBlock->GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce).SetFlags(Flag::None);
	Wildcard->GetDeclArgOwner().push_back(
		new DeclArg(Gurax_Symbol(x), VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr));
	Wildcard->GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce);
	Wildcard->SetFlags(Flag::AnyAttr);
}

DeclCallable::DeclCallable() :
	_pVTypeResult(&VTYPE_Any), _flags(0), _pAttr(new Attribute()),
	_pSymbolOfDict(Symbol::Empty), _pSymbolOfAccessor(Symbol::Empty)
{
}

bool DeclCallable::IsNaked() const
{
	return GetDeclArgOwner().empty();
}

bool DeclCallable::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, const Expr_Block* pExprOfBlock)
{
	_declArgOwner.reserve(exprLinkCdr.CountSequence());
	for (const Expr* pExpr = exprLinkCdr.GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_UnaryOp>()) {
			const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
			if (pExprEx->GetOperator()->IsType(OpType::PostMod)) {
				if (!_pSymbolOfDict->IsEmpty()) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "duplicated declaration of dictionary argument");
					return false;
				}
				if (!pExprEx->GetExprChild().IsType<Expr_Identifier>()) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "invalid format of dictionary argument");
					return false;
				}
				const Expr_Identifier& exprIdentifier =
					dynamic_cast<const Expr_Identifier&>(pExprEx->GetExprChild());
				if (!exprIdentifier.IsPureSymbol()) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "dictionary argument cannot have attributes");
					return false;
				}
				const Symbol* pSymbol = exprIdentifier.GetSymbol();
				if (IsDeclaredSymbol(pSymbol)) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "duplicated symbol declaration: %s", pSymbol->GetName());
					return false;
				}
				_pSymbolOfDict = pSymbol;
				continue;
			} else if (pExprEx->GetOperator()->IsType(OpType::PostModMod)) {
				if (!_pSymbolOfAccessor->IsEmpty()) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "duplicated declaration of argument accessor");
					return false;
				}
				if (!pExprEx->GetExprChild().IsType<Expr_Identifier>()) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "invalid format of argument accessor");
					return false;
				}
				const Expr_Identifier& exprIdentifier =
					dynamic_cast<const Expr_Identifier&>(pExprEx->GetExprChild());
				if (!exprIdentifier.IsPureSymbol()) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "argument accessor cannot have attributes");
					return false;
				}
				const Symbol* pSymbol = exprIdentifier.GetSymbol();
				if (IsDeclaredSymbol(pSymbol)) {
					Error::IssueWith(ErrorType::DeclarationError, *pExpr,
									 "duplicated symbol declaration: %s", pSymbol->GetName());
					return false;
				}
				_pSymbolOfAccessor = pSymbol;
				continue;
			}
		}
		RefPtr<DeclArg> pDeclArg(DeclArg::CreateFromExpr(*pExpr));
		if (!pDeclArg) return false;
		if (IsDeclaredSymbol(pDeclArg->GetSymbol())) {
			Error::IssueWith(ErrorType::DeclarationError, *pExpr,
							 "duplicated symbol declaration: %s", pDeclArg->GetSymbol()->GetName());
			return false;
		}
		if (!DeclArg::CheckFlagConfliction(pDeclArg->GetFlags())) return false;
		_declArgOwner.push_back(pDeclArg.release());
	}
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		Flags flag = SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	if (!CheckFlagConfliction(GetFlags())) return false;
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
	if (pExprOfBlock) {
		const char* strError = "invalid format of block declaration";
		if (pExprOfBlock->HasExprParam()) {
			Error::IssueWith(ErrorType::DeclarationError, *pExprOfBlock, strError);
			return false;
		}
		Flags flags = DeclBlock::Flag::None;
		const DeclBlock::Occur* pOccur = nullptr;
		if (pExprOfBlock->CountExprElem() != 1) {
			Error::IssueWith(ErrorType::DeclarationError, *pExprOfBlock, strError);
			return false;
		}
		const Expr* pExpr = pExprOfBlock->GetExprLinkElem().GetExprFirst();
		while (pExpr->IsType<Expr_UnaryOp>()) {
			const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
			if (pExprEx->GetOperator()->IsType(OpType::Quote)) {
				if (flags & DeclBlock::Flag::Quote) {
					Error::IssueWith(ErrorType::DeclarationError, *pExprOfBlock, strError);
					return false;
				}
				flags |= DeclBlock::Flag::Quote;
			} else if (pExprEx->GetOperator()->IsType(OpType::PostQuestion)) {
				if (pOccur) {
					Error::IssueWith(ErrorType::DeclarationError, *pExprOfBlock, strError);
					return false;
				}
				pOccur = &DeclBlock::Occur::ZeroOrOnce;
			} else {
				Error::IssueWith(ErrorType::DeclarationError, *pExprOfBlock, strError);
				return false;
			}
			pExpr = &pExprEx->GetExprChild();
		}
		GetDeclBlock().SetFlags(flags).SetOccur(pOccur? *pOccur : DeclBlock::Occur::Once);
		if (pExpr->IsType<Expr_Identifier>()) {
			const Expr_Identifier* pExprEx = dynamic_cast<const Expr_Identifier*>(pExpr);
			const Symbol* pSymbol = pExprEx->GetSymbol();
			if (IsDeclaredSymbol(pSymbol)) {
				Error::IssueWith(ErrorType::DeclarationError, *pExpr,
								 "duplicated symbol declaration: %s", pSymbol->GetName());
				return false;
			}
			GetDeclBlock().SetSymbol(pSymbol);
		} else {
			Error::IssueWith(ErrorType::DeclarationError, *pExpr, strError);
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
	if (IsSet(Flag::AnyAttr)) return true;
	for (const Symbol* pSymbol: attr.GetSymbols()) {
		if (!GetAttr().GetSymbolSetOpt().IsSet(pSymbol)) {
			Error::Issue(ErrorType::ArgumentError, "unacceptable attribute symbol: %s", pSymbol->GetName());
			return false;
		}
	}
	return true;
}

bool DeclCallable::CheckFlagConfliction(Flags flags)
{
	if ((flags & Flag::Map) != 0 && (flags & Flag::NoMap) != 0) {
		Error::Issue(ErrorType::ArgumentError,
					 "attribute :map and :nomap can not be specified together");
		return false;
	}
	if ((flags & Flag::Public) != 0 && (flags & Flag::Private) != 0) {
		Error::Issue(ErrorType::ArgumentError,
					 "attribute :public and :private can not be specified together");
		return false;
	}
	if ((flags & Flag::List) != 0 && (flags & Flag::XList) != 0 &&
		(flags & Flag::Iter) != 0 && (flags & Flag::XIter) != 0) {
		Error::Issue(ErrorType::ArgumentError,
					 "attribute :list, :xlist, :iter and :xiter can not be specified together");
		return false;
	}
	return true;
}

bool DeclCallable::IsMappable(const DeclArg& declArg, Flags flags)
{
	if (declArg.IsSet(DeclArg::Flag::NoMap)) return false;
	if (declArg.IsSet(DeclArg::Flag::Map)) return true;
	if ((flags & (Flag::NoMap | Flag::Map)) != Flag::Map) return false;
	if (declArg.GetVType().IsListOrIterator()) return false;
	return true;
}

String DeclCallable::ToString(const StringStyle& ss) const
{
	String str;
	str += "(";
	str += GetDeclArgOwner().ToString(ss);
	if (!GetSymbolOfDict()->IsEmpty()) {
		if (!GetDeclArgOwner().empty()) str += ss.GetComma();
		str += GetSymbolOfDict()->GetName();
		str += "%";
	}
	if (!GetSymbolOfAccessor()->IsEmpty()) {
		if (!GetDeclArgOwner().empty() || !GetSymbolOfDict()->IsEmpty()) {
			str += ss.GetComma();
		}
		str += GetSymbolOfAccessor()->GetName();
		str += "%%";
	}
	str += ")";
	str += FlagsToString(_flags);
	str += GetAttr().ToString(ss);
	if (!GetDeclBlock().IsOccurZero()) {
		str += ss.IsCram()? "{" : " {";
		str += GetDeclBlock().ToString(ss);
		str += "}";
	}
	return str;
}

DeclCallable::Flags DeclCallable::SymbolsToFlags(const SymbolList& symbols)
{
	Flags flags = 0;
	for (const Symbol* pSymbol : symbols) flags |= SymbolToFlag(pSymbol);
	return flags;
}

String DeclCallable::FlagsToString(Flags flags)
{
	String str;
	for (Flags flag = 1; flags; flag <<= 1, flags >>= 1) {
		if (flags & 1) {
			str += ':';
			str += FlagToSymbol(flag)->GetName();
		}
	}
	return str;
}

}
