//==============================================================================
// VType_BitmapInfoHeader.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_VTYPE_BITMAPINFOHEADER_H
#define GURAX_MODULE_BMP_VTYPE_BITMAPINFOHEADER_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// VType_BitmapInfoHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_BitmapInfoHeader : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_BitmapInfoHeader VTYPE_BitmapInfoHeader;

//------------------------------------------------------------------------------
// Value_BitmapInfoHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_BitmapInfoHeader : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_BitmapInfoHeader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_BitmapInfoHeader");
protected:
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_BitmapInfoHeader() = delete;
	explicit Value_BitmapInfoHeader(Content* pContent, VType& vtype = VTYPE_BitmapInfoHeader) :
		Value_Object(vtype), _pContent(pContent) {}
	// Copy constructor/operator
	Value_BitmapInfoHeader(const Value_BitmapInfoHeader& src) :
		Value_Object(src), _pContent(src._pContent->Reference()) {}
	Value_BitmapInfoHeader& operator=(const Value_BitmapInfoHeader& src) = delete;
	// Move constructor/operator
	Value_BitmapInfoHeader(Value_BitmapInfoHeader&& src) = delete;
	Value_BitmapInfoHeader& operator=(Value_BitmapInfoHeader&& src) noexcept = delete;
protected:
	// Destructor
	~Value_BitmapInfoHeader() = default;
public:
	Content& GetContent() { return *_pContent; }
	const Content& GetContent() const { return *_pContent; }
public:
	static Content& GetContent(Value& value) {
		return dynamic_cast<Value_BitmapInfoHeader&>(value).GetContent();
	}
	static const Content& GetContent(const Value& value) {
		return dynamic_cast<const Value_BitmapInfoHeader&>(value).GetContent();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetContent().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetContent().IsEqualTo(Value_BitmapInfoHeader::GetContent(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetContent().IsLessThan(Value_BitmapInfoHeader::GetContent(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(bmp)

#endif
