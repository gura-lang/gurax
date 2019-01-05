//==============================================================================
// Frame.h
//==============================================================================
#ifndef GURAX_FRAME_H
#define GURAX_FRAME_H
#include "Object.h"
#include "MemoryPool.h"

namespace Gurax {

class Frame;

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame);
public:
	enum class Type { Node, Branch };
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
	bool IsNode() const { return _type == Type::Node; }
	bool IsBranch() const { return _type == Type::Branch; }
	Frame* Expand() const;
	static Frame* Shrink(Frame* pFrame);
	virtual void AssignKlass(const Symbol* pSymbol, Klass* pKlasss) = 0;
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) = 0;
	virtual Klass* LookupKlass(const Symbol* pSymbol) const = 0;
	virtual Object* LookupObject(const Symbol* pSymbol) const = 0;
};

//------------------------------------------------------------------------------
// Frame_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Node : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Node);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Node");
protected:
	RefPtr<KlassMap> _pKlassMap;
	RefPtr<ObjectMap> _pObjectMap;
public:
	// Constructor
	Frame_Node() : Frame(Type::Node), _pObjectMap(new ObjectMap()) {}
public:
	virtual void AssignKlass(const Symbol* pSymbol, Klass* pKlass) override {
		if (!_pKlassMap) _pKlassMap.reset(new KlassMap());
		_pKlassMap->Assign(pSymbol, pKlass);
	}
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override {
		_pObjectMap->Assign(pSymbol, pObject);
	}
	virtual Klass* LookupKlass(const Symbol* pSymbol) const override {
		return _pKlassMap? _pKlassMap->Lookup(pSymbol) : nullptr;
	}
	virtual Object* LookupObject(const Symbol* pSymbol) const override {
		return _pObjectMap->Lookup(pSymbol);
	}
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
	Frame_Branch(Frame* pFrameLeft, Frame* pFrameRight) : Frame(Type::Branch),
		_pFrameLeft(pFrameLeft), _pFrameRight(pFrameRight) {}
public:
	const Frame* GetLeft() const { return _pFrameLeft.get(); }
	const Frame* GetRight() const { return _pFrameRight.get(); }
public:
	virtual void AssignKlass(const Symbol* pSymbol, Klass* pKlass) override {
		_pFrameRight->AssignKlass(pSymbol, pKlass);
	}
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override {
		_pFrameRight->AssignObject(pSymbol, pObject);
	}
	virtual Klass* LookupKlass(const Symbol* pSymbol) const override {
		if (Klass* pKlass = _pFrameRight->LookupKlass(pSymbol)) return pKlass;
		return _pFrameLeft->LookupKlass(pSymbol);
	}
	virtual Object* LookupObject(const Symbol* pSymbol) const override {
		if (Object* pObject = _pFrameRight->LookupObject(pSymbol)) return pObject;
		return _pFrameLeft->LookupObject(pSymbol);
	}
};

}

#endif
