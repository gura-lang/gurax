//==============================================================================
// Item.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_ITEM_H
#define GURAX_MODULE_MARKDOWN_ITEM_H
#include <gurax.h>

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Item : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Item);
public:
	// Constructor
	Item() {}
	// Copy constructor/operator
	Item(const Item& src) = delete;
	Item& operator=(const Item& src) = delete;
	// Move constructor/operator
	Item(Item&& src) = delete;
	Item& operator=(Item&& src) noexcept = delete;
protected:
	~Item() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Item& other) const { return this == &other; }
	bool IsEqualTo(const Item& other) const { return IsIdentical(other); }
	bool IsLessThan(const Item& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(markdown)

#endif
