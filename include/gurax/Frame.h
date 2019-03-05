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
	enum class Type { Branch, ValueMap };
private:
	Type _type;
public:
	// Constructor
	explicit Frame(Type type) : _type(type) {}
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
	static Frame_Branch* CreateOfBranch(Frame* pFrameLeft, Frame* pFrameRight);
	static Frame* CreateOfValueMap();
	bool IsBranch() const { return _type == Type::Branch; }
	bool IsValueMap() const { return _type == Type::ValueMap; }
	Frame* Expand() const;
	static Frame* Shrink(Frame* pFrame);
	//Value* SeekTarget(const DottedSymbol& dottedSymbol, size_t nTail = 0);
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
// Frame_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Branch : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Branch);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Branch");
protected:
	RefPtr<Frame> _pFrameLeft;
	RefPtr<Frame> _pFrameRight;
public:
	// Constructor
	Frame_Branch(Frame* pFrameLeft, Frame* pFrameRight) :
		Frame(Type::Branch), _pFrameLeft(pFrameLeft), _pFrameRight(pFrameRight) {}
public:
	void SetLeft(Frame* pFrame) { _pFrameLeft.reset(pFrame); }
	void SetRight(Frame* pFrame) { _pFrameRight.reset(pFrame); }
	const Frame* GetLeft() const { return _pFrameLeft.get(); }
	const Frame* GetRight() const { return _pFrameRight.get(); }
public:
	// Virtual functions of Frame
	virtual void AssignValue(const Symbol* pSymbol, Value* pValue) override;
	virtual Value* LookupValue(const Symbol* pSymbol) const override;
};

}

#endif
