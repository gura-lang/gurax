//==============================================================================
// Referencer.h
//==============================================================================
#ifndef GURAX_REFERENCER_H
#define GURAX_REFERENCER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Referencer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Referencer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Referencer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Referencer");
private:
	RefPtr<Frame> _pFrame;
	const Symbol* _pSymbol;
	RefPtr<Value> _pValue;
public:
	// Constructor
	Referencer() {}
	// Copy constructor/operator
	Referencer(const Referencer& src) = delete;
	Referencer& operator=(const Referencer& src) = delete;
	// Move constructor/operator
	Referencer(Referencer&& src) noexcept = delete;
	Referencer& operator=(Referencer&& src) noexcept = delete;
protected:
	~Referencer() = default;
public:
	static void Bootup();
public:
	virtual Frame& GetFrame() = 0;
	virtual const Frame& GetFrame() const = 0;
	virtual const Symbol* GetSymbol() const = 0;
	virtual void SetValue(Processor& processor, Value* pValue) = 0;
	virtual Value& GetValue() = 0;
	virtual const Value& GetValue() const = 0;
	virtual Referencer* CloneWithCastedValue(Value* pValueCasted) const = 0;
public:
	template<typename T> T& Get() { return dynamic_cast<T&>(GetValue()); }
	template<typename T> const T& Get() const { return dynamic_cast<const T&>(GetValue()); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Referencer& other) const { return this == &other; }
	bool IsEqualTo(const Referencer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Referencer& other) const { return this < &other; }
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const = 0;
};

//------------------------------------------------------------------------------
// Referencer_Lookup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Referencer_Lookup : public Referencer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Referencer_Lookup);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Referencer_Lookup");
private:
	RefPtr<Frame> _pFrame;
	const Symbol* _pSymbol;
	RefPtr<Value> _pValue;
public:
	// Constructor
	Referencer_Lookup(Frame* pFrame, const Symbol* pSymbol, Value* pValue);
	// Copy constructor/operator
	Referencer_Lookup(const Referencer_Lookup& src) = delete;
	Referencer_Lookup& operator=(const Referencer_Lookup& src) = delete;
	// Move constructor/operator
	Referencer_Lookup(Referencer_Lookup&& src) noexcept = delete;
	Referencer_Lookup& operator=(Referencer_Lookup&& src) noexcept = delete;
protected:
	~Referencer_Lookup() = default;
public:
	virtual Frame& GetFrame() override { return *_pFrame; }
	virtual const Frame& GetFrame() const override { return *_pFrame; }
	virtual const Symbol* GetSymbol() const override { return _pSymbol; }
	virtual void SetValue(Processor& processor, Value* pValue) override;
	virtual Value& GetValue() override { return *_pValue; }
	virtual const Value& GetValue() const override { return *_pValue; }
	virtual Referencer* CloneWithCastedValue(Value* pValueCasted) const override {
		return new Referencer_Lookup(GetFrame().Reference(), GetSymbol(), pValueCasted);
	}
public:
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
};

//------------------------------------------------------------------------------
// ReferencerList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReferencerList : public ListBase<Referencer*> {
};

//------------------------------------------------------------------------------
// ReferencerOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReferencerOwner : public ReferencerList {
public:
	~ReferencerOwner() { Clear(); }
	void Clear();
};

}

#endif
