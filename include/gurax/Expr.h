//==============================================================================
// Expr.h
//==============================================================================
#ifndef GURAX_EXPR_H
#define GURAX_EXPR_H
#include "Attribute.h"
#include "DeclCallable.h"
#include "Operator.h"
#include "SuffixMgr.h"

namespace Gurax {

class Composer;
class Iterator;
class Processor;
class PUnit;
class Value;

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

class GURAX_DLLDECLARE SymbolAssoc_MemberMode : public SymbolAssoc<MemberMode, MemberMode::None> {
public:
	SymbolAssoc_MemberMode() {
		Assoc(Gurax_SymbolMark(Period),			MemberMode::Normal);
		Assoc(Gurax_SymbolMark(ColonAnd),		MemberMode::MapAlong);
		Assoc(Gurax_SymbolMark(ColonAsterisk),	MemberMode::MapToIter);
		Assoc(Gurax_SymbolMark(ColonColon),		MemberMode::MapToList);
	}
	static const SymbolAssoc& GetInstance() {
		static SymbolAssoc* pSymbolAssoc = nullptr;
		return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_MemberMode());
	}
};

inline MemberMode SymbolToMemberMode(const Symbol* pSymbol)
{
	return SymbolAssoc_MemberMode::GetInstance().ToAssociated(pSymbol);
}

inline const Symbol* MemberModeToSymbol(MemberMode memberMode)
{
	return SymbolAssoc_MemberMode::GetInstance().ToSymbol(memberMode);
}

//------------------------------------------------------------------------------
// Expr
// [class hierarchy under Expr]
// Expr <-+- Expr_Node <------+- Expr_Value
//        |                   +- Expr_Identifier
//        |                   +- Expr_String
//        |                   +- Expr_Suffixed
//        |                   `- Expr_Member
//        +- Expr_Unary <------- Expr_UnaryOp
//        +- Expr_Binary <----+- Expr_BinaryOp
//        |                   `- Expr_Assign
//        +- Expr_Collector <-+- Expr_Root
//        |                   +- Expr_Block
//        |                   +- Expr_Lister
//        |                   `- Expr_Tuple
//        `- Expr_Composite <-+- Expr_Indexer
//                            `- Expr_Caller
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr);
public:
	enum class TypeId {
		Empty,
		Member,
		Value,
		Identifier,
		String,
		Suffixed,
		UnaryOp,
		BinaryOp,
		Assign,
		Root,
		Block,
		Tuple,
		Lister,
		Indexer,
		Caller,
		TmplString,
		TmplScript,
		Template,
	};
	class GURAX_DLLDECLARE TypeInfo {
	private:
		TypeId _typeId;
		const char* _name;
	public:
		TypeInfo(TypeId typeId, const char* name) : _typeId(typeId), _name(name) {}
		TypeId GetTypeId() const { return _typeId; }
		const char* GetName() const { return _name; }
		bool IsIdentical(const TypeInfo& typeInfo) const { return this == &typeInfo; }
	};
	class GURAX_DLLDECLARE Visitor {
	public:
		virtual bool Visit(Expr* pExpr) = 0;
	};
	class GURAX_DLLDECLARE Visitor_Prepare : public Visitor {
	public:
		virtual bool Visit(Expr* pExpr) override { return pExpr->DoPrepare(); }
	};
	class GURAX_DLLDECLARE Visitor_GatherArgSymbols : public Visitor {
	private:
		SymbolList& _symbolList;
	public:
		Visitor_GatherArgSymbols(SymbolList& symbolList) : _symbolList(symbolList) {}
	public:
		virtual bool Visit(Expr* pExpr) override;
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
	const PUnit* _pPUnitFirst;
	const PUnit* _pPUnitEnd;
	const PUnit* _pPUnitSubFirst;
public:
	static RefPtr<Expr> Empty;
public:
	// Constructor
	Expr(const TypeInfo& typeInfo) :
		_typeInfo(typeInfo), _pPathNameSrc(StringReferable::Empty->Reference()),
		_pPUnitFirst(nullptr), _pPUnitEnd(nullptr), _pPUnitSubFirst(nullptr) {}
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
	static void Bootup();
	void SetSourceInfo(StringReferable *pPathNameSrc, int lineNoTop, int lineNoBtm) {
		_pPathNameSrc.reset(pPathNameSrc);
		_lineNoTop = lineNoTop, _lineNoBtm = lineNoBtm;
	}
	const char* GetPathNameSrc() const { return _pPathNameSrc->GetString(); }
	const StringReferable& GetPathNameSrcReferable() const { return *_pPathNameSrc; }
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
	void SetPUnitFirst(const PUnit* pPUnit) { if (!_pPUnitFirst) _pPUnitFirst = pPUnit; }
	const PUnit* GetPUnitFirst() const { return _pPUnitFirst; }
	void SetPUnitEnd(const PUnit* pPUnit) { if (!_pPUnitEnd) _pPUnitEnd = pPUnit; }
	const PUnit* GetPUnitEnd() const { return _pPUnitEnd; }
	void SetPUnitSubFirst(const PUnit* pPUnit) { if (!_pPUnitSubFirst) _pPUnitSubFirst = pPUnit; }
	const PUnit* GetPUnitSubFirst() const { return _pPUnitSubFirst; }
public:
	void ComposeOrNil(Composer& composer);
	Iterator* EachPUnit() const;
	int CalcIndentLevel() const;
	const TypeInfo& GetTypeInfo() const { return _typeInfo; }
	TypeId GetTypeId() const { return _typeInfo.GetTypeId(); }
	template<typename T> bool IsType() const { return _typeInfo.IsIdentical(T::typeInfo); }
	template<typename T> static bool IsType(const Expr* pExpr) { return pExpr && pExpr->IsType<T>(); }
	bool Prepare();
	bool PrepareAndCompose(Composer& composer);
	SymbolList GatherArgSymbols() const;
	Value* Eval(Processor& processor) const;
	Value* Eval(Processor& processor, Event& event) const;
	Value* Eval(Processor& processor, Argument& argument) const;
	Value* Eval(Processor& processor, Argument& argument, Event& event) const;
	static size_t CountSequence(const Expr* pExpr);
	bool IsPureAssign() const;
	void ComposeSequence(Composer& composer, Expr* pExpr) const;
public:
	// Virtual functions
	virtual bool HasSymbol(const Symbol* pSymbol) const { return false; }
	virtual bool HasPureSymbol(const Symbol* pSymbol) const { return false; }
	virtual bool IsEmpty() const { return false; }
	virtual bool IsStatement(const Symbol* pSymbol) const { return false; }
	virtual bool IsCollector() const { return false; }
	virtual bool IsUnaryOp(OpType opType) const { return false; }
	virtual bool IsBinaryOp(OpType opType) const { return false; }
	virtual bool IsSuffixed(SuffixMgr::Mode mode) const { return false; }
	virtual bool IsShortCircuitOperator() const { return false; }
	virtual bool IsDeclArgWithDefault(Expr_Binary** ppExpr) const { return false; }
	virtual const Symbol* GetPureSymbol() const { return nullptr; }
	virtual DeclCallable* RetrieveDeclCallable() const { return nullptr; } // used by Template
	virtual bool Traverse(Visitor& visitor) = 0;
	virtual void Compose(Composer& composer) = 0;
	virtual void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag);
	virtual void ComposeWithinLister(Composer& composer);
	virtual void ComposeWithinTuple(Composer& composer);
	virtual void ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol);
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol);
	virtual void ComposeWithinAssignmentInClass(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag);
	virtual void ComposeWithinArgSlot(Composer& composer);
	virtual void ComposeReferencer(Composer& composer);
	virtual Attribute* GetAttrToAppend() { return nullptr; }
	virtual void ResetAttrToAppend() {}
	virtual bool DoPrepare() { return true; }
public:
	// Virtual functions for structure inspecting
	virtual const Expr* InspectChild() const { return nullptr; }
	virtual const Expr* InspectLeft() const { return nullptr; }
	virtual const Expr* InspectRight() const { return nullptr; }
	virtual const Expr* InspectCar() const { return nullptr; }
	virtual const Expr* InspectTarget() const { return nullptr; }
	virtual const Expr* InspectBlock() const { return nullptr; }
	virtual const Expr* InspectTrailer() const { return nullptr; }
	virtual StringReferable* InspectStringReferable() const { return nullptr; }
	virtual const Symbol* InspectSymbol() const { return nullptr; }
	virtual const Attribute* InspectAttr() const { return nullptr; }
	virtual Value* InspectValue() const { return nullptr; }
	virtual Operator* InspectOperator() const { return nullptr; }
	virtual const Symbol* InspectModeAsSymbol() const { return nullptr; }
	virtual Iterator* EachParam() const;
	virtual Iterator* EachElem() const;
public:
	virtual size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Expr& expr) const { return IsIdentical(expr); }
	virtual bool IsLessThan(const Expr& expr) const { return this < &expr; }
	static int Compare(const Expr& expr1, const Expr& expr2) {
		return expr1.IsLessThan(expr2)? -1 : expr2.IsLessThan(expr1)? +1 : 0;
	}
public:
	bool IsIdentical(const Expr& expr) const { return this == &expr; }
	static String TextizeExprList(const StringStyle& ss, const Expr* pExpr, int indentLevel);
	String ToString() const { return ToString(StringStyle::Empty, 0); }
	virtual String ToString(const StringStyle& ss, int indentLevel = 0) const = 0;
};

//------------------------------------------------------------------------------
// ExprList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprList : public ListBase<Expr*> {
public:
	static const ExprList Empty;
public:
	bool Traverse(Expr::Visitor& visitor);
	void Compose(Composer& composer);
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
class GURAX_DLLDECLARE ExprLink : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ExprLink);
private:
	RefPtr<Expr> _pExprFirst;
	Expr* _pExprLast;
public:
	// Constructor
	ExprLink() : _pExprLast(nullptr) {}
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
	bool IsEmpty() const { return _pExprFirst.get() == nullptr; }
	bool HasSingle() const { return _pExprLast && _pExprFirst.get() == _pExprLast; }
	Expr* GetExprFirst() const { return _pExprFirst.get(); }
	Expr* GetExprLast() const{ return _pExprLast; }
	void AddExpr(Expr* pExpr) {
		if (_pExprLast) {
			_pExprLast->SetExprNext(pExpr);
		} else {
			_pExprFirst.reset(pExpr);
		}
		_pExprLast = pExpr;
	}
	void RemoveExprFirst() {
		if (_pExprFirst) {
			RefPtr<Expr> pExprFirst(_pExprFirst.release());
			if (pExprFirst->GetExprNext()) {
				_pExprFirst.reset(pExprFirst->GetExprNext()->Reference());
			} else {
				_pExprLast = nullptr;
			}
		}
	}
	size_t CountSequence() const;
	void SetExprParent(const Expr* pExprParent);
	bool Traverse(Expr::Visitor& visitor);
	void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) const;
	void ComposeWithinArgSlot(Composer& composer) const;
	Iterator* CreateIterator() const;
};

//------------------------------------------------------------------------------
// Expr_Empty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Empty : public Expr {
public:
	static const TypeInfo typeInfo;
public:
	Expr_Empty() : Expr(typeInfo) {}
public:
	// Virtual functions of Expr
	virtual bool IsEmpty() const override { return true; }
	virtual bool Traverse(Visitor& visitor) override { return false; }
	virtual void Compose(Composer& composer) override {}
	virtual String ToString(const StringStyle& ss, int indentLevel) const override { return String::Empty; }
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
	Expr& GetExprChild() { return *_pExprChild; }
	const Expr& GetExprChild() const { return *_pExprChild; }
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (_pExprChild && !_pExprChild->Traverse(visitor)) return false;
		return true;
	}
public:
	// Virtual functions for structure inspecting
	virtual const Expr* InspectChild() const override { return &GetExprChild(); }
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
	Expr& GetExprLeft() { return *_pExprLeft; }
	Expr& GetExprRight() { return *_pExprRight; }
	const Expr& GetExprLeft() const { return *_pExprLeft; }
	const Expr& GetExprRight() const { return *_pExprRight; }
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (_pExprLeft && !_pExprLeft->Traverse(visitor)) return false;
		if (_pExprRight && !_pExprRight->Traverse(visitor)) return false;
		return true;
	}
public:
	// Virtual functions for structure inspecting
	virtual const Expr* InspectLeft() const override { return &GetExprLeft(); }
	virtual const Expr* InspectRight() const override { return &GetExprRight(); }
};

//------------------------------------------------------------------------------
// Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Collector : public Expr {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Collector);
protected:
	RefPtr<ExprLink> _pExprLinkElem;
public:
	Expr_Collector(const TypeInfo& typeInfo, ExprLink* pExprLinkElem) :
		Expr(typeInfo), _pExprLinkElem(pExprLinkElem) {
		_pExprLinkElem->SetExprParent(this);
	}
	ExprLink& GetExprLinkElem() { return *_pExprLinkElem; }
	const ExprLink& GetExprLinkElem() const { return *_pExprLinkElem; }
	size_t CountExprElem() const { return _pExprLinkElem->CountSequence(); }
	bool HasExprElem() const { return !_pExprLinkElem->IsEmpty(); }
	bool HasSingleExprElem() const { return _pExprLinkElem->HasSingle(); }
	Expr* GetExprElemFirst() { return _pExprLinkElem->GetExprFirst(); }
	const Expr* GetExprElemFirst() const { return _pExprLinkElem->GetExprFirst(); }
	Expr* GetExprElemLast() { return _pExprLinkElem->GetExprLast(); }
	const Expr* GetExprElemLast() const { return _pExprLinkElem->GetExprLast(); }
	void AddExprElem(Expr* pExprElem);
public:
	// Virtual functions of Expr
	virtual bool IsCollector() const override { return true; }
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (!_pExprLinkElem->Traverse(visitor)) return false;
		return true;
	}
public:
	// Virtual functions for structure inspecting
	virtual Iterator* EachElem() const override { return GetExprLinkElem().CreateIterator(); }
};

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Composite : public Expr {
protected:
	RefPtr<Expr> _pExprCar;
	RefPtr<ExprLink> _pExprLinkParam;
	RefPtr<Attribute> _pAttr;
public:
	Expr_Composite(const TypeInfo& typeInfo) :
		Expr(typeInfo), _pExprLinkParam(new ExprLink()), _pAttr(new Attribute()) {}
	Expr_Composite(const TypeInfo& typeInfo, Attribute* pAttr) :
		Expr(typeInfo), _pExprLinkParam(new ExprLink()), _pAttr(pAttr? pAttr : new Attribute()) {}
	void SetExprCar(Expr* pExprCar) {
		_pExprCar.reset(pExprCar);
		_pExprCar->SetExprParent(this);
	}
	Expr& GetExprCar() { return *_pExprCar; }
	const Expr& GetExprCar() const { return *_pExprCar; }
	void SetExprLinkParam(ExprLink* pExprLinkParam) {
		_pExprLinkParam.reset(pExprLinkParam);
		_pExprLinkParam->SetExprParent(this);
	}
	ExprLink& GetExprLinkParam() { return *_pExprLinkParam; }
	const ExprLink& GetExprLinkParam() const { return *_pExprLinkParam; }
	bool HasExprParam() const { return !_pExprLinkParam->IsEmpty(); }
	Expr* GetExprParamFirst() { return _pExprLinkParam->GetExprFirst(); }
	const Expr* GetExprParamFirst() const { return _pExprLinkParam->GetExprFirst(); }
	size_t CountExprParam() const { return GetExprLinkParam().CountSequence(); }
	void AddExprParam(Expr* pExprParam);
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (_pExprCar && !_pExprCar->Traverse(visitor)) return false;
		if (!_pExprLinkParam->Traverse(visitor)) return false;
		return true;
	}
	virtual Attribute* GetAttrToAppend() override { return &GetAttr(); }
	virtual void ResetAttrToAppend() { _pAttr.reset(new Attribute()); }
public:
	// Virtual functions for structure inspecting
	virtual const Expr* InspectCar() const override { return &GetExprCar(); }
	virtual const Attribute* InspectAttr() const override { return &GetAttr(); }
	virtual Iterator* EachParam() const override { return GetExprLinkParam().CreateIterator(); }
};

//------------------------------------------------------------------------------
// Expr_Member
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Member : public Expr {
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
		Expr(typeInfo), _pExprTarget(pExprTarget), _pSymbol(pSymbol), _pAttr(pAttr),
		_memberMode(memberMode) {}
public:
	Expr& GetExprTarget() { return *_pExprTarget; }
	const Expr& GetExprTarget() const { return *_pExprTarget; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
	MemberMode GetMemberMode() const { return _memberMode; }
	const Symbol* GetMemberModeAsSymbol() const;
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!visitor.Visit(this)) return false;
		if (!_pExprTarget->Traverse(visitor)) return false;
		return true;
	}
	virtual Attribute* GetAttrToAppend() override { return &GetAttr(); }
	virtual void ResetAttrToAppend() { _pAttr.reset(new Attribute()); }
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeReferencer(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual const Expr* InspectTarget() const override { return &GetExprTarget(); }
	virtual const Symbol* InspectSymbol() const override { return GetSymbol(); }
	virtual const Attribute* InspectAttr() const { return &GetAttr(); }
	virtual const Symbol* InspectModeAsSymbol() const { return GetMemberModeAsSymbol(); }
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
	Value& GetValue() { return *_pValue; }
	const Value& GetValue() const { return *_pValue; }
	bool HasSource() const { return _pStrSource.get() != nullptr; }
	const char* GetSource() const { return _pStrSource->GetString(); }
	const String& GetSourceSTL() const { return _pStrSource->GetStringSTL(); }
public:
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinArgSlot(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual Value* InspectValue() const override;
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
	bool HasAttr() const { return !GetAttr().IsEmpty(); }
public:
	// Virtual functions of Expr
	virtual bool HasSymbol(const Symbol* pSymbol) const override { return _pSymbol->IsIdentical(pSymbol); }
	virtual bool HasPureSymbol(const Symbol* pSymbol) const override {
		return !HasAttr() && _pSymbol->IsIdentical(pSymbol);
	}
	virtual const Symbol* GetPureSymbol() const override { return HasAttr()? nullptr : _pSymbol; }
	virtual DeclCallable* RetrieveDeclCallable() const override; // used by Template
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual void ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeWithinAssignmentInClass(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual void ComposeWithinArgSlot(Composer& composer) override;
	virtual void ComposeReferencer(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override { return ToString(ss, ""); }
	virtual Attribute* GetAttrToAppend() override { return &GetAttr(); }
	virtual void ResetAttrToAppend() { _pAttr.reset(new Attribute()); }
public:
	virtual size_t CalcHash() const override;
	virtual bool IsEqualTo(const Expr& expr) const override;
	virtual bool IsLessThan(const Expr& expr) const override;
public:
	// Virtual functions for structure inspecting
	virtual const Symbol* InspectSymbol() const override { return _pSymbol; }
	virtual const Attribute* InspectAttr() const override { return &GetAttr(); }
private:
	bool ParseAttr(bool* pExternFlag) const;
};

//------------------------------------------------------------------------------
// Expr_String : Expr_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_String : public Expr_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_String);
public:
	static const TypeInfo typeInfo;
protected:
	RefPtr<StringReferable> _pStrSegment;
public:
	Expr_String(StringReferable* pStrSegment) : Expr_Node(typeInfo), _pStrSegment(pStrSegment) {}
	const StringReferable& GetSegmentReferable() const { return *_pStrSegment; }
	const char* GetSegment() const { return _pStrSegment->GetString(); }
	const String& GetSegmentSTL() const { return _pStrSegment->GetStringSTL(); }
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinArgSlot(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual StringReferable* InspectStringReferable() const override {
		return _pStrSegment.Reference();
	}
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
	const Symbol* _pSymbol;
	SuffixMgr::Mode _mode;
public:
	Expr_Suffixed(StringReferable* pStrSegment, const Symbol* pSymbolSuffix, SuffixMgr::Mode mode) :
		Expr_Node(typeInfo), _pStrSegment(pStrSegment), _pSymbol(pSymbolSuffix), _mode(mode) {}
	const StringReferable& GetSegmentReferable() const { return *_pStrSegment; }
	const char* GetSegment() const { return _pStrSegment->GetString(); }
	const String& GetSegmentSTL() const { return _pStrSegment->GetStringSTL(); }
	const Symbol* GetSymbol() const { return _pSymbol; }
	SuffixMgr::Mode GetMode() const { return _mode; }
	const Symbol* GetModeAsSymbol() const { return SuffixMgr::ModeToSymbol(_mode); }
public:
	// Virtual functions of Expr
	virtual bool IsSuffixed(SuffixMgr::Mode mode) const override { return _mode == mode; }
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual StringReferable* InspectStringReferable() const override {
		return _pStrSegment.Reference();
	}
	virtual const Symbol* InspectSymbol() const override { return GetSymbol(); }
	virtual const Symbol* InspectModeAsSymbol() const { return GetModeAsSymbol(); }
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
	Operator* _pOp;
public:
	Expr_UnaryOp(Expr* pExprChild, Operator* pOp) :
			Expr_Unary(typeInfo, pExprChild), _pOp(pOp) {}
	Operator* GetOperator() const { return _pOp; }
public:
	// Virtual functions of Expr
	virtual bool IsUnaryOp(OpType opType) const override { return GetOperator()->IsType(opType); }
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinLister(Composer& composer) override;
	virtual void ComposeWithinTuple(Composer& composer) override;
	virtual void ComposeWithinArgSlot(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual Operator* InspectOperator() const { return GetOperator(); }
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
	Operator* _pOp;
public:
	Expr_BinaryOp(Expr* pExprLeft, Expr* pExprRight, Operator* pOp) :
			Expr_Binary(typeInfo, pExprLeft, pExprRight), _pOp(pOp) {}
	Operator* GetOperator() const { return _pOp; }
public:
	// Virtual functions of Expr
	virtual bool IsBinaryOp(OpType opType) const override { return GetOperator()->IsType(opType); }
	virtual bool IsShortCircuitOperator() const override {
		return GetOperator()->IsType(OpType::AndAnd) || GetOperator()->IsType(OpType::OrOr);
	}
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinLister(Composer& composer) override;
	virtual void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual void ComposeWithinArgSlot(Composer& composer) override;
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol);
	virtual void ComposeWithinAssignmentInClass(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual Operator* InspectOperator() const { return GetOperator(); }
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
	Operator* _pOp;	// this may be nullptr
public:
	Expr_Assign(Expr* pExprLeft, Expr* pExprRight, Operator* pOp) :
			Expr_Binary(typeInfo, pExprLeft, pExprRight), _pOp(pOp) {}
	Operator* GetOperator() const { return _pOp; }
public:
	// Virtual functions of Expr
	virtual bool DoPrepare() override;
	virtual bool IsDeclArgWithDefault(Expr_Binary** ppExpr) const override;
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual void ComposeWithinArgSlot(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual Operator* InspectOperator() const { return GetOperator(); }
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
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
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
	Expr_Block() : Expr_Block(new ExprLink()) {}
	void SetExprLinkParam(ExprLink* pExprLinkParam) {
		_pExprLinkParam.reset(pExprLinkParam);
		_pExprLinkParam->SetExprParent(this);
	}
	bool HasExprParam() const { return _pExprLinkParam && !_pExprLinkParam->IsEmpty(); }
	const ExprLink& GetExprLinkParam() const { return *_pExprLinkParam; }
	Expr* GetExprParamFirst() {
		return _pExprLinkParam? _pExprLinkParam->GetExprFirst() : nullptr;
	}
	const Expr* GetExprParamFirst() const {
		return _pExprLinkParam? _pExprLinkParam->GetExprFirst() : nullptr;
	}
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	bool PrepareDeclCallable() {
		if (!_pExprLinkParam) return true;
		return _pDeclCallable->Prepare(GetExprLinkParam(), *Attribute::Empty, nullptr);
	}
	bool HasCallerAsParent() const;
	bool IsDelegation() const {
		//return !HasExprElem() && _pExprLinkParam && _pExprLinkParam->HasSingle();
		return !HasExprParam() && HasSingleExprElem() && GetExprElemFirst()->IsType<Expr_Block>(); 
	}
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg) const;
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2) const;
public:
	// Virtual functions of Expr
	virtual bool Traverse(Visitor& visitor) override {
		if (!Expr_Collector::Traverse(visitor)) return false;
		if (_pExprLinkParam && !_pExprLinkParam->Traverse(visitor)) return false;
		return true;
	}
	virtual bool DoPrepare() override;
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinLister(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual Iterator* EachParam() const override {
		return HasExprParam()? GetExprLinkParam().CreateIterator() : Expr::EachParam();
	}
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
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
};

//------------------------------------------------------------------------------
// Expr_Tuple : Expr_Collector
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr_Tuple : public Expr_Collector {
public:
	// Referable declaration
	Gurax_DeclareReferable(Expr_Tuple);
public:
	static const TypeInfo typeInfo;
public:
	Expr_Tuple(ExprLink* pExprLinkElem) : Expr_Collector(typeInfo, pExprLinkElem) {}
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
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
	Expr_Indexer(Attribute* pAttr) : Expr_Composite(typeInfo, pAttr) {}
public:
	// Virtual functions of Expr
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinValueAssignment(Composer& composer, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual void ComposeWithinAssignmentInClass(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual void ComposeReferencer(Composer& composer) override;
	virtual String ToString(const StringStyle& ss, int indentLevel) const override { return ToString(ss, "", indentLevel); }
	String ToString(const StringStyle& ss, const char* strInsert, int indentLevel = 0) const;
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
	RefPtr<Expr_Block> _pExprOfBlock;	// this may be nullptr
	RefPtr<Expr_Caller> _pExprTrailer;	// this may be nullptr
public:
	Expr_Caller() : Expr_Composite(typeInfo), _pDeclCallable(new DeclCallable()) {}
	Expr_Caller(Attribute* pAttr) : Expr_Composite(typeInfo, pAttr), _pDeclCallable(new DeclCallable()) {}
public:
	bool PrepareDeclCallable() {
		return _pDeclCallable->Prepare(GetExprLinkParam(), GetAttr(), GetExprOfBlock());
	}
	void SetExprOfBlock(Expr_Block* pExprOfBlock) {
		_pExprOfBlock.reset(pExprOfBlock);
		_pExprOfBlock->SetExprParent(this);
	}
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	bool HasExprOfBlock() const { return _pExprOfBlock.get() != nullptr; }
	bool HasEmptyExprOfBlock() const { return _pExprOfBlock && !_pExprOfBlock->HasExprElem(); }
	Expr_Block* GetExprOfBlock() { return _pExprOfBlock.get(); }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
	void SetExprTrailer(Expr_Caller* pExprTrailer);
	bool HasExprTrailer() const { return _pExprTrailer.get() != nullptr; }
	Expr_Caller* GetExprTrailer() { return _pExprTrailer.get(); }
	const Expr_Caller* GetExprTrailer() const { return _pExprTrailer.get(); }
	Expr_Caller& GetExprTrailerLast();
	Function* GenerateFunction(Composer& composer, DeclCallable::Type type,
			Expr& exprAssigned, RefPtr<DottedSymbol> pDottedSymbol);
public:
	// Virtual functions of Expr
	virtual bool IsStatement(const Symbol* pSymbol) const override {
		return GetExprCar().HasPureSymbol(pSymbol);
	}
	virtual DeclCallable* RetrieveDeclCallable() const override; // used by Template
	virtual bool Traverse(Visitor& visitor) override {
		if (!Expr_Composite::Traverse(visitor)) return false;
		if (_pExprOfBlock && !_pExprOfBlock->Traverse(visitor)) return false;
		if (_pExprTrailer && !_pExprTrailer->Traverse(visitor)) return false;
		return true;
	}
	virtual void Compose(Composer& composer) override;
	virtual void ComposeWithinClass(Composer& composer, RefPtr<DottedSymbol> pDottedSymbol, bool publiclFlag) override;
	virtual void ComposeWithinAssignment(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol) override;
	virtual void ComposeWithinAssignmentInClass(
		Composer& composer, Expr& exprAssigned, Operator* pOp, RefPtr<DottedSymbol> pDottedSymbol, bool publicFlag) override;
	virtual Attribute* GetAttrToAppend() override { return &GetExprTrailerLast().GetAttr(); }
	virtual void ResetAttrToAppend() { GetExprTrailerLast().ResetAttrToAppend(); }
	virtual String ToString(const StringStyle& ss, int indentLevel) const override;
public:
	// Virtual functions for structure inspecting
	virtual const Expr* InspectBlock() const override { return HasExprOfBlock()? GetExprOfBlock() : nullptr; }
	virtual const Expr* InspectTrailer() const override { return HasExprTrailer()? GetExprTrailer() : nullptr; }
};

}

#endif
