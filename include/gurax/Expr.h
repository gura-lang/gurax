//==============================================================================
// Expr.h
//==============================================================================
#ifndef GURAX_EXPR_H
#define GURAX_EXPR_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
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
// Expr_Unary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Unary : public Expr {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Expr> _pExprChild;
public:
	Expr_Unary(Expr* pExprChild) : Expr(typeInfo), _pExprChild(pExprChild) {
		_pExprChild->SetParent(this);
	}
	const Expr* GetChild() const { return _pExprChild.get(); }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Binary : public Expr {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Expr> _pExprLeft;
	RefPtr<Expr> _pExprRight;
public:
	Expr_Binary(Expr* pExprLeft, Expr* pExprRight) : Expr(typeInfo), _pExprLeft(pExprLeft), _pExprRight(pExprRight) {
		_pExprLeft->SetParent(this), _pExprRight->SetParent(this);
	}
	const Expr* GetLeft() const { return _pExprLeft.get(); }
	const Expr* GetRight() const { return _pExprRight.get(); }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Container
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Container : public Expr {
protected:
	RefPtr<ExprOwner> _pExprChildren;
public:
	Expr_Container(const TypeInfo& typeInfo) : Expr(typeInfo), _pExprChildren(new ExprOwner()) {}
	const ExprOwner& GetChildren() const { return *_pExprChildren; }
	void AddChild(Expr* pExpr);
};

//------------------------------------------------------------------------------
// Expr_Block
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Block : public Expr_Container {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Block() : Expr_Container(typeInfo) {}
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Lister
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Lister : public Expr_Container {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Lister() : Expr_Container(typeInfo) {}
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Composite : public Expr {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Expr> _pExprCar;
	RefPtr<ExprOwner> _pExprCdrs;
public:
	Expr_Composite(Expr* pExprCar) : Expr(typeInfo), _pExprCar(pExprCar), _pExprCdrs(new ExprOwner()) {
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
// Expr_Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Object : public Expr {
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Object> _pObject;
public:
	Expr_Object(Object* pObject) : Expr(typeInfo), _pObject(pObject) {}
	Object* GetObject() { return _pObject.get(); }
	const Object* GetObject() const { return _pObject.get(); }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Identifier
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Identifier : public Expr {
public:
	static const TypeInfo typeInfo;
protected:
	const Symbol* _pSymbol;
public:
	Expr_Identifier(const Symbol* pSymbol) : Expr(typeInfo), _pSymbol(pSymbol) {}
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	virtual void Exec() const;
};

}

#endif
