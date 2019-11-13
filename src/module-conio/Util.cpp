//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(conio)

#if 0
#if defined(GURAX_ON_MSWIN)
void Clear(Environment &env, const Symbol *pSymbol)
{
	Signal &sig = env.GetSignal();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	//const Symbol *pSymbol = arg.Is_symbol(0)? arg.GetSymbol(0) : nullptr;
	COORD coordStart = { 0, 0 };
	COORD coordHome = { 0, 0 };
	DWORD dwConSize = 0;
	if (pSymbol == nullptr) {
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	} else if (pSymbol == Gura_Symbol(line_)) {
		int width = csbi.dwSize.X;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else if (pSymbol == Gura_Symbol(up)) {
		int height = csbi.dwCursorPosition.Y + 1;
		coordHome = csbi.dwCursorPosition;
		dwConSize = csbi.dwSize.X * height;
	} else if (pSymbol == Gura_Symbol(down)) {
		int height = csbi.dwSize.Y - csbi.dwCursorPosition.Y;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = csbi.dwSize.X * height;
	} else if (pSymbol == Gura_Symbol(left)) {
		int width = csbi.dwCursorPosition.X + 1;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else if (pSymbol == Gura_Symbol(right)) {
		int width = csbi.dwSize.X - csbi.dwCursorPosition.X;
		coordStart = csbi.dwCursorPosition;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else {
		sig.SetError(ERR_ValueError, "invalid symbol %s", pSymbol->GetName());
		return;
	}
	do {
		DWORD cCharsWritten;
		::FillConsoleOutputCharacter(hConsole, ' ',
							dwConSize, coordStart, &cCharsWritten);
		::FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
							dwConSize, coordStart, &cCharsWritten );
		::SetConsoleCursorPosition(hConsole, coordHome);
	} while (0);
}

void GetWinSize(Environment &env, size_t *pWidth, size_t *pHeight)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	*pWidth = csbi.srWindow.Right + 1 - csbi.srWindow.Left;
	*pHeight = csbi.srWindow.Bottom + 1 - csbi.srWindow.Top;
}

void SetColor(Environment &env, const Symbol *pSymbolFg,
			  const Symbol *pSymbolBg, const Expr_Block *pExprBlock)
{
	Signal &sig = env.GetSignal();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	int fg = csbi.wAttributes & 0x000f;
	int bg = (csbi.wAttributes & 0x00f0) >> 4;
	if (pSymbolFg != nullptr && !SymbolToNumber(sig, pSymbolFg, &fg)) {
		return;
	}
	if (pSymbolBg != nullptr && !SymbolToNumber(sig, pSymbolBg, &bg)) {
		return;
	}
	::SetConsoleTextAttribute(hConsole, fg + (bg << 4));
	if (pExprBlock != nullptr) {
		pExprBlock->Exec(env);
		::SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	}
}

void MoveTo(Environment &env, int x, int y, const Expr_Block *pExprBlock)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD pos = { x, y };
	::SetConsoleCursorPosition(hConsole, pos);
	if (pExprBlock != nullptr) {
		pExprBlock->Exec(env);
		::SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
	}
}

bool CheckKey()
{
	return ::_kbhit() != 0;
}

int WaitKey(Environment &env, bool raiseFlag)
{
	Signal &sig = env.GetSignal();
	//bool raiseFlag = arg.IsSet(Gura_Symbol(raise));
	int chRtn = 0;
	enum {
		STAT_None, STAT_Special,
	} stat = STAT_None;
	for (;;) {
		int ch = ::_getch();
		//::printf("- %02x\n", ch);
		if (stat == STAT_None) {
			if (ch == 0xe0) {
				stat = STAT_Special;
			} else if (ch == 0x0d) {
				chRtn = K_RETURN;
				break;
			} else if (raiseFlag && ch == 0x03) {
				sig.SetSignal(SIGTYPE_Terminate, Value::Nil);
				return 0;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == STAT_Special) {
			if (ch == 0x52) {			// E0 52
				chRtn = K_INSERT;
				break;
			} else if (ch == 0x53) {	// E0 53
				chRtn = K_DELETE;
				break;
			} else if (ch == 0x49) {	// E0 49
				chRtn = K_PAGEUP;
				break;
			} else if (ch == 0x51) {	// E0 51
				chRtn = K_PAGEDOWN;
				break;
			} else if (ch == 0x47) {	// E0 47
				chRtn = K_HOME;
				break;
			} else if (ch == 0x4f) {	// E0 4F
				chRtn = K_END;
				break;
			} else if (ch == 0x48) {	// E0 48
				chRtn = K_UP;
				break;
			} else if (ch == 0x50) {	// E0 50
				chRtn = K_DOWN;
				break;
			} else if (ch == 0x4d) {	// E0 4D
				chRtn = K_RIGHT;
				break;
			} else if (ch == 0x4b) {	// E0 4B
				chRtn = K_LEFT;
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
void Clear(Environment &env, const Symbol *pSymbol)
{
	Signal &sig = env.GetSignal();
	//const Symbol *pSymbol = arg.Is_symbol(0)? arg.GetSymbol(0) : nullptr;
	if (pSymbol == nullptr) {
		::printf("\033[2J");
		::printf("\033[H");
	} else if (pSymbol == Gura_Symbol(line_)) {
		::printf("\033[2K");
	} else if (pSymbol == Gura_Symbol(up)) {
		::printf("\033[D");
		::printf("\033[1J");
	} else if (pSymbol == Gura_Symbol(down)) {
		::printf("\033[J");
	} else if (pSymbol == Gura_Symbol(left)) {
		::printf("\033[1K");
	} else if (pSymbol == Gura_Symbol(right)) {
		::printf("\033[K");
	} else {
		sig.SetError(ERR_ValueError, "invalid symbol %s", pSymbol->GetName());
	}
}

void GetWinSize(Environment &env, size_t *pWidth, size_t *pHeight)
{
	struct winsize ws;
	::ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	*pWidth = ws.ws_col, *pHeight = ws.ws_row;
}

StringList g_attrStack;

void SetColor(Environment &env, const Symbol *pSymbolFg,
			  const Symbol *pSymbolBg, const Expr_Block *pExprBlock)
{
	Signal &sig = env.GetSignal();
	int fg = 0, bg = 0;
	String str;
	if (pSymbolFg == nullptr) {
		// nothing to do
	} else if (!SymbolToNumber(sig, pSymbolFg, &fg)) {
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
	if (pSymbolBg == nullptr) {
		// nothing to do
	} else if (!SymbolToNumber(sig, pSymbolBg, &bg)) {
		return;
	} else {
		if (!str.empty()) str += ';';
		str += '4';
		str += ('0' + (bg & 7));
	}
	if (!str.empty()) {
		::printf("\033[%sm", str.c_str());
	}
	if (pExprBlock != nullptr) {
		g_attrStack.push_back(str);
		pExprBlock->Exec(env);
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

void MoveTo(Environment &env, int x, int y, const Expr_Block *pExprBlock)
{
	//Signal &sig = env.GetSignal();
	if (pExprBlock == nullptr) {
		::printf("\033[%d;%dH", y + 1, x + 1);
	} else {
		::printf("\033[s");
		::printf("\033[%d;%dH", y + 1, x + 1);
		pExprBlock->Exec(env);
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

int WaitKey(Environment &env, bool raiseFlag)
{
	Signal &sig = env.GetSignal();
	//bool raiseFlag = arg.IsSet(Gura_Symbol(raise));
	struct termios termios_org, termios_new;
	::tcgetattr(STDIN_FILENO, &termios_org);
	termios_new = termios_org;
	termios_new.c_lflag &= ~ICANON;	// cancel canonical mode
	termios_new.c_lflag &= ~ECHO;	// cancel echo
	termios_new.c_lflag &= ~ISIG;	// disable signal
	::tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
	int chRtn = 0;
	enum {
		STAT_None, STAT_ESC, STAT_LBracket, STAT_O, STAT_SkipChar,
	} stat = STAT_None;
	for (;;) {
		int ch = ::getchar();
		//::printf("- %02x\n", ch);
		if (stat == STAT_None) {
			if (ch == 0x1b) {
				stat = STAT_ESC;
			} else if (ch == 0x7f) {
				chRtn = K_BACKSPACE;
				break;
			} else if (raiseFlag && ch == 0x03) {
				sig.SetSignal(SIGTYPE_Terminate, Value::Nil);
				::tcsetattr(STDIN_FILENO, TCSANOW, &termios_org);
				return 0;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == STAT_ESC) {
			if (ch == '[') {
				stat = STAT_LBracket;
			} else if (ch == 'O') {
				stat = STAT_O;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == STAT_LBracket) {
			if (ch == '1') {			// ESC [1
				chRtn = K_HOME;
				stat = STAT_SkipChar;
			} else if (ch == '2') {		// ESC [2
				chRtn = K_INSERT;
				stat = STAT_SkipChar;
			} else if (ch == '3') {		// ESC [3
				chRtn = K_DELETE;
				stat = STAT_SkipChar;
			} else if (ch == '4') {		// ESC [4
				chRtn = K_END;
				stat = STAT_SkipChar;
			} else if (ch == '5') {		// ESC [5
				chRtn = K_PAGEUP;
				stat = STAT_SkipChar;
			} else if (ch == '6') {		// ESC [6
				chRtn = K_PAGEDOWN;
				stat = STAT_SkipChar;
			} else if (ch == 'A') {		// ESC [A
				chRtn = K_UP;
				break;
			} else if (ch == 'B') {		// ESC [B 
				chRtn = K_DOWN;
				break;
			} else if (ch == 'C') {		// ESC [C
				chRtn = K_RIGHT;
				break;
			} else if (ch == 'D') {		// ESC [D
				chRtn = K_LEFT;
				break;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == STAT_O) {
			if (ch == 'F') {			// ESC OF
				chRtn = K_END;
				break;
			} else if (ch == 'H') {		// ESC OH
				chRtn = K_HOME;
				break;
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == STAT_SkipChar) {
			break;
		}
	}
	::tcsetattr(STDIN_FILENO, TCSANOW, &termios_org);
	return chRtn;
}

#else
#error unsupported platform
#endif
#endif

Gurax_EndModuleScope(conio)
