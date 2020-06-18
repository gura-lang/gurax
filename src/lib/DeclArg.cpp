//==============================================================================
// DeclArg.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclArg
//------------------------------------------------------------------------------
DeclArg* DeclArg::Undefined;
DeclArg* DeclArg::Any;

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
	Undefined = new DeclArg(Symbol::Empty, VTYPE_Undefined, Occur::Once, Flag::None, nullptr);
	Any = new DeclArg(Symbol::Empty, VTYPE_Any, Occur::Once, Flag::None, nullptr);
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
	Expr_Binary* pExprEx = nullptr;
	if (pExpr->IsDeclArgWithDefault(&pExprEx)) {
		// x = value
		pExpr = &pExprEx->GetExprLeft();
		pExprDefault.reset(pExprEx->GetExprRight().Reference());
	}
	if (pExpr->IsType<Expr_UnaryOp>()) {
		const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
		Operator* pOp = pExprEx->GetOperator();
		pExpr = &pExprEx->GetExprChild();
		if (pOp->IsType(OpType::Quote)) {
			// `x
			pVType = &VTYPE_Quote;
		} else if (pOp->IsType(OpType::PostMod)) {
			// x% ... nothing to do here
		} else if (pOp->IsType(OpType::PostModMod)) {
			// x%% ... nothing to do here
		} else if (pOp->IsType(OpType::PostMul)) {
			// x*
			pOccur = &Occur::ZeroOrMore;
		} else if (pOp->IsType(OpType::PostPos)) {
			// x+
			pOccur = &Occur::OnceOrMore;
		} else if (pOp->IsType(OpType::PostQuestion)) {
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
		pExpr = &pExprEx->GetExprCar();
		pAttrSrc = &pExprEx->GetAttr();
		flags |= Flag::ListVar;
	}
	if (!pExpr->IsType<Expr_Identifier>()) {
		Error::Issue(ErrorType::SyntaxError, "invalid declaration of argument");
		return nullptr;
	}
	const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExpr);
	const Symbol* pSymbol = pExprIdentifier->GetSymbol();
	if (!pAttrSrc) {
		pAttrSrc = &pExprIdentifier->GetAttr();
	} else if (pExprIdentifier->HasAttr()) {
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
	RefPtr<Value> pValue(frame.Retrieve(GetDottedSymbol()));
	if (pValue && pValue->IsType(VTYPE_VType)) {
		_pVType = &dynamic_cast<Value_VType&>(*pValue).GetVTypeThis();
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
	if (value.IsNil() && (IsSet(Flag::Nil) || IsOccurZeroOrOnce())) return value.Reference();
	return GetVType().Cast(value, GetFlags());
}

bool DeclArg::CheckFlagConfliction(Flags flags)
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
	return true;
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
		str += ss.IsCram()? "=" : " = ";
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
bool DeclArgList::IsValidArgNum(size_t nArgs) const
{
	size_t nMin = 0;
	for (const DeclArg* pDeclArg : *this) {
		if (pDeclArg->IsOccurOnce() || pDeclArg->IsOccurOnceOrMore()) {
			nMin++;
		} else {
			break;
		}
	}
	if (nArgs < nMin) return false;
	if (!empty()) {
		const DeclArg* pDeclArg = back();
		if (!(pDeclArg->IsOccurZeroOrMore() || pDeclArg->IsOccurOnceOrMore() || 
			  nArgs <= size())) return false;
	}
	return true;
}

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
