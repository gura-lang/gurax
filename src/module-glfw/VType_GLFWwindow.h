//==============================================================================
// VType_GLFWwindow.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_VTYPE_GLFWWINDOW_H
#define GURAX_MODULE_GLFW_VTYPE_GLFWWINDOW_H
#include <gurax.h>
#include <GLFW/glfw3.h>

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// VType_GLFWwindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLFWwindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLFWwindow VTYPE_GLFWwindow;

//------------------------------------------------------------------------------
// Value_GLFWwindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLFWwindow : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLFWwindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLFWwindow");
protected:
	GLFWwindow* _pGLFWwindow;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWwindow() = delete;
	explicit Value_GLFWwindow(GLFWwindow* pGLFWwindow, VType& vtype = VTYPE_GLFWwindow) :
		Value_Object(vtype), _pGLFWwindow(pGLFWwindow) {}
	// Copy constructor/operator
	Value_GLFWwindow(const Value_GLFWwindow& src) = delete;
	Value_GLFWwindow& operator=(const Value_GLFWwindow& src) = delete;
	// Move constructor/operator
	Value_GLFWwindow(Value_GLFWwindow&& src) noexcept = delete;
	Value_GLFWwindow& operator=(Value_GLFWwindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLFWwindow() = default;
public:
	GLFWwindow* GetEntity() { return _pGLFWwindow; }
	const GLFWwindow* GetEntity() const { return _pGLFWwindow; }
public:
	static GLFWwindow* GetEntity(Value& value) {
		return dynamic_cast<Value_GLFWwindow&>(value).GetEntity();
	}
	static const GLFWwindow* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWwindow&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetEntity() == Value_GLFWwindow::GetEntity(*pValue);
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetEntity() < Value_GLFWwindow::GetEntity(*pValue) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif