//==============================================================================
// VType_Point.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_POINT_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_POINT_H
#include <gurax.h>
#include "Data.h"
#include "Point.h"
#include "Content.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Point : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Point VTYPE_Point;

//------------------------------------------------------------------------------
// Value_Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Point : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Point);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Point");
protected:
	RefPtr<Content> _pContent;
	RefPtr<Point> _pPoint;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Point() = delete;
	Value_Point(Content* pContent, Point* pPoint, VType& vtype = VTYPE_Point) :
		Value_Object(vtype), _pContent(pContent), _pPoint(pPoint) {}
	// Copy constructor/operator
	Value_Point(const Value_Point& src) :
		Value_Object(src), _pPoint(src._pPoint->Reference()) {}
	Value_Point& operator=(const Value_Point& src) = delete;
	// Move constructor/operator
	Value_Point(Value_Point&& src) noexcept = delete;
	Value_Point& operator=(Value_Point&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Point() = default;
public:
	const Content& GetContent() const { return *_pContent; }
	Point& GetPoint() { return *_pPoint; }
	const Point& GetPoint() const { return *_pPoint; }
public:
	static Point& GetPoint(Value& value) {
		return dynamic_cast<Value_Point&>(value).GetPoint();
	}
	static const Point& GetPoint(const Value& value) {
		return dynamic_cast<const Value_Point&>(value).GetPoint();
	}
	static Point* GetEntityPtr(Value& value) { return &GetPoint(value); }
	static const Point* GetEntityPtr(const Value& value) { return &GetPoint(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPoint().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPoint().IsEqualTo(Value_Point::GetPoint(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPoint().IsLessThan(Value_Point::GetPoint(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
