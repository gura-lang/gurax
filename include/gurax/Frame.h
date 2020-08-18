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
class VType;
class Value;
class ValueMap;

//------------------------------------------------------------------------------
// FrameMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FrameMap :
	public std::unordered_map<const Symbol*, Frame*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(FrameMap);
protected:
	~FrameMap() { Clear(); }
public:
	void Clear();
	void Assign(const Symbol* pSymbol, Frame* pFrame);
	Frame* Lookup(const Symbol* pSymbol) {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
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
	void AssignFromArgument(const Symbol* pSymbol, Value* pValue) { DoAssignFromArgument(pSymbol, pValue); }
	bool Assign(const DottedSymbol& dottedSymbol, Value* pValue);
	void Assign(const char* name, Value* pValue) { Assign(Symbol::Add(name), pValue); }
	bool AssignWithCast(DeclArg& declArg, const Value& value);
	bool Assign(Module* pModule);
	void Assign(VType& vtype);
	void Assign(Function* pFunction);
	static String MakeFullName(const Frame* pFrame, const char* name);
public:
	// Virtual functions
	virtual bool IsFrameOfBasement() const { return false; }
	virtual bool IsFrameOfVType() const { return false; }
	virtual bool IsFrameOfModule() const { return false; }
	virtual bool IsFrameOfScope() const { return false; }
	virtual bool IsFrameOfBlock() const { return false; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) = 0;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) = 0;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) = 0;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) = 0;
	virtual bool ExportTo(Frame& frameDst, bool overwriteFlag) const { return true; }
	virtual const DottedSymbol& GetDottedSymbol() const { return DottedSymbol::Empty; }
	virtual void GatherSymbol(SymbolList& symbolList) const {}
	virtual const char* GetTypeName() const = 0;
	virtual void PrintTree(int indentLevel) const {
		::printf("%*s%s(%p)\n", indentLevel * 2, "", GetTypeName(), this);
		if (_pFrameOuter) _pFrameOuter->PrintTree(indentLevel + 1);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Frame& frame) const { return this == &frame; }
	bool IsEqualTo(const Frame& frame) const { return IsIdentical(frame); }
	bool IsLessThan(const Frame& frame) const { return this < &frame; }
	//String ToString() const { return ToString(StringStyle::Empty); }
};

//------------------------------------------------------------------------------
// FrameList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FrameList : public ListBase<Frame*> {
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
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual bool ExportTo(Frame& frameDst, bool overwriteFlag) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	virtual bool ExportTo(Frame& frameDst, bool overwriteFlag) const override {
		return GetFrameLocal()? GetFrameLocal()->ExportTo(frameDst, overwriteFlag) : true;
	}
	Value* RetrieveLocal(const Symbol* pSymbol) {
		return _pFrameLocal? _pFrameLocal->Retrieve(pSymbol) : nullptr;
	}
	Value* RetrieveLocal(const char* name) { return RetrieveLocal(Symbol::Add(name)); }
	virtual void PrintTree(int indentLevel) const override {
		::printf("%*s%s(%p)\n", indentLevel * 2, "", GetTypeName(), this);
		if (_pFrameOuter) _pFrameOuter->PrintTree(indentLevel + 1);
		if (_pFrameLocal) _pFrameLocal->PrintTree(indentLevel + 1);
	}
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
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual const char* GetTypeName() const override { return name; }
};

//------------------------------------------------------------------------------
// Frame_OfMember
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_OfMember : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_OfMember);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_OfMember");
public:
	static const char* name;
public:
	// Constructor
	explicit Frame_OfMember(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual bool IsFrameOfVType() const override { return true; }
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual const DottedSymbol& GetDottedSymbol() const override { return *_pDottedSymbol; }
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoRetrieve(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual Value* DoRetrieveLocal(const Symbol* pSymbol, Frame** ppFrameSrc) override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
	virtual const char* GetTypeName() const override { return name; }
};

}

#endif
