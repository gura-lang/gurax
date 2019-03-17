//==============================================================================
// Frame.h
//==============================================================================
#ifndef GURAX_FRAME_H
#define GURAX_FRAME_H
#include "MemoryPool.h"

namespace Gurax {

class Function;
class VType;
class Value;
class ValueMap;
class Module;

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame);
protected:
	RefPtr<Frame> _pFrameOuter;
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
	Value* Lookup(const DottedSymbol& dottedSymbol, size_t nTail = 0) const;
	bool Assign(const DottedSymbol& dottedSymbol, Value* pValue);
	void Assign(const char* name, Value* pValue) { Assign(Symbol::Add(name), pValue); }
	bool Assign(Module* pModule);
	void Assign(VType& vtype);
	void Assign(Function* pFunction);
	Value* Lookup(const char* name) { return Lookup(Symbol::Add(name)); }
public:
	// Virtual functions
	virtual void Assign(const Symbol* pSymbol, Value* pValue) = 0;
	virtual void AssignFromArgument(const Symbol* pSymbol, Value* pValue) = 0;
	virtual Value* Lookup(const Symbol* pSymbol) const = 0;
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
	void Pop() { pop_back(); }
};

//------------------------------------------------------------------------------
// Frame_ValueMap
//------------------------------------------------------------------------------
class Frame_ValueMap : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_ValueMap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_ValueMap");
protected:
	ValueMap* _pValueMap;	// RefPtr can not be used here because Value.h hasn't included yet.
public:
	// Constructor
	Frame_ValueMap();
protected:
	// Destructor
	virtual ~Frame_ValueMap() override;
public:
	// Virtual functions of Frame
	virtual void Assign(const Symbol* pSymbol, Value* pValue) override;
	virtual void AssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* Lookup(const Symbol* pSymbol) const override;
};

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Branch : public Frame {
protected:
	RefPtr<Frame> _pFrameLocal;
public:
	// Constructor
	Frame_Branch(Frame* pFrameOuter, Frame* pFrameLocal) :
		Frame(pFrameOuter), _pFrameLocal(pFrameLocal) {}
public:
	void SetFrameLocal(Frame* pFrame) { _pFrameLocal.reset(pFrame); }
	const Frame* GetFrameLocal() const { return _pFrameLocal.get(); }
};

//------------------------------------------------------------------------------
// Frame_Root
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Root : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Root);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Root");
public:
	// Constructor
	Frame_Root();
public:
	// Virtual functions of Frame
	virtual void Assign(const Symbol* pSymbol, Value* pValue) override;
	virtual void AssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* Lookup(const Symbol* pSymbol) const override;
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
	// Constructor
	explicit Frame_VType(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual void Assign(const Symbol* pSymbol, Value* pValue) override;
	virtual void AssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* Lookup(const Symbol* pSymbol) const override;
};

//------------------------------------------------------------------------------
// Frame_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Function : public Frame_Branch {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Function");
public:
	// Constructor
	explicit Frame_Function(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual void Assign(const Symbol* pSymbol, Value* pValue) override;
	virtual void AssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* Lookup(const Symbol* pSymbol) const override;
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
	// Constructor
	explicit Frame_Block(Frame* pFrameOuter);
public:
	// Virtual functions of Frame
	virtual void Assign(const Symbol* pSymbol, Value* pValue) override;
	virtual void AssignFromArgument(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* Lookup(const Symbol* pSymbol) const override;
};

}

#endif
