//==============================================================================
// Parser.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
Parser::Parser() : _pDocument(new Document())
{
	_parser = ::XML_ParserCreate(nullptr);
	::XML_SetUserData(_parser, this);
	::XML_SetStartElementHandler(_parser,			StartElementHandler);
	::XML_SetEndElementHandler(_parser,				EndElementHandler);
	::XML_SetCharacterDataHandler(_parser,			CharacterDataHandler);
	::XML_SetProcessingInstructionHandler(_parser,	ProcessingInstructionHandler);
	::XML_SetCommentHandler(_parser,				CommentHandler);
	::XML_SetStartCdataSectionHandler(_parser,		StartCdataSectionHandler);
	::XML_SetEndCdataSectionHandler(_parser,		EndCdataSectionHandler);
	::XML_SetDefaultHandler(_parser,				DefaultHandler);
	::XML_SetDefaultHandlerExpand(_parser,			DefaultHandlerExpand);
	::XML_SetExternalEntityRefHandler(_parser,		ExternalEntityRefHandler);
	::XML_SetSkippedEntityHandler(_parser,			SkippedEntityHandler);
	::XML_SetUnknownEncodingHandler(_parser,		UnknownEncodingHandler, this);
	::XML_SetStartNamespaceDeclHandler(_parser,		StartNamespaceDeclHandler);
	::XML_SetEndNamespaceDeclHandler(_parser,		EndNamespaceDeclHandler);
	::XML_SetXmlDeclHandler(_parser,				XmlDeclHandler);
	::XML_SetStartDoctypeDeclHandler(_parser,		StartDoctypeDeclHandler);
	::XML_SetEndDoctypeDeclHandler(_parser,			EndDoctypeDeclHandler);
	::XML_SetElementDeclHandler(_parser,			ElementDeclHandler);
	::XML_SetAttlistDeclHandler(_parser,			AttlistDeclHandler);
	::XML_SetEntityDeclHandler(_parser,				EntityDeclHandler);
	::XML_SetNotationDeclHandler(_parser,			NotationDeclHandler);
	::XML_SetNotStandaloneHandler(_parser,			NotStandaloneHandler);
}

Parser::~Parser()
{
	::XML_ParserFree(_parser);
}

bool Parser::Parse(Stream& stream)
{
	const size_t bytesToRead = 1024 * 8;
	int isFinal = 0;
	do {
		char* buff = reinterpret_cast<char*>(::XML_GetBuffer(_parser, bytesToRead));
		size_t bytesRead = static_cast<int>(stream.Read(buff, bytesToRead));
		if (Error::IsIssued()) return false;
		isFinal = (bytesRead < bytesToRead);
		XML_Status status = ::XML_Parse(_parser, buff, static_cast<int>(bytesRead), isFinal);
		if (Error::IsIssued()) {
			return false;
		} else if (status == XML_STATUS_ERROR) {
			Error::Issue(ErrorType::FormatError, "expat: %s at line %lu\n",
				::XML_ErrorString(XML_GetErrorCode(_parser)), ::XML_GetCurrentLineNumber(_parser));
			return false;
		} else if (status != XML_STATUS_OK) {
			return false;
		}
	} while (!isFinal);
	return true;
}

void XMLCALL Parser::StartElementHandler(void* userData, const XML_Char* name, const XML_Char** atts)
{
	// <name attr0="value0" attr1="value1" attr2="value">
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	RefPtr<Element> pElement(new Element(name));
	for (const XML_Char** p = atts; *p && *(p + 1); p += 2) {
		pElement->GetAttrs().push_back(new Attr(*p, *(p + 1)));
	}
	if (parser.HasElement()) {
		Element& elementCur = parser.GetElementCur();
		parser.PushElement(pElement.get());
		elementCur.AddNodeChild(pElement.release());
	} else {
		parser.PushElement(pElement.get());
		parser.GetDocument().SetElementRoot(pElement.release());
	}
}

void XMLCALL Parser::EndElementHandler(void* userData, const XML_Char* name)
{
	// </name>
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	parser.PopElement();
}

void XMLCALL Parser::CharacterDataHandler(void* userData, const XML_Char* text, int len)
{
	// text
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	const NodeOwner& nodes = parser.GetElementCur().GetNodesChild();
	if (!nodes.empty()) {
		Node* pNodeLast = nodes.back();
		if (parser.HasCData()) {
			parser.GetCData().AddText(text, len);
			return;
		} else if (pNodeLast->GetType() == Node::Type::Text) {
			dynamic_cast<Text*>(pNodeLast)->AddText(text, len);
			return;
		}
	}
	parser.GetElementCur().AddNodeChild(new Text(String(text, len)));
}

void XMLCALL Parser::ProcessingInstructionHandler(void* userData, const XML_Char* target, const XML_Char* data)
{
	// <?target data>
}

void XMLCALL Parser::CommentHandler(void* userData, const XML_Char* data)
{
	// <--data-->
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	RefPtr<Comment> pComment(new Comment(data));
	parser.GetElementCur().AddNodeChild(pComment.release());
}

void XMLCALL Parser::StartCdataSectionHandler(void* userData)
{
	// <![CDATA[
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	RefPtr<CData> pCData(new CData());
	parser.SetCData(pCData.Reference());
	parser.GetElementCur().AddNodeChild(pCData.release());
}

void XMLCALL Parser::EndCdataSectionHandler(void* userData)
{
	// ]]>
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	parser.ClearCData();
}

void XMLCALL Parser::DefaultHandler(void* userData, const XML_Char* text, int len)
{
}

void XMLCALL Parser::DefaultHandlerExpand(void* userData, const XML_Char* text, int len)
{
}

int XMLCALL Parser::ExternalEntityRefHandler(XML_Parser parser, const XML_Char* args,
				const XML_Char* base, const XML_Char* systemId, const XML_Char* publicId)
{
	// <!ENTITY>
	return 0;
}

void XMLCALL Parser::SkippedEntityHandler(void* userData, const XML_Char* entityName, int isParameterEntity)
{
}

int XMLCALL Parser::UnknownEncodingHandler(void* encodingHandlerData, const XML_Char* name, XML_Encoding* info)
{
	for (int i = 0; i < Gurax_ArraySizeOf(info->map); i++) info->map[i] = -1;
	if (::strcasecmp(name, "shift_jis") == 0) {
		for (int i = 0; i <= 0x7f; i++) info->map[i] = i;
		for (int i = 0x81; i <= 0x9f; i++) info->map[i] = -2;
		for (int i = 0xe0; i <= 0xee; i++) info->map[i] = -2;
		for (int i = 0xfa; i <= 0xfc; i++) info->map[i] = -2;
		info->data = nullptr;
		info->convert = Convert_shift_jis;
		info->release = nullptr;
		return XML_STATUS_OK;
	} else if (::strcasecmp(name, "euc-jp") == 0) {
		for (int i = 0; i <= 0x7f; i++) info->map[i] = i;
		for (int i = 0x81; i <= 0xff; i++) info->map[i] = -2;
		info->data = nullptr;
		info->convert = Convert_euc_jp;
		info->release = nullptr;
		return XML_STATUS_OK;
	}
	return XML_STATUS_ERROR;
}

void XMLCALL Parser::StartNamespaceDeclHandler(void* userData, const XML_Char* prefix, const XML_Char* uri)
{
	// <tag xmlns:prefix="uri">
}

void XMLCALL Parser::EndNamespaceDeclHandler(void* userData, const XML_Char* prefix)
{
}

void XMLCALL Parser::XmlDeclHandler(void* userData, const XML_Char* version, const XML_Char* encoding, int standalone)
{
	// <?xml version="version" encoding="encoding" standalone="yes|no"?>
	Parser& parser = *reinterpret_cast<Parser*>(userData);
	RefPtr<XmlDecl> pXmlDecl(new XmlDecl(version, encoding, standalone));
	parser.GetDocument().SetXmlDecl(pXmlDecl.release());
}

void XMLCALL Parser::StartDoctypeDeclHandler(void* userData, const XML_Char* doctypeName,
			const XML_Char* systemId, const XML_Char* publicId, int hasInternalSubset)
{
	// <!DOCTYPE doctypeName systemId "publicId"[
}

void XMLCALL Parser::EndDoctypeDeclHandler(void* userData)
{
	// ]>
}

void XMLCALL Parser::ElementDeclHandler(void* userData, const XML_Char* name, XML_Content* model)
{
	// DTD
}

void XMLCALL Parser::AttlistDeclHandler(void* userData,
			const XML_Char* elemName, const XML_Char* attName,
			const XML_Char* attType, const XML_Char* defaultValue, int isRequired)
{
	// DTD
}

void XMLCALL Parser::EntityDeclHandler(void* userData, const XML_Char* entityName, int isParameterEntity,
			const XML_Char* value, int valueLength, const XML_Char* base, const XML_Char* systemId,
			const XML_Char* publicId, const XML_Char* notationName)
{
	// <!ENTITY>
}

void XMLCALL Parser::NotationDeclHandler(void* userData, const XML_Char* notationName,
			const XML_Char* base, const XML_Char* systemId, const XML_Char* publicId)
{
}

int XMLCALL Parser::NotStandaloneHandler(void* userData)
{
	return 0;
}

int Parser::Convert_shift_jis(void* data, const char* s)
{
	UInt16 codeCP932 = (static_cast<UInt16>(static_cast<UInt8>(s[0])) << 8) + static_cast<UInt8>(s[1]);
	UInt16 codeUTF16 = CP932ToUTF16(codeCP932);
	return (codeUTF16 == 0)? -1 : codeUTF16;
}

int Parser::Convert_euc_jp(void* data, const char* s)
{
	UInt16 codeEUCJP = (static_cast<UInt16>(static_cast<UInt8>(s[0])) << 8) + static_cast<UInt8>(s[1]);
	UInt16 codeCP932 = EUCJPToCP932(codeEUCJP);
	UInt16 codeUTF16 = CP932ToUTF16(codeCP932);
	return (codeUTF16 == 0)? -1 : codeUTF16;
}

String Parser::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Parser");
}

Gurax_EndModuleScope(xml)
