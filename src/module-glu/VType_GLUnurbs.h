//==============================================================================
// VType_GLUnurbs.h
//==============================================================================
#ifndef GURAX_MODULE_GLU_VTYPE_GLUNURBS_H
#define GURAX_MODULE_GLU_VTYPE_GLUNURBS_H
#include <gurax.h>
#include <GL/GLU.h>

Gurax_BeginModuleScope(glu)

//------------------------------------------------------------------------------
// VType_GLUnurbs
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLUnurbs : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLUnurbs VTYPE_GLUnurbs;

//------------------------------------------------------------------------------
// Value_GLUnurbs
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLUnurbs : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLUnurbs);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLUnurbs");
protected:
	GLUnurbs* _pGLUnurbs;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLUnurbs() = delete;
	explicit Value_GLUnurbs(GLUnurbs* pGLUnurbs, VType& vtype = VTYPE_GLUnurbs) :
		Value_Object(vtype), _pGLUnurbs(pGLUnurbs) {}
	// Copy constructor/operator
	Value_GLUnurbs(const Value_GLUnurbs& src) :
		Value_Object(src), _pGLUnurbs(src._pGLUnurbs) {}
	Value_GLUnurbs& operator=(const Value_GLUnurbs& src) = delete;
	// Move constructor/operator
	Value_GLUnurbs(Value_GLUnurbs&& src) noexcept = delete;
	Value_GLUnurbs& operator=(Value_GLUnurbs&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLUnurbs() = default;
public:
	GLUnurbs* GetEntityPtr() { return _pGLUnurbs; }
	const GLUnurbs* GetEntityPtr() const { return _pGLUnurbs; }
public:
	static GLUnurbs* GetEntityPtr(Value& value) { return dynamic_cast<Value_GLUnurbs&>(value).GetEntityPtr(); }
	static const GLUnurbs* GetEntityPtr(const Value& value) { return dynamic_cast<const Value_GLUnurbs&>(value).GetEntityPtr(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override { return false; }
	virtual bool IsLessThan(const Value& value) const override { return false; }
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glu)

#endif
