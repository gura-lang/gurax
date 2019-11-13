//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CONIO_UTIL_H
#define GURAX_MODULE_CONIO_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(conio)

enum {
	K_CTRL_A	= 0x01,
	K_CTRL_B	= 0x02,
	K_CTRL_C	= 0x03,
	K_CTRL_D	= 0x04,
	K_CTRL_E	= 0x05,
	K_CTRL_F	= 0x06,
	K_CTRL_G	= 0x07,
	K_CTRL_H	= 0x08,
	K_CTRL_I	= 0x09,
	K_CTRL_J	= 0x0a,
	K_CTRL_K	= 0x0b,
	K_CTRL_L	= 0x0c,
	K_CTRL_M	= 0x0d,
	K_CTRL_N	= 0x0e,
	K_CTRL_O	= 0x0f,
	K_CTRL_P	= 0x10,
	K_CTRL_Q	= 0x11,
	K_CTRL_R	= 0x12,
	K_CTRL_S	= 0x13,
	K_CTRL_T	= 0x14,
	K_CTRL_U	= 0x15,
	K_CTRL_V	= 0x16,
	K_CTRL_W	= 0x17,
	K_CTRL_X	= 0x18,
	K_CTRL_Y	= 0x19,
	K_CTRL_Z	= 0x1a,
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

void Clear(const Symbol* pSymbol);
void GetWinSize(size_t* pWidth, size_t* pHeight);
void SetColor(const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprBlock);
void MoveTo(int x, int y, const Expr_Block* pExprBlock);
bool CheckKey();
int WaitKey(bool raiseFlag);

bool SymbolToNumber(const Symbol* pSymbol, int* pNum);

Gurax_EndModuleScope(conio)

#endif
