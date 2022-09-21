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

// yaml.Read(stream as Stream)
Gurax_DeclareFunction(Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Read)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Parser> pParser(new Parser(stream.Reference()));
	RefPtr<Value> pValue(pParser->Parse());
	if (pValue) return pValue.release();
	return nullptr;
}

// yaml.Write(stream:w as Stream, value)
Gurax_DeclareFunction(Write)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::StreamW);
	DeclareArg("value", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Write)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	const Value& value = args.PickValue();
	// Function body
	RefPtr<Emitter> pEmitter(new Emitter(stream.Reference()));
	if (!pEmitter->EmitStreamStart()) return Value::nil();
	if (!pEmitter->EmitDocumentStart()) return Value::nil();
	if (!pEmitter->Emit(value)) return Value::nil();
	if (!pEmitter->EmitDocumentEnd()) return Value::nil();
	if (!pEmitter->EmitStreamEnd()) return Value::nil();
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
	Assign(Gurax_CreateFunction(Read));
	Assign(Gurax_CreateFunction(Write));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(yaml)
