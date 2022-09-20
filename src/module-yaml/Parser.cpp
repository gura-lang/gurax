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
}

Parser::~Parser()
{
	yaml_parser_delete(&_parser);
}

Value* Parser::Parse()
{
#if 0
	RefPtr<Value_List> pValueList(new Value_List());
	StockerList stockerList;
	yaml_event_t event;
	for (bool contFlag = true; contFlag; ) {
		if (!::yaml_parser_parse(&_parser, &event)) {
			Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_parser.error));
			break;
		}
		if (event.type == YAML_STREAM_START_EVENT) {
			//::printf("STREAM_START\n");
			//yaml_encoding_t encoding = event.data.stream_start.encoding;
		} else if (event.type == YAML_DOCUMENT_START_EVENT) {
			//yaml_version_directive_t *version_directive = event.data.document_start.version_directive;
			//yaml_tag_directive_t *tag_start = event.data.document_start.tag_directives.start;
			//yaml_tag_directive_t *tag_end = event.data.document_start.tag_directives.end;
			//int implicit = event.data.document_start.implicit;
			//::printf("DOCUMENT_START %p %p %p\n",
			//					version_directive, tag_start, tag_end);
			//tag_start->handle;
			//tag_start->prefix;
			//tag_end->handle;
			//tag_end->prefix;
		} else if (event.type == YAML_SCALAR_EVENT ||
					event.type == YAML_SEQUENCE_START_EVENT ||
					event.type == YAML_MAPPING_START_EVENT) {
			yaml_char_t *anchor = nullptr;
			yaml_char_t *tag = nullptr;
			RefPtr<Value> pValue;
			//Stocker *pStockerTop = stockerList.empty()? nullptr : stockerList.back();
			Stocker* pStockerTop = stockerList.back();
			if (event.type == YAML_SCALAR_EVENT) {
				anchor = event.data.scalar.anchor;
				tag = event.data.scalar.tag;
				yaml_char_t* valueRaw = event.data.scalar.value;
				size_t length = event.data.scalar.length;
				int plain_implicit = event.data.scalar.plain_implicit;
				int quoted_implicit = event.data.scalar.quoted_implicit;
				yaml_scalar_style_t style = event.data.scalar.style;
				String valueStr(reinterpret_cast<char*>(valueRaw), length);
				//::printf("SCALAR %s %s %s\n", anchor, tag, valueStr.c_str());
				pValue.reset(new Value_String(valueStr));
			} else if (event.type == YAML_SEQUENCE_START_EVENT) {
				anchor = event.data.sequence_start.anchor;
				tag = event.data.sequence_start.tag;
				int implicit = event.data.sequence_start.implicit;
				yaml_sequence_style_t style = event.data.sequence_start.style;
				//::printf("SEQUENCE_START %s %s\n", anchor, tag);
				Stocker *pStocker = new Stocker_Sequence(env);
				stockerList.push_back(pStocker);
				value = pStocker->GetValue();
			} else { // event.type == YAML_MAPPING_START_EVENT
				anchor = event.data.mapping_start.anchor;
				tag = event.data.mapping_start.tag;
				int implicit = event.data.mapping_start.implicit;
				yaml_mapping_style_t style = event.data.mapping_start.style;
				//::printf("MAPPING_START %s %s\n", anchor, tag);
				Stocker *pStocker = new Stocker_Mapping(env);
				stockerList.push_back(pStocker);
				value = pStocker->GetValue();
			}
			if (pStockerTop == nullptr) {
				result = value;
			} else {
				pStockerTop->Stock(value);
			}
			if (anchor != nullptr) {
				anchorMap[reinterpret_cast<char *>(anchor)] = value;
			}
		} else if (event.type == YAML_ALIAS_EVENT) {
			yaml_char_t *anchor = event.data.alias.anchor;
			//::printf("ALIAS\ %s\n", anchor);
			AnchorMap::iterator iter =
							anchorMap.find(reinterpret_cast<char *>(anchor));
			if (iter == anchorMap.end()) {
				sig.SetError(ERR_FormatError, "undefined anchor %s", anchor);
				contFlag = false;
			} else if (stockerList.empty()) {
				// something's wrong
			} else {
				stockerList.back()->Stock(iter->second);
			}
		} else if (event.type == YAML_STREAM_END_EVENT) {
			//::printf("STREAM_END\n");
			contFlag = false;
		} else if (event.type == YAML_DOCUMENT_END_EVENT) {
			int implicit = event.data.document_end.implicit;
			//::printf("DOCUMENT_END\n");
			contFlag = false;
		} else if (event.type == YAML_SEQUENCE_END_EVENT) {
			//::printf("SEQUENCE_END\n");
			stockerList.pop_back();
		} else if (event.type == YAML_MAPPING_END_EVENT) {
			//::printf("MAPPING_END\n");
			stockerList.pop_back();
		} else {
			sig.SetError(ERR_FormatError, "unknown event %d\n", event.type);
			contFlag = false;
		}
		::yaml_event_delete(&event);
	}
	if (sig.IsSignalled()) return Value::Nil;
	return result;
#endif
	return nullptr;
}

String Parser::ToString(const StringStyle& ss) const
{
	return String().Format("yaml.Parser");
}

Gurax_EndModuleScope(yaml)
