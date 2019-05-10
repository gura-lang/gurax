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
protected:
	RefPtr<Expr> _pExprSrc;
	SeqId _seqId;
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
	String MakeSeqIdString(int seqIdOffset = 0) const;
	static String MakeSeqIdString(const PUnit* pPUnit, int seqIdOffset = 0) {
		return pPUnit? pPUnit->MakeSeqIdString(seqIdOffset) : "null";
	}
	void AppendInfoToString(String& str, const StringStyle& ss) const;
	void Print(const StringStyle& ss = StringStyle::Empty, int seqIdOffset = 0) const;
	static void Print(const PUnit* pPUnit, const PUnit* pPUnitSentinel,
					  const StringStyle& ss = StringStyle::Empty, int seqIdOffset = 0);
public:
	template<typename... Args>
	void IssueError(const ErrorType& errorType, const char* format, const Args&... args) const {
		Error::IssueWith(errorType, GetExprSrc(), format, args...);
	}
public:
	// Virtual functions
	virtual bool IsBridge() const { return false; }
	virtual bool IsBeginSequence() const { return false; }
	virtual bool IsEndSequence() const { return false; }
	virtual bool GetDiscardValueFlag() const = 0;
	virtual void SetPUnitSentinel(const PUnit* pPUnit) { /* just ignore it */ }
	virtual void SetPUnitCont(const PUnit* pPUnit) { /* just ignore it */ }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) { /* just ignore it */ }
	virtual const PUnit* GetPUnitSentinel() const { return nullptr; } // only PUnit_BeginSequence returns a valid value.
	virtual const PUnit* GetPUnitCont() const = 0;
	virtual const PUnit* GetPUnitNext() const = 0;
	virtual const PUnit* GetPUnitBranchDest() const { return nullptr; }
	virtual void Exec(Processor& processor) const = 0;
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
	virtual size_t GetPUnitSize() const = 0;
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
	void Shrink(size_t cnt);
};

//------------------------------------------------------------------------------
// Iterator_PUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_PUnit : public Iterator {
private:
	const PUnit* _pPUnit;
	const PUnit* _pPUnitSentinel;
public:
	Iterator_PUnit(const PUnit* pPUnit, const PUnit* pPUnitSentinel) :
		_pPUnit(pPUnit), _pPUnitSentinel(pPUnitSentinel) {}
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
	// Virtual function of PUnit
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitBranchDest = pPUnit; }
	virtual const PUnit* GetPUnitBranchDest() const override { return _pPUnitBranchDest; }
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override { return sizeof(PUnit_Value<false>); }
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Lookup<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_AssignToSymbol<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_AssignToDeclArg<false>);
	}
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
public:
	// Constructor
	PUnit_AssignFunction(Expr* pExprSrc, SeqId seqId, Function* pFunction) :
		PUnit(pExprSrc, seqId), _pFunction(pFunction) {}
public:
	const Function& GetFunction() const { return *_pFunction; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_AssignFunction : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignFunction");
private:
	RefPtr<Function> _pFunction;
public:
	PUnitFactory_AssignFunction(Expr* pExprSrc, PUnit::SeqId seqId, Function* pFunction) :
		PUnitFactory(pExprSrc, seqId), _pFunction(pFunction) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_AssignFunction<false>);
	}
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
	bool _listVarFlag;
public:
	// Constructor
	PUnit_Cast(Expr* pExprSrc, SeqId seqId, const VType& vtype, bool listVarFlag) :
		PUnit(pExprSrc, seqId), _vtype(vtype), _listVarFlag(listVarFlag) {}
public:
	const VType& GetVType() const { return _vtype; }
	bool GetListVarFlag() const { return _listVarFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Cast : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Cast");
private:
	const VType& _vtype;
	bool _listVarFlag;
public:
	PUnitFactory_Cast(Expr* pExprSrc, PUnit::SeqId seqId, const VType& vtype, bool listVarFlag) :
		PUnitFactory(pExprSrc, seqId), _vtype(vtype), _listVarFlag(listVarFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Cast<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenRangeIterator<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenCounterIterator<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_EvalIterator<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_ForEach<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_UnaryOp<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_BinaryOp<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Import
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Import : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<DottedSymbol> _pDottedSymbol;
	std::unique_ptr<SymbolList> _pSymbolList;
	bool _mixInFlag;
public:
	// Constructor
	PUnit_Import(Expr* pExprSrc, SeqId seqId, DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag) :
		PUnit(pExprSrc, seqId), _pDottedSymbol(pDottedSymbol), _pSymbolList(pSymbolList), _mixInFlag(mixInFlag) {}
public:
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	const SymbolList* GetSymbolList() const { return _pSymbolList.get(); }
	bool GetMixInFlag() const { return _mixInFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Import : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Import");
private:
	RefPtr<DottedSymbol> _pDottedSymbol;
	std::unique_ptr<SymbolList> _pSymbolList;
	bool _mixInFlag;
public:
	PUnitFactory_Import(Expr* pExprSrc, PUnit::SeqId seqId, DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag) :
		PUnitFactory(pExprSrc, seqId), _pDottedSymbol(pDottedSymbol), _pSymbolList(pSymbolList), _mixInFlag(mixInFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Import<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_CreateList<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ListElem
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool xlistFlag>
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_ListElem : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ListElem");
private:
	size_t _offset;
	bool _xlistFlag;
public:
	PUnitFactory_ListElem(Expr* pExprSrc, PUnit::SeqId seqId, size_t offset, bool xlistFlag) :
		PUnitFactory(pExprSrc, seqId), _offset(offset), _xlistFlag(xlistFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_ListElem<false, false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_CreateDict<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_DictElem<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Index<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_FeedIndex<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_IndexGet<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_IndexSet<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_PropGet<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_PropSet<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Member<false>);
	}
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
	DeclCallable::Flags _flags;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
public:
	// Constructor
	PUnit_Argument(Expr* pExprSrc, SeqId seqId, const Attribute& attr, Expr_Block* pExprOfBlock);
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	DeclCallable::Flags GetFlags() const { return _flags; }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Argument<false>);
	}
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
	const PUnit* _pPUnitSentinel;
public:
	// Constructor
	PUnit_ArgSlot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_pPUnitSentinel(this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool IsBeginSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitSentinel(const PUnit* pPUnit) override { _pPUnitSentinel = pPUnit; }
	virtual const PUnit* GetPUnitSentinel() const override { return _pPUnitSentinel; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_ArgSlot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ArgSlot");
public:
	PUnitFactory_ArgSlot(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_ArgSlot<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_FeedArgSlot<false>);
	}
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
	const PUnit* _pPUnitSentinel;
public:
	// Constructor
	PUnit_ArgSlotNamed(Expr* pExprSrc, SeqId seqId, const Symbol* pSymbol,
					   Expr* pExprAssigned, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_pSymbol(pSymbol), _pExprAssigned(pExprAssigned), _pPUnitSentinel(this + 1) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExprAssigned() const { return _pExprAssigned.get(); }
public:
	// Virtual functions of PUnit
	virtual bool IsBeginSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitSentinel(const PUnit* pPUnit) override { _pPUnitSentinel = pPUnit; }
	virtual const PUnit* GetPUnitSentinel() const override { return _pPUnitSentinel; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_ArgSlotNamed<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_FeedArgSlotNamed<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Call<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Jump<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_JumpIf<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_JumpIfNot<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_NilJumpIf<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_NilJumpIfNot<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_KeepJumpIf
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_KeepJumpIf : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_KeepJumpIf(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_KeepJumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_KeepJumpIf");
private:
public:
	PUnitFactory_KeepJumpIf(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_KeepJumpIf<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_KeepJumpIfNot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_KeepJumpIfNot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_KeepJumpIfNot(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_KeepJumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_KeepJumpIfNot");
private:
public:
	PUnitFactory_KeepJumpIfNot(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_KeepJumpIfNot<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginTryBlock
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginTryBlock : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_BeginTryBlock(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_BeginTryBlock : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginTryBlock");
private:
public:
	PUnitFactory_BeginTryBlock(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_BeginTryBlock<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndTryBlock
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndTryBlock : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit_EndTryBlock(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitCont) :
		PUnit(pExprSrc, seqId), _pPUnitCont(pPUnitCont? pPUnitCont : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class PUnitFactory_EndTryBlock : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndTryBlock");
private:
	const PUnit* _pPUnitCont;
public:
	PUnitFactory_EndTryBlock(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitCont) :
		PUnitFactory(pExprSrc, seqId), _pPUnitCont(pPUnitCont) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_EndTryBlock<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatch
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIfNoCatch : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_JumpIfNoCatch(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_JumpIfNoCatch : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNoCatch");
private:
public:
	PUnitFactory_JumpIfNoCatch(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_JumpIfNoCatch<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatchAny
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIfNoCatchAny : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_JumpIfNoCatchAny(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_JumpIfNoCatchAny : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNoCatchAny");
private:
public:
	PUnitFactory_JumpIfNoCatchAny(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_JumpIfNoCatchAny<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNoCatch
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIfNoCatch : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_NilJumpIfNoCatch(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_NilJumpIfNoCatch : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNoCatch");
private:
public:
	PUnitFactory_NilJumpIfNoCatch(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_NilJumpIfNoCatch<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNoCatchAny
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIfNoCatchAny : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_NilJumpIfNoCatchAny(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pExprSrc, seqId, pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_NilJumpIfNoCatchAny : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNoCatchAny");
private:
public:
	PUnitFactory_NilJumpIfNoCatchAny(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitBranchDest) :
		PUnitFactory_Branch(pExprSrc, seqId, pPUnitBranchDest) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_NilJumpIfNoCatchAny<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginSequence
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginSequence : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitSentinel;
public:
	// Constructor
	PUnit_BeginSequence(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitSentinel) :
		PUnit(pExprSrc, seqId), _pPUnitSentinel(pPUnitSentinel) {}
public:
	// Virtual functions of PUnit
	virtual bool IsBeginSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitSentinel(const PUnit* pPUnit) override { _pPUnitSentinel = pPUnit; }
	virtual const PUnit* GetPUnitSentinel() const override { return _pPUnitSentinel; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_BeginSequence : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginSequence");
private:
	const PUnit* _pPUnitSentinel;
public:
	PUnitFactory_BeginSequence(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitSentinel) :
		PUnitFactory(pExprSrc, seqId), _pPUnitSentinel(pPUnitSentinel) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_BeginSequence<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndSequence
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndSequence : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_EndSequence(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual bool IsEndSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class PUnitFactory_EndSequence : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndSequence");
public:
	PUnitFactory_EndSequence(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_EndSequence<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_DiscardValue
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_DiscardValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_DiscardValue(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_DiscardValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_DiscardValue");
public:
	PUnitFactory_DiscardValue(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_DiscardValue<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_RemoveValue<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_RemoveValues<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Break
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool breakPointFlag>
class GURAX_DLLDECLARE PUnit_Break : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitMarked;
public:
	// Constructor
	PUnit_Break(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitMarked) :
		PUnit(pExprSrc, seqId), _pPUnitMarked(pPUnitMarked) {}
public:
	const PUnit* GetPUnitMarked() const { return _pPUnitMarked; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class PUnitFactory_Break : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Break");
private:
	const PUnit* _pPUnitMarked;
	bool _branchDestFlag;
public:
	PUnitFactory_Break(Expr* pExprSrc, PUnit::SeqId seqId,
					   const PUnit* pPUnitMarked, bool branchDestFlag) :
		PUnitFactory(pExprSrc, seqId), _pPUnitMarked(pPUnitMarked),
		_branchDestFlag(branchDestFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Break<false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Continue
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Continue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitOfLoop;
public:
	// Constructor
	PUnit_Continue(Expr* pExprSrc, SeqId seqId, const PUnit* pPUnitOfLoop) :
		PUnit(pExprSrc, seqId), _pPUnitOfLoop(pPUnitOfLoop) {}
public:
	const PUnit* GetPUnitOfLoop() const { return _pPUnitOfLoop; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class PUnitFactory_Continue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Continue");
private:
	const PUnit* _pPUnitOfLoop;
public:
	PUnitFactory_Continue(Expr* pExprSrc, PUnit::SeqId seqId, const PUnit* pPUnitOfLoop) :
		PUnitFactory(pExprSrc, seqId), _pPUnitOfLoop(pPUnitOfLoop) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Continue<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Miscatch
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Miscatch : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Value> _pValue;
public:
	// Constructor
	PUnit_Miscatch(Expr* pExprSrc, SeqId seqId, Value* pValue) :
		PUnit(pExprSrc, seqId), _pValue(pValue) {}
public:
	const Value* GetValue() const { return _pValue.get(); }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_Miscatch : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Miscatch");
private:
	RefPtr<Value> _pValue;
public:
	PUnitFactory_Miscatch(Expr* pExprSrc, PUnit::SeqId seqId, Value* pValue) :
		PUnitFactory(pExprSrc, seqId), _pValue(pValue) {}
	virtual size_t GetPUnitSize() const override { return sizeof(PUnit_Miscatch<false>); }
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Return<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PushFrame
//------------------------------------------------------------------------------
template<typename T_Frame, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_PushFrame : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_PushFrame(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

template<typename T_Frame>
class PUnitFactory_PushFrame : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PushFrame");
public:
	PUnitFactory_PushFrame(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_PushFrame<T_Frame, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PushFrameFromStack
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_PushFrameFromStack : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	PUnit_PushFrameFromStack(Expr* pExprSrc, SeqId seqId) : PUnit(pExprSrc, seqId) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class PUnitFactory_PushFrameFromStack : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PushFrameFromStack");
public:
	PUnitFactory_PushFrameFromStack(Expr* pExprSrc, PUnit::SeqId seqId) :
		PUnitFactory(pExprSrc, seqId) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_PushFrameFromStack<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_PopFrame<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_NoOperation<false>);
	}
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
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return nullptr; }
	virtual void Exec(Processor& processor) const override;
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
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Terminate<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_REPLEnd
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_REPLEnd : public PUnit {
public:
	// Uses MemoryPool allocator
	static void *operator new(size_t bytes) {
		return MemoryPool::Global().GetChunkPUnit().AllocateGhost();
	}
	static void operator delete(void* p) {}
public:
	// Constructor
	PUnit_REPLEnd() : PUnit(Expr::Empty->Reference(), 0) {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return false; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return nullptr; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
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
		return MemoryPool::Global().GetChunkPUnit().AllocateGhost();
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
	virtual bool GetDiscardValueFlag() const override { return false; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return _GetPUnitCont(); }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

}

#endif
