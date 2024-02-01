//==============================================================================
// Frame.h
//==============================================================================
#ifndef GURAX_FRAME_H
#define GURAX_FRAME_H
#include "MemoryPool.h"

namespace Gurax {

class DeclArg;
class Frame;
class Function;
class Module;
class Processor;
class PropSlotMap;
class Stream;
class StringStyle;
class VType;
class Value;
class ValueMap;

//------------------------------------------------------------------------------
// FrameMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FrameMap : public Referable {
public:
	using Map = std::unordered_map<const Symbol*, Frame*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	Map _map;
public:
	// Referable declaration
	Gurax_DeclareReferable(FrameMap);
protected:
	~FrameMap() { Clear(); }
public:
	Map& GetMap() { return _map; }
	const Map& GetMap() const { return _map; }
	void Clear();
	void Assign(const Symbol* pSymbol, Frame* pFrame);
	Frame* Lookup(const Symbol* pSymbol) {
		auto pPair = _map.find(pSymbol);
		return (pPair == _map.end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return _map.find(pSymbol) != _map.end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	//String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame);
public:
	class GURAX_DLLDECLARE GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const = 0;
	};
protected:
	RefPtr<Frame> _pFrameOuter;
	RefPtr<FrameMap> _pFrameMap;
public:
	// Constructor
	explicit Frame(Frame* pFrameOuter) : _pFrameOuter(pFrameOuter) {}
	// Copy constructor/operator
	Frame(const Frame& src) = delete;
	Frame& operator=(const Frame& src) = delete;
	// Move constructor/operator
	Frame(Frame&& src) = delete;
	Frame& operator=(Frame&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Frame() = default;
public:
	void SetFrameOuter(Frame* pFrame) { _pFrameOuter.reset(pFrame); }
	Frame* GetFrameOuter() { return _pFrameOuter.get(); }
	const Frame* GetFrameOuter() const { return _pFrameOuter.get(); }
	Frame* GetFrameExtern(const Symbol* pSymbol);
	const Frame* GetFrameExtern(const Symbol* pSymbol) const {
		return const_cast<Frame*>(this)->GetFrameExtern(pSymbol);
	}
	size_t GetId() const { return reinterpret_cast<size_t>(this); }
	String MakeId() const;
	Value* Retrieve(const DottedSymbol& dottedSymbol, size_t nTail = 0);
	Value* Retrieve(const Symbol* pSymbol);
	Value* Retrieve(const char* name) { return Retrieve(Symbol::Add(name)); }
	Value* RetrieveLocal(const Symbol* pSymbol);
	Value* RetrieveLocal(const char* name) { return RetrieveLocal(Symbol::Add(name)); }
	bool IsAssigned(const DottedSymbol& dottedSymbol, size_t nTail = 0) {
		RefPtr<Value> pValue(Retrieve(dottedSymbol, nTail)); return !!pValue;
	}
	bool IsAssigned(const Symbol* pSymbol) {
		RefPtr<Value> pValue(Retrieve(pSymbol)); return !!pValue;
	}
	bool IsAssignedLocal(const Symbol* pSymbol) {
		RefPtr<Value> pValue(RetrieveLocal(pSymbol)); return !!pValue;
	}
	void Assign(const Symbol* pSymbol, Value* pValue);
	void AssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) { DoAssignFromArgument(processor, pSymbol, pValue); }
	bool Assign(Processor& processor, const DottedSymbol& dottedSymbol, Value* pValue);
	void Assign(const char* name, Value* pValue) { Assign(Symbol::Add(name), pValue); }
	bool AssignWithCast(Processor& processor, DeclArg& declArg, const Value& value);
	bool Assign(Processor& processor, Module* pModule);
	void Assign(VType& vtype);
	void Assign(Function* pFunction);
	static String MakeFullName(const Frame* pFrame, const char* name);
public:
	// Virtual functions
	virtual Frame* DoGetFrameLocal() { return nullptr; }
	virtual bool IsFrameOfBasement() const { return false; }
	virtual bool IsFrameOfMember() const { return false; }
	virtual bool IsFrameOfModule() const { return false; }
	virtual bool IsFrameOfScope() const { return false; }
	virtual bool IsFrameOfFunction() const { return false; }
	virtual bool IsFrameOfBlock() const { return false; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) = 0;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) = 0;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) = 0;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) = 0;
	virtual bool ExportTo(Processor& processor, Frame& frameDst, bool overwriteFlag) const { return true; }
	virtual const DottedSymbol& GetDottedSymbol() const { return DottedSymbol::Empty; }
	virtual void GatherSymbol(SymbolList& symbolList) const {}
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const {}
	virtual const char* GetTypeName() const = 0;
	virtual void PrintTree(Stream& stream, int indentLevel = 0) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Frame& frame) const { return this == &frame; }
	bool IsEqualTo(const Frame& frame) const { return IsIdentical(frame); }
	bool IsLessThan(const Frame& frame) const { return this < &frame; }
	String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// FrameList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FrameList : public ListBase<Frame*> {
public:
	void Print(Stream& stream) const;
};

//------------------------------------------------------------------------------
// FrameOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FrameOwner : public FrameList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(FrameOwner);
protected:
	~FrameOwner() { Clear(); }
public:
	void Clear();
};

//------------------------------------------------------------------------------
// FrameStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FrameStack : public FrameOwner {
public:
	Frame* GetCur() { return back(); }
	void Push(Frame* pFrame) { push_back(pFrame); }
	void Pop() { Frame::Delete(back()); pop_back(); }
	void Shrink(size_t cnt);
};

//------------------------------------------------------------------------------
// Frame_ValueMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_ValueMap : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_ValueMap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_ValueMap");
protected:
	ValueMap* _pValueMap;	// RefPtr can not be used here because Value.h isn't included yet.
public:
	static const char* name;
public:
	// Constructor
	Frame_ValueMap();
protected:
	// Destructor
	virtual ~Frame_ValueMap() override;
public:
	// Virtual functions of Frame
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual bool ExportTo(Processor& processor, Frame& frameDst, bool overwriteFlag) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const override;
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_OfMember
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_OfMember : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_OfMember);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_OfMember");
protected:
	ValueMap* _pValueMap;		// RefPtr can not be used here because Value.h isn't included yet.
	PropSlotMap* _pPropSlotMap;	// RefPtr can not be used here because PropSlot.h isn't included yet.
public:
	static const char* name;
public:
	// Constructor
	explicit Frame_OfMember(Frame* pFrameOuter);
protected:
	// Destructor
	virtual ~Frame_OfMember() override;
public:
	ValueMap& GetValueMap() { return *_pValueMap; }
	PropSlotMap& GetPropSlotMap() { return *_pPropSlotMap; }
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfMember() const override { return true; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual bool ExportTo(Processor& processor, Frame& frameDst, bool overwriteFlag) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const override;
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Branch : public Frame {
protected:
	RefPtr<Frame> _pFrameLocal;
public:
	static const char* name;
public:
	// Constructor
	Frame_Branch(Frame* pFrameOuter, Frame* pFrameLocal) :
		Frame(pFrameOuter), _pFrameLocal(pFrameLocal) {}
public:
	void SetFrameLocal(Frame* pFrame) { _pFrameLocal.reset(pFrame); }
	Frame* GetFrameLocal() { return _pFrameLocal.get(); }
	const Frame* GetFrameLocal() const { return _pFrameLocal.get(); }
	virtual bool ExportTo(Processor& processor, Frame& frameDst, bool overwriteFlag) const override {
		return GetFrameLocal()? GetFrameLocal()->ExportTo(processor, frameDst, overwriteFlag) : true;
	}
	Value* RetrieveLocal(const Symbol* pSymbol) {
		return _pFrameLocal? _pFrameLocal->Retrieve(pSymbol) : nullptr;
	}
	Value* RetrieveLocal(const char* name) { return RetrieveLocal(Symbol::Add(name)); }
	virtual Frame* DoGetFrameLocal() override { return GetFrameLocal(); }
	virtual void PrintTree(Stream& stream, int indentLevel) const override;
};

//------------------------------------------------------------------------------
// Frame_Basement
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Basement : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Basement);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Basement");
public:
	static const char* name;
public:
	// Constructor
	Frame_Basement();
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfBasement() const override { return true; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const override;
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_Module
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Module : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Module);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Module");
private:
	RefPtr<DottedSymbol> _pDottedSymbol;
public:
	static const char* name;
public:
	// Constructor
	Frame_Module(Frame* pFrameOuter, DottedSymbol* pDottedSymbol);
public:
	void SetDottedSymbol(DottedSymbol* pDottedSymbol) { _pDottedSymbol.reset(pDottedSymbol); }
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfModule() const override { return true; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual const DottedSymbol& GetDottedSymbol() const override { return *_pDottedSymbol; }
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const override;
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_Scope
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Scope : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Scope);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Scope");
public:
	static const char* name;
public:
	// Constructor
	explicit Frame_Scope(Frame* pFrameOuter, Frame* pFrameLocal = nullptr);
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfScope() const override { return true; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const override;
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Function : public Frame_Scope {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Function");
public:
	static const char* name;
public:
	// Constructor
	explicit Frame_Function(Frame* pFrameOuter, Frame* pFrameLocal = nullptr);
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfFunction() const override { return true; }
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_Block
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Block : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Block);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Block");
public:
	static const char* name;
public:
	// Constructor
	explicit Frame_Block(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfBlock() const override { return true; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(Processor& processor, const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual void GatherSymbolIf(SymbolList& symbolList, const GatherCriteria& gatherCriteria) const override;
	virtual const char* GetTypeName() const override { return name; }
};

}

#endif
