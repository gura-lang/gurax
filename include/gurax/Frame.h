//==============================================================================
// Frame.h
//==============================================================================
#ifndef GURAX_FRAME_H
#define GURAX_FRAME_H
#include "MemoryPool.h"

namespace Gurax {

class Function;
class Klass;
class Object;
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
	bool AssignObject(const DottedSymbol& dottedSymbol, Object* pObject);
	Object* LookupObject(const DottedSymbol& dottedSymbol) const;
	bool AssignModule(Module* pModule);
	void AssignKlass(Klass& klass);
	void AssignFunction(Function* pFunction);
public:
	// Virtual functions
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) = 0;
	virtual Object* LookupObject(const Symbol* pSymbol) const = 0;
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
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override;
	virtual Object* LookupObject(const Symbol* pSymbol) const override;
};

}

#endif
