//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CONIO_UTIL_H
#define GURAX_MODULE_CONIO_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(conio)

enum {
	K_CTRL_A	= 0x01,
	K_CTRL_B,
	K_CTRL_C,
	K_CTRL_D,
	K_CTRL_E,
	K_CTRL_F,
	K_CTRL_G,
	K_CTRL_H,
	K_CTRL_I,
	K_CTRL_J,
	K_CTRL_K,
	K_CTRL_L,
	K_CTRL_M,
	K_CTRL_N,
	K_CTRL_O,
	K_CTRL_P,
	K_CTRL_Q,
	K_CTRL_R,
	K_CTRL_S,
	K_CTRL_T,
	K_CTRL_U,
	K_CTRL_V,
	K_CTRL_W,
	K_CTRL_X,
	K_CTRL_Y,
	K_CTRL_Z,
	K_BACKSPACE	= 0x08,
	K_TAB		= 0x09,
	K_RETURN	= 0x0a,
	K_ESCAPE	= 0x1b,
	K_SPACE		= 0x20,
	// special key code
	K_UP		= 0x80,
	K_DOWN,
	K_RIGHT,
	K_LEFT,
	K_INSERT,
	K_HOME,
	K_END,
	K_PAGEUP,
	K_PAGEDOWN,
	K_DELETE,
};

void Flush();
bool Clear(const Symbol* pSymbol);
void GetWinSize(size_t* pWidth, size_t* pHeight);
Value* SetColor(Processor& processor, const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprOfBlock);
Value* MoveTo(Processor& processor, int x, int y, const Expr_Block* pExprOfBlock);
bool CheckKey();
Value* WaitKey(Processor* pProcessor);

bool SymbolToNumber(const Symbol* pSymbol, int* pNum);

Gurax_EndModuleScope(conio)

#endif
