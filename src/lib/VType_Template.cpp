//==============================================================================
// VType_Template.cpp
//==============================================================================
#include "stdafx.h"
#include "gurax/VType_Template.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Template(src?:Stream:r):map:[lasteol,noindent] {block}
Gurax_DeclareFunction(Template)
{
	Declare(VTYPE_Template, Flag::Map);
	DeclareArg("src", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
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
	Stream* pStreamSrc = args.IsValid()? &args.Pick<Value_Stream>().GetStream() : nullptr;
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noindent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lasteol));
	// Function body
	RefPtr<Template> pTmpl(new Template());
	if (pStreamSrc && !pTmpl->ParseStream(*pStreamSrc, autoIndentFlag, appendLastEOLFlag)) {
		return Value::nil();
	}
	return ReturnValue(processor, argument, new Value_Template(pTmpl.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Template#Parse(str:String):void:[lasteol,noindent]
Gurax_DeclareMethod(Template, Parse)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(noindent));
	DeclareAttrOpt(Gurax_Symbol(lasteol));
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `template` instance by parsing a script-embedded text in a string.\n"
		"\n"
		"Following attributes would customize the parser's behavior:\n"
		"\n"
		"- `:lasteol`\n"
		"- `:noindent`\n");
}

Gurax_ImplementMethod(Template, Parse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noindent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lasteol));
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	// Function body
	tmpl.ParseString(str, autoIndentFlag, appendLastEOLFlag);
	return Value::nil();
}

// Template#Read(src:Stream:r):void:[lasteol,noindent]
Gurax_DeclareMethod(Template, Read)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareAttrOpt(Gurax_Symbol(noindent));
	DeclareAttrOpt(Gurax_Symbol(lasteol));
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `template` instance by parsing a script-embedded text from a stream.\n"
		"\n"
		"Following attributes would customize the parser's behavior:\n"
		"\n"
		"- `:lasteol`\n"
		"- `:noindent`\n");
}

Gurax_ImplementMethod(Template, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noindent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lasteol));
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.Pick<Value_Stream>().GetStream();
	// Function body
	tmpl.ParseStream(streamSrc, autoIndentFlag, appendLastEOLFlag);
	return Value::nil();
}

// Template#Render(dst?:Stream:w)
Gurax_DeclareMethod(Template, Render)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Renders stored content to the specified stream.\n"
		"\n"
		"If the stream is omitted, the function returns the rendered result as a string.\n");
}

Gurax_ImplementMethod(Template, Render)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	Stream* pStreamDst = args.IsValid()? &args.Pick<Value_Stream>().GetStream() : nullptr;
	// Function body
	if (pStreamDst) {
		tmpl.Render(*pStreamDst);
		return Value::nil();
	} else {
		RefPtr<Stream_Binary> pStreamDst(new Stream_Binary());
		tmpl.Render(*pStreamDst);
		return new Value_String(pStreamDst->GetBuff().ConvertToString());
	}
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Template#expr
Gurax_DeclareProperty_R(Template, expr)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance that represents parsed expressions of the template body.");
}

Gurax_ImplementPropertyGetter(Template, expr)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Expr(valueThis.GetTemplate().GetExprForBody().Reference());
}

// Template#exprForInit
Gurax_DeclareProperty_R(Template, exprForInit)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance that represents parsed expressions of the template's initialization part.");
}

Gurax_ImplementPropertyGetter(Template, exprForInit)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Expr(valueThis.GetTemplate().GetExprForInit().Reference());
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
	Assign(Gurax_CreateMethod(Template, Parse));
	Assign(Gurax_CreateMethod(Template, Read));
	Assign(Gurax_CreateMethod(Template, Render));
	// Assignment of property
	Assign(Gurax_CreateProperty(Template, expr));
	Assign(Gurax_CreateProperty(Template, exprForInit));
}

//------------------------------------------------------------------------------
// Value_Template
//------------------------------------------------------------------------------
VType& Value_Template::vtype = VTYPE_Template;

}
