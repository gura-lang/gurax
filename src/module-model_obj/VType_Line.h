//==============================================================================
// VType_Line.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_LINE_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_LINE_H
#include <gurax.h>
#include "Line.h"
#include "Content.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Line
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Line : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Line VTYPE_Line;

//------------------------------------------------------------------------------
// Value_Line
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Line : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Line);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Line");
protected:
	RefPtr<Content> _pContent;
	RefPtr<Line> _pLine;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Line() = delete;
	Value_Line(Content* pContent, Line* pLine, VType& vtype = VTYPE_Line) :
		Value_Object(vtype), _pContent(pContent), _pLine(pLine) {}
	// Copy constructor/operator
	Value_Line(const Value_Line& src) :
		Value_Object(src), _pLine(src._pLine->Reference()) {}
	Value_Line& operator=(const Value_Line& src) = delete;
	// Move constructor/operator
	Value_Line(Value_Line&& src) noexcept = delete;
	Value_Line& operator=(Value_Line&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Line() = default;
public:
	const Content& GetContent() const { return *_pContent; }
	Line& GetLine() { return *_pLine; }
	const Line& GetLine() const { return *_pLine; }
public:
	static Line& GetLine(Value& value) {
		return dynamic_cast<Value_Line&>(value).GetLine();
	}
	static const Line& GetLine(const Value& value) {
		return dynamic_cast<const Value_Line&>(value).GetLine();
	}
	static Line* GetEntityPtr(Value& value) { return &GetLine(value); }
	static const Line* GetEntityPtr(const Value& value) { return &GetLine(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetLine().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetLine().IsEqualTo(Value_Line::GetLine(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetLine().IsLessThan(Value_Line::GetLine(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
