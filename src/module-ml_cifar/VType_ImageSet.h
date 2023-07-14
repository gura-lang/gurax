//==============================================================================
// VType_ImageSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_VTYPE_IMAGESET_H
#define GURAX_MODULE_ML_CIFAR_VTYPE_IMAGESET_H
#include <gurax.h>
#include "ImageSet.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// VType_ImageSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ImageSet : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ImageSet VTYPE_ImageSet;

//------------------------------------------------------------------------------
// Value_ImageSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ImageSet : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ImageSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ImageSet");
protected:
	RefPtr<ImageSet> _pImageSet;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ImageSet() = delete;
	explicit Value_ImageSet(ImageSet* pImageSet, VType& vtype = VTYPE_ImageSet) :
		Value_Object(vtype), _pImageSet(pImageSet) {}
	// Copy constructor/operator
	Value_ImageSet(const Value_ImageSet& src) :
		Value_Object(src), _pImageSet(src._pImageSet->Reference()) {}
	Value_ImageSet& operator=(const Value_ImageSet& src) = delete;
	// Move constructor/operator
	Value_ImageSet(Value_ImageSet&& src) noexcept = delete;
	Value_ImageSet& operator=(Value_ImageSet&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ImageSet() = default;
public:
	ImageSet& GetImageSet() { return *_pImageSet; }
	const ImageSet& GetImageSet() const { return *_pImageSet; }
public:
	static ImageSet& GetImageSet(Value& value) {
		return dynamic_cast<Value_ImageSet&>(value).GetImageSet();
	}
	static const ImageSet& GetImageSet(const Value& value) {
		return dynamic_cast<const Value_ImageSet&>(value).GetImageSet();
	}
	static ImageSet* GetEntityPtr(Value& value) { return &GetImageSet(value); }
	static const ImageSet* GetEntityPtr(const Value& value) { return &GetImageSet(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetImageSet().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetImageSet().IsEqualTo(Value_ImageSet::GetImageSet(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetImageSet().IsLessThan(Value_ImageSet::GetImageSet(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_cifar)

#endif
