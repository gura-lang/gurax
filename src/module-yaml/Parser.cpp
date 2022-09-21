//==============================================================================
// Parser.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(yaml)

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
Parser::Parser(Stream* pStream) : _pStream(pStream)
{
	::yaml_parser_initialize(&_parser);
	::yaml_parser_set_input(&_parser, reinterpret_cast<yaml_read_handler_t*>(ReadHandler), this);
}

Parser::~Parser()
{
	yaml_parser_delete(&_parser);
	for (auto pair : _anchorMap) Value::Delete(pair.second);
}

Value* Parser::Parse()
{
	StockerStack stockerStack;
	RefPtr<Value_List> pValueRtn(new Value_List());
	stockerStack.Push(new Stocker_Sequence(pValueRtn.Reference()));
	for (bool contFlag = true; contFlag; ) {
		yaml_event_t event;
		if (!::yaml_parser_parse(&_parser, &event)) {
			Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_parser.error));
			return nullptr;
		}
		switch (event.type) {
		case YAML_STREAM_START_EVENT:
			//::printf("STREAM_START\n");
			//yaml_encoding_t encoding = event.data.stream_start.encoding;
			break;
		case YAML_STREAM_END_EVENT:
			//::printf("STREAM_END\n");
			contFlag = false;
			break;
		case YAML_DOCUMENT_START_EVENT: {
			//yaml_version_directive_t* version_directive = event.data.document_start.version_directive;
			//yaml_tag_directive_t* tag_start = event.data.document_start.tag_directives.start;
			//yaml_tag_directive_t* tag_end = event.data.document_start.tag_directives.end;
			//int implicit = event.data.document_start.implicit;
			//::printf("DOCUMENT_START\n");
			//tag_start->handle;
			//tag_start->prefix;
			//tag_end->handle;
			//tag_end->prefix;
			RefPtr<Value_List> pValue(new Value_List());
			stockerStack.GetTop()->Stock(pValue.Reference());
			stockerStack.Push(new Stocker_Sequence(pValue.Reference()));
			break;
		}
		case YAML_DOCUMENT_END_EVENT: {
			int implicit = event.data.document_end.implicit;
			//::printf("DOCUMENT_END\n");
			stockerStack.Pop();
			break;
		}
		case YAML_ALIAS_EVENT: {
			yaml_char_t* anchor = event.data.alias.anchor;
			//::printf("ALIAS %s\n", anchor);
			auto iter = _anchorMap.find(reinterpret_cast<char*>(anchor));
			if (iter == _anchorMap.end()) {
				Error::Issue(ErrorType::FormatError, "undefined anchor %s", anchor);
				return nullptr;
			} else {
				stockerStack.GetTop()->Stock(iter->second->Reference());
			}
			break;
		}
		case YAML_SCALAR_EVENT: {
			yaml_char_t* anchor = event.data.scalar.anchor;
			yaml_char_t* tag = event.data.scalar.tag;
			yaml_char_t* valueRaw = event.data.scalar.value;
			size_t length = event.data.scalar.length;
			int plain_implicit = event.data.scalar.plain_implicit;
			int quoted_implicit = event.data.scalar.quoted_implicit;
			yaml_scalar_style_t style = event.data.scalar.style;
			//::printf("SCALAR %s %s\n", anchor, tag);
			RefPtr<Value_String> pValue(new Value_String(String(reinterpret_cast<char*>(valueRaw), length)));
			stockerStack.GetTop()->Stock(pValue.Reference());
			if (anchor) _anchorMap[reinterpret_cast<char *>(anchor)] = pValue.release();
			break;
		}
		case YAML_SEQUENCE_START_EVENT: {
			yaml_char_t* anchor = event.data.sequence_start.anchor;
			yaml_char_t* tag = event.data.sequence_start.tag;
			int implicit = event.data.sequence_start.implicit;
			yaml_sequence_style_t style = event.data.sequence_start.style;
			//::printf("SEQUENCE_START %s %s\n", anchor, tag);
			RefPtr<Value_List> pValue(new Value_List());
			stockerStack.GetTop()->Stock(pValue.Reference());
			stockerStack.Push(new Stocker_Sequence(pValue.Reference()));
			if (anchor) _anchorMap[reinterpret_cast<char *>(anchor)] = pValue.release();
			break;
		}
		case YAML_SEQUENCE_END_EVENT:
			//::printf("SEQUENCE_END\n");
			stockerStack.Pop();
			break;
		case YAML_MAPPING_START_EVENT: {
			yaml_char_t* anchor = event.data.mapping_start.anchor;
			yaml_char_t* tag = event.data.mapping_start.tag;
			int implicit = event.data.mapping_start.implicit;
			yaml_mapping_style_t style = event.data.mapping_start.style;
			//::printf("MAPPING_START %s %s\n", anchor, tag);
			RefPtr<Value_Dict> pValue(new Value_Dict());
			stockerStack.GetTop()->Stock(pValue.Reference());
			stockerStack.Push(new Stocker_Mapping(pValue.Reference()));
			if (anchor) _anchorMap[reinterpret_cast<char *>(anchor)] = pValue.release();
			break;
		}
		case YAML_MAPPING_END_EVENT:
			//::printf("MAPPING_END\n");
			stockerStack.Pop();
			break;
		default:
			Error::Issue(ErrorType::FormatError, "unknown event %d\n", event.type);
			return nullptr;
		}
		::yaml_event_delete(&event);
	}
	stockerStack.Pop();
	return pValueRtn.release();
}

int Parser::ReadHandler(void* ext, char* buffer, int size, int* length)
{
	Parser& parser = *reinterpret_cast<Parser*>(ext);
	*length = parser.GetStream().Read(buffer, size);
	return Error::IsIssued()? 0 : 1;
}

String Parser::ToString(const StringStyle& ss) const
{
	return String().Format("yaml.Parser");
}

//------------------------------------------------------------------------------
// Parser::Stocker
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Parser::Stocker_Mapping
//------------------------------------------------------------------------------
void Parser::Stocker_Mapping::Stock(Value* pValue)
{
	if (_keyFlag) {
		_pValueKey.reset(pValue);
	} else {
		_pValueDict->GetValueDict().Assign(_pValueKey.release(), pValue);
	}
	_keyFlag = !_keyFlag;
}

//------------------------------------------------------------------------------
// Parser::Stocker_Sequence
//------------------------------------------------------------------------------
void Parser::Stocker_Sequence::Stock(Value* pValue)
{
	_pValueList->GetValueTypedOwner().Add(pValue);
}

Gurax_EndModuleScope(yaml)
