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
		RefPtr<Value> pValue(pProcessor->ProcessExpr(*pExprOfRoot));
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			return 1;
		}
	}
	return 0;
}

void RunREPL()
{
	Stream& stream = *Stream::COut;
	RefPtr<Parser> pParser(new Parser("*REPL*"));
	Composer composer(true);
	RefPtr<Processor> pProcessor(Processor::Create(false));
	Expr_Root& exprRoot = pParser->GetExprRoot();
	Expr* pExprLast = nullptr;
	const PUnit* pPUnit = nullptr;
	stream.Printf("%s\n", Version::GetBanner(false));
	for (;;) {
		String strLine;
		String prompt;
		prompt.Printf("%d:%s", pParser->GetLineNo(),
					  pParser->IsContinued()? Basement::Inst.GetPS2() : Basement::Inst.GetPS1());
		if (!ReadLine(prompt.c_str(), strLine)) break;
		bool blankLineFlag = true;
		for (char ch : strLine) {
			if (!String::IsSpace(ch)) {
				blankLineFlag = false;
				break;
			}
		}
		if (blankLineFlag) continue;
		for (char ch : strLine) {
			pParser->ParseChar(ch);
			if (Error::IsIssued()) break;
		}
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			Error::Clear();
			continue;
		}
		Expr* pExpr = pExprLast? pExprLast->GetExprNext() : exprRoot.GetExprElemFirst();
		for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
			if (!pExpr->Prepare()) break;
			if (Error::IsIssued()) break;
			pExpr->Compose(composer);
			pExprLast = pExpr;
			composer.Flush();
			if (Error::IsIssued()) break;
			const PUnit* pPUnitSentinel = composer.PeekPUnitCont();
			if (!pPUnit && !(pPUnit = composer.GetPUnitFirst())) continue;
			//PUnit::Print(pPUnit, pPUnitSentinel);
			pProcessor->SetPUnitNext(pPUnit);
			while (pPUnit != pPUnitSentinel && pProcessor->GetContFlag()) {
				pPUnit->Exec(*pProcessor);
				pPUnit = pProcessor->GetPUnitNext();
				if (Error::IsIssued()) break;
			}
			if (Error::IsIssued()) {
				Error::Print(*Stream::CErr);
				pProcessor->ClearValueStack();
				pProcessor->ClearError();
				pPUnit = composer.PeekPUnitCont();
				break;
			} else {
				RefPtr<Value> pValue(pProcessor->PopValue());
				if (pValue->IsValid()) stream.Printf("%s\n", pValue->ToString().c_str());
			}
		}
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
		strLine += ch;
		if (ch == '\n') break;
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
	strLine += '\n';
	return true;
}
#endif

}

int main(int argc, char* argv[])
{
	Gurax::Initialize();
	return Gurax::Main(argc, argv);
}
