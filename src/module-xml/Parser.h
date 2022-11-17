//==============================================================================
// Parser.h
//==============================================================================
#ifndef GURAX_MODULE_XML_PARSER_H
#define GURAX_MODULE_XML_PARSER_H
#include <gurax.h>
#include <expat.h>
#include "CData.h"
#include "Document.h"
#include "Element.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Parser : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Parser);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Parser");
private:
	XML_Parser _parser;
	RefPtr<Document> _pDocument;
	RefPtr<CData> _pCData;
	ElementStack _elementStack;
public:
	// Constructor
	Parser();
	// Copy constructor/operator
	Parser(const Parser& src) = delete;
	Parser& operator=(const Parser& src) = delete;
	// Move constructor/operator
	Parser(Parser&& src) noexcept = delete;
	Parser& operator=(Parser&& src) noexcept = delete;
protected:
	~Parser();
public:
	bool Parse(Stream& stream);
	Document& GetDocument() { return *_pDocument; }
public:
	void PushElement(Element* pElement) { _elementStack.push_back(pElement); }
	void PopElement() { _elementStack.pop_back(); }
	bool HasElement() const { return !_elementStack.empty(); }
	Element& GetElementCur() { return *_elementStack.back(); }
public:
	void SetCData(CData* pCData) { _pCData.reset(pCData); }
	void ClearCData() { _pCData.reset(); }
	bool HasCData() const { return !!_pCData; }
	CData& GetCData() { return *_pCData; }
private:
	static void XMLCALL StartElementHandler(void* userData, const XML_Char* name, const XML_Char** atts);
	static void XMLCALL EndElementHandler(void* userData, const XML_Char* name);
	static void XMLCALL CharacterDataHandler(void* userData, const XML_Char* s, int len);
	static void XMLCALL ProcessingInstructionHandler(void* userData, const XML_Char* target, const XML_Char* data);
	static void XMLCALL CommentHandler(void* userData, const XML_Char* data);
	static void XMLCALL StartCdataSectionHandler(void* userData);
	static void XMLCALL EndCdataSectionHandler(void* userData);
	static void XMLCALL DefaultHandler(void* userData, const XML_Char* s, int len);
	static void XMLCALL DefaultHandlerExpand(void* userData, const XML_Char* s, int len);
	static int  XMLCALL ExternalEntityRefHandler(XML_Parser p, const XML_Char* args, const XML_Char* base, const XML_Char* systemId, const XML_Char* publicId);
	static void XMLCALL SkippedEntityHandler(void* userData, const XML_Char* entityName, int isParameterEntity);
	static int  XMLCALL UnknownEncodingHandler(void* encodingHandlerData, const XML_Char* name, XML_Encoding* info);
	static void XMLCALL StartNamespaceDeclHandler(void* userData, const XML_Char* prefix, const XML_Char* uri);
	static void XMLCALL EndNamespaceDeclHandler(void* userData, const XML_Char* prefix);
	static void XMLCALL XmlDeclHandler(void* userData, const XML_Char* version, const XML_Char* encoding, int standalone);
	static void XMLCALL StartDoctypeDeclHandler(void* userData, const XML_Char* doctypeName, const XML_Char* systemId, const XML_Char* publicId, int hasInternalSubset);
	static void XMLCALL EndDoctypeDeclHandler(void* userData);
	static void XMLCALL ElementDeclHandler(void* userData, const XML_Char* name, XML_Content* model);
	static void XMLCALL AttlistDeclHandler(void* userData, const XML_Char* elname, const XML_Char* attname, const XML_Char* attType, const XML_Char* dflt, int isRequired);
	static void XMLCALL EntityDeclHandler(void* userData, const XML_Char* entityName, int isParameterEntity, const XML_Char* value, int valueLength, const XML_Char* base, const XML_Char* systemId, const XML_Char* publicId, const XML_Char* notationName);
	static void XMLCALL NotationDeclHandler(void* userData, const XML_Char* notationName, const XML_Char* base, const XML_Char* systemId, const XML_Char* publicId);
	static int  XMLCALL NotStandaloneHandler(void* userData);
public:
	static int Convert_shift_jis(void* data, const char* s);
	static int Convert_euc_jp(void* data, const char* s);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Parser& other) const { return this == &other; }
	bool IsEqualTo(const Parser& other) const { return IsIdentical(other); }
	bool IsLessThan(const Parser& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(xml)

#endif
