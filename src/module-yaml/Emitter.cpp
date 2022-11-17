//==============================================================================
// Emitter.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(yaml)

//------------------------------------------------------------------------------
// Emitter
//------------------------------------------------------------------------------
Emitter::Emitter(Stream* pStream, bool jsonFlag) : _pStream(pStream),
	_sequence_style(jsonFlag? YAML_FLOW_SEQUENCE_STYLE : YAML_ANY_SEQUENCE_STYLE),
	_mapping_style(jsonFlag? YAML_FLOW_MAPPING_STYLE : YAML_ANY_MAPPING_STYLE),
	_scalar_style_String(jsonFlag? YAML_DOUBLE_QUOTED_SCALAR_STYLE : YAML_ANY_SCALAR_STYLE)
{
	::yaml_emitter_initialize(&_emitter);
	::yaml_emitter_set_output(&_emitter, reinterpret_cast<yaml_write_handler_t*>(WriteHandler), this);
}

Emitter::~Emitter()
{
	::yaml_emitter_delete(&_emitter);
}

bool Emitter::EmitStreamStart()
{
	yaml_encoding_t encoding = YAML_UTF8_ENCODING;
	yaml_event_t event;
	::yaml_stream_start_event_initialize(&event, encoding);
	if (::yaml_emitter_emit(&_emitter, &event)) return true;
	Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
	return false;
}

bool Emitter::EmitStreamEnd()
{
	yaml_event_t event;
	::yaml_stream_end_event_initialize(&event);
	if (::yaml_emitter_emit(&_emitter, &event)) return true;
	Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
	return false;
}

bool Emitter::EmitDocumentStart()
{
	yaml_version_directive_t* version_directive = nullptr;
	yaml_tag_directive_t* tag_start = nullptr;
	yaml_tag_directive_t* tag_end = nullptr;
	int implicit = 1;
	yaml_event_t event;
	::yaml_document_start_event_initialize(&event, version_directive, tag_start, tag_end, implicit);
	if (::yaml_emitter_emit(&_emitter, &event)) return true;
	Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
	return false;
}

bool Emitter::EmitDocumentEnd()
{
	int implicit = 1;
	yaml_event_t event;
	::yaml_document_end_event_initialize(&event, implicit);
	if (::yaml_emitter_emit(&_emitter, &event)) return true;
	Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
	return false;
}

bool Emitter::EmitGeneric(const Value& value)
{
	if (value.IsType(VTYPE_List)) {
		return EmitSequence(Value_List::GetValueOwner(value));
	} else if (value.IsType(VTYPE_Tuple)) {
		return EmitSequence(Value_Tuple::GetValueOwner(value));
	} else if (value.IsType(VTYPE_Dict)) {
		return EmitMapping(Value_Dict::GetValueDict(value));
	} else if (value.IsType(VTYPE_String)) {
		return EmitScalar(Value_String::GetStringSTL(value), _scalar_style_String);
	} else if (value.IsType(VTYPE_Number)) {
		return EmitScalar(value.ToString(), YAML_LITERAL_SCALAR_STYLE);
	} else {
		return EmitScalar(value.ToString(), _scalar_style_String);
	}
}

bool Emitter::EmitSequence(const ValueList& valueList)
{
	do {
		yaml_char_t* anchor = nullptr;
		yaml_char_t* tag = nullptr;
		int implicit = 0;
		yaml_event_t event;
		::yaml_sequence_start_event_initialize(&event, anchor, tag, implicit, _sequence_style);
		if (!::yaml_emitter_emit(&_emitter, &event)) {
			Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
			return false;
		}
	} while (0);
	for (Value* pValueEach : valueList) {
		if (!EmitGeneric(*pValueEach)) return false;
	}
	do {
		yaml_event_t event;
		::yaml_sequence_end_event_initialize(&event);
		if (!::yaml_emitter_emit(&_emitter, &event)) {
			Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
			return false;
		}
	} while (0);
	return true;
}

bool Emitter::EmitMapping(const ValueDict& valueDict)
{
	do {
		yaml_char_t* anchor = nullptr;
		yaml_char_t* tag = nullptr;
		int implicit = 0;
		yaml_event_t event;
		::yaml_mapping_start_event_initialize(&event, anchor, tag, implicit, _mapping_style);
		if (!::yaml_emitter_emit(&_emitter, &event)) {
			return false;
		}
	} while (0);
	for (auto pair : valueDict.GetMap()) {
		if (!EmitGeneric(*pair.first) || !EmitGeneric(*pair.second)) return false;
	}
	do {
		yaml_event_t event;
		::yaml_mapping_end_event_initialize(&event);
		if (!::yaml_emitter_emit(&_emitter, &event)) {
			Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
			return false;
		}
	} while (0);
	return true;
}

bool Emitter::EmitScalar(const String& str, yaml_scalar_style_t style)
{
	yaml_char_t* anchor = nullptr;
	yaml_char_t* tag = nullptr;
	yaml_char_t* value = reinterpret_cast<yaml_char_t*>(const_cast<char*>(str.c_str()));
	size_t length = str.size();
	int plain_implicit = 1;
	int quoted_implicit = 1;
	yaml_event_t event;
	::yaml_scalar_event_initialize(&event, anchor, tag, value, length, plain_implicit, quoted_implicit, style);
	if (!::yaml_emitter_emit(&_emitter, &event)) {
		Error::Issue(ErrorType::FormatError, "%s", GetYAMLErrorText(_emitter.error));
		return false;
	}
	return true;
}

int Emitter::WriteHandler(void* ext, unsigned char* buffer, size_t size)
{
	Emitter& emitter = *reinterpret_cast<Emitter*>(ext);
	emitter.GetStream().Write(buffer, size);
	return Error::IsIssued()? 0 : 1;
}

String Emitter::ToString(const StringStyle& ss) const
{
	return String().Format("yaml.Emitter");
}

Gurax_EndModuleScope(yaml)
