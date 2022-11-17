//==============================================================================
// VType_GLFWvidmode.h
//==============================================================================
#ifndef GURAX_MODULE_GLFW_VTYPE_GLFWVIDMODE_H
#define GURAX_MODULE_GLFW_VTYPE_GLFWVIDMODE_H
#include <gurax.h>
#include <GLFW/glfw3.h>

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// VType_GLFWvidmode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GLFWvidmode : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GLFWvidmode VTYPE_GLFWvidmode;

//------------------------------------------------------------------------------
// Value_GLFWvidmode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GLFWvidmode : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GLFWvidmode);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GLFWvidmode");
protected:
	const GLFWvidmode* _pGLFWvidmode;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GLFWvidmode() = delete;
	explicit Value_GLFWvidmode(const GLFWvidmode* pGLFWvidmode, VType& vtype = VTYPE_GLFWvidmode) :
		Value_Object(vtype), _pGLFWvidmode(pGLFWvidmode) {}
	// Copy constructor/operator
	Value_GLFWvidmode(const Value_GLFWvidmode& src) = delete;
	Value_GLFWvidmode& operator=(const Value_GLFWvidmode& src) = delete;
	// Move constructor/operator
	Value_GLFWvidmode(Value_GLFWvidmode&& src) noexcept = delete;
	Value_GLFWvidmode& operator=(Value_GLFWvidmode&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GLFWvidmode() = default;
public:
	const GLFWvidmode* GetEntity() const { return _pGLFWvidmode; }
public:
	static const GLFWvidmode* GetEntity(const Value& value) {
		return dynamic_cast<const Value_GLFWvidmode&>(value).GetEntity();
	}
	static GLFWvidmode ValueForVector(Value& value) { return *GetEntity(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity() == Value_GLFWvidmode::GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntity() < Value_GLFWvidmode::GetEntity(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(glfw)

#endif
