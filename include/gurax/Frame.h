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
	const Frame* GetFrameOuter() const { return _pFrameOuter.get(); }
	Value* GetValue(const DottedSymbol& dottedSymbol, size_t nTail = 0);
	Value* GetValue(const Symbol* pSymbol);
	Value* GetValue(const char* name) { return GetValue(Symbol::Add(name)); }
	Value* GetValueLocal(const Symbol* pSymbol);
	Value* GetValueLocal(const char* name) { return GetValueLocal(Symbol::Add(name)); }
	bool IsAssigned(const DottedSymbol& dottedSymbol, size_t nTail = 0) {
		RefPtr<Value> pValue(GetValue(dottedSymbol, nTail)); return !!pValue;
	}
	bool IsAssigned(const Symbol* pSymbol) {
		RefPtr<Value> pValue(GetValue(pSymbol)); return !!pValue;
	}
	bool IsAssignedLocal(const Symbol* pSymbol) {
		RefPtr<Value> pValue(GetValueLocal(pSymbol)); return !!pValue;
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
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) = 0;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) = 0;
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const = 0;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const = 0;
	virtual bool ExportTo(Frame& frameDst, bool overwriteFlag) const { return true; }
	virtual const DottedSymbol& GetDottedSymbol() const { return DottedSymbol::Empty; }
	virtual void GatherSymbol(SymbolList& symbolList) const {}
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
class GURAX_DLLDECLARE FrameList : public std::vector<Frame*> {
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
	ValueMap* _pValueMap;	// RefPtr can not be used here because Value.h hasn't included yet.
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
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual bool ExportTo(Frame& frameDst, bool overwriteFlag) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	const Frame* GetFrameLocal() const { return _pFrameLocal.get(); }
	virtual bool ExportTo(Frame& frameDst, bool overwriteFlag) const override {
		return GetFrameLocal()? GetFrameLocal()->ExportTo(frameDst, overwriteFlag) : true;
	}
	Value* GetValueLocal(const Symbol* pSymbol) {
		return _pFrameLocal? _pFrameLocal->GetValue(pSymbol) : nullptr;
	}
	Value* GetValueLocal(const char* name) { return GetValueLocal(Symbol::Add(name)); }
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
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
};

//------------------------------------------------------------------------------
// Frame_VType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_VType : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_VType);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_VType");
public:
	static const char* name;
public:
	// Constructor
	explicit Frame_VType(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual const DottedSymbol& GetDottedSymbol() const override { return *_pDottedSymbol; }
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	explicit Frame_Scope(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
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
	virtual void DoAssign(const Symbol* pSymbol, Value* pValue) override;
	virtual void DoAssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* DoGetValue(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual Value* DoGetValueLocal(const Symbol* pSymbol, const Frame** ppFrameSrc) const override;
	virtual void GatherSymbol(SymbolList& symbolList) const override;
};

}

#endif
