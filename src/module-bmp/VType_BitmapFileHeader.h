//==============================================================================
// VType_BitmapFileHeader.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_VTYPE_BITMAPFILEHEADER_H
#define GURAX_MODULE_BMP_VTYPE_BITMAPFILEHEADER_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// VType_BitmapFileHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_BitmapFileHeader : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_BitmapFileHeader VTYPE_BitmapFileHeader;

//------------------------------------------------------------------------------
// Value_BitmapFileHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_BitmapFileHeader : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_BitmapFileHeader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_BitmapFileHeader");
protected:
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_BitmapFileHeader() = delete;
	explicit Value_BitmapFileHeader(Content* pContent, VType& vtype = VTYPE_BitmapFileHeader) :
		Value_Object(vtype), _pContent(pContent) {}
	// Copy constructor/operator
	Value_BitmapFileHeader(const Value_BitmapFileHeader& src) :
		Value_Object(src), _pContent(src._pContent->Reference()) {}
	Value_BitmapFileHeader& operator=(const Value_BitmapFileHeader& src) = delete;
	// Move constructor/operator
	Value_BitmapFileHeader(Value_BitmapFileHeader&& src) = delete;
	Value_BitmapFileHeader& operator=(Value_BitmapFileHeader&& src) noexcept = delete;
protected:
	// Destructor
	~Value_BitmapFileHeader() = default;
public:
	Content& GetContent() { return *_pContent; }
	const Content& GetContent() const { return *_pContent; }
public:
	static Content& GetContent(Value& value) {
		return dynamic_cast<Value_BitmapFileHeader&>(value).GetContent();
	}
	static const Content& GetContent(const Value& value) {
		return dynamic_cast<const Value_BitmapFileHeader&>(value).GetContent();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetContent().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetContent().IsEqualTo(Value_BitmapFileHeader::GetContent(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetContent().IsLessThan(Value_BitmapFileHeader::GetContent(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(bmp)

#endif
