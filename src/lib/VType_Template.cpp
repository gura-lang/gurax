//==============================================================================
// VType_Template.cpp
//==============================================================================
#include "stdafx.h"
#include "gurax/VType_Template.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Template(src:Stream:r):map:[lasteol,noindent] {block}
Gurax_DeclareFunction(Template)
{
	Declare(VTYPE_Template, Flag::Map);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::Once);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `template` instance.\n"
		"\n"
		"If the stream `src` is specified, the instance would be initialized\n"
		"with the parsed result of the script-embedded text from the stream.\n"
		"\n"
		"Following attributes would customize the parser's behavior:\n"
		"\n"
		"- `:lasteol`\n"
		"- `:noindent`\n");
}

Gurax_ImplementFunction(Template)
{
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.Pick<Value_Stream>().GetStream();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noindent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lasteol));
	// Function body
	RefPtr<Template> pTmpl(new Template());
	if (!pTmpl->ParseStream(streamSrc, autoIndentFlag, appendLastEOLFlag)) return Value::nil();
	return ReturnValue(processor, argument, new Value_Template(pTmpl.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Template#Render(dst?:Stream:w)
Gurax_DeclareMethod(Template, Render)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Renders stored content to the specified stream.\n"
		"\n"
		"If the stream is omitted, the function returns the rendered result as a string.\n");
}

Gurax_ImplementMethod(Template, Render)
{
#if 0
	Template *pTemplate = Object_template::GetObjectThis(arg)->GetTemplate();
	if (arg.Is_stream(0)) {
		Stream &streamDst = arg.GetStream(0);
		pTemplate->Render(env, &streamDst);
		return Value::Nil;
	} else {
		String strDst;
		SimpleStream_StringWriter streamDst(strDst);
		if (!pTemplate->Render(env, &streamDst)) return Value::Nil;
		return Value(strDst);
	}
#endif
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Template
//------------------------------------------------------------------------------
VType_Template VTYPE_Template("Template");

void VType_Template::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Template));
	// Assignment of method
	Assign(Gurax_CreateMethod(Template, Render));
}

//------------------------------------------------------------------------------
// Value_Template
//------------------------------------------------------------------------------
VType& Value_Template::vtype = VTYPE_Template;

}
