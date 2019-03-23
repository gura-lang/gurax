//==============================================================================
// PUnit.h
//==============================================================================
#ifndef GURAX_PUNIT_H
#define GURAX_PUNIT_H
#include "Expr.h"
#include "Error.h"

namespace Gurax {

class Processor;

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit {
public:
	using SeqId = UInt32;
	using Flags = UInt32;
	struct Flag {
		static const Flags None					= 0;
		static const Flags PopValueToDiscard	= (1 << 0);
	};
protected:
	RefPtr<Expr> _pExprSrc;
	SeqId _seqId;
	Flags _flags;
public:
	// Constructor
	explicit PUnit(Expr* pExprSrc, SeqId seqId, Flags flags = Flag::None);
	// Copy constructor/operator
	PUnit(const PUnit& src) = delete;
	PUnit& operator=(const PUnit& src) = delete;
	// Move constructor/operator
	PUnit(PUnit&& src) = delete;
	PUnit& operator=(PUnit&& src) noexcept = delete;
	// Destructor
	virtual ~PUnit() = default;
public:
	const Expr& GetExprSrc() const { return *_pExprSrc; }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PUnit* pPUnit) const { return this == pPUnit; }
	bool IsEqualTo(const PUnit* pPUnit) const { return IsIdentical(pPUnit); }
	bool IsLessThan(const PUnit* pPUnit) const { return this < pPUnit; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	size_t GetSeqId() const { return _seqId; }
	bool IsBridge() const { return GetSeqId() == 0; }
	void SetPopValueToDiscardFlag() { _flags |= Flag::PopValueToDiscard; }
	bool GetPopValueToDiscardFlag() const { return (_flags & Flag::PopValueToDiscard) != 0; }
	void AppendInfoToString(String& str, const StringStyle& ss) const;
	void Print() const;
	static void PrintSequence(const PUnit* pPUnit);
public:
	template<typename... Args>
	void IssueError(const ErrorType& errorType, const char* format, const Args&... args) const {
		Error::IssueWith(errorType, GetExprSrc(), format, args...);
	}
public:
	// Virtual functions
	virtual const PUnit* GetPUnitExit() const { return nullptr; } // only PUnit_ExitPoint returns a valid value.
	virtual const PUnit* GetPUnitCont() const = 0;
	virtual const PUnit* GetPUnitNext() const = 0;
	virtual const PUnit* Exec(Processor& processor) const = 0;
	virtual String ToString(const StringStyle& ss) const = 0;
};

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitList : public std::vector<const PUnit*> {
public:
	void Print() const;
};

//------------------------------------------------------------------------------
// PUnitStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitStack : public PUnitList {
public:
	const PUnit* Peek(int offset) { return *(rbegin() + offset); }
	void Push(const PUnit* pPUnit) { push_back(pPUnit); }
	const PUnit* Pop() { const PUnit* pPUnit = back(); pop_back(); return pPUnit; }
};


//------------------------------------------------------------------------------
// PUnit_Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Value : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Value> _pValue;
public:
	// Constructor
	PUnit_Value(Expr* pExprSrc, SeqId seqId, Value* pValue) :
		PUnit(pExprSrc, seqId), _pValue(pValue) {}
public:
	const Value* GetValue() const { return _pValue.get(); }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_ValueAndJump
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ValueAndJump : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Value> _pValue;
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_ValueAndJump(Expr* pExprSrc, SeqId seqId, Value* pValue) :
	PUnit(pExprSrc, seqId), _pValue(pValue), _pPUnitCont(this + 1) {}
public:
	const Value* GetValue() const { return _pValue.get(); }
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

//------------------------------------------------------------------------------
// PUnit_Lookup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Lookup : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Lookup(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol) :
		PUnit(pExprSrc, seqId), _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AssignToSymbol : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_AssignToSymbol(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol) :
		PUnit(pExprSrc, seqId), _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AssignToDeclArg : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<DeclArg> _pDeclArg;
public:
	// Constructor
	PUnit_AssignToDeclArg(Expr* pExprSrc, SeqId seqId, DeclArg* pDeclArg) :
		PUnit(pExprSrc, seqId), _pDeclArg(pDeclArg) {}
public:
	const DeclArg& GetDeclArg() const { return *_pDeclArg; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_AssignFunction
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AssignFunction : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Function> _pFunction;
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_AssignFunction(Expr* pExprSrc, SeqId seqId, Function* pFunction) :
		PUnit(pExprSrc, seqId), _pFunction(pFunction), _pPUnitCont(this + 1) {}
public:
	const Function& GetFunction() const { return *_pFunction; }
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

//------------------------------------------------------------------------------
// PUnit_Cast
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Cast : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const VType& _vtype;
public:
	// Constructor
	PUnit_Cast(Expr* pExprSrc, SeqId seqId, const VType& vtype) :
		PUnit(pExprSrc, seqId), _vtype(vtype) {}
public:
	const VType& GetVType() const { return _vtype; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_GenIterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_GenIterator : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_GenIterator(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_GenRangeIterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_GenRangeIterator : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_GenRangeIterator(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_EvalIterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_EvalIterator : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	const PUnit* _pPUnitBranch;
public:
	// Constructor
	PUnit_EvalIterator(Expr* pExprSrc, SeqId seqId, size_t offset, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _offset(offset), _pPUnitBranch(pPUnitBranch) {}
public:
	size_t GetOffset() const { return _offset; }
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_UnaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_UnaryOp(Expr* pExprSrc, SeqId seqId, const Operator* pOperator) :
		PUnit(pExprSrc, seqId), _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_BinaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_BinaryOp(Expr* pExprSrc, SeqId seqId, const Operator* pOperator) :
		PUnit(pExprSrc, seqId), _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Add
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Add : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	int _added;
public:
	// Constructor
	PUnit_Add(Expr* pExprSrc, SeqId seqId, int added) :
		PUnit(pExprSrc, seqId), _added(added) {}
public:
	const int GetAdded() const { return _added; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_CreateList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _sizeReserve;
public:
	// Constructor
	explicit PUnit_CreateList(Expr* pExprSrc, SeqId seqId, size_t sizeReserve) :
		PUnit(pExprSrc, seqId), _sizeReserve(sizeReserve) {}
public:
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_AddList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AddList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_AddList(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_CreateDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateDict : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_CreateDict(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_AddDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AddDict : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_AddDict(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Index
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Index : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	size_t _sizeReserve;
public:
	// Constructor
	PUnit_Index(Expr* pExprSrc, SeqId seqId, Attribute* pAttr, size_t sizeReserve) :
		PUnit(pExprSrc, seqId), _pAttr(pAttr), _sizeReserve(sizeReserve) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_FeedIndex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedIndex : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_FeedIndex(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_IndexGet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_IndexGet(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_IndexSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_IndexSet(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_PropGet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PropGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropGet(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol, Attribute* pAttr) :
		PUnit(pExprSrc, seqId), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_PropSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PropSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropSet(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol, Attribute* pAttr) :
		PUnit(pExprSrc, seqId), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Member
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Member : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Member(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol, Attribute* pAttr) :
		PUnit(pExprSrc, seqId), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Argument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
public:
	// Constructor
	PUnit_Argument(Expr* pExprSrc, SeqId seqId, Attribute* pAttr, Expr_Block* pExprOfBlock) :
		PUnit(pExprSrc, seqId), _pAttr(pAttr), _pExprOfBlock(pExprOfBlock) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitBranch;
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_ArgSlot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _pPUnitBranch(pPUnitBranch), _pPUnitCont(this + 1) {}
public:
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_FeedArgSlot(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
	const PUnit* _pPUnitBranch;
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_ArgSlotNamed(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol, Expr* pExprAssigned, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _pSymbol(pSymbol), _pExprAssigned(pExprAssigned),
		_pPUnitBranch(pPUnitBranch), _pPUnitCont(this + 1) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExprAssigned() const { return _pExprAssigned.get(); }
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_FeedArgSlotNamed(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Call
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Call : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
public:
	// Constructor
	explicit PUnit_Call(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId), _pPUnitCont(this + 1) {}
public:
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

//------------------------------------------------------------------------------
// PUnit_Jump
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Jump : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_Jump(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitCont) :
		PUnit(pExprSrc, seqId), _pPUnitCont(pPUnitCont) {}
	PUnit_Jump(Expr* pExprSrc, SeqId seqId) : PUnit_Jump(pExprSrc, seqId, this + 1) {}
public:
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

//------------------------------------------------------------------------------
// PUnit_JumpIf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_JumpIf : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitBranch;
public:
	// Constructor
	PUnit_JumpIf(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _pPUnitBranch(pPUnitBranch) {}
public:
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_JumpIfNot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitBranch;
public:
	// Constructor
	PUnit_JumpIfNot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _pPUnitBranch(pPUnitBranch) {}
public:
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_NilJumpIf : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitBranch;
public:
	// Constructor
	PUnit_NilJumpIf(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _pPUnitBranch(pPUnitBranch) {}
public:
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_NilJumpIfNot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitBranch;
public:
	// Constructor
	PUnit_NilJumpIfNot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranch) :
		PUnit(pExprSrc, seqId), _pPUnitBranch(pPUnitBranch) {}
public:
	void SetPUnitBranch(const PUnit* pPUnit) { _pPUnitBranch = pPUnit; }
	const PUnit* GetPUnitBranch() const { return _pPUnitBranch; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_ExitPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ExitPoint : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitExit;
public:
	// Constructor
	PUnit_ExitPoint(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitExit) :
		PUnit(pExprSrc, seqId), _pPUnitExit(pPUnitExit) {}
public:
	void SetPUnitExit(const PUnit* pPUnit) { _pPUnitExit = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitExit() const override { return _pPUnitExit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_PopValueToDiscard
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PopValueToDiscard : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_PopValueToDiscard(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_RemoveValue
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_RemoveValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
public:
	// Constructor
	explicit PUnit_RemoveValue(Expr* pExprSrc, SeqId seqId, size_t offset) :
		PUnit(pExprSrc, seqId), _offset(offset) {}
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Return
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Return : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_Return(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

//------------------------------------------------------------------------------
// PUnit_PushFrame_Block
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PushFrame_Block : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_PushFrame_Block(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_PopFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PopFrame : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_PopFrame(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

//------------------------------------------------------------------------------
// PUnit_Terminate
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Terminate : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_Terminate(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return nullptr; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

//------------------------------------------------------------------------------
// PUnit_Bridge
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Bridge : public PUnit {
public:
	// Uses MemoryPool allocator
	static void *operator new(size_t bytes) {
		return MemoryPool::Global().chunkPUnit.AllocateBridge();
	}
	static void operator delete(void* p) {}
private:
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_Bridge() : PUnit(Expr::Empty->Reference(), 0), _pPUnitCont(this + 1) {}
public:
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return _GetPUnitCont(); }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

}

#endif
