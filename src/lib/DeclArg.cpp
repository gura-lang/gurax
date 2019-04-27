//==============================================================================
// DeclArg.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclArg
//------------------------------------------------------------------------------
DeclArg* DeclArg::Empty;

DeclArg::DeclArg(const Symbol* pSymbol, DottedSymbol* pDottedSymbol,
				 const Occur& occur, Flags flags, Expr* pExprDefault) :
	_pSymbol(pSymbol), _pDottedSymbol(pDottedSymbol),
	_pVType(pDottedSymbol->IsEmpty()?
			dynamic_cast<VType*>(&VTYPE_Any) : dynamic_cast<VType*>(&VTYPE_Undefined)),
	_occur(occur), _flags(flags), _pExprDefault(pExprDefault)
{
}

DeclArg::DeclArg(const Symbol* pSymbol, const VType& vtype,
				 const Occur& occur, Flags flags, Expr* pExprDefault) :
	_pSymbol(pSymbol), _pDottedSymbol(vtype.MakeDottedSymbol()), _pVType(&vtype),
	_occur(occur), _flags(flags), _pExprDefault(pExprDefault)
{
}

void DeclArg::Bootup()
{
	Empty = new DeclArg(Symbol::Empty, VTYPE_Undefined, Occur::Once, Flag::None, nullptr);
}

DeclArg* DeclArg::CreateFromExpr(const Expr& expr)
{
	RefPtr<DottedSymbol> pDottedSymbol;
	const VType* pVType = nullptr;
	const Occur* pOccur = &Occur::Once;
	Flags flags = 0;
	RefPtr<Expr> pExprDefault;
	const Attribute* pAttrSrc = nullptr;
	const Expr* pExpr = &expr;
	if (pExpr->IsType<Expr_BinaryOp>()) {
		const Expr_BinaryOp* pExprEx = dynamic_cast<const Expr_BinaryOp*>(pExpr);
		if (!pExprEx->GetOperator()->IsType(OpType::Pair)) {
			Error::Issue(ErrorType::SyntaxError, "invalid format of declaration");
			return nullptr;
		}
		// x => value
		pExpr = pExprEx->GetExprLeft();
		pExprDefault.reset(pExprEx->GetExprRight()->Reference());
	}
	if (pExpr->IsType<Expr_UnaryOp>()) {
		const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
		const Operator* pOperator = pExprEx->GetOperator();
		pExpr = pExprEx->GetExprChild();
		if (pOperator->IsType(OpType::Quote)) {
			// `x
			pVType = &VTYPE_Quote;
		} else if (pOperator->IsType(OpType::PostMod)) {
			// x% ... nothing to do here
		} else if (pOperator->IsType(OpType::PostModMod)) {
			// x%% ... nothing to do here
		} else if (pOperator->IsType(OpType::PostMul)) {
			// x*
			pOccur = &Occur::ZeroOrMore;
		} else if (pOperator->IsType(OpType::PostPos)) {
			// x+
			pOccur = &Occur::OnceOrMore;
		} else if (pOperator->IsType(OpType::PostQuestion)) {
			// x?
			pOccur = &Occur::ZeroOrOnce;
		} else {
			Error::Issue(ErrorType::SyntaxError, "invalid format of declaration");
			return nullptr;
		}
	}
	if (pExpr->IsType<Expr_Indexer>()) {
		const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(pExpr);
		if (!pExprEx->GetExprLinkCdr().IsEmpty()) {
			Error::Issue(ErrorType::SyntaxError, "bracket must be empty");
			return nullptr;
		}
		// x[]
		pExpr = pExprEx->GetExprCar();
		pAttrSrc = &pExprEx->GetAttr();
		flags |= Flag::ListVar;
	}
	if (!pExpr->IsType<Expr_Identifier>()) {
		Error::Issue(ErrorType::SyntaxError, "declaration must be an indentifier");
		return nullptr;
	}
	const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExpr);
	const Symbol* pSymbol = pExprIdentifier->GetSymbol();
	if (!pAttrSrc) {
		pAttrSrc = &pExprIdentifier->GetAttr();
	} else if (!pExprIdentifier->IsPureSymbol()) {
		Error::Issue(ErrorType::SyntaxError, "invalid attribute");
		return nullptr;
	}
	if (!pAttrSrc->GetSymbolsOpt().empty()) {
		Error::Issue(ErrorType::SyntaxError, "optional attribute can not be declared");
		return nullptr;
	}
	pDottedSymbol.reset(pAttrSrc->GetDottedSymbol().Reference());
	bool firstFlag = true;
	for (const Symbol* pSymbol : pAttrSrc->GetSymbols()) {
		Flags flag = SymbolToFlag(pSymbol);
		flags |= flag;
		if (flag) {
			if (firstFlag && pDottedSymbol->IsEqualTo(pSymbol)) {
				pDottedSymbol.reset(DottedSymbol::Empty.Reference());
			}
		} else {
			if (!firstFlag) {
				Error::Issue(ErrorType::SyntaxError, "unsupported symbol: %s", pSymbol->GetName());
				return nullptr;
			}
		}
		firstFlag = false;
	}
	return pVType?
		new DeclArg(pSymbol, *pVType, *pOccur, flags, pExprDefault.release()) :
		new DeclArg(pSymbol, pDottedSymbol.release(), *pOccur, flags, pExprDefault.release());
}

bool DeclArg::FixVType(Frame& frame)
{
	Value* pValue = frame.Lookup(GetDottedSymbol());
	if (pValue && pValue->IsType(VTYPE_VType)) {
		_pVType = &dynamic_cast<Value_VType*>(pValue)->GetVTypeThis();
		return true;
	}
	return false;
}

Value* DeclArg::Cast(Frame& frame, const Value& value)
{
	if (GetVType().IsIdentical(VTYPE_Undefined) && !FixVType(frame)) {
		Error::Issue(ErrorType::TypeError,
					 "unknown value type: %s", GetDottedSymbol().ToString().c_str());
		return nullptr;
	}
	return GetVType().Cast(value, GetListVarFlag());
}

String DeclArg::FlagsToString(Flags flags)
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

String DeclArg::ToString(const StringStyle& ss) const
{
	String str;
	bool quoteFlag = GetVType().IsIdentical(VTYPE_Quote);
	if (quoteFlag) str += '`';
	str += GetSymbol()->GetName();
	if (GetFlags() & Flag::ListVar) str += "[]";
	str += GetOccur().GetMarker();
	if (quoteFlag) {
		// nothing to do 
	} else if (!GetDottedSymbol().IsEmpty()) {
		str += ':';
		str += GetDottedSymbol().ToString();
	} else if (ss.IsVerbose()) {
		str += ':';
		str += VTYPE_Any.GetName();
	}
	str += FlagsToString(GetFlags() & ~Flag::ListVar);
	if (GetExprDefault()) {
		str += ss.IsCram()? "=>" : " => ";
		str += GetExprDefault()->ToString(ss);
	}
	return str;
}

//------------------------------------------------------------------------------
// DeclArg::Occur
//------------------------------------------------------------------------------
const DeclArg::Occur DeclArg::Occur::Invalid	("",	ArgSlot_Once::factory);
const DeclArg::Occur DeclArg::Occur::Zero		("",	ArgSlot_Once::factory);
const DeclArg::Occur DeclArg::Occur::Once		("",	ArgSlot_Once::factory);
const DeclArg::Occur DeclArg::Occur::ZeroOrOnce	("?",	ArgSlot_ZeroOrOnce::factory);
const DeclArg::Occur DeclArg::Occur::ZeroOrMore	("*",	ArgSlot_ZeroOrMore::factory);
const DeclArg::Occur DeclArg::Occur::OnceOrMore	("+",	ArgSlot_OnceOrMore::factory);

//------------------------------------------------------------------------------
// DeclArgList
//------------------------------------------------------------------------------
DeclArg* DeclArgList::FindBySymbol(const Symbol* pSymbol) const
{
	for (DeclArg* pDeclArg : *this) {
		if (pDeclArg->GetSymbol()->IsIdentical(pSymbol)) return pDeclArg;
	}
	return nullptr;
}

String DeclArgList::ToString(const StringStyle& ss) const
{
	String str;
	for (auto ppDeclArg = begin(); ppDeclArg != end(); ppDeclArg++) {
		const DeclArg* pDeclArg = *ppDeclArg;
		if (ppDeclArg != begin()) str += ss.GetComma();
		str += pDeclArg->ToString(ss);
	}
	return str;
}

//------------------------------------------------------------------------------
// DeclArgOwner
//------------------------------------------------------------------------------

}
