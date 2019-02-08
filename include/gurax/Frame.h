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
	bool IsSource() const { return _type == Type::Source; }
	bool IsBranch() const { return _type == Type::Branch; }
	Frame* Expand() const;
	static Frame* Shrink(Frame* pFrame);
	Frame* SeekTarget(const DottedSymbol& dottedSymbol, size_t nTail = 0);
	bool AssignObject(const DottedSymbol& dottedSymbol, Object* pObject);
	Object* LookupObject(const DottedSymbol& dottedSymbol) const;
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) = 0;
	virtual Object* LookupObject(const Symbol* pSymbol) const = 0;
	void AssignKlass(Klass& klass);
	void AssignFunction(Function* pFunction);
	bool AssignModule(Module* pModule);
};

}

#endif
