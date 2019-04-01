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
		static const Flags None			= 0;
		static const Flags DiscardValue	= (1 << 0);
	};
protected:
	RefPtr<Expr> _pExprSrc;
	SeqId _seqId;
	Flags _flags;
public:
	// Constructor
	PUnit(Expr* pExprSrc, SeqId seqId);
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
	String ToString() const { return ToString(StringStyle::Empty, 0); }
	String ToString(int seqIdOffset) const { return ToString(StringStyle::Empty, seqIdOffset); }
	String ToString(const StringStyle& ss) const { return ToString(ss, 0); }
public:
	size_t GetSeqId(int seqIdOffset = 0) const { return _seqId - seqIdOffset; }
	String MakeSeqIdString(int seqIdOffset = 0) const {
		return String().Printf((seqIdOffset == 0)? "#%zu" : "##%zu", GetSeqId(seqIdOffset));
	}
	void _SetDiscardValueFlag() { _flags |= Flag::DiscardValue; }
	bool GetDiscardValueFlag() const { return (_flags & Flag::DiscardValue) != 0; }
	void AppendInfoToString(String& str, const StringStyle& ss) const;
	void Print(const StringStyle& ss = StringStyle::Empty, int seqIdOffset = 0) const;
public:
	template<typename... Args>
	void IssueError(const ErrorType& errorType, const char* format, const Args&... args) const {
		Error::IssueWith(errorType, GetExprSrc(), format, args...);
	}
public:
	// Virtual functions
	virtual bool IsReturn() const { return false; }
	virtual bool IsBridge() const { return false; }
	virtual bool GetDiscardValueFlag_New() const { return false; }
	virtual void SetPUnitExit(const PUnit* pPUnit) { /* just ignore it */ }
	virtual void SetPUnitCont(const PUnit* pPUnit) { /* just ignore it */ }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) { /* just ignore it */ }
	virtual const PUnit* GetPUnitExit() const { return nullptr; } // only PUnit_ExitPoint returns a valid value.
	virtual const PUnit* GetPUnitCont() const = 0;
	virtual const PUnit* GetPUnitNext() const = 0;
	virtual const PUnit* Exec(Processor& processor) const = 0;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const = 0;
};

//------------------------------------------------------------------------------
// PUnitFactory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitFactory : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PUnitFactory);
protected:
	RefPtr<Expr> _pExprSrc;
	PUnit::SeqId _seqId;
	PUnit* _pPUnitCreated;
public:
	// Constructor
	PUnitFactory(Expr* pExprSrc, PUnit::SeqId seqId) :
		_pExprSrc(pExprSrc), _seqId(seqId), _pPUnitCreated(nullptr) {}
	// Copy constructor/operator
	PUnitFactory(const PUnitFactory& src) = delete;
	PUnitFactory& operator=(const PUnitFactory& src) = delete;
	// Move constructor/operator
	PUnitFactory(PUnitFactory&& src) = delete;
	PUnitFactory& operator=(PUnitFactory&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~PUnitFactory() = default;
public:
	void SetPUnitExit(const PUnit* pPUnit) {
		if (_pPUnitCreated) _pPUnitCreated->SetPUnitExit(pPUnit);
	}
	void SetPUnitCont(const PUnit* pPUnit) {
		if (_pPUnitCreated) _pPUnitCreated->SetPUnitCont(pPUnit);
	}
	void SetPUnitBranchDest(const PUnit* pPUnit) {
		if (_pPUnitCreated) _pPUnitCreated->SetPUnitBranchDest(pPUnit);
	}
public:
	virtual PUnit* Create(bool discardValueFlag) = 0;
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
// Iterator_EachPUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachPUnit : public Iterator {
private:
	const PUnit* _pPUnit;
	const PUnit* _pPUnitExit;
	bool _returnAsEndFlag;
public:
	Iterator_EachPUnit(const PUnit* pPUnit, const PUnit* pPUnitExit, bool returnAsEndFlag) :
		_pPUnit(pPUnit), _pPUnitExit(pPUnitExit), _returnAsEndFlag(returnAsEndFlag) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual Value* NextValue() override;
	virtual size_t GetLength() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Branch : public PUnit {
private:
	const PUnit* _pPUnitBranchDest;
public:
	// Constructor
	PUnit_Branch(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit(pExprSrc, seqId), _pPUnitBranchDest(pPUnitBranchDest) {}
public:
	const PUnit* GetPUnitBranchDest() const { return _pPUnitBranchDest; }
public:
	// Virtual function of PUnit
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitBranchDest = pPUnit; }
};

class PUnitFactory_Branch : public PUnitFactory {
protected:
	const PUnit* _pPUnitBranchDest;
public:
	PUnitFactory_Branch(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory(pExprSrc, seqId), _pPUnitBranchDest(pPUnitBranchDest) {}
};

//------------------------------------------------------------------------------
// PUnit_Value
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual bool GetDiscardValueFlag_New() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Value : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Value");
private:
	RefPtr<Value> _pValue;
public:
	PUnitFactory_Value(Expr* pExprSrc, PUnit::SeqId seqId, Value* pValue) :
		PUnitFactory(pExprSrc, seqId), _pValue(pValue) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ValueAndJump
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
public:
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class PUnitFactory_ValueAndJump : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ValueAndJump");
private:
	RefPtr<Value> _pValue;
public:
	PUnitFactory_ValueAndJump(Expr* pExprSrc, PUnit::SeqId seqId, Value* pValue) :
		PUnitFactory(pExprSrc, seqId), _pValue(pValue) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Lookup
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Lookup : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Lookup");
private:
	const Symbol* _pSymbol;
public:
	PUnitFactory_Lookup(Expr* pExprSrc, PUnit::SeqId seqId, const Symbol* pSymbol) :
		PUnitFactory(pExprSrc, seqId), _pSymbol(pSymbol) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_AssignToSymbol : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignToSymbol");
private:
	const Symbol* _pSymbol;
public:
	PUnitFactory_AssignToSymbol(Expr* pExprSrc, PUnit::SeqId seqId, const Symbol* pSymbol) :
		PUnitFactory(pExprSrc, seqId), _pSymbol(pSymbol) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_AssignToDeclArg : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignToDeclArg");
private:
	RefPtr<DeclArg> _pDeclArg;
public:
	PUnitFactory_AssignToDeclArg(Expr* pExprSrc, PUnit::SeqId seqId, DeclArg* pDeclArg) :
		PUnitFactory(pExprSrc, seqId), _pDeclArg(pDeclArg) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignFunction
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
public:
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class PUnitFactory_AssignFunction : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignFunction");
private:
	RefPtr<Function> _pFunction;
public:
	PUnitFactory_AssignFunction(Expr* pExprSrc, PUnit::SeqId seqId, Function* pFunction) :
		PUnitFactory(pExprSrc, seqId), _pFunction(pFunction) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Cast
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Cast : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Cast");
private:
	const VType& _vtype;
public:
	PUnitFactory_Cast(Expr* pExprSrc, PUnit::SeqId seqId, const VType& vtype) :
		PUnitFactory(pExprSrc, seqId), _vtype(vtype) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_GenIterator : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator");
public:
	PUnitFactory_GenIterator(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenRangeIterator
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_GenRangeIterator : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenRangeIterator");
public:
	PUnitFactory_GenRangeIterator(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenCounterIterator
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenCounterIterator : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_GenCounterIterator(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_GenCounterIterator : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenCounterIterator");
public:
	PUnitFactory_GenCounterIterator(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EvalIterator
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EvalIterator : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
public:
	// Constructor
	PUnit_EvalIterator(Expr* pExprSrc, SeqId seqId, size_t offset, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1), _offset(offset) {}
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_EvalIterator : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EvalIterator");
private:
	size_t _offset;
public:
	PUnitFactory_EvalIterator(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest), _offset(offset) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ForEach
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ForEach : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	std::unique_ptr<DeclArgOwner> _pDeclArgOwner;
public:
	// Constructor
	PUnit_ForEach(Expr* pExprSrc, SeqId seqId, size_t offset,
				  DeclArgOwner* pDeclArgOwner, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_offset(offset), _pDeclArgOwner(pDeclArgOwner) {}
public:
	size_t GetOffset() const { return _offset; }
	const DeclArgOwner& GetDeclArgOwner() const { return *_pDeclArgOwner; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_ForEach : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ForEach");
private:
	size_t _offset;
	std::unique_ptr<DeclArgOwner> _pDeclArgOwner;
public:
	PUnitFactory_ForEach(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset,
		DeclArgOwner* pDeclArgOwner, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest), _offset(offset),
		_pDeclArgOwner(pDeclArgOwner) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_UnaryOp : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_UnaryOp");
private:
	const Operator* _pOperator;
public:
	PUnitFactory_UnaryOp(Expr* pExprSrc, PUnit::SeqId seqId, const Operator* pOperator) :
		PUnitFactory(pExprSrc, seqId), _pOperator(pOperator) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_BinaryOp : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BinaryOp");
private:
	const Operator* _pOperator;
public:
	PUnitFactory_BinaryOp(Expr* pExprSrc, PUnit::SeqId seqId, const Operator* pOperator) :
		PUnitFactory(pExprSrc, seqId), _pOperator(pOperator) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CreateList
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_CreateList : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateList");
private:
	size_t _sizeReserve;
public:
	PUnitFactory_CreateList(Expr* pExprSrc, PUnit::SeqId seqId, size_t sizeReserve) :
		PUnitFactory(pExprSrc, seqId), _sizeReserve(sizeReserve) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ListElem
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ListElem : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
public:
	// Constructor
	explicit PUnit_ListElem(Expr* pExprSrc, SeqId seqId, size_t offset) :
		PUnit(pExprSrc, seqId), _offset(offset) {}
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_ListElem : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ListElem");
private:
	size_t _offset;
public:
	PUnitFactory_ListElem(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset) :
		PUnitFactory(pExprSrc, seqId), _offset(offset) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CreateDict
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_CreateDict : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateDict");
public:
	PUnitFactory_CreateDict(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_DictElem
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_DictElem : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
public:
	// Constructor
	explicit PUnit_DictElem(Expr* pExprSrc, SeqId seqId, size_t offset) :
		PUnit(pExprSrc, seqId), _offset(offset) {}
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_DictElem : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_DictElem");
private:
	size_t _offset;
public:
	PUnitFactory_DictElem(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset) :
		PUnitFactory(pExprSrc, seqId), _offset(offset) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Index
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Index : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Index");
private:
	RefPtr<Attribute> _pAttr;
	size_t _sizeReserve;
public:
	PUnitFactory_Index(Expr* pExprSrc, PUnit::SeqId seqId, Attribute* pAttr, size_t sizeReserve) :
		PUnitFactory(pExprSrc, seqId), _pAttr(pAttr), _sizeReserve(sizeReserve) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_FeedIndex
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_FeedIndex : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_FeedIndex");
public:
	PUnitFactory_FeedIndex(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_IndexGet
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_IndexGet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexGet");
public:
	PUnitFactory_IndexGet(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_IndexSet
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_IndexSet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexSet");
public:
	PUnitFactory_IndexSet(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PropGet
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_PropGet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PropGet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_PropGet(Expr* pExprSrc, PUnit::SeqId seqId, const Symbol* pSymbol, Attribute* pAttr) :
		PUnitFactory(pExprSrc, seqId), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PropSet
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_PropSet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PropSet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_PropSet(Expr* pExprSrc, PUnit::SeqId seqId, const Symbol* pSymbol, Attribute* pAttr) :
		PUnitFactory(pExprSrc, seqId), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Member
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Member : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Member");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_Member(Expr* pExprSrc, PUnit::SeqId seqId, const Symbol* pSymbol, Attribute* pAttr) :
		PUnitFactory(pExprSrc, seqId), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Argument
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Argument : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Argument");
private:
	RefPtr<Attribute> _pAttr;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
public:
	PUnitFactory_Argument(Expr* pExprSrc, PUnit::SeqId seqId, Attribute* pAttr, Expr_Block* pExprOfBlock) :
		PUnitFactory(pExprSrc, seqId), _pAttr(pAttr), _pExprOfBlock(pExprOfBlock) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ArgSlot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ArgSlot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_ArgSlot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_pPUnitCont(this + 1) {}
public:
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class PUnitFactory_ArgSlot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ArgSlot");
public:
	PUnitFactory_ArgSlot(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_FeedArgSlot : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_FeedArgSlot");
private:
public:
	PUnitFactory_FeedArgSlot(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ArgSlotNamed : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_ArgSlotNamed(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol,
					   Expr* pExprAssigned, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_pSymbol(pSymbol), _pExprAssigned(pExprAssigned), _pPUnitCont(this + 1) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExprAssigned() const { return _pExprAssigned.get(); }
public:
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class PUnitFactory_ArgSlotNamed : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ArgSlotNamed");
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
public:
	PUnitFactory_ArgSlotNamed(Expr* pExprSrc, PUnit::SeqId seqId, const Symbol* pSymbol,
							  Expr* pExprAssigned, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest),
		_pSymbol(pSymbol), _pExprAssigned(pExprAssigned) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_FeedArgSlotNamed : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_FeedArgSlotNamed");
private:
public:
	PUnitFactory_FeedArgSlotNamed(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Call
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Call : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_Call(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Call : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Call");
public:
	PUnitFactory_Call(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Jump
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Jump : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_Jump(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitCont) :
		PUnit(pExprSrc, seqId), _pPUnitCont(pPUnitCont? pPUnitCont : this + 1) {}
	PUnit_Jump(Expr* pExprSrc, SeqId seqId) : PUnit_Jump(pExprSrc, seqId, this + 1) {}
public:
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class PUnitFactory_Jump : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Jump");
private:
	const PUnit* _pPUnitCont;
public:
	PUnitFactory_Jump(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitCont) :
		PUnitFactory(pExprSrc, seqId), _pPUnitCont(pPUnitCont) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIf
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIf : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_JumpIf(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_JumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIf");
private:
public:
	PUnitFactory_JumpIf(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIfNot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_JumpIfNot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_JumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNot");
private:
public:
	PUnitFactory_JumpIfNot(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIf : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_NilJumpIf(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_NilJumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIf");
private:
public:
	PUnitFactory_NilJumpIf(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIfNot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_NilJumpIfNot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_NilJumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNot");
private:
public:
	PUnitFactory_NilJumpIfNot(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ExitPoint
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	// Virtual functions of PUnit
	virtual void SetPUnitExit(const PUnit* pPUnit) override { _pPUnitExit = pPUnit; }
	virtual const PUnit* GetPUnitExit() const override { return _pPUnitExit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_ExitPoint : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ExitPoint");
private:
	const PUnit* _pPUnitExit;
public:
	PUnitFactory_ExitPoint(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitExit) :
		PUnitFactory(pExprSrc, seqId), _pPUnitExit(pPUnitExit) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PopValue
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_PopValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_PopValue(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_PopValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PopValue");
public:
	PUnitFactory_PopValue(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_RemoveValue
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_RemoveValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_RemoveValue");
private:
	size_t _offset;
public:
	PUnitFactory_RemoveValue(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset) :
		PUnitFactory(pExprSrc, seqId), _offset(offset) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_RemoveValues
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_RemoveValues : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	size_t _cnt;
public:
	// Constructor
	explicit PUnit_RemoveValues(Expr* pExprSrc, SeqId seqId, size_t offset, size_t cnt) :
		PUnit(pExprSrc, seqId), _offset(offset), _cnt(cnt) {}
public:
	size_t GetOffset() const { return _offset; }
	size_t GetCount() const { return _cnt; }
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_RemoveValues : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_RemoveValues");
private:
	size_t _offset;
	size_t _cnt;
public:
	PUnitFactory_RemoveValues(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset, size_t cnt) :
		PUnitFactory(pExprSrc, seqId), _offset(offset), _cnt(cnt) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Return
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Return : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_Return(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual bool IsReturn() const override { return true; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class PUnitFactory_Return : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Return");
public:
	PUnitFactory_Return(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PushFrame_Block
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_PushFrame_Block : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PushFrame_Block");
public:
	PUnitFactory_PushFrame_Block(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PopFrame
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_PopFrame : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PopFrame");
public:
	PUnitFactory_PopFrame(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NoOperation
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NoOperation : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_NoOperation(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_NoOperation : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NoOperation");
public:
	PUnitFactory_NoOperation(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Terminate
//------------------------------------------------------------------------------
template<bool discardValueFlag>
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
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class PUnitFactory_Terminate : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Terminate");
public:
	PUnitFactory_Terminate(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual PUnit* Create(bool discardValueFlag) override;
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
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual bool IsBridge() const override { return true; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return _GetPUnitCont(); }
	virtual const PUnit* Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

}

#endif
