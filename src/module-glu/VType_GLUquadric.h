//==============================================================================
// VType_GLUquadric.h
//==============================================================================
#ifndef GURAX_MODULE_GLU_VTYPE_GLUQUADRIC_H
#define GURAX_MODULE_GLU_VTYPE_GLUQUADRIC_H
#include <gurax.h>
#include <GL/GLU.h>

Gurax_BeginModuleScope(glu)

//------------------------------------------------------------------------------
// VType_GLUquadric
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLUquadric : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLUquadric VTYPE_GLUquadric;

//------------------------------------------------------------------------------
// Value_GLUquadric
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLUquadric : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLUquadric);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLUquadric");
protected:
	GLUquadric* _pGLUquadric;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLUquadric() = delete;
	explicit Value_GLUquadric(GLUquadric* pGLUquadric, VType& vtype = VTYPE_GLUquadric) :
		Value_Object(vtype), _pGLUquadric(pGLUquadric) {}
	// Copy constructor/operator
	Value_GLUquadric(const Value_GLUquadric& src) :
		Value_Object(src), _pGLUquadric(src._pGLUquadric) {}
	Value_GLUquadric& operator=(const Value_GLUquadric& src) = delete;
	// Move constructor/operator
	Value_GLUquadric(Value_GLUquadric&& src) noexcept = delete;
	Value_GLUquadric& operator=(Value_GLUquadric&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLUquadric() = default;
public:
	GLUquadric* GetEntityPtr() { return _pGLUquadric; }
	const GLUquadric* GetEntityPtr() const { return _pGLUquadric; }
public:
	static GLUquadric* GetEntityPtr(Value& value) { return dynamic_cast<Value_GLUquadric&>(value).GetEntityPtr(); }
	static const GLUquadric* GetEntityPtr(const Value& value) { return dynamic_cast<const Value_GLUquadric&>(value).GetEntityPtr(); }
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
