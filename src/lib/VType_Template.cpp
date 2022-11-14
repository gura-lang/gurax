//==============================================================================
// VType_Template.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Template, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Template, `en)}

${help.ComposeMethodHelp(Template, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Template(src?:Stream:r):map:[lastEol,noIndent] {block}
Gurax_DeclareConstructor(Template)
{
	Declare(VTYPE_Template, Flag::Map);
	DeclareArg("src", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `template` instance.

If the stream `src` is specified, the instance would be initialized
with the parsed result of the script-embedded text from the stream.

Following attributes would customize the parser's behavior:

- `:lastEol`
- `:noIndent`
)**");
}

Gurax_ImplementConstructor(Template)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStreamSrc = args.IsValid()? &args.PickStream() : nullptr;
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noIndent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lastEol));
	// Function body
	RefPtr<Template> pTmpl(new Template());
	if (pStreamSrc &&
		(!pTmpl->ParseStream(*pStreamSrc, autoIndentFlag, appendLastEOLFlag) ||
		 !pTmpl->PrepareAndCompose())) return Value::nil();
	return argument.ReturnValue(processor, new Value_Template(pTmpl.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Template#Eval()
Gurax_DeclareMethod(Template, Eval)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(
Evaluates the template and returns the rendered string.
)**");
}

Gurax_ImplementMethod(Template, Eval)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Function body
	String strDst;
	if (!tmpl.Render(processor, strDst)) return Value::nil();
	return new Value_String(strDst);
}

// Template#Parse(str:String):reduce:[lastEol,noIndent]
Gurax_DeclareMethod(Template, Parse)
{
	Declare(VTYPE_Template, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(noIndent));
	DeclareAttrOpt(Gurax_Symbol(lastEol));
	AddHelp("en", u8R"**(
Creates a `template` instance by parsing a script-embedded text in a string.

Following attributes would customize the parser's behavior:

- `:lastEol`
- `:noIndent`
)**");
}

Gurax_ImplementMethod(Template, Parse)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noIndent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lastEol));
	// Function body
	if (!tmpl.ParseString(str, autoIndentFlag, appendLastEOLFlag) ||
		!tmpl.PrepareAndCompose()) return Value::nil();
	return valueThis.Reference();
}

// Template#Read(src:Stream:r):reduce:[lastEol,noIndent]
Gurax_DeclareMethod(Template, Read)
{
	Declare(VTYPE_Template, Flag::Reduce);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareAttrOpt(Gurax_Symbol(noIndent));
	DeclareAttrOpt(Gurax_Symbol(lastEol));
	AddHelp("en", u8R"**(
Creates a `template` instance by parsing a script-embedded text from a stream.

Following attributes would customize the parser's behavior:

- `:lastEol`
- `:noIndent`
)**");
}

Gurax_ImplementMethod(Template, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noIndent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lastEol));
	// Function body
	if (!tmpl.ParseStream(streamSrc, autoIndentFlag, appendLastEOLFlag) ||
		!tmpl.PrepareAndCompose()) return Value::nil();
	return valueThis.Reference();
}

// Template#Render(dst?:Stream:w):void
Gurax_DeclareMethod(Template, Render)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp("en", u8R"**(
Renders stored content to the specified stream.

If the argument is omitted, it would be rendered to the standard output.
)**");
}

Gurax_ImplementMethod(Template, Render)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	Stream& streamDst = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	// Function body
	tmpl.Render(processor, streamDst);
	return Value::nil();
#if 0
	String strDst;
	if (!tmpl.Render(processor, strDst)) return Value::nil();
#endif
}

//-----------------------------------------------------------------------------
// Implementation of directive methods
//-----------------------------------------------------------------------------
// Template#block(symbol:symbol):void
Gurax_DeclareMethod(Template, block)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Creates a template block which content is supposed to be replaced by a derived template.

This method is called by template directive `${=block()}`
during both the initialization and presentation phase of a template process.

- **Initialization:** Creates a template block from the specified block
  that is then registered in the current template with the specified symbol.
- **Presentation:** Evaluates a template block registered with the specified symbol.

Consider an example.
Assume that a block associated with symbol `` `foo`` is declared
in a template file named `base.tmpl` as below:

`[base.tmpl]`

    Block begins here.
    ${=block(`foo)}
    Content of base.
    ${end}
    Block ends here.

This template renders the following result:

    Block begins here.
    Content of derived.
    Block ends here.

Below is another template named `derived.tmpl` that devies from `base.tmpl`
and overrides the block `` `foo``.

`[derived.tmpl]`

    ${=extends('base.tmpl')}
    
    ${=block(`foo)}
    Content of derived.
    ${end}

This template renders the following result:

    Block begins here.
    Content of derived.
    Block ends here.
)**");
}

Gurax_ImplementMethod(Template, block)
{
   	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	const Value* pValue = tmpl.LookupValue(pSymbol);
	if (!pValue || !pValue->IsType(VTYPE_Expr)) return Value::nil();
	const Expr& expr = Value_Expr::GetExpr(*pValue);
	processor.PushFrame<Frame_Block>().Assign(Gurax_Symbol(this_), valueThis.Reference());
	Value::Delete(expr.Eval(processor));
	processor.PopFrame();
	return Value::nil();
}

// Template#call(symbol:symbol, args*)
Gurax_DeclareMethod(Template, call)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp("en", u8R"**(
Calls a template macro that has been created by directive `${=define}`.

This method is called by template directive `${=call()}`
during the presentation phase of a template process.

Below is an exemple to call a template macro:

    ${=call(`show_person, 'Harry', 24)}

This method would return `nil` if a line-break character is rendered at last
and would return a null string otherwise.
)**");
}

Gurax_ImplementMethod(Template, call)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	const ValueList& values = args.PickList();
	// Function body
	const Value* pValue = tmpl.LookupValue(pSymbol);
	if (!pValue || !pValue->IsType(VTYPE_Function)) return Value::nil();
	const Function& function = Value_Function::GetFunction(*pValue);
	RefPtr<Argument> pArgument(new Argument(processor, function));
	do {
		ArgFeeder args(*pArgument, processor.GetFrameCur());
		if (!args.FeedValues(values)) return Value::nil();
	} while (0);
	tmpl.ClearLastChar();
	Value::Delete(function.Eval(processor, *pArgument));
	return (tmpl.GetLastChar() == '\n')? Value::nil() : new Value_String(String::Empty);
}

// Template#define(symbol:symbol, `args*):void
Gurax_DeclareMethod(Template, define)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Quote, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp("en", u8R"**(
Creates a template macro from the specified block,
which is supposed to be called by `${=call}` directive,
and associates it with the specified symbol.

This method is called by template directive `${=define()}`
during the initialization phase of a template process.

Below is an example to create a template macro:

    ${=define(`show_person, name:string, age:number)}
    ${name} is ${age} years old.
    ${end}
)**");
}

Gurax_ImplementMethod(Template, define)
{
	// nothing to do
	return Value::nil();
}

// Template#embed(template:Template)
Gurax_DeclareMethod(Template, embed)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("template", VTYPE_Template, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Renders the specified template at the current position.

This method is called by template directive `${=embed()}`
during the presentation phase of a template process.

Below is an example to embed a template file named `foo.tmpl`.

    ${=embed('foo.tmpl')}

As the template rendered by this method runs in a different context
from the current one, macros and blocks that it defines
are not reflected to the current context.

This method would return `nil` if a line-break character is rendered at last
and would return a null string otherwise.
)**");
}

Gurax_ImplementMethod(Template, embed)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	Template& tmplEmbedded = args.PickTemplate();
	// Function body
	tmplEmbedded.ClearLastChar();
	if (!tmplEmbedded.Render(processor, tmpl.GetStreamDst())) return Value::nil();
	return (tmplEmbedded.GetLastChar() == '\n')? Value::nil() : new Value_String(String::Empty);
}

// Template#extends(template:Template):void
Gurax_DeclareMethod(Template, extends)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("template", VTYPE_Template, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Declares the current template as a derived one from the specified template.

This method is called by template directive `${=extends()}`
during the initialization phase of a template process.

The directive must appear in a template only once.
An error occurs if the current template has already derived from another template.

Below is an example to declare the current template as one derived from `base.tmpl`.

    ${=extends('base.tmpl')}
)**");
}

Gurax_ImplementMethod(Template, extends)
{
	// nothing to do
	return Value::nil();
}

// Template#super(symbol:Symbol):void
Gurax_DeclareMethod(Template, super)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Evaluates a template block registered with the specified symbol in a template
from which the current template has derived.

This method is called by template directive `${=super()}`
during the presentation phase of a template process.
The directive is intended to be used within a directive `${=block()}`.

Consider an example.
Assume that a block associated with symbol `` `foo`` is declared
in a template named `base.tmpl` as below:

`[base.tmpl]`

    Block begins here.
    ${=block(`foo)}
    Content of base.
    ${end}
    Block ends here.

This template renders the following result:

    Block begins here.
    Content of derived.
    Block ends here.

Below is another template named `derived.tmpl` that devies from `base.tmpl`
and overrides the block `` `foo``.

`[derived.tmpl]`

    ${=extends('base.tmpl')}
    
    ${=block(`foo)}
    ${=super(`foo)}
    Content of derived.
    ${end}

This template renders the following result:

    Block begins here.
    Content of base.
    Content of derived.
    Block ends here.
)**");
}

Gurax_ImplementMethod(Template, super)
{
   	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Template* pTmplSuper = tmpl.GetTemplateSuper();
	if (!pTmplSuper) pTmplSuper = &tmpl;
	const Value* pValue = pTmplSuper->LookupValue(pSymbol);
	if (!pValue || !pValue->IsType(VTYPE_Expr)) return Value::nil();
	const Expr& expr = Value_Expr::GetExpr(*pValue);
	processor.PushFrame<Frame_Block>().Assign(Gurax_Symbol(this_), valueThis.Reference());
	Value::Delete(expr.Eval(processor));
	processor.PopFrame();
	return Value::nil();
}

// Template#init_block(symbol:Symbol):void {block}
Gurax_DeclareMethod(Template, init_block)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::Once);
	LinkHelp(VTYPE_Template, Symbol::Add("block"));
}

Gurax_ImplementMethod(Template, init_block)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	tmpl.AssignValue(pSymbol, new Value_Expr(pExprOfBlock->Reference()));
	return Value::nil();
}

// Template#init_call(symbol:Symbol, args*):void
Gurax_DeclareMethod(Template, init_call)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	LinkHelp(VTYPE_Template, Symbol::Add("call"));
}

Gurax_ImplementMethod(Template, init_call)
{
	// nothing to do
	return Value::nil();
}

// Template#init_define(symbol:Symbol, `args*):void {block}
Gurax_DeclareMethod(Template, init_define)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Quote, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::Once);
	LinkHelp(VTYPE_Template, Symbol::Add("define"));
}

Gurax_ImplementMethod(Template, init_define)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	const ValueList& valuesExpr = args.PickList();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	RefPtr<Function> pFunction(Function::CreateDynamicFunction(pSymbol, valuesExpr, *pExprOfBlock));
	if (!pFunction) return Value::nil();
	pFunction->SetFrameOuter(processor.GetFrameCur());
	tmpl.AssignValue(pSymbol, new Value_Function(pFunction.release()));
	return Value::nil();
}

// Template#init_embed(template:Template):void
Gurax_DeclareMethod(Template, init_embed)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("template", VTYPE_Template, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Template, Symbol::Add("embed"));
}

Gurax_ImplementMethod(Template, init_embed)
{
	// nothing to do
	return Value::nil();
}

// Template#init_extends(template:Template):void
Gurax_DeclareMethod(Template, init_extends)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("template", VTYPE_Template, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Template, Symbol::Add("extends"));
}

Gurax_ImplementMethod(Template, init_extends)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	const Template& tmplSuper = args.PickTemplate();
	// Function body
	tmpl.SetTemplateSuper(tmplSuper.Reference());
	return Value::nil();
}

// Template#init_super(symbol:Symbol):void
Gurax_DeclareMethod(Template, init_super)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	LinkHelp(VTYPE_Template, Symbol::Add("super"));
}

Gurax_ImplementMethod(Template, init_super)
{
	// nothing to do
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Template#expr
Gurax_DeclareProperty_R(Template, expr)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
An `Expr` instance that represents parsed expressions of the template body.
)**");
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
	AddHelp("en", u8R"**(
An `Expr` instance that represents parsed expressions of the template's initialization part.
)**");
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
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Template));
	// Assignment of method
	Assign(Gurax_CreateMethod(Template, Eval));
	Assign(Gurax_CreateMethod(Template, Parse));
	Assign(Gurax_CreateMethod(Template, Read));
	Assign(Gurax_CreateMethod(Template, Render));
	// Assignment of directive methods
	Assign(Gurax_CreateMethod(Template, block));
	Assign(Gurax_CreateMethod(Template, call));
	Assign(Gurax_CreateMethod(Template, define));
	Assign(Gurax_CreateMethod(Template, embed));
	Assign(Gurax_CreateMethod(Template, extends));
	Assign(Gurax_CreateMethod(Template, super));
	Assign(Gurax_CreateMethod(Template, init_block));
	Assign(Gurax_CreateMethod(Template, init_call));
	Assign(Gurax_CreateMethod(Template, init_define));
	Assign(Gurax_CreateMethod(Template, init_embed));
	Assign(Gurax_CreateMethod(Template, init_extends));
	Assign(Gurax_CreateMethod(Template, init_super));
	// Assignment of property
	Assign(Gurax_CreateProperty(Template, expr));
	Assign(Gurax_CreateProperty(Template, exprForInit));
}

Value* VType_Template::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	RefPtr<Value_Stream> pValueCasted(value.Cast<Value_Stream>(flags));
	if (!pValueCasted) return nullptr;
	RefPtr<Template> pTmpl(new Template());
	bool autoIndentFlag = true;
	bool appendLastEOLFlag = false;
	if ((!pTmpl->ParseStream(pValueCasted->GetStream(), autoIndentFlag, appendLastEOLFlag) ||
		 !pTmpl->PrepareAndCompose())) return Value::nil();
	return new Value_Template(pTmpl.release());
}

//------------------------------------------------------------------------------
// Value_Template
//------------------------------------------------------------------------------
VType& Value_Template::vtype = VTYPE_Template;

String Value_Template::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTemplate().ToString(ss));
}

}
