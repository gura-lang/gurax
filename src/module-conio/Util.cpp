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

class SymbolAssoc_ColorCode : public SymbolAssoc<int, -1> {
public:
	SymbolAssoc_ColorCode() {
#if defined(GURAX_ON_MSWIN)
		Assoc(Gurax_Symbol(black),			0);
		Assoc(Gurax_Symbol(blue),			1);
		Assoc(Gurax_Symbol(green),			2);
		Assoc(Gurax_Symbol(aqua),			3);
		Assoc(Gurax_Symbol(cyan),			3);
		Assoc(Gurax_Symbol(red),			4);
		Assoc(Gurax_Symbol(purple),			5);
		Assoc(Gurax_Symbol(magenta),		5);
		Assoc(Gurax_Symbol(yellow),			6);
		Assoc(Gurax_Symbol(white),			7);
		Assoc(Gurax_Symbol(gray),			8 + 0);
		Assoc(Gurax_Symbol(brightBlue),	8 + 1);
		Assoc(Gurax_Symbol(brightGreen),	8 + 2);
		Assoc(Gurax_Symbol(brightAqua),	8 + 3);
		Assoc(Gurax_Symbol(brightCyan),	8 + 3);
		Assoc(Gurax_Symbol(brightRed),		8 + 4);
		Assoc(Gurax_Symbol(brightPurple),	8 + 5);
		Assoc(Gurax_Symbol(brightMagenta),	8 + 5);
		Assoc(Gurax_Symbol(brightYellow),	8 + 6);
		Assoc(Gurax_Symbol(brightWhite),	8 + 7);
#elif defined(GURAX_ON_LINUX) || defined(GURAX_ON_DARWIN)
		Assoc(Gurax_Symbol(black),			0);
		Assoc(Gurax_Symbol(red),			1);
		Assoc(Gurax_Symbol(green),			2);
		Assoc(Gurax_Symbol(yellow),			3);
		Assoc(Gurax_Symbol(blue),			4);
		Assoc(Gurax_Symbol(purple),			5);
		Assoc(Gurax_Symbol(magenta),		5);
		Assoc(Gurax_Symbol(aqua),			6);
		Assoc(Gurax_Symbol(cyan),			6);
		Assoc(Gurax_Symbol(white),			7);
		Assoc(Gurax_Symbol(gray),			8 + 0);
		Assoc(Gurax_Symbol(brightRed),		8 + 1);
		Assoc(Gurax_Symbol(brightGreen),	8 + 2);
		Assoc(Gurax_Symbol(brightYellow),	8 + 3);
		Assoc(Gurax_Symbol(brightBlue),	8 + 4);
		Assoc(Gurax_Symbol(brightPurple),	8 + 5);
		Assoc(Gurax_Symbol(brightMagenta),	8 + 5);
		Assoc(Gurax_Symbol(brightAqua),	8 + 6);
		Assoc(Gurax_Symbol(brightCyan),	8 + 6);
		Assoc(Gurax_Symbol(brightWhite),	8 + 7);
#endif
	}
	static const SymbolAssoc& GetInstance() {
		static SymbolAssoc* pSymbolAssoc = nullptr;
		return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_ColorCode());
	}
};

bool SymbolToColorCode(const Symbol* pSymbol, int* pColorCode)
{
	*pColorCode = SymbolAssoc_ColorCode::GetInstance().ToAssociated(pSymbol);
	if (*pColorCode < 0) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for color: %s", pSymbol->GetName());
		return false;
	}
	return true;
}

#if defined(GURAX_ON_MSWIN)
void Flush()
{
}

bool Clear(const Symbol* pSymbol)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD coordStart = { 0, 0 };
	COORD coordHome = { 0, 0 };
	DWORD dwConSize = 0;
	if (!pSymbol) {
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(line_))) {
		int width = csbi.dwSize.X;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(up))) {
		int height = csbi.dwCursorPosition.Y + 1;
		coordHome = csbi.dwCursorPosition;
		dwConSize = csbi.dwSize.X * height;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(down))) {
		int height = csbi.dwSize.Y - csbi.dwCursorPosition.Y;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = csbi.dwSize.X * height;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(left))) {
		int width = csbi.dwCursorPosition.X + 1;
		coordStart = csbi.dwCursorPosition;
		coordStart.X = 0;
		coordHome = csbi.dwCursorPosition;
		dwConSize = width;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(right))) {
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

Value* SetColor(Processor& processor, const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprOfBlock)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	int fg = csbi.wAttributes & 0x000f;
	int bg = (csbi.wAttributes & 0x00f0) >> 4;
	if (pSymbolFg && !SymbolToColorCode(pSymbolFg, &fg)) return Value::nil();
	if (pSymbolBg && !SymbolToColorCode(pSymbolBg, &bg)) return Value::nil();
	::SetConsoleTextAttribute(hConsole, fg + (bg << 4));
	if (pExprOfBlock) {
		RefPtr<Value> pValue(pExprOfBlock->Eval(processor));
		if (Error::IsIssued()) return Value::nil();
		::SetConsoleTextAttribute(hConsole, csbi.wAttributes);
		return pValue.release();
	}
	return Value::nil();
}

Value* MoveTo(Processor& processor, int x, int y, const Expr_Block* pExprOfBlock)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(hConsole, pos);
	if (pExprOfBlock) {
		RefPtr<Value> pValue(pExprOfBlock->Eval(processor));
		if (Error::IsIssued()) return Value::nil();
		::SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		return pValue.release();
	}
	return Value::nil();
}

bool CheckKey()
{
	return ::_kbhit() != 0;
}

Value* WaitKey(Processor* pProcessor)
{
	int chRtn = 0;
	enum class Stat { None, Special, } stat = Stat::None;
	for (;;) {
		int ch = ::_getch();
		//::printf("- %02x\n", ch);
		if (stat == Stat::None) {
			if (ch == 0xe0) {
				stat = Stat::Special;
			} else if (ch == 0x0d) {
				chRtn = K_RETURN;
				break;
			} else if (pProcessor && ch == 0x03) {
				pProcessor->Terminate();
				return Value::nil();
			} else {
				chRtn = ch;
				break;
			}
		} else if (stat == Stat::Special) {
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
	return new Value_Number(chRtn);
}

#elif defined(GURAX_ON_LINUX) || defined(GURAX_ON_DARWIN)

void Flush()
{
	::fflush(stdout);
}

bool Clear(const Symbol* pSymbol)
{
	//const Symbol* pSymbol = arg.Is_symbol(0)? arg.GetSymbol(0) : nullptr;
	if (!pSymbol) {
		::printf("\033[2J");
		::printf("\033[H");
	} else if (pSymbol->IsIdentical(Gurax_Symbol(line_))) {
		::printf("\033[2K");
	} else if (pSymbol->IsIdentical(Gurax_Symbol(up))) {
		::printf("\033[D");
		::printf("\033[1J");
	} else if (pSymbol->IsIdentical(Gurax_Symbol(down))) {
		::printf("\033[J");
	} else if (pSymbol->IsIdentical(Gurax_Symbol(left))) {
		::printf("\033[1K");
	} else if (pSymbol->IsIdentical(Gurax_Symbol(right))) {
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

Value* SetColor(Processor& processor, const Symbol* pSymbolFg, const Symbol* pSymbolBg, const Expr_Block* pExprOfBlock)
{
	int fg = 0, bg = 0;
	String str;
	if (!pSymbolFg) {
		// nothing to do
	} else if (!SymbolToColorCode(pSymbolFg, &fg)) {
		return Value::nil();
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
	} else if (!SymbolToColorCode(pSymbolBg, &bg)) {
		return Value::nil();
	} else {
		if (!str.empty()) str += ';';
		str += '4';
		str += ('0' + (bg & 7));
	}
	if (!str.empty()) {
		::printf("\033[%sm", str.c_str());
	}
	if (pExprOfBlock) {
		g_attrStack.push_back(str);
		RefPtr<Value> pValue(pExprOfBlock->Eval(processor));
		if (Error::IsIssued()) return Value::nil();
		if (!g_attrStack.empty()) g_attrStack.pop_back();
		if (g_attrStack.empty()) {
			::printf("\033[0m");
		} else {
			::printf("\033[%sm", g_attrStack.back().c_str());
		}
		return pValue.release();
	}
	if (!g_attrStack.empty()) g_attrStack.pop_back();
	g_attrStack.push_back(str);
	return Value::nil();
}

Value* MoveTo(Processor& processor, int x, int y, const Expr_Block* pExprOfBlock)
{
	if (pExprOfBlock) {
		::printf("\033[s");
		::printf("\033[%d;%dH", y + 1, x + 1);
		RefPtr<Value> pValue(pExprOfBlock->Eval(processor));
		if (Error::IsIssued()) return Value::nil();
		::printf("\033[u");
		return pValue.release();
	}
	::printf("\033[%d;%dH", y + 1, x + 1);
	return Value::nil();
}

bool CheckKey()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return ::select(1, &fds, NULL, NULL, &tv) > 0;
}

Value* WaitKey(Processor* pProcessor)
{
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
				chRtn = K_BACKSPACE;
				break;
			} else if (pProcessor && ch == 0x03) {
				pProcessor->Terminate();
				::tcsetattr(STDIN_FILENO, TCSANOW, &termios_org);
				return Value::nil();
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
				chRtn = K_HOME;
				stat = Stat::SkipChar;
			} else if (ch == '2') {		// ESC [2
				chRtn = K_INSERT;
				stat = Stat::SkipChar;
			} else if (ch == '3') {		// ESC [3
				chRtn = K_DELETE;
				stat = Stat::SkipChar;
			} else if (ch == '4') {		// ESC [4
				chRtn = K_END;
				stat = Stat::SkipChar;
			} else if (ch == '5') {		// ESC [5
				chRtn = K_PAGEUP;
				stat = Stat::SkipChar;
			} else if (ch == '6') {		// ESC [6
				chRtn = K_PAGEDOWN;
				stat = Stat::SkipChar;
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
		} else if (stat == Stat::O) {
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
		} else if (stat == Stat::SkipChar) {
			break;
		}
	}
	::tcsetattr(STDIN_FILENO, TCSANOW, &termios_org);
	return new Value_Number(chRtn);
}

#endif

Gurax_EndModuleScope(conio)
