//==============================================================================
// VType_Face.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_FACE_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_FACE_H
#include <gurax.h>
#include "Data.h"
#include "Face.h"
#include "Content.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Face
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Face : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Face VTYPE_Face;

//------------------------------------------------------------------------------
// Value_Face
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Face : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Face);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Face");
protected:
	RefPtr<Content> _pContent;
	RefPtr<Face> _pFace;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Face() = delete;
	Value_Face(Content* pContent, Face* pFace, VType& vtype = VTYPE_Face) :
		Value_Object(vtype), _pContent(pContent), _pFace(pFace) {}
	// Copy constructor/operator
	Value_Face(const Value_Face& src) :
		Value_Object(src), _pFace(src._pFace->Reference()) {}
	Value_Face& operator=(const Value_Face& src) = delete;
	// Move constructor/operator
	Value_Face(Value_Face&& src) noexcept = delete;
	Value_Face& operator=(Value_Face&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Face() = default;
public:
	const Content& GetContent() const { return *_pContent; }
	Face& GetFace() { return *_pFace; }
	const Face& GetFace() const { return *_pFace; }
public:
	static Face& GetFace(Value& value) {
		return dynamic_cast<Value_Face&>(value).GetFace();
	}
	static const Face& GetFace(const Value& value) {
		return dynamic_cast<const Value_Face&>(value).GetFace();
	}
	static Face* GetEntityPtr(Value& value) { return &GetFace(value); }
	static const Face* GetEntityPtr(const Value& value) { return &GetFace(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFace().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFace().IsEqualTo(Value_Face::GetFace(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFace().IsLessThan(Value_Face::GetFace(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
