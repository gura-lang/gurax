//==============================================================================
// VType_GLUtesselator.h
//==============================================================================
#ifndef GURAX_MODULE_GLU_VTYPE_GLUTESSELATOR_H
#define GURAX_MODULE_GLU_VTYPE_GLUTESSELATOR_H
#include <gurax.h>
#include <GL/GLU.h>

Gurax_BeginModuleScope(glu)

//------------------------------------------------------------------------------
// VType_GLUtesselator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLUtesselator : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLUtesselator VTYPE_GLUtesselator;

//------------------------------------------------------------------------------
// Value_GLUtesselator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLUtesselator : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLUtesselator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLUtesselator");
protected:
	GLUtesselator* _pGLUtesselator;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLUtesselator() = delete;
	explicit Value_GLUtesselator(GLUtesselator* pGLUtesselator, VType& vtype = VTYPE_GLUtesselator) :
		Value_Object(vtype), _pGLUtesselator(pGLUtesselator) {}
	// Copy constructor/operator
	Value_GLUtesselator(const Value_GLUtesselator& src) :
		Value_Object(src), _pGLUtesselator(src._pGLUtesselator) {}
	Value_GLUtesselator& operator=(const Value_GLUtesselator& src) = delete;
	// Move constructor/operator
	Value_GLUtesselator(Value_GLUtesselator&& src) noexcept = delete;
	Value_GLUtesselator& operator=(Value_GLUtesselator&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLUtesselator() = default;
public:
	GLUtesselator& GetGLUtesselator() { return *_pGLUtesselator; }
	const GLUtesselator& GetGLUtesselator() const { return *_pGLUtesselator; }
public:
	static GLUtesselator& GetGLUtesselator(Value& value) {
		return dynamic_cast<Value_GLUtesselator&>(value).GetGLUtesselator();
	}
	static const GLUtesselator& GetGLUtesselator(const Value& value) {
		return dynamic_cast<const Value_GLUtesselator&>(value).GetGLUtesselator();
	}
	static GLUtesselator* GetEntityPtr(Value& value) { return &GetGLUtesselator(value); }
	static const GLUtesselator* GetEntityPtr(const Value& value) { return &GetGLUtesselator(value); }
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
