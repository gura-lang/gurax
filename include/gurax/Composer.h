//==============================================================================
// Composer.h
//==============================================================================
#ifndef GURAX_COMPOSER_H
#define GURAX_COMPOSER_H
#include "PUnit.h"
#include "Template.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Composer {
public:
	class GURAX_DLLDECLARE TryInfo {
	private:
		const PUnit* _pPUnitOfFinally;
		bool _withinFinallyFlag;
	public:
		// Constructor
		TryInfo() = delete;
		TryInfo(const PUnit* pPUnitOfFinally, bool withinFinallyFlag) :
			_pPUnitOfFinally(pPUnitOfFinally), _withinFinallyFlag(withinFinallyFlag) {}
		// Copy constructor/operator
		TryInfo(const TryInfo& src) :
			_pPUnitOfFinally(src._pPUnitOfFinally), _withinFinallyFlag(src._withinFinallyFlag) {}
		TryInfo& operator=(const TryInfo& src) = delete;
		// Move constructor/operator
		TryInfo(TryInfo&& src) = delete;
		TryInfo& operator=(TryInfo&& src) noexcept = delete;
		// Destructor
		virtual ~TryInfo() = default;
	public:
		const PUnit* GetPUnitOfFinally() const { return _pPUnitOfFinally; }
		bool IsWithinFinally() const { return _withinFinallyFlag; }
	};
	class GURAX_DLLDECLARE TryInfoTbl : public ListBase<TryInfo*> {
	};
	class GURAX_DLLDECLARE TryInfoOwner : public TryInfoTbl {
	public:
		~TryInfoOwner() { Clear(); }
		void Clear();
	};
	class GURAX_DLLDECLARE RepeaterInfo {
	private:
		const PUnit* _pPUnitOfLoop;
		const PUnit* _pPUnitOfBranch;
		const PUnit* _pPUnitOfBreak;
	public:
		// Constructor
		RepeaterInfo() = delete;
		RepeaterInfo(const PUnit* pPUnitOfLoop, const PUnit* pPUnitOfBranch,
					const PUnit* pPUnitOfBreak) :
			_pPUnitOfLoop(pPUnitOfLoop), _pPUnitOfBranch(pPUnitOfBranch),
			_pPUnitOfBreak(pPUnitOfBreak) {}
		// Copy constructor/operator
		RepeaterInfo(const RepeaterInfo& src) :
			_pPUnitOfLoop(src._pPUnitOfLoop), _pPUnitOfBranch(src._pPUnitOfBranch),
			_pPUnitOfBreak(src._pPUnitOfBreak) {}
		RepeaterInfo& operator=(const RepeaterInfo& src) = delete;
		// Move constructor/operator
		RepeaterInfo(RepeaterInfo&& src) = delete;
		RepeaterInfo& operator=(RepeaterInfo&& src) noexcept = delete;
		// Destructor
		virtual ~RepeaterInfo() = default;
	public:
		const PUnit* GetPUnitOfLoop() const { return _pPUnitOfLoop; }
		const PUnit* GetPUnitOfBranch() const { return _pPUnitOfBranch; }
		const PUnit* GetPUnitOfBreak() const { return _pPUnitOfBreak; }
	};
	class GURAX_DLLDECLARE RepeaterInfoTbl : public ListBase<RepeaterInfo*> {
	};
	class GURAX_DLLDECLARE RepeaterInfoOwner : public RepeaterInfoTbl {
	public:
		~RepeaterInfoOwner() { Clear(); }
		void Clear();
	};
private:
	bool _replFlag;
	PUnit* _pPUnitFirst;
	PUnit* _pPUnitLast;
	PUnitStack _punitStack;
	RefPtr<PUnitFactory> _pPUnitFactory;
	RepeaterInfoOwner _repeaterInfoStack;
	TryInfoOwner _tryInfoStack;
public:
	// Constructor
	Composer(bool replFlag = false);
	// Copy constructor/operator
	Composer(const Composer& src) = delete;
	Composer& operator=(const Composer& src) = delete;
	// Move constructor/operator
	Composer(Composer&& src) = delete;
	Composer& operator=(Composer&& src) noexcept = delete;
	// Destructor
	virtual ~Composer() = default;
public:
	PUnitStack& GetPUnitStack() { return _punitStack; }
	const PUnit* GetPUnitFirst() const { return _pPUnitFirst; }
	PUnit* PeekPUnitCont() const;
	void Begin() { _pPUnitLast = nullptr; }
	void Add(PUnit* pPUnit);
	void SetFactory(PUnitFactory* pPUnitFactory);
	void Flush() { _Flush(false); }
	void FlushDiscard() { _Flush(true); }
	bool HasValidRepeaterInfo() const { return !_repeaterInfoStack.empty(); }
	const RepeaterInfo& GetRepeaterInfoCur() const { return *_repeaterInfoStack.back(); }
	void BeginRepeaterBlock(const PUnit* pPUnitOfLoop, const PUnit* pPUnitOfBranch, const PUnit* pPUnitOfBreak) {
		_repeaterInfoStack.push_back(new RepeaterInfo(pPUnitOfLoop, pPUnitOfBranch, pPUnitOfBreak));
	}
	void EndRepeaterBlock() {
		_repeaterInfoStack.pop_back();
	}
	bool HasValidTryInfo() const { return !_tryInfoStack.empty(); }
	const TryInfo& GetTryInfoCur() const { return *_tryInfoStack.back(); }
	void BeginTryBlock(const PUnit* pPUnitOfFinally) {
		_tryInfoStack.push_back(new TryInfo(pPUnitOfFinally, false));
	}
	void EndTryBlock() {
		_tryInfoStack.pop_back();
	}
	void BeginFinallyBlock() {
		_tryInfoStack.push_back(new TryInfo(nullptr, true));
	}
	void EndFinallyBlock() {
		_tryInfoStack.pop_back();
	}
	PUnitFactory& GetFactory() { return *_pPUnitFactory; }
	void ComposeAsSequence(Expr& expr);
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
public:
	void Add_Value(Value* pValue, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Value(pValue, exprSrc.Reference()));
	}
	void Add_Lookup(const Symbol* pSymbol, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Lookup(pSymbol, exprSrc.Reference()));
	}
	void Add_Referencer(const Symbol* pSymbol, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Referencer(pSymbol, exprSrc.Reference()));
	}
	void Add_Suffixed(StringReferable* pStrSegment, SuffixMgr::Mode mode, const Symbol* pSymbol,
					const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Suffixed(pStrSegment, mode, pSymbol, exprSrc.Reference()));
	}
	void Add_AssignToSymbol(const Symbol* pSymbol, bool externFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_AssignToSymbol(pSymbol, externFlag, exprSrc.Reference()));
	}
	void Add_AssignToDeclArg(DeclArg* pDeclArg, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_AssignToDeclArg(pDeclArg, exprSrc.Reference()));
	}
	void Add_AssignFunction(Function* pFunction, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_AssignFunction(pFunction, exprSrc.Reference()));
	}
	void Add_AssignMethod(Function* pFunction, bool keepTargetFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_AssignMethod(pFunction, keepTargetFlag, exprSrc.Reference()));
	}
	void Add_AssignPropSlot(const Symbol* pSymbol, RefPtr<DottedSymbol> pDottedSymbol, PropSlot::Flags flags,
							const Attribute& attr, bool initializerFlag, const Expr& exprSrc);
	void Add_Cast(const VType& vtype, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Cast(vtype, DeclArg::Flag::None, exprSrc.Reference()));
	}
	void Add_Cast(const VType& vtype, DeclArg::Flags flags, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Cast(vtype, flags, exprSrc.Reference()));
	}
	void Add_GenIterator(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator(exprSrc.Reference()));
	}
	void Add_GenIterator_Range(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator_Range(exprSrc.Reference()));
	}
	void Add_GenIterator_Counter(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator_Counter(exprSrc.Reference()));
	}
	void Add_GenIterator_ForLister(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator_ForLister(exprSrc.Reference()));
	}
	void Add_GenIterator_for(Expr_Block* pExprOfBlock, DeclArgOwner* pDeclArgOwner, bool skipNilFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator_for(pExprOfBlock, pDeclArgOwner, skipNilFlag, exprSrc.Reference()));
	}
	void Add_GenIterator_while(Expr* pExprCriteria, Expr_Block* pExprOfBlock, bool skipNilFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator_while(pExprCriteria, pExprOfBlock, skipNilFlag, exprSrc.Reference()));
	}
	void Add_GenIterator_repeat(Expr_Block* pExprOfBlock, bool finiteFlag, bool skipNilFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_GenIterator_repeat(pExprOfBlock, finiteFlag, skipNilFlag, exprSrc.Reference()));
	}
	void Add_EvalIterator(size_t offset, bool raiseFlag, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_EvalIterator(offset, raiseFlag, pPUnitBranchDest, exprSrc.Reference()));
	}
	void Add_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_ForEach(offset, pDeclArgOwner, pPUnitBranchDest, exprSrc.Reference()));
	}
	void Add_UnaryOp(Operator* pOp, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_UnaryOp(pOp, exprSrc.Reference()));
	}
	void Add_BinaryOp(Operator* pOp, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_BinaryOp(pOp, exprSrc.Reference()));
	}
	void Add_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList,
					bool binaryFlag, bool mixInFlag, bool overwriteFlag, bool symbolForModuleFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Import(pDottedSymbol, pSymbolList,
										binaryFlag, mixInFlag, overwriteFlag, symbolForModuleFlag,
										exprSrc.Reference()));
	}
	void Add_VTypeBegin(bool inheritFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_VTypeBegin(inheritFlag, exprSrc.Reference()));
	}
	void Add_VTypeEnd_Class(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_VTypeEnd_Class(exprSrc.Reference()));
	}
	void Add_VTypeEnd_Struct(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_VTypeEnd_Struct(exprSrc.Reference()));
	}
	void Add_CreateList(size_t sizeReserve, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_CreateList(sizeReserve, exprSrc.Reference()));
	}
	void Add_ListElem(size_t offset, bool xlistFlag, bool expandFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_ListElem(offset, xlistFlag, expandFlag, exprSrc.Reference()));
	}
	void Add_CreateTuple(size_t sizeReserve, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_CreateTuple(sizeReserve, exprSrc.Reference()));
	}
	void Add_TupleElem(size_t offset, bool expandFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_TupleElem(offset, expandFlag, exprSrc.Reference()));
	}
	void Add_CreateDict(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_CreateDict(exprSrc.Reference()));
	}
	void Add_DictElem(size_t offset, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_DictElem(offset, exprSrc.Reference()));
	}
	void Add_Index(Attribute* pAttr, size_t sizeReserve, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Index(pAttr, sizeReserve, exprSrc.Reference()));
	}
	void Add_FeedIndex(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_FeedIndex(exprSrc.Reference()));
	}
	void Add_IndexGet(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_IndexGet(exprSrc.Reference()));
	}
	void Add_IndexSet(bool valueFirstFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_IndexSet(valueFirstFlag, exprSrc.Reference()));
	}
	void Add_IndexOpApply(Operator* pOp, bool valueFirstFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_IndexOpApply(pOp, valueFirstFlag, exprSrc.Reference()));
	}
	void Add_MemberSet_Normal(const Symbol* pSymbol, Attribute* pAttr, bool valueFirstFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberSet_Normal(pSymbol, pAttr, valueFirstFlag, exprSrc.Reference()));
	}
	void Add_MemberSet_Map(const Symbol* pSymbol, Attribute* pAttr, bool mapAssignedFlag, bool valueFirstFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberSet_Map(pSymbol, pAttr, mapAssignedFlag, valueFirstFlag, exprSrc.Reference()));
	}
	void Add_MemberOpApply_Normal(const Symbol* pSymbol, Attribute* pAttr, Operator* pOp, bool valueFirstFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberOpApply_Normal(pSymbol, pAttr, pOp, valueFirstFlag, exprSrc.Reference()));
	}
	void Add_MemberOpApply_Map(const Symbol* pSymbol, Attribute* pAttr, Operator* pOp, bool mapAssignedFlag, bool valueFirstFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberOpApply_Map(pSymbol, pAttr, pOp, mapAssignedFlag, valueFirstFlag, exprSrc.Reference()));
	}
	void Add_MemberGet_Normal(const Symbol* pSymbol, Attribute* pAttr, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberGet_Normal(pSymbol, pAttr, exprSrc.Reference()));
	}
	void Add_MemberGet_MapAlong(const Symbol* pSymbol, Attribute* pAttr, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberGet_MapAlong(pSymbol, pAttr, exprSrc.Reference()));
	}
	void Add_MemberGet_MapToList(const Symbol* pSymbol, Attribute* pAttr, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberGet_MapToList(pSymbol, pAttr, exprSrc.Reference()));
	}
	void Add_MemberGet_MapToIter(const Symbol* pSymbol, Attribute* pAttr, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_MemberGet_MapToIter(pSymbol, pAttr, exprSrc.Reference()));
	}
	void Add_Argument(Attribute* pAttr, Expr_Block* pExprOfBlock, bool keepCarFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Argument(pAttr, pExprOfBlock, keepCarFlag, exprSrc.Reference()));
	}
	void Add_ArgumentDelegation(Attribute* pAttr, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_ArgumentDelegation(pAttr, exprSrc.Reference()));
	}
	void Add_ArgSlot_Value(Value* pValue, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_ArgSlot_Value(pValue, exprSrc.Reference()));
	}
	void Add_ArgSlot_Lookup(const Symbol* pSymbol, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_ArgSlot_Lookup(pSymbol, exprSrc.Reference()));
	}
	void Add_ArgSlotBegin(const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_ArgSlotBegin(pPUnitBranchDest, exprSrc.Reference()));
	}
	void Add_ArgSlotEnd(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_ArgSlotEnd(exprSrc.Reference()));
	}
	void Add_ArgSlotEnd_Expand(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_ArgSlotEnd_Expand(exprSrc.Reference()));
	}
	void Add_NamedArgSlotBegin(const Symbol* pSymbol, Expr* pExprAssigned, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_NamedArgSlotBegin(
					pSymbol, pExprAssigned, pPUnitBranchDest, exprSrc.Reference()));
	}
	void Add_NamedArgSlotEnd(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_NamedArgSlotEnd(exprSrc.Reference()));
	}
	void Add_Call(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Call(exprSrc.Reference()));
	}
	void Add_Jump(const Expr& exprSrc) {
		const PUnit* pPUnitCont = nullptr;
		SetFactory(new PUnitFactory_Jump(pPUnitCont, exprSrc.Reference()));
		Flush();
	}
	void Add_Jump(const PUnit* pPUnitCont, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Jump(pPUnitCont, exprSrc.Reference()));
		Flush();
	}
	void Add_JumpIf(PUnit::BranchMode branchMode, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIf(pPUnitBranchDest, branchMode, exprSrc.Reference()));
	}
	void Add_JumpIfNot(PUnit::BranchMode branchMode, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIfNot(pPUnitBranchDest, branchMode, exprSrc.Reference()));
	}
	void Add_TryBlockBegin(const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_TryBlockBegin(pPUnitBranchDest, exprSrc.Reference()));
	}
	void Add_TryBlockEnd(const Expr& exprSrc) {
		const PUnit* pPUnitCont = nullptr;
		SetFactory(new PUnitFactory_TryBlockEnd(pPUnitCont, exprSrc.Reference()));
	}
	void Add_JumpIfNoCatch(PUnit::BranchMode branchMode, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIfNoCatch(pPUnitBranchDest, branchMode, exprSrc.Reference()));
	}
	void Add_JumpIfNoCatchAny(PUnit::BranchMode branchMode, const Expr& exprSrc) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIfNoCatchAny(pPUnitBranchDest, branchMode, exprSrc.Reference()));
	}
	void Add_ProcessSequence(const Expr& exprSrc) {
		const PUnit* pPUnitSentinel = nullptr;
		SetFactory(new PUnitFactory_ProcessSequence(pPUnitSentinel, exprSrc.Reference()));
	}
	void Add_SequenceBegin(const Expr& exprSrc) {
		const PUnit* pPUnitSentinel = nullptr;
		SetFactory(new PUnitFactory_SequenceBegin(pPUnitSentinel, exprSrc.Reference()));
	}
	void Add_SequenceEnd(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_SequenceEnd(exprSrc.Reference()));
	}
	void Add_DiscardValue(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_DiscardValue(exprSrc.Reference()));
	}
	void Add_RemoveValue(size_t offset, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_RemoveValue(offset, exprSrc.Reference()));
	}
	void Add_RemoveValues(size_t offset, size_t cnt, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_RemoveValues(offset, cnt, exprSrc.Reference()));
	}
	void Add_Break(const PUnit* pPUnitMarked, bool branchDestFlag, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Break(pPUnitMarked, branchDestFlag, exprSrc.Reference()));
	}
	void Add_Continue(const PUnit* pPUnitOfLoop, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Continue(pPUnitOfLoop, exprSrc.Reference()));
	}
	void Add_FailCatch(Value* pValue, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_FailCatch(pValue, exprSrc.Reference()));
	}
	void Add_Return(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_Return(exprSrc.Reference()));
	}
	template<typename T_Frame> void Add_PushFrame(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_PushFrame<T_Frame>(exprSrc.Reference()));
	}
	void Add_PushFrameFromStack(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_PushFrameFromStack(exprSrc.Reference()));
	}
	void Add_PopFrame(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_PopFrame(exprSrc.Reference()));
	}
	void Add_NoOperation(const Expr& exprSrc) {
		SetFactory(new PUnitFactory_NoOperation(exprSrc.Reference()));
	}
	void Add_Terminate() {
		SetFactory(new PUnitFactory_Terminate());
		Flush();
	}
	// PUnit for Template
	void Add_TmplString(Template* pTmpl, const String& str, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_TmplString(pTmpl, str, exprSrc.Reference()));
	}	
	void Add_TmplScript(Expr_TmplScript* pExprTmplScript, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_TmplScript(pExprTmplScript, exprSrc.Reference()));
	}	
	void Add_TmplEmbedded(Template* pTmpl, const Expr& exprSrc) {
		SetFactory(new PUnitFactory_TmplEmbedded(pTmpl, exprSrc.Reference()));
	}	
private:
	void _Flush(bool discardValueFlag);
};

}

#endif
