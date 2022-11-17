//==============================================================================
// VType_GLFWgammaramp.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_VTYPE_GLFWGAMMARAMP_H
#define GURAX_MODULE_GLFW_VTYPE_GLFWGAMMARAMP_H
#include <gurax.h>
#include <GLFW/glfw3.h>

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// VType_GLFWgammaramp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLFWgammaramp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLFWgammaramp VTYPE_GLFWgammaramp;

//------------------------------------------------------------------------------
// Value_GLFWgammaramp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLFWgammaramp : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLFWgammaramp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLFWgammaramp");
protected:
	const GLFWgammaramp* _pGLFWgammaramp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWgammaramp() = delete;
	explicit Value_GLFWgammaramp(const GLFWgammaramp* pGLFWgammaramp, VType& vtype = VTYPE_GLFWgammaramp) :
		Value_Object(vtype), _pGLFWgammaramp(pGLFWgammaramp) {}
	// Copy constructor/operator
	Value_GLFWgammaramp(const Value_GLFWgammaramp& src) = delete;
	Value_GLFWgammaramp& operator=(const Value_GLFWgammaramp& src) = delete;
	// Move constructor/operator
	Value_GLFWgammaramp(Value_GLFWgammaramp&& src) noexcept = delete;
	Value_GLFWgammaramp& operator=(Value_GLFWgammaramp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLFWgammaramp() = default;
public:
	const GLFWgammaramp* GetEntity() const { return _pGLFWgammaramp; }
public:
	static const GLFWgammaramp* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWgammaramp&>(value).GetEntity();
	}
	static GLFWgammaramp ValueForVector(Value& value) { return *GetEntity(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity() == Value_GLFWgammaramp::GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntity() < Value_GLFWgammaramp::GetEntity(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif
