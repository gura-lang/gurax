//==============================================================================
// module-xml.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(xml)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// xml.Parse(text as String) {block?}
Gurax_DeclareFunction(Parse)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementFunction(Parse)
{
	// Arguments
	ArgPicker args(argument);
	const StringReferable& text = args.PickStringReferable();
	// Function body
	RefPtr<Stream> pStream(new Stream_StringReader(text.Reference()));
	RefPtr<Parser> pParser(new Parser());
	if (!pParser->Parse(*pStream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Document(pParser->GetDocument().Reference()));
}

// xml.Read(stream as Stream) {block?}
Gurax_DeclareFunction(Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementFunction(Read)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Parser> pParser(new Parser());
	if (!pParser->Parse(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Document(pParser->GetDocument().Reference()));
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
	// Assignment of VType
	Assign(VTYPE_Attr);
	Assign(VTYPE_Attrs);
	Assign(VTYPE_CData);
	Assign(VTYPE_Comment);
	Assign(VTYPE_Document);
	Assign(VTYPE_Element);
	Assign(VTYPE_Node);
	Assign(VTYPE_Nodes);
	Assign(VTYPE_Text);
	Assign(VTYPE_XmlDecl);
	// Assignment of function
	Assign(Gurax_CreateFunction(Parse));
	Assign(Gurax_CreateFunction(Read));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(xml)
