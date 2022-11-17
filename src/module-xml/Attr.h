//==============================================================================
// Attr.h
//==============================================================================
#ifndef GURAX_MODULE_XML_ATTR_H
#define GURAX_MODULE_XML_ATTR_H
#include <gurax.h>

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Attr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Attr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Attr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Attr");
private:
	String _name;
	String _value;
public:
	// Constructor
	Attr(String name, String value) : _name(name), _value(value) {}
	// Copy constructor/operator
	Attr(const Attr& src) = delete;
	Attr& operator=(const Attr& src) = delete;
	// Move constructor/operator
	Attr(Attr&& src) noexcept = delete;
	Attr& operator=(Attr&& src) noexcept = delete;
protected:
	~Attr() = default;
public:
	const char* GetName() const { return _name.c_str(); }
	const char* GetValue() const { return _value.c_str(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Attr& other) const { return this == &other; }
	bool IsEqualTo(const Attr& other) const { return IsIdentical(other); }
	bool IsLessThan(const Attr& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// AttrList
//------------------------------------------------------------------------------
class AttrList : public ListBase<Attr*> {
public:
	const Attr* Find(const char* name) const;
	const Attr* IndexGet(const Value& valueIndex) const;
};

//------------------------------------------------------------------------------
// AttrOwner
//------------------------------------------------------------------------------
class AttrOwner : public AttrList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(AttrOwner);
public:
	AttrOwner() {}
	~AttrOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// Iterator_Attr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Attr : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Attr");
private:
	RefPtr<AttrOwner> _pAttrOwner;
	size_t _idx;
public:
	Iterator_Attr(AttrOwner* pAttrOwner) : _pAttrOwner(pAttrOwner), _idx(0) {}
public:
	AttrOwner& GetAttrOwner() { return *_pAttrOwner; }
	const AttrOwner& GetAttrOwner() const { return *_pAttrOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetAttrOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
