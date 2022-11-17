//==============================================================================
// VType_Document.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_DOCUMENT_H
#define GURAX_MODULE_XML_VTYPE_DOCUMENT_H
#include <gurax.h>
#include "Document.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Document
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Document : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Document VTYPE_Document;

//------------------------------------------------------------------------------
// Value_Document
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Document : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Document);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Document");
protected:
	RefPtr<Document> _pDocument;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Document() = delete;
	explicit Value_Document(Document* pDocument, VType& vtype = VTYPE_Document) :
		Value_Object(vtype), _pDocument(pDocument) {}
	// Copy constructor/operator
	Value_Document(const Value_Document& src) :
		Value_Object(src), _pDocument(src._pDocument->Reference()) {}
	Value_Document& operator=(const Value_Document& src) = delete;
	// Move constructor/operator
	Value_Document(Value_Document&& src) noexcept = delete;
	Value_Document& operator=(Value_Document&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Document() = default;
public:
	Document& GetDocument() { return *_pDocument; }
	const Document& GetDocument() const { return *_pDocument; }
public:
	static Document& GetDocument(Value& value) {
		return dynamic_cast<Value_Document&>(value).GetDocument();
	}
	static const Document& GetDocument(const Value& value) {
		return dynamic_cast<const Value_Document&>(value).GetDocument();
	}
	static Document* GetEntityPtr(Value& value) { return &GetDocument(value); }
	static const Document* GetEntityPtr(const Value& value) { return &GetDocument(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDocument().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetDocument().IsEqualTo(Value_Document::GetDocument(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetDocument().IsLessThan(Value_Document::GetDocument(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
