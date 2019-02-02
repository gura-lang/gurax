//==============================================================================
// Declaration.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------------
void Declaration::Bootup()
{
#if 0
			{ Gura_Symbol(closure),			FLAG_Closure		},
			{ Gura_Symbol(cut_extra_args),	FLAG_CutExtraArgs	},
			{ Gura_Symbol(dynamic_scope),	FLAG_DynamicScope	},
			{ Gura_Symbol(end_marker),		FLAG_EndMarker		},
			{ Gura_Symbol(finalizer),		FLAG_Finalizer		},
			{ Gura_Symbol(flat),			FLAG_Flat			},
			{ Gura_Symbol(fork),			FLAG_Fork			},
			{ Gura_Symbol(leader),			FLAG_Leader			},
			{ Gura_Symbol(listvar),			FLAG_ListVar		},
			{ Gura_Symbol(map),				FLAG_Map			},
			{ Gura_Symbol(nil),				FLAG_Nil			},
			{ Gura_Symbol(nocast),			FLAG_NoCast			},
			{ Gura_Symbol(nomap),			FLAG_NoMap			},
			{ Gura_Symbol(nonamed),			FLAG_NoNamed		},
			{ Gura_Symbol(private_),		FLAG_Private		},
			{ Gura_Symbol(privileged),		FLAG_Privileged		},
			{ Gura_Symbol(public_),			FLAG_Public			},
			{ Gura_Symbol(r),				FLAG_Read			},
			{ Gura_Symbol(symbol_func),		FLAG_SymbolFunc		},
			{ Gura_Symbol(trailer),			FLAG_Trailer		},
			{ Gura_Symbol(w),				FLAG_Write			},
#endif
}

bool Declaration::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, bool issueErrorFlag)
{
	_argInfoOwner.reserve(exprLinkCdr.GetSize());
	for (const Expr* pExpr = exprLinkCdr.GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		UInt32 flags = 0;
		const Attribute* pAttrSrc = nullptr;
		if (pExpr->IsType<Expr_Indexer>()) {
			const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(pExpr);
			pExpr = pExprEx->GetExprCar();
			if (!pExprEx->GetExprLinkCdr().IsEmpty()) {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "bracket must be empty");
				}
				return false;
			}
			pAttrSrc = &pExprEx->GetAttr();
		}
		if (!pExpr->IsType<Expr_Identifier>()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "declaration must be an indentifier");
			}
			return false;
		}
		const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExpr);
		if (!pAttrSrc) pAttrSrc = &pExprIdentifier->GetAttr();
		if (!pAttrSrc->GetSymbolsOpt().empty()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "optional attribute can not be declared");
			}
			return false;
		}
		RefPtr<Attribute> pAttr(new Attribute());
		pAttr->SetDottedSymbol(pAttrSrc->GetDottedSymbol().Reference());
		for (const Symbol* pSymbol : pAttrSrc->GetSymbols()) {
			
			pAttr->AddSymbol(pSymbol);
		}
		_argInfoOwner.push_back(new ArgInfo(pExprIdentifier->GetSymbol(), flags, pAttr.release()));
	}
	_pAttr.reset(attr.Reference());
	_validFlag = true;
	return true;
}

}
