//==============================================================================
// VType_Template.cpp
//==============================================================================
#include "stdafx.h"

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
	if (pStreamSrc &&
		(!pTmpl->ParseStream_(*pStreamSrc, autoIndentFlag, appendLastEOLFlag) ||
		 !pTmpl->PrepareAndCompose())) return Value::nil();
	return argument.ReturnValue(processor, new Value_Template(pTmpl.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Template#Parse(str:String):reduce:[lasteol,noindent]
Gurax_DeclareMethod(Template, Parse)
{
	Declare(VTYPE_Template, Flag::Reduce);
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
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noindent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lasteol));
	// Function body
	if (!tmpl.ParseString_(str, autoIndentFlag, appendLastEOLFlag) ||
		!tmpl.PrepareAndCompose()) return Value::nil();
	return valueThis.Reference();
}

// Template#Read(src:Stream:r):reduce:[lasteol,noindent]
Gurax_DeclareMethod(Template, Read)
{
	Declare(VTYPE_Template, Flag::Reduce);
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
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.Pick<Value_Stream>().GetStream();
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noindent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lasteol));
	// Function body
	if (!tmpl.ParseStream_(streamSrc, autoIndentFlag, appendLastEOLFlag) ||
		!tmpl.PrepareAndCompose()) return Value::nil();
	return valueThis.Reference();
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
		tmpl.Render(processor, *pStreamDst);
		return Value::nil();
	} else {
		String strDst;
		if (!tmpl.Render(processor, strDst)) return Value::nil();
		return new Value_String(strDst);
	}
}

//-----------------------------------------------------------------------------
// Implementation of directive methods
//-----------------------------------------------------------------------------
// Template#block(symbol:symbol):void
Gurax_DeclareMethod(Template, block)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a template block which content is supposed to be replaced by a derived template.\n"
		"\n"
		"This method is called by template directive `${=block()}`\n"
		"during both the initialization and presentation phase of a template process.\n"
		"\n"
		"- **Initialization:** Creates a template block from the specified block\n"
		"  that is then registered in the current template with the specified symbol.\n"
		"- **Presentation:** Evaluates a template block registered with the specified symbol.\n"
		"\n"
		"Consider an example.\n"
		"Assume that a block associated with symbol `` `foo`` is declared\n"
		"in a template file named `base.tmpl` as below:\n"
		"\n"
		"`[base.tmpl]`\n"
		"\n"
		"    Block begins here.\n"
		"    ${=block(`foo)}\n"
		"    Content of base.\n"
		"    ${end}\n"
		"    Block ends here.\n"
		"\n"
		"This template renders the following result:\n"
		"\n"
		"    Block begins here.\n"
		"    Content of derived.\n"
		"    Block ends here.\n"
		"\n"
		"Below is another template named `derived.tmpl` that devies from `base.tmpl`\n"
		"and overrides the block `` `foo``.\n"
		"\n"
		"`[derived.tmpl]`\n"
		"\n"
		"    ${=extends('base.tmpl')}\n"
		"    \n"
		"    ${=block(`foo)}\n"
		"    Content of derived.\n"
		"    ${end}\n"
		"\n"
		"This template renders the following result:\n"
		"\n"
		"    Block begins here.\n"
		"    Content of derived.\n"
		"    Block ends here.\n");
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
	processor.EvalExpr(expr);
	processor.PopFrame();
	return Value::nil();
}

// Template#call(symbol:symbol, args*)
Gurax_DeclareMethod(Template, call)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Calls a template macro that has been created by directive `${=define}`.\n"
		"\n"
		"This method is called by template directive `${=call()}`\n"
		"during the presentation phase of a template process.\n"
		"\n"
		"Below is an exemple to call a template macro:\n"
		"\n"
		"    ${=call(`show_person, 'Harry', 24)}\n"
		"\n"
		"This method would return `nil` if a line-break character is rendered at last\n"
		"and would return a null string otherwise.\n");
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
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgument(new Argument(function));
	do {
		ArgFeeder args(*pArgument);
		if (!args.FeedValues(frame, values)) return Value::nil();
	} while (0);
	tmpl.ClearLastChar();
	function.DoEvalVoid(processor, *pArgument);
	return (tmpl.GetLastChar() == '\n')? Value::nil() : new Value_String(String::Empty);
}

// Template#define(symbol:symbol, `args*):void
Gurax_DeclareMethod(Template, define)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Quote, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a template macro from the specified block,\n"
		"which is supposed to be called by `${=call}` directive,\n"
		"and associates it with the specified symbol.\n"
		"\n"
		"This method is called by template directive `${=define()}`\n"
		"during the initialization phase of a template process.\n"
		"\n"
		"Below is an example to create a template macro:\n"
		"\n"
		"    ${=define(`show_person, name:string, age:number)}\n"
		"    ${name} is ${age} years old.\n"
		"    ${end}\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Renders the specified template at the current position.\n"
		"\n"
		"This method is called by template directive `${=embed()}`\n"
		"during the presentation phase of a template process.\n"
		"\n"
		"Below is an example to embed a template file named `foo.tmpl`.\n"
		"\n"
		"    ${=embed('foo.tmpl')}\n"
		"\n"
		"As the template rendered by this method runs in a different context\n"
		"from the current one, macros and blocks that it defines\n"
		"are not reflected to the current context.\n"
		"\n"
		"This method would return `nil` if a line-break character is rendered at last\n"
		"and would return a null string otherwise.\n");
}

Gurax_ImplementMethod(Template, embed)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Template& tmpl = valueThis.GetTemplate();
	// Arguments
	ArgPicker args(argument);
	Template& tmplEmbedded = args.Pick<Value_Template>().GetTemplate();
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
	AddHelp(
		Gurax_Symbol(en),
		"Declares the current template as a derived one from the specified template.\n"
		"\n"
		"This method is called by template directive `${=extends()}`\n"
		"during the initialization phase of a template process.\n"
		"\n"
		"The directive must appear in a template only once.\n"
		"An error occurs if the current template has already derived from another template.\n"
		"\n"
		"Below is an example to declare the current template as one derived from `base.tmpl`.\n"
		"\n"
		"    ${=extends('base.tmpl')}\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Evaluates a template block registered with the specified symbol in a template\n"
		"from which the current template has derived.\n"
		"\n"
		"This method is called by template directive `${=super()}`\n"
		"during the presentation phase of a template process.\n"
		"The directive is intended to be used within a directive `${=block()}`.\n"
		"\n"
		"Consider an example.\n"
		"Assume that a block associated with symbol `` `foo`` is declared\n"
		"in a template named `base.tmpl` as below:\n"
		"\n"
		"`[base.tmpl]`\n"
		"\n"
		"    Block begins here.\n"
		"    ${=block(`foo)}\n"
		"    Content of base.\n"
		"    ${end}\n"
		"    Block ends here.\n"
		"\n"
		"This template renders the following result:\n"
		"\n"
		"    Block begins here.\n"
		"    Content of derived.\n"
		"    Block ends here.\n"
		"\n"
		"Below is another template named `derived.tmpl` that devies from `base.tmpl`\n"
		"and overrides the block `` `foo``.\n"
		"\n"
		"`[derived.tmpl]`\n"
		"\n"
		"    ${=extends('base.tmpl')}\n"
		"    \n"
		"    ${=block(`foo)}\n"
		"    ${=super(`foo)}\n"
		"    Content of derived.\n"
		"    ${end}\n"
		"\n"
		"This template renders the following result:\n"
		"\n"
		"    Block begins here.\n"
		"    Content of base.\n"
		"    Content of derived.\n"
		"    Block ends here.\n");
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
	processor.EvalExpr(expr);
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
	const Template& tmplSuper = args.Pick<Value_Template>().GetTemplate();
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
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(Template));
	// Assignment of method
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

//------------------------------------------------------------------------------
// Value_Template
//------------------------------------------------------------------------------
VType& Value_Template::vtype = VTYPE_Template;

}
