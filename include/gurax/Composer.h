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
	class RepeaterInfoTbl : public std::vector<RepeaterInfo*> {
	};
	class RepeaterInfoOwner : public RepeaterInfoTbl {
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
	PUnitFactory& GetFactory() { return *_pPUnitFactory; }
	void ComposeAsSequence(Expr& expr);
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
public:
	void Add_Value(Value* pValue, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Value(pValue, Expr::Reference(pExprSrc)));
	}
	void Add_Lookup(const Symbol* pSymbol, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Lookup(pSymbol, Expr::Reference(pExprSrc)));
	}
	void Add_Suffixed(StringReferable* pStrSegment, SuffixMgr::Target target, const Symbol* pSymbolSuffix,
					  const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Suffixed(pStrSegment, target, pSymbolSuffix, Expr::Reference(pExprSrc)));
	}
	void Add_AssignToSymbol(const Symbol* pSymbol, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_AssignToSymbol(pSymbol, Expr::Reference(pExprSrc)));
	}
	void Add_AssignToDeclArg(DeclArg* pDeclArg, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_AssignToDeclArg(pDeclArg, Expr::Reference(pExprSrc)));
	}
	void Add_AssignFunction(Function* pFunction, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_AssignFunction(pFunction, Expr::Reference(pExprSrc)));
	}
	void Add_AssignMethod(Function* pFunction, bool keepTargetFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_AssignMethod(pFunction, keepTargetFlag, Expr::Reference(pExprSrc)));
	}
	void Add_AssignPropHandler(const Symbol* pSymbol, PropHandler::Flags flags,
							   const Attribute& attr, bool initByNilFlag, const Expr* pExprSrc);
	void Add_Cast(const VType& vtype, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Cast(vtype, DeclArg::Flag::None, Expr::Reference(pExprSrc)));
	}
	void Add_Cast(const VType& vtype, DeclArg::Flags flags, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Cast(vtype, flags, Expr::Reference(pExprSrc)));
	}
	void Add_GenIterator(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_GenIterator(Expr::Reference(pExprSrc)));
	}
	void Add_GenIterator_Range(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_GenIterator_Range(Expr::Reference(pExprSrc)));
	}
	void Add_GenIterator_Counter(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_GenIterator_Counter(Expr::Reference(pExprSrc)));
	}
	void Add_GenIterator_ForLister(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_GenIterator_ForLister(Expr::Reference(pExprSrc)));
	}
	void Add_GenIterator_repeat(Expr_Block* pExprOfBlock, bool finiteFlag, bool skipNilFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_GenIterator_repeat(pExprOfBlock, finiteFlag, skipNilFlag, Expr::Reference(pExprSrc)));
	}
	void Add_EvalIterator(size_t offset, bool raiseFlag, const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_EvalIterator(offset, raiseFlag, pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_ForEach(offset, pDeclArgOwner, pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_UnaryOp(const Operator* pOp, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_UnaryOp(pOp, Expr::Reference(pExprSrc)));
	}
	void Add_BinaryOp(const Operator* pOp, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_BinaryOp(pOp, Expr::Reference(pExprSrc)));
	}
	void Add_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList,
					bool binaryFlag, bool mixInFlag, bool overwriteFlag, bool symbolForModuleFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Import(pDottedSymbol, pSymbolList,
										   binaryFlag, mixInFlag, overwriteFlag, symbolForModuleFlag,
										   Expr::Reference(pExprSrc)));
	}
	void Add_CreateVType(bool inheritFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_CreateVType(inheritFlag, Expr::Reference(pExprSrc)));
	}
	void Add_CompleteStruct(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_CompleteStruct(Expr::Reference(pExprSrc)));
	}
	void Add_CreateList(size_t sizeReserve, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_CreateList(sizeReserve, Expr::Reference(pExprSrc)));
	}
	void Add_ListElem(size_t offset, bool xlistFlag, bool expandFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_ListElem(offset, xlistFlag, expandFlag, Expr::Reference(pExprSrc)));
	}
	void Add_CreateDict(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_CreateDict(Expr::Reference(pExprSrc)));
	}
	void Add_DictElem(size_t offset, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_DictElem(offset, Expr::Reference(pExprSrc)));
	}
	void Add_Index(Attribute* pAttr, size_t sizeReserve, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Index(pAttr, sizeReserve, Expr::Reference(pExprSrc)));
	}
	void Add_FeedIndex(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_FeedIndex(Expr::Reference(pExprSrc)));
	}
	void Add_IndexGet(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_IndexGet(Expr::Reference(pExprSrc)));
	}
	void Add_IndexSet(bool valueFirstFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_IndexSet(valueFirstFlag, Expr::Reference(pExprSrc)));
	}
	void Add_IndexOpApply(const Operator* pOp, bool valueFirstFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_IndexOpApply(pOp, valueFirstFlag, Expr::Reference(pExprSrc)));
	}
	void Add_MemberSet_Normal(const Symbol* pSymbol, Attribute* pAttr, bool valueFirstFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_MemberSet_Normal(pSymbol, pAttr, valueFirstFlag, Expr::Reference(pExprSrc)));
	}
	void Add_MemberOpApply_Normal(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp, bool valueFirstFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_MemberOpApply_Normal(pSymbol, pAttr, pOp, valueFirstFlag, Expr::Reference(pExprSrc)));
	}
	void Add_MemberGet_Normal(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_MemberGet_Normal(pSymbol, pAttr, Expr::Reference(pExprSrc)));
	}
	void Add_MemberGet_MapAlong(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_MemberGet_MapAlong(pSymbol, pAttr, Expr::Reference(pExprSrc)));
	}
	void Add_MemberGet_MapToList(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_MemberGet_MapToList(pSymbol, pAttr, Expr::Reference(pExprSrc)));
	}
	void Add_MemberGet_MapToIter(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_MemberGet_MapToIter(pSymbol, pAttr, Expr::Reference(pExprSrc)));
	}
	void Add_Argument(Attribute* pAttr, Expr_Block* pExprOfBlock, bool keepCarFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Argument(pAttr, pExprOfBlock, keepCarFlag, Expr::Reference(pExprSrc)));
	}
	void Add_ArgumentDelegation(Attribute* pAttr, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_ArgumentDelegation(pAttr, Expr::Reference(pExprSrc)));
	}
	void Add_BeginArgSlot(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_BeginArgSlot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_EndArgSlot(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_EndArgSlot(Expr::Reference(pExprSrc)));
	}
	void Add_EndArgSlotExpand(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_EndArgSlotExpand(Expr::Reference(pExprSrc)));
	}
	void Add_BeginArgSlotNamed(const Symbol* pSymbol, Expr* pExprAssigned, const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_BeginArgSlotNamed(
					   pSymbol, pExprAssigned, pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_EndArgSlotNamed(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_EndArgSlotNamed(Expr::Reference(pExprSrc)));
	}
	void Add_Call(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Call(Expr::Reference(pExprSrc)));
	}
	void Add_Jump(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitCont = nullptr;
		SetFactory(new PUnitFactory_Jump(pPUnitCont, Expr::Reference(pExprSrc)));
	}
	void Add_Jump(const PUnit* pPUnitCont, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Jump(pPUnitCont, Expr::Reference(pExprSrc)));
	}
	void Add_JumpIf(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIf(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_JumpIfNot(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIfNot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_NilJumpIf(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_NilJumpIf(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_NilJumpIfNot(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_NilJumpIfNot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_KeepJumpIf(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_KeepJumpIf(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_KeepJumpIfNot(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_KeepJumpIfNot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_BeginTryBlock(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_BeginTryBlock(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_EndTryBlock(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitCont = nullptr;
		SetFactory(new PUnitFactory_EndTryBlock(pPUnitCont, Expr::Reference(pExprSrc)));
	}
	void Add_JumpIfNoCatch(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIfNoCatch(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_JumpIfNoCatchAny(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_JumpIfNoCatchAny(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_NilJumpIfNoCatch(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_NilJumpIfNoCatch(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_NilJumpIfNoCatchAny(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitBranchDest = nullptr;
		SetFactory(new PUnitFactory_NilJumpIfNoCatchAny(pPUnitBranchDest, Expr::Reference(pExprSrc)));
	}
	void Add_BeginSequence(const Expr* pExprSrc = nullptr) {
		const PUnit* pPUnitSentinel = nullptr;
		SetFactory(new PUnitFactory_BeginSequence(pPUnitSentinel, Expr::Reference(pExprSrc)));
	}
	void Add_EndSequence(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_EndSequence(Expr::Reference(pExprSrc)));
	}
	void Add_DiscardValue(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_DiscardValue(Expr::Reference(pExprSrc)));
	}
	void Add_RemoveValue(size_t offset, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_RemoveValue(offset, Expr::Reference(pExprSrc)));
	}
	void Add_RemoveValues(size_t offset, size_t cnt, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_RemoveValues(offset, cnt, Expr::Reference(pExprSrc)));
	}
	void Add_Break(const PUnit* pPUnitMarked, bool branchDestFlag, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Break(pPUnitMarked, branchDestFlag, Expr::Reference(pExprSrc)));
	}
	void Add_Continue(const PUnit* pPUnitOfLoop, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Continue(pPUnitOfLoop, Expr::Reference(pExprSrc)));
	}
	void Add_Miscatch(Value* pValue, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Miscatch(pValue, Expr::Reference(pExprSrc)));
	}
	void Add_Return(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_Return(Expr::Reference(pExprSrc)));
	}
	template<typename T_Frame> void Add_PushFrame(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_PushFrame<T_Frame>(Expr::Reference(pExprSrc)));
	}
	void Add_PushFrameFromStack(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_PushFrameFromStack(Expr::Reference(pExprSrc)));
	}
	void Add_PopFrame(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_PopFrame(Expr::Reference(pExprSrc)));
	}
	void Add_NoOperation(const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_NoOperation(Expr::Reference(pExprSrc)));
	}
	void Add_Terminate() {
		SetFactory(new PUnitFactory_Terminate());
		Flush();
	}
	// PUnit for Template
	void Add_TmplString(Template* pTmpl, const String& str, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_TmplString(pTmpl, str, Expr::Reference(pExprSrc)));
	}	
	void Add_TmplScript(Expr_TmplScript* pExprTmplScript, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_TmplScript(pExprTmplScript, Expr::Reference(pExprSrc)));
	}	
	void Add_TmplEmbedded(Template* pTmpl, const Expr* pExprSrc = nullptr) {
		SetFactory(new PUnitFactory_TmplEmbedded(pTmpl, Expr::Reference(pExprSrc)));
	}	
private:
	void _Flush(bool discardValueFlag);
};

}

#endif
