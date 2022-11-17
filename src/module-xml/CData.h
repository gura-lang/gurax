//==============================================================================
// CData.h
//==============================================================================
#ifndef GURAX_MODULE_XML_CDATA_H
#define GURAX_MODULE_XML_CDATA_H
#include <gurax.h>
#include "Node.h"
#include "Text.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// CData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CData : public Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(CData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.CData");
private:
	String _text;
public:
	// Constructor
	CData() : Node(Type::CData) {}
	// Copy constructor/operator
	CData(const CData& src) = delete;
	CData& operator=(const CData& src) = delete;
	// Move constructor/operator
	CData(CData&& src) noexcept = delete;
	CData& operator=(CData&& src) noexcept = delete;
protected:
	~CData() = default;
public:
	void AddText(const char* text, size_t len) { _text.append(text, len); }
	String Textize() const;
	virtual bool CheckTypeMask(UInt32 typeMask, const char* tagName) const override {
		return typeMask & TypeMask::CData;
	}
	virtual const char* GetText() const override { return _text.c_str(); }
	virtual Value* CreateValue() const override;
	virtual bool Compose(Stream& stream) const override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const CData& other) const { return this == &other; }
	bool IsEqualTo(const CData& other) const { return IsIdentical(other); }
	bool IsLessThan(const CData& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CDataStack
//------------------------------------------------------------------------------
class CDataStack : public ListBase<CData*> {
};

Gurax_EndModuleScope(xml)

#endif
