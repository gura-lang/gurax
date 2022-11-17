//==============================================================================
// VType_GLFWimage.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_VTYPE_GLFWIMAGE_H
#define GURAX_MODULE_GLFW_VTYPE_GLFWIMAGE_H
#include <gurax.h>
#include <GLFW/glfw3.h>

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// VType_GLFWimage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLFWimage : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLFWimage VTYPE_GLFWimage;

//------------------------------------------------------------------------------
// Value_GLFWimage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLFWimage : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLFWimage);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLFWimage");
protected:
	GLFWimage* _pGLFWimage;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWimage() = delete;
	explicit Value_GLFWimage(GLFWimage* pGLFWimage, VType& vtype = VTYPE_GLFWimage) :
		Value_Object(vtype), _pGLFWimage(pGLFWimage) {}
	// Copy constructor/operator
	Value_GLFWimage(const Value_GLFWimage& src) = delete;
	Value_GLFWimage& operator=(const Value_GLFWimage& src) = delete;
	// Move constructor/operator
	Value_GLFWimage(Value_GLFWimage&& src) noexcept = delete;
	Value_GLFWimage& operator=(Value_GLFWimage&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLFWimage() = default;
public:
	GLFWimage* GetEntity() { return _pGLFWimage; }
	const GLFWimage* GetEntity() const { return _pGLFWimage; }
public:
	static GLFWimage* GetEntity(Value& value) {
		return dynamic_cast<Value_GLFWimage&>(value).GetEntity();
	}
	static const GLFWimage* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWimage&>(value).GetEntity();
	}
	static GLFWimage ValueForVector(Value& value) { return *GetEntity(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity() == Value_GLFWimage::GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntity() < Value_GLFWimage::GetEntity(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif
