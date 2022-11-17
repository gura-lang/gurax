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
RefPtr<DeclCallable> DeclCallable::Unary;
RefPtr<DeclCallable> DeclCallable::UnaryPost;
RefPtr<DeclCallable> DeclCallable::Binary;
RefPtr<DeclCallable> DeclCallable::Binary_NoMap;
RefPtr<DeclCallable> DeclCallable::MathUnary;
RefPtr<DeclCallable> DeclCallable::MathBinary;

void DeclCallable::Bootup()
{
	do {
		Empty.reset(new DeclCallable());
	} while (0);
	do {
		EmptyWithBlock.reset(new DeclCallable());
		DeclCallable& dc = *EmptyWithBlock;
		dc.GetDeclBlock().SetOccur(DeclBlock::Occur::Once).SetFlags(Flag::None);
	} while (0);
	do {
		EmptyWithOptionalBlock.reset(new DeclCallable());
		DeclCallable& dc = *EmptyWithOptionalBlock;
		dc.GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce).SetFlags(Flag::None);
	} while (0);
	do {
		Wildcard.reset(new DeclCallable());
		DeclCallable& dc = *Wildcard;
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(x), VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr));
		dc.GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce);
		dc.SetFlags(Flag::AnyAttr);
	} while (0);
	do {
		Unary.reset(new DeclCallable());
		DeclCallable& dc = *Unary;
		dc.SetFlags(DeclCallable::Flag::Map);
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(a), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
	} while (0);
	do {
		UnaryPost.reset(new DeclCallable());
		DeclCallable& dc = *UnaryPost;
		dc.SetFlags(DeclCallable::Flag::Map);
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(a), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
	} while (0);
	do {
		Binary.reset(new DeclCallable());
		DeclCallable& dc = *Binary;
		dc.SetFlags(DeclCallable::Flag::Map);
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(a), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(b), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
	} while (0);
	do {
		Binary_NoMap.reset(new DeclCallable());
		DeclCallable& dc = *Binary_NoMap;
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(a), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(b), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
	} while (0);
	do {
		MathUnary.reset(new DeclCallable());
		DeclCallable& dc = *MathUnary;
		dc.SetFlags(DeclCallable::Flag::Map);
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(a), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
	} while (0);
	do {
		MathBinary.reset(new DeclCallable());
		DeclCallable& dc = *MathBinary;
		dc.SetFlags(DeclCallable::Flag::Map);
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(a), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
		dc.GetDeclArgOwner().push_back(
			new DeclArg(Gurax_Symbol(b), VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
	} while (0);
}

DeclCallable::DeclCallable(Flags flags) :
	_pVTypeResult(&VTYPE_Any), _pDottedSymbol(DottedSymbol::Empty.Reference()),
	_flags(flags), _pAttr(new Attribute()), _pDeclArgOwner(new DeclArgOwner()),
	_pSymbolOfDict(Symbol::Empty), _pSymbolOfAccessor(Symbol::Empty)
{
}

bool DeclCallable::IsNaked() const
{
	return GetDeclArgOwner().empty();
}

bool DeclCallable::Prepare(const ExprLink& exprLinkParam, const Attribute& attr, const Expr_Block* pExprOfBlock)
{
	GetDeclArgOwner().reserve(exprLinkParam.CountSequence());
	for (const Expr* pExpr = exprLinkParam.GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
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
				if (exprIdentifier.HasAttr()) {
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
				if (exprIdentifier.HasAttr()) {
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
		GetDeclArgOwner().push_back(pDeclArg.release());
	}
	if (attr.IsSet(Gurax_Symbol(void_))) SetVTypeResult(VTYPE_Nil);
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
	GetDeclArgOwner().Clear();
	_flags = 0;
	_pAttr.reset(new Attribute());
}

bool DeclCallable::CheckAttribute(const Attribute& attr) const
{
	if (IsSet(Flag::AnyAttr)) return true;
	for (const Symbol* pSymbol: attr.GetSymbols()) {
		if (!GetAttr().GetSymbolSetOpt().IsSet(pSymbol)) {
			Error::Issue(ErrorType::ArgumentError, "invalid attribute symbol: %s", pSymbol->GetName());
			return false;
		}
	}
	return true;
}

bool DeclCallable::CheckFlagConfliction(Flags flags)
{
	if ((flags & Flag::Map) != 0 && (flags & Flag::NoMap) != 0) {
		Error::Issue(ErrorType::ArgumentError,
					 "attribute :map and :noMap can not be specified together");
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
	if (declArg.IsSet(DeclArg::Flag::ListVar)) return false;
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
	if (!GetDottedSymbol().IsEmpty()) {
		str += " as ";
		str += GetDottedSymbol().ToString();
	}
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
			const char* name = FlagToSymbol(flag)->GetName();
			if (*name) {
				str += ':';
				str += name;
			}
		}
	}
	return str;
}

}
