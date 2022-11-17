//==============================================================================
// VType_GLFWcursor.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_VTYPE_GLFWCURSOR_H
#define GURAX_MODULE_GLFW_VTYPE_GLFWCURSOR_H
#include <gurax.h>
#include <GLFW/glfw3.h>

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// VType_GLFWcursor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLFWcursor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLFWcursor VTYPE_GLFWcursor;

//------------------------------------------------------------------------------
// Value_GLFWcursor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLFWcursor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLFWcursor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLFWcursor");
protected:
	GLFWcursor* _pGLFWcursor;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWcursor() = delete;
	explicit Value_GLFWcursor(GLFWcursor* pGLFWcursor, VType& vtype = VTYPE_GLFWcursor) :
		Value_Object(vtype), _pGLFWcursor(pGLFWcursor) {}
	// Copy constructor/operator
	Value_GLFWcursor(const Value_GLFWcursor& src) = delete;
	Value_GLFWcursor& operator=(const Value_GLFWcursor& src) = delete;
	// Move constructor/operator
	Value_GLFWcursor(Value_GLFWcursor&& src) noexcept = delete;
	Value_GLFWcursor& operator=(Value_GLFWcursor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLFWcursor() = default;
public:
	GLFWcursor* GetEntity() { return _pGLFWcursor; }
	const GLFWcursor* GetEntity() const { return _pGLFWcursor; }
public:
	static GLFWcursor* GetEntity(Value& value) {
		return dynamic_cast<Value_GLFWcursor&>(value).GetEntity();
	}
	static const GLFWcursor* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWcursor&>(value).GetEntity();
	}
	static GLFWcursor* ValueForVector(Value& value) { return GetEntity(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity() == Value_GLFWcursor::GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntity() < Value_GLFWcursor::GetEntity(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif
