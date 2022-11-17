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
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunc_WindowPosCallback;
	RefPtr<Function> _pFunc_WindowSizeCallback;
	RefPtr<Function> _pFunc_WindowCloseCallback;
	RefPtr<Function> _pFunc_WindowRefreshCallback;
	RefPtr<Function> _pFunc_WindowFocusCallback;
	RefPtr<Function> _pFunc_WindowIconifyCallback;
	RefPtr<Function> _pFunc_WindowMaximizeCallback;
	RefPtr<Function> _pFunc_FramebufferSizeCallback;
	RefPtr<Function> _pFunc_WindowContentScaleCallback;
	RefPtr<Function> _pFunc_MouseButtonCallback;
	RefPtr<Function> _pFunc_CursorPosCallback;
	RefPtr<Function> _pFunc_CursorEnterCallback;
	RefPtr<Function> _pFunc_ScrollCallback;
	RefPtr<Function> _pFunc_KeyCallback;
	RefPtr<Function> _pFunc_CharCallback;
	RefPtr<Function> _pFunc_CharModsCallback;
	RefPtr<Function> _pFunc_DropCallback;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWwindow() = delete;
	explicit Value_GLFWwindow(GLFWwindow* pGLFWwindow, Processor* pProcessor, VType& vtype = VTYPE_GLFWwindow) :
		Value_Object(vtype), _pGLFWwindow(pGLFWwindow), _pProcessor(pProcessor) {
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
	Processor& GetProcessor() { return *_pProcessor; }
public:
	static GLFWwindow* GetEntity(Value& value) {
		return dynamic_cast<Value_GLFWwindow&>(value).GetEntity();
	}
	static const GLFWwindow* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWwindow&>(value).GetEntity();
	}
	static GLFWwindow* ValueForVector(const Value& value) { return GetEntity(const_cast<Value&>(value)); }
public:
	static Value_GLFWwindow& GetValue(GLFWwindow* pGLFWwindow) {
		return *reinterpret_cast<Value_GLFWwindow*>(glfwGetWindowUserPointer(pGLFWwindow));
	}
public:
	void SetFunc_WindowPosCallback(Function* pFunc) { _pFunc_WindowPosCallback.reset(pFunc); }
	void SetFunc_WindowSizeCallback(Function* pFunc) { _pFunc_WindowSizeCallback.reset(pFunc); }
	void SetFunc_WindowCloseCallback(Function* pFunc) { _pFunc_WindowCloseCallback.reset(pFunc); }
	void SetFunc_WindowRefreshCallback(Function* pFunc) { _pFunc_WindowRefreshCallback.reset(pFunc); }
	void SetFunc_WindowFocusCallback(Function* pFunc) { _pFunc_WindowFocusCallback.reset(pFunc); }
	void SetFunc_WindowIconifyCallback(Function* pFunc) { _pFunc_WindowIconifyCallback.reset(pFunc); }
	void SetFunc_WindowMaximizeCallback(Function* pFunc) { _pFunc_WindowMaximizeCallback.reset(pFunc); }
	void SetFunc_FramebufferSizeCallback(Function* pFunc) { _pFunc_FramebufferSizeCallback.reset(pFunc); }
	void SetFunc_WindowContentScaleCallback(Function* pFunc) { _pFunc_WindowContentScaleCallback.reset(pFunc); }
	void SetFunc_MouseButtonCallback(Function* pFunc) { _pFunc_MouseButtonCallback.reset(pFunc); }
	void SetFunc_CursorPosCallback(Function* pFunc) { _pFunc_CursorPosCallback.reset(pFunc); }
	void SetFunc_CursorEnterCallback(Function* pFunc) { _pFunc_CursorEnterCallback.reset(pFunc); }
	void SetFunc_ScrollCallback(Function* pFunc) { _pFunc_ScrollCallback.reset(pFunc); }
	void SetFunc_KeyCallback(Function* pFunc) { _pFunc_KeyCallback.reset(pFunc); }
	void SetFunc_CharCallback(Function* pFunc) { _pFunc_CharCallback.reset(pFunc); }
	void SetFunc_CharModsCallback(Function* pFunc) { _pFunc_CharModsCallback.reset(pFunc); }
	void SetFunc_DropCallback(Function* pFunc) { _pFunc_DropCallback.reset(pFunc); }
	Function* GetFunc_WindowPosCallback() { return _pFunc_WindowPosCallback.get(); }
	Function* GetFunc_WindowSizeCallback() { return _pFunc_WindowSizeCallback.get(); }
	Function* GetFunc_WindowCloseCallback() { return _pFunc_WindowCloseCallback.get(); }
	Function* GetFunc_WindowRefreshCallback() { return _pFunc_WindowRefreshCallback.get(); }
	Function* GetFunc_WindowFocusCallback() { return _pFunc_WindowFocusCallback.get(); }
	Function* GetFunc_WindowIconifyCallback() { return _pFunc_WindowIconifyCallback.get(); }
	Function* GetFunc_WindowMaximizeCallback() { return _pFunc_WindowMaximizeCallback.get(); }
	Function* GetFunc_FramebufferSizeCallback() { return _pFunc_FramebufferSizeCallback.get(); }
	Function* GetFunc_WindowContentScaleCallback() { return _pFunc_WindowContentScaleCallback.get(); }
	Function* GetFunc_MouseButtonCallback() { return _pFunc_MouseButtonCallback.get(); }
	Function* GetFunc_CursorPosCallback() { return _pFunc_CursorPosCallback.get(); }
	Function* GetFunc_CursorEnterCallback() { return _pFunc_CursorEnterCallback.get(); }
	Function* GetFunc_ScrollCallback() { return _pFunc_ScrollCallback.get(); }
	Function* GetFunc_KeyCallback() { return _pFunc_KeyCallback.get(); }
	Function* GetFunc_CharCallback() { return _pFunc_CharCallback.get(); }
	Function* GetFunc_CharModsCallback() { return _pFunc_CharModsCallback.get(); }
	Function* GetFunc_DropCallback() { return _pFunc_DropCallback.get(); }
public:
	// Callback Function
	static void callback_WindowPosCallback(GLFWwindow* window, int xpos, int ypos);
	static void callback_WindowSizeCallback(GLFWwindow* window, int width, int height);
	static void callback_WindowCloseCallback(GLFWwindow* window);
	static void callback_WindowRefreshCallback(GLFWwindow* window);
	static void callback_WindowFocusCallback(GLFWwindow* window, int focused);
	static void callback_WindowIconifyCallback(GLFWwindow* window, int iconified);
	static void callback_WindowMaximizeCallback(GLFWwindow* window, int maximized);
	static void callback_FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void callback_WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
	static void callback_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void callback_CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void callback_CursorEnterCallback(GLFWwindow* window, int entered);
	static void callback_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void callback_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void callback_CharCallback(GLFWwindow* window, unsigned int codepoint);
	static void callback_CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	static void callback_DropCallback(GLFWwindow* window, int path_count, const char* paths[]);

	static void callback_JoystickCallback(int jid, int event);
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntity() == Value_GLFWwindow::GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntity() < Value_GLFWwindow::GetEntity(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif
