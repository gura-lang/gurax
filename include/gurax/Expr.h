//==============================================================================
// Expr.h
//==============================================================================
#ifndef GURAX_EXPR_H
#define GURAX_EXPR_H
#include "Object.h"
#include "Operator.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
// [class hierarchy under Expr]
// Expr <-+- Expr_Node <------+- Expr_Object
//        |                   +- Expr_Identifier
//        |                   +- Expr_Suffixed
//        |                   `- Expr_Embedded
//        +- Expr_Unary <------- Expr_UnaryOp
//        +- Expr_Binary <----+- Expr_BinaryOp
//        |                   `- Expr_Assign
//        +- Expr_Collector <-+- Expr_Block
//        |                   +- Expr_Lister
//        |                   `- Expr_Iterer
//        `- Expr_Composite <-+- Expr_Indexer
//                            `- Expr_Caller
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr);
public:
	class TypeInfo {
	public:
		bool IsIdentical(const TypeInfo& typeInfo) const { return this == &typeInfo; }
	};
protected:
	const TypeInfo& _typeInfo;
	bool _silentFlag = false;
	RefPtr<StringReferable> _pPathNameSrc;
	int _lineNoTop = 0;
	int _lineNoBtm = 0;
	RefPtr<WeakPtr> _pwExprParent;
public:
	// Constructor
	Expr(const TypeInfo& typeInfo) : _typeInfo(typeInfo) {}
	// Copy constructor/operator
	Expr(const Expr& src) = delete;
	Expr& operator=(const Expr& src) = delete;
	// Move constructor/operator
	Expr(Expr&& src) = delete;
	Expr& operator=(Expr&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Expr() = default;
public:
	void SetSourceInfo(StringReferable *pPathNameSrc, int lineNoTop, int lineNoBtm) {
		_pPathNameSrc.reset(pPathNameSrc);
		_lineNoTop = lineNoTop, _lineNoBtm = lineNoBtm;
	}
	const char* GetPathNameSrc() const { return _pPathNameSrc->GetString(); }
	int GetLineNoTop() const { return _lineNoTop; }
	int GetLineNoBtm() const { return _lineNoBtm; }
	void SetSilentFlag(bool silentFlag) { _silentFlag = silentFlag; }
	bool GetSilentFlag() const { return _silentFlag; }
	void SetParent(const Expr* pExpr) { _pwExprParent.reset(pExpr->GetWeakPtr()); }
	template<typename T> bool IsType() const { return _typeInfo.IsIdentical(T::typeInfo); }
	template<typename T> static bool IsType(const Expr* pExpr) { return pExpr && pExpr->IsType<T>(); }
public:
	virtual void Exec() const = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Expr* pExpr) const { return this == pExpr; }
	bool IsEqualTo(const Expr* pExpr) const { return IsIdentical(pExpr); }
	bool IsLessThan(const Expr* pExpr) const { return this < pExpr; }
	String ToString() const { return "(expr)"; }
};

//------------------------------------------------------------------------------
// ExprList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprList : public std::vector<Expr*> {
public:
	void Exec() const;
};

//------------------------------------------------------------------------------
// ExprOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprOwner : public ExprList, public Referable {
protected:
	~ExprOwner() { Clear(); }
public:
	// Referable accessor
	Gurax_DeclareReferable(ExprOwner);
public:
	void Clear() {
		for (Expr* pExpr : *this) Expr::Delete(pExpr);
		clear();
	}
};

//------------------------------------------------------------------------------
// Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Node : public Expr {
public:
	Expr_Node(const TypeInfo& typeInfo) : Expr(typeInfo) {}
};

//------------------------------------------------------------------------------
// Expr_Unary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Unary : public Expr {
protected:
	const Operator* _pOperator;
	RefPtr<Expr> _pExprChild;
public:
	Expr_Unary(const TypeInfo& typeInfo, Expr* pExprChild) : Expr(typeInfo), _pExprChild(pExprChild) {
		_pExprChild->SetParent(this);
	}
	Expr* GetChild() { return _pExprChild.get(); }
	const Expr* GetChild() const { return _pExprChild.get(); }
};

//------------------------------------------------------------------------------
// Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Binary : public Expr {
protected:
	RefPtr<Expr> _pExprLeft;
	RefPtr<Expr> _pExprRight;
public:
	Expr_Binary(const TypeInfo& typeInfo, Expr* pExprLeft, Expr* pExprRight) :
			Expr(typeInfo), _pExprLeft(pExprLeft), _pExprRight(pExprRight) {
		_pExprLeft->SetParent(this), _pExprRight->SetParent(this);
	}
	Expr* GetLeft() { return _pExprLeft.get(); }
	Expr* GetRight() { return _pExprRight.get(); }
	const Expr* GetLeft() const { return _pExprLeft.get(); }
	const Expr* GetRight() const { return _pExprRight.get(); }
};

//------------------------------------------------------------------------------
// Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Collector : public Expr {
protected:
	RefPtr<ExprOwner> _pExprChildren;
public:
	Expr_Collector(const TypeInfo& typeInfo) : Expr(typeInfo), _pExprChildren(new ExprOwner()) {}
	const ExprOwner& GetChildren() const { return *_pExprChildren; }
	void AddChild(Expr* pExpr);
};

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Composite : public Expr {
protected:
	RefPtr<Expr> _pExprCar;
	RefPtr<ExprOwner> _pExprCdrs;
public:
	Expr_Composite(const TypeInfo& typeInfo, Expr* pExprCar) :
			Expr(typeInfo), _pExprCar(pExprCar), _pExprCdrs(new ExprOwner()) {
		_pExprCar->SetParent(this);
	}
	Expr* GetCar() { return _pExprCar.get(); }
	const Expr* GetCar() const { return _pExprCar.get(); }
	const ExprOwner& GetCdr() const { return *_pExprCdrs; }
	void AddCdr(Expr* pExpr);
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Object : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Object : public Expr_Node {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Object> _pObject;
public:
	Expr_Object(Object* pObject) : Expr_Node(typeInfo), _pObject(pObject) {}
	Object* GetObject() { return _pObject.get(); }
	const Object* GetObject() const { return _pObject.get(); }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Identifier : public Expr_Node {
public:
	static const TypeInfo typeInfo;
protected:
	const Symbol* _pSymbol;
protected:
	SymbolList _symbols;
	SymbolList _symbolsOpt;
	RefPtr<DottedSymbol> _pDottedSymbol;
public:
	Expr_Identifier(const Symbol* pSymbol) :
		Expr_Node(typeInfo), _pSymbol(pSymbol), _pDottedSymbol(new DottedSymbol()) {}
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	virtual void Exec() const;
	void AppendAttrSymbolFirst(const Symbol* pSymbol) { _pDottedSymbol->Append(pSymbol); }
	void AddAttrSymbol(const Symbol* pSymbol) { _symbols.push_back(pSymbol); }
	void AddAttrSymbolOpt(const Symbol* pSymbol) { _symbolsOpt.push_back(pSymbol); }
	const DottedSymbol& GetAttrSymbolFirst() const { return *_pDottedSymbol; }
};

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Suffixed : public Expr_Node {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<StringReferable> _pStrValue;
	const Symbol* _pSymbolSuffix;
	bool _numberFlag;
public:
	Expr_Suffixed(StringReferable* pStrValue, const Symbol* pSymbolSuffix, bool numberFlag) :
		Expr_Node(typeInfo), _pStrValue(pStrValue), _pSymbolSuffix(pSymbolSuffix), _numberFlag(numberFlag) {}
	const char* GetValue() const { return _pStrValue->GetString(); }
	const String& GetValueSTL() const { return _pStrValue->GetStringSTL(); }
	const Symbol* GetSuffix() const { return _pSymbolSuffix; }
	bool IsNumber() const { return _numberFlag; }
	bool IsString() const { return !_numberFlag; }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Embedded : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Embedded : public Expr_Node {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<StringReferable> _pStr;
public:
	Expr_Embedded(StringReferable* pStr) : Expr_Node(typeInfo), _pStr(pStr) {}
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_UnaryOp : public Expr_Unary {
public:
	static const TypeInfo typeInfo;
protected:
	const Operator* _pOperator;
public:
	Expr_UnaryOp(Expr* pExprChild, const Operator* pOperator) :
			Expr_Unary(typeInfo, pExprChild), _pOperator(pOperator) {}
	const Operator* GetOperator() const { return _pOperator; }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_BinaryOp : Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_BinaryOp : public Expr_Binary {
public:
	static const TypeInfo typeInfo;
protected:
	const Operator* _pOperator;
public:
	Expr_BinaryOp(Expr* pExprLeft, Expr* pExprRight, const Operator* pOperator) :
			Expr_Binary(typeInfo, pExprLeft, pExprRight), _pOperator(pOperator) {}
	const Operator* GetOperator() const { return _pOperator; }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Assign : Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Assign : public Expr_Binary {
public:
	static const TypeInfo typeInfo;
protected:
	const Operator* _pOperator;	// this may be nullptr
public:
	Expr_Assign(Expr* pExprLeft, Expr* pExprRight, const Operator* pOperator) :
			Expr_Binary(typeInfo, pExprLeft, pExprRight), _pOperator(pOperator) {}
	const Operator* GetOperator() const { return _pOperator; }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Member : Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Member : public Expr_Binary {
public:
	static const TypeInfo typeInfo;
protected:
	MemberMode _memberMode;
public:
	Expr_Member(Expr* pExprLeft, Expr* pExprRight, MemberMode memberMode) :
		Expr_Binary(typeInfo, pExprLeft, pExprRight), _memberMode(memberMode) {}
public:
	MemberMode GetMemberMode() const { return _memberMode; }
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Block : public Expr_Collector {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Block() : Expr_Collector(typeInfo) {}
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Lister : public Expr_Collector {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Lister() : Expr_Collector(typeInfo) {}
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Iterer : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Iterer : public Expr_Collector {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Iterer() : Expr_Collector(typeInfo) {}
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Indexer : public Expr_Composite {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Indexer(Expr* pExprCar) : Expr_Composite(typeInfo, pExprCar) {}
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Caller : public Expr_Composite {
public:
	static const TypeInfo typeInfo;
protected:
	SymbolList _attrs;
	SymbolList _attrsOpt;
	RefPtr<DottedSymbol> _pAttrFirst;
public:
	Expr_Caller(Expr* pExprCar) :
		Expr_Composite(typeInfo, pExprCar), _pAttrFirst(new DottedSymbol()) {}
public:
	virtual void Exec() const;
	void AppendAttrSymbolFirst(const Symbol* pSymbol) { _pAttrFirst->Append(pSymbol); }
	void AddAttrSymbol(const Symbol* pSymbol);
	void AddAttrSymbolOpt(const Symbol* pSymbol) { _attrsOpt.push_back(pSymbol); }
	const DottedSymbol& GetAttrSymbolFirst() const { return *_pAttrFirst; }
	Expr_Caller* GetLastTrailer() { return this; }
};

}

#endif
