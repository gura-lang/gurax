//==============================================================================
// VType_Vertex.h
//==============================================================================
#ifndef GURAX_VTYPE_VERTEX_H
#define GURAX_VTYPE_VERTEX_H
#include "VType_Object.h"
#include "Vertex.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Vertex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Vertex : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Vertex VTYPE_Vertex;

//------------------------------------------------------------------------------
// Value_Vertex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Vertex : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Vertex);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Vertex");
protected:
	Vertex _vertex;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Vertex() = delete;
	explicit Value_Vertex(Vertex vertex, VType& vtype = VTYPE_Vertex) :
		Value_Object(vtype), _vertex(vertex) {}
	// Copy constructor/operator
	Value_Vertex(const Value_Vertex& src) :
		Value_Object(src), _vertex(src._vertex) {}
	Value_Vertex& operator=(const Value_Vertex& src) = delete;
	// Move constructor/operator
	Value_Vertex(Value_Vertex&& src) noexcept = delete;
	Value_Vertex& operator=(Value_Vertex&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Vertex() = default;
public:
	Vertex& GetVertex() { return _vertex; }
	const Vertex& GetVertex() const { return _vertex; }
public:
	static Vertex& GetVertex(Value& value) {
		return dynamic_cast<Value_Vertex&>(value).GetVertex();
	}
	static const Vertex& GetVertex(const Value& value) {
		return dynamic_cast<const Value_Vertex&>(value).GetVertex();
	}
	static Vertex* GetEntityPtr(Value& value) { return &GetVertex(value); }
	static const Vertex* GetEntityPtr(const Value& value) { return &GetVertex(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetVertex().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetVertex().IsEqualTo(Value_Vertex::GetVertex(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetVertex().IsLessThan(Value_Vertex::GetVertex(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
