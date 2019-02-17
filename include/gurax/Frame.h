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
class Property;
class Frame_Branch;

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame);
public:
	enum class Type { Source, Branch };
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
	static Frame* CreateSource();
	static Frame_Branch* CreateBranch(Frame* pFrameLeft, Frame* pFrameRight);
	bool IsSource() const { return _type == Type::Source; }
	bool IsBranch() const { return _type == Type::Branch; }
	Frame* Expand() const;
	static Frame* Shrink(Frame* pFrame);
	Frame* SeekTarget(const DottedSymbol& dottedSymbol, size_t nTail = 0);
	bool AssignValue(const DottedSymbol& dottedSymbol, Value* pValue);
	Value* LookupValue(const DottedSymbol& dottedSymbol) const;
	bool AssignModule(Module* pModule);
	void AssignVType(VType& vtype);
	void AssignFunction(Function* pFunction);
public:
	// Virtual functions
	virtual void AssignValue(const Symbol* pSymbol, Value* pValue) = 0;
	virtual void AssignProperty(const Symbol* pSymbol, Property* pProperty) = 0;
	virtual Value* LookupValue(const Symbol* pSymbol) const = 0;
	virtual Property* LookupProperty(const Symbol* pSymbol) const = 0;
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
	virtual void AssignProperty(const Symbol* pSymbol, Property* pProperty) override;
	virtual Value* LookupValue(const Symbol* pSymbol) const override;
	virtual Property* LookupProperty(const Symbol* pSymbol) const override;
};

}

#endif
