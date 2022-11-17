//==============================================================================
// VType_Item.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_VTYPE_ITEM_H
#define GURAX_MODULE_MARKDOWN_VTYPE_ITEM_H
#include <gurax.h>
#include "Item.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// VType_Item
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Item : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Item VTYPE_Item;

//------------------------------------------------------------------------------
// Value_Item
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Item : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Item);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Item");
protected:
	RefPtr<Item> _pItem;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Item() = delete;
	explicit Value_Item(Item* pItem, VType& vtype = VTYPE_Item) :
		Value_Object(vtype), _pItem(pItem) {}
	// Copy constructor/operator
	Value_Item(const Value_Item& src) :
		Value_Object(src), _pItem(src._pItem->Reference()) {}
	Value_Item& operator=(const Value_Item& src) = delete;
	// Move constructor/operator
	Value_Item(Value_Item&& src) = delete;
	Value_Item& operator=(Value_Item&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Item() = default;
public:
	Item& GetItem() { return *_pItem; }
	const Item& GetItem() const { return *_pItem; }
public:
	static Item& GetItem(Value& value) {
		return dynamic_cast<Value_Item&>(value).GetItem();
	}
	static const Item& GetItem(const Value& value) {
		return dynamic_cast<const Value_Item&>(value).GetItem();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetItem().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetItem().IsEqualTo(Value_Item::GetItem(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetItem().IsLessThan(Value_Item::GetItem(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(markdown)

#endif
