//==============================================================================
// module-conio.cpp
//==============================================================================
#include "stdafx.h"

#define AssignValue_Number(name) Assign(#name, new Value_Number(name))

Gurax_BeginModule(conio)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
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

// conio.Flush():void
Gurax_DeclareFunction(Flush)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Flushes the pending request of drawing.\n");
}

Gurax_ImplementFunction(Flush)
{
	// Function body
	Flush();
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

// conio.MoveTo(x:Number, y:Number):map {block?}
Gurax_DeclareFunction(MoveTo)
{
	Declare(VTYPE_Any, Flag::Map);
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

Gurax_ImplementFunction(MoveTo)
{
	// Arguments
	ArgPicker args(argument);
	int x = args.PickNumberNonNeg<int>();
	int y = args.PickNumberNonNeg<int>();
	if (Error::IsIssued()) return Value::nil();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	return MoveTo(processor, x, y, pExprOfBlock);
}

// conio.ReadKey():[raise]
Gurax_DeclareFunction(ReadKey)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
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

Gurax_ImplementFunction(ReadKey)
{
	// Arguments
	bool raiseFlag = argument.IsSet(Gurax_Symbol(raise));
	// Function body
	if (!CheckKey()) return Value::nil();
	return WaitKey(raiseFlag? &processor : nullptr);
}

// conio.SetColor(fg:Symbol:nil, bg?:Symbol):map {block?}
Gurax_DeclareFunction(SetColor)
{
	Declare(VTYPE_Any, Flag::Map);
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
		"- `` `brightBlue``\n"
		"- `` `brightGreen``\n"
		"- `` `brightAqua``\n"
		"- `` `brightCyan``\n"
		"- `` `brightRed``\n"
		"- `` `brightPurple``\n"
		"- `` `brightMagenta``\n"
		"- `` `brightYellow``\n"
		"- `` `brightWhite``\n"
		"\n"
		"If `fg` is set to nil, the foreground color remains unchanged.\n"
		"If `bg` is omitted or set to nil, the background color remains unchanged.\n"
		"\n"
		"If `block` is specified, the color is changed before evaluating the block,\n"
		"and then gets back to what has been set when done.\n");
}

Gurax_ImplementFunction(SetColor)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol_fg = args.IsValid()? args.PickSymbol() : nullptr;
	const Symbol* pSymbol_bg = args.IsValid()? args.PickSymbol() : nullptr;
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	return SetColor(processor, pSymbol_fg, pSymbol_bg, pExprOfBlock);
}

// conio.WaitKey():[raise]
Gurax_DeclareFunction(WaitKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
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

Gurax_ImplementFunction(WaitKey)
{
	// Arguments
	bool raiseFlag = argument.IsSet(Gurax_Symbol(raise));
	// Function body
	return WaitKey(raiseFlag? &processor : nullptr);
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
	// Assignment of value
	AssignValue_Number(K_CTRL_A);
	AssignValue_Number(K_CTRL_B);
	AssignValue_Number(K_CTRL_C);
	AssignValue_Number(K_CTRL_D);
	AssignValue_Number(K_CTRL_E);
	AssignValue_Number(K_CTRL_F);
	AssignValue_Number(K_CTRL_G);
	AssignValue_Number(K_CTRL_H);
	AssignValue_Number(K_CTRL_I);
	AssignValue_Number(K_CTRL_J);
	AssignValue_Number(K_CTRL_K);
	AssignValue_Number(K_CTRL_L);
	AssignValue_Number(K_CTRL_M);
	AssignValue_Number(K_CTRL_N);
	AssignValue_Number(K_CTRL_O);
	AssignValue_Number(K_CTRL_P);
	AssignValue_Number(K_CTRL_Q);
	AssignValue_Number(K_CTRL_R);
	AssignValue_Number(K_CTRL_S);
	AssignValue_Number(K_CTRL_T);
	AssignValue_Number(K_CTRL_U);
	AssignValue_Number(K_CTRL_V);
	AssignValue_Number(K_CTRL_W);
	AssignValue_Number(K_CTRL_X);
	AssignValue_Number(K_CTRL_Y);
	AssignValue_Number(K_CTRL_Z);
	AssignValue_Number(K_BACKSPACE);
	AssignValue_Number(K_TAB);
	AssignValue_Number(K_RETURN);
	AssignValue_Number(K_ESCAPE);
	AssignValue_Number(K_SPACE);
	AssignValue_Number(K_UP);
	AssignValue_Number(K_DOWN);
	AssignValue_Number(K_RIGHT);
	AssignValue_Number(K_LEFT);
	AssignValue_Number(K_INSERT);
	AssignValue_Number(K_HOME);
	AssignValue_Number(K_END);
	AssignValue_Number(K_PAGEUP);
	AssignValue_Number(K_PAGEDOWN);
	AssignValue_Number(K_DELETE);
	// Assignment of function
	Assign(Gurax_CreateFunction(Clear));
	Assign(Gurax_CreateFunction(Flush));
	Assign(Gurax_CreateFunction(GetWinSize));
	Assign(Gurax_CreateFunction(MoveTo));
	Assign(Gurax_CreateFunction(ReadKey));
	Assign(Gurax_CreateFunction(SetColor));
	Assign(Gurax_CreateFunction(WaitKey));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(conio)
