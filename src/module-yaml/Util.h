//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_YAML_UTIL_H
#define GURAX_MODULE_YAML_UTIL_H
#include <gurax.h>
#include <yaml.h>

Gurax_BeginModuleScope(yaml)

const char* GetYAMLErrorText(yaml_error_type_e error);

Gurax_EndModuleScope(yaml)

#endif
