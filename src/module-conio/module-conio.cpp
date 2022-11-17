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
	AddHelp(Gurax_Symbol(en), u8R"**(
Clears the screen.

In default, it clears whole the screen.
Argument `region` that takes one of the symbols below
would specify the region to be cleared.

- `` `line`` .. clears characters in the line where the cursor exists.
- `` `left`` .. clears characters on the left side of the cursor.
- `` `right`` .. clears characters on the right side of the cursor.
- `` `top`` .. clears characters on the above side of the cursor.
- `` `bottom`` .. clears characters on the below side of the cursor.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Flushes the pending request of drawing.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the screen size as a tuple `(width, height)`.
)**");
}

Gurax_ImplementFunction(GetWinSize)
{
	// Function body
	size_t width, height;
	GetWinSize(&width, &height);
	return Value_Tuple::Create(new Value_Number(width), new Value_Number(height));
}

// conio.MoveTo(x:Number, y:Number):map {block?}
Gurax_DeclareFunction(MoveTo)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Moves cursor to the specified position.
The most top-left position on the screen is represented as `0, 0`.

If `block` is specified, the cursor is moved before evaluating the block,
and then gets back to where it has been when done.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Reads a keyboard input and returns a character code number associated with the key
without blocking.

If `:raise` attribute is specified, hitting `Ctrl-C` issues a terminating signal
that causes the program done.

Character code numbers of some of the special keys are defined as below:

- `conio.K_BACKSPACE`
- `conio.K_TAB`
- `conio.K_RETURN`
- `conio.K_ESCAPE`
- `conio.K_SPACE`
- `conio.K_UP`
- `conio.K_DOWN`
- `conio.K_RIGHT`
- `conio.K_LEFT`
- `conio.K_INSERT`
- `conio.K_HOME`
- `conio.K_END`
- `conio.K_PAGEUP`
- `conio.K_PAGEDOWN`
- `conio.K_DELETE`
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Sets foreground and background color of text by specifying a color symbol.
Available color symbols are listed below:

- `` `black``
- `` `blue``
- `` `green``
- `` `aqua``
- `` `cyan``
- `` `red``
- `` `purple``
- `` `magenta``
- `` `yellow``
- `` `white``
- `` `gray``
- `` `brightBlue``
- `` `brightGreen``
- `` `brightAqua``
- `` `brightCyan``
- `` `brightRed``
- `` `brightPurple``
- `` `brightMagenta``
- `` `brightYellow``
- `` `brightWhite``

If `fg` is set to nil, the foreground color remains unchanged.
If `bg` is omitted or set to nil, the background color remains unchanged.

If `block` is specified, the color is changed before evaluating the block,
and then gets back to what has been set when done.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Waits for a keyboard input and returns a character code number associated with the key.

If `:raise` attribute is specified, hitting `Ctrl-C` issues a terminating signal
that causes the program done.

Character code numbers of some of the special keys are defined as below:

- `conio.K_BACKSPACE`
- `conio.K_TAB`
- `conio.K_RETURN`
- `conio.K_ESCAPE`
- `conio.K_SPACE`
- `conio.K_UP`
- `conio.K_DOWN`
- `conio.K_RIGHT`
- `conio.K_LEFT`
- `conio.K_INSERT`
- `conio.K_HOME`
- `conio.K_END`
- `conio.K_PAGEUP`
- `conio.K_PAGEDOWN`
- `conio.K_DELETE`
)**");
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
