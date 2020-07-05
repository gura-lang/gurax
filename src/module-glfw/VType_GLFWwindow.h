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
		Value_Object(vtype), _pGLFWwindow(pGLFWwindow) {
		glfwSetWindowUserPointer(pGLFWwindow, this);
	}
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
	static GLFWwindow* ValueForVector(const Value& value) { return GetEntity(const_cast<Value&>(value)); }
public:
	static Value_GLFWwindow* GetValue(GLFWwindow* pGLFWwindow) {
		return reinterpret_cast<Value_GLFWwindow*>(glfwGetWindowUserPointer(pGLFWwindow));
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
public:
	// Callback Function
	static void callback_errorfun(int error_code, const char* description);
	static void callback_windowposfun(GLFWwindow* window, int xpos, int ypos);
	static void callback_windowsizefun(GLFWwindow* window, int width, int height);
	static void callback_windowclosefun(GLFWwindow* window);
	static void callback_windowrefreshfun(GLFWwindow* window);
	static void callback_windowfocusfun(GLFWwindow* window, int focused);
	static void callback_windowiconifyfun(GLFWwindow* window, int iconified);
	static void callback_windowmaximizefun(GLFWwindow* window, int maximized);
	static void callback_framebuffersizefun(GLFWwindow* window, int width, int height);
	static void callback_windowcontentscalefun(GLFWwindow* window, float xscale, float yscale);
	static void callback_mousebuttonfun(GLFWwindow* window, int button, int action, int mods);
	static void callback_cursorposfun(GLFWwindow* window, double xpos, double ypos);
	static void callback_cursorenterfun(GLFWwindow* window, int entered);
	static void callback_scrollfun(GLFWwindow* window, double xoffset, double yoffset);
	static void callback_keyfun(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void callback_charfun(GLFWwindow* window, unsigned int codepoint);
	static void callback_charmodsfun(GLFWwindow* window, unsigned int codepoint, int mods);
	static void callback_dropfun(GLFWwindow* window, int path_count, const char* paths[]);
	static void callback_monitorfun(GLFWmonitor* monitor, int event);
	static void callback_joystickfun(int jid, int event);
};

Gurax_EndModuleScope(glfw)

#endif
