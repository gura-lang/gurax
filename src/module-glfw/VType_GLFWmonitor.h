//==============================================================================
// VType_GLFWmonitor.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_VTYPE_GLFWMONITOR_H
#define GURAX_MODULE_GLFW_VTYPE_GLFWMONITOR_H
#include <gurax.h>
#include <GLFW/glfw3.h>

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// VType_GLFWmonitor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLFWmonitor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLFWmonitor VTYPE_GLFWmonitor;

//------------------------------------------------------------------------------
// Value_GLFWmonitor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLFWmonitor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLFWmonitor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLFWmonitor");
protected:
	GLFWmonitor* _pGLFWmonitor;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWmonitor() = delete;
	explicit Value_GLFWmonitor(GLFWmonitor* pGLFWmonitor, VType& vtype = VTYPE_GLFWmonitor) :
		Value_Object(vtype), _pGLFWmonitor(pGLFWmonitor) {
		glfwSetMonitorUserPointer(pGLFWmonitor, this);
	}
	// Copy constructor/operator
	Value_GLFWmonitor(const Value_GLFWmonitor& src) = delete;
	Value_GLFWmonitor& operator=(const Value_GLFWmonitor& src) = delete;
	// Move constructor/operator
	Value_GLFWmonitor(Value_GLFWmonitor&& src) noexcept = delete;
	Value_GLFWmonitor& operator=(Value_GLFWmonitor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLFWmonitor() = default;
public:
	GLFWmonitor* GetEntity() { return _pGLFWmonitor; }
	const GLFWmonitor* GetEntity() const { return _pGLFWmonitor; }
public:
	static GLFWmonitor* GetEntity(Value& value) {
		return dynamic_cast<Value_GLFWmonitor&>(value).GetEntity();
	}
	static const GLFWmonitor* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWmonitor&>(value).GetEntity();
	}
	static GLFWmonitor* ValueForVector(Value& value) { return GetEntity(value); }
public:
	static Value_GLFWmonitor& GetValue(GLFWmonitor* pGLFWmonitor) {
		return *reinterpret_cast<Value_GLFWmonitor*>(glfwGetMonitorUserPointer(pGLFWmonitor));
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity() == Value_GLFWmonitor::GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntity() < Value_GLFWmonitor::GetEntity(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif
