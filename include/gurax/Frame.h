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
	Frame* Expand() const;
	virtual void AssignKlass(const Symbol* pSymbol, Klass* pKlasss) = 0;
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) = 0;
	virtual Klass* LookupKlass(const Symbol* pSymbol) const = 0;
	virtual Object* LookupObject(const Symbol* pSymbol) const = 0;
};

//------------------------------------------------------------------------------
// Frame_Item
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Item : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Item);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Item");
protected:
	RefPtr<KlassMap> _pKlassMap;
	RefPtr<ObjectMap> _pObjectMap;
public:
	// Constructor
	Frame_Item() : _pObjectMap(new ObjectMap()) {}
public:
	virtual void AssignKlass(const Symbol* pSymbol, Klass* pKlass) override {
		if (!_pKlassMap) _pKlassMap.reset(new KlassMap());
		_pKlassMap->Set(pSymbol, pKlass);
	}
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override {
		_pObjectMap->Set(pSymbol, pObject);
	}
	virtual Klass* LookupKlass(const Symbol* pSymbol) const override {
		return _pKlassMap? _pKlassMap->Get(pSymbol) : nullptr;
	}
	virtual Object* LookupObject(const Symbol* pSymbol) const override {
		return _pObjectMap->Get(pSymbol);
	}
};

//------------------------------------------------------------------------------
// Frame_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Binary : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Binary);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Binary");
protected:
	RefPtr<Frame> _pFrameLeft;
	RefPtr<Frame> _pFrameRight;
public:
	// Constructor
	Frame_Binary(Frame* pFrameLeft, Frame* pFrameRight) : _pFrameLeft(pFrameLeft), _pFrameRight(pFrameRight) {}
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
