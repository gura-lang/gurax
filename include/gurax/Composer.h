//==============================================================================
// Composer.h
//==============================================================================
#ifndef GURAX_COMPOSER_H
#define GURAX_COMPOSER_H
#include "PUnit.h"

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
	PUnit::SeqId _seqIdCur;
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
	PUnit::SeqId NextSeqId() { return _seqIdCur++; }
	PUnitStack& GetPUnitStack() { return _punitStack; }
	const PUnit* GetPUnitFirst() const { return _pPUnitFirst; }
	PUnit* PeekPUnitCont() const;
	void Begin() { _pPUnitLast = nullptr; }
	void Add(PUnit* pPUnit);
	void SetFactory(PUnitFactory* pPUnitFactory);
	void Flush(bool discardValueFlag);
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
public:
	void Add_Value(const Expr& exprSrc, Value* pValue);
	void Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol);
	void Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol);
	void Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg);
	void Add_AssignFunction(const Expr& exprSrc, Function* pFunction);
	void Add_Cast(const Expr& exprSrc, const VType& vtype, bool listVarFlag);
	void Add_GenIterator(const Expr& exprSrc);
	void Add_GenRangeIterator(const Expr& exprSrc);
	void Add_GenCounterIterator(const Expr& exprSrc);
	void Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest = nullptr);

	void Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
					   const PUnit* pPUnitBranchDest = nullptr);
	void Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator);
	void Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator);
	void Add_Import(const Expr& exprSrc, DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag);
	void Add_CreateList(const Expr& exprSrc, size_t sizeReserve);
	void Add_ListElem(const Expr& exprSrc, size_t offset, bool xlistFlag);
	void Add_CreateDict(const Expr& exprSrc);
	void Add_DictElem(const Expr& exprSrc, size_t offset);
	void Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve);
	void Add_FeedIndex(const Expr& exprSrc);
	void Add_IndexGet(const Expr& exprSrc);
	void Add_IndexSet(const Expr& exprSrc);
	void Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	void Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	void Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	void Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock);
	void Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_FeedArgSlot(const Expr& exprSrc);
	void Add_ArgSlotNamed(
		const Expr& exprSrc, const Symbol* pSymbol,
		Expr* pExprAssigned, const PUnit* pPUnitBranchDest = nullptr);
	void Add_FeedArgSlotNamed(const Expr& exprSrc);
	void Add_Call(const Expr& exprSrc);
	void Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont = nullptr);
	void Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_KeepJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_KeepJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	void Add_BeginSequence(const Expr& exprSrc, const PUnit* pPUnitSentinel = nullptr);
	void Add_EndSequence(const Expr& exprSrc);
	void Add_DiscardValue(const Expr& exprSrc);
	void Add_RemoveValue(const Expr& exprSrc, size_t offset);
	void Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt);
	void Add_Break(const Expr& exprSrc, const PUnit* pPUnitMarked, bool branchDestFlag);
	void Add_Continue(const Expr& exprSrc, const PUnit* pPUnitOfLoop);
	void Add_Return(const Expr& exprSrc);
	template<typename T_Frame> void Add_PushFrame(const Expr& exprSrc);
	void Add_PushFrameFromStack(const Expr& exprSrc);
	void Add_PopFrame(const Expr& exprSrc);
	void Add_NoOperation(const Expr& exprSrc);
	void Add_Terminate(const Expr& exprSrc);
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
};

template<typename T_Frame>
void Composer::Add_PushFrame(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PushFrame<T_Frame>(exprSrc.Reference(), NextSeqId()));
}

}

#endif
