//==============================================================================
// Expr.h
//==============================================================================
#ifndef GURAX_EXPR_H
#define GURAX_EXPR_H
#include "Attribute.h"
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
//        +- Expr_Collector <-+- Expr_Root
//        |                   +- Expr_Block
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
	void SetExprParent(const Expr* pExprParent) { _pwExprParent.reset(pExprParent->GetWeakPtr()); }
	Expr* LockExprParent() const { return _pwExprParent? _pwExprParent->Lock() : nullptr; }
	int CalcIndentLevel() const;
	String ComposeIndent(const StringStyle& ss) const;
	template<typename T> bool IsType() const { return _typeInfo.IsIdentical(T::typeInfo); }
	template<typename T> static bool IsType(const Expr* pExpr) { return pExpr && pExpr->IsType<T>(); }
public:
	virtual void Exec() const = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Expr& expr) const { return this == &expr; }
	bool IsEqualTo(const Expr& expr) const { return IsIdentical(expr); }
	bool IsLessThan(const Expr& expr) const { return this < &expr; }
	String ToString() const { return ToString(StringStyle::Empty); }
	virtual String ToString(const StringStyle& ss) const = 0;
};

//------------------------------------------------------------------------------
// ExprList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprList : public std::vector<Expr*> {
public:
	static const ExprList Empty;
public:
	void Exec() const;
	void SetExprParent(const Expr* pExprParent);
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
		_pExprChild->SetExprParent(this);
	}
	Expr* GetExprChild() { return _pExprChild.get(); }
	const Expr* GetExprChild() const { return _pExprChild.get(); }
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
		_pExprLeft->SetExprParent(this), _pExprRight->SetExprParent(this);
	}
	Expr* GetExprLeft() { return _pExprLeft.get(); }
	Expr* GetExprRight() { return _pExprRight.get(); }
	const Expr* GetExprLeft() const { return _pExprLeft.get(); }
	const Expr* GetExprRight() const { return _pExprRight.get(); }
};

//------------------------------------------------------------------------------
// Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Collector : public Expr {
protected:
	RefPtr<ExprOwner> _pExprOwnerElem;
public:
	Expr_Collector(const TypeInfo& typeInfo, ExprOwner* pExprOwnerElem) :
		Expr(typeInfo), _pExprOwnerElem(pExprOwnerElem) {
		_pExprOwnerElem->SetExprParent(this);
	}
	ExprOwner& GetExprOwnerElem() { return *_pExprOwnerElem; }
	const ExprList& GetExprsElem() const { return *_pExprOwnerElem; }
	ExprOwner* ReleaseExprOwnerElem() { return _pExprOwnerElem.release(); }
	void AddExprElem(Expr* pExprElem);
};

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Composite : public Expr {
protected:
	RefPtr<Expr> _pExprCar;
	RefPtr<ExprOwner> _pExprOwnerCdr;
	RefPtr<Attribute> _pAttr;
public:
	Expr_Composite(const TypeInfo& typeInfo) :
		Expr(typeInfo), _pExprOwnerCdr(new ExprOwner()), _pAttr(new Attribute()) {}
	void SetExprCar(Expr* pExprCar) {
		_pExprCar.reset(pExprCar);
		_pExprCar->SetExprParent(this);
	}
	Expr* GetExprCar() { return _pExprCar.get(); }
	const Expr* GetExprCar() const { return _pExprCar.get(); }
	void SetExprOwnerCdr(ExprOwner* pExprOwnerCdr) {
		_pExprOwnerCdr.reset(pExprOwnerCdr);
		_pExprOwnerCdr->SetExprParent(this);
	}
	const ExprList& GetExprsCdr() const { return *_pExprOwnerCdr; }
	void AddExprCdr(Expr* pExprCdr);
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	virtual void Exec() const;
};

//------------------------------------------------------------------------------
// Expr_Object : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Object : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Object);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Object> _pObject;
	RefPtr<StringReferable> _pStrSource;
public:
	Expr_Object(Object* pObject) : Expr_Node(typeInfo), _pObject(pObject) {}
	Expr_Object(Object* pObject, StringReferable* pStrSource) :
		Expr_Node(typeInfo), _pObject(pObject), _pStrSource(pStrSource) {}
	Object* GetObject() { return _pObject.get(); }
	const Object* GetObject() const { return _pObject.get(); }
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Identifier : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Identifier);
public:
	static const TypeInfo typeInfo;
protected:
	const Symbol* _pSymbol;
protected:
	RefPtr<Attribute> _pAttr;
public:
	Expr_Identifier(const Symbol* pSymbol) :
		Expr_Node(typeInfo), _pSymbol(pSymbol), _pAttr(new Attribute()) {}
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
};

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Suffixed : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Suffixed);
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
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Embedded : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Embedded : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Embedded);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<StringReferable> _pStr;
public:
	Expr_Embedded(StringReferable* pStr) : Expr_Node(typeInfo), _pStr(pStr) {}
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_UnaryOp : public Expr_Unary {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_UnaryOp);
public:
	static const TypeInfo typeInfo;
protected:
	const Operator* _pOperator;
public:
	Expr_UnaryOp(Expr* pExprChild, const Operator* pOperator) :
			Expr_Unary(typeInfo, pExprChild), _pOperator(pOperator) {}
	const Operator* GetOperator() const { return _pOperator; }
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_BinaryOp : Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_BinaryOp : public Expr_Binary {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_BinaryOp);
public:
	static const TypeInfo typeInfo;
protected:
	const Operator* _pOperator;
public:
	Expr_BinaryOp(Expr* pExprLeft, Expr* pExprRight, const Operator* pOperator) :
			Expr_Binary(typeInfo, pExprLeft, pExprRight), _pOperator(pOperator) {}
	const Operator* GetOperator() const { return _pOperator; }
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Assign : Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Assign : public Expr_Binary {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Assign);
public:
	static const TypeInfo typeInfo;
protected:
	const Operator* _pOperator;	// this may be nullptr
public:
	Expr_Assign(Expr* pExprLeft, Expr* pExprRight, const Operator* pOperator) :
			Expr_Binary(typeInfo, pExprLeft, pExprRight), _pOperator(pOperator) {}
	const Operator* GetOperator() const { return _pOperator; }
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Member : Expr_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Member : public Expr_Binary {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Member);
public:
	static const TypeInfo typeInfo;
protected:
	MemberMode _memberMode;
public:
	Expr_Member(Expr* pExprLeft, Expr* pExprRight, MemberMode memberMode) :
		Expr_Binary(typeInfo, pExprLeft, pExprRight), _memberMode(memberMode) {}
public:
	MemberMode GetMemberMode() const { return _memberMode; }
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Root : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Root : public Expr_Collector {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Root);
public:
	static const TypeInfo typeInfo;
public:
	Expr_Root(ExprOwner* pExprOwnerElem) : Expr_Collector(typeInfo, pExprOwnerElem) {}
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Block : public Expr_Collector {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Block);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<ExprOwner> _pExprOwnerParam;	// this may be nullptr
public:
	explicit Expr_Block(ExprOwner* pExprOwnerElem) : Expr_Collector(typeInfo, pExprOwnerElem) {}
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
	void SetExprOwnerParam(ExprOwner* pExprOwnerParam) {
		_pExprOwnerParam.reset(pExprOwnerParam);
		_pExprOwnerParam->SetExprParent(this);
	}
	bool HasExprsParam() const { return _pExprOwnerParam.get() != nullptr; }
	const ExprList& GetExprsParam() const { return *_pExprOwnerParam; }
};

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Lister : public Expr_Collector {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Lister);
public:
	static const TypeInfo typeInfo;
public:
	Expr_Lister(ExprOwner* pExprOwnerElem) : Expr_Collector(typeInfo, pExprOwnerElem) {}
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Iterer : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Iterer : public Expr_Collector {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Iterer);
public:
	static const TypeInfo typeInfo;
public:
	Expr_Iterer(ExprOwner* pExprOwnerElem) : Expr_Collector(typeInfo, pExprOwnerElem) {}
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Indexer : public Expr_Composite {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Indexer);
public:
	static const TypeInfo typeInfo;
public:
	Expr_Indexer() : Expr_Composite(typeInfo) {}
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Caller : public Expr_Composite {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Caller);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Expr_Block> _pExprBlock;		// this may be nullptr
	RefPtr<Expr_Caller> _pExprTrailer;	// this may be nullptr
public:
	Expr_Caller() : Expr_Composite(typeInfo) {}
public:
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
	void SetExprBlock(Expr_Block* pExprBlock) {
		_pExprBlock.reset(pExprBlock);
		_pExprBlock->SetExprParent(this);
	}
	bool HasExprBlock() const { return _pExprBlock.get() != nullptr; }
	const Expr_Block* GetExprBlock() const { return _pExprBlock.get(); }
	void SetExprTrailer(Expr_Caller* pExprTrailer);
	void AppendExprTrailer(Expr_Caller* pExprTrailer);
	bool HasExprTrailer() const { return _pExprTrailer.get() != nullptr; }
	Expr_Caller* GetExprTrailer() { return _pExprTrailer.get(); }
	const Expr_Caller* GetExprTrailer() const { return _pExprTrailer.get(); }
	Expr_Caller* GetExprTrailerLast();
	bool IsTrailer() const { return false; }
};

}

#endif
