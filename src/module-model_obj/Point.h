//==============================================================================
// Point.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_POINT_H
#define GURAX_MODULE_MODEL_OBJ_POINT_H
#include <gurax.h>
#include "Data.h"
#include "Index.h"
#include "Vertex4.h"

Gurax_BeginModuleScope(model_obj)

class Content;

//------------------------------------------------------------------------------
// Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Point : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Point);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Point");
private:
	IndexList _indexList;
public:
	// Constructor
	Point() { _indexList.reserve(16); }
	// Copy constructor/operator
	Point(const Point& src) = delete;
	Point& operator=(const Point& src) = delete;
	// Move constructor/operator
	Point(Point&& src) noexcept = delete;
	Point& operator=(Point&& src) noexcept = delete;
protected:
	~Point() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	void AddIndex(Index iV) { _indexList.push_back(iV); }
	const IndexList& GetIndexList() const { return _indexList; }
	const Vertex4* GetV(const Content& content, size_t iIndex) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Point& other) const { return this == &other; }
	bool IsEqualTo(const Point& other) const { return IsIdentical(other); }
	bool IsLessThan(const Point& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// PointList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PointList : public ListBase<Point*> {
};

//------------------------------------------------------------------------------
// PointOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PointOwner : public PointList {
public:
	~PointOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
