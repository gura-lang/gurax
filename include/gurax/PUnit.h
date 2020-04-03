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
public:
	// Constructor
	PUnit();
	// Copy constructor/operator
	PUnit(const PUnit& src) = delete;
	PUnit& operator=(const PUnit& src) = delete;
	// Move constructor/operator
	PUnit(PUnit&& src) = delete;
	PUnit& operator=(PUnit&& src) noexcept = delete;
	// Destructor
	virtual ~PUnit() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PUnit* pPUnit) const { return this == pPUnit; }
	bool IsEqualTo(const PUnit* pPUnit) const { return IsIdentical(pPUnit); }
	bool IsLessThan(const PUnit* pPUnit) const { return this < pPUnit; }
	String ToString() const { return ToString(StringStyle::Empty, 0); }
	String ToString(int seqIdOffset) const { return ToString(StringStyle::Empty, seqIdOffset); }
	String ToString(const StringStyle& ss) const { return ToString(ss, 0); }
public:
	SeqId GetSeqId(int seqIdOffset = 0) const {
		return MemoryPool::Global().GetChunkPUnit().CalcSeqId(this) - seqIdOffset;
	}
	String MakeSeqIdString(int seqIdOffset = 0) const;
	static String MakeSeqIdString(const PUnit* pPUnit, int seqIdOffset = 0) {
		return pPUnit? pPUnit->MakeSeqIdString(seqIdOffset) : "null";
	}
	void AppendInfoToString(String& str, const StringStyle& ss) const;
	void Print(const StringStyle& ss = StringStyle::Empty, int seqIdOffset = 0) const;
	static void Print(const PUnit* pPUnit, const PUnit* pPUnitSentinel,
					  const StringStyle& ss = StringStyle::Empty, int seqIdOffset = 0);
public:
	// Virtual functions
	virtual bool IsBridge() const { return false; }
	virtual bool IsBeginSequence() const { return false; }
	virtual bool IsEndSequence() const { return false; }
	virtual bool IsReturn() const { return false; }
	virtual bool GetDiscardValueFlag() const = 0;
	virtual void SetPUnitSentinel(const PUnit* pPUnit) { /* just ignore it */ }
	virtual void SetPUnitCont(const PUnit* pPUnit) { /* just ignore it */ }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) { /* just ignore it */ }
	virtual const PUnit* GetPUnitSentinel() const { return nullptr; } // only PUnit_BeginSequence returns a valid value.
	virtual const PUnit* GetPUnitCont() const = 0;
	virtual const PUnit* GetPUnitNext() const = 0;
	virtual const PUnit* GetPUnitAdjacent() const = 0;
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
	PUnit* _pPUnitCreated;
public:
	// Constructor
	PUnitFactory(Expr* pExprSrc) : _pExprSrc(pExprSrc), _pPUnitCreated(nullptr) {}
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
// PUnit_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Branch : public PUnit {
private:
	const PUnit* _pPUnitBranchDest;
public:
	// Constructor
	PUnit_Branch(const PUnit* pPUnitBranchDest) : _pPUnitBranchDest(pPUnitBranchDest) {}
public:
	// Virtual function of PUnit
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitBranchDest = pPUnit; }
	virtual const PUnit* GetPUnitBranchDest() const override { return _pPUnitBranchDest; }
};

class GURAX_DLLDECLARE PUnitFactory_Branch : public PUnitFactory {
protected:
	const PUnit* _pPUnitBranchDest;
public:
	PUnitFactory_Branch(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitBranchDest(pPUnitBranchDest) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Value(Value* pValue) : _pValue(pValue) {}
	PUnit_Value(Value* pValue, Expr* pExpr) : PUnit_Value(pValue) { _ppExprSrc[0] = pExpr; }
public:
	const Value* GetValue() const { return _pValue.get(); }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Value : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Value");
private:
	RefPtr<Value> _pValue;
public://_pExprSrc\ ? (sizeof\([^ \)] + \)). +
	PUnitFactory_Value(Value* pValue, Expr* pExprSrc) : PUnitFactory(pExprSrc), _pValue(pValue) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Value<false>);
	}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Lookup(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
	PUnit_Lookup(const Symbol* pSymbol, Expr* pExpr) : PUnit_Lookup(pSymbol) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Lookup : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Lookup");
private:
	const Symbol* _pSymbol;
public:
	PUnitFactory_Lookup(const Symbol* pSymbol, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Lookup<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Suffixed
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Suffixed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<StringReferable> _pStr;
	SuffixMgr::Target _target;
	const Symbol* _pSymbolSuffix;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Suffixed(StringReferable* pStr, SuffixMgr::Target target, const Symbol* pSymbolSuffix) :
		_pStr(pStr), _target(target), _pSymbolSuffix(pSymbolSuffix) {}
	PUnit_Suffixed(StringReferable* pStr, SuffixMgr::Target target, const Symbol* pSymbolSuffix, Expr* pExpr) :
		PUnit_Suffixed(pStr, target, pSymbolSuffix) { _ppExprSrc[0] = pExpr; }
public:
	const StringReferable& GetStringReferable() const { return *_pStr; }
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
	SuffixMgr::Target GetTarget() const { return _target; }
	const Symbol* GetSymbolSuffix() const { return _pSymbolSuffix; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Suffixed : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Suffixed");
private:
	RefPtr<StringReferable> _pStr;
	SuffixMgr::Target _target;
	const Symbol* _pSymbolSuffix;
public:
	PUnitFactory_Suffixed(StringReferable* pStr, SuffixMgr::Target target, const Symbol* pSymbolSuffix, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pStr(pStr), _target(target), _pSymbolSuffix(pSymbolSuffix) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Suffixed<false>);
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_AssignToSymbol(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
	PUnit_AssignToSymbol(const Symbol* pSymbol, Expr* pExpr) : PUnit_AssignToSymbol(pSymbol) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_AssignToSymbol : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignToSymbol");
private:
	const Symbol* _pSymbol;
public:
	PUnitFactory_AssignToSymbol(const Symbol* pSymbol, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_AssignToDeclArg(DeclArg* pDeclArg) : _pDeclArg(pDeclArg) {}
	PUnit_AssignToDeclArg(DeclArg* pDeclArg, Expr* pExpr) : PUnit_AssignToDeclArg(pDeclArg) { _ppExprSrc[0] = pExpr; }
public:
	const DeclArg& GetDeclArg() const { return *_pDeclArg; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_AssignToDeclArg : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignToDeclArg");
private:
	RefPtr<DeclArg> _pDeclArg;
public:
	PUnitFactory_AssignToDeclArg(DeclArg* pDeclArg, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pDeclArg(pDeclArg) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_AssignFunction(Function* pFunction) : _pFunction(pFunction) {}
	PUnit_AssignFunction(Function* pFunction, Expr* pExpr) : PUnit_AssignFunction(pFunction) { _ppExprSrc[0] = pExpr; }
public:
	const Function& GetFunction() const { return *_pFunction; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_AssignFunction : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignFunction");
private:
	RefPtr<Function> _pFunction;
public:
	PUnitFactory_AssignFunction(Function* pFunction, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pFunction(pFunction) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_AssignFunction<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignMethod
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool keepTargetFlag>
class GURAX_DLLDECLARE PUnit_AssignMethod : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Function> _pFunction;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_AssignMethod(Function* pFunction) : _pFunction(pFunction) {}
	PUnit_AssignMethod(Function* pFunction, Expr* pExpr) : PUnit_AssignMethod(pFunction) { _ppExprSrc[0] = pExpr; }
public:
	const Function& GetFunction() const { return *_pFunction; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_AssignMethod : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignMethod");
private:
	RefPtr<Function> _pFunction;
	bool _keepTargetFlag;
public:
	PUnitFactory_AssignMethod(Function* pFunction, bool keepTargetFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pFunction(pFunction), _keepTargetFlag(keepTargetFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_AssignMethod<false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignPropHandler
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool initByNilFlag>
class GURAX_DLLDECLARE PUnit_AssignPropHandler : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<DottedSymbol> _pDottedSymbol;
	PropHandler::Flags _flags;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_AssignPropHandler(const Symbol* pSymbol, DottedSymbol* pDottedSymbol, PropHandler::Flags flags) :
		_pSymbol(pSymbol), _pDottedSymbol(pDottedSymbol), _flags(flags) {}
	PUnit_AssignPropHandler(const Symbol* pSymbol, DottedSymbol* pDottedSymbol, PropHandler::Flags flags, Expr* pExpr) :
		PUnit_AssignPropHandler(pSymbol, pDottedSymbol, flags) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	const PropHandler::Flags GetFlags() const { return _flags; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_AssignPropHandler : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignPropHandler");
private:
	const Symbol* _pSymbol;
	RefPtr<DottedSymbol> _pDottedSymbol;
	PropHandler::Flags _flags;
	bool _initByNilFlag;
public:
	PUnitFactory_AssignPropHandler(const Symbol* pSymbol, DottedSymbol* pDottedSymbol, PropHandler::Flags flags, bool initByNilFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pDottedSymbol(pDottedSymbol), _flags(flags), _initByNilFlag(initByNilFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_AssignPropHandler<false, false>);
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
	DeclArg::Flags _flags;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Cast(const VType& vtype, DeclArg::Flags flags) : _vtype(vtype), _flags(flags) {}
	PUnit_Cast(const VType& vtype, DeclArg::Flags flags, Expr* pExpr) : PUnit_Cast(vtype, flags) { _ppExprSrc[0] = pExpr; }
public:
	const VType& GetVType() const { return _vtype; }
	DeclArg::Flags GetFlags() const { return _flags; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Cast : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Cast");
private:
	const VType& _vtype;
	DeclArg::Flags _flags;
public:
	PUnitFactory_Cast(const VType& vtype, DeclArg::Flags flags, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _vtype(vtype), _flags(flags) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator() {}
	PUnit_GenIterator(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator");
public:
	PUnitFactory_GenIterator(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_Range
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_Range : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator_Range() {}
	PUnit_GenIterator_Range(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator_Range : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_Range");
public:
	PUnitFactory_GenIterator_Range(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator_Range<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_Counter
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_Counter : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator_Counter() {}
	PUnit_GenIterator_Counter(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator_Counter : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_Counter");
public:
	PUnitFactory_GenIterator_Counter(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator_Counter<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_ForLister
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_ForLister : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator_ForLister() {}
	PUnit_GenIterator_ForLister(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator_ForLister : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_ForLister");
public:
	PUnitFactory_GenIterator_ForLister(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator_ForLister<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_for
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_for : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	bool _skipNilFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator_for(Expr_Block* pExprOfBlock, DeclArgOwner* pDeclArgOwner, bool skipNilFlag) :
		_pExprOfBlock(pExprOfBlock), _pDeclArgOwner(pDeclArgOwner), _skipNilFlag(skipNilFlag) {}
	PUnit_GenIterator_for(Expr_Block* pExprOfBlock, DeclArgOwner* pDeclArgOwner, bool skipNilFlag, Expr* pExpr) :
		PUnit_GenIterator_for(pExprOfBlock, pDeclArgOwner, skipNilFlag) { _ppExprSrc[0] = pExpr; }
public:
	const Expr_Block& GetExprOfBlock() const { return *_pExprOfBlock; }
	const DeclArgOwner& GetDeclArgOwner() const { return *_pDeclArgOwner; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator_for : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_for");
private:
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	bool _skipNilFlag;
public:
	PUnitFactory_GenIterator_for(Expr_Block* pExprOfBlock, DeclArgOwner* pDeclArgOwner, bool skipNilFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pExprOfBlock(pExprOfBlock), _pDeclArgOwner(pDeclArgOwner), _skipNilFlag(skipNilFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator_for<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_while
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_while : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	RefPtr<Expr> _pExprCriteria;
	RefPtr<Expr_Block> _pExprOfBlock;
	bool _skipNilFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator_while(Expr* pExprCriteria, Expr_Block* pExprOfBlock, bool skipNilFlag) :
		_pExprCriteria(pExprCriteria), _pExprOfBlock(pExprOfBlock), _skipNilFlag(skipNilFlag) {}
	PUnit_GenIterator_while(Expr* pExprCriteria, Expr_Block* pExprOfBlock, bool skipNilFlag, Expr* pExpr) :
		PUnit_GenIterator_while(pExprCriteria, pExprOfBlock, skipNilFlag) { _ppExprSrc[0] = pExpr; }
public:
	const Expr& GetExprCriteria() const { return *_pExprCriteria; }
	const Expr_Block& GetExprOfBlock() const { return *_pExprOfBlock; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator_while : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_while");
private:
	RefPtr<Expr> _pExprCriteria;
	RefPtr<Expr_Block> _pExprOfBlock;
	bool _skipNilFlag;
public:
	PUnitFactory_GenIterator_while(Expr* pExprCriteria, Expr_Block* pExprOfBlock, bool skipNilFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pExprCriteria(pExprCriteria), _pExprOfBlock(pExprOfBlock),
		_skipNilFlag(skipNilFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator_while<false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_repeat
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_repeat : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	RefPtr<Expr_Block> _pExprOfBlock;
	bool _finiteFlag;
	bool _skipNilFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_GenIterator_repeat(Expr_Block* pExprOfBlock, bool finiteFlag, bool skipNilFlag) :
		_pExprOfBlock(pExprOfBlock), _finiteFlag(finiteFlag), _skipNilFlag(skipNilFlag) {}
	PUnit_GenIterator_repeat(Expr_Block* pExprOfBlock, bool finiteFlag, bool skipNilFlag, Expr* pExpr) :
		PUnit_GenIterator_repeat(pExprOfBlock, finiteFlag, skipNilFlag) { _ppExprSrc[0] = pExpr; }
public:
	const Expr_Block& GetExprOfBlock() const { return *_pExprOfBlock; }
	bool GetFiniteFlag() const { return _finiteFlag; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_GenIterator_repeat : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_repeat");
private:
	RefPtr<Expr_Block> _pExprOfBlock;
	bool _finiteFlag;
	bool _skipNilFlag;
public:
	PUnitFactory_GenIterator_repeat(Expr_Block* pExprOfBlock, bool finiteFlag, bool skipNilFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pExprOfBlock(pExprOfBlock), _finiteFlag(finiteFlag), _skipNilFlag(skipNilFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_GenIterator_repeat<false>);
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
	bool _raiseFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_EvalIterator(size_t offset, bool raiseFlag, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1), _offset(offset), _raiseFlag(raiseFlag) {}
	PUnit_EvalIterator(size_t offset, bool raiseFlag, const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_EvalIterator(offset, raiseFlag, pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_EvalIterator : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EvalIterator");
private:
	size_t _offset;
	bool _raiseFlag;
public:
	PUnitFactory_EvalIterator(size_t offset, bool raiseFlag, const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc), _offset(offset), _raiseFlag(raiseFlag) {}
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
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_offset(offset), _pDeclArgOwner(pDeclArgOwner) {}
	PUnit_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_ForEach(offset, pDeclArgOwner, pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetOffset() const { return _offset; }
	const DeclArgOwner& GetDeclArgOwner() const { return *_pDeclArgOwner; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_ForEach : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ForEach");
private:
	size_t _offset;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
public:
	PUnitFactory_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc), _offset(offset), _pDeclArgOwner(pDeclArgOwner) {}
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
	const Operator* _pOp;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_UnaryOp(const Operator* pOp) : _pOp(pOp) {}
	PUnit_UnaryOp(const Operator* pOp, Expr* pExpr) : PUnit_UnaryOp(pOp) { _ppExprSrc[0] = pExpr; }
public:
	const Operator* GetOperator() const { return _pOp; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_UnaryOp : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_UnaryOp");
private:
	const Operator* _pOp;
public:
	PUnitFactory_UnaryOp(const Operator* pOp, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pOp(pOp) {}
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
	const Operator* _pOp;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_BinaryOp(const Operator* pOp) : _pOp(pOp) {}
	PUnit_BinaryOp(const Operator* pOp, Expr* pExpr) : PUnit_BinaryOp(pOp) { _ppExprSrc[0] = pExpr; }
public:
	const Operator* GetOperator() const { return _pOp; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_BinaryOp : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BinaryOp");
private:
	const Operator* _pOp;
public:
	PUnitFactory_BinaryOp(const Operator* pOp, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pOp(pOp) {}
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
	bool _binaryFlag;
	bool _mixInFlag;
	bool _overwriteFlag;
	bool _symbolForModuleFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool binaryFlag, bool mixInFlag, bool overwriteFlag, bool symbolForModuleFlag) :
		_pDottedSymbol(pDottedSymbol), _pSymbolList(pSymbolList),
		_binaryFlag(binaryFlag), _mixInFlag(mixInFlag), _overwriteFlag(overwriteFlag),
		_symbolForModuleFlag(symbolForModuleFlag) {}
	PUnit_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool binaryFlag, bool mixInFlag, bool overwriteFlag, bool symbolForModuleFlag, Expr* pExpr) :
		PUnit_Import(pDottedSymbol, pSymbolList, binaryFlag, mixInFlag, overwriteFlag, symbolForModuleFlag) { _ppExprSrc[0] = pExpr; }
public:
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	const SymbolList* GetSymbolList() const { return _pSymbolList.get(); }
	bool GetBinaryFlag() const { return _binaryFlag; }
	bool GetMixInFlag() const { return _mixInFlag; }
	bool GetOverwriteFlag() const { return _overwriteFlag; }
	bool GetSymbolForModuleFlag() const { return _symbolForModuleFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Import : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Import");
private:
	RefPtr<DottedSymbol> _pDottedSymbol;
	std::unique_ptr<SymbolList> _pSymbolList;
	bool _binaryFlag;
	bool _mixInFlag;
	bool _overwriteFlag;
	bool _symbolForModuleFlag;
public:
	PUnitFactory_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool binaryFlag, bool mixInFlag, bool overwriteFlag, bool symbolForModuleFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pDottedSymbol(pDottedSymbol), _pSymbolList(pSymbolList),
		_binaryFlag(binaryFlag), _mixInFlag(mixInFlag), _overwriteFlag(overwriteFlag), _symbolForModuleFlag(symbolForModuleFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Import<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CreateVType
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool inheritFlag>
class GURAX_DLLDECLARE PUnit_CreateVType : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_CreateVType() {}
	explicit PUnit_CreateVType(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_CreateVType : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateVType");
private:
	bool _inheritFlag;
public:
	PUnitFactory_CreateVType(bool inheritFlag, Expr* pExprSrc) : PUnitFactory(pExprSrc), _inheritFlag(inheritFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_CreateVType<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CompleteStruct
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_CompleteStruct : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_CompleteStruct() {}
	explicit PUnit_CompleteStruct(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_CompleteStruct : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CompleteStruct");
private:
public:
	PUnitFactory_CompleteStruct(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_CompleteStruct<false>);

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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_CreateList(size_t sizeReserve) : _sizeReserve(sizeReserve) {}
	explicit PUnit_CreateList(size_t sizeReserve, Expr* pExpr) : PUnit_CreateList(sizeReserve) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_CreateList : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateList");
private:
	size_t _sizeReserve;
public:
	PUnitFactory_CreateList(size_t sizeReserve, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _sizeReserve(sizeReserve) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_CreateList<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ListElem
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool xlistFlag, bool expandFlag>
class GURAX_DLLDECLARE PUnit_ListElem : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_ListElem(size_t offset) : _offset(offset) {}
	explicit PUnit_ListElem(size_t offset, Expr* pExpr) : PUnit_ListElem(offset) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_ListElem : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ListElem");
private:
	size_t _offset;
	bool _xlistFlag;
	bool _expandFlag;
public:
	PUnitFactory_ListElem(size_t offset, bool xlistFlag, bool expandFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _offset(offset), _xlistFlag(xlistFlag), _expandFlag(expandFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_ListElem<false, false, false>);

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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_CreateDict() {}
	explicit PUnit_CreateDict(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_CreateDict : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateDict");
public:
	PUnitFactory_CreateDict(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_DictElem(size_t offset) : _offset(offset) {}
	explicit PUnit_DictElem(size_t offset, Expr* pExpr) : PUnit_DictElem(offset) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_DictElem : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_DictElem");
private:
	size_t _offset;
public:
	PUnitFactory_DictElem(size_t offset, Expr* pExprSrc) : PUnitFactory(pExprSrc), _offset(offset) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Index(Attribute* pAttr, size_t sizeReserve) : _pAttr(pAttr), _sizeReserve(sizeReserve) {}
	PUnit_Index(Attribute* pAttr, size_t sizeReserve, Expr* pExpr) :
		PUnit_Index(pAttr, sizeReserve) { _ppExprSrc[0] = pExpr; }
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Index : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Index");
private:
	RefPtr<Attribute> _pAttr;
	size_t _sizeReserve;
public:
	PUnitFactory_Index(Attribute* pAttr, size_t sizeReserve, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pAttr(pAttr), _sizeReserve(sizeReserve) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_FeedIndex() {}
	explicit PUnit_FeedIndex(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_FeedIndex : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_FeedIndex");
public:
	PUnitFactory_FeedIndex(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_IndexGet() {}
	explicit PUnit_IndexGet(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_IndexGet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexGet");
public:
	PUnitFactory_IndexGet(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_IndexGet<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_IndexSet
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_IndexSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_IndexSet() {}
	explicit PUnit_IndexSet(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_IndexSet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexSet");
private:
	bool _valueFirstFlag;
public:
	PUnitFactory_IndexSet(bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_IndexSet<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_IndexOpApply
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_IndexOpApply : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
	const Operator* _pOp;
public:
	// Constructor
	PUnit_IndexOpApply(const Operator* pOp) : _pOp(pOp) {}
	explicit PUnit_IndexOpApply(const Operator* pOp, Expr* pExpr) :
		PUnit_IndexOpApply(pOp) { _ppExprSrc[0] = pExpr; }
public:
	const Operator& GetOperator() { return *_pOp; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_IndexOpApply : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexOpApply");
private:
	const Operator* _pOp;
	bool _valueFirstFlag;
public:
	PUnitFactory_IndexOpApply(const Operator* pOp, bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pOp(pOp), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_IndexOpApply<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberSet_Normal
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_MemberSet_Normal : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberSet_Normal(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_MemberSet_Normal(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_MemberSet_Normal(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberSet_Normal : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberSet_Normal");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	bool _valueFirstFlag;
public:
	PUnitFactory_MemberSet_Normal(const Symbol* pSymbol, Attribute* pAttr, bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberSet_Normal<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberSet_Map
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_MemberSet_Map : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	bool _mapAssignedFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberSet_Map(const Symbol* pSymbol, Attribute* pAttr, bool mapAssignedFlag) :
		_pSymbol(pSymbol), _pAttr(pAttr), _mapAssignedFlag(mapAssignedFlag) {}
	PUnit_MemberSet_Map(const Symbol* pSymbol, Attribute* pAttr, bool mapAssignedFlag, Expr* pExpr) :
		PUnit_MemberSet_Map(pSymbol, pAttr, mapAssignedFlag) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool GetMapAssignedFlag() const { return _mapAssignedFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberSet_Map : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberSet_Map");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	bool _mapAssignedFlag;
	bool _valueFirstFlag;
public:
	PUnitFactory_MemberSet_Map(const Symbol* pSymbol, Attribute* pAttr, bool mapAssignedFlag, bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr), _mapAssignedFlag(mapAssignedFlag), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberSet_Map<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberOpApply_Normal
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_MemberOpApply_Normal : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	const Operator* _pOp;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberOpApply_Normal(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp) :
		_pSymbol(pSymbol), _pAttr(pAttr), _pOp(pOp) {}
	PUnit_MemberOpApply_Normal(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp, Expr* pExpr) :
		PUnit_MemberOpApply_Normal(pSymbol, pAttr, pOp) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
	const Operator& GetOperator() const { return *_pOp; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberOpApply_Normal : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberOpApply_Normal");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	const Operator* _pOp;
	bool _valueFirstFlag;
public:
	PUnitFactory_MemberOpApply_Normal(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp, bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr), _pOp(pOp), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberOpApply_Normal<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberOpApply_Map
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_MemberOpApply_Map : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	const Operator* _pOp;
	bool _mapAssignedFlag;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberOpApply_Map(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp, bool mapAssignedFlag) :
		_pSymbol(pSymbol), _pAttr(pAttr), _pOp(pOp), _mapAssignedFlag(mapAssignedFlag) {}
	PUnit_MemberOpApply_Map(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp, bool mapAssignedFlag, Expr* pExpr) :
		PUnit_MemberOpApply_Map(pSymbol, pAttr, pOp, mapAssignedFlag) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
	const Operator& GetOperator() const { return *_pOp; }
	bool GetMapAssignedFlag() const { return _mapAssignedFlag; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberOpApply_Map : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberOpApply_Map");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	const Operator* _pOp;
	bool _mapAssignedFlag;
	bool _valueFirstFlag;
public:
	PUnitFactory_MemberOpApply_Map(const Symbol* pSymbol, Attribute* pAttr, const Operator* pOp, bool mapAssignedFlag, bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr), _pOp(pOp), _mapAssignedFlag(mapAssignedFlag), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberOpApply_Map<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberGet_Normal
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_MemberGet_Normal : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberGet_Normal(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_MemberGet_Normal(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_MemberGet_Normal(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberGet_Normal : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberGet_Normal");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_MemberGet_Normal(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberGet_Normal<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberGet_MapAlong
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_MemberGet_MapAlong : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberGet_MapAlong(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_MemberGet_MapAlong(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_MemberGet_MapAlong(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberGet_MapAlong : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberGet_MapAlong");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_MemberGet_MapAlong(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberGet_MapAlong<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberGet_MapToList
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_MemberGet_MapToList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberGet_MapToList(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_MemberGet_MapToList(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_MemberGet_MapToList(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberGet_MapToList : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberGet_MapToList");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_MemberGet_MapToList(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberGet_MapToList<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_MemberGet_MapToIter
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_MemberGet_MapToIter : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_MemberGet_MapToIter(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_MemberGet_MapToIter(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_MemberGet_MapToIter(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_MemberGet_MapToIter : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_MemberGet_MapToIter");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_MemberGet_MapToIter(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_MemberGet_MapToIter<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Argument
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool keepCarFlag>
class GURAX_DLLDECLARE PUnit_Argument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	DeclCallable::Flags _flags;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Argument(const Attribute& attr, Expr_Block* pExprOfBlock);
	PUnit_Argument(const Attribute& attr, Expr_Block* pExprOfBlock, Expr* pExpr) :
		PUnit_Argument(attr, pExprOfBlock) { _ppExprSrc[0] = pExpr; }
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	DeclCallable::Flags GetFlags() const { return _flags; }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Argument : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Argument");
private:
	RefPtr<Attribute> _pAttr;
	bool _keepCarFlag;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
public:
	PUnitFactory_Argument(Attribute* pAttr, Expr_Block* pExprOfBlock, bool keepCarFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pAttr(pAttr), _keepCarFlag(keepCarFlag), _pExprOfBlock(pExprOfBlock) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Argument<false, false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ArgumentDelegation
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ArgumentDelegation : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	DeclCallable::Flags _flags;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_ArgumentDelegation(const Attribute& attr);
	PUnit_ArgumentDelegation(const Attribute& attr, Expr* pExpr) :
		PUnit_ArgumentDelegation(attr) { _ppExprSrc[0] = pExpr; }
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	DeclCallable::Flags GetFlags() const { return _flags; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_ArgumentDelegation : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ArgumentDelegation");
private:
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_ArgumentDelegation(Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_ArgumentDelegation<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginArgSlot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginArgSlot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitSentinel;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_BeginArgSlot(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_pPUnitSentinel(this + 1) {}
	PUnit_BeginArgSlot(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_BeginArgSlot(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	const Expr& GetExprSrc() const { return *_ppExprSrc[0]; }
public:
	// Virtual functions of PUnit
	virtual bool IsBeginSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitSentinel(const PUnit* pPUnit) override { _pPUnitSentinel = pPUnit; }
	virtual const PUnit* GetPUnitSentinel() const override { return _pPUnitSentinel; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_BeginArgSlot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginArgSlot");
public:
	PUnitFactory_BeginArgSlot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_BeginArgSlot<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndArgSlot
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_EndArgSlot() {}
	explicit PUnit_EndArgSlot(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_EndArgSlot : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndArgSlot");
private:
public:
	PUnitFactory_EndArgSlot(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_EndArgSlot<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndArgSlotExpand
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndArgSlotExpand : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_EndArgSlotExpand() {}
	explicit PUnit_EndArgSlotExpand(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_EndArgSlotExpand : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndArgSlotExpand");
private:
public:
	PUnitFactory_EndArgSlotExpand(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_EndArgSlotExpand<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginArgSlotNamed
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginArgSlotNamed : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
	const PUnit* _pPUnitSentinel;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_BeginArgSlotNamed(const Symbol* pSymbol, Expr* pExprAssigned, const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1),
		_pSymbol(pSymbol), _pExprAssigned(pExprAssigned), _pPUnitSentinel(this + 1) {}
	PUnit_BeginArgSlotNamed(const Symbol* pSymbol, Expr* pExprAssigned, const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_BeginArgSlotNamed(pSymbol, pExprAssigned, pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExprAssigned() const { return _pExprAssigned.get(); }
	const Expr& GetExprSrc() const { return *_ppExprSrc[0]; }
public:
	// Virtual functions of PUnit
	virtual bool IsBeginSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitSentinel(const PUnit* pPUnit) override { _pPUnitSentinel = pPUnit; }
	virtual const PUnit* GetPUnitSentinel() const override { return _pPUnitSentinel; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_BeginArgSlotNamed : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginArgSlotNamed");
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
public:
	PUnitFactory_BeginArgSlotNamed(const Symbol* pSymbol,
								   Expr* pExprAssigned, const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc), _pSymbol(pSymbol), _pExprAssigned(pExprAssigned) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_BeginArgSlotNamed<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndArgSlotNamed
//------------------------------------------------------------------------------
template<bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_EndArgSlotNamed() {}
	explicit PUnit_EndArgSlotNamed(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_EndArgSlotNamed : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndArgSlotNamed");
private:
public:
	PUnitFactory_EndArgSlotNamed(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_EndArgSlotNamed<false>);

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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_Call() {}
	explicit PUnit_Call(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Call : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Call");
public:
	PUnitFactory_Call(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Jump(const PUnit* pPUnitCont) : _pPUnitCont(pPUnitCont? pPUnitCont : this + 1) {}
	PUnit_Jump() : PUnit_Jump(this + 1) {}
	PUnit_Jump(const PUnit* pPUnitCont, Expr* pExpr) : PUnit_Jump(pPUnitCont) { _ppExprSrc[0] = pExpr; }
	PUnit_Jump(Expr* pExpr) : PUnit_Jump(this + 1) { _ppExprSrc[0] = pExpr; }
	
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class GURAX_DLLDECLARE PUnitFactory_Jump : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Jump");
private:
	const PUnit* _pPUnitCont;
public:
	PUnitFactory_Jump(const PUnit* pPUnitCont, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitCont(pPUnitCont) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_JumpIf(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_JumpIf(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_JumpIf(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_JumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIf");
private:
public:
	PUnitFactory_JumpIf(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_JumpIfNot(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_JumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_JumpIfNot(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_JumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNot");
private:
public:
	PUnitFactory_JumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_NilJumpIf(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_NilJumpIf(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_NilJumpIf(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_NilJumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIf");
private:
public:
	PUnitFactory_NilJumpIf(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_NilJumpIfNot(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_NilJumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_NilJumpIfNot(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_NilJumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNot");
private:
public:
	PUnitFactory_NilJumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_KeepJumpIf(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_KeepJumpIf(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_KeepJumpIf(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_KeepJumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_KeepJumpIf");
private:
public:
	PUnitFactory_KeepJumpIf(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_KeepJumpIfNot(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_KeepJumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_KeepJumpIfNot(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_KeepJumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_KeepJumpIfNot");
private:
public:
	PUnitFactory_KeepJumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_BeginTryBlock(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_BeginTryBlock(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_BeginTryBlock(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_BeginTryBlock : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginTryBlock");
private:
public:
	PUnitFactory_BeginTryBlock(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_EndTryBlock(const PUnit* pPUnitCont) : _pPUnitCont(pPUnitCont? pPUnitCont : this + 1) {}
	PUnit_EndTryBlock(const PUnit* pPUnitCont, Expr* pExpr) :
		PUnit_EndTryBlock(pPUnitCont) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual void SetPUnitBranchDest(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

class GURAX_DLLDECLARE PUnitFactory_EndTryBlock : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndTryBlock");
private:
	const PUnit* _pPUnitCont;
public:
	PUnitFactory_EndTryBlock(const PUnit* pPUnitCont, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitCont(pPUnitCont) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_JumpIfNoCatch(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_JumpIfNoCatch(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_JumpIfNoCatch(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_JumpIfNoCatch : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNoCatch");
private:
public:
	PUnitFactory_JumpIfNoCatch(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_JumpIfNoCatchAny(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_JumpIfNoCatchAny(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_JumpIfNoCatchAny(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_JumpIfNoCatchAny : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNoCatchAny");
private:
public:
	PUnitFactory_JumpIfNoCatchAny(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_NilJumpIfNoCatch(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_NilJumpIfNoCatch(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_NilJumpIfNoCatch(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_NilJumpIfNoCatch : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNoCatch");
private:
public:
	PUnitFactory_NilJumpIfNoCatch(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_NilJumpIfNoCatchAny(const PUnit* pPUnitBranchDest) :
		PUnit_Branch(pPUnitBranchDest? pPUnitBranchDest : this + 1) {}
	PUnit_NilJumpIfNoCatchAny(const PUnit* pPUnitBranchDest, Expr* pExpr) :
		PUnit_NilJumpIfNoCatchAny(pPUnitBranchDest) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_NilJumpIfNoCatchAny : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNoCatchAny");
private:
public:
	PUnitFactory_NilJumpIfNoCatchAny(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_BeginSequence(const PUnit* pPUnitSentinel) : _pPUnitSentinel(pPUnitSentinel) {}
	PUnit_BeginSequence(const PUnit* pPUnitSentinel, Expr* pExpr) :
		PUnit_BeginSequence(pPUnitSentinel) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool IsBeginSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual void SetPUnitSentinel(const PUnit* pPUnit) override { _pPUnitSentinel = pPUnit; }
	virtual const PUnit* GetPUnitSentinel() const override { return _pPUnitSentinel; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_BeginSequence : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginSequence");
private:
	const PUnit* _pPUnitSentinel;
public:
	PUnitFactory_BeginSequence(const PUnit* pPUnitSentinel, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitSentinel(pPUnitSentinel) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_EndSequence() {}
	PUnit_EndSequence(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool IsEndSequence() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class GURAX_DLLDECLARE PUnitFactory_EndSequence : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndSequence");
public:
	PUnitFactory_EndSequence(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_DiscardValue() {}
	explicit PUnit_DiscardValue(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_DiscardValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_DiscardValue");
public:
	PUnitFactory_DiscardValue(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_RemoveValue(size_t offset) : _offset(offset) {}
	explicit PUnit_RemoveValue(size_t offset, Expr* pExpr) : PUnit_RemoveValue(offset) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetOffset() const { return _offset; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_RemoveValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_RemoveValue");
private:
	size_t _offset;
public:
	PUnitFactory_RemoveValue(size_t offset, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _offset(offset) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	explicit PUnit_RemoveValues(size_t offset, size_t cnt) : _offset(offset), _cnt(cnt) {}
	explicit PUnit_RemoveValues(size_t offset, size_t cnt, Expr* pExpr) :
		PUnit_RemoveValues(offset, cnt) { _ppExprSrc[0] = pExpr; }
public:
	size_t GetOffset() const { return _offset; }
	size_t GetCount() const { return _cnt; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_RemoveValues : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_RemoveValues");
private:
	size_t _offset;
	size_t _cnt;
public:
	PUnitFactory_RemoveValues(size_t offset, size_t cnt, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _offset(offset), _cnt(cnt) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_RemoveValues<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Break
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool branchDestFlag>
class GURAX_DLLDECLARE PUnit_Break : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitMarked;
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Break(const PUnit* pPUnitMarked) : _pPUnitMarked(pPUnitMarked) {}
	PUnit_Break(const PUnit* pPUnitMarked, Expr* pExpr) : PUnit_Break(pPUnitMarked) { _ppExprSrc[0] = pExpr; }
public:
	const PUnit* GetPUnitMarked() const { return _pPUnitMarked; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class GURAX_DLLDECLARE PUnitFactory_Break : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Break");
private:
	const PUnit* _pPUnitMarked;
	bool _branchDestFlag;
public:
	PUnitFactory_Break(const PUnit* pPUnitMarked, bool branchDestFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitMarked(pPUnitMarked),
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Continue(const PUnit* pPUnitOfLoop) : _pPUnitOfLoop(pPUnitOfLoop) {}
	PUnit_Continue(const PUnit* pPUnitOfLoop, Expr* pExpr) : PUnit_Continue(pPUnitOfLoop) { _ppExprSrc[0] = pExpr; }
public:
	const PUnit* GetPUnitOfLoop() const { return _pPUnitOfLoop; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class GURAX_DLLDECLARE PUnitFactory_Continue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Continue");
private:
	const PUnit* _pPUnitOfLoop;
public:
	PUnitFactory_Continue(const PUnit* pPUnitOfLoop, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitOfLoop(pPUnitOfLoop) {}
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
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Miscatch(Value* pValue) : _pValue(pValue) {}
	PUnit_Miscatch(Value* pValue, Expr* pExpr) : PUnit_Miscatch(pValue) { _ppExprSrc[0] = pExpr; }
public:
	const Value* GetValue() const { return _pValue.get(); }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_Miscatch : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Miscatch");
private:
	RefPtr<Value> _pValue;
public:
	PUnitFactory_Miscatch(Value* pValue, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pValue(pValue) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Miscatch<false>);

	}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_Return() {}
	PUnit_Return(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool IsReturn() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class GURAX_DLLDECLARE PUnitFactory_Return : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Return");
public:
	PUnitFactory_Return(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_Return<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PushFrame
//------------------------------------------------------------------------------
template<bool discardValueFlag, typename T_Frame>
class GURAX_DLLDECLARE PUnit_PushFrame : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_PushFrame() {}
	PUnit_PushFrame(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
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
	PUnitFactory_PushFrame(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_PushFrame<false, T_Frame>);

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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_PushFrameFromStack() {}
	PUnit_PushFrameFromStack(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_PushFrameFromStack : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PushFrameFromStack");
public:
	PUnitFactory_PushFrameFromStack(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_PopFrame() {}
	PUnit_PopFrame(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_PopFrame : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PopFrame");
public:
	PUnitFactory_PopFrame(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
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
private:
	Expr* _ppExprSrc[1];
public:
	// Constructor
	PUnit_NoOperation() {}
	PUnit_NoOperation(Expr* pExpr) { _ppExprSrc[0] = pExpr; }
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return discardValueFlag; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return this + 1; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return this + 1; }
};

class GURAX_DLLDECLARE PUnitFactory_NoOperation : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NoOperation");
public:
	PUnitFactory_NoOperation(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return sizeof(PUnit_NoOperation<false>);

	}
	virtual PUnit* Create(bool discardValueFlag) override;
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
	PUnit_Terminate() {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return false; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return nullptr; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return nullptr; }
};

class GURAX_DLLDECLARE PUnitFactory_Terminate : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Terminate");
public:
	PUnitFactory_Terminate() : PUnitFactory(Expr::Empty->Reference()) {}
	virtual size_t GetPUnitSize() const override { return sizeof(PUnit_Terminate); }
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
	PUnit_REPLEnd() {}
public:
	// Virtual functions of PUnit
	virtual bool GetDiscardValueFlag() const override { return false; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return nullptr; }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
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
	PUnit_Bridge() : _pPUnitCont(this + 1) {}
public:
	// Virtual functions of PUnit
	virtual void SetPUnitCont(const PUnit* pPUnit) override { _pPUnitCont = pPUnit; }
	virtual bool IsBridge() const override { return true; }
	virtual bool GetDiscardValueFlag() const override { return false; }
	virtual const PUnit* GetPUnitCont() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitNext() const override { return _GetPUnitCont(); }
	virtual const PUnit* GetPUnitAdjacent() const override { return this + 1; }
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss, int seqIdOffset) const override;
private:
	const PUnit* _GetPUnitCont() const { return _pPUnitCont; }
};

}

#endif
