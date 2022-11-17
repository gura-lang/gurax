//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(yaml)

const char* GetYAMLErrorText(yaml_error_type_e error)
{
	static const struct {
		yaml_error_type_e error;
		const char* str;
	} tbl[] = {
		{ YAML_MEMORY_ERROR,	"Cannot allocate or reallocate a block of memory."	},
		{ YAML_READER_ERROR,	"Cannot read or decode the input stream."			},
		{ YAML_SCANNER_ERROR,	"Cannot scan the input stream."						},
		{ YAML_PARSER_ERROR,	"Cannot parse the input stream."					},
		{ YAML_COMPOSER_ERROR,	"Cannot compose a YAML document."					},
		{ YAML_WRITER_ERROR,	"Cannot write to the output stream."				},
		{ YAML_EMITTER_ERROR,	"Cannot emit a YAML stream."						},
	};
	for (int i = 0; i < Gurax_ArraySizeOf(tbl); i++) {
		if (tbl[i].error == error) return tbl[i].str;
	}
	return "unknown error";
}

Gurax_EndModuleScope(yaml)
