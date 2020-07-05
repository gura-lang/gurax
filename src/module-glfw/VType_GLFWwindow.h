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
	RefPtr<Function> _pFunc_windowposfun;
	RefPtr<Function> _pFunc_windowsizefun;
	RefPtr<Function> _pFunc_windowclosefun;
	RefPtr<Function> _pFunc_windowrefreshfun;
	RefPtr<Function> _pFunc_windowfocusfun;
	RefPtr<Function> _pFunc_windowiconifyfun;
	RefPtr<Function> _pFunc_windowmaximizefun;
	RefPtr<Function> _pFunc_framebuffersizefun;
	RefPtr<Function> _pFunc_windowcontentscalefun;
	RefPtr<Function> _pFunc_mousebuttonfun;
	RefPtr<Function> _pFunc_cursorposfun;
	RefPtr<Function> _pFunc_cursorenterfun;
	RefPtr<Function> _pFunc_scrollfun;
	RefPtr<Function> _pFunc_keyfun;
	RefPtr<Function> _pFunc_charfun;
	RefPtr<Function> _pFunc_charmodsfun;
	RefPtr<Function> _pFunc_dropfun;
	RefPtr<Function> _pFunc_monitorfun;
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
	static Value_GLFWwindow* GetValue(GLFWwindow* pGLFWwindow) {
		return reinterpret_cast<Value_GLFWwindow*>(glfwGetWindowUserPointer(pGLFWwindow));
	}
public:
	void SetFunc_windowposfun(Function* pFunc) { _pFunc_windowposfun.reset(pFunc); }
	void SetFunc_windowsizefun(Function* pFunc) { _pFunc_windowsizefun.reset(pFunc); }
	void SetFunc_windowclosefun(Function* pFunc) { _pFunc_windowclosefun.reset(pFunc); }
	void SetFunc_windowrefreshfun(Function* pFunc) { _pFunc_windowrefreshfun.reset(pFunc); }
	void SetFunc_windowfocusfun(Function* pFunc) { _pFunc_windowfocusfun.reset(pFunc); }
	void SetFunc_windowiconifyfun(Function* pFunc) { _pFunc_windowiconifyfun.reset(pFunc); }
	void SetFunc_windowmaximizefun(Function* pFunc) { _pFunc_windowmaximizefun.reset(pFunc); }
	void SetFunc_framebuffersizefun(Function* pFunc) { _pFunc_framebuffersizefun.reset(pFunc); }
	void SetFunc_windowcontentscalefun(Function* pFunc) { _pFunc_windowcontentscalefun.reset(pFunc); }
	void SetFunc_mousebuttonfun(Function* pFunc) { _pFunc_mousebuttonfun.reset(pFunc); }
	void SetFunc_cursorposfun(Function* pFunc) { _pFunc_cursorposfun.reset(pFunc); }
	void SetFunc_cursorenterfun(Function* pFunc) { _pFunc_cursorenterfun.reset(pFunc); }
	void SetFunc_scrollfun(Function* pFunc) { _pFunc_scrollfun.reset(pFunc); }
	void SetFunc_keyfun(Function* pFunc) { _pFunc_keyfun.reset(pFunc); }
	void SetFunc_charfun(Function* pFunc) { _pFunc_charfun.reset(pFunc); }
	void SetFunc_charmodsfun(Function* pFunc) { _pFunc_charmodsfun.reset(pFunc); }
	void SetFunc_dropfun(Function* pFunc) { _pFunc_dropfun.reset(pFunc); }
	void SetFunc_monitorfun(Function* pFunc) { _pFunc_monitorfun.reset(pFunc); }
	Function* GetFunc_windowposfun() { return _pFunc_windowposfun.get(); }
	Function* GetFunc_windowsizefun() { return _pFunc_windowsizefun.get(); }
	Function* GetFunc_windowclosefun() { return _pFunc_windowclosefun.get(); }
	Function* GetFunc_windowrefreshfun() { return _pFunc_windowrefreshfun.get(); }
	Function* GetFunc_windowfocusfun() { return _pFunc_windowfocusfun.get(); }
	Function* GetFunc_windowiconifyfun() { return _pFunc_windowiconifyfun.get(); }
	Function* GetFunc_windowmaximizefun() { return _pFunc_windowmaximizefun.get(); }
	Function* GetFunc_framebuffersizefun() { return _pFunc_framebuffersizefun.get(); }
	Function* GetFunc_windowcontentscalefun() { return _pFunc_windowcontentscalefun.get(); }
	Function* GetFunc_mousebuttonfun() { return _pFunc_mousebuttonfun.get(); }
	Function* GetFunc_cursorposfun() { return _pFunc_cursorposfun.get(); }
	Function* GetFunc_cursorenterfun() { return _pFunc_cursorenterfun.get(); }
	Function* GetFunc_scrollfun() { return _pFunc_scrollfun.get(); }
	Function* GetFunc_keyfun() { return _pFunc_keyfun.get(); }
	Function* GetFunc_charfun() { return _pFunc_charfun.get(); }
	Function* GetFunc_charmodsfun() { return _pFunc_charmodsfun.get(); }
	Function* GetFunc_dropfun() { return _pFunc_dropfun.get(); }
	Function* GetFunc_monitorfun() { return _pFunc_monitorfun.get(); }
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
