//==============================================================================
// module-yaml.cpp
//==============================================================================
#include "stdafx.h"
#include <yaml.h>
Gurax_BeginModule(yaml)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// yaml.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

int read_handler(void *ext, char *buffer, int size, int *length)
{
	/* ... */
	//*buffer = ...;
	//*length = ...;
	///* ... */
	//return error ? 0 : 1;
	return 0;
}

Gurax_ImplementFunction(Test)
{
	yaml_parser_t parser;
	yaml_event_t event;

	int done = 0;

	/* Create the Parser object. */
	yaml_parser_initialize(&parser);

	/* Set a string input. */
	//char *input = "...";
	//size_t length = strlen(input);
	//
	//yaml_parser_set_input_string(&parser, input, length);

	/* Set a file input. */
	FILE *input = fopen("...", "rb");
	
	yaml_parser_set_input_file(&parser, input);

	/* Set a generic reader. */
	//void *ext = "";
	//
	//yaml_parser_set_input(&parser, read_handler, ext);

	/* Read the event sequence. */
	while (!done) {

	    /* Get the next event. */
	    if (!yaml_parser_parse(&parser, &event))
	        return Value::nil();

	    /*
	      ...
	      Process the event.
	      ...
	    */

	    /* Are we finished? */
	    done = (event.type == YAML_STREAM_END_EVENT);

	    /* The application is responsible for destroying the event object. */
	    yaml_event_delete(&event);

	}

	/* Destroy the Parser object. */
	yaml_parser_delete(&parser);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(yaml)
