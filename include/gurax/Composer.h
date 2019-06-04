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
public:
	void Add_Value(Value* pValue, const Expr* pExprSrc = nullptr);
	void Add_Lookup(const Symbol* pSymbol, const Expr* pExprSrc = nullptr);
	void Add_AssignToSymbol(const Symbol* pSymbol, const Expr* pExprSrc = nullptr);
	void Add_AssignToDeclArg(DeclArg* pDeclArg, const Expr* pExprSrc = nullptr);
	void Add_AssignFunction(Function* pFunction, const Expr* pExprSrc = nullptr);
	void Add_Cast(const VType& vtype, bool listVarFlag, const Expr* pExprSrc = nullptr);
	void Add_GenIterator(const Expr* pExprSrc = nullptr);
	void Add_GenRangeIterator(const Expr* pExprSrc = nullptr);
	void Add_GenCounterIterator(const Expr* pExprSrc = nullptr);
	void Add_EvalIterator(size_t offset, const Expr* pExprSrc = nullptr);
	void Add_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const Expr* pExprSrc = nullptr);
	void Add_UnaryOp(const Operator* pOperator, const Expr* pExprSrc = nullptr);
	void Add_BinaryOp(const Operator* pOperator, const Expr* pExprSrc = nullptr);
	void Add_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag, const Expr* pExprSrc = nullptr);
	void Add_CreateVType(const Expr* pExprSrc = nullptr);
	void Add_CreateList(size_t sizeReserve, const Expr* pExprSrc = nullptr);
	void Add_ListElem(size_t offset, bool xlistFlag, const Expr* pExprSrc = nullptr);
	void Add_CreateDict(const Expr* pExprSrc = nullptr);
	void Add_DictElem(size_t offset, const Expr* pExprSrc = nullptr);
	void Add_Index(Attribute* pAttr, size_t sizeReserve, const Expr* pExprSrc = nullptr);
	void Add_FeedIndex(const Expr* pExprSrc = nullptr);
	void Add_IndexGet(const Expr* pExprSrc = nullptr);
	void Add_IndexSet(const Expr* pExprSrc = nullptr);
	void Add_PropGet(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr);
	void Add_PropSet(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr);
	void Add_Member(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc = nullptr);
	void Add_Argument(Attribute* pAttr, Expr_Block* pExprOfBlock, const Expr* pExprSrc = nullptr);
	void Add_BeginArgSlot(const Expr* pExprSrc = nullptr);
	void Add_EndArgSlot(const Expr* pExprSrc = nullptr);
	void Add_BeginArgSlotNamed(const Symbol* pSymbol, Expr* pExprAssigned, const Expr* pExprSrc = nullptr);
	void Add_EndArgSlotNamed(const Expr* pExprSrc = nullptr);
	void Add_Call(const Expr* pExprSrc = nullptr);
	void Add_Jump(const Expr* pExprSrc = nullptr);
	void Add_Jump(const PUnit* pPUnitCont, const Expr* pExprSrc = nullptr);
	void Add_JumpIf(const Expr* pExprSrc = nullptr);
	void Add_JumpIfNot(const Expr* pExprSrc = nullptr);
	void Add_NilJumpIf(const Expr* pExprSrc = nullptr);
	void Add_NilJumpIfNot(const Expr* pExprSrc = nullptr);
	void Add_KeepJumpIf(const Expr* pExprSrc = nullptr);
	void Add_KeepJumpIfNot(const Expr* pExprSrc = nullptr);
	void Add_BeginTryBlock(const Expr* pExprSrc = nullptr);
	void Add_EndTryBlock(const Expr* pExprSrc = nullptr);
	void Add_JumpIfNoCatch(const Expr* pExprSrc = nullptr);
	void Add_JumpIfNoCatchAny(const Expr* pExprSrc = nullptr);
	void Add_NilJumpIfNoCatch(const Expr* pExprSrc = nullptr);
	void Add_NilJumpIfNoCatchAny(const Expr* pExprSrc = nullptr);
	void Add_BeginSequence(const Expr* pExprSrc = nullptr);
	void Add_EndSequence(const Expr* pExprSrc = nullptr);
	void Add_DiscardValue(const Expr* pExprSrc = nullptr);
	void Add_RemoveValue(size_t offset, const Expr* pExprSrc = nullptr);
	void Add_RemoveValues(size_t offset, size_t cnt, const Expr* pExprSrc = nullptr);
	void Add_Break(const PUnit* pPUnitMarked, bool branchDestFlag, const Expr* pExprSrc = nullptr);
	void Add_Continue(const PUnit* pPUnitOfLoop, const Expr* pExprSrc = nullptr);
	void Add_Miscatch(Value* pValue, const Expr* pExprSrc = nullptr);
	void Add_Return(const Expr* pExprSrc = nullptr);
	template<typename T_Frame> void Add_PushFrame(const Expr* pExprSrc = nullptr);
	void Add_PushFrameFromStack(const Expr* pExprSrc = nullptr);
	void Add_PopFrame(const Expr* pExprSrc = nullptr);
	void Add_NoOperation(const Expr* pExprSrc = nullptr);
	void Add_Terminate();
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
private:
	void _Flush(bool discardValueFlag);
};

template<typename T_Frame>
void Composer::Add_PushFrame(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_PushFrame<T_Frame>(Expr::Reference(pExprSrc)));
}

}

#endif
