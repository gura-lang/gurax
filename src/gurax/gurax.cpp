//==============================================================================
// gurax.cpp
// Copyright (C) 2011-2019 ypsitau
//==============================================================================
#include "stdafx.h"
#if defined(GURAX_ON_MSWIN)
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

namespace Gurax {

bool ReadLine(const char* prompt, String& strLine);
void RunREPL();

int Main(int argc, char* argv[])
{
	CommandLine cmdLine;
	if (!cmdLine
		.OptBool("debug",	'g')
		.OptBool("list",	'L')
		.Parse(argc, argv)) {
		Stream::CErr->Printf("%s\n", cmdLine.GetError());
		return 1;
	}
	if (argc < 2) {
		RunREPL();
		return 1;
	}
	const char* fileName = argv[1];
	RefPtr<Stream> pStream(Stream_File::Open(fileName, "rt"));
	if (!pStream) {
		Stream::CErr->Printf("failed to open file '%s'\n", fileName);
		return 1;
	}
	RefPtr<Expr_Root> pExprOfRoot(Parser::ParseStream(*pStream));
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	Composer composer;
	pExprOfRoot->Compose(composer);
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		return 1;
	}
	if (cmdLine.GetBool("list")) {
		composer.PrintPUnit();
	} else {
		RefPtr<Processor> pProcessor(Processor::Create(cmdLine.GetBool("debug")));
		pProcessor->Process(composer);
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			return 1;
		}
	}
	return 0;
}

void RunREPL()
{
	for (;;) {
		String strLine;
		ReadLine(">>>", strLine);
		::printf("%s\n", strLine.c_str());
	}
}

#if defined(GURAX_ON_MSWIN)
bool ReadLine(const char* prompt, String& strLine)
{
	strLine.clear();
	::printf("%s", prompt);
	for (;;) {
		int chRaw = ::fgetc(stdin);
		if (chRaw < 0) return false;
		char ch = static_cast<UChar>(chRaw);
		if (ch == '\n') break;
		strLine += ch;
	}
	return true;
}
#else
bool ReadLine(const char* prompt, String& strLine)
{
	char* lineBuff = readline(prompt);
	if (lineBuff == nullptr) return false;
	if (lineBuff[0] != '\0') add_history(lineBuff);
	strLine = lineBuff;
	::free(lineBuff);
	return true;
}
#endif

}

int main(int argc, char* argv[])
{
	Gurax::Initialize();
	return Gurax::Main(argc, argv);
}
