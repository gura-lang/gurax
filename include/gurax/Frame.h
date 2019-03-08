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
class Frame_Branch;

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame);
public:
	// Constructor
	Frame() {}
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
	Value* LookupValue(const DottedSymbol& dottedSymbol, size_t nTail = 0) const;
	bool AssignValue(const DottedSymbol& dottedSymbol, Value* pValue);
	bool AssignModule(Module* pModule);
	void AssignVType(VType& vtype);
	void AssignFunction(Function* pFunction);
	void AssignValue(const char* name, Value* pValue) { AssignValue(Symbol::Add(name), pValue); }
	Value* LookupValue(const char* name) { return LookupValue(Symbol::Add(name)); }
public:
	// Virtual functions
	virtual void AssignValue(const Symbol* pSymbol, Value* pValue) = 0;
	virtual Value* LookupValue(const Symbol* pSymbol) const = 0;
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
	virtual void AssignValue(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* LookupValue(const Symbol* pSymbol) const override;
};

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Branch : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Branch);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Branch");
protected:
	RefPtr<Frame> _pFrameOuter;
	RefPtr<Frame> _pFrameLocal;
public:
	// Constructor
	Frame_Branch(Frame* pFrameOuter, Frame* pFrameLocal) :
		_pFrameOuter(pFrameOuter), _pFrameLocal(pFrameLocal) {}
public:
	void SetFrameOuter(Frame* pFrame) { _pFrameOuter.reset(pFrame); }
	void SetFrameLocal(Frame* pFrame) { _pFrameLocal.reset(pFrame); }
	const Frame* GetFrameOuter() const { return _pFrameOuter.get(); }
	const Frame* GetFrameLocal() const { return _pFrameLocal.get(); }
public:
	// Virtual functions of Frame
	virtual void AssignValue(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* LookupValue(const Symbol* pSymbol) const override;
};

}

#endif
