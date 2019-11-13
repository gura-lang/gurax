//==============================================================================
// module-conio.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(conio)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// re.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	Int num = args.PickNumber<Int>();
	// Function body
	return new Value_String(String::Repeat(str, num));
}

// conio.Clear(region?:Symbol):void
Gurax_DeclareFunction(Clear)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("region", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Clears the screen.\n"
		"\n"
		"In default, it clears whole the screen.\n"
		"Argument `region` that takes one of the symbols below\n"
		"would specify the region to be cleared.\n"
		"\n"
		"- `` `line`` .. clears characters in the line where the cursor exists.\n"
		"- `` `left`` .. clears characters on the left side of the cursor.\n"
		"- `` `right`` .. clears characters on the right side of the cursor.\n"
		"- `` `top`` .. clears characters on the above side of the cursor.\n"
		"- `` `bottom`` .. clears characters on the below side of the cursor.\n");
}

Gurax_ImplementFunction(Clear)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	Clear(pSymbol);
	return Value::nil();
}

// conio.GetWinSize()
Gurax_DeclareFunction(GetWinSize)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns the screen size as a list `[width, height]`.");
}

Gurax_ImplementFunction(GetWinSize)
{
	// Function body
	size_t width, height;
	GetWinSize(&width, &height);
	return Value_List::Create(new Value_Number(width), new Value_Number(height));
}

#if 0
// conio.setcolor(fg:symbol:nil, bg?:symbol):map:void {block?}
Gurax_DeclareFunction(setcolor)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fg", VTYPE_Symbol, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("bg", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Sets foreground and background color of text by specifying a color symbol.\n"
		"Available color symbols are listed below:\n"
		"\n"
		"- `` `black``\n"
		"- `` `blue``\n"
		"- `` `green``\n"
		"- `` `aqua``\n"
		"- `` `cyan``\n"
		"- `` `red``\n"
		"- `` `purple``\n"
		"- `` `magenta``\n"
		"- `` `yellow``\n"
		"- `` `white``\n"
		"- `` `gray``\n"
		"- `` `bright_blue``\n"
		"- `` `bright_green``\n"
		"- `` `bright_aqua``\n"
		"- `` `bright_cyan``\n"
		"- `` `bright_red``\n"
		"- `` `bright_purple``\n"
		"- `` `bright_magenta``\n"
		"- `` `bright_yellow``\n"
		"- `` `bright_white``\n"
		"\n"
		"If `fg` is set to nil, the foreground color remains unchanged.\n"
		"If `bg` is omitted or set to nil, the background color remains unchanged.\n"
		"\n"
		"If `block` is specified, the color is changed before evaluating the block,\n"
		"and then gets back to what has been set when done.\n");
}

Gurax_ImplementFunction(setcolor)
{
	Signal &sig = env.GetSignal();
	const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
	if (sig.IsSignalled()) return Value::Nil;
	SetColor(env, arg.Is_symbol(0)? arg.GetSymbol(0) : nullptr,
			 arg.Is_symbol(1)? arg.GetSymbol(1) : nullptr, pExprBlock);
	return Value::Nil;
}

// conio.moveto(x:number, y:number):map:void {block?}
Gurax_DeclareFunction(moveto)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Moves cursor to the specified position.\n"
		"The most top-left position on the screen is represented as `0, 0`.\n"
		"\n"
		"If `block` is specified, the cursor is moved before evaluating the block,\n"
		"and then gets back to where it has been when done.\n");
}

Gurax_ImplementFunction(moveto)
{
	const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
	if (env.IsSignalled()) return Value::Nil;
	MoveTo(env, arg.GetInt(0), arg.GetInt(1), pExprBlock);
	return Value::Nil;
}

// conio.waitkey():[raise]
Gurax_DeclareFunction(waitkey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttr(Gurax_Symbol(raise));
	AddHelp(
		Gurax_Symbol(en),
		"Waits for a keyboard input and returns a character code number associated with the key.\n"
		"\n"
		"If `:raise` attribute is specified, hitting `Ctrl-C` issues a terminating signal\n"
		"that causes the program done.\n"
		"\n"
		"Character code numbers of some of the special keys are defined as below:\n"
		"\n"
		"- `conio.K_BACKSPACE`\n"
		"- `conio.K_TAB`\n"
		"- `conio.K_RETURN`\n"
		"- `conio.K_ESCAPE`\n"
		"- `conio.K_SPACE`\n"
		"- `conio.K_UP`\n"
		"- `conio.K_DOWN`\n"
		"- `conio.K_RIGHT`\n"
		"- `conio.K_LEFT`\n"
		"- `conio.K_INSERT`\n"
		"- `conio.K_HOME`\n"
		"- `conio.K_END`\n"
		"- `conio.K_PAGEUP`\n"
		"- `conio.K_PAGEDOWN`\n"
		"- `conio.K_DELETE`\n");
}

Gurax_ImplementFunction(waitkey)
{
	int chRtn = WaitKey(env, arg.IsSet(Gurax_Symbol(raise)));
	if (env.IsSignalled()) return Value::Nil;
	return Value(chRtn);
}

// conio.readkey():[raise]
Gurax_DeclareFunction(readkey)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(raise));
	AddHelp(
		Gurax_Symbol(en),
		"Reads a keyboard input and returns a character code number associated with the key\n"
		"without blocking."
		"\n"
		"If `:raise` attribute is specified, hitting `Ctrl-C` issues a terminating signal\n"
		"that causes the program done.\n"
		"\n"
		"Character code numbers of some of the special keys are defined as below:\n"
		"\n"
		"- `conio.K_BACKSPACE`\n"
		"- `conio.K_TAB`\n"
		"- `conio.K_RETURN`\n"
		"- `conio.K_ESCAPE`\n"
		"- `conio.K_SPACE`\n"
		"- `conio.K_UP`\n"
		"- `conio.K_DOWN`\n"
		"- `conio.K_RIGHT`\n"
		"- `conio.K_LEFT`\n"
		"- `conio.K_INSERT`\n"
		"- `conio.K_HOME`\n"
		"- `conio.K_END`\n"
		"- `conio.K_PAGEUP`\n"
		"- `conio.K_PAGEDOWN`\n"
		"- `conio.K_DELETE`\n");
}

Gurax_ImplementFunction(readkey)
{
	if (!CheckKey()) return Value::Nil;
	int chRtn = WaitKey(env, arg.IsSet(Gurax_Symbol(raise)));
	if (env.IsSignalled()) return Value::Nil;
	return Value(chRtn);
}
#endif

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
	Assign(Gurax_CreateFunction(Clear));
	Assign(Gurax_CreateFunction(GetWinSize));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(conio)
