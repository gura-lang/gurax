//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"
#if defined(GURAX_ON_MSWIN)
#include <conio.h>
#elif defined(GURAX_ON_LINUX) || defined(GURAX_ON_DARWIN)
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#else
#error unsupported platform
#endif

Gurax_BeginModuleScope(conio)

bool SymbolToNumber(const Symbol* pSymbol, int* pNum)
{
	return false;
}

#if 0
bool SymbolToNumber(Signal &sig, const Symbol *pSymbol, int *pNum)
{
#if defined(GURA_ON_MSWIN)
	int num =
		(pSymbol == Gura_Symbol(black))?			0 :
		(pSymbol == Gura_Symbol(blue))?				1 :
		(pSymbol == Gura_Symbol(green))?			2 :
		(pSymbol == Gura_Symbol(aqua))?				3 :
		(pSymbol == Gura_Symbol(cyan))?				3 :
		(pSymbol == Gura_Symbol(red))?				4 :
		(pSymbol == Gura_Symbol(purple))?			5 :
		(pSymbol == Gura_Symbol(magenta))?			5 :
		(pSymbol == Gura_Symbol(yellow))?			6 :
		(pSymbol == Gura_Symbol(white))?			7 :
		(pSymbol == Gura_Symbol(gray))?				8 :
		(pSymbol == Gura_Symbol(bright_blue))?		9 :
		(pSymbol == Gura_Symbol(bright_green))?		10 :
		(pSymbol == Gura_Symbol(bright_aqua))?		11 :
		(pSymbol == Gura_Symbol(bright_cyan))?		11 :
		(pSymbol == Gura_Symbol(bright_red))?		12 :
		(pSymbol == Gura_Symbol(bright_purple))?	13 :
		(pSymbol == Gura_Symbol(bright_magenta))?	13 :
		(pSymbol == Gura_Symbol(bright_yellow))?	14 :
		(pSymbol == Gura_Symbol(bright_white))?		15 : -1;
#elif defined(GURA_ON_LINUX) || defined(GURA_ON_DARWIN)
	int num =
		(pSymbol == Gura_Symbol(black))?			0 :
		(pSymbol == Gura_Symbol(red))?				1 :
		(pSymbol == Gura_Symbol(green))?			2 :
		(pSymbol == Gura_Symbol(yellow))?			3 :
		(pSymbol == Gura_Symbol(blue))?				4 :
		(pSymbol == Gura_Symbol(purple))?			5 :
		(pSymbol == Gura_Symbol(magenta))?			5 :
		(pSymbol == Gura_Symbol(aqua))?				6 :
		(pSymbol == Gura_Symbol(cyan))?				6 :
		(pSymbol == Gura_Symbol(white))?			7 :
		(pSymbol == Gura_Symbol(gray))?				8 :
		(pSymbol == Gura_Symbol(bright_red))?		9 :
		(pSymbol == Gura_Symbol(bright_green))?		10 :
		(pSymbol == Gura_Symbol(bright_yellow))?	11 :
		(pSymbol == Gura_Symbol(bright_blue))?		12 :
		(pSymbol == Gura_Symbol(bright_purple))?	13 :
		(pSymbol == Gura_Symbol(bright_magenta))?	13 :
		(pSymbol == Gura_Symbol(bright_aqua))?		14 :
		(pSymbol == Gura_Symbol(bright_cyan))?		14 :
		(pSymbol == Gura_Symbol(bright_white))?		15 : -1;
#else
#error unsupported platform
#endif
	if (num < 0) {
		sig.SetError(ERR_ValueError, "invalid symbol for color: %s", pSymbol->GetName());
		return false;
	}
	*pNum = num;
	return true;
}
#endif

#if defined(GURAX_ON_MSWIN)
bool Clear(const Symbol* pSymbol)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	//const Symbol* pSymbol = arg.Is_symbol(0)? arg.GetSymbol(0) : nullptr;
	COORD coordStart = { 0, 0 };
	COORD coordHome = { 0, 0 };
	DWORD dwConSize = 0;
	if (!pSymbol) {
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	} else if (pSymbol == Gurax_Symbol(line_)) {
		int width = csbi.dwSize.X;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else if (pSymbol == Gurax_Symbol(up)) {
		int height = csbi.dwCursorPosition.Y + 1;
		coordHome = csbi.dwCursorPosition;
		dwConSize = csbi.dwSize.X * height;
	} else if (pSymbol == Gurax_Symbol(down)) {
		int height = csbi.dwSize.Y - csbi.dwCursorPosition.Y;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = csbi.dwSize.X * height;
	} else if (pSymbol == Gurax_Symbol(left)) {
		int width = csbi.dwCursorPosition.X + 1;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else if (pSymbol == Gurax_Symbol(right)) {
		int width = csbi.dwSize.X - csbi.dwCursorPosition.X;
		coordStart = csbi.dwCursorPosition;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else {
		Error::Issue(ErrorType::ValueError, "invalid symbol %s", pSymbol->GetName());
		return false;
	}
	do {
		DWORD cCharsWritten;
		::FillConsoleOutputCharacter(hConsole, ' ',
							dwConSize, coordStart, &cCharsWritten);
		::FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
							dwConSize, coordStart, &cCharsWritten );
		::SetConsoleCursorPosition(hConsole, coordHome);
	} while (0);
	return true;
}

void GetWinSize(size_t* pWidth, size_t* pHeight)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	*pWidth = csbi.srWindow.Right + 1 - csbi.srWindow.Left;
	*pHeight = csbi.srWindow.Bottom + 1 - csbi.srWindow.Top;
}

void SetColor(const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprBlock)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	int fg = csbi.wAttributes & 0x000f;
	int bg = (csbi.wAttributes & 0x00f0) >> 4;
	if (pSymbolFg && !SymbolToNumber(pSymbolFg, &fg)) {
		return;
	}
	if (pSymbolBg && !SymbolToNumber(pSymbolBg, &bg)) {
		return;
	}
	::SetConsoleTextAttribute(hConsole, fg + (bg << 4));
	if (pExprBlock) {
		pExprBlock->Exec(env);
		::SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	}
}

void MoveTo(int x, int y, const Expr_Block* pExprBlock)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD pos = { x, y };
	::SetConsoleCursorPosition(hConsole, pos);
	if (pExprBlock) {
		pExprBlock->Exec(env);
		::SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
	}
}

bool CheckKey()
{
	return ::_kbhit() != 0;
}

int WaitKey(bool raiseFlag)
{
	//bool raiseFlag = arg.IsSet(Gurax_Symbol(raise));
	int chRtn = 0;
	enum class Stat { None, Special, } stat = Stat::None;
	for (;;) {
		int ch = ::_getch();
		//::printf("- %02x\n", ch);
		if (stat == Stat::None) {
			if (ch == 0xe0) {
				stat = Stat::Special;
			} else if (ch == 0x0d) {
				chRtn = Key::RETURN;
				break;
			} else if (raiseFlag && ch == 0x03) {
				sig.SetSignal(SIGTYPE_Terminate, Value::Nil);
				return 0;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == Stat::Special) {
			if (ch == 0x52) {			// E0 52
				chRtn = Key::INSERT;
				break;
			} else if (ch == 0x53) {	// E0 53
				chRtn = Key::DELETE;
				break;
			} else if (ch == 0x49) {	// E0 49
				chRtn = Key::PAGEUP;
				break;
			} else if (ch == 0x51) {	// E0 51
				chRtn = Key::PAGEDOWN;
				break;
			} else if (ch == 0x47) {	// E0 47
				chRtn = Key::HOME;
				break;
			} else if (ch == 0x4f) {	// E0 4F
				chRtn = Key::END;
				break;
			} else if (ch == 0x48) {	// E0 48
				chRtn = Key::UP;
				break;
			} else if (ch == 0x50) {	// E0 50
				chRtn = Key::DOWN;
				break;
			} else if (ch == 0x4d) {	// E0 4D
				chRtn = Key::RIGHT;
				break;
			} else if (ch == 0x4b) {	// E0 4B
				chRtn = Key::LEFT;
				break;
			} else {
				chRtn = ch;
				break;
			}
		}
	}
	return chRtn;
}

#elif defined(GURAX_ON_LINUX) || defined(GURAX_ON_DARWIN)

bool Clear(const Symbol* pSymbol)
{
	//const Symbol* pSymbol = arg.Is_symbol(0)? arg.GetSymbol(0) : nullptr;
	if (!pSymbol) {
		::printf("\033[2J");
		::printf("\033[H");
	} else if (pSymbol == Gurax_Symbol(line_)) {
		::printf("\033[2K");
	} else if (pSymbol == Gurax_Symbol(up)) {
		::printf("\033[D");
		::printf("\033[1J");
	} else if (pSymbol == Gurax_Symbol(down)) {
		::printf("\033[J");
	} else if (pSymbol == Gurax_Symbol(left)) {
		::printf("\033[1K");
	} else if (pSymbol == Gurax_Symbol(right)) {
		::printf("\033[K");
	} else {
		Error::Issue(ErrorType::ValueError, "invalid symbol %s", pSymbol->GetName());
		return false;
	}
	return true;
}

void GetWinSize(size_t* pWidth, size_t* pHeight)
{
	struct winsize ws;
	::ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	*pWidth = ws.ws_col, *pHeight = ws.ws_row;
}

StringList g_attrStack;

void SetColor(const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprBlock)
{
	int fg = 0, bg = 0;
	String str;
	if (!pSymbolFg) {
		// nothing to do
	} else if (!SymbolToNumber(pSymbolFg, &fg)) {
		return;
	} else {
		if (fg & 8) {
			str += "1;";
		} else {
			str += "0;";
		}
		str += '3';
		str += ('0' + (fg & 7));
	}
	if (!pSymbolBg) {
		// nothing to do
	} else if (!SymbolToNumber(pSymbolBg, &bg)) {
		return;
	} else {
		if (!str.empty()) str += ';';
		str += '4';
		str += ('0' + (bg & 7));
	}
	if (!str.empty()) {
		::printf("\033[%sm", str.c_str());
	}
	if (pExprBlock) {
		g_attrStack.push_back(str);
		//pExprBlock->Exec(env);
		if (!g_attrStack.empty()) g_attrStack.pop_back();
		if (g_attrStack.empty()) {
			::printf("\033[0m");
		} else {
			::printf("\033[%sm", g_attrStack.back().c_str());
		}
	} else {
		if (!g_attrStack.empty()) g_attrStack.pop_back();
		g_attrStack.push_back(str);
	}
}

void MoveTo(int x, int y, const Expr_Block* pExprBlock)
{
	if (!pExprBlock) {
		::printf("\033[%d;%dH", y + 1, x + 1);
	} else {
		::printf("\033[s");
		::printf("\033[%d;%dH", y + 1, x + 1);
		//pExprBlock->Exec(env);
		::printf("\033[u");
	}
}

bool CheckKey()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return ::select(1, &fds, NULL, NULL, &tv) > 0;
}

int WaitKey(bool raiseFlag)
{
	//bool raiseFlag = arg.IsSet(Gurax_Symbol(raise));
	struct termios termios_org, termios_new;
	::tcgetattr(STDIN_FILENO, &termios_org);
	termios_new = termios_org;
	termios_new.c_lflag &= ~ICANON;	// cancel canonical mode
	termios_new.c_lflag &= ~ECHO;	// cancel echo
	termios_new.c_lflag &= ~ISIG;	// disable signal
	::tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
	int chRtn = 0;
	enum class Stat { None, ESC, LBracket, O, SkipChar, } stat = Stat::None;
	for (;;) {
		int ch = ::getchar();
		//::printf("- %02x\n", ch);
		if (stat == Stat::None) {
			if (ch == 0x1b) {
				stat = Stat::ESC;
			} else if (ch == 0x7f) {
				chRtn = Key::BACKSPACE;
				break;
			} else if (raiseFlag && ch == 0x03) {
				//sig.SetSignal(SIGTYPE_Terminate, Value::Nil);
				::tcsetattr(STDIN_FILENO, TCSANOW, &termios_org);
				return 0;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == Stat::ESC) {
			if (ch == '[') {
				stat = Stat::LBracket;
			} else if (ch == 'O') {
				stat = Stat::O;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == Stat::LBracket) {
			if (ch == '1') {			// ESC [1
				chRtn = Key::HOME;
				stat = Stat::SkipChar;
			} else if (ch == '2') {		// ESC [2
				chRtn = Key::INSERT;
				stat = Stat::SkipChar;
			} else if (ch == '3') {		// ESC [3
				chRtn = Key::DELETE;
				stat = Stat::SkipChar;
			} else if (ch == '4') {		// ESC [4
				chRtn = Key::END;
				stat = Stat::SkipChar;
			} else if (ch == '5') {		// ESC [5
				chRtn = Key::PAGEUP;
				stat = Stat::SkipChar;
			} else if (ch == '6') {		// ESC [6
				chRtn = Key::PAGEDOWN;
				stat = Stat::SkipChar;
			} else if (ch == 'A') {		// ESC [A
				chRtn = Key::UP;
				break;
			} else if (ch == 'B') {		// ESC [B 
				chRtn = Key::DOWN;
				break;
			} else if (ch == 'C') {		// ESC [C
				chRtn = Key::RIGHT;
				break;
			} else if (ch == 'D') {		// ESC [D
				chRtn = Key::LEFT;
				break;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == Stat::O) {
			if (ch == 'F') {			// ESC OF
				chRtn = Key::END;
				break;
			} else if (ch == 'H') {		// ESC OH
				chRtn = Key::HOME;
				break;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == Stat::SkipChar) {
			break;
		}
	}
	::tcsetattr(STDIN_FILENO, TCSANOW, &termios_org);
	return chRtn;
}

#endif

Gurax_EndModuleScope(conio)
