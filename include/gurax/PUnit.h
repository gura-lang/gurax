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

class PUnitFactory_Branch : public PUnitFactory {
protected:
	const PUnit* _pPUnitBranchDest;
public:
	PUnitFactory_Branch(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitBranchDest(pPUnitBranchDest) {}
};

//------------------------------------------------------------------------------
// PUnit_Value
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Value : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Value> _pValue;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Value : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Value");
private:
	RefPtr<Value> _pValue;
public:
	PUnitFactory_Value(Value* pValue, Expr* pExprSrc) : PUnitFactory(pExprSrc), _pValue(pValue) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Value<1, false>) : sizeof(PUnit_Value<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Lookup
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Lookup : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Lookup : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Lookup");
private:
	const Symbol* _pSymbol;
public:
	PUnitFactory_Lookup(const Symbol* pSymbol, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Lookup<1, false>) : sizeof(PUnit_Lookup<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Suffixed
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Suffixed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<StringReferable> _pStr;
	SuffixMgr::Target _target;
	const Symbol* _pSymbolSuffix;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Suffixed : public PUnitFactory {
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
		return _pExprSrc? sizeof(PUnit_Suffixed<1, false>) : sizeof(PUnit_Suffixed<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_AssignToSymbol : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_AssignToSymbol : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignToSymbol");
private:
	const Symbol* _pSymbol;
public:
	PUnitFactory_AssignToSymbol(const Symbol* pSymbol, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_AssignToSymbol<1, false>) : sizeof(PUnit_AssignToSymbol<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_AssignToDeclArg : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<DeclArg> _pDeclArg;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_AssignToDeclArg : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignToDeclArg");
private:
	RefPtr<DeclArg> _pDeclArg;
public:
	PUnitFactory_AssignToDeclArg(DeclArg* pDeclArg, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pDeclArg(pDeclArg) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_AssignToDeclArg<1, false>) : sizeof(PUnit_AssignToDeclArg<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignFunction
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_AssignFunction : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Function> _pFunction;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_AssignFunction : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignFunction");
private:
	RefPtr<Function> _pFunction;
public:
	PUnitFactory_AssignFunction(Function* pFunction, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pFunction(pFunction) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_AssignFunction<1, false>) : sizeof(PUnit_AssignFunction<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignMethod
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool keepTargetFlag>
class GURAX_DLLDECLARE PUnit_AssignMethod : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Function> _pFunction;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_AssignMethod : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_AssignMethod");
private:
	RefPtr<Function> _pFunction;
	bool _keepTargetFlag;
public:
	PUnitFactory_AssignMethod(Function* pFunction, bool keepTargetFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pFunction(pFunction), _keepTargetFlag(keepTargetFlag) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_AssignMethod<1, false, false>) : sizeof(PUnit_AssignMethod<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_AssignPropHandler
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool initByNilFlag>
class GURAX_DLLDECLARE PUnit_AssignPropHandler : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<DottedSymbol> _pDottedSymbol;
	PropHandler::Flags _flags;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_AssignPropHandler : public PUnitFactory {
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
		return _pExprSrc? sizeof(PUnit_AssignPropHandler<1, false, false>) : sizeof(PUnit_AssignPropHandler<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Cast
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Cast : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const VType& _vtype;
	DeclArg::Flags _flags;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Cast : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Cast");
private:
	const VType& _vtype;
	DeclArg::Flags _flags;
public:
	PUnitFactory_Cast(const VType& vtype, DeclArg::Flags flags, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _vtype(vtype), _flags(flags) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Cast<1, false>) : sizeof(PUnit_Cast<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_GenIterator : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator");
public:
	PUnitFactory_GenIterator(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_GenIterator<1, false>) : sizeof(PUnit_GenIterator<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_Range
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_Range : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_GenIterator_Range : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_Range");
public:
	PUnitFactory_GenIterator_Range(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_GenIterator_Range<1, false>) : sizeof(PUnit_GenIterator_Range<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_Counter
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_Counter : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_GenIterator_Counter : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_Counter");
public:
	PUnitFactory_GenIterator_Counter(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_GenIterator_Counter<1, false>) : sizeof(PUnit_GenIterator_Counter<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_ForLister
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_ForLister : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_GenIterator_ForLister : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_GenIterator_ForLister");
public:
	PUnitFactory_GenIterator_ForLister(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_GenIterator_ForLister<1, false>) : sizeof(PUnit_GenIterator_ForLister<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_GenIterator_repeat
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_GenIterator_repeat : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
	RefPtr<Expr_Block> _pExprOfBlock;
	bool _finiteFlag;
	bool _skipNilFlag;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_GenIterator_repeat : public PUnitFactory {
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
		return _pExprSrc?
			sizeof(PUnit_GenIterator_repeat<1, false>) :
			sizeof(PUnit_GenIterator_repeat<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EvalIterator
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EvalIterator : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	bool _raiseFlag;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_EvalIterator : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EvalIterator");
private:
	size_t _offset;
	bool _raiseFlag;
public:
	PUnitFactory_EvalIterator(size_t offset, bool raiseFlag, const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc), _offset(offset), _raiseFlag(raiseFlag) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_EvalIterator<1, false>) : sizeof(PUnit_EvalIterator<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ForEach
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ForEach : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_ForEach : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ForEach");
private:
	size_t _offset;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
public:
	PUnitFactory_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc), _offset(offset), _pDeclArgOwner(pDeclArgOwner) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_ForEach<1, false>) : sizeof(PUnit_ForEach<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_UnaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Operator* _pOperator;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_UnaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
	PUnit_UnaryOp(const Operator* pOperator, Expr* pExpr) : PUnit_UnaryOp(pOperator) { _ppExprSrc[0] = pExpr; }
public:
	const Operator* GetOperator() const { return _pOperator; }
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

class PUnitFactory_UnaryOp : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_UnaryOp");
private:
	const Operator* _pOperator;
public:
	PUnitFactory_UnaryOp(const Operator* pOperator, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pOperator(pOperator) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_UnaryOp<1, false>) : sizeof(PUnit_UnaryOp<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BinaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Operator* _pOperator;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_BinaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
	PUnit_BinaryOp(const Operator* pOperator, Expr* pExpr) : PUnit_BinaryOp(pOperator) { _ppExprSrc[0] = pExpr; }
public:
	const Operator* GetOperator() const { return _pOperator; }
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

class PUnitFactory_BinaryOp : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BinaryOp");
private:
	const Operator* _pOperator;
public:
	PUnitFactory_BinaryOp(const Operator* pOperator, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pOperator(pOperator) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_BinaryOp<1, false>) : sizeof(PUnit_BinaryOp<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Import
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
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
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Import : public PUnitFactory {
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
		return _pExprSrc? sizeof(PUnit_Import<1, false>) : sizeof(PUnit_Import<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CreateVType
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool inheritFlag>
class GURAX_DLLDECLARE PUnit_CreateVType : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_CreateVType : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateVType");
private:
	bool _inheritFlag;
public:
	PUnitFactory_CreateVType(bool inheritFlag, Expr* pExprSrc) : PUnitFactory(pExprSrc), _inheritFlag(inheritFlag) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_CreateVType<1, false, false>) : sizeof(PUnit_CreateVType<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CompleteStruct
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_CompleteStruct : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_CompleteStruct : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CompleteStruct");
private:
public:
	PUnitFactory_CompleteStruct(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_CompleteStruct<1, false>) : sizeof(PUnit_CompleteStruct<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CreateList
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_CreateList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _sizeReserve;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_CreateList : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateList");
private:
	size_t _sizeReserve;
public:
	PUnitFactory_CreateList(size_t sizeReserve, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _sizeReserve(sizeReserve) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_CreateList<1, false>) : sizeof(PUnit_CreateList<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ListElem
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool xlistFlag, bool expandFlag>
class GURAX_DLLDECLARE PUnit_ListElem : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_ListElem : public PUnitFactory {
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
		return _pExprSrc? sizeof(PUnit_ListElem<1, false, false, false>) : sizeof(PUnit_ListElem<0, false, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_CreateDict
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_CreateDict : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_CreateDict : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_CreateDict");
public:
	PUnitFactory_CreateDict(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_CreateDict<1, false>) : sizeof(PUnit_CreateDict<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_DictElem
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_DictElem : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_DictElem : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_DictElem");
private:
	size_t _offset;
public:
	PUnitFactory_DictElem(size_t offset, Expr* pExprSrc) : PUnitFactory(pExprSrc), _offset(offset) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_DictElem<1, false>) : sizeof(PUnit_DictElem<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Index
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Index : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	size_t _sizeReserve;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Index : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Index");
private:
	RefPtr<Attribute> _pAttr;
	size_t _sizeReserve;
public:
	PUnitFactory_Index(Attribute* pAttr, size_t sizeReserve, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pAttr(pAttr), _sizeReserve(sizeReserve) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Index<1, false>) : sizeof(PUnit_Index<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_FeedIndex
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_FeedIndex : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_FeedIndex : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_FeedIndex");
public:
	PUnitFactory_FeedIndex(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_FeedIndex<1, false>) : sizeof(PUnit_FeedIndex<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_IndexGet
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_IndexGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_IndexGet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexGet");
public:
	PUnitFactory_IndexGet(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_IndexGet<1, false>) : sizeof(PUnit_IndexGet<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_IndexSet
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_IndexSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_IndexSet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_IndexSet");
private:
	bool _valueFirstFlag;
public:
	PUnitFactory_IndexSet(bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_IndexSet<1, false, false>) : sizeof(PUnit_IndexSet<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PropGet
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_PropGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_PropGet(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_PropGet(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_PropGet(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
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

class PUnitFactory_PropGet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PropGet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_PropGet(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_PropGet<1, false>) : sizeof(PUnit_PropGet<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PropSet
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
class GURAX_DLLDECLARE PUnit_PropSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_PropSet(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_PropSet(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_PropSet(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
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

class PUnitFactory_PropSet : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PropSet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	bool _valueFirstFlag;
public:
	PUnitFactory_PropSet(const Symbol* pSymbol, Attribute* pAttr, bool valueFirstFlag, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr), _valueFirstFlag(valueFirstFlag) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_PropSet<1, false, false>) : sizeof(PUnit_PropSet<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Member_Normal
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Member_Normal : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_Member_Normal(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_Member_Normal(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_Member_Normal(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
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

class PUnitFactory_Member_Normal : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Member_Normal");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_Member_Normal(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Member_Normal<1, false>) : sizeof(PUnit_Member_Normal<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Member_MapAlong
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Member_MapAlong : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_Member_MapAlong(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_Member_MapAlong(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_Member_MapAlong(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
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

class PUnitFactory_Member_MapAlong : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Member_MapAlong");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_Member_MapAlong(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Member_MapAlong<1, false>) : sizeof(PUnit_Member_MapAlong<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Member_MapToList
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Member_MapToList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_Member_MapToList(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_Member_MapToList(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_Member_MapToList(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
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

class PUnitFactory_Member_MapToList : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Member_MapToList");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_Member_MapToList(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Member_MapToList<1, false>) : sizeof(PUnit_Member_MapToList<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Member_MapToIter
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Member_MapToIter : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
protected:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
	Expr* _ppExprSrc[nExprSrc];
public:
	// Constructor
	PUnit_Member_MapToIter(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
	PUnit_Member_MapToIter(const Symbol* pSymbol, Attribute* pAttr, Expr* pExpr) :
		PUnit_Member_MapToIter(pSymbol, pAttr) { _ppExprSrc[0] = pExpr; }
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

class PUnitFactory_Member_MapToIter : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Member_MapToIter");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_Member_MapToIter(const Symbol* pSymbol, Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Member_MapToIter<1, false>) : sizeof(PUnit_Member_MapToIter<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Argument
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool keepCarFlag>
class GURAX_DLLDECLARE PUnit_Argument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	DeclCallable::Flags _flags;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Argument : public PUnitFactory {
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
		return _pExprSrc? sizeof(PUnit_Argument<1, false, false>) : sizeof(PUnit_Argument<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_ArgumentDelegation
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_ArgumentDelegation : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	DeclCallable::Flags _flags;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_ArgumentDelegation : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_ArgumentDelegation");
private:
	RefPtr<Attribute> _pAttr;
public:
	PUnitFactory_ArgumentDelegation(Attribute* pAttr, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pAttr(pAttr) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_ArgumentDelegation<1, false>) : sizeof(PUnit_ArgumentDelegation<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginArgSlot
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginArgSlot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitSentinel;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_BeginArgSlot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginArgSlot");
public:
	PUnitFactory_BeginArgSlot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_BeginArgSlot<1, false>) : sizeof(PUnit_BeginArgSlot<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndArgSlot
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_EndArgSlot : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndArgSlot");
private:
public:
	PUnitFactory_EndArgSlot(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_EndArgSlot<1, false>) : sizeof(PUnit_EndArgSlot<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndArgSlotExpand
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndArgSlotExpand : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_EndArgSlotExpand : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndArgSlotExpand");
private:
public:
	PUnitFactory_EndArgSlotExpand(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_EndArgSlotExpand<1, false>) : sizeof(PUnit_EndArgSlotExpand<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginArgSlotNamed
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginArgSlotNamed : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
	const PUnit* _pPUnitSentinel;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_BeginArgSlotNamed : public PUnitFactory_Branch {
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
		return _pExprSrc? sizeof(PUnit_BeginArgSlotNamed<1, false>) : sizeof(PUnit_BeginArgSlotNamed<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndArgSlotNamed
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_EndArgSlotNamed : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndArgSlotNamed");
private:
public:
	PUnitFactory_EndArgSlotNamed(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_EndArgSlotNamed<1, false>) : sizeof(PUnit_EndArgSlotNamed<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Call
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Call : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Call : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Call");
public:
	PUnitFactory_Call(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Call<1, false>) : sizeof(PUnit_Call<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Jump
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Jump : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Jump : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Jump");
private:
	const PUnit* _pPUnitCont;
public:
	PUnitFactory_Jump(const PUnit* pPUnitCont, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitCont(pPUnitCont) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Jump<1, false>) : sizeof(PUnit_Jump<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIf
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIf : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_JumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIf");
private:
public:
	PUnitFactory_JumpIf(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_JumpIf<1, false>) : sizeof(PUnit_JumpIf<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIfNot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_JumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNot");
private:
public:
	PUnitFactory_JumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_JumpIfNot<1, false>) : sizeof(PUnit_JumpIfNot<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIf : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_NilJumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIf");
private:
public:
	PUnitFactory_NilJumpIf(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_NilJumpIf<1, false>) : sizeof(PUnit_NilJumpIf<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIfNot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_NilJumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNot");
private:
public:
	PUnitFactory_NilJumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_NilJumpIfNot<1, false>) : sizeof(PUnit_NilJumpIfNot<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_KeepJumpIf
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_KeepJumpIf : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_KeepJumpIf : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_KeepJumpIf");
private:
public:
	PUnitFactory_KeepJumpIf(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_KeepJumpIf<1, false>) : sizeof(PUnit_KeepJumpIf<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_KeepJumpIfNot
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_KeepJumpIfNot : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_KeepJumpIfNot : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_KeepJumpIfNot");
private:
public:
	PUnitFactory_KeepJumpIfNot(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_KeepJumpIfNot<1, false>) : sizeof(PUnit_KeepJumpIfNot<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginTryBlock
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginTryBlock : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_BeginTryBlock : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginTryBlock");
private:
public:
	PUnitFactory_BeginTryBlock(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_BeginTryBlock<1, false>) : sizeof(PUnit_BeginTryBlock<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndTryBlock
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndTryBlock : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitCont;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_EndTryBlock : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndTryBlock");
private:
	const PUnit* _pPUnitCont;
public:
	PUnitFactory_EndTryBlock(const PUnit* pPUnitCont, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitCont(pPUnitCont) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_EndTryBlock<1, false>) : sizeof(PUnit_EndTryBlock<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatch
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIfNoCatch : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_JumpIfNoCatch : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNoCatch");
private:
public:
	PUnitFactory_JumpIfNoCatch(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_JumpIfNoCatch<1, false>) : sizeof(PUnit_JumpIfNoCatch<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatchAny
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_JumpIfNoCatchAny : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_JumpIfNoCatchAny : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_JumpIfNoCatchAny");
private:
public:
	PUnitFactory_JumpIfNoCatchAny(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_JumpIfNoCatchAny<1, false>) : sizeof(PUnit_JumpIfNoCatchAny<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNoCatch
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIfNoCatch : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_NilJumpIfNoCatch : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNoCatch");
private:
public:
	PUnitFactory_NilJumpIfNoCatch(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_NilJumpIfNoCatch<1, false>) : sizeof(PUnit_NilJumpIfNoCatch<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNoCatchAny
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NilJumpIfNoCatchAny : public PUnit_Branch {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_NilJumpIfNoCatchAny : public PUnitFactory_Branch {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NilJumpIfNoCatchAny");
private:
public:
	PUnitFactory_NilJumpIfNoCatchAny(const PUnit* pPUnitBranchDest, Expr* pExprSrc) :
		PUnitFactory_Branch(pPUnitBranchDest, pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_NilJumpIfNoCatchAny<1, false>) : sizeof(PUnit_NilJumpIfNoCatchAny<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_BeginSequence
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_BeginSequence : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitSentinel;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_BeginSequence : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_BeginSequence");
private:
	const PUnit* _pPUnitSentinel;
public:
	PUnitFactory_BeginSequence(const PUnit* pPUnitSentinel, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitSentinel(pPUnitSentinel) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_BeginSequence<1, false>) : sizeof(PUnit_BeginSequence<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_EndSequence
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_EndSequence : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_EndSequence : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_EndSequence");
public:
	PUnitFactory_EndSequence(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_EndSequence<1, false>) : sizeof(PUnit_EndSequence<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_DiscardValue
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_DiscardValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_DiscardValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_DiscardValue");
public:
	PUnitFactory_DiscardValue(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_DiscardValue<1, false>) : sizeof(PUnit_DiscardValue<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_RemoveValue
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_RemoveValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_RemoveValue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_RemoveValue");
private:
	size_t _offset;
public:
	PUnitFactory_RemoveValue(size_t offset, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _offset(offset) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_RemoveValue<1, false>) : sizeof(PUnit_RemoveValue<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_RemoveValues
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_RemoveValues : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _offset;
	size_t _cnt;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_RemoveValues : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_RemoveValues");
private:
	size_t _offset;
	size_t _cnt;
public:
	PUnitFactory_RemoveValues(size_t offset, size_t cnt, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _offset(offset), _cnt(cnt) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_RemoveValues<1, false>) : sizeof(PUnit_RemoveValues<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Break
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool branchDestFlag>
class GURAX_DLLDECLARE PUnit_Break : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitMarked;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Break : public PUnitFactory {
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
		return _pExprSrc? sizeof(PUnit_Break<1, false, false>) : sizeof(PUnit_Break<0, false, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Continue
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Continue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitOfLoop;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Continue : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Continue");
private:
	const PUnit* _pPUnitOfLoop;
public:
	PUnitFactory_Continue(const PUnit* pPUnitOfLoop, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pPUnitOfLoop(pPUnitOfLoop) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Continue<1, false>) : sizeof(PUnit_Continue<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Miscatch
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Miscatch : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Value> _pValue;
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Miscatch : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Miscatch");
private:
	RefPtr<Value> _pValue;
public:
	PUnitFactory_Miscatch(Value* pValue, Expr* pExprSrc) :
		PUnitFactory(pExprSrc), _pValue(pValue) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Miscatch<1, false>) : sizeof(PUnit_Miscatch<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_Return
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_Return : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_Return : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_Return");
public:
	PUnitFactory_Return(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_Return<1, false>) : sizeof(PUnit_Return<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PushFrame
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, typename T_Frame>
class GURAX_DLLDECLARE PUnit_PushFrame : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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
		return _pExprSrc? sizeof(PUnit_PushFrame<1, false, T_Frame>) : sizeof(PUnit_PushFrame<0, false, T_Frame>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PushFrameFromStack
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_PushFrameFromStack : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_PushFrameFromStack : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PushFrameFromStack");
public:
	PUnitFactory_PushFrameFromStack(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_PushFrameFromStack<1, false>) : sizeof(PUnit_PushFrameFromStack<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_PopFrame
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_PopFrame : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_PopFrame : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_PopFrame");
public:
	PUnitFactory_PopFrame(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_PopFrame<1, false>) : sizeof(PUnit_PopFrame<0, false>);
	}
	virtual PUnit* Create(bool discardValueFlag) override;
};

//------------------------------------------------------------------------------
// PUnit_NoOperation
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
class GURAX_DLLDECLARE PUnit_NoOperation : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	Expr* _ppExprSrc[nExprSrc];
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

class PUnitFactory_NoOperation : public PUnitFactory {
public:
	Gurax_MemoryPoolAllocator("PUnitFactory_NoOperation");
public:
	PUnitFactory_NoOperation(Expr* pExprSrc) : PUnitFactory(pExprSrc) {}
	virtual size_t GetPUnitSize() const override {
		return _pExprSrc? sizeof(PUnit_NoOperation<1, false>) : sizeof(PUnit_NoOperation<0, false>);
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

class PUnitFactory_Terminate : public PUnitFactory {
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
