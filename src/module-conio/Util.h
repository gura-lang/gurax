//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CONIO_UTIL_H
#define GURAX_MODULE_CONIO_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(conio)

class Key {
public:
	static const int CTRL_A		= 0x01;
	static const int CTRL_B		= 0x02;
	static const int CTRL_C		= 0x03;
	static const int CTRL_D		= 0x04;
	static const int CTRL_E		= 0x05;
	static const int CTRL_F		= 0x06;
	static const int CTRL_G		= 0x07;
	static const int CTRL_H		= 0x08;
	static const int CTRL_I		= 0x09;
	static const int CTRL_J		= 0x0a;
	static const int CTRL_K		= 0x0b;
	static const int CTRL_L		= 0x0c;
	static const int CTRL_M		= 0x0d;
	static const int CTRL_N		= 0x0e;
	static const int CTRL_O		= 0x0f;
	static const int CTRL_P		= 0x10;
	static const int CTRL_Q		= 0x11;
	static const int CTRL_R		= 0x12;
	static const int CTRL_S		= 0x13;
	static const int CTRL_T		= 0x14;
	static const int CTRL_U		= 0x15;
	static const int CTRL_V		= 0x16;
	static const int CTRL_W		= 0x17;
	static const int CTRL_X		= 0x18;
	static const int CTRL_Y		= 0x19;
	static const int CTRL_Z		= 0x1a;
	static const int BACKSPACE	= 0x08;
	static const int TAB		= 0x09;
	static const int RETURN		= 0x0a;
	static const int ESCAPE		= 0x1b;
	static const int SPACE		= 0x20;
	// special key code
	static const int UP			= 0x80;
	static const int DOWN		= 0x81;
	static const int RIGHT		= 0x82;
	static const int LEFT		= 0x83;
	static const int INSERT		= 0x84;
	static const int HOME		= 0x85;
	static const int END		= 0x86;
	static const int PAGEUP		= 0x87;
	static const int PAGEDOWN	= 0x88;
	static const int DELETE		= 0x89;
};

bool Clear(const Symbol* pSymbol);
void GetWinSize(size_t* pWidth, size_t* pHeight);
Value* SetColor(const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprOfBlock);
Value* MoveTo(int x, int y, const Expr_Block* pExprOfBlock);
bool CheckKey();
int WaitKey(Processor* pProcessor);

bool SymbolToNumber(const Symbol* pSymbol, int* pNum);

Gurax_EndModuleScope(conio)

#endif
