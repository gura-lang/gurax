//==============================================================================
// Expr.h
//==============================================================================
#ifndef GURAX_EXPR_H
#define GURAX_EXPR_H
#include "Attribute.h"
#include "DeclCallable.h"
#include "Operator.h"
#include "Template.h"
#include "Value.h"

namespace Gurax {

class Composer;
class Processor;
class PUnit;

//------------------------------------------------------------------------------
// MemberMode
//------------------------------------------------------------------------------
enum class MemberMode {
	None,
	Normal,		// foo.bar
	MapAlong,	// foo:&bar .. map-along
	MapToIter,	// foo:*bar .. map-to-iterator
	MapToList,	// foo::bar .. map-to-list
};

class SymbolAssoc_MemberMode : public SymbolAssoc<MemberMode, MemberMode::None> {
public:
	SymbolAssoc_MemberMode() {
		Assoc(Gurax_SymbolMark(Period),			MemberMode::Normal);
		Assoc(Gurax_SymbolMark(ColonAnd),		MemberMode::MapAlong);
		Assoc(Gurax_SymbolMark(ColonAsterisk),	MemberMode::MapToIter);
		Assoc(Gurax_SymbolMark(ColonColon),		MemberMode::MapToList);
	}
	static SymbolAssoc* GetInstance() {
		return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_MemberMode());
	}
};

inline MemberMode SymbolToMemberMode(const Symbol* pSymbol)
{
	return SymbolAssoc_MemberMode::GetInstance()->ToAssociated(pSymbol);
}

inline const Symbol* MemberModeToSymbol(MemberMode memberMode)
{
	return SymbolAssoc_MemberMode::GetInstance()->ToSymbol(memberMode);
}

//------------------------------------------------------------------------------
// Expr
// [class hierarchy under Expr]
// Expr <-+- Expr_Node <------+- Expr_Value
//        |                   +- Expr_Identifier
//        |                   +- Expr_Suffixed
//        |                   +- Expr_Embedded
//        |                   `- Expr_Member
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
	class Visitor {
	public:
		virtual bool Visit(Expr* pExpr) = 0;
	};
	class Visitor_Prepare : public Visitor {
	public:
		virtual bool Visit(Expr* pExpr) override { return pExpr->DoPrepare(); }
	};
protected:
	const TypeInfo& _typeInfo;
	bool _silentFlag = false;
	RefPtr<StringReferable> _pPathNameSrc;
	int _lineNoTop = 0;
	int _lineNoBtm = 0;
	RefPtr<Expr> _pExprNext;
	RefPtr<WeakPtr> _pwExprPrev;
	RefPtr<WeakPtr> _pwExprParent;
	const PUnit* _pPUnitTop;
public:
	// Constructor
	Expr(const TypeInfo& typeInfo) : _typeInfo(typeInfo), _pPUnitTop(nullptr) {}
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
	void SetExprNext(Expr* pExprNext) {
		_pExprNext.reset(pExprNext);
		pExprNext->_pwExprPrev.reset(GetWeakPtr());
	}
	Expr* GetExprNext() { return _pExprNext.get(); }
	const Expr* GetExprNext() const { return _pExprNext.get(); }
	Expr* LockExprPrev() const { return _pwExprPrev? _pwExprPrev->Lock() : nullptr; }
	void SetExprParent(const Expr* pExprParent) { _pwExprParent.reset(pExprParent->GetWeakPtr()); }
	Expr* LockExprParent() const { return _pwExprParent? _pwExprParent->Lock() : nullptr; }
	void SetPUnitTop(const PUnit* pPUnit) { if (!_pPUnitTop) _pPUnitTop = pPUnit; }
	const PUnit* GetPUnitTop() const { return _pPUnitTop; }
	int CalcIndentLevel() const;
	String MakeIndent(const StringStyle& ss) const;
	template<typename T> bool IsType() const { return _typeInfo.IsIdentical(T::typeInfo); }
	template<typename T> static bool IsType(const Expr* pExpr) { return pExpr && pExpr->IsType<T>(); }
	bool Prepare() {
		Visitor_Prepare visitor;
		return Traverse(visitor);
	}
	static size_t CountSequence(const Expr* pExpr);
	static void ComposeForArgSlot(Composer& composer, const Expr* pExpr);
	static void ComposeSequence(Composer& composer, const Expr* pExpr);
public:
	// Virtual functions
	virtual bool Traverse(Visitor& visitor) = 0;
	virtual void Compose(Composer& composer) const = 0;
	virtual void ComposeForAssignment(
		Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const;
	virtual void ComposeForArgSlot(Composer& composer) const;
	virtual Attribute* GetAttrToAppend() { return nullptr; }
	virtual bool DoPrepare() { return true; }
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
	bool Traverse(Expr::Visitor& visitor);
	void Compose(Composer& composer) const;
	void SetExprParent(const Expr* pExprParent);
};

//------------------------------------------------------------------------------
// ExprOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprOwner : public ExprList, public Referable {
public:
	// Referable accessor
	Gurax_DeclareReferable(ExprOwner);
protected:
	~ExprOwner() { Clear(); }
public:
	void Clear() {
		for (Expr* pExpr : *this) Expr::Delete(pExpr);
		clear();
	}
};

//------------------------------------------------------------------------------
// ExprLink
//------------------------------------------------------------------------------
class ExprLink : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ExprLink);
private:
	RefPtr<Expr> _pExprHead;
	Expr* _pExprTail;
public:
	// Constructor
	ExprLink() : _pExprTail(nullptr) {}
	// Copy constructor/operator
	ExprLink(const ExprLink& src) = delete;
	ExprLink& operator=(const ExprLink& src) = delete;
	// Move constructor/operator
	ExprLink(ExprLink&& src) = delete;
	ExprLink& operator=(ExprLink&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ExprLink() = default;
public:	
	bool IsEmpty() const { return _pExprHead.get() == nullptr; }
	Expr* GetExprHead() { return _pExprHead.get(); }
	const Expr* GetExprHead() const { return _pExprHead.get(); }
	Expr* GetExprTail() { return _pExprTail; }
	const Expr* GetExprTail() const { return _pExprTail; }
	void AddExpr(Expr* pExpr) {
		if (_pExprTail) {
			_pExprTail->SetExprNext(pExpr);
		} else {
			_pExprHead.reset(pExpr);
		}
		_pExprTail = pExpr;
	}
	size_t CountSequence() const;
	void SetExprParent(const Expr* pExprParent);
	bool Traverse(Expr::Visitor& visitor);
};

//------------------------------------------------------------------------------
// Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Node : public Expr {
public:
	Expr_Node(const TypeInfo& typeInfo) : Expr(typeInfo) {}
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		return visitor.Visit(this);
	}
};

//------------------------------------------------------------------------------
// Expr_Unary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Unary : public Expr {
protected:
	RefPtr<Expr> _pExprChild;
public:
	Expr_Unary(const TypeInfo& typeInfo, Expr* pExprChild) : Expr(typeInfo), _pExprChild(pExprChild) {
		_pExprChild->SetExprParent(this);
	}
	Expr* GetExprChild() { return _pExprChild.get(); }
	const Expr* GetExprChild() const { return _pExprChild.get(); }
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (_pExprChild && !_pExprChild->Traverse(visitor)) return false;
		return true;
	}
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
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (_pExprLeft && !_pExprLeft->Traverse(visitor)) return false;
		if (_pExprRight && !_pExprRight->Traverse(visitor)) return false;
		return true;
	}
};

//------------------------------------------------------------------------------
// Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Collector : public Expr {
protected:
	RefPtr<ExprLink> _pExprLinkElem;
public:
	Expr_Collector(const TypeInfo& typeInfo, ExprLink* pExprLinkElem) :
		Expr(typeInfo), _pExprLinkElem(pExprLinkElem) {
		_pExprLinkElem->SetExprParent(this);
	}
	const ExprLink& GetExprLinkElem() const { return *_pExprLinkElem; }
	size_t CountExprElem() const { return _pExprLinkElem->CountSequence(); }
	bool HasExprElem() const { return !_pExprLinkElem->IsEmpty(); }
	const Expr* GetExprElemHead() const { return _pExprLinkElem->GetExprHead(); }
	void AddExprElem(Expr* pExprElem);
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (!_pExprLinkElem->Traverse(visitor)) return false;
		return true;
	}
};

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Composite : public Expr {
protected:
	RefPtr<Expr> _pExprCar;
	RefPtr<ExprLink> _pExprLinkCdr;
	RefPtr<Attribute> _pAttr;
public:
	Expr_Composite(const TypeInfo& typeInfo) :
		Expr(typeInfo), _pExprLinkCdr(new ExprLink()), _pAttr(new Attribute()) {}
	void SetExprCar(Expr* pExprCar) {
		_pExprCar.reset(pExprCar);
		_pExprCar->SetExprParent(this);
	}
	Expr* GetExprCar() { return _pExprCar.get(); }
	const Expr* GetExprCar() const { return _pExprCar.get(); }
	void SetExprLinkCdr(ExprLink* pExprLinkCdr) {
		_pExprLinkCdr.reset(pExprLinkCdr);
		_pExprLinkCdr->SetExprParent(this);
	}
	const ExprLink& GetExprLinkCdr() const { return *_pExprLinkCdr; }
	bool HasExprCdr() const { return !_pExprLinkCdr->IsEmpty(); }
	const Expr* GetExprCdrHead() const { return _pExprLinkCdr->GetExprHead(); }
	size_t CountExprCdr() const { return GetExprLinkCdr().CountSequence(); }
	void AddExprCdr(Expr* pExprCdr);
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (_pExprCar && !_pExprCar->Traverse(visitor)) return false;
		if (!_pExprLinkCdr->Traverse(visitor)) return false;
		return true;
	}
	virtual Attribute* GetAttrToAppend() override { return &GetAttr(); }
};

//------------------------------------------------------------------------------
// Expr_Value : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Value : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Value);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Value> _pValue;
	RefPtr<StringReferable> _pStrSource;
public:
	Expr_Value(Value* pValue) : Expr_Node(typeInfo), _pValue(pValue) {}
	Expr_Value(Value* pValue, StringReferable* pStrSource) :
		Expr_Node(typeInfo), _pValue(pValue), _pStrSource(pStrSource) {}
	Value* GetValue() { return _pValue.get(); }
	const Value* GetValue() const { return _pValue.get(); }
	bool HasSource() const { return _pStrSource.get() != nullptr; }
	const char* GetSource() const { return _pStrSource->GetString(); }
	const String& GetSourceSTL() const { return _pStrSource->GetStringSTL(); }
public:
	virtual void Compose(Composer& composer) const override;
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
	RefPtr<Attribute> _pAttr;
public:
	Expr_Identifier(const Symbol* pSymbol) :
		Expr_Node(typeInfo), _pSymbol(pSymbol), _pAttr(new Attribute()) {}
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	String ToString(const StringStyle& ss, const char* strInsert) const;
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
	virtual void ComposeForAssignment(
		Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const override;
	virtual String ToString(const StringStyle& ss) const override { return ToString(ss, ""); }
	virtual Attribute* GetAttrToAppend() override { return &GetAttr(); }
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
	RefPtr<StringReferable> _pStrSegment;
	const Symbol* _pSymbolSuffix;
	bool _numberFlag;
public:
	Expr_Suffixed(StringReferable* pStrSegment, const Symbol* pSymbolSuffix, bool numberFlag) :
		Expr_Node(typeInfo), _pStrSegment(pStrSegment), _pSymbolSuffix(pSymbolSuffix), _numberFlag(numberFlag) {}
	const char* GetSegment() const { return _pStrSegment->GetString(); }
	const String& GetSegmentSTL() const { return _pStrSegment->GetStringSTL(); }
	const Symbol* GetSuffix() const { return _pSymbolSuffix; }
	bool IsNumber() const { return _numberFlag; }
	bool IsString() const { return !_numberFlag; }
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
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
	RefPtr<Template> _pTempl;
	RefPtr<StringReferable> _pStr;
public:
	Expr_Embedded(Template* pTempl, StringReferable* pStr) : Expr_Node(typeInfo), _pTempl(pTempl), _pStr(pStr) {}
	const Template& GetTemplate() const { return *_pTempl; }
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Expr_Member : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Member : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Member);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<Expr> _pExprTarget;
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	MemberMode _memberMode;
public:
	Expr_Member(Expr* pExprTarget, const Symbol* pSymbol, Attribute* pAttr, MemberMode memberMode) :
		Expr_Node(typeInfo), _pExprTarget(pExprTarget), _pSymbol(pSymbol), _pAttr(pAttr),
		_memberMode(memberMode) {}
public:
	const Expr* GetExprTarget() const { return _pExprTarget.get(); }	
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
	MemberMode GetMemberMode() const { return _memberMode; }
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
	virtual void ComposeForAssignment(
		Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const override;
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
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
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
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
	virtual void ComposeForArgSlot(Composer& composer) const override;
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
	// Virtual functions of Expr
	virtual bool DoPrepare() override;
	virtual void Compose(Composer& composer) const override;
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
	Expr_Root(ExprLink* pExprLinkElem) : Expr_Collector(typeInfo, pExprLinkElem) {}
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
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
	RefPtr<ExprLink> _pExprLinkParam;		// this may be nullptr
	RefPtr<DeclCallable> _pDeclCallable;
public:
	explicit Expr_Block(ExprLink* pExprLinkElem) :
		Expr_Collector(typeInfo, pExprLinkElem), _pDeclCallable(new DeclCallable()) {}
	void SetExprLinkParam(ExprLink* pExprLinkParam) {
		_pExprLinkParam.reset(pExprLinkParam);
		_pExprLinkParam->SetExprParent(this);
	}
	bool HasExprParam() const { return _pExprLinkParam && !_pExprLinkParam->IsEmpty(); }
	const ExprLink& GetExprLinkParam() const { return *_pExprLinkParam; }
	const Expr* GetExprParamHead() const {
		return _pExprLinkParam? _pExprLinkParam->GetExprHead() : nullptr;
	}
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	bool PrepareDeclCallable() {
		if (!_pExprLinkParam) return true;
		return _pDeclCallable->Prepare(GetExprLinkParam(), *Attribute::Empty, nullptr);
	}
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!Expr_Collector::Traverse(visitor)) return false;
		if (_pExprLinkParam && !_pExprLinkParam->Traverse(visitor)) return false;
		return true;
	}
	virtual bool DoPrepare() override;
	virtual void Compose(Composer& composer) const override;
	virtual String ToString(const StringStyle& ss) const override;
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
	Expr_Lister(ExprLink* pExprLinkElem) : Expr_Collector(typeInfo, pExprLinkElem) {}
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
	virtual void ComposeForAssignment(
		Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const override;
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
	Expr_Iterer(ExprLink* pExprLinkElem) : Expr_Collector(typeInfo, pExprLinkElem) {}
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
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
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) const override;
	virtual void ComposeForAssignment(
		Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const override;
	virtual String ToString(const StringStyle& ss) const override { return ToString(ss, ""); }
	String ToString(const StringStyle& ss, const char* strInsert) const;
	virtual Attribute* GetAttrToAppend() override { return &GetAttr(); }
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
	RefPtr<DeclCallable> _pDeclCallable;
	RefPtr<Expr_Block> _pExprBlock;		// this may be nullptr
	RefPtr<Expr_Caller> _pExprTrailer;	// this may be nullptr
public:
	Expr_Caller() : Expr_Composite(typeInfo), _pDeclCallable(new DeclCallable()) {}
public:
	bool PrepareDeclCallable() {
		return _pDeclCallable->Prepare(GetExprLinkCdr(), GetAttr(), GetExprBlock());
	}
	void SetExprBlock(Expr_Block* pExprBlock) {
		_pExprBlock.reset(pExprBlock);
		_pExprBlock->SetExprParent(this);
	}
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	bool HasExprBlock() const { return _pExprBlock.get() != nullptr; }
	const Expr_Block* GetExprBlock() const { return _pExprBlock.get(); }
	void SetExprTrailer(Expr_Caller* pExprTrailer);
	void AppendExprTrailer(Expr_Caller* pExprTrailer);
	bool HasExprTrailer() const { return _pExprTrailer.get() != nullptr; }
	Expr_Caller* GetExprTrailer() { return _pExprTrailer.get(); }
	const Expr_Caller* GetExprTrailer() const { return _pExprTrailer.get(); }
	Expr_Caller* GetExprTrailerLast();
	bool IsTrailer() const { return false; }
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!Expr_Composite::Traverse(visitor)) return false;
		if (_pExprBlock && !_pExprBlock->Traverse(visitor)) return false;
		if (_pExprTrailer && !_pExprTrailer->Traverse(visitor)) return false;
		return true;
	}
	virtual void Compose(Composer& composer) const override;
	virtual void ComposeForAssignment(
		Composer& composer, const Expr* pExprAssigned, const Operator* pOperator) const override;
	virtual Attribute* GetAttrToAppend() override { return &GetExprTrailerLast()->GetAttr(); }
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
