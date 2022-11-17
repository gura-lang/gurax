//==============================================================================
// VType_Tag.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_VTYPE_TAG_H
#define GURAX_MODULE_JPEG_VTYPE_TAG_H
#include <gurax.h>
#include "Tag.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// VType_Tag
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Tag : public VType {
public:
	class GURAX_DLLDECLARE Iterator_Each : public Iterator {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("Tag.Each");
	private:
		RefPtr<TagOwner> _pTagOwner;
		size_t _idx;
	public:
		Iterator_Each(TagOwner* pTagOwner) : _pTagOwner(pTagOwner), _idx(0) {}
	public:
		TagOwner& GetTagOwner() { return *_pTagOwner; }
		const TagOwner& GetTagOwner() const { return *_pTagOwner; }
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetTagOwner().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Tag VTYPE_Tag;

//------------------------------------------------------------------------------
// Value_Tag
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Tag : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Tag);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Tag");
protected:
	RefPtr<Tag> _pTag;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Tag() = delete;
	explicit Value_Tag(Tag* pTag, VType& vtype = VTYPE_Tag) :
		Value_Object(vtype), _pTag(pTag) {}
	// Copy constructor/operator
	Value_Tag(const Value_Tag& src) :
		Value_Object(src), _pTag(src._pTag->Reference()) {}
	Value_Tag& operator=(const Value_Tag& src) = delete;
	// Move constructor/operator
	Value_Tag(Value_Tag&& src) = delete;
	Value_Tag& operator=(Value_Tag&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Tag() = default;
public:
	Tag& GetTag() { return *_pTag; }
	const Tag& GetTag() const { return *_pTag; }
public:
	static Tag& GetTag(Value& value) {
		return dynamic_cast<Value_Tag&>(value).GetTag();
	}
	static const Tag& GetTag(const Value& value) {
		return dynamic_cast<const Value_Tag&>(value).GetTag();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTag().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTag().IsEqualTo(Value_Tag::GetTag(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTag().IsLessThan(Value_Tag::GetTag(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(jpeg)

#endif
